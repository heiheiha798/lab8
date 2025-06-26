`timescale 1ns / 1ps

module pe #(
    parameter INPUT_DATA_WIDTH = 8,
    parameter ACCUM_DATA_WIDTH = 32,
    parameter MAC_COUNT_TARGET = 16,
    parameter ROW_IDX = 0, // 新增参数：PE的行索引
    parameter COL_IDX = 0  // 新增参数：PE的列索引
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
    input wire                          start_new_systolic_pass,

    // --- New ports for done signal propagation ---
    input wire                          pe_row_propagate_done_in, // From PE to the left, or 1'b1 for first PE in row
    output wire                         pe_row_propagate_done_out // To PE to the right
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
    reg pe_calculation_done_latch; // This is a level signal, asserted when PE finishes for current K-iter

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

    // --- Logic for pe_row_propagate_done_out ---
    // This signal indicates that this PE AND all PEs to its left in the row are done.
    // pe_calculation_done_latch stays high until the next start_new_systolic_pass.
    assign pe_row_propagate_done_out = pe_row_propagate_done_in && pe_calculation_done_latch;

    // 添加一个寄存器用于跟踪 pe_calculation_done_latch 的前一个值，以便检测变化
    reg pe_calculation_done_latch_prev;
    reg enable_prev;

    // 启用 enable_prev 逻辑来检测 enable 信号的变化
    always @(posedge clk) begin // 独立的 always 块
        enable_prev <= enable;
    end

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        a_reg                   <= 0;
        b_reg                   <= 0;
        a_valid_for_output_reg  <= 1'b0;
        b_valid_for_output_reg  <= 1'b0;
        inputs_that_produced_a_b_regs_were_valid_reg <= 1'b0;
        local_accumulator_reg   <= 0;
        mul_result_reg          <= 0;
        mul_valid_reg           <= 1'b0; // 在rst_n时清零是正确的
        performed_mac_count     <= 0;
        result_valid_reg        <= 1'b0;
        pe_calculation_done_latch <= 1'b0;
        pe_calculation_done_latch_prev <= 1'b0;
    end else begin
        result_valid_reg <= 1'b0; // 脉冲行为

        // 1. 处理 start_new_systolic_pass (主要用于复位状态和累加器)
        if (start_new_systolic_pass) begin
            performed_mac_count     <= 0;
            pe_calculation_done_latch <= 1'b0;
            if (conditionally_clear_sum) begin
                local_accumulator_reg   <= 0;
            end
            inputs_that_produced_a_b_regs_were_valid_reg <= 1'b0;
            mul_valid_reg <= 1'b0;

            // if (COL_IDX == 0) begin // Or your specific PE for detailed logging
            //     $strobe("[%0t] [PE(%0d,%0d)] InNewPassBlock: local_accum_TARGET=0, performed_mac_count_TARGET=0, inputs_that_prod_TARGET=0, mul_valid_TARGET=0. Current a_reg=%d, b_reg=%d, mul_result_reg_CURRENT=%d, mul_valid_reg_CURRENT=%b",
            //             $time, ROW_IDX, COL_IDX, a_reg, b_reg, mul_result_reg, mul_valid_reg);
            // end
        end
        // 2. 处理PE的使能和流水线操作 (仅当 enable 为高)
        else if (enable) begin // *** CHANGED TO ELSE IF ***
            // 流水线阶段 1: 锁存输入数据和有效性
            a_reg <= a_data_in;
            b_reg <= b_data_in;
            // `inputs_that_produced_a_b_regs_were_valid_reg` 记录了当前 a_reg/b_reg 是否由有效输入产生
            inputs_that_produced_a_b_regs_were_valid_reg <= a_valid_in && b_valid_in;
            a_valid_for_output_reg <= a_valid_in; // Propagate valid
            b_valid_for_output_reg <= b_valid_in; // Propagate valid

            // 流水线阶段 2: 乘法
            // `mul_result_reg` 存储 a_reg * b_reg 的结果 (即上上周期输入的乘积)
            // `mul_valid_reg` 表明 `mul_result_reg` 中的数据是否有效
            mul_result_reg <= mul_output_data; // mul_output_data = a_reg * b_reg (组合逻辑)
            // mul_valid_reg 现在正确地基于 *上一个周期* 的 inputs_that_produced_a_b_regs_were_valid_reg
            // 如果上一个周期是 start_new_systolic_pass，则此处的 mul_valid_reg 会是 0，从而阻止累加
            mul_valid_reg  <= inputs_that_produced_a_b_regs_were_valid_reg;

            // 流水线阶段 3: 累加
            if (!pe_calculation_done_latch) begin
                // if (COL_IDX == 0) begin
                //     $strobe("[%0t] [PE(%0d,%0d)] ACCUM_CHECK: mul_valid_CURRENT=%b, performed_mac_count_CURRENT=%d, mul_result_reg_TO_USE=%d, local_accum_BEFORE_UPDATE=%d",
                //             $time, ROW_IDX, COL_IDX, mul_valid_reg, performed_mac_count, mul_result_reg, local_accumulator_reg);
                // end
                if (mul_valid_reg) begin // 仅当来自流水线上一级的乘积有效时
                    // 当 performed_mac_count 为0时，是本轮K迭代的第一次有效乘积累加
                    // 此时，如果累加器已被 start_new_systolic_pass 清零，则直接加载；否则累加。
                    if (performed_mac_count == 0) begin // (并且 conditionally_clear_sum 已经在 start_pass 时处理了清零)
                        local_accumulator_reg <= mul_result_reg;
                    end else begin
                        local_accumulator_reg <= add_output_data; // add_output_data = mul_result_reg + local_accumulator_reg_prev
                    end
                    
                    // 更新已执行的MAC计数
                    performed_mac_count <= next_performed_mac_count_w;

                    // 检查是否完成了所有的MAC操作
                    if (next_performed_mac_count_w == MAC_COUNT_TARGET) begin
                        result_valid_reg <= 1'b1; // 输出结果有效信号（脉冲）
                        pe_calculation_done_latch <= 1'b1; // 标记PE完成当前K轮次计算
                    end
                end
            end
        end else begin // if (!enable AND not start_new_systolic_pass)
            // 当PE不使能时，理想情况下不应该有新的有效乘积产生
            // 为了确保安全，可以在不使能时将mul_valid_reg清零
            mul_valid_reg <= 1'b0;
            // inputs_that_produced_a_b_regs_were_valid_reg will naturally become 0 if a_valid_in/b_valid_in are 0
        end

        // 更新 pe_calculation_done_latch_prev 用于调试日志
        pe_calculation_done_latch_prev <= pe_calculation_done_latch;

        // --- 调试信息 ---
        // if ((ROW_IDX == 0 && COL_IDX == 0) || (ROW_IDX == 1 && COL_IDX == 1) || (ROW_IDX == 15 && COL_IDX == 15)) begin
        // // if (COL_IDX == 0) begin
        //     if (start_new_systolic_pass) begin // Display on pass start
        //         $strobe("[%0t] [PE(%0d,%0d)] NewPass: MAC_count_reset_to_0, pe_done_latch_reset_to_0, mul_valid_reset_to_0",
        //                 $time, ROW_IDX, COL_IDX);
        //     end

        //     if (enable) begin // Only display when PE is supposed to be active
        //         if (mul_valid_reg) begin // Display when a multiplication is considered valid for accumulation
        //             $strobe("[%0t] [PE(%0d,%0d)] MAC: count_prev=%0d, count_next=%0d, mul_val=%b, a_in=%d, b_in=%d, a_reg=%d, b_reg=%d, mul_res=%d, cur_sum=%d, next_sum_val_if_acc=%d, pe_done_latch=%b",
        //                     $time, ROW_IDX, COL_IDX, performed_mac_count, next_performed_mac_count_w, mul_valid_reg,
        //                     a_data_in, b_data_in, a_reg, b_reg, mul_result_reg, local_accumulator_reg, add_output_data, pe_calculation_done_latch);
        //         end

        //         // Display when the done latch condition is met OR when it changes
        //         if ((performed_mac_count == (MAC_COUNT_TARGET-1) && mul_valid_reg) && !pe_calculation_done_latch) begin
        //                $strobe("[%0t] [PE(%0d,%0d)] DoneLatch_AboutToSet: count=%0d (target-1=%0d), mul_valid=%b. Latch will be 1 next.",
        //                        $time, ROW_IDX, COL_IDX, performed_mac_count, MAC_COUNT_TARGET-1, mul_valid_reg);
        //         end
        //         // 监测 done latch 的变化
        //         if (pe_calculation_done_latch != pe_calculation_done_latch_prev) begin
        //             $strobe("[%0t] [PE(%0d,%0d)] DoneLatch_Change: %b -> %b, MAC_count_at_change_moment=%d, mul_valid_reg=%b",
        //                     $time, ROW_IDX, COL_IDX, pe_calculation_done_latch_prev, pe_calculation_done_latch, performed_mac_count, mul_valid_reg);
        //         end
        //     end

        //     // Display for when enable goes low
        //     if (enable_prev && !enable) begin
        //         $strobe("[%0t] [PE(%0d,%0d)] PE_DISABLE: MAC_count=%0d, pe_done_latch=%b", $time, ROW_IDX, COL_IDX, performed_mac_count, pe_calculation_done_latch);
        //     end
        // end
    end
end
    
    assign result_out = local_accumulator_reg;
    assign result_valid = result_valid_reg;

endmodule