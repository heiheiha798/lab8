//
// Filename: sram_banked.v
// Description: A behavioral model of a banked SRAM for A and B tiles.
//              It consists of TILE_SIZE independent banks to allow for parallel
//              reads from the Data_Formatter, enabling high-throughput data skewing.
//
`timescale 1ns / 1ps

module sram_banked #(
    parameter IS_SRAM_A     = 1'b1, // 删除了 'bit' 关键字
    parameter NUM_BANKS         = 16, // Typically TILE_SIZE
    parameter BANK_DEPTH        = 16, // Typically TILE_SIZE
    parameter BANK_DATA_WIDTH   = 8,  // For SINT8 inputs (A and B)
    parameter BUS_DATA_WIDTH    = 64  // Width of the loader's write bus
)(
    input wire clk,
    
    // --- Write Port (from Loader) ---
    input wire                                  we,
    input wire [$clog2(NUM_BANKS*BANK_DEPTH*BANK_DATA_WIDTH/BUS_DATA_WIDTH)-1:0] waddr, // Word address from loader
    input wire [BUS_DATA_WIDTH-1:0]             wdata,

    // --- Parallel Read Port (from Data_Formatter) ---
    input wire [NUM_BANKS*$clog2(BANK_DEPTH)-1:0] raddr, // Concatenated addresses for all banks
    output reg [NUM_BANKS*BANK_DATA_WIDTH-1:0]   rdata  // Concatenated data from all banks
);

    localparam BANK_ADDR_WIDTH = $clog2(BANK_DEPTH);
    localparam BYTES_PER_BUS_WORD = BUS_DATA_WIDTH / 8;

    // Core memory structure: 16 banks, each 16 deep, 8 bits wide
    reg [BANK_DATA_WIDTH-1:0] memory [0:NUM_BANKS-1][0:BANK_DEPTH-1];

    // Declare integer variables outside the 'if' block, at the top of the always block.
    integer row_idx;
    integer bank_group_start;
    integer i; // Loop variable for the write loop
    integer j; // Loop variable for the read loop
    integer addr_bank0; // 用于存储bank 0的地址

    // --- Write Logic ---
    always @(posedge clk) begin
        if (we) begin
            row_idx = waddr / (NUM_BANKS / BYTES_PER_BUS_WORD);
            bank_group_start = (waddr % (NUM_BANKS / BYTES_PER_BUS_WORD)) * BYTES_PER_BUS_WORD;
            
            for (i = 0; i < BYTES_PER_BUS_WORD; i = i + 1) begin
                memory[bank_group_start + i][row_idx] <= wdata[i*BANK_DATA_WIDTH +: BANK_DATA_WIDTH];
                // 替换 $display 为输出写入后的数据
                $write("%0t [%s WRITE] waddr=%d, row_idx=%d, bank=%d, Written data=0x%h to memory[%d][%d]\n",
                    $time, IS_SRAM_A ? "SRAM-A" : "SRAM-B", waddr, row_idx, bank_group_start + i, 
                    wdata[i*BANK_DATA_WIDTH +: BANK_DATA_WIDTH], bank_group_start + i, row_idx);
            end
        end
    end

    // --- Parallel Read Logic ---
    always @(posedge clk) begin
        addr_bank0 = raddr[0*BANK_ADDR_WIDTH +: BANK_ADDR_WIDTH];
        for (j = 0; j < NUM_BANKS; j = j + 1) begin
            rdata[j*BANK_DATA_WIDTH +: BANK_DATA_WIDTH] <= memory[j][raddr[j*BANK_ADDR_WIDTH +: BANK_ADDR_WIDTH]];
        end
    end

endmodule
