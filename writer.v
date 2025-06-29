//
// Filename: writer_debug_fixed.v
// Description: An ultra high-performance, pipelined data writer.
//              This version is REVISED to support "zig-zag" (two-pass, column-first)
//              half-width SRAM C read, disassemble data, and stream to main memory.
//              It maintains a pipelined throughput by carefully managing internal buffers
//              and state transitions.
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
    parameter BASE_ADDR_C               = 32'h30000000,
    
    // NEW: From SA's configuration, to understand SRAM C structure
    parameter SRAM_C_WRITE_WIDTH        = 256, // For 16x16 matrix, 32-bit accum, this means 8 PE results (8 * 32 = 256)
    parameter PE_ACCUM_DATA_WIDTH       = 32 // Needed for internal calculation of data size
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
    input wire                                  mem_write_done, // Assuming this means the last outstanding write has completed

    // SRAM 读取接口
    // SRAM C的地址线宽度现在取决于SRAM_C_WRITE_WIDTH和总数据量 (TILE_SIZE * TILE_SIZE * PE_ACCUM_DATA_WIDTH)
    // 其深度是 (TILE_SIZE * TILE_SIZE * PE_ACCUM_DATA_WIDTH) / SRAM_C_WRITE_WIDTH
    output reg [$clog2( (TILE_SIZE*TILE_SIZE*PE_ACCUM_DATA_WIDTH)/SRAM_C_WRITE_WIDTH )-1:0]   sram_c_addr,
    input wire [SRAM_C_WRITE_WIDTH-1:0]                                                     sram_c_rdata // MODIFIED: SRAM C read data width
);
    
    //--------------------------------------------------------------------------
    // 内部参数定义
    //--------------------------------------------------------------------------
    localparam NUM_TILES_PER_DIM       = MATRIX_SIZE / TILE_SIZE;
    localparam TILE_ACCUM_BITS         = TILE_SIZE * TILE_SIZE * PE_ACCUM_DATA_WIDTH;
    localparam C_TILE_BYTES            = TILE_ACCUM_BITS / 8; // Total bytes for one C tile

    // Number of main memory writes needed for one wide SRAM C read
    // This assumes SRAM_C_WRITE_WIDTH is a multiple of MAIN_MEM_DATA_WIDTH_BITS
    localparam MEM_WRITES_PER_SRAM_READ = SRAM_C_WRITE_WIDTH / MAIN_MEM_DATA_WIDTH_BITS;

    // FSM States
    typedef enum logic [1:0] { // 2 bits is enough for 3 states
        S_IDLE,
        S_READ_FIRST_HALVES,    // Read and disassemble all first halves
        S_READ_SECOND_HALVES,   // Read and disassemble all second halves
        S_PIPELINE_DRAIN        // Wait for the last memory write to complete
    } state_t;

    //--------------------------------------------------------------------------
    // 内部寄存器定义
    //--------------------------------------------------------------------------
    state_t current_state_q, next_state_d; // _q for registered, _d for combinational next

    // Tile indices for the current write operation
    reg [$clog2(NUM_TILES_PER_DIM)-1:0] i_tile_idx_q, j_tile_idx_q; 
    
    // Pointer for current SRAM C row being read (0 to TILE_SIZE-1)
    reg [$clog2(TILE_SIZE)-1:0] sram_row_idx_q, sram_row_idx_d; 

    // Counter for disassembling a wide SRAM word into narrow main memory words
    reg [$clog2(MEM_WRITES_PER_SRAM_READ)-1:0] disassemble_ptr_q, disassemble_ptr_d;

    // A wide buffer to hold one full read from SRAM C. This is a pipeline stage 1 output.
    reg [SRAM_C_WRITE_WIDTH-1:0] sram_data_buffer_q;
    
    // Main memory write address (byte offset within the C matrix)
    reg [MAIN_MEM_ADDR_WIDTH-1:0] mem_current_byte_addr_q, mem_current_byte_addr_d;
    
    // Pipeline stage for main memory request
    reg mem_req_valid_s1_q; // Staging the mem_req_valid signal
    reg [MAIN_MEM_ADDR_WIDTH-1:0] mem_req_addr_s1_q; // Staging the address
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0] mem_req_wdata_s1_q; // Staging the data

    // Control signal to indicate if the main memory pipeline is not stalled
    wire mem_pipeline_not_stalled;
    assign mem_pipeline_not_stalled = (mem_req_ready || !mem_req_valid_s1_q); // If mem_req_valid_s1_q is false, it's not stalled. If true, it depends on mem_req_ready.

    //--------------------------------------------------------------------------
    // FSM State and Pointer Sequential Logic
    //--------------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state_q <= S_IDLE;
            sram_row_idx_q <= 0;
            disassemble_ptr_q <= 0;
            mem_current_byte_addr_q <= '0;
            i_tile_idx_q <= 0;
            j_tile_idx_q <= 0;
            sram_data_buffer_q <= '0; // Initialize wide buffer
            
            // Initialize pipeline registers
            mem_req_valid_s1_q <= 1'b0;
            mem_req_addr_s1_q <= '0;
            mem_req_wdata_s1_q <= '0;
        end else begin
            // Stall logic: only update state and pointers if main memory pipeline is not stalled
            if (mem_pipeline_not_stalled) begin
                current_state_q <= next_state_d;
                sram_row_idx_q <= sram_row_idx_d;
                disassemble_ptr_q <= disassemble_ptr_d;
                mem_current_byte_addr_q <= mem_current_byte_addr_d;
            end
            
            // Latch tile indices (happens once per tile operation)
            if (current_state_q == S_IDLE && write_req) begin
                i_tile_idx_q <= i_tile_idx;
                j_tile_idx_q <= j_tile_idx;
            end

            // Latch the wide data from SRAM C (this is the Stage 1 of the pipeline).
            // It happens ONE cycle AFTER the read address is issued by sram_c_addr_d.
            // Data is latched when starting a new disassembly process (disassemble_ptr_d == 0)
            // and pipeline is not stalled.
            if ((current_state_q == S_READ_FIRST_HALVES || current_state_q == S_READ_SECOND_HALVES) &&
                mem_pipeline_not_stalled && disassemble_ptr_d == 0) begin
                sram_data_buffer_q <= sram_c_rdata;
            end

            // Pipeline Stage 1 -> Stage 2 (Main Memory Request Generation)
            // mem_req_valid_s1_q and mem_req_addr_s1_q are updated always,
            // but their *values* depend on the `mem_pipeline_not_stalled` condition
            // from the previous cycle.
            if (current_state_q == S_READ_FIRST_HALVES || current_state_q == S_READ_SECOND_HALVES) begin
                // mem_req_valid_s1_q becomes high when `disassemble_ptr_q` points to the first chunk
                // of a new main memory word.
                mem_req_valid_s1_q <= 1'b1; // Always valid during streaming, unless stalled or finished
                mem_req_addr_s1_q  <= BASE_ADDR_C + mem_current_byte_addr_q;
                // Select the correct chunk from the buffer for the memory write
                mem_req_wdata_s1_q <= sram_data_buffer_q >> (disassemble_ptr_q * MAIN_MEM_DATA_WIDTH_BITS);
            end else begin
                mem_req_valid_s1_q <= 1'b0; // Not sending memory requests in IDLE or DRAIN states
            end

            // Debug display: log successful writes
            if (mem_req_valid && mem_req_ready) begin
                $display("%0t Writer: Wrote 0x%H to MEM ADDR 0x%H (Tile [%0d,%0d], Word offset %0d)", 
                         $time, mem_req_wdata, mem_req_addr, i_tile_idx_q, j_tile_idx_q, 
                         (mem_current_byte_addr_q / (MAIN_MEM_DATA_WIDTH_BITS/8)));
            end
        end
    end

    //--------------------------------------------------------------------------
    // Combinational Logic for FSM and Outputs
    //--------------------------------------------------------------------------
    always_comb begin
        // Default assignments (prevent latches)
        next_state_d = current_state_q;
        write_busy   = (current_state_q != S_IDLE);
        write_done   = 1'b0;
        
        // Main Memory Interface Outputs (Stage 2 of pipeline)
        mem_req_valid = mem_req_valid_s1_q; 
        mem_req_wdata = mem_req_wdata_s1_q;
        mem_req_addr  = mem_req_addr_s1_q;

        // Default pointer updates (hold current values if stalled)
        sram_row_idx_d        = sram_row_idx_q;
        disassemble_ptr_d     = disassemble_ptr_q;
        mem_current_byte_addr_d = mem_current_byte_addr_q;

        // SRAM C Address Generation (Stage 0 of pipeline)
        case (current_state_q)
            S_READ_FIRST_HALVES:  sram_c_addr = {sram_row_idx_q, 1'b0}; // Address for first half of the row
            S_READ_SECOND_HALVES: sram_c_addr = {sram_row_idx_q, 1'b1}; // Address for second half of the row
            default:              sram_c_addr = '0; // No SRAM C reads in IDLE or DRAIN
        endcase

        // FSM State Transitions and Logic
        case (current_state_q)
            S_IDLE: begin
                if (write_req) begin
                    next_state_d = S_READ_FIRST_HALVES;
                    sram_row_idx_d = 0;         // Start from row 0
                    disassemble_ptr_d = 0;      // Start disassembling from the first chunk
                    // Calculate the starting byte address for the current tile
                    mem_current_byte_addr_d = (i_tile_idx * NUM_TILES_PER_DIM * C_TILE_BYTES) + 
                                              (j_tile_idx * C_TILE_BYTES);
                end
            end

            S_READ_FIRST_HALVES: begin
                // This state manages reading all first halves and writing them to memory
                // It advances the disassemble_ptr and mem_current_byte_addr every cycle (if not stalled)
                // It advances sram_row_idx every MEM_WRITES_PER_SRAM_READ cycles (when disassemble_ptr wraps)
                disassemble_ptr_d = disassemble_ptr_q + 1;
                mem_current_byte_addr_d = mem_current_byte_addr_q + (MAIN_MEM_DATA_WIDTH_BITS / 8);

                if (disassemble_ptr_q == MEM_WRITES_PER_SRAM_READ - 1) begin
                    // Just finished disassembling and sending the last chunk of the current SRAM word
                    disassemble_ptr_d = 0; // Reset for the next SRAM word
                    sram_row_idx_d = sram_row_idx_q + 1; // Advance to the next row's first half

                    if (sram_row_idx_q == TILE_SIZE - 1) begin
                        // All first halves (Row 0 through TILE_SIZE-1) have been processed
                        next_state_d = S_READ_SECOND_HALVES;
                        sram_row_idx_d = 0; // Reset row index for the second pass
                        // IMPORTANT: mem_current_byte_addr_d continues from where it left off,
                        // as the second halves logically follow the first halves in main memory.
                        // No need to reset mem_current_byte_addr_d here.
                    end
                end
            end

            S_READ_SECOND_HALVES: begin
                // This state manages reading all second halves and writing them to memory
                disassemble_ptr_d = disassemble_ptr_q + 1;
                mem_current_byte_addr_d = mem_current_byte_addr_q + (MAIN_MEM_DATA_WIDTH_BITS / 8);

                if (disassemble_ptr_q == MEM_WRITES_PER_SRAM_READ - 1) begin
                    // Just finished disassembling and sending the last chunk of the current SRAM word
                    disassemble_ptr_d = 0; // Reset for the next SRAM word
                    sram_row_idx_d = sram_row_idx_q + 1; // Advance to the next row's second half

                    if (sram_row_idx_q == TILE_SIZE - 1) begin
                        // All second halves (Row 0 through TILE_SIZE-1) have been processed.
                        // All main memory writes for this tile have been initiated.
                        next_state_d = S_PIPELINE_DRAIN;
                    end
                end
            end
            
            S_PIPELINE_DRAIN: begin
                // Wait for the main memory to signal that the last write has completed.
                // The `mem_write_done` signal usually comes from an external memory controller.
                if (mem_write_done) begin
                    write_done = 1'b1; // Signal completion to the top controller
                    next_state_d = S_IDLE;
                end
            end

            default: next_state_d = S_IDLE; // Should not happen
        endcase
    end

endmodule