// accelerator.v

`timescale 1ns / 1ps

module accelerator #(
    parameter MATRIX_SIZE               = 48,
    parameter TILE_SIZE                 = 16,
    parameter INPUT_DATA_WIDTH          = 8,
    parameter PE_ACCUM_DATA_WIDTH       = 32,
    parameter MAIN_MEM_DATA_WIDTH_BYTES = 8, // 64-bit bus
    parameter MAIN_MEM_ADDR_WIDTH       = 32
)(
    input wire clk,
    input wire rst_n,

    // Interface to control the accelerator
    input wire start_computation,
    output reg computation_done,

    // Main Memory Interface
    output reg                                          mem_req_valid,
    output reg                                          mem_req_write,
    output reg [MAIN_MEM_ADDR_WIDTH-1:0]                mem_req_addr,
    output reg [MAIN_MEM_DATA_WIDTH_BYTES*8-1:0]        mem_req_wdata,
    input wire                                          mem_req_ready,
    input wire                                          mem_resp_valid,
    input wire [MAIN_MEM_DATA_WIDTH_BYTES*8-1:0]        mem_resp_rdata,
    input wire                                          mem_write_done
);

    localparam NUM_TILES_PER_DIM = MATRIX_SIZE / TILE_SIZE; // 32
    localparam TILE_ELEMENTS     = TILE_SIZE * TILE_SIZE;   // 256
    localparam A_B_TILE_BYTES    = TILE_ELEMENTS * (INPUT_DATA_WIDTH / 8); // 256 Bytes
    localparam C_TILE_BYTES      = TILE_ELEMENTS * (PE_ACCUM_DATA_WIDTH / 8); // 1024 Bytes
    localparam A_B_LOAD_CYCLES   = A_B_TILE_BYTES / MAIN_MEM_DATA_WIDTH_BYTES; // 32
    localparam C_WRITE_CYCLES    = C_TILE_BYTES / MAIN_MEM_DATA_WIDTH_BYTES;   // 128
    localparam COMPUTE_CYCLES    = 3 * TILE_SIZE - 2; // 46

    // Base addresses for matrices in main memory
    parameter BASE_ADDR_A = 32'h10000000;
    parameter BASE_ADDR_B = 32'h20000000;
    parameter BASE_ADDR_C = 32'h30000000;

    // SRAM instances for ping-pong buffering and accumulation
    reg signed [INPUT_DATA_WIDTH-1:0]       sram_a_ping [TILE_ELEMENTS-1:0];
    reg signed [INPUT_DATA_WIDTH-1:0]       sram_a_pong [TILE_ELEMENTS-1:0];
    reg signed [INPUT_DATA_WIDTH-1:0]       sram_b_ping [TILE_ELEMENTS-1:0];
    reg signed [INPUT_DATA_WIDTH-1:0]       sram_b_pong [TILE_ELEMENTS-1:0];
    reg signed [PE_ACCUM_DATA_WIDTH-1:0]    sram_c_accum [TILE_ELEMENTS-1:0];

    // Systolic Array Instance
    systolic_array #(
        .SIZE(TILE_SIZE),
        .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH),
        .PE_ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH)
    ) systolic_array_inst (
        .clk(clk),
        .rst_n(rst_n),
        .clear_all_pe_accumulators(ctrl_clear_all_pe_accumulators),
        .conditionally_clear_pe_sums_level(ctrl_conditionally_clear_pe_sums_level),
        .activate_pe_computation(ctrl_activate_pe_computation),
        .array_data_valid_in(ctrl_array_data_valid_in),
        .array_a_in(sa_array_a_in_flat),
        .array_b_in(sa_array_b_in_flat),
        .select_output_row_idx(ctrl_select_output_row_idx),
        .enable_tile_row_output(ctrl_enable_tile_row_output),
        .array_a_data_valid_out(),
        .array_a_out(),
        .array_b_data_valid_out(),
        .array_b_out(),
        .tile_row_result_out(sa_tile_row_result_out),
        .tile_row_result_valid(sa_tile_row_result_valid),
        .tile_all_pes_done_one_pass(sa_tile_all_pes_done_one_pass),
        .start_new_systolic_pass(ctrl_start_new_systolic_pass)
    );

    // Control signals for systolic array
    reg ctrl_clear_all_pe_accumulators;
    reg ctrl_conditionally_clear_pe_sums_level;
    reg ctrl_activate_pe_computation;
    reg ctrl_array_data_valid_in;
    reg ctrl_start_new_systolic_pass;
    reg [$clog2(TILE_SIZE)-1:0] ctrl_select_output_row_idx;
    reg ctrl_enable_tile_row_output;

    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sa_array_a_in_flat;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sa_array_b_in_flat;
    wire signed [TILE_SIZE*PE_ACCUM_DATA_WIDTH-1:0] sa_tile_row_result_out;
    wire sa_tile_row_result_valid;
    wire sa_tile_all_pes_done_one_pass;

    // Main FSM
    typedef enum logic [3:0] { IDLE, INIT, LOAD_FIRST, COMPUTE_LOOP, WRITE_LAST, DONE } state_t;
    state_t current_state, next_state;

    // Loop counters
    reg [$clog2(NUM_TILES_PER_DIM)-1:0] i_tile, j_tile, k_tile;

    // Ping-pong buffer control
    reg compute_is_ping; // 1: compute uses ping, load to pong. 0: compute uses pong, load to ping

    // --- Sub-module control signals and status ---
    // Loader
    reg load_req;
    reg [$clog2(NUM_TILES_PER_DIM)-1:0] load_i, load_j, load_k;
    reg load_to_ping;
    wire load_busy;
    wire load_done;

    // Compute
    reg compute_req;
    reg [$clog2(NUM_TILES_PER_DIM)-1:0] compute_k;
    wire compute_busy;
    wire compute_done;

    // Writer
    reg write_req;
    reg [$clog2(NUM_TILES_PER_DIM)-1:0] write_i, write_j;
    wire write_busy;
    wire write_done;

    // Top-level FSM
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state <= IDLE;
            computation_done <= 1'b0;
            i_tile <= 0; j_tile <= 0; k_tile <= 0;
        end else begin
            current_state <= next_state;
        end
    end

    always_comb begin
        next_state = current_state;
        computation_done = 1'b0;

        // Default submodule requests to low
        load_req = 1'b0;
        compute_req = 1'b0;
        write_req = 1'b0;

        case(current_state)
            IDLE: begin
                if (start_computation) begin
                    next_state = INIT;
                end
            end
            INIT: begin
                i_tile = 0; j_tile = 0; k_tile = 0;
                compute_is_ping = 1'b1; // First compute will use ping
                next_state = LOAD_FIRST;
            end
            LOAD_FIRST: begin
                // Load the very first tiles for C(i,j) = A(i,0)*B(0,j)
                load_req = 1'b1;
                load_i = i_tile; load_j = j_tile; load_k = k_tile;
                load_to_ping = 1'b1; // Load to ping
                if (load_done) begin // Wait for the first load to complete
                    next_state = COMPUTE_LOOP;
                end
            end
            COMPUTE_LOOP: begin
                // Main pipeline loop. Three things happen concurrently:
                // 1. Compute C_ij += A_ik * B_kj
                // 2. Load A_i(k+1) and B_(k+1)j for the next iteration
                // 3. Write back C_i(j-1) if it's ready

                // Trigger computation for k_tile
                compute_req = !compute_busy;
                compute_k = k_tile;

                // Trigger load for next k (k_tile+1) if not the last k
                if (k_tile < NUM_TILES_PER_DIM - 1) begin
                    load_req = !load_busy;
                    load_i = i_tile; load_j = j_tile; load_k = k_tile + 1;
                    load_to_ping = ~compute_is_ping; // Load to the other buffer
                end

                // Trigger write for previous C tile (C_i(j-1)) if k is 0 and it's not the very first tile
                if (k_tile == 0 && (i_tile != 0 || j_tile != 0)) begin
                    write_req = !write_busy;
                    // Calculate previous tile indices
                    write_i = (j_tile == 0) ? (i_tile - 1) : i_tile;
                    write_j = (j_tile == 0) ? (NUM_TILES_PER_DIM - 1) : (j_tile - 1);
                end

                // When compute for k_tile is done, and load for k_tile+1 is also done, advance k
                if (compute_done && (load_done || k_tile == NUM_TILES_PER_DIM - 1)) begin
                    k_tile = k_tile + 1;
                    compute_is_ping = ~compute_is_ping; // Swap buffers for next compute

                    if (k_tile == NUM_TILES_PER_DIM) begin // Finished a C_ij tile
                        k_tile = 0;
                        j_tile = j_tile + 1;
                        if (j_tile == NUM_TILES_PER_DIM) begin
                            j_tile = 0;
                            i_tile = i_tile + 1;
                            if (i_tile == NUM_TILES_PER_DIM) begin
                                next_state = WRITE_LAST;
                            end
                        end
                    end
                end
            end
            WRITE_LAST: begin
                // Write the very last C tile
                write_req = 1'b1;
                write_i = NUM_TILES_PER_DIM - 1;
                write_j = NUM_TILES_PER_DIM - 1;
                if(write_done) begin
                    next_state = DONE;
                end
            end
            DONE: begin
                computation_done = 1'b1;
                next_state = IDLE;
            end
        endcase
    end

    // --- Data Loader Sub-module (Conceptual FSM) ---
    reg [2:0] loader_state;
    reg [$clog2(A_B_LOAD_CYCLES)-1:0] load_a_cnt, load_b_cnt;
    reg [MAIN_MEM_ADDR_WIDTH-1:0] load_addr;
    assign load_busy = (loader_state != 0);
    assign load_done = (loader_state == 4);

    always @(posedge clk or negedge rst_n) begin
        if(!rst_n) begin loader_state <= 0; end
        else begin
            case(loader_state)
                0: if(load_req) begin loader_state <= 1; load_a_cnt <= 0; end // Idle
                1: begin // Load A
                    // ... Address calculation logic for A[load_i][load_k] ...
                    // ... Memory request logic ...
                    if (mem_req_ready && mem_resp_valid) load_a_cnt <= load_a_cnt + 1;
                    if (load_a_cnt == A_B_LOAD_CYCLES - 1) begin loader_state <= 2; load_b_cnt <= 0; end
                end
                2: begin // Load B
                    // ... Address calculation logic for B[load_k][load_j] ...
                    // ... Memory request logic ...
                    if (mem_req_ready && mem_resp_valid) load_b_cnt <= load_b_cnt + 1;
                    if (load_b_cnt == A_B_LOAD_CYCLES - 1) loader_state <= 3;
                end
                3: begin loader_state <= 4; end // Done signal high for one cycle
                4: begin loader_state <= 0; end
            endcase
            // ... Logic to write mem_resp_rdata into sram_a/b_ping/pong based on load_to_ping ...
        end
    end


    // --- Compute Controller Sub-module (Conceptual FSM) ---
    // This module reads from the correct ping/pong buffer, feeds the SA,
    // and accumulates results into sram_c_accum.
    // ... Implementation would involve another state machine and counters ...
    assign compute_busy = 0; // Placeholder
    assign compute_done = 0; // Placeholder


    // --- Data Writer Sub-module (Conceptual FSM) ---
    // This module reads from sram_c_accum and writes back to main memory.
    // ... Implementation would involve another state machine and counters ...
    assign write_busy = 0; // Placeholder
    assign write_done = 0; // Placeholder


    // --- Logic to feed data from SRAM to Systolic Array ---
    // This part requires careful mapping based on how data is stored in SRAM
    // and how the systolic array expects it. This is a simplified example.
    wire signed [INPUT_DATA_WIDTH-1:0] current_a_buf [TILE_ELEMENTS-1:0];
    wire signed [INPUT_DATA_WIDTH-1:0] current_b_buf [TILE_ELEMENTS-1:0];
    assign current_a_buf = compute_is_ping ? sram_a_ping : sram_a_pong;
    assign current_b_buf = compute_is_ping ? sram_b_ping : sram_b_pong;

    // ... Generate block to connect current_a/b_buf to sa_array_a/b_in_flat ...
    // This connection depends on the data layout in the tile buffers.

endmodule