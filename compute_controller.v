//
// Filename: compute_controller.v
// Description: A reconstructed, high-performance compute controller.
//              This version is adapted to work with an external Data_Formatter
//              and a pure-computation systolic array. It no longer handles
//              data feeding, only high-level control and result accumulation.
//
`timescale 1ns / 1ps

module compute_controller #(
    parameter TILE_SIZE                 = 16,
    parameter PE_ACCUM_DATA_WIDTH       = 32,
    parameter MAIN_MEM_DATA_WIDTH_BITS  = TILE_SIZE * PE_ACCUM_DATA_WIDTH,
    // [UNCHANGED] The latency of the accumulation pipeline itself remains the same.
    parameter ACCUM_PIPE_DELAY          = 2
)(
    // --- Control Interface ---
    input wire                                          clk,
    input wire                                          rst_n,
    input wire                                          compute_req, // From top-level accelerator
    output reg                                          compute_busy,
    output reg                                          compute_done,

    // --- Systolic Array (SA) Result Interface ---
    // [UNCHANGED] This interface for receiving results remains the same.
    output wire                                         dut_ready_for_sa_partial_sum,
    input wire                                          sa_partial_sum_valid,
    input wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]    sa_partial_sum_in,
    input wire [$clog2(TILE_SIZE)-1:0]                  sa_partial_sum_row_idx,
    input wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]    sa_final_sum_in,
    input wire                                          sa_tile_all_pes_done_one_pass, // Still useful for observation/debug

    // --- Systolic Array & Formatter Control Interface ---
    // [MODIFIED] This is now a high-level start pulse for both the formatter and the array.
    output reg                                          ctrl_start_new_systolic_pass,
    // [MODIFIED] This is a general enable signal, active during computation.
    output wire                                         ctrl_activate_pe_computation,

    // --- SA Final Adder Control Ports ---
    // [UNCHANGED] This logic is part of the accumulation pipeline.
    output wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]   ctrl_c_data_to_sa,
    output wire                                         ctrl_enable_final_add,
    output wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]   ctrl_partial_sum_to_sa,

    // --- C-ACCUM (Accumulator SRAM) Interface ---
    // [UNCHANGED] The interface to the result accumulator SRAM is identical.
    output wire [$clog2(TILE_SIZE)-1:0]                 c_accum_raddr,
    input wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]           c_accum_rdata,
    output wire [$clog2(TILE_SIZE)-1:0]                 c_accum_waddr,
    output wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]          c_accum_wdata,
    output wire                                         c_accum_we

    // --- [REMOVED] SRAM Read and SA Data Feed Interfaces ---
    // All ports related to reading from A/B SRAMs and feeding the array
    // (sram_a_addr, sram_a_rdata, sa_array_a_in_flat, etc.) have been removed.
    // This functionality is now handled by the Data_Formatter.
);

    //======================================================================
    //== Internal Parameters and Signals
    //======================================================================

    // -- Internal state --
    reg  is_computing; // Main state flag, replaces complex FSM
    reg  [$clog2(TILE_SIZE):0] processed_row_count;

    // -- Accumulation pipeline registers --
    // [UNCHANGED] This pipeline is independent of the data feed mechanism.
    reg [ACCUM_PIPE_DELAY-1:0]                  pipe_valid;
    reg [$clog2(TILE_SIZE)-1:0]                 pipe_row_idx      [ACCUM_PIPE_DELAY-1:0];
    reg signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]   pipe_partial_sum  [ACCUM_PIPE_DELAY-1:0];
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0]          pipe_c_old_data   [ACCUM_PIPE_DELAY-1:0];

    // -- Handshake signal --
    wire handshake_fire;

    // -- [REMOVED] Data feed logic --
    // The `sa_feed_counter` register has been removed.

    genvar i;

    //======================================================================
    //== Core Logic Implementation
    //======================================================================

    // --- Handshake & Status Control ---
    assign dut_ready_for_sa_partial_sum = 1'b1; // Assume accum pipeline can always accept data
    assign handshake_fire = sa_partial_sum_valid && dut_ready_for_sa_partial_sum;

    // This signal is a level that stays high for the duration of the computation pass.
    assign ctrl_activate_pe_computation = is_computing;

    // Main Control Logic (FSM-like behavior)
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            is_computing <= 1'b0;
            compute_busy <= 1'b0;
            compute_done <= 1'b0;
            ctrl_start_new_systolic_pass <= 1'b0;
            processed_row_count <= 0;
        end else begin
            // Default to a single-cycle pulse for starting a pass
            ctrl_start_new_systolic_pass <= 1'b0;

            if (compute_req && !is_computing) begin
                // A new computation request for a tile pass (one 'k' iteration)
                is_computing <= 1'b1;
                compute_busy <= 1'b1;
                compute_done <= 1'b0;
                // [MODIFIED] Send a single pulse to start the Data_Formatter and Systolic Array
                ctrl_start_new_systolic_pass <= 1'b1;
                processed_row_count <= 0;
            end else if (is_computing) begin
                compute_busy <= 1'b1;

                // [UNCHANGED] Row counting logic is driven by the accumulation pipeline's write enable.
                if (c_accum_we) begin
                    processed_row_count <= processed_row_count + 1;
                end

                // [UNCHANGED] The condition for finishing a pass is when the last row
                // has been written to the accumulator. This logic is robust and remains.
                if (c_accum_we && (processed_row_count == TILE_SIZE - 1)) begin
                    is_computing <= 1'b0;
                    compute_busy <= 1'b0;
                    compute_done <= 1'b1; // Assert completion signal
                end else begin
                    compute_done <= 1'b0;
                end
            end else begin
                // Idle state
                compute_busy <= 1'b0;
                compute_done <= 1'b0; // De-assert done when not busy
                if (!compute_req) begin
                    processed_row_count <= 0;
                end
            end
        end
    end

    // --- High-Performance Accumulation Pipeline ---
    // This logic is purely reactive to the `sa_partial_sum_valid` signal
    // from the systolic array and requires no changes.

    // Stage 0: Issue read command to C-ACCUM SRAM
    assign c_accum_raddr = sa_partial_sum_row_idx;

    // Pipeline Stage 1: Latch inputs
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            pipe_valid[0] <= 1'b0;
        end else begin
            pipe_valid[0] <= handshake_fire;
            if (handshake_fire) begin
                pipe_row_idx[0]     <= sa_partial_sum_row_idx;
                pipe_partial_sum[0] <= sa_partial_sum_in;
                pipe_c_old_data[0]  <= c_accum_rdata;
            end
        end
    end

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

endmodule