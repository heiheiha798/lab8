//
// Filename: sram_c_accum.v
// Description: A behavioral model of the C-Accumulator SRAM with dual read ports.
//              Port A serves the Compute Controller (reading full rows).
//              Port B serves the Writer (reading 64-bit words).
//
`timescale 1ns / 1ps

module sram_c_accum #(
    parameter NUM_ROWS      = 16, // TILE_SIZE
    parameter ELEM_PER_ROW  = 16, // TILE_SIZE
    parameter ELEM_WIDTH    = 32, // PE_ACCUM_DATA_WIDTH
    parameter BUS_DATA_WIDTH = 64  // Width of the writer's read bus
)(
    input wire clk,

    // --- Write Port (from Compute Controller) ---
    input wire                                  we,
    input wire [$clog2(NUM_ROWS)-1:0]           waddr, // Row address
    input wire [ELEM_PER_ROW*ELEM_WIDTH-1:0]    wdata, // A full row of result data

    // --- Read Port A (for Compute Controller, reads full rows) ---
    input wire [$clog2(NUM_ROWS)-1:0]           raddr_A,
    output reg [ELEM_PER_ROW*ELEM_WIDTH-1:0]    rdata_A,

    // --- Read Port B (for Writer, reads 64-bit words) ---
    input wire [$clog2(NUM_ROWS*ELEM_PER_ROW*ELEM_WIDTH/BUS_DATA_WIDTH)-1:0] raddr_B,
    output reg [BUS_DATA_WIDTH-1:0]                                          rdata_B
);

    localparam ROW_WIDTH_BITS = ELEM_PER_ROW * ELEM_WIDTH;
    localparam WORDS_PER_ROW = ROW_WIDTH_BITS / BUS_DATA_WIDTH;

    // Core memory: 16 rows, each 512 bits wide
    reg [ROW_WIDTH_BITS-1:0] memory [0:NUM_ROWS-1];

    // Variables for Read Port B logic, declared outside the always block
    integer row_idx;
    integer word_offset_in_row;

    // --- Write Logic (Unchanged) ---
    always @(posedge clk) begin
        if (we) begin
            memory[waddr] <= wdata;
        end
    end

    // --- Read Port A Logic (Synchronous Read) ---
    always @(posedge clk) begin
        rdata_A <= memory[raddr_A];
    end
    
    // --- Read Port B Logic (Synchronous Read) ---
    always @(posedge clk) begin
        // Calculate row and word offset
        row_idx = raddr_B / WORDS_PER_ROW;
        word_offset_in_row = raddr_B % WORDS_PER_ROW;
        
        // Select the correct 64-bit slice from the wide 512-bit row
        rdata_B <= memory[row_idx] >> (word_offset_in_row * BUS_DATA_WIDTH);
    end

endmodule