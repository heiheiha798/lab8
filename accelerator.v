//
// Filename: accelerator.v
// Description: Redesigned, robust top-level accelerator module.
//              Implements a true pipeline manager using status flags to
//              decouple Load, Compute, and Write operations, preventing deadlocks.
//
`timescale 1ns / 1ps

module accelerator #(
    parameter MATRIX_SIZE               = 48,
    parameter TILE_SIZE                 = 16,
    parameter INPUT_DATA_WIDTH          = 8,
    parameter PE_ACCUM_DATA_WIDTH       = 32,
    parameter MAIN_MEM_ADDR_WIDTH       = 32,
    parameter MAIN_MEM_DATA_WIDTH_BITS  = 64,
    parameter BASE_ADDR_A               = 32'h10000000,
    parameter BASE_ADDR_B               = 32'h20000000,
    parameter BASE_ADDR_C               = 32'h30000000
)(
    input wire                                          clk,
    input wire                                          rst_n,
    input wire                                          start,
    output wire                                         busy,
    output wire                                         done,

    // 主存读取接口 (for Loader)
    output wire                                         imem_req_valid,
    input wire                                          imem_req_ready,
    input wire                                          imem_resp_valid,
    input wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]           imem_resp_rdata,
    output wire [MAIN_MEM_ADDR_WIDTH-1:0]               imem_req_addr,

    // 主存写入接口 (for Writer)
    output wire                                         omem_req_valid,
    output wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]          omem_req_wdata,
    output wire [MAIN_MEM_ADDR_WIDTH-1:0]               omem_req_addr,
    input wire                                          omem_req_ready
);

    //======================================================================
    //== Local Parameters and State Definitions
    //======================================================================
    localparam NUM_TILES_PER_DIM = MATRIX_SIZE / TILE_SIZE;
    
    // FSM 状态定义
    localparam FSM_STATE_WIDTH   = 3;
    localparam S_IDLE            = {FSM_STATE_WIDTH{1'b0}};
    localparam S_RUN_PIPELINE    = S_IDLE + 1;
    localparam S_DRAIN_PIPELINE  = S_RUN_PIPELINE + 1;
    localparam S_KICKOFF_WRITE   = S_DRAIN_PIPELINE + 1;
    localparam S_WAIT_FINAL_WRITE= S_KICKOFF_WRITE + 1;
    localparam S_DONE            = S_WAIT_FINAL_WRITE + 1;

    //======================================================================
    //== Internal Wires and Registers
    //======================================================================

    localparam TILE_IDX_WIDTH = ($clog2(NUM_TILES_PER_DIM) > 0) ? $clog2(NUM_TILES_PER_DIM) : 1;

    // --- FSM and Loop Control ---
    reg [FSM_STATE_WIDTH-1:0] current_state, next_state;
    reg [TILE_IDX_WIDTH-1:0] i, j;
    reg [TILE_IDX_WIDTH-1:0] load_k_ptr;
    reg [TILE_IDX_WIDTH-1:0] compute_k_ptr;

    // --- Ping-Pong Buffer Control & Status Flags ---
    // A/B SRAMs (for Loader and Compute Controller)
    reg  load_to_pong;      // Loader 写入的目标: 0=ping, 1=pong
    reg  compute_from_pong; // Compute 读取的来源: 0=ping, 1=pong
    reg  buffer_is_valid[1:0];   // 标志位: 0=ping, 1=pong. 1表示数据已加载好，可供计算
    reg  buffer_is_loading[1:0]; // 标志位: 1表示此缓冲区正在被加载
    wire load_target_is_pong = load_to_pong;
    wire compute_source_is_pong = compute_from_pong;

    // C SRAM (for Compute Controller and Writer)
    reg  accum_to_pong;     // Compute 累加的目标: 0=ping, 1=pong
    reg  write_from_pong;   // Writer 读取的来源: 0=ping, 1=pong
    
    // --- Sub-module Control and Status ---
    reg  loader_req;
    wire loader_busy, loader_done;
    reg  compute_req;
    wire compute_busy, compute_done;
    reg  writer_req;
    wire writer_busy, writer_done;
    wire clear_pe_accum_for_k0; // 用于在 k=0 时清空PE累加器

    // --- Datapath Wires ---
    // A/B SRAMs
    wire [TILE_SIZE*$clog2(TILE_SIZE)-1:0] sram_a_addr_from_formatter, sram_b_addr_from_formatter;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_a_rdata, sram_b_rdata;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_a_ping_rdata, sram_a_pong_rdata;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_b_ping_rdata, sram_b_pong_rdata;
    wire [$clog2(TILE_SIZE*TILE_SIZE*8/MAIN_MEM_DATA_WIDTH_BITS)-1:0] sram_a_waddr, sram_b_waddr;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0] sram_a_wdata, sram_b_wdata;
    wire sram_a_we, sram_b_we;
    
    // Data Formatter -> Systolic Array
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] skewed_a_to_sa, skewed_b_to_sa;
    wire formatter_valid_out_to_sa;
    
    // Systolic Array -> Compute Controller
    wire signed [TILE_SIZE*PE_ACCUM_DATA_WIDTH-1:0] sa_partial_sum_out;
    wire sa_partial_sum_valid;
    wire [$clog2(TILE_SIZE)-1:0] sa_partial_sum_row_idx;
    wire tile_all_pes_done_one_pass;

    // Compute Controller <-> C-SRAM
    wire [$clog2(TILE_SIZE)-1:0]                 c_accum_waddr, c_accum_raddr;
    wire [TILE_SIZE*PE_ACCUM_DATA_WIDTH-1:0]    c_accum_wdata, c_accum_rdata_from_A;
    wire [TILE_SIZE*PE_ACCUM_DATA_WIDTH-1:0]    c_accum_ping_rdata_A, c_accum_pong_rdata_A;
    wire                                         c_accum_we;
    wire [TILE_SIZE*PE_ACCUM_DATA_WIDTH-1:0]    sa_final_sum_in;
    
    // C-SRAM -> Writer (CORRECTED INTERFACE)
    wire [$clog2(TILE_SIZE*TILE_SIZE*PE_ACCUM_DATA_WIDTH/MAIN_MEM_DATA_WIDTH_BITS)-1:0] sram_c_raddr_from_writer;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]                                sram_c_rdata_to_writer;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]                                sram_c_ping_rdata_B, sram_c_pong_rdata_B;

    // Misc Control
    wire ctrl_start_new_systolic_pass;
    wire ctrl_activate_pe_computation;

    //======================================================================
    //== On-Chip SRAM Instantiations and Muxing
    //======================================================================
    // --- A/B SRAM Banks for Input Tiles ---
    assign sram_a_rdata = compute_source_is_pong ? sram_a_pong_rdata : sram_a_ping_rdata;
    assign sram_b_rdata = compute_source_is_pong ? sram_b_pong_rdata : sram_b_ping_rdata;

    sram_banked sram_a_ping (.clk(clk), .we(sram_a_we & ~load_target_is_pong), .waddr(sram_a_waddr), .wdata(sram_a_wdata), .raddr(sram_a_addr_from_formatter), .rdata(sram_a_ping_rdata));
    sram_banked sram_a_pong (.clk(clk), .we(sram_a_we &  load_target_is_pong), .waddr(sram_a_waddr), .wdata(sram_a_wdata), .raddr(sram_a_addr_from_formatter), .rdata(sram_a_pong_rdata));
    sram_banked sram_b_ping (.clk(clk), .we(sram_b_we & ~load_target_is_pong), .waddr(sram_b_waddr), .wdata(sram_b_wdata), .raddr(sram_b_addr_from_formatter), .rdata(sram_b_ping_rdata));
    sram_banked sram_b_pong (.clk(clk), .we(sram_b_we &  load_target_is_pong), .waddr(sram_b_waddr), .wdata(sram_b_wdata), .raddr(sram_b_addr_from_formatter), .rdata(sram_b_pong_rdata));

    // --- C-Accumulator SRAM Banks for Output Tiles ---
    // Port A for Compute Controller (wide read/write)
    assign c_accum_rdata_from_A = accum_to_pong ? c_accum_pong_rdata_A : c_accum_ping_rdata_A;
    // Port B for Writer (narrow read)
    assign sram_c_rdata_to_writer = write_from_pong ? sram_c_pong_rdata_B : sram_c_ping_rdata_B;
    
    sram_c_accum sram_c_ping (.clk(clk), .we(c_accum_we & ~accum_to_pong), .waddr(c_accum_waddr), .wdata(c_accum_wdata), .raddr_A(c_accum_raddr), .rdata_A(c_accum_ping_rdata_A), .raddr_B(sram_c_raddr_from_writer), .rdata_B(sram_c_ping_rdata_B));
    sram_c_accum sram_c_pong (.clk(clk), .we(c_accum_we &  accum_to_pong), .waddr(c_accum_waddr), .wdata(c_accum_wdata), .raddr_A(c_accum_raddr), .rdata_A(c_accum_pong_rdata_A), .raddr_B(sram_c_raddr_from_writer), .rdata_B(sram_c_pong_rdata_B));
    
    //======================================================================
    //== Sub-Module Instantiations
    //======================================================================
    loader #(.MATRIX_SIZE(MATRIX_SIZE), .TILE_SIZE(TILE_SIZE), .MAIN_MEM_ADDR_WIDTH(MAIN_MEM_ADDR_WIDTH), .MAIN_MEM_DATA_WIDTH_BITS(MAIN_MEM_DATA_WIDTH_BITS), .BASE_ADDR_A(BASE_ADDR_A), .BASE_ADDR_B(BASE_ADDR_B)) 
    i_loader (.clk(clk), .rst_n(rst_n), .load_req(loader_req), .i_tile_idx(i), .j_tile_idx(j), .k_tile_idx(load_k_ptr), .load_to_ping(~load_target_is_pong), .load_busy(loader_busy), .load_done(loader_done), .mem_req_valid(imem_req_valid), .mem_req_ready(imem_req_ready), .mem_resp_valid(imem_resp_valid), .mem_resp_rdata(imem_resp_rdata), .mem_req_addr(imem_req_addr), .sram_a_addr(sram_a_waddr), .sram_a_wdata(sram_a_wdata), .sram_a_we(sram_a_we), .sram_b_addr(sram_b_waddr), .sram_b_wdata(sram_b_wdata), .sram_b_we(sram_b_we));
    
    data_formatter #(.TILE_SIZE(TILE_SIZE), .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH)) 
    i_formatter (.clk(clk), .rst_n(rst_n), .start_pass(ctrl_start_new_systolic_pass), .pass_done(), .sram_a_addr(sram_a_addr_from_formatter), .sram_a_rdata(sram_a_rdata), .sram_b_addr(sram_b_addr_from_formatter), .sram_b_rdata(sram_b_rdata), .skewed_a_out(skewed_a_to_sa), .skewed_b_out(skewed_b_to_sa), .data_valid_out(formatter_valid_out_to_sa));
    
    systolic_array #(.SIZE(TILE_SIZE), .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH), .PE_ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH)) 
    i_sa (.clk(clk), .rst_n(rst_n), .clear_all_pe_accumulators(clear_pe_accum_for_k0), .conditionally_clear_pe_sums_level(clear_pe_accum_for_k0), .activate_pe_computation(ctrl_activate_pe_computation), .array_data_valid_in(formatter_valid_out_to_sa), .array_a_in(skewed_a_to_sa), .array_b_in(skewed_b_to_sa), .array_a_data_valid_out(), .array_a_out(), .array_b_data_valid_out(), .array_b_out(), .tile_row_result_out(sa_partial_sum_out), .tile_row_result_valid(sa_partial_sum_valid), .sa_partial_sum_row_idx(sa_partial_sum_row_idx), .tile_all_pes_done_one_pass(tile_all_pes_done_one_pass), .start_new_systolic_pass(ctrl_start_new_systolic_pass));
    
    compute_controller #(.TILE_SIZE(TILE_SIZE), .PE_ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH)) 
    i_comp (.clk(clk), .rst_n(rst_n), .compute_req(compute_req), .compute_busy(compute_busy), .compute_done(compute_done), .dut_ready_for_sa_partial_sum(), .sa_partial_sum_valid(sa_partial_sum_valid), .sa_partial_sum_in(sa_partial_sum_out), .sa_partial_sum_row_idx(sa_partial_sum_row_idx), .sa_final_sum_in(sa_final_sum_in), .sa_tile_all_pes_done_one_pass(tile_all_pes_done_one_pass), .ctrl_start_new_systolic_pass(ctrl_start_new_systolic_pass), .ctrl_activate_pe_computation(ctrl_activate_pe_computation), .ctrl_c_data_to_sa(), .ctrl_enable_final_add(), .ctrl_partial_sum_to_sa(), .c_accum_raddr(c_accum_raddr), .c_accum_rdata(c_accum_rdata_from_A), .c_accum_waddr(c_accum_waddr), .c_accum_wdata(c_accum_wdata), .c_accum_we(c_accum_we));
    
    writer #(.MATRIX_SIZE(MATRIX_SIZE), .TILE_SIZE(TILE_SIZE), .MAIN_MEM_ADDR_WIDTH(MAIN_MEM_ADDR_WIDTH), .MAIN_MEM_DATA_WIDTH_BITS(MAIN_MEM_DATA_WIDTH_BITS), .BASE_ADDR_C(BASE_ADDR_C)) 
    i_writer (.clk(clk), .rst_n(rst_n), .write_req(writer_req), .i_tile_idx(i), .j_tile_idx(j), .write_busy(writer_busy), .write_done(writer_done), .mem_req_valid(omem_req_valid), .mem_req_wdata(omem_req_wdata), .mem_req_addr(omem_req_addr), .mem_req_ready(omem_req_ready), .sram_c_addr(sram_c_raddr_from_writer), .sram_c_rdata(sram_c_rdata_to_writer));

    // 简化: 假设存在一个理想的单周期加法器
    // 在真实设计中, 这会是一个多级流水线的加法器
    assign sa_final_sum_in = sa_partial_sum_out + c_accum_rdata_from_A;
    assign clear_pe_accum_for_k0 = (compute_k_ptr == 0);

    //======================================================================
    //== Top-Level FSM
    //======================================================================
    assign busy = (current_state != S_IDLE) && (current_state != S_DONE);
    assign done = (current_state == S_DONE);
    
    // --- Combinational FSM Logic ---
    always @(*) begin
        // 默认值, 防止锁存器
        next_state    = current_state;
        loader_req    = 1'b0;
        compute_req   = 1'b0;
        writer_req    = 1'b0;

        case (current_state)
            S_IDLE: begin
                if (start) begin
                    next_state = S_RUN_PIPELINE;
                end
            end

            S_RUN_PIPELINE: begin
                // --- 计算任务分派逻辑 ---
                // 条件: 对应的输入缓冲区数据有效 且 计算单元空闲
                if (buffer_is_valid[compute_source_is_pong] && !compute_busy) begin
                    compute_req = 1'b1;
                end

                // --- 加载任务分派逻辑 ---
                // 条件: 存在空闲的输入缓冲区 且 加载单元空闲 且 还有k需要加载
                if (!buffer_is_valid[load_target_is_pong] && !buffer_is_loading[load_target_is_pong] && !loader_busy && (load_k_ptr < NUM_TILES_PER_DIM)) begin
                    loader_req = 1'b1;
                end

                // --- 状态转移逻辑 ---
                // 当所有k的计算任务都已分派，进入流水线排空状态
                if (compute_k_ptr == NUM_TILES_PER_DIM) begin
                    next_state = S_DRAIN_PIPELINE;
                end
            end

            S_DRAIN_PIPELINE: begin
                // 等待流水线中的最后一个计算任务完成
                if (!compute_busy) begin
                    next_state = S_KICKOFF_WRITE;
                end
            end

            S_KICKOFF_WRITE: begin
                // 发起写回任务
                writer_req = 1'b1;
                
                // 判断是否所有瓦片都已完成
                if (i == NUM_TILES_PER_DIM - 1 && j == NUM_TILES_PER_DIM - 1) begin
                    // 这是最后一个瓦片，进入等待最终写回完成的状态
                    next_state = S_WAIT_FINAL_WRITE;
                end else begin
                    // 还有其他瓦片，返回RUN状态开始下一轮
                    next_state = S_RUN_PIPELINE;
                end
            end

            S_WAIT_FINAL_WRITE: begin
                // 等待最后一个写回任务完成
                if (!writer_busy) begin
                    next_state = S_DONE;
                end
            end

            S_DONE: begin
                if (!start) begin // 等待 start 信号释放后才能回到 IDLE
                    next_state = S_IDLE;
                end
            end
            
            default: begin
                next_state = S_IDLE;
            end
        endcase
    end

    // --- Sequential FSM Logic and State Variable Updates ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // FSM and Loop Counters
            current_state <= S_IDLE;
            i <= 0;
            j <= 0;
            load_k_ptr <= 0;
            compute_k_ptr <= 0;

            // A/B Buffer Control
            load_to_pong <= 1'b0;      // 第一次加载到 Ping (buffer 0)
            compute_from_pong <= 1'b0; // 对应计算也从 Ping 开始
            buffer_is_valid[0] <= 1'b0;
            buffer_is_valid[1] <= 1'b0;
            buffer_is_loading[0] <= 1'b0;
            buffer_is_loading[1] <= 1'b0;

            // C Buffer Control
            accum_to_pong <= 1'b0;
            write_from_pong <= 1'b0; // 假设写回单元从pong开始，与累加单元错开

        end else begin
            // --- FSM State Transition ---
            current_state <= next_state;

            // --- 任务触发与指针更新 (基于组合逻辑的决定) ---
            // 对 loader_req 的处理: 只有在请求成功发出时才更新指针和标志
            if (loader_req) begin
                // 检查以防止在 loader_busy 的延迟窗口内重复触发
                // 只有当目标缓冲区当前不是 loading 状态时，才真正地分派任务
                if (!buffer_is_loading[load_target_is_pong]) begin
                    buffer_is_loading[load_target_is_pong] <= 1'b1;
                    load_k_ptr <= load_k_ptr + 1;
                    load_to_pong <= ~load_to_pong; // 为下一次加载准备
                end
            end

            // 对 compute_req 的处理: 消耗数据，更新指针
            if (compute_req) begin
                 // 检查以确保不会意外触发
                if (buffer_is_valid[compute_source_is_pong]) begin
                    buffer_is_valid[compute_source_is_pong] <= 1'b0; // 消耗掉这个缓冲区的数据
                    compute_k_ptr <= compute_k_ptr + 1;
                    compute_from_pong <= ~compute_from_pong; // 为下一次计算准备
                end
            end

            // --- 状态标志更新 (基于硬件的完成信号) ---
            if (loader_done) begin
                // 当加载任务完成时，我们需要找出是哪个缓冲区完成了加载
                // 这种写法比依赖 ~load_target_is_pong 更稳健
                if (buffer_is_loading[0]) begin
                    buffer_is_loading[0] <= 1'b0;
                    buffer_is_valid[0] <= 1'b1;
                end
                if (buffer_is_loading[1]) begin
                    buffer_is_loading[1] <= 1'b0;
                    buffer_is_valid[1] <= 1'b1;
                end
            end
            
            // --- C[i,j] 瓦片迭代与全局状态重置 ---
            if (next_state == S_RUN_PIPELINE && current_state != S_RUN_PIPELINE) begin
                // 这是一个新C_ij瓦片的开始 (从 KICKOFF_WRITE 或 IDLE 进入)
                load_k_ptr <= 0;
                compute_k_ptr <= 0;

                load_to_pong <= 1'b0;
                compute_from_pong <= 1'b0;

                buffer_is_valid[0] <= 1'b0;
                buffer_is_valid[1] <= 1'b0;
                buffer_is_loading[0] <= 1'b0;
                buffer_is_loading[1] <= 1'b0;

                // 更新 i, j 索引
                if (current_state == S_KICKOFF_WRITE) begin
                     if (j == NUM_TILES_PER_DIM - 1) begin
                         j <= 0;
                         i <= i + 1;
                     end else begin
                         j <= j + 1;
                     end
                end
            end
            
            if (current_state == S_KICKOFF_WRITE) begin
                // C缓冲区的乒乓切换
                accum_to_pong <= ~accum_to_pong;
                write_from_pong <= ~write_from_pong;
            end
            
            // --- 顶层复位逻辑 ---
            if (next_state == S_IDLE) begin
                i <= 0;
                j <= 0;
            end
        end
    end

endmodule