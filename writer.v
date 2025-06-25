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
    reg [$clog2(TILE_SIZE*TILE_SIZE*4/8)-1:0] prev_sram_c_addr_for_log;

    // 使用 typedef 定义FSM状态
    typedef enum logic [1:0] {
        S_IDLE,
        S_WRITING,
        S_DONE
    } state_t;

    //--------------------------------------------------------------------------
    // 内部寄存器定义
    //--------------------------------------------------------------------------
    state_t current_state, next_state;
    
    reg [$clog2(NUM_TILES_PER_DIM)-1:0] i_reg, j_reg;
    reg [$clog2(MEM_WRITES_PER_TILE + 1)-1:0] mem_transaction_cnt;
    
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0] sram_data_pipeline;

    //--------------------------------------------------------------------------
    // FSM 状态转移逻辑 (Sequential)
    //--------------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state <= S_IDLE;
        end else begin
            current_state <= next_state;
            // 锁存 sram_c_addr 以便在下一个周期打印 sram_c_rdata 时知道是哪个地址请求的数据
            prev_sram_c_addr_for_log <= sram_c_addr; 
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
        mem_req_wdata = {MAIN_MEM_DATA_WIDTH_BITS{1'b0}}; // 显式初始化为0
        mem_req_addr  = {MAIN_MEM_ADDR_WIDTH{1'b0}};      // 显式初始化为0
        sram_c_addr   = 1'b0;

        case (current_state)
            S_IDLE: begin
                if (write_req) begin
                    next_state = S_WRITING;
                end
            end

            S_WRITING: begin
                write_busy = 1'b1;
                sram_c_addr = mem_transaction_cnt; // 当前周期请求SRAM的地址
                mem_req_wdata = sram_data_pipeline; // 写入的数据是上一周期从SRAM读出的数据

                mem_req_addr = BASE_ADDR_C + 
                            (i_reg * NUM_TILES_PER_DIM * C_TILE_BYTES) + 
                            (j_reg * C_TILE_BYTES) + 
                            (mem_transaction_cnt * (MAIN_MEM_DATA_WIDTH_BITS / 8));
                
                if (mem_transaction_cnt < MEM_WRITES_PER_TILE) begin
                    mem_req_valid = 1'b1; 

                    // 打印即将写入主存的数据和地址 (组合逻辑值)
                    if (i_reg == 0 && j_reg == 0 && mem_transaction_cnt < 2) begin
                        $display("[%0t] [WRITER_MEM_WRITE] Addr: 0x%h, WData_Low32: %d, WData_High32: %d (Raw: 0x%h)",
                                $time, mem_req_addr, 
                                mem_req_wdata[31:0], mem_req_wdata[63:32], mem_req_wdata);
                    end
                end else begin 
                    mem_req_valid = 1'b0; 
                end
                
                if (mem_transaction_cnt == MEM_WRITES_PER_TILE) begin
                    next_state = S_DONE;
                end
            end

            S_DONE: begin
                $display("[%0t] [WRITER_FSM] Reached S_DONE state. Pulsing write_done.", $time);
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
            sram_data_pipeline <= {MAIN_MEM_DATA_WIDTH_BITS{1'b0}}; // 显式初始化为0
        end else begin
            // 打印 SRAM_C_RData_Now: 这是由 prev_sram_c_addr_for_log 在上一个周期请求的SRAM数据
            if (current_state == S_WRITING && i_reg == 0 && j_reg == 0 && mem_transaction_cnt < 2) begin
                $display("[%0t] [WRITER_SRAM_READ] SRAM_C_Addr_Req_Prev_Cycle: %d, SRAM_C_RData_Now: 0x%h (Low32: %d, High32: %d)",
                            $time, prev_sram_c_addr_for_log, sram_c_rdata, sram_c_rdata[31:0], sram_c_rdata[63:32]);
            end
            sram_data_pipeline <= sram_c_rdata; // 锁存当前SRAM读取的数据，用于下一个周期写入主存

            case (current_state)
                S_IDLE: begin
                    if (write_req) begin
                        i_reg <= i_tile_idx;
                        j_reg <= j_tile_idx;
                        $display("[%0t] [WRITER] INFO: New request latched (i=%d, j=%d).", $time, i_tile_idx, j_tile_idx);
                    end
                    mem_transaction_cnt <= 0;
                end
                
                S_WRITING: begin
                    if (mem_req_valid && mem_req_ready) begin
                        mem_transaction_cnt <= mem_transaction_cnt + 1;
                        $display("[%0t] [WRITER] INFO: Writing to Mem, transaction %d (old_val). Addr 0x%h. mem_req_valid=%b, mem_req_ready=%b",
                            $time, mem_transaction_cnt, mem_req_addr, mem_req_valid, mem_req_ready);
                    end else if (current_state == S_WRITING) begin // Add an else if to see why it's not incrementing
                        $display("[%0t] [WRITER_STALL] In S_WRITING, but mem_transaction_cnt NOT incrementing. mem_req_valid=%b, mem_req_ready=%b, mem_trans_cnt_curr=%d",
                                $time, mem_req_valid, mem_req_ready, mem_transaction_cnt);
                    end
                end
                
                S_DONE: begin
                    $display("[%0t] [WRITER] INFO: Write request completed. Returning to IDLE.", $time);
                end
            endcase
        end
    end

endmodule