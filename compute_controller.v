//
// Filename: compute_controller_robust.v
// Description: A robust compute controller implementing a full valid/ready handshake
//              and a realistic, pipelined accumulation FSM. This design accounts
//              for memory/adder latencies and non-ideal systolic array outputs.
//
`timescale 1ns / 1ps

module compute_controller #(
    parameter TILE_SIZE                 = 16,
    parameter INPUT_DATA_WIDTH          = 8,
    parameter PE_ACCUM_DATA_WIDTH       = 32,
    parameter MAIN_MEM_DATA_WIDTH_BITS  = TILE_SIZE * PE_ACCUM_DATA_WIDTH,
    parameter MATRIX_SIZE               = 512,
    // 假设外部加法器完成一次加法需要1个周期
    parameter FINAL_ADDER_LATENCY       = 1
)(
    // 控制接口
    input wire                                          clk,
    input wire                                          rst_n,
    input wire                                          compute_req,
    input wire [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      k_tile_idx,
    output reg                                          compute_busy,
    output reg                                          compute_done,

    // ---- 脉动阵列 (SA) 接口 ----
    // 握手信号
    output wire                                         dut_ready_for_sa_partial_sum,
    input wire                                          sa_partial_sum_valid,
    // 部分和 (A_tile * B_tile) 输入
    input wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]    sa_partial_sum_in,
    input wire [$clog2(TILE_SIZE)-1:0]                  sa_partial_sum_row_idx,
    // 最终和 (A_tile * B_tile + C_old) 输入
    input wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]    sa_final_sum_in,
    // SA 状态
    input wire                                          sa_tile_all_pes_done_one_pass,
    // SA 控制
    output reg                                          ctrl_clear_all_pe_accumulators,
    output reg                                          ctrl_start_new_systolic_pass,
    output wire                                         ctrl_activate_pe_computation,

    // ---- SA 最终加法器控制端口 ----
    output reg signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]    ctrl_c_data_to_sa,
    output reg                                          ctrl_enable_final_add,

    // ---- A/B SRAM 读取接口 (给SA喂数据) ----
    output wire [$clog2(TILE_SIZE)-1:0]                 sram_a_addr,
    input wire  [TILE_SIZE*INPUT_DATA_WIDTH-1:0]        sram_a_rdata_flat,
    output wire [$clog2(TILE_SIZE)-1:0]                 sram_b_addr,
    input wire  [TILE_SIZE*INPUT_DATA_WIDTH-1:0]        sram_b_rdata_flat,
    output wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0]        sa_array_a_in_flat,
    output wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0]        sa_array_b_in_flat,
    output wire                                         ctrl_array_data_valid_in,

    // ---- C-SRAM 读写接口 ----
    output reg [$clog2(TILE_SIZE)-1:0]                  sram_c_addr,
    output reg [MAIN_MEM_DATA_WIDTH_BITS-1:0]           sram_c_wdata,
    output reg                                          sram_c_we,
    input wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]           sram_c_rdata
);

    //======================================================================
    //== 内部参数和信号声明
    //======================================================================

    // -- 主FSM --
    localparam MAIN_FSM_WIDTH = 2;
    localparam S_IDLE         = {MAIN_FSM_WIDTH{1'b0}},
               S_START_SA     = S_IDLE + 1,
               S_COMPUTING    = S_START_SA + 1,
               S_FINISH       = S_COMPUTING + 1;
    reg [MAIN_FSM_WIDTH-1:0] main_fsm_state, main_fsm_next_state;
    reg [TILE_SIZE-1:0]      row_done_flags;

    // -- 累加微流水线 FSM --
    localparam ACCUM_FSM_WIDTH = 3;
    localparam ACCUM_IDLE              = {ACCUM_FSM_WIDTH{1'b0}},
               ACCUM_LATCH_PARTIAL     = ACCUM_IDLE + 1,
               // k > 0 分支
               ACCUM_READ_C_CMD        = ACCUM_LATCH_PARTIAL + 1,
               ACCUM_WAIT_C_AND_ADD    = ACCUM_READ_C_CMD + 1,
               ACCUM_WAIT_FINAL_SUM    = ACCUM_WAIT_C_AND_ADD + 1,
               ACCUM_WRITE_FINAL_CMD   = ACCUM_WAIT_FINAL_SUM + 1,
               // k = 0 分支
               ACCUM_WRITE_PARTIAL_CMD = ACCUM_WRITE_FINAL_CMD + 1;
    reg [ACCUM_FSM_WIDTH-1:0] accum_fsm_state, accum_fsm_next_state;

    // -- 数据喂入逻辑 --
    reg [$clog2(TILE_SIZE)-1:0] sa_feed_counter;
    
    // -- 数据寄存器 --
    reg [$clog2(TILE_SIZE)-1:0]                 processing_row_idx_reg;
    reg signed [MAIN_MEM_DATA_WIDTH_BITS-1:0]   partial_sum_reg;

    // -- 握手信号 --
    wire handshake_fire;


    //======================================================================
    //== 核心逻辑实现
    //======================================================================

    // --- 握手与就绪信号 ---
    // 当累加FSM空闲时，我们才能接收下一个结果
    assign dut_ready_for_sa_partial_sum = (accum_fsm_state == ACCUM_IDLE);
    // 握手成功信号
    assign handshake_fire = sa_partial_sum_valid && dut_ready_for_sa_partial_sum;


    // --- 主 FSM ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            main_fsm_state <= S_IDLE;
        end else begin
            main_fsm_state <= main_fsm_next_state;
        end
    end

    always @(*) begin
        main_fsm_next_state = main_fsm_state;
        compute_busy = 1'b0;
        compute_done = 1'b0;
        ctrl_start_new_systolic_pass = 1'b0;
        ctrl_clear_all_pe_accumulators = 1'b0;

        case(main_fsm_state)
            S_IDLE: begin
                if (compute_req) begin
                    main_fsm_next_state = S_START_SA;
                end
            end
            S_START_SA: begin
                compute_busy = 1'b1;
                ctrl_start_new_systolic_pass = 1'b1;
                // 仅在整个矩阵乘法的第一个k-tile时才清除PE累加器
                if (k_tile_idx == 0) begin
                    ctrl_clear_all_pe_accumulators = 1'b1;
                end
                main_fsm_next_state = S_COMPUTING;
            end
            S_COMPUTING: begin
                compute_busy = 1'b1;
                // 当所有行的结果都已处理完毕，并且SA本身也完成了它的计算 pass，才算结束
                if (row_done_flags == {TILE_SIZE{1'b1}} && sa_tile_all_pes_done_one_pass) begin
                    main_fsm_next_state = S_FINISH;
                end
            end
            S_FINISH: begin
                compute_done = 1'b1;
                main_fsm_next_state = S_IDLE;
            end
            default: begin
                main_fsm_next_state = S_IDLE;
            end
        endcase
    end


    // --- 数据喂入SA的逻辑 ---
    assign ctrl_activate_pe_computation = (main_fsm_state == S_COMPUTING);
    assign ctrl_array_data_valid_in = (main_fsm_state == S_COMPUTING && sa_feed_counter < TILE_SIZE);
    
    // SRAM地址生成与数据通路连接
    assign sram_a_addr = sa_feed_counter;
    assign sram_b_addr = sa_feed_counter;
    assign sa_array_a_in_flat = sram_a_rdata_flat;
    assign sa_array_b_in_flat = sram_b_rdata_flat;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            sa_feed_counter <= 0;
        end else if (ctrl_start_new_systolic_pass) begin
            sa_feed_counter <= 0;
        end else if (ctrl_array_data_valid_in) begin
            sa_feed_counter <= sa_feed_counter + 1;
        end
    end


    // --- 累加微流水线 FSM ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            accum_fsm_state <= ACCUM_IDLE;
        end else begin
            accum_fsm_state <= accum_fsm_next_state;
        end
    end

    // 累加FSM的组合逻辑（状态输出）
    always @(*) begin
        accum_fsm_next_state = accum_fsm_state;
        sram_c_we = 1'b0;
        sram_c_addr = 0;
        sram_c_wdata = 0;
        ctrl_enable_final_add = 1'b0;
        ctrl_c_data_to_sa = 0;

        case(accum_fsm_state)
            ACCUM_IDLE: begin
                if (handshake_fire) begin
                    accum_fsm_next_state = ACCUM_LATCH_PARTIAL;
                end
            end
            ACCUM_LATCH_PARTIAL: begin
                // 根据k值决定走累加路径还是直接写路径
                if (k_tile_idx > 0) begin
                    accum_fsm_next_state = ACCUM_READ_C_CMD;
                end else begin
                    accum_fsm_next_state = ACCUM_WRITE_PARTIAL_CMD;
                end
            end
            // --- k > 0 的累加路径 ---
            ACCUM_READ_C_CMD: begin
                // 向C-SRAM发出读指令
                sram_c_addr = processing_row_idx_reg;
                accum_fsm_next_state = ACCUM_WAIT_C_AND_ADD;
            end
            ACCUM_WAIT_C_AND_ADD: begin
                // C-SRAM数据已准备好，送给加法器并使其能
                ctrl_c_data_to_sa = sram_c_rdata;
                ctrl_enable_final_add = 1'b1;
                // 假设加法器有N周期延迟
                if (FINAL_ADDER_LATENCY == 0) begin
                    accum_fsm_next_state = ACCUM_WRITE_FINAL_CMD;
                end else begin
                    // 这里我们简单等待1周期，可扩展为多周期
                    accum_fsm_next_state = ACCUM_WAIT_FINAL_SUM;
                end
            end
            ACCUM_WAIT_FINAL_SUM: begin
                 // 等待加法器输出最终和
                accum_fsm_next_state = ACCUM_WRITE_FINAL_CMD;
            end
            ACCUM_WRITE_FINAL_CMD: begin
                // 将最终和写入C-SRAM
                sram_c_we = 1'b1;
                sram_c_addr = processing_row_idx_reg;
                sram_c_wdata = sa_final_sum_in;
                accum_fsm_next_state = ACCUM_IDLE;
            end
            // --- k = 0 的直接写路径 ---
            ACCUM_WRITE_PARTIAL_CMD: begin
                // 直接将部分和写入C-SRAM
                sram_c_we = 1'b1;
                sram_c_addr = processing_row_idx_reg;
                sram_c_wdata = partial_sum_reg;
                accum_fsm_next_state = ACCUM_IDLE;
            end
            default: begin
                accum_fsm_next_state = ACCUM_IDLE;
            end
        endcase
    end

    // --- 数据锁存与状态标志更新的序贯逻辑 ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            row_done_flags <= 0;
            processing_row_idx_reg <= 0;
            partial_sum_reg <= 0;
        end else begin
            // 在新一轮计算开始时，清除所有完成标志
            if (ctrl_start_new_systolic_pass) begin
                row_done_flags <= 0;
            end

            // 当握手成功时，锁存来自SA的数据
            if (handshake_fire) begin
                processing_row_idx_reg <= sa_partial_sum_row_idx;
                partial_sum_reg        <= sa_partial_sum_in;
            end

            // 当累加FSM完成一轮循环并即将返回IDLE时，设置对应行的完成标志
            if (accum_fsm_state != ACCUM_IDLE && accum_fsm_next_state == ACCUM_IDLE) begin
                row_done_flags[processing_row_idx_reg] <= 1'b1;
            end
        end
    end

endmodule