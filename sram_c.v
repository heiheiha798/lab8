//
// Filename: sram_c.v
// Description: A generic, single-port (1R1W) SRAM model for the C-tile buffer.
// REVISED FOR PARAMETRIC USE:
// - Parameters are now generic (NUM_ENTRIES, ENTRY_WIDTH) to be set by the instantiating module.
// - All port widths and internal logic are derived from these generic parameters.
//
`timescale 1ns / 1ps

module sram_c #(
    // Generic parameters with default values for typical use case
    parameter NUM_ENTRIES    = 16,  // Default to 16 entries (e.g., for 512-bit width)
    parameter ENTRY_WIDTH    = 256, // Default to 256 bits
    parameter BUS_DATA_WIDTH = 64   // Width of the reader's bus (e.g., Writer)
)(
    input wire clk,
    input wire rst_n,

    // --- Write Port (from sa_enhanced) ---
    input wire                                  we,
    input wire [$clog2(NUM_ENTRIES)-1:0]        waddr, // Address is now generic
    input wire [ENTRY_WIDTH-1:0]                wdata, // Width is now generic

    // --- Read Port (for Writer) ---
    input wire [$clog2(NUM_ENTRIES * ENTRY_WIDTH / BUS_DATA_WIDTH)-1:0] raddr,
    output reg [BUS_DATA_WIDTH-1:0]                                      rdata
);

    // --- Core Memory Structure ---
    reg [ENTRY_WIDTH-1:0] memory [0:NUM_ENTRIES-1];

    // --- Internal variables for read logic ---
    localparam WORDS_PER_ENTRY = ENTRY_WIDTH / BUS_DATA_WIDTH;
    integer entry_idx;
    integer word_offset;
    integer i;

    // --- Write Logic (Synchronous) ---
    always @(posedge clk) begin
        if (we) begin
            memory[waddr] <= wdata;
        end
    end

    // --- Display Written Data ---
    always @(posedge clk) begin
        if (we) begin
            $display("%0t Write Data: waddr = %d, wdata = %h", $time, waddr, wdata);
        end
    end

    // --- Read Logic (Synchronous) ---
    always @(posedge clk) begin
        if (!rst_n) begin
            rdata <= {BUS_DATA_WIDTH{1'b0}};
        end else begin
            // Calculate which entry and which slice to read
            entry_idx = raddr / WORDS_PER_ENTRY;
            word_offset = raddr % WORDS_PER_ENTRY;
            
            // Perform read, with a basic bounds check
            if (entry_idx < NUM_ENTRIES) begin
                 rdata <= memory[entry_idx] >> (word_offset * BUS_DATA_WIDTH);
            end else begin
                 rdata <= {BUS_DATA_WIDTH{1'bx}}; // Return 'x' if address is out of bounds
            end
        end
    end

    // --- Memory Initialization on Reset ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < NUM_ENTRIES; i = i + 1) begin
                memory[i] <= {ENTRY_WIDTH{1'b0}};
            end
        end
    end

endmodule
