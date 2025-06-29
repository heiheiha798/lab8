//
// Filename: sram_c_fixed.v
// Description: A generic, single-port (1R1W) SRAM model for the C-tile buffer.
// REVISED FOR SYMMETRIC PORTS:
// - The read port now has the same width as the write port (ENTRY_WIDTH).
// - The read address (raddr) and write address (waddr) now have the same width.
// - This models a true 1R1W SRAM, removing the complex and incorrect "wide-write, narrow-read" logic.
//
`timescale 1ns / 1ps

module sram_c #(
    // Generic parameters with default values
    parameter NUM_ENTRIES    = 32,
    parameter ENTRY_WIDTH    = 256
    // BUS_DATA_WIDTH is no longer needed as the read port is now ENTRY_WIDTH
)(
    input wire clk,
    input wire rst_n,

    // --- Write Port (from sa_enhanced) ---
    input wire                                  we,
    input wire [$clog2(NUM_ENTRIES)-1:0]        waddr,
    input wire [ENTRY_WIDTH-1:0]                wdata,

    // --- Read Port (for Writer) ---
    // *** BUG FIX: raddr now has the same width as waddr ***
    input wire [$clog2(NUM_ENTRIES)-1:0]        raddr,
    // *** BUG FIX: rdata now has the same width as wdata ***
    output reg [ENTRY_WIDTH-1:0]                rdata
);

    // --- Core Memory Structure ---
    reg [ENTRY_WIDTH-1:0] memory [0:NUM_ENTRIES-1];
    integer i;

    // --- Write Logic (Synchronous) ---
    always @(posedge clk) begin
        if (we) begin
            memory[waddr] <= wdata;
        end
    end

    // --- Read Logic (Synchronous) ---
    // Simple synchronous read: data is available on the next cycle after address is presented.
    always @(posedge clk) begin
        if (!rst_n) begin
            rdata <= {ENTRY_WIDTH{1'b0}};
        end else begin
            // Perform read, with a basic bounds check
            if (raddr < NUM_ENTRIES) begin
                 rdata <= memory[raddr];
            end else begin
                 rdata <= {ENTRY_WIDTH{1'bx}}; // Return 'x' if address is out of bounds
            end
        end
    end
    
    // --- Display Logic (Optional, but useful for debug) ---
    always @(posedge clk) begin
        if (we) begin
            $display("%0t [SRAM_C] Write: waddr = %d, wdata = %h", $time, waddr, wdata);
        end
    end

    // The read display in the original was a bit confusing as it showed the *previous* cycle's data.
    // A better way to display reads is from the reader's perspective (like in writer.v).
    // If you want to keep a display here, it should be clear about the timing.
    // Example:
    // reg [$clog2(NUM_ENTRIES)-1:0] raddr_q;
    // always @(posedge clk) raddr_q <= raddr;
    // always @(posedge clk) $display("%0t [SRAM_C] Read: raddr=%d (from prev cycle), rdata driven=%h", $time, raddr_q, rdata);


    // --- Memory Initialization on Reset ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < NUM_ENTRIES; i = i + 1) begin
                memory[i] <= {ENTRY_WIDTH{1'b0}};
            end
        end
    end

    always @(posedge clk) begin
            $display("%0t [SRAM_C] READ: raddr = %d, rdata = %h", $time, raddr, rdata);
    end

endmodule