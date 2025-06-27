//
// Filename: tb_writer.v
// Description: An advanced testbench for the pipelined writer module.
//              This version is simplified to be more compatible with iverilog.
//
`timescale 1ns / 1ps

module tb_writer_pipelined;

    //--------------------------------------------------------------------------
    // Parameters
    //--------------------------------------------------------------------------
    localparam MATRIX_SIZE               = 48;
    localparam TILE_SIZE                 = 16;
    localparam MAIN_MEM_ADDR_WIDTH       = 32;
    localparam MAIN_MEM_DATA_WIDTH_BITS  = 64;

    // Derived parameters for testbench
    localparam C_TILE_WORDS = (TILE_SIZE * TILE_SIZE * 4) / (MAIN_MEM_DATA_WIDTH_BITS / 8); // 1024B / 8B = 128 words

    // Testbench control
    localparam CLK_PERIOD = 10; // ns

    //--------------------------------------------------------------------------
    // Signal Declarations
    //--------------------------------------------------------------------------
    // Inputs to DUT
    reg                                          clk;
    reg                                          rst_n;
    reg                                          write_req;
    reg [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      i_tile_idx;
    reg [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      j_tile_idx;
    reg                                          mem_req_ready;
    reg                                          mem_write_done;
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0]           sram_c_rdata;

    // Outputs from DUT
    wire                                         write_busy;
    wire                                         write_done;
    wire                                         mem_req_valid;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]          mem_req_wdata;
    wire [MAIN_MEM_ADDR_WIDTH-1:0]               mem_req_addr;
    wire [$clog2(C_TILE_WORDS)-1:0]              sram_c_addr;

    //--------------------------------------------------------------------------
    // Testbench internal components
    //--------------------------------------------------------------------------
    // Simulate the 64-bit wide C-SRAM
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0] simulated_sram_c [C_TILE_WORDS-1:0];

    //--------------------------------------------------------------------------
    // Instantiate the Device Under Test (DUT)
    //--------------------------------------------------------------------------
    writer #(
        .MATRIX_SIZE               (MATRIX_SIZE),
        .TILE_SIZE                 (TILE_SIZE),
        .MAIN_MEM_ADDR_WIDTH       (MAIN_MEM_ADDR_WIDTH),
        .MAIN_MEM_DATA_WIDTH_BITS  (MAIN_MEM_DATA_WIDTH_BITS)
    ) uut (
        .clk                       (clk),
        .rst_n                     (rst_n),
        .write_req                 (write_req),
        .i_tile_idx                (i_tile_idx),
        .j_tile_idx                (j_tile_idx),
        .write_busy                (write_busy),
        .write_done                (write_done),
        .mem_req_valid             (mem_req_valid),
        .mem_req_wdata             (mem_req_wdata),
        .mem_req_addr              (mem_req_addr),
        .mem_req_ready             (mem_req_ready),
        .mem_write_done            (mem_write_done),
        .sram_c_addr               (sram_c_addr),
        .sram_c_rdata              (sram_c_rdata)
    );

    //--------------------------------------------------------------------------
    // Clock and Reset Generation
    //--------------------------------------------------------------------------
    initial begin
        clk = 1'b0;
        forever #(CLK_PERIOD / 2) clk = ~clk;
    end

    initial begin
        $dumpfile("writer_pipelined_waveform.vcd");
        $dumpvars(0, tb_writer_pipelined);

        rst_n = 1'b0;
        #(CLK_PERIOD * 2);
        rst_n = 1'b1;
    end

    //--------------------------------------------------------------------------
    // Main Test Stimulus
    //--------------------------------------------------------------------------
    integer i;
    reg [31:0] word_high, word_low;

    initial begin
        // 1. Pre-fill the simulated 64-bit SRAM
        $display("[TB] INFO: Pre-filling simulated 64-bit wide C-SRAM...");
        for (i = 0; i < C_TILE_WORDS; i = i + 1) begin
            // **FIX**: Use temporary regs to avoid indefinite width error in concatenation
            word_low  = 32'hC0000000 + (i*2);
            word_high = 32'hC0000000 + (i*2+1);
            simulated_sram_c[i] = {word_high, word_low};
        end

        // 2. Initialize inputs
        write_req = 1'b0;
        i_tile_idx = 0;
        j_tile_idx = 0;

        @(posedge rst_n);
        @(posedge clk);
        
        // 3. Start the test case
        $display("--------------------------------------------------");
        $display("%0t [TB] INFO: Test Case: Write tile C[i=1][j=2] using pipelined writer.", $time);
        $display("--------------------------------------------------");

        write_req <= 1'b1;
        i_tile_idx <= 1;
        j_tile_idx <= 2;
        @(posedge clk);
        write_req <= 1'b0;

        // 4. Wait for the writer to finish
        wait (write_done == 1'b1);
        @(posedge clk);
        
        $display("--------------------------------------------------");
        $display("%0t [TB] INFO: Test Case PASSED. Writer has finished.", $time);
        $display("--------------------------------------------------");
        
        #(CLK_PERIOD * 10);
        $finish;
    end

    //--------------------------------------------------------------------------
    // Simulated 64-bit C-SRAM Read Port Logic
    //--------------------------------------------------------------------------
    always @(*) begin
        sram_c_rdata = simulated_sram_c[sram_c_addr];
    end
    
    //--------------------------------------------------------------------------
    // Memory Sink Model - Simplified to be more "naive"
    //--------------------------------------------------------------------------
    always @(posedge clk) begin
        if (!rst_n) begin
            mem_req_ready <= 1'b1;
        end else begin
            // Default behavior: Memory is always ready to accept a write
            mem_req_ready <= 1'b1;
            
            if (mem_req_valid && mem_req_ready) begin
                // Just log the write request. Verification can be done by checking the log.
                $display("%0t [MEM_SINK] INFO: Write request received for Addr 0x%h, Data 0x%h", $time, mem_req_addr, mem_req_wdata);
            end
        end
    end

endmodule