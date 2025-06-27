// sa_enhanced.v
// Description: Enhanced Systolic Array with C-SRAM accumulation.
// REVISED: Implements a "blind-start" strategy for the accumulation pipeline.
//          It waits only for the first row to be computed, then runs the
//          high-throughput 2-cycle/row accumulation pipeline, trusting
//          the architectural determinism.

`timescale 1ns / 1ps

module sa_enhanced #(
    parameter SIZE = 16,
    parameter INPUT_DATA_WIDTH = 8,
    parameter PE_ACCUM_DATA_WIDTH = 32,
    parameter ROW_WIDTH_BITS = SIZE * PE_ACCUM_DATA_WIDTH // Typically 16*32 = 512
)(
    // --- Clock and Reset ---
    input wire clk,
    input wire rst_n,

    // --- Control from Compute Controller (Interface Unchanged) ---
    input wire start_new_k_iteration,
    input wire activate_pe_computation,
    input wire k_tile_is_first,

    // --- Data Input from Formatter/TB (Interface Unchanged) ---
    input wire [SIZE*INPUT_DATA_WIDTH-1:0] array_a_in,
    input wire [SIZE*INPUT_DATA_WIDTH-1:0] array_b_in,
    input wire [SIZE-1:0] array_a_valid_in_indywidual,
    input wire [SIZE-1:0] array_b_valid_in_indywidual,

    // --- Status to Compute Controller (Interface Unchanged) ---
    output reg sa_k_iteration_accum_done,
    output reg sa_busy,

    // --- SRAM C Port A Interface (SA is master, Interface Unchanged) ---
    output reg [$clog2(SIZE)-1:0]               sram_c_raddr_A_to_sram,
    input wire [ROW_WIDTH_BITS-1:0]             sram_c_rdata_A_from_sram,
    output reg [$clog2(SIZE)-1:0]               sram_c_waddr_to_sram,
    output reg signed [ROW_WIDTH_BITS-1:0]      sram_c_wdata_to_sram,
    output reg                                  sram_c_we_to_sram
);

    // --- Internal Wires for PE Array (Unchanged) ---
    wire signed [INPUT_DATA_WIDTH-1:0]      a_data_wires [SIZE-1:0][SIZE:0];
    wire signed [INPUT_DATA_WIDTH-1:0]      b_data_wires [SIZE:0][SIZE-1:0];
    wire                                    a_valid_wires [SIZE-1:0][SIZE:0];
    wire                                    b_valid_wires [SIZE:0][SIZE-1:0];
    wire signed [PE_ACCUM_DATA_WIDTH-1:0]   pe_result_out_internal [SIZE-1:0][SIZE-1:0];
    wire                                    pe_result_valid_internal [SIZE-1:0][SIZE-1:0];

    // --- Row-wise Status Tracking (Unchanged structure, but accum logic will differ) ---
    reg  [SIZE-1:0] row_calc_done_q;
    reg  [SIZE-1:0] row_accum_done_q;
    wire all_rows_accumulated = &row_accum_done_q;

    // --- Wires for Done Propagation (Unchanged) ---
    wire pe_row_propagate_done_chain [SIZE-1:0][SIZE:0];
    wire last_column_done_signals [SIZE-1:0];

    // --- Register for k_tile_is_first status (Unchanged) ---
    reg k_tile_is_first_reg;

    // --- Shadow Buffer for Pk (Unchanged) ---
    reg signed [ROW_WIDTH_BITS-1:0] pk_shadow_buffer [0:SIZE-1];

    // --- Main SA Control FSM (Unchanged) ---
    typedef enum logic [0:0] {
        SA_FSM_IDLE             = 1'b0,
        SA_FSM_COMPUTE_AND_ACCUM = 1'b1
    } sa_fsm_state_e;
    sa_fsm_state_e sa_fsm_state_q, sa_fsm_state_d;

    // --- Accumulation Sub-control (Unchanged) ---
    reg [$clog2(SIZE)-1:0] accum_current_row_q, accum_current_row_d;
    typedef enum logic [1:0] {
        ACCUM_PIPE_IDLE = 2'b00,
        ACCUM_PIPE_SRAM_READ_ISSUED = 2'b01,
        ACCUM_PIPE_SRAM_DATA_BACK_ADD_WRITE_ISSUED = 2'b10
    } accum_pipe_state_e;
    accum_pipe_state_e accum_pipe_state_q, accum_pipe_state_d;

    reg signed [ROW_WIDTH_BITS-1:0] pk_row_for_accum_q;
    reg signed [ROW_WIDTH_BITS-1:0] sram_old_row_for_accum_q;

    // --- Row Adder (Unchanged) ---
    wire signed [ROW_WIDTH_BITS-1:0] accumulated_row_val;
    genvar r_add_gen_local;
    generate
        for (r_add_gen_local = 0; r_add_gen_local < SIZE; r_add_gen_local = r_add_gen_local + 1) begin : row_adder_elements
            assign accumulated_row_val[r_add_gen_local*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] =
                   pk_row_for_accum_q[r_add_gen_local*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] +
                   sram_old_row_for_accum_q[r_add_gen_local*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH];
        end
    endgenerate

    //===============================================================
    //== PE Array Instantiation and Boundary Connections (Unchanged)
    //===============================================================
    // ... (This entire section is identical, so it is omitted for brevity) ...
    genvar r_gen_local, c_gen_local;
    generate
        for (r_gen_local = 0; r_gen_local < SIZE; r_gen_local = r_gen_local + 1) begin : connect_a_to_pe_boundary
            assign a_data_wires[r_gen_local][0] = array_a_in[r_gen_local*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
            assign a_valid_wires[r_gen_local][0] = array_a_valid_in_indywidual[r_gen_local];
        end
        for (c_gen_local = 0; c_gen_local < SIZE; c_gen_local = c_gen_local + 1) begin : connect_b_to_pe_boundary
            assign b_data_wires[0][c_gen_local] = array_b_in[c_gen_local*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
            assign b_valid_wires[0][c_gen_local] = array_b_valid_in_indywidual[c_gen_local];
        end
    endgenerate

    generate
        for (r_gen_local = 0; r_gen_local < SIZE; r_gen_local = r_gen_local + 1) begin : pe_row_gen
            assign pe_row_propagate_done_chain[r_gen_local][0] = 1'b1;

            for (c_gen_local = 0; c_gen_local < SIZE; c_gen_local = c_gen_local + 1) begin : pe_col_gen
                pe #(
                    .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH),
                    .ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH),
                    .MAC_COUNT_TARGET(SIZE),
                    .ROW_IDX(r_gen_local),
                    .COL_IDX(c_gen_local)
                ) u_pe_inst (
                    .clk(clk),
                    .rst_n(rst_n),
                    .enable(activate_pe_computation),
                    .clear_accumulator(1'b0),
                    .conditionally_clear_sum(1'b1),
                    .a_valid_in(a_valid_wires[r_gen_local][c_gen_local]),
                    .a_data_in(a_data_wires[r_gen_local][c_gen_local]),
                    .a_valid_out(a_valid_wires[r_gen_local][c_gen_local+1]),
                    .a_data_out(a_data_wires[r_gen_local][c_gen_local+1]),
                    .b_valid_in(b_valid_wires[r_gen_local][c_gen_local]),
                    .b_data_in(b_data_wires[r_gen_local][c_gen_local]),
                    .b_valid_out(b_valid_wires[r_gen_local+1][c_gen_local]),
                    .b_data_out(b_data_wires[r_gen_local+1][c_gen_local]),
                    .result_out(pe_result_out_internal[r_gen_local][c_gen_local]),
                    .result_valid(pe_result_valid_internal[r_gen_local][c_gen_local]),
                    .start_new_systolic_pass(start_new_k_iteration),
                    .pe_row_propagate_done_in(pe_row_propagate_done_chain[r_gen_local][c_gen_local]),
                    .pe_row_propagate_done_out(pe_row_propagate_done_chain[r_gen_local][c_gen_local+1])
                );
            end
            assign last_column_done_signals[r_gen_local] = pe_row_propagate_done_chain[r_gen_local][SIZE];
        end
    endgenerate


    // --- Row-wise Calculation Done Latching and Status Update (Unchanged) ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            row_calc_done_q <= 0;
        end else begin
            if (start_new_k_iteration) begin
                row_calc_done_q <= 0;
            end else if (sa_fsm_state_q == SA_FSM_COMPUTE_AND_ACCUM) begin
                for (integer i = 0; i < SIZE; i = i + 1) begin
                    if (last_column_done_signals[i] && !row_calc_done_q[i]) begin
                        row_calc_done_q[i] <= 1'b1;
                        for (integer c_idx = 0; c_idx < SIZE; c_idx = c_idx + 1) begin
                            pk_shadow_buffer[i][c_idx*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] <= pe_result_out_internal[i][c_idx];
                        end
                    end
                end
            end
        end
    end

    // --- Row-wise Accumulation Done Status Update (Unchanged) ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            row_accum_done_q <= 0;
        end else begin
            if (start_new_k_iteration) begin
                row_accum_done_q <= 0;
            end else if (sram_c_we_to_sram) begin
                row_accum_done_q[sram_c_waddr_to_sram] <= 1'b1;
            end
        end
    end

    // --- Main SA Control FSM (Sequential Part, Unchanged) ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            sa_fsm_state_q <= SA_FSM_IDLE;
            sa_busy <= 1'b0;
            sa_k_iteration_accum_done <= 1'b0;
            accum_current_row_q <= 0;
            accum_pipe_state_q <= ACCUM_PIPE_IDLE;
            k_tile_is_first_reg <= 1'b0;
        end else begin
            sa_fsm_state_q <= sa_fsm_state_d;
            sa_busy <= (sa_fsm_state_d != SA_FSM_IDLE);

            accum_current_row_q <= accum_current_row_d;
            accum_pipe_state_q <= accum_pipe_state_d;
            
            if (start_new_k_iteration) begin
                k_tile_is_first_reg <= k_tile_is_first;
            end

            if (accum_pipe_state_q == ACCUM_PIPE_SRAM_READ_ISSUED && accum_pipe_state_d == ACCUM_PIPE_SRAM_DATA_BACK_ADD_WRITE_ISSUED) begin
                 sram_old_row_for_accum_q <= sram_c_rdata_A_from_sram;
                 pk_row_for_accum_q       <= pk_shadow_buffer[accum_current_row_q];
            end

            sa_k_iteration_accum_done <= (sa_fsm_state_q == SA_FSM_COMPUTE_AND_ACCUM) && (sa_fsm_state_d == SA_FSM_IDLE);
        end
    end

    // --- [REVISED] Main SA Control FSM (Combinational Part) ---
    always @(*) begin
        sa_fsm_state_d = sa_fsm_state_q;
        // Default SRAM signals
        sram_c_raddr_A_to_sram = accum_current_row_q;
        sram_c_waddr_to_sram   = accum_current_row_q;
        sram_c_wdata_to_sram   = 0;
        sram_c_we_to_sram      = 1'b0;

        // Default next state for control registers
        accum_current_row_d = accum_current_row_q;
        accum_pipe_state_d = accum_pipe_state_q;

        case (sa_fsm_state_q)
            SA_FSM_IDLE: begin
                if (start_new_k_iteration) begin
                    sa_fsm_state_d = SA_FSM_COMPUTE_AND_ACCUM;
                    accum_current_row_d = 0;
                    accum_pipe_state_d = ACCUM_PIPE_IDLE;
                end
            end

            SA_FSM_COMPUTE_AND_ACCUM: begin
                if (all_rows_accumulated) begin
                    sa_fsm_state_d = SA_FSM_IDLE;
                    accum_pipe_state_d = ACCUM_PIPE_IDLE;
                end else begin
                    case (accum_pipe_state_q)
                        ACCUM_PIPE_IDLE: begin
                            // **BLIND-START HANDSHAKE**: Only check the very first row.
                            // The `row_accum_done_q[0]` check prevents re-starting if we loop back to this state for some reason.
                            if (last_column_done_signals[0] && !row_accum_done_q[0]) begin
                                accum_pipe_state_d = ACCUM_PIPE_SRAM_READ_ISSUED;
                                sram_c_raddr_A_to_sram = 0; // Start with row 0
                            end
                            // Once started, we never return to IDLE until the entire K-iter is done.
                        end

                        ACCUM_PIPE_SRAM_READ_ISSUED: begin
                            // Wait for SRAM data, then move to write stage.
                            accum_pipe_state_d = ACCUM_PIPE_SRAM_DATA_BACK_ADD_WRITE_ISSUED;
                        end

                        ACCUM_PIPE_SRAM_DATA_BACK_ADD_WRITE_ISSUED: begin
                            // **HIGH-THROUGHPUT 2-CYCLE LOGIC**
                            // Action 1: Issue write for the current row (`accum_current_row_q`)
                            sram_c_waddr_to_sram = accum_current_row_q;
                            sram_c_we_to_sram    = 1'b1;
                            
                            if (k_tile_is_first_reg) begin
                                sram_c_wdata_to_sram = pk_row_for_accum_q;
                            end else begin
                                sram_c_wdata_to_sram = accumulated_row_val;
                            end
                            
                            // Action 2: Simultaneously issue read for the next row
                            if (accum_current_row_q == SIZE - 1) begin
                                // Last row's write is issued. Pipeline is done.
                                accum_pipe_state_d = ACCUM_PIPE_IDLE; 
                            end else begin
                                // Fire and forget: move to next row and issue its read immediately.
                                accum_current_row_d = accum_current_row_q + 1;
                                accum_pipe_state_d = ACCUM_PIPE_SRAM_READ_ISSUED;
                                sram_c_raddr_A_to_sram = accum_current_row_q + 1;
                            end
                        end
                    endcase
                end
            end
        endcase
    end

endmodule