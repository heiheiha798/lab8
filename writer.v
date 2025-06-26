//
// Filename: writer.v
// Description: An ultra high-performance, pipelined data writer.
//              This is the FINAL version, designed NOT to be a system bottleneck.
//              It assumes a 64-bit wide C-SRAM to match the memory bus, enabling
//              a fully pipelined 1-to-1 data transfer from SRAM to main memory.
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
    input wire                                  mem_write_done, // For future use with more complex buses

    // SRAM 读取接口 (关键: 64位宽)
    output reg [$clog2(TILE_SIZE*TILE_SIZE*4/8)-1:0]   sram_c_addr, // 4 bytes/elem, 8 bytes/word
    input wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]   sram_c_rdata
);
    
    //--------------------------------------------------------------------------
    // 内部参数定义
    //--------------------------------------------------------------------------
    localparam NUM_TILES_PER_DIM   = MATRIX_SIZE / TILE_SIZE;
    localparam C_TILE_BYTES        = TILE_SIZE * TILE_SIZE * 4; // 每个元素32位
    localparam MEM_WRITES_PER_TILE = C_TILE_BYTES / (MAIN_MEM_DATA_WIDTH_BITS / 8); // 1024 / 8 = 128

    // 使用 typedef 定义FSM状态
    typedef enum logic [2:0] { // Changed to [2:0] to accommodate 5 states
        S_IDLE,
        S_REQ_SRAM,     // 新状态: 请求从 SRAM C 读取数据
        S_WAIT_SRAM_DATA, // 新状态: 等待 SRAM C 数据有效
        S_WRITE_MEM,    // 现有状态: 写入主存
        S_DONE
    } state_t;

    //--------------------------------------------------------------------------
    // 内部寄存器定义
    //--------------------------------------------------------------------------
    state_t current_state, next_state;
    
    reg [$clog2(NUM_TILES_PER_DIM)-1:0] i_reg, j_reg;
    // 用于组合逻辑中生成寄存器的下一状态值
    reg [$clog2(NUM_TILES_PER_DIM)-1:0] i_reg_d, j_reg_d; 
    
    // sram_read_ptr: 指向当前Tile中SRAM C要读取的下一个64位字
    reg [$clog2(MEM_WRITES_PER_TILE)-1:0] sram_read_ptr_q, sram_read_ptr_d;
    // mem_write_ptr: 指向当前Tile要写入主存的下一个64位字
    reg [$clog2(MEM_WRITES_PER_TILE)-1:0] mem_write_ptr_q, mem_write_ptr_d;

    // data_to_write_to_mem_q: 保存从SRAM读取的数据，准备写入内存
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0] data_to_write_to_mem_q; 

    // 调试信号
    reg [$clog2(TILE_SIZE*TILE_SIZE*4/8)-1:0] sram_c_addr_prev_log;
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0]   sram_c_rdata_prev_log;


    //--------------------------------------------------------------------------
    // FSM 状态转移逻辑 (Sequential)
    //--------------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state <= S_IDLE;
            sram_read_ptr_q <= 0;
            mem_write_ptr_q <= 0;
            data_to_write_to_mem_q <= {MAIN_MEM_DATA_WIDTH_BITS{1'b0}};
            i_reg <= 0; // Reset i_reg
            j_reg <= 0; // Reset j_reg
        end else begin
            current_state   <= next_state;
            sram_read_ptr_q   <= sram_read_ptr_d;
            mem_write_ptr_q   <= mem_write_ptr_d;
            i_reg <= i_reg_d; // 从下一状态寄存器更新i_reg
            j_reg <= j_reg_d; // 从下一状态寄存器更新j_reg

            // 在S_WAIT_SRAM_DATA状态下锁存SRAM数据
            if (current_state == S_WAIT_SRAM_DATA) begin 
                data_to_write_to_mem_q <= sram_c_rdata; // 锁存从SRAM读取的数据
            end

            // 调试日志
            sram_c_addr_prev_log <= sram_c_addr; // sram_c_addr是组合输出
            sram_c_rdata_prev_log <= sram_c_rdata; // sram_c_rdata是输入
        end
        $display("[%0t] [WRITER_FF_START] 状态: %s, sram_rd_ptr: %d, mem_wr_ptr: %d, 待写入数据: %h",
                     $time, current_state.name(), sram_read_ptr_q, mem_write_ptr_q, data_to_write_to_mem_q);
    end

    //--------------------------------------------------------------------------
    // 核心状态机及组合逻辑 (Combinational)
    //--------------------------------------------------------------------------
    always @(*) begin
        // 默认输出值
        next_state    = current_state;
        write_busy    = (current_state != S_IDLE && current_state != S_DONE);
        write_done    = 1'b0;
        mem_req_valid = 1'b0;
        mem_req_wdata = data_to_write_to_mem_q; // 使用锁存的数据进行写入
        mem_req_addr  = BASE_ADDR_C + 
                        (i_reg * NUM_TILES_PER_DIM * C_TILE_BYTES) + 
                        (j_reg * C_TILE_BYTES) + 
                        (mem_write_ptr_q * (MAIN_MEM_DATA_WIDTH_BITS / 8)); // 地址基于 mem_write_ptr_q
        sram_c_addr   = sram_read_ptr_q; // SRAM 地址基于 sram_read_ptr_q

        sram_read_ptr_d = sram_read_ptr_q; // 默认: 不变
        mem_write_ptr_d = mem_write_ptr_q; // 默认: 不变
        i_reg_d = i_reg; // 默认: 保持当前值
        j_reg_d = j_reg; // 默认: 保持当前值

        // $display("[%0t] [WRITER_COMB_START] 状态(FSM): %s, sram_rd_ptr(reg): %d, mem_wr_ptr(reg): %d",
        //              $time, current_state.name(), sram_read_ptr_q, mem_write_ptr_q);
        // $display("[%0t] [WRITER_COMB_OUTS] sram_c_addr_out: %d, mem_req_addr_out: 0x%h, mem_req_wdata_out: %h, mem_req_valid_next: %b",
        //              $time, sram_c_addr, mem_req_addr, mem_req_wdata, mem_req_valid);

        case (current_state)
            S_IDLE: begin
                if (write_req) begin
                    next_state = S_REQ_SRAM;
                    sram_read_ptr_d = 0; // 开始从SRAM C的Tile开头读取
                    mem_write_ptr_d = 0; // 开始从主存的Tile开头写入
                    i_reg_d = i_tile_idx; // 赋值给下一状态寄存器
                    j_reg_d = j_tile_idx; // 赋值给下一状态寄存器
                    $display("[%0t] [WRITER] 新的写入请求. i_tile=%d, j_tile=%d. 进入 S_REQ_SRAM 状态.", $time, i_tile_idx, j_tile_idx);
                end
            end

            S_REQ_SRAM: begin // 发出SRAM读取请求
                // sram_c_addr 已经设置为 sram_read_ptr_q
                // 此状态确保 sram_c_addr 稳定一个周期，以便SRAM C锁存它。
                next_state = S_WAIT_SRAM_DATA;
                $display("[%0t] [WRITER] 在 S_REQ_SRAM 状态. sram_c_addr (用于SRAM读取) = %d.", $time, sram_c_addr);
            end

            S_WAIT_SRAM_DATA: begin // 等待SRAM数据 (1周期延迟)
                // 在此周期，sram_c_rdata (Writer的输入) 现在包含 sram_read_ptr_q 的数据
                // 此数据将在时钟上升沿锁存到 data_to_write_to_mem_q。
                // 如果还未到末尾，我们可以并行发出下一个SRAM读取请求。
                if (sram_read_ptr_q < MEM_WRITES_PER_TILE - 1) begin // 如果该Tile还有更多数据要从SRAM读取
                    sram_read_ptr_d = sram_read_ptr_q + 1; // 递增指针以进行下一次SRAM读取
                end
                next_state = S_WRITE_MEM; // 在下一个周期写入主存
                $display("[%0t] [WRITER] 在 S_WAIT_SRAM_DATA 状态. 地址 %d (上一周期请求) 的数据现在在 sram_c_rdata (%h) 上. 将被锁存. 下一个 sram_read_ptr_d=%d.",
                             $time, sram_read_ptr_q, sram_c_rdata, sram_read_ptr_d);
            end

            S_WRITE_MEM: begin
                // mem_req_wdata 已经设置为 data_to_write_to_mem_q (来自上一次SRAM读取的数据)
                // mem_req_addr 已经基于 mem_write_ptr_q 设置
                mem_req_valid = 1'b1; // 断言有效，写入主存

                $display("[%0t] [WRITER] 在 S_WRITE_MEM 状态. 写入 mem_write_ptr %d 到地址 0x%h，数据 %h.",
                             $time, mem_write_ptr_q, mem_req_addr, mem_req_wdata);

                if (mem_req_ready) begin // 如果主存接受写入
                    mem_write_ptr_d = mem_write_ptr_q + 1; // 递增主存写入指针

                    if (mem_write_ptr_q == MEM_WRITES_PER_TILE - 1) begin // 该Tile的最后一次写入
                        next_state = S_DONE;
                        $display("[%0t] [WRITER] Tile的最后一次写入 (ptr %d) 已接受. 进入 S_DONE 状态.", $time, mem_write_ptr_q);
                    end else begin
                        // 我们需要返回请求SRAM的下一段数据，如果可用的话。
                        // 或者如果下一个SRAM读取已经在进行中，则等待。
                        // 由于我们对SRAM读取和内存写入进行了流水线处理，sram_read_ptr 领先。
                        next_state = S_REQ_SRAM; 
                        $display("[%0t] [WRITER] 写入 ptr %d 已接受. 下一个 mem_write_ptr_d=%d. 进入 S_REQ_SRAM 状态，sram_read_ptr 为 %d.",
                                     $time, mem_write_ptr_q, mem_write_ptr_d, sram_read_ptr_q);
                    end
                end else begin
                    // 内存未准备好，保持在 S_WRITE_MEM 状态以重试当前写入
                    next_state = S_WRITE_MEM;
                    // $display("[%0t] [WRITER] 主存未准备好. 重试写入 ptr %d.", $time, mem_write_ptr_q);
                end
            end

            S_DONE: begin
                write_done = 1'b1; // 脉冲高一个周期
                next_state = S_IDLE;
                $display("[%0t] [WRITER] 在 S_DONE 状态. 脉冲 write_done. 进入 S_IDLE 状态.", $time);
            end

            default: begin
                next_state = S_IDLE;
            end
        endcase
    end

endmodule
