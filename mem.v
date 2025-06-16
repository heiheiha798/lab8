// ram.v
`timescale 1ns / 1ps

`define BASE_ADDR_C_FOR_RAM_DEBUG 256

module ram #
(
    parameter DATA_WIDTH = 64,
    parameter ADDR_WIDTH = 17
)
(
    input wire clk,
    input wire [ADDR_WIDTH-1:0] address, // Input port
    input wire [DATA_WIDTH-1:0] d,
    output reg [DATA_WIDTH-1:0] q,
    input wire cs,
    input wire web
);

    localparam RAM_DEPTH = 1 << ADDR_WIDTH;
    reg [DATA_WIDTH-1:0] mem [0:RAM_DEPTH-1];

    // Reg to hold the sampled address at the beginning of the clocked block
    reg [ADDR_WIDTH-1:0] address_clk_sample;

    initial begin
        q = {DATA_WIDTH{1'b0}};
        address_clk_sample = {ADDR_WIDTH{1'bx}}; // Initialize to X
    end

    // Write Logic
    always @(posedge clk) begin
        // Sample the address input at the very beginning of the clocked event
        address_clk_sample = address;

        // $display("@%0t [RAM_INPUT_TRACE_CLK] Addr_in_PORT:%h (SampledAs:%h), CS_in_PORT:%b, WEB_in_PORT:%b, D_in_PORT:%h",
        //          $time, address, address_clk_sample, cs, web, d);

        if (cs && !web) begin
            // Use the sampled address for memory operation
            mem[address_clk_sample] <= d;

            // Monitor for write attempt to address 0x100 using the sampled address
            // if (address_clk_sample == `BASE_ADDR_C_FOR_RAM_DEBUG) begin
            //     $display("@%0t [RAM_MONITOR_WRITE_0x100] Addr_SAMPLED:%h, Data_in:%h, CS_in:%b, WEB_in:%b",
            //              $time, address_clk_sample, d, cs, web);
            // end

            // Strobe for writes within the C area, using the sampled address
            // if (address_clk_sample >= `BASE_ADDR_C_FOR_RAM_DEBUG && address_clk_sample < (`BASE_ADDR_C_FOR_RAM_DEBUG + 256)) begin
            //      $strobe("@%0t [RAM_WRITE_C_AREA_SAMPLED] Addr_SAMPLED: %h (%0d), Data_to_write: %h, cs:%b, web:%b",
            //              $time, address_clk_sample, address_clk_sample, d, cs, web);
            // end
        end
    end

    // Read Logic
    always @(posedge clk) begin
        // For consistency, if reads also need to be robust to this, sample address here too.
        // However, reads are often less timing critical in this specific way for simple RAMs.
        // For now, keeping it simple, assuming 'address' for read is fine.
        if (cs && web) begin
            q <= mem[address];
        end
    end

endmodule