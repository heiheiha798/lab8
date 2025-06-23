//
// Filename: sram_banked.v
// Description: A behavioral model of a banked SRAM for A and B tiles.
//              It consists of TILE_SIZE independent banks to allow for parallel
//              reads from the Data_Formatter, enabling high-throughput data skewing.
//
`timescale 1ns / 1ps

module sram_banked #(
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
    // In plain Verilog, 'integer' variables declared within an 'always' block
    // cannot be initialized at declaration.
    integer row_idx;
    integer bank_group_start;
    integer i; // Loop variable for the write loop
    integer j; // Loop variable for the read loop

    // --- Write Logic ---
    // The loader writes linearly. We distribute the 64-bit bus data across 8 banks at a time.
    always @(posedge clk) begin
        if (we) begin
            // Calculate which row and which group of 8 banks to write to
            // Assignments moved to separate lines after declaration
            row_idx = waddr / (NUM_BANKS / BYTES_PER_BUS_WORD);
            bank_group_start = (waddr % (NUM_BANKS / BYTES_PER_BUS_WORD)) * BYTES_PER_BUS_WORD;
            
            // Loop variable 'i' is declared above
            for (i = 0; i < BYTES_PER_BUS_WORD; i = i + 1) begin
                memory[bank_group_start + i][row_idx] <= wdata[i*BANK_DATA_WIDTH +: BANK_DATA_WIDTH];
            end
        end
    end

    // --- Parallel Read Logic ---
    // Reads from all banks simultaneously based on the concatenated address vector.
    // This is a synchronous read, output is available on the next cycle.
    // Directly use the sliced 'raddr' for memory access.
    always @(posedge clk) begin
        // Loop variable 'j' is declared above
        for (j = 0; j < NUM_BANKS; j = j + 1) begin
            rdata[j*BANK_DATA_WIDTH +: BANK_DATA_WIDTH] <= memory[j][raddr[j*BANK_ADDR_WIDTH +: BANK_ADDR_WIDTH]];
        end
    end

endmodule
