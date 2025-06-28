//
// Filename: loader.v
// Description: A high-performance, pipelined data loader for the systolic array accelerator.
//              It pipelines memory requests for A and B tiles and assumes a 64-bit wide
//              SRAM interface to match the memory bus width, enabling single-cycle writes.
//
`timescale 1ns / 1ps

module loader #(
    // 主参数
    parameter MATRIX_SIZE               = 48,
    parameter TILE_SIZE                 = 16,
    
    // 外部总线参数
    parameter MAIN_MEM_ADDR_WIDTH       = 32,
    parameter MAIN_MEM_DATA_WIDTH_BITS  = 64,

    // 矩阵基地址
    parameter BASE_ADDR_A               = 32'h10000000,
    parameter BASE_ADDR_B               = 32'h20000000
)(
    // 控制接口
    input wire                                          clk,
    input wire                                          rst_n,
    input wire                                          load_req,
    input wire [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      i_tile_idx,
    input wire [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      j_tile_idx,
    input wire [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      k_tile_idx,
    input wire                                          load_to_ping,
    output reg                                          load_busy,
    output reg                                          load_done,

    // 主存读取接口
    output reg                                          mem_req_valid,
    input wire                                          mem_req_ready,
    input wire                                          mem_resp_valid,
    input wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]           mem_resp_rdata,
    output reg [MAIN_MEM_ADDR_WIDTH-1:0]                mem_req_addr,

    // SRAM A 写入接口 (64-bit wide)
    output reg [$clog2(TILE_SIZE*TILE_SIZE*8/MAIN_MEM_DATA_WIDTH_BITS)-1:0] sram_a_addr,
    output reg [MAIN_MEM_DATA_WIDTH_BITS-1:0]                             sram_a_wdata,
    output reg                                                            sram_a_we,

    // SRAM B 写入接口 (64-bit wide)
    output reg [$clog2(TILE_SIZE*TILE_SIZE*8/MAIN_MEM_DATA_WIDTH_BITS)-1:0] sram_b_addr,
    output reg [MAIN_MEM_DATA_WIDTH_BITS-1:0]                             sram_b_wdata,
    output reg                                                            sram_b_we
);

    //--------------------------------------------------------------------------
    // 内部参数定义
    //--------------------------------------------------------------------------
    localparam NUM_TILES_PER_DIM = MATRIX_SIZE / TILE_SIZE;
    localparam A_B_TILE_BYTES    = TILE_SIZE * TILE_SIZE; // SINT8, so 1 byte per element
    localparam WORDS_PER_TILE    = A_B_TILE_BYTES / (MAIN_MEM_DATA_WIDTH_BITS / 8);

    localparam FSM_STATE_WIDTH = 2;
    localparam S_IDLE          = {FSM_STATE_WIDTH{1'b0}};
    localparam S_LOADING       = S_IDLE + 1;
    localparam S_DONE          = S_LOADING + 1;

    //--------------------------------------------------------------------------
    // 内部寄存器定义
    //--------------------------------------------------------------------------
    reg [FSM_STATE_WIDTH-1:0] current_state, next_state;

    // Latched input registers
    reg [$clog2(NUM_TILES_PER_DIM)-1:0] i_reg, j_reg, k_reg;
    reg                                load_to_ping_reg;
    
    // Pipelined request and response counters
    reg [$clog2(WORDS_PER_TILE*2)-1:0] req_cnt;  // 总请求计数 (0 to 63)
    reg [$clog2(WORDS_PER_TILE*2)-1:0] resp_cnt; // 总响应计数 (0 to 63)
    
    reg [MAIN_MEM_ADDR_WIDTH-1:0] a_base_addr, b_base_addr;

    //--------------------------------------------------------------------------
    // FSM 状态转移逻辑
    //--------------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state <= S_IDLE;
        end else begin
            current_state <= next_state;
        end
    end

    //--------------------------------------------------------------------------
    // 核心状态机及组合逻辑
    //--------------------------------------------------------------------------
    always @(*) begin
        // Default output values
        next_state    = current_state;
        load_busy     = 1'b0;
        load_done     = 1'b0;
        mem_req_valid = 1'b0;
        mem_req_addr  = {MAIN_MEM_ADDR_WIDTH{1'b0}};
        sram_a_addr   = 0;
        sram_a_wdata  = 0;
        sram_a_we     = 1'b0;
        sram_b_addr   = 0;
        sram_b_wdata  = 0;
        sram_b_we     = 1'b0;
        
        case (current_state)
            S_IDLE: begin
                if (load_req) begin
                    next_state = S_LOADING;
                end
            end

            S_LOADING: begin
                load_busy = 1'b1;

                // Request Logic
                // Keep sending requests as long as not all requests have been sent
                if (req_cnt < WORDS_PER_TILE * 2 && mem_req_ready) begin
                    mem_req_valid = 1'b1;
                    if (req_cnt < WORDS_PER_TILE) begin
                        // Requesting A tile
                        mem_req_addr = a_base_addr + (req_cnt * (MAIN_MEM_DATA_WIDTH_BITS / 8));
                    end else begin
                        // Requesting B tile
                        mem_req_addr = b_base_addr + ((req_cnt - WORDS_PER_TILE) * (MAIN_MEM_DATA_WIDTH_BITS / 8));
                    end
                end

                // Response & SRAM Write Logic
                // Write to SRAM as long as there is a memory response
                if (mem_resp_valid) begin
                    if (resp_cnt < WORDS_PER_TILE) begin
                        // Response corresponds to A tile
                        sram_a_we = 1'b1;
                        sram_a_wdata = mem_resp_rdata;
                        sram_a_addr = resp_cnt; // Address is 0 to 31
                    end else begin
                        // Response corresponds to B tile
                        sram_b_we = 1'b1;
                        sram_b_wdata = mem_resp_rdata;
                        sram_b_addr = resp_cnt - WORDS_PER_TILE; // Address is 0 to 31
                    end
                end

                // State transition logic
                // Task is done when all responses have been received and processed
                if (resp_cnt == (WORDS_PER_TILE * 2) - 1 && mem_resp_valid) begin
                    next_state = S_DONE;
                end
            end

            S_DONE: begin
                load_done = 1'b1;
                next_state = S_IDLE;
            end
            
            default: begin
                next_state = S_IDLE;
            end
        endcase
    end
    
    //--------------------------------------------------------------------------
    // 内部寄存器与计数器更新逻辑
    //--------------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            i_reg            <= 0;
            j_reg            <= 0;
            k_reg            <= 0;
            load_to_ping_reg <= 1'b0;
            req_cnt          <= 0;
            resp_cnt         <= 0;
            a_base_addr      <= 0;
            b_base_addr      <= 0;
        end else begin
            case (current_state)
                S_IDLE: begin
                    if (load_req) begin
                        // Latch inputs and calculate base addresses
                        i_reg            <= i_tile_idx;
                        j_reg            <= j_tile_idx;
                        k_reg            <= k_tile_idx;
                        load_to_ping_reg <= load_to_ping;
                        a_base_addr      <= BASE_ADDR_A + ((i_tile_idx * NUM_TILES_PER_DIM + k_tile_idx) * A_B_TILE_BYTES);
                        b_base_addr      <= BASE_ADDR_B + ((k_tile_idx * NUM_TILES_PER_DIM + j_tile_idx) * A_B_TILE_BYTES);
                    end
                    // Reset counters in IDLE state
                    req_cnt  <= 0;
                    resp_cnt <= 0;
                end
                
                S_LOADING: begin
                    // Pipelined update of request counter
                    if (req_cnt < WORDS_PER_TILE * 2 && mem_req_ready && mem_req_valid) begin
                        req_cnt <= req_cnt + 1;
                    end
                    
                    // Pipelined update of response counter and data display
                    if (mem_resp_valid) begin
                        resp_cnt <= resp_cnt + 1;
                        // Display what is loaded in each FSM cycle
                        $display("%0t [LOADER] FSM周期中第%d个加载的数据, 具体数值是0x%h", $time, resp_cnt + 1, mem_resp_rdata);
                    end
                end
                
                S_DONE: begin
                    // Empty for now, as per request to remove specific display here
                end
            endcase
        end
    end

endmodule
