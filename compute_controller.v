// Filename: compute_controller.v
// Description: A reconstructed, high-performance compute controller.
//              This version is adapted to work with an external Data_Formatter
//              and a pure-computation systolic array. It no longer handles
//              data feeding, only high-level control and result accumulation.
//              MODIFIED: Fixed SRAM read alignment bug.
//
`timescale 1ns / 1ps

module compute_controller #(
    parameter TILE_SIZE                 = 16,
    parameter PE_ACCUM_DATA_WIDTH       = 32,
    parameter MAIN_MEM_DATA_WIDTH_BITS  = TILE_SIZE * PE_ACCUM_DATA_WIDTH,
    // This delay is AFTER the SRAM data is correctly latched
    parameter ACCUM_PIPE_DELAY          = 2
)(
    // --- Control Interface ---
    input wire                                          clk,
    input wire                                          rst_n,
    input wire                                          compute_req, // From top-level accelerator
    output reg                                          compute_busy,
    output reg                                          compute_done,

    // --- Systolic Array (SA) Result Interface ---
    output wire                                         dut_ready_for_sa_partial_sum,
    input wire                                          sa_partial_sum_valid,
    input wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]    sa_partial_sum_in,
    input wire [$clog2(TILE_SIZE)-1:0]                  sa_partial_sum_row_idx,
    input wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]    sa_final_sum_in,
    input wire                                          sa_tile_all_pes_done_one_pass, // Still useful for observation/debug

    // --- Systolic Array & Formatter Control Interface ---
    output reg                                          ctrl_start_new_systolic_pass,
    output wire                                         ctrl_activate_pe_computation,

    // --- SA Final Adder Control Ports ---
    output wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]   ctrl_c_data_to_sa,
    output wire                                         ctrl_enable_final_add,
    output wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]   ctrl_partial_sum_to_sa,

    // --- C-ACCUM (Accumulator SRAM) Interface ---
    output wire [$clog2(TILE_SIZE)-1:0]                 c_accum_raddr,
    input wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]           c_accum_rdata,
    output wire [$clog2(TILE_SIZE)-1:0]                 c_accum_waddr,
    output wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]          c_accum_wdata,
    output wire                                         c_accum_we
);

    //======================================================================
    //== Internal Parameters and Signals
    //======================================================================

    // -- Internal state --
    reg  is_computing;
    reg  [$clog2(TILE_SIZE):0] processed_row_count;

    // -- Accumulation pipeline registers --
    // These registers are for data *after* SRAM read is aligned
    reg [ACCUM_PIPE_DELAY-1:0]                  pipe_valid;
    reg [$clog2(TILE_SIZE)-1:0]                 pipe_row_idx      [ACCUM_PIPE_DELAY-1:0];
    reg signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]   pipe_partial_sum  [ACCUM_PIPE_DELAY-1:0];
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0]          pipe_c_old_data   [ACCUM_PIPE_DELAY-1:0];

    // -- NEW: Stage 0 registers to hold SA data while SRAM reads --
    reg                                         s0_sa_valid_reg;
    reg [$clog2(TILE_SIZE)-1:0]                 s0_sa_row_idx_reg;
    reg signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]   s0_sa_partial_sum_reg;

    // -- Handshake signal --
    wire handshake_fire;
    genvar i;

    //======================================================================
    //== Core Logic Implementation
    //======================================================================

    // --- Handshake & Status Control ---
    assign dut_ready_for_sa_partial_sum = 1'b1;
    assign handshake_fire = sa_partial_sum_valid && dut_ready_for_sa_partial_sum;
    assign ctrl_activate_pe_computation = is_computing;

    // Main Control Logic (FSM-like behavior) - NO CHANGE HERE
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            is_computing <= 1'b0;
            compute_busy <= 1'b0;
            compute_done <= 1'b0;
            ctrl_start_new_systolic_pass <= 1'b0;
            processed_row_count <= 0;
        end else begin
            ctrl_start_new_systolic_pass <= 1'b0;
            if (compute_req && !is_computing) begin
                is_computing <= 1'b1;
                compute_busy <= 1'b1;
                compute_done <= 1'b0;
                ctrl_start_new_systolic_pass <= 1'b1;
                processed_row_count <= 0;
            end else if (is_computing) begin
                compute_busy <= 1'b1;
                if (c_accum_we) begin
                    processed_row_count <= processed_row_count + 1;
                end
                if (c_accum_we && (processed_row_count == TILE_SIZE - 1)) begin
                    is_computing <= 1'b0;
                    compute_busy <= 1'b0;
                    compute_done <= 1'b1;
                end else begin
                    compute_done <= 1'b0;
                end
            end else begin
                compute_busy <= 1'b0;
                compute_done <= 1'b0;
                if (!compute_req) begin
                    processed_row_count <= 0;
                end
            end
        end
    end

    // --- High-Performance Accumulation Pipeline ---

    // **MODIFIED PART STARTS HERE**

    // Stage 0: Latch SA data and issue read command to C-ACCUM SRAM.
    // SRAM gets address based on current SA output
    assign c_accum_raddr = sa_partial_sum_row_idx;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s0_sa_valid_reg <= 1'b0;
            s0_sa_row_idx_reg <= 0;
            s0_sa_partial_sum_reg <= 0;
        end else begin
            // s0_sa_valid_reg <= handshake_fire; // Capture if SA had valid data this cycle
            // if (handshake_fire) begin
            //     s0_sa_row_idx_reg     <= sa_partial_sum_row_idx;
            //     s0_sa_partial_sum_reg <= sa_partial_sum_in;
            // end
            s0_sa_valid_reg <= handshake_fire && is_computing;
            if (handshake_fire && is_computing) begin
                s0_sa_row_idx_reg     <= sa_partial_sum_row_idx;
                s0_sa_partial_sum_reg <= sa_partial_sum_in;
            end
        end
    end

`ifdef DEBUG_CTRL_ACCUM
    always @(posedge clk) begin
        if (rst_n && s0_sa_valid_reg) begin // When s0 latches valid SA data
            $display("[%0t] [CTRL_S0_LATCH] SA_Valid_Latched: %b, SA_Row_Latched: %d, SA_PSum_Latched[0]=%d",
                     $time,
                     s0_sa_valid_reg,
                     s0_sa_row_idx_reg,
                     s0_sa_partial_sum_reg[PE_ACCUM_DATA_WIDTH-1:0]);
        end
    end
`endif

    // Pipeline Stage 1 (was original pipe[0]):
    // Latch s0 SA data (from previous cycle) and c_accum_rdata (which is now valid for s0_sa_row_idx_reg).
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            pipe_valid[0] <= 1'b0;
        end else begin
            pipe_valid[0] <= s0_sa_valid_reg; // Data is valid if SA data was valid in the PREVIOUS cycle
            if (s0_sa_valid_reg) begin // If SA data from PREVIOUS cycle was valid
                pipe_row_idx[0]       <= s0_sa_row_idx_reg;       // SA row_idx from PREVIOUS cycle
                pipe_partial_sum[0]   <= s0_sa_partial_sum_reg; // SA partial_sum from PREVIOUS cycle
                pipe_c_old_data[0]    <= c_accum_rdata;          // SRAM data corresponding to s0_sa_row_idx_reg
            end
        end
    end

`ifdef DEBUG_CTRL_ACCUM
    always @(posedge clk) begin
        if (rst_n && pipe_valid[0]) begin // This is inside the existing always block for pipe_valid[0]
            $display("[%0t] [CTRL_PIPE0_LATCH] Pipe0_Valid: %b, Row: %d, PSum_SA[0]=%d, C_Old[0]=%d (from SRAM rdata)",
                     $time,
                     pipe_valid[0], // Value being assigned
                     pipe_row_idx[0],
                     pipe_partial_sum[0][PE_ACCUM_DATA_WIDTH-1:0],
                     pipe_c_old_data[0][PE_ACCUM_DATA_WIDTH-1:0]);
        end
    end
`endif

    // Pipeline Stage 2 to N-1: Intermediate registers
    generate
        for (i = 0; i < ACCUM_PIPE_DELAY - 1; i = i + 1) begin: pipe_middle_stages
            always @(posedge clk or negedge rst_n) begin
                if (!rst_n) begin
                    pipe_valid[i+1] <= 1'b0;
                end else begin
                    pipe_valid[i+1]       <= pipe_valid[i];
                    pipe_row_idx[i+1]     <= pipe_row_idx[i];
                    pipe_partial_sum[i+1] <= pipe_partial_sum[i];
                    pipe_c_old_data[i+1]  <= pipe_c_old_data[i];
                end
            end
        end
    endgenerate

    // Pipeline Last Stage: Drive final adder and C-ACCUM write
    assign ctrl_c_data_to_sa      = pipe_c_old_data[ACCUM_PIPE_DELAY-1];
    assign ctrl_partial_sum_to_sa = pipe_partial_sum[ACCUM_PIPE_DELAY-1];
    assign ctrl_enable_final_add  = pipe_valid[ACCUM_PIPE_DELAY-1];

    assign c_accum_waddr = pipe_row_idx[ACCUM_PIPE_DELAY-1];
    assign c_accum_wdata = sa_final_sum_in;
    assign c_accum_we    = pipe_valid[ACCUM_PIPE_DELAY-1];

`ifdef DEBUG_CTRL_ACCUM
    always @(posedge clk) begin
        if (rst_n && pipe_valid[ACCUM_PIPE_DELAY-1]) begin // This is when c_accum_we is high
            $display("[%0t] [CTRL_FINAL_ACCUM] ToSRAM_Row: %d, PSum_Input[0]: %d, C_Old_Input[0]: %d, FinalSumToSRAM[0]: %d (c_accum_wdata[0])",
                     $time,
                     pipe_row_idx[ACCUM_PIPE_DELAY-1],
                     pipe_partial_sum[ACCUM_PIPE_DELAY-1][PE_ACCUM_DATA_WIDTH-1:0],
                     pipe_c_old_data[ACCUM_PIPE_DELAY-1][PE_ACCUM_DATA_WIDTH-1:0],
                     c_accum_wdata[PE_ACCUM_DATA_WIDTH-1:0]); // c_accum_wdata is sa_final_sum_in
        end
    end
`endif

    // **MODIFIED PART ENDS HERE**

endmodule
