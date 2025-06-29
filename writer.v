//
// Filename: writer_final_robust.v
// Description: An ultra high-performance, pipelined data writer using a ping-pong buffer.
//              This FINAL ROBUST version uses consumer progress to trigger the producer (SRAM read),
//              creating a perfectly synchronized "Just-in-Time" data flow that prevents
//              buffer overrun while maintaining a zero-bubble pipeline.
//
`timescale 1ns / 1ps

module writer #(
    parameter MATRIX_SIZE               = 16,
    parameter TILE_SIZE                 = 16,
    parameter MAIN_MEM_ADDR_WIDTH       = 32,
    parameter MAIN_MEM_DATA_WIDTH_BITS  = 64,
    parameter BASE_ADDR_C               = 32'h30000000,
    parameter SRAM_C_WRITE_WIDTH        = 256,
    parameter PE_ACCUM_DATA_WIDTH       = 32
)(
    input wire                                  clk,
    input wire                                  rst_n,
    input wire                                  write_req,
    input wire [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]    i_tile_idx,
    input wire [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]    j_tile_idx,
    output logic                                write_busy,
    output logic                                write_done,
    output logic                                mem_req_valid,
    output logic [MAIN_MEM_DATA_WIDTH_BITS-1:0]   mem_req_wdata,
    output logic [MAIN_MEM_ADDR_WIDTH-1:0]        mem_req_addr,
    input wire                                  mem_req_ready,
    input wire                                  mem_write_done,
    output logic [$clog2( (TILE_SIZE*TILE_SIZE*PE_ACCUM_DATA_WIDTH)/SRAM_C_WRITE_WIDTH )-1:0]   sram_c_addr,
    input wire [SRAM_C_WRITE_WIDTH-1:0]                                                     sram_c_rdata
);
    
    //--------------------------------------------------------------------------
    // 内部参数定义
    //--------------------------------------------------------------------------
    localparam NUM_TILES_PER_DIM       = MATRIX_SIZE / TILE_SIZE;
    localparam C_TILE_BYTES            = (TILE_SIZE * TILE_SIZE * PE_ACCUM_DATA_WIDTH) / 8;
    localparam MEM_WRITES_PER_SRAM_READ = SRAM_C_WRITE_WIDTH / MAIN_MEM_DATA_WIDTH_BITS;
    localparam SRAM_READS_PER_TILE     = (TILE_SIZE * TILE_SIZE * PE_ACCUM_DATA_WIDTH) / SRAM_C_WRITE_WIDTH;

    typedef enum logic [0:0] { S_IDLE, S_STREAMING } state_t;

    //--------------------------------------------------------------------------
    // 内部信号和寄存器
    //--------------------------------------------------------------------------
    state_t current_state_q, next_state_d;

    // --- Ping-Pong Buffer and Control ---
    reg [SRAM_C_WRITE_WIDTH-1:0] data_buffer_ping_q;
    reg [SRAM_C_WRITE_WIDTH-1:0] data_buffer_pong_q;
    reg                          write_to_pong_q;
    reg                          read_from_pong_q;
    reg [1:0]                    buffer_valid_q;   // [1] for pong, [0] for ping

    // --- Pointers ---
    reg [$clog2(SRAM_READS_PER_TILE)-1:0] sram_read_ptr_q;
    reg [$clog2(MEM_WRITES_PER_SRAM_READ)-1:0] chunk_idx_q;
    reg [$clog2(SRAM_READS_PER_TILE)-1:0] active_sram_addr_q;

    // --- Control Signals ---
    wire sram_read_fire;
    reg sram_read_fire_s1_q;
    wire mem_write_fire;
    
    // --- Latched Inputs ---
    reg [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0] i_tile_idx_q, j_tile_idx_q;

    //--------------------------------------------------------------------------
    // 时序逻辑 (Sequential)
    //--------------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state_q  <= S_IDLE;
            sram_read_ptr_q  <= '0;
            chunk_idx_q      <= '0;
            active_sram_addr_q <= '0;
            write_to_pong_q  <= 1'b0;
            read_from_pong_q <= 1'b0;
            buffer_valid_q   <= 2'b00;
            i_tile_idx_q     <= '0;
            j_tile_idx_q     <= '0;
            sram_read_fire_s1_q <= 1'b0;
        end else begin
            current_state_q <= next_state_d;

            if (write_req) begin
                i_tile_idx_q <= i_tile_idx;
                j_tile_idx_q <= j_tile_idx;
            end

            sram_read_fire_s1_q <= sram_read_fire;

            // ******************************************************************
            // *** BUG FIX: 更新SRAM读指针 ***
            // *** 每次触发SRAM读取时，必须将读指针加一，为下一次读取做准备。
            // ******************************************************************
            if (sram_read_fire) begin
                sram_read_ptr_q <= sram_read_ptr_q + 1;
            end

            // --- Producer Logic (SRAM Read Data Capture) ---
            if (sram_read_fire_s1_q) begin // One cycle after read fires, data is valid
                if (!write_to_pong_q) begin
                    data_buffer_ping_q <= sram_c_rdata;
                    buffer_valid_q[0]  <= 1'b1;
                    $display("Time %0t: 读取SRAM数值 (Ping): %h", $time, sram_c_rdata); // 输出读取的数值
                end else begin
                    data_buffer_pong_q <= sram_c_rdata;
                    buffer_valid_q[1]  <= 1'b1;
                    $display("Time %0t: 读取SRAM数值 (Pong): %h", $time, sram_c_rdata); // 输出读取的数值
                end
                write_to_pong_q <= ~write_to_pong_q; // Flip for next write
            end

            // --- Consumer Logic (MEM Write) ---
            if (mem_write_fire) begin
                $display("Time %0t: 写回主存数值: %h (地址: %h)", $time, mem_req_wdata, mem_req_addr); // 输出写回的数值
                if (chunk_idx_q == MEM_WRITES_PER_SRAM_READ - 1) begin
                    chunk_idx_q <= '0;
                    if (!read_from_pong_q) begin
                        buffer_valid_q[0] <= 1'b0;
                    end else begin
                        buffer_valid_q[1] <= 1'b0;
                    end
                    read_from_pong_q <= ~read_from_pong_q;
                    active_sram_addr_q <= active_sram_addr_q + 1;
                end else begin
                    chunk_idx_q <= chunk_idx_q + 1;
                end
            end
            
            // --- Reset Logic ---
            // Note: This logic correctly overrides the increment on the last cycle.
            if (next_state_d == S_IDLE && current_state_q != S_IDLE) begin
                sram_read_ptr_q <= '0;
                chunk_idx_q     <= '0;
                active_sram_addr_q <= '0;
                write_to_pong_q <= 1'b0;
                read_from_pong_q <= 1'b0;
                buffer_valid_q   <= 2'b00;
                sram_read_fire_s1_q <= 1'b0;
            end
        end
    end

    //--------------------------------------------------------------------------
    // 组合逻辑 (Combinational)
    //--------------------------------------------------------------------------
    // The SRAM address is driven by the read pointer register
    assign sram_c_addr = sram_read_ptr_q;
    
    // *** CRITICAL FIX: The robust producer trigger logic ***
    // The producer fires only when the consumer is about to need the next block.
    // Trigger condition:
    // 1. We are in the streaming state.
    // 2. The consumer is starting to process a new 256-bit word (chunk_idx_q == 0)
    //    AND a write was successful in this cycle (mem_write_fire).
    //    This means a new buffer is just starting to be consumed.
    // 3. There are still more words to read from SRAM.
    // Exception: For the very first read, we trigger immediately when entering S_STREAMING.
    assign sram_read_fire = ((current_state_q == S_STREAMING && chunk_idx_q == 0 && mem_write_fire) || 
                            (current_state_q == S_IDLE && next_state_d == S_STREAMING)) &&
                            (sram_read_ptr_q < SRAM_READS_PER_TILE);

    assign mem_write_fire = mem_req_valid && mem_req_ready;

    // --- FSM Logic ---
    always_comb begin
        next_state_d = current_state_q;
        case (current_state_q)
            S_IDLE: begin
                if (write_req) begin
                    next_state_d = S_STREAMING;
                end
            end
            S_STREAMING: begin
                // Done when the last sram block has been fully consumed.
                if (active_sram_addr_q == SRAM_READS_PER_TILE - 1 &&
                    chunk_idx_q == MEM_WRITES_PER_SRAM_READ - 1 &&
                    mem_write_fire) begin
                    next_state_d = S_IDLE;
                end
            end
        endcase
    end

    // --- Output Logic ---
    assign write_busy = (current_state_q != S_IDLE);
    assign write_done = (current_state_q == S_STREAMING && next_state_d == S_IDLE);
    
    // Valid to write if the buffer we are reading from is valid
    assign mem_req_valid = (!read_from_pong_q && buffer_valid_q[0]) || (read_from_pong_q && buffer_valid_q[1]);
    
    logic [MAIN_MEM_ADDR_WIDTH-1:0] tile_base_addr;
    assign tile_base_addr = BASE_ADDR_C + (i_tile_idx_q * NUM_TILES_PER_DIM * C_TILE_BYTES) + 
                                         (j_tile_idx_q * C_TILE_BYTES);
    
    assign mem_req_addr = tile_base_addr + 
                          (active_sram_addr_q * (SRAM_C_WRITE_WIDTH/8)) +
                          (chunk_idx_q * (MAIN_MEM_DATA_WIDTH_BITS/8));
    
    // Select data from the correct buffer
    assign mem_req_wdata = (!read_from_pong_q ? data_buffer_ping_q : data_buffer_pong_q) >> (chunk_idx_q * MAIN_MEM_DATA_WIDTH_BITS);

endmodule