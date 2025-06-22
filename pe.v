// pe.v
`timescale 1ns / 1ps

module pe #(
    parameter INPUT_DATA_WIDTH = 8,
    parameter ACCUM_DATA_WIDTH = 32,
    parameter MAC_COUNT_TARGET = 16
)(
    input wire                          clk,
    input wire                          rst_n,
    input wire                          enable,
    input wire                          clear_accumulator,
    input wire                          a_valid_in,
    input wire signed [INPUT_DATA_WIDTH-1:0] a_data_in,
    output wire                         a_valid_out,
    output wire signed [INPUT_DATA_WIDTH-1:0] a_data_out,
    input wire                          b_valid_in,
    input wire signed [INPUT_DATA_WIDTH-1:0] b_data_in,
    output wire                         b_valid_out,
    output wire signed [INPUT_DATA_WIDTH-1:0] b_data_out,
    output wire signed [ACCUM_DATA_WIDTH-1:0] result_out,
    output wire                         result_valid,
    input wire                          conditionally_clear_sum,
    input wire                          start_new_systolic_pass
);
    reg signed [INPUT_DATA_WIDTH-1:0] a_reg; // Holds a_data_in from PREVIOUS cycle
    reg signed [INPUT_DATA_WIDTH-1:0] b_reg; // Holds b_data_in from PREVIOUS cycle
    reg                               a_valid_for_output_reg; // For propagating valid signal
    reg                               b_valid_for_output_reg; // For propagating valid signal
    reg                               inputs_that_produced_a_b_regs_were_valid_reg;

    localparam MULT_RESULT_WIDTH = INPUT_DATA_WIDTH * 2;
    reg signed [MULT_RESULT_WIDTH-1:0] mul_result_reg; // Holds product of a_reg, b_reg (i.e., product of PREVIOUS cycle's inputs)
    reg                                mul_valid_reg;  // Indicates if data in mul_result_reg is valid

    reg signed [ACCUM_DATA_WIDTH-1:0] local_accumulator_reg;
    reg [$clog2(MAC_COUNT_TARGET+1)-1:0] performed_mac_count;
    wire [$clog2(MAC_COUNT_TARGET+1)-1:0] next_performed_mac_count_w;
    reg result_valid_reg;
    reg pe_calculation_done_latch;

    wire signed [MULT_RESULT_WIDTH-1:0] mul_output_data; // Combinational: a_reg * b_reg
    wire signed [ACCUM_DATA_WIDTH-1:0] add_output_data;

    assign mul_output_data = a_reg * b_reg;
    assign add_output_data = mul_result_reg + local_accumulator_reg;
    assign a_valid_out = a_valid_for_output_reg;
    assign b_valid_out = b_valid_for_output_reg;
    assign a_data_out  = a_reg; // a_reg is the latched input, so output is delayed by one cycle
    assign b_data_out  = b_reg; // b_reg is the latched input

    assign next_performed_mac_count_w = (!pe_calculation_done_latch && mul_valid_reg && (performed_mac_count < MAC_COUNT_TARGET)) ?
                                        (performed_mac_count + 1) :
                                        performed_mac_count;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            a_reg                   <= '0;
            b_reg                   <= '0;
            a_valid_for_output_reg  <= 1'b0;
            b_valid_for_output_reg  <= 1'b0;
            inputs_that_produced_a_b_regs_were_valid_reg <= 1'b0;
            local_accumulator_reg   <= '0;
            mul_result_reg          <= '0;
            mul_valid_reg           <= 1'b0;
            performed_mac_count     <= 0;
            result_valid_reg        <= 1'b0;
            pe_calculation_done_latch <= 1'b0;
        end else begin
            result_valid_reg <= 1'b0;

            // 优先处理新的 systolic pass 开始的复位（针对每个 k 迭代）
            if (start_new_systolic_pass) begin
                performed_mac_count     <= 0;      // 为新的 k 迭代复位 MAC 计数
                pe_calculation_done_latch <= 1'b0; // 允许新的计算完成过程
                mul_valid_reg           <= 1'b0;   // 前一个 pass 的乘积无效了
                // local_accumulator_reg 不在这里复位，除非 clear_accumulator 也有效
                if (clear_accumulator) begin // 这个只在 k=0 且 start_new_systolic_pass 同时发生时为真
                    if (conditionally_clear_sum) begin // 这个也应该只在 k=0 时为真
                        local_accumulator_reg   <= '0;
                    end
                end
            end 
            // 处理 k=0 时的累加器完全清零（如果 start_new_systolic_pass 和 clear_accumulator 不是严格同时）
            // 这个分支可能可以被上面的 if (start_new_systolic_pass) begin if (clear_accumulator) ... end end 覆盖
            // 但保留它以明确 k=0 的特殊处理，以防万一。
            else if (clear_accumulator) begin 
            // performed_mac_count 和 pe_calculation_done_latch 应该已经被 start_new_systolic_pass 处理了
            if (conditionally_clear_sum) begin // conditionally_clear_sum 通常与 clear_accumulator 一起用于 k=0
                local_accumulator_reg   <= '0;
            end
            end else if (enable) begin
                a_reg <= a_data_in;
                b_reg <= b_data_in;
                inputs_that_produced_a_b_regs_were_valid_reg <= a_valid_in && b_valid_in;
                a_valid_for_output_reg <= a_valid_in;
                b_valid_for_output_reg <= b_valid_in;
                mul_result_reg <= mul_output_data; // Product of a_reg, b_reg (inputs from previous cycle)
                mul_valid_reg  <= inputs_that_produced_a_b_regs_were_valid_reg; // Validity of those inputs
                if (!pe_calculation_done_latch) begin
                    if (mul_valid_reg) begin // If product from previous cycle (now in mul_result_reg) is valid
                        local_accumulator_reg <= add_output_data; // add_output_data uses current mul_result_reg & local_accumulator_reg
                        performed_mac_count <= next_performed_mac_count_w;
                    end

                    if (mul_valid_reg && (performed_mac_count < MAC_COUNT_TARGET) && (next_performed_mac_count_w == MAC_COUNT_TARGET)) begin
                        result_valid_reg <= 1'b1;
                        pe_calculation_done_latch <= 1'b1;
                    end
                end
            end
        end
    end

    assign result_out = local_accumulator_reg;
    assign result_valid = result_valid_reg;

endmodule
