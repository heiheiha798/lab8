// Filename: sram_c_accum.v
// Description: A behavioral model of the C-Accumulator SRAM with dual read ports.
//              MODIFIED: Initializes memory to zero on reset.
//512bit写 
`timescale 1ns / 1ps

module sram_c_accum #(
    parameter NUM_ROWS      = 16, // TILE_SIZE
    parameter ELEM_PER_ROW  = 16, // TILE_SIZE
    parameter ELEM_WIDTH    = 32, // PE_ACCUM_DATA_WIDTH
    parameter BUS_DATA_WIDTH = 64  // Width of the writer's read bus
)(
    input wire clk,
    input wire rst_n, // Added reset for initialization

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
    localparam WORDS_PER_ROW_B = ROW_WIDTH_BITS / BUS_DATA_WIDTH; // Renamed for clarity with Port B

    // Core memory: 16 rows, each 512 bits wide
    reg [ROW_WIDTH_BITS-1:0] memory [0:NUM_ROWS-1];

    // Variables for Read Port B logic, declared outside the always block
    integer row_idx_b;        // Renamed for clarity
    integer word_offset_in_row_b; // Renamed for clarity
    integer i; // For initialization loop

    // --- Write Logic ---
    always @(posedge clk) begin
        if (we) begin
            memory[waddr] <= wdata;
            // Add this display, only for waddr = 0
            if (waddr == 0) begin
                $display("[%0t] [SRAM_C_WRITE] Addr: %d, WData[0]=%d, WData[1]=%d, WData[2]=%d, WData[3]=%d",
                        $time, waddr,
                        wdata[0*ELEM_WIDTH +: ELEM_WIDTH],
                        wdata[1*ELEM_WIDTH +: ELEM_WIDTH],
                        wdata[2*ELEM_WIDTH +: ELEM_WIDTH],
                        wdata[3*ELEM_WIDTH +: ELEM_WIDTH]);
            end
        end
    end

    // --- Read Port A Logic (Synchronous Read) ---
    always @(posedge clk) begin
        // If rst_n is used to clear, read might output 0 during/after reset
        // For functional model, direct read is fine.
        if (!rst_n) begin
             rdata_A <= {(ELEM_PER_ROW*ELEM_WIDTH){1'b0}}; // Output 0 during reset
        end else begin
             rdata_A <= memory[raddr_A];
        end
    end
    
    // --- Read Port B Logic (Synchronous Read) ---
    always @(posedge clk) begin
        if (!rst_n) begin
            rdata_B <= {BUS_DATA_WIDTH{1'b0}}; // Output 0 during reset
        end else begin
            // Calculate row and word offset for Port B
            row_idx_b = raddr_B / WORDS_PER_ROW_B;
            word_offset_in_row_b = raddr_B % WORDS_PER_ROW_B;
            
            // Select the correct 64-bit slice from the wide 512-bit row
            if (row_idx_b < NUM_ROWS) begin // Bounds check
                 rdata_B <= memory[row_idx_b] >> (word_offset_in_row_b * BUS_DATA_WIDTH);
            end else begin
                 rdata_B <= {BUS_DATA_WIDTH{1'bx}}; // Or 0, if out of bounds
            end
        end
    end

    // --- Memory Initialization on Reset ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < NUM_ROWS; i = i + 1) begin
                memory[i] <= {(ELEM_PER_ROW*ELEM_WIDTH){1'b0}};
            end
        end
    end

endmodule
