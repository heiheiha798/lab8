//
// Filename: writer_debug_fixed.v
// Description: An ultra high-performance, pipelined data writer.
//              This is the FINAL version, designed NOT to be a system bottleneck.
//              It achieves a throughput of one 64-bit word per cycle by deeply
//              pipelining the SRAM read and main memory write operations.
//              Fixed off-by-one error and pipeline synchronization for address.
//              S_PIPELINE_FILL state has been merged into S_STREAMING.
//
`timescale 1ns / 1ps

module writer #(
    // 主参数
    parameter MATRIX_SIZE               = 48,
    parameter TILE_SIZE                 = 16,
    
    // 外部总线参数
    parameter MAIN_MEM_ADDR_WIDTH       = 32,
    parameter MAIN_MEM_DATA_WIDTH_BITS  = 64,

    // 矩阵基地址
    parameter BASE_ADDR_C               = 32'h30000000
)(
    // 控制接口
    input wire                                  clk,
    input wire                                  rst_n,
    input wire                                  write_req,
    input wire [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]    i_tile_idx,
    input wire [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]    j_tile_idx,
    output reg                                  write_busy,
    output reg                                  write_done,

    // 主存写入接口
    output reg                                  mem_req_valid,
    output reg [MAIN_MEM_DATA_WIDTH_BITS-1:0]   mem_req_wdata,
    output reg [MAIN_MEM_ADDR_WIDTH-1:0]        mem_req_addr,
    input wire                                  mem_req_ready,
    input wire                                  mem_write_done,

    // SRAM 读取接口
    output reg [$clog2(TILE_SIZE*TILE_SIZE*4/8)-1:0]   sram_c_addr,
    input wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]   sram_c_rdata
);
    
    //--------------------------------------------------------------------------
    // 内部参数定义
    //--------------------------------------------------------------------------
    localparam NUM_TILES_PER_DIM   = MATRIX_SIZE / TILE_SIZE;
    localparam C_TILE_BYTES        = TILE_SIZE * TILE_SIZE * 4;
    localparam MEM_WRITES_PER_TILE = C_TILE_BYTES / (MAIN_MEM_DATA_WIDTH_BITS / 8);

    // 使用 typedef 定义FSM状态
    typedef enum logic [1:0] {
        S_IDLE,
        S_STREAMING,     // 全速流式写入，包括启动和后续的数据传输
        S_PIPELINE_DRAIN // 等待最后一个写入完成
    } state_t;

    //--------------------------------------------------------------------------
    // 内部寄存器定义
    //--------------------------------------------------------------------------
    state_t current_state, next_state;
    
    reg [$clog2(NUM_TILES_PER_DIM)-1:0] i_reg_q, j_reg_q;
    
    // write_ptr: 统一的指针，既用于SRAM读，也用于主存写（通过流水线寄存器同步）
    reg [$clog2(MEM_WRITES_PER_TILE)-1:0] write_ptr_q, write_ptr_d;

    // 流水线寄存器
    // mem_req_valid_s1_q: SRAM读请求发出后一个周期，主存写请求的valid信号
    reg mem_req_valid_s1_q; 
    // mem_req_addr_s1_q: SRAM读请求发出后一个周期，主存写请求的地址
    reg [MAIN_MEM_ADDR_WIDTH-1:0] mem_req_addr_s1_q;

    //--------------------------------------------------------------------------
    // FSM 状态转移逻辑 (Sequential)
    //--------------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state <= S_IDLE;
            write_ptr_q <= 0;
            i_reg_q <= 0;
            j_reg_q <= 0;
            mem_req_valid_s1_q <= 1'b0;
            mem_req_addr_s1_q <= 0;
        end else begin
            current_state <= next_state;
            
            // 只有当流水线没有被阻塞时才更新指针和流水线寄存器
            // mem_req_valid 是当前周期组合逻辑输出，如果它为高且mem_req_ready为低，则表示阻塞
            if (mem_req_ready || !mem_req_valid) begin
                 write_ptr_q <= write_ptr_d;
                 // 阶段1 -> 阶段2 的 valid 传递
                 // 当处于S_STREAMING状态时，SRAM读请求有效，其对应的mem_req_valid_s1_q下一周期才有效
                 mem_req_valid_s1_q <= (current_state == S_STREAMING);
                 
                 // 阶段1 地址计算并锁存
                 // 只有在S_STREAMING状态且没有阻塞时才更新地址流水线寄存器
                 if (current_state == S_STREAMING) begin
                     mem_req_addr_s1_q <= BASE_ADDR_C + 
                                          (i_reg_q * NUM_TILES_PER_DIM * C_TILE_BYTES) + 
                                          (j_reg_q * C_TILE_BYTES) + 
                                          (write_ptr_q * (MAIN_MEM_DATA_WIDTH_BITS / 8));
                 end
            end

            // 锁存tile索引：在S_IDLE接收到写请求时，在下一个周期锁存
            if (current_state == S_IDLE && write_req) begin
                i_reg_q <= i_tile_idx;
                j_reg_q <= j_tile_idx;
            end
        end
    end

    //--------------------------------------------------------------------------
    // 核心状态机及组合逻辑 (Combinational)
    //--------------------------------------------------------------------------
    always_comb begin
        // 默认输出值
        next_state    = current_state;
        write_busy    = (current_state != S_IDLE);
        write_done    = 1'b0;
        
        // --- 流水线阶段 2: 主存写入 ---
        // 只有当上一级(s1)有效时，本级(s2)才有效
        mem_req_valid = mem_req_valid_s1_q; 
        mem_req_wdata = sram_c_rdata; // 直接使用SRAM输出，因为数据已经经过流水线同步
        mem_req_addr  = mem_req_addr_s1_q; // 使用流水线寄存器中的地址

        // --- 流水线阶段 1: SRAM读取 ---
        sram_c_addr = write_ptr_q;

        // 默认指针不更新
        write_ptr_d = write_ptr_q;

        case (current_state)
            S_IDLE: begin
                if (write_req) begin
                    next_state = S_STREAMING;
                    write_ptr_d = 0; // 准备从地址0开始读
                end
            end

            S_STREAMING: begin
                // 持续发出SRAM读请求和MEM写请求
                // 如果流水线没有被阻塞，则指针前进
                if (mem_req_ready || !mem_req_valid) begin // 没有阻塞
                    write_ptr_d = write_ptr_q + 1;
                    if (write_ptr_q == MEM_WRITES_PER_TILE - 1) begin
                        // 已经发出了最后一个SRAM读请求 (例如地址127)
                        // 下一周期 mem_req_valid_s1_q 会被拉高，然后进入 S_PIPELINE_DRAIN
                        next_state = S_PIPELINE_DRAIN;
                    end
                end
            end

            S_PIPELINE_DRAIN: begin
                // 此时，最后一个写请求(mem_req_valid)已经发出
                // 等待它完成
                if (mem_write_done) begin // 确认最后一个写入完成 (使用mem_write_done更准确)
                    write_done = 1'b1;
                    next_state = S_IDLE;
                end
                // else 保持状态，等待内存完成最后一个写操作
            end
        endcase
    end

endmodule
