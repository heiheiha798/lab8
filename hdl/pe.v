`timescale 1ns / 1ps

module pe #(
    parameter INPUT_DATA_WIDTH = 8,
    parameter ACCUM_DATA_WIDTH = 32,
    parameter MAC_COUNT_TARGET = 16,
    parameter ROW_IDX = 0, 
    parameter COL_IDX = 0  
)(
    input wire                           clk,
    input wire                           rst_n,
    input wire                           enable,
    input wire                           a_valid_in,
    input wire signed [INPUT_DATA_WIDTH-1:0] a_data_in,
    output wire                          a_valid_out,
    output wire signed [INPUT_DATA_WIDTH-1:0] a_data_out,
    input wire                           b_valid_in,
    input wire signed [INPUT_DATA_WIDTH-1:0] b_data_in,
    output wire                          b_valid_out,
    output wire signed [INPUT_DATA_WIDTH-1:0] b_data_out,
    output wire signed [ACCUM_DATA_WIDTH-1:0] result_out,
    output wire                          result_valid,
    input wire                           clear_for_new_tile, // For a new C(i,j) tile
    input wire                           start_new_systolic_pass, // For a new k-slice

    // --- New ports for done signal propagation ---
    input wire                           pe_row_propagate_done_in, 
    output wire                          pe_row_propagate_done_out 
);
    reg signed [INPUT_DATA_WIDTH-1:0] a_reg; 
    reg signed [INPUT_DATA_WIDTH-1:0] b_reg; 
    reg                               a_valid_for_output_reg; 
    reg                               b_valid_for_output_reg; 
    reg                               inputs_that_produced_a_b_regs_were_valid_reg;

    localparam MULT_RESULT_WIDTH = INPUT_DATA_WIDTH * 2;
    reg signed [MULT_RESULT_WIDTH-1:0] mul_result_reg; 
    reg                                mul_valid_reg;  

    reg signed [ACCUM_DATA_WIDTH-1:0] local_accumulator_reg;
    reg [$clog2(MAC_COUNT_TARGET+1)-1:0] performed_mac_count;
    wire [$clog2(MAC_COUNT_TARGET+1)-1:0] next_performed_mac_count_w;
    reg result_valid_reg;
    reg pe_calculation_done_latch; 

    wire signed [MULT_RESULT_WIDTH-1:0] mul_output_data; 
    wire signed [ACCUM_DATA_WIDTH-1:0] add_output_data;

    assign mul_output_data = a_reg * b_reg;
    assign add_output_data = mul_result_reg + local_accumulator_reg;
    assign a_valid_out = a_valid_for_output_reg;
    assign b_valid_out = b_valid_for_output_reg;
    assign a_data_out  = a_reg; 
    assign b_data_out  = b_reg; 

    assign next_performed_mac_count_w = (!pe_calculation_done_latch && mul_valid_reg && (performed_mac_count < MAC_COUNT_TARGET)) ?
                                        (performed_mac_count + 1) :
                                        performed_mac_count;

    assign pe_row_propagate_done_out = pe_row_propagate_done_in && pe_calculation_done_latch;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            a_reg                                       <= 0;
            b_reg                                       <= 0;
            a_valid_for_output_reg                      <= 1'b0;
            b_valid_for_output_reg                      <= 1'b0;
            inputs_that_produced_a_b_regs_were_valid_reg<= 1'b0;
            local_accumulator_reg                       <= 0;
            mul_result_reg                              <= 0;
            mul_valid_reg                               <= 1'b0;
            performed_mac_count                         <= 0;
            result_valid_reg                            <= 1'b0;
            pe_calculation_done_latch                   <= 1'b0;
        end else begin
            // --- MODIFIED LOGIC ---
            // Block 1: Accumulator update logic.
            // Priority 1: A new tile computation is starting, accumulator must be cleared.
            if (clear_for_new_tile) begin
                local_accumulator_reg <= 0;
            // Priority 2: If not clearing, ALWAYS add the valid multiplication result to the accumulator.
            // This ensures results from all k-iterations are summed up correctly.
            end else if (enable && mul_valid_reg && !pe_calculation_done_latch) begin
                local_accumulator_reg <= add_output_data;
            end
            // If neither condition is met, local_accumulator_reg holds its value.

            // --- Block 2: General Pipeline and Control Logic ---
            result_valid_reg <= 1'b0; // Pulse behavior

            // 1. Handle start_new_systolic_pass (resets state for the k-iteration)
            if (start_new_systolic_pass) begin
                performed_mac_count                         <= 0;
                pe_calculation_done_latch                   <= 1'b0;
                inputs_that_produced_a_b_regs_were_valid_reg<= 1'b0;
                mul_valid_reg                               <= 1'b0;
            // 2. Handle PE's enable and pipeline operation (only when enable is high)
            end else if (enable) begin
                // Pipeline Stage 1: Latch inputs
                a_reg <= a_data_in;
                b_reg <= b_data_in;
                inputs_that_produced_a_b_regs_were_valid_reg <= a_valid_in && b_valid_in;
                a_valid_for_output_reg <= a_valid_in;
                b_valid_for_output_reg <= b_valid_in;

                // Pipeline Stage 2: Multiply
                mul_result_reg <= mul_output_data;
                mul_valid_reg  <= inputs_that_produced_a_b_regs_were_valid_reg;

                // Pipeline Stage 3: Update counters and done latch (Accumulator logic is separate)
                if (!pe_calculation_done_latch) begin
                    if (mul_valid_reg) begin
                        performed_mac_count <= next_performed_mac_count_w;
                        if (next_performed_mac_count_w == MAC_COUNT_TARGET) begin
                            result_valid_reg <= 1'b1;
                            pe_calculation_done_latch <= 1'b1;
                        end
                    end
                end

                // Display for PE(0,0) - Only display when a valid multiplication occurs
                // if (ROW_IDX == 0 && COL_IDX == 0 && mul_valid_reg) begin
                //     $display("%0t [PE(0,0)] Input A:0x%h, Input B:0x%h, Latched A:0x%h, Latched B:0x%h, Acc:0x%h",
                //              $time, a_data_in, b_data_in, a_reg, b_reg, local_accumulator_reg);
                // end

                // Display for PE(15,15) - Only display when a valid multiplication occurs
                // if (ROW_IDX == 15 && COL_IDX == 15 && mul_valid_reg) begin
                //     $display("%0t [PE(15,15)] Input A:0x%h, Input B:0x%h, Latched A:0x%h, Latched B:0x%h, Acc:0x%h",
                //              $time, a_data_in, b_data_in, a_reg, b_reg, local_accumulator_reg);
                // end

            end else begin // if (!enable AND not start_new_systolic_pass)
                mul_valid_reg <= 1'b0;
            end
        end
    end
    
    assign result_out = local_accumulator_reg;
    assign result_valid = result_valid_reg;

endmodule
