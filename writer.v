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
    input wire                                          clk,
    input wire                                          rst_n,
    input wire                                          write_req,
    input wire [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      i_tile_idx,
    input wire [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      j_tile_idx,
    output reg                                          write_busy,
    output reg                                          write_done,

    // 主存写入接口
    output reg                                          mem_req_valid,
    output reg [MAIN_MEM_DATA_WIDTH_BITS-1:0]           mem_req_wdata,
    output reg [MAIN_MEM_ADDR_WIDTH-1:0]                mem_req_addr,
    input wire                                          mem_req_ready,
    input wire                                          mem_write_done, // For future use with more complex buses

    // SRAM 读取接口 (关键: 64位宽)
    output reg [$clog2(TILE_SIZE*TILE_SIZE/2)-1:0]      sram_c_addr,
    input wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]           sram_c_rdata
);
    
    //--------------------------------------------------------------------------
    // 内部参数定义
    //--------------------------------------------------------------------------
    localparam NUM_TILES_PER_DIM   = MATRIX_SIZE / TILE_SIZE;
    localparam C_TILE_BYTES        = TILE_SIZE * TILE_SIZE * 4; // 每个元素32位
    localparam MEM_WRITES_PER_TILE = C_TILE_BYTES / (MAIN_MEM_DATA_WIDTH_BITS / 8); // 1024 / 8 = 128

    localparam FSM_STATE_WIDTH = 2;
    localparam S_IDLE          = {FSM_STATE_WIDTH{1'b0}};
    localparam S_WRITING       = S_IDLE + 1;
    localparam S_DONE          = S_WRITING + 1;

    //--------------------------------------------------------------------------
    // 内部寄存器定义
    //--------------------------------------------------------------------------
    reg [FSM_STATE_WIDTH-1:0] current_state, next_state;
    
    reg [$clog2(NUM_TILES_PER_DIM)-1:0] i_reg, j_reg;
    reg [$clog2(MEM_WRITES_PER_TILE + 1)-1:0] mem_transaction_cnt;
    
    // 用于实现SRAM读与MEM写的流水线寄存器
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0] sram_data_pipeline;

    //--------------------------------------------------------------------------
    // FSM 状态转移逻辑 (Sequential)
    //--------------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state <= S_IDLE;
        end else begin
            current_state <= next_state;
        end
    end

    //--------------------------------------------------------------------------
    // 核心状态机及组合逻辑 (Combinational)
    //--------------------------------------------------------------------------
    always @(*) begin
        // 默认输出值
        next_state    = current_state;
        write_busy    = 1'b0;
        write_done    = 1'b0;
        mem_req_valid = 1'b0;
        mem_req_wdata = 1'b0;
        mem_req_addr  = 1'b0;
        sram_c_addr   = 1'b0;

        case (current_state)
            S_IDLE: begin
                if (write_req) begin
                    next_state = S_WRITING;
                end
            end

            S_WRITING: begin
                write_busy = 1'b1;

                // --- SRAM读取逻辑 ---
                // 持续不断地请求SRAM中的下一个64位字
                sram_c_addr = mem_transaction_cnt;

                // --- 内存写入逻辑 ---
                // 要写入内存的数据是上一个周期从SRAM读出的，已存入流水线寄存器
                mem_req_wdata = sram_data_pipeline; 
                mem_req_addr = (i_reg * NUM_TILES_PER_DIM * C_TILE_BYTES) + (j_reg * C_TILE_BYTES) + (mem_transaction_cnt * (MAIN_MEM_DATA_WIDTH_BITS / 8));
                
                // 只要还有数据需要发送，就保持写请求有效
                if (mem_transaction_cnt < MEM_WRITES_PER_TILE) begin
                    mem_req_valid = 1'b1;
                end
                
                // --- 状态转移逻辑 ---
                // 当最后一个字已经被内存接收，任务就完成了
                if (mem_transaction_cnt == MEM_WRITES_PER_TILE) begin
                     // Note: We check for count reaching max, assuming the last req has been accepted.
                     // A more robust design might wait for mem_write_done for the last transaction.
                    next_state = S_DONE;
                end
            end

            S_DONE: begin
                write_done = 1'b1;
                next_state = S_IDLE;
            end

            default: begin
                next_state = S_IDLE;
            end
        endcase
    end

    //--------------------------------------------------------------------------
    // 内部寄存器更新逻辑 (Sequential)
    //--------------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            i_reg <= 0;
            j_reg <= 0;
            mem_transaction_cnt <= 0;
            sram_data_pipeline <= 0;
        end else begin
            // 这是实现流水线的关键: 每个周期都将SRAM的输出锁存到流水线寄存器中,
            // 供下一个周期发送给内存。
            sram_data_pipeline <= sram_c_rdata;

            case (current_state)
                S_IDLE: begin
                    if (write_req) begin
                        i_reg <= i_tile_idx;
                        j_reg <= j_tile_idx;
                        $display("%0t [WRITER] INFO: New request latched (i=%d, j=%d).", $time, i_tile_idx, j_tile_idx);
                    end
                    // 在IDLE状态，为下一次写操作重置计数器
                    mem_transaction_cnt <= 0;
                end
                
                S_WRITING: begin
                    // 仅当内存准备好接收时，才递增计数器，准备下一次传输
                    if (mem_req_valid && mem_req_ready) begin
                        mem_transaction_cnt <= mem_transaction_cnt + 1;
                        $display("%0t [WRITER] INFO: Writing to Mem, transaction %d. Addr 0x%h", $time, mem_transaction_cnt, mem_req_addr);
                    end
                end
                
                S_DONE: begin
                    $display("%0t [WRITER] INFO: Write request completed. Returning to IDLE.", $time);
                end
            endcase
        end
    end

endmodule