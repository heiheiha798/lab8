//
// Filename: data_formatter.v
// Description: A high-performance data formatter for the systolic array.
//              It reads data from banked on-chip SRAMs and generates the
//              time-skewed data wavefronts required by the pure-computation
//              systolic array, enabling maximum throughput.
//
`timescale 1ns / 1ps

module data_formatter #(
    parameter TILE_SIZE         = 16,
    parameter INPUT_DATA_WIDTH  = 8
)(
    // --- Control Interface ---
    input wire                                  clk,
    input wire                                  rst_n,
    input wire                                  start_pass, // From Compute Controller
    output reg                                  pass_done,  // To Compute Controller

    // --- SRAM Read Interface (Banked) ---
    // Assumes 16 independent banks for A and 16 for B.
    // Each bank stores one row/column of a tile.
    output wire [TILE_SIZE*$clog2(TILE_SIZE)-1:0] sram_a_addr,
    input wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0]   sram_a_rdata, // Concatenated data from all A banks
    output wire [TILE_SIZE*$clog2(TILE_SIZE)-1:0] sram_b_addr,
    input wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0]   sram_b_rdata, // Concatenated data from all B banks

    // --- Systolic Array Feed Interface ---
    output reg [TILE_SIZE*INPUT_DATA_WIDTH-1:0]   skewed_a_out,
    output reg [TILE_SIZE*INPUT_DATA_WIDTH-1:0]   skewed_b_out,
    output reg                                    data_valid_out
);

    //======================================================================
    //== Local Parameters and State Definitions
    //======================================================================
    localparam FSM_STATE_WIDTH   = 2;
    localparam S_IDLE            = {FSM_STATE_WIDTH{1'b0}};
    localparam S_STREAMING       = S_IDLE + 1;
    localparam S_DONE            = S_STREAMING + 1;

    // A full data pass requires 2*SIZE - 1 wavefronts. Counter goes from 0 to 2*SIZE-2.
    localparam TIME_COUNTER_WIDTH = $clog2(TILE_SIZE * 2 - 1);
    localparam TIME_COUNTER_MAX   = TILE_SIZE * 2 - 2;

    localparam SRAM_ADDR_WIDTH = $clog2(TILE_SIZE);

    //======================================================================
    //== Internal Registers and Wires
    //======================================================================
    reg [FSM_STATE_WIDTH-1:0] current_state, next_state;
    reg [TIME_COUNTER_WIDTH-1:0] time_cnt;

    // Pipeline register for data read from SRAM to improve timing
    reg [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_a_rdata_reg;
    reg [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_b_rdata_reg;

    //======================================================================
    //== FSM and Control Logic
    //======================================================================

    // FSM state transitions (sequential)
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state <= S_IDLE;
        end else begin
            current_state <= next_state;
        end
    end

    // FSM outputs and next-state logic (combinational)
    always @(*) begin
        next_state      = current_state;
        pass_done       = 1'b0;
        data_valid_out  = 1'b0;

        case (current_state)
            S_IDLE: begin
                if (start_pass) begin
                    next_state = S_STREAMING;
                end
            end
            S_STREAMING: begin
                data_valid_out = 1'b1;
                if (time_cnt == TIME_COUNTER_MAX) begin
                    next_state = S_DONE;
                end
            end
            S_DONE: begin
                pass_done = 1'b1;
                next_state = S_IDLE;
            end
            default: begin
                next_state = S_IDLE;
            end
        endcase
    end

    // Time counter logic (sequential)
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            time_cnt <= 0;
        end else if (current_state == S_IDLE && next_state == S_STREAMING) begin
            time_cnt <= 0; // Reset counter when starting a new pass
        end else if (current_state == S_STREAMING) begin
            time_cnt <= time_cnt + 1;
        end
    end

    //======================================================================
    //== Datapath Logic
    //======================================================================

    // --- SRAM Address Generation (Combinational) ---
    // This logic generates 16 parallel addresses for the 16 SRAM banks each cycle.
    generate
        genvar i;
        for (i = 0; i < TILE_SIZE; i = i + 1) begin : addr_gen_loop
            // The address for bank 'i' is `time - i`.
            // If `time < i`, the subtraction would underflow, but the `valid_mask`
            // ensures that the output data for this bank is zeroed out anyway.
            wire [SRAM_ADDR_WIDTH-1:0] a_addr = time_cnt - i;
            wire [SRAM_ADDR_WIDTH-1:0] b_addr = time_cnt - i;

            assign sram_a_addr[i*SRAM_ADDR_WIDTH +: SRAM_ADDR_WIDTH] = a_addr;
            assign sram_b_addr[i*SRAM_ADDR_WIDTH +: SRAM_ADDR_WIDTH] = b_addr;
        end
    endgenerate


    // --- SRAM Data Pipelining and Skewed Output Generation ---

    // Latch the parallel data read from all SRAM banks
    always @(posedge clk) begin
        sram_a_rdata_reg <= sram_a_rdata;
        sram_b_rdata_reg <= sram_b_rdata;
    end

    // Generate the final skewed output for the systolic array
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            skewed_a_out <= 0;
            skewed_b_out <= 0;
        end else if (data_valid_out) begin // Only update when streaming
            // For each input of the systolic array, select the corresponding
            // data from the pipelined SRAM read data IF it's valid for the
            // current time step. Otherwise, output zero.
            for (integer i = 0; i < TILE_SIZE; i = i + 1) begin
                // A data element for row/col 'i' is valid only when time >= i
                if (time_cnt >= i) begin
                    skewed_a_out[i*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] <= sram_a_rdata_reg[i*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
                    skewed_b_out[i*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] <= sram_b_rdata_reg[i*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
                end else begin
                    // Before its time, feed zeros. The PE will ignore it
                    // because its corresponding valid signal will be low.
                    skewed_a_out[i*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] <= 0;
                    skewed_b_out[i*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] <= 0;
                end
            end
        end else begin
            skewed_a_out <= 0;
            skewed_b_out <= 0;
        end
    end

endmodule