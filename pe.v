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
            mul_valid_reg           <= 1'b0;
            performed_mac_count     <= 0;
            result_valid_reg        <= 1'b0;
            pe_calculation_done_latch <= 1'b0;
            pe_calculation_done_latch_prev <= 1'b0; // 初始化
        end else begin
            result_valid_reg <= 1'b0; // Pulse behavior for result_valid

            // 优先处理新的 systolic pass 开始的复位（针对每个 k 迭代）
            if (start_new_systolic_pass) begin
                performed_mac_count     <= 0;      // 为新的 k 迭代复位 MAC 计数
                pe_calculation_done_latch <= 1'b0; // 允许新的计算完成过程
                mul_valid_reg           <= 1'b0;   // 前一个 pass 的乘积无效了
                if (clear_accumulator) begin
                    if (conditionally_clear_sum) begin
                        local_accumulator_reg   <= 0;
                    end
                end
            end
            // 处理 k=0 时的累加器完全清零（如果 start_new_systolic_pass 和 clear_accumulator 不是严格同时）
            else if (clear_accumulator) begin
                if (conditionally_clear_sum) begin
                    local_accumulator_reg   <= 0;
                end
            end else if (enable) begin
                // Pipeline stage 1: Input data registers
                a_reg <= a_data_in;
                b_reg <= b_data_in;
                inputs_that_produced_a_b_regs_were_valid_reg <= a_valid_in && b_valid_in;
                a_valid_for_output_reg <= a_valid_in;
                b_valid_for_output_reg <= b_valid_in;

                // Pipeline stage 2: Multiplication
                mul_result_reg <= mul_output_data; // Product of a_reg, b_reg (inputs from previous cycle)
                mul_valid_reg  <= inputs_that_produced_a_b_regs_were_valid_reg; // Validity of those inputs

                // ==================== MODIFIED LOGIC BLOCK START ====================
                // Pipeline stage 3: Accumulation
                if (!pe_calculation_done_latch) begin
                    if (mul_valid_reg) begin // If product from previous cycle (now in mul_result_reg) is valid
                        
                        // Step 1: Accumulate
                        if (conditionally_clear_sum && performed_mac_count == 0) begin // If it's the first MAC of a new pass
                            local_accumulator_reg <= mul_result_reg; // Start with the product
                        end else begin
                            local_accumulator_reg <= add_output_data; // Accumulate
                        end
                        
                        // Step 2: Update count
                        performed_mac_count <= next_performed_mac_count_w;

                        // Step 3: Assert pe_calculation_done_latch when the last MAC is processed
                        // This check is now inside the same block as accumulation, ensuring they are scheduled together.
                        // It triggers when the count is ABOUT to become the target.
                        if (next_performed_mac_count_w == MAC_COUNT_TARGET) begin
                            result_valid_reg <= 1'b1;
                            pe_calculation_done_latch <= 1'b1;
                        end
                    end
                end
                // ===================== MODIFIED LOGIC BLOCK END =====================
            end

            // 更新 pe_calculation_done_latch_prev
            pe_calculation_done_latch_prev <= pe_calculation_done_latch;

            // --- 调试信息 ---
            // if ((ROW_IDX == 0 && COL_IDX == 0) || (ROW_IDX == 1 && COL_IDX == 1) || (ROW_IDX == 15 && COL_IDX == 15)) begin
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