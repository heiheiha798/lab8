//
// Filename: tb_loader.v
// Description: Testbench for the high-performance pipelined loader module.
//              Designed for use with Icarus Verilog (iverilog) and vvp.
//
`timescale 1ns / 1ps

module tb_loader;

    //--------------------------------------------------------------------------
    // Parameters
    //--------------------------------------------------------------------------
    localparam MATRIX_SIZE               = 48;
    localparam TILE_SIZE                 = 16;
    localparam INPUT_DATA_WIDTH          = 8; // Not directly used here, but good for context
    localparam MAIN_MEM_ADDR_WIDTH       = 32;
    localparam MAIN_MEM_DATA_WIDTH_BITS  = 64;

    // Testbench control
    localparam CLK_PERIOD = 10; // ns

    //--------------------------------------------------------------------------
    // Signal Declarations
    //--------------------------------------------------------------------------
    // Inputs to DUT
    reg                                          clk;
    reg                                          rst_n;
    reg                                          load_req;
    reg [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      i_tile_idx;
    reg [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      j_tile_idx;
    reg [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      k_tile_idx;
    reg                                          load_to_ping;

    // Memory interface signals (driven by testbench memory model)
    reg                                          mem_req_ready;
    reg                                          mem_resp_valid;
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0]           mem_resp_rdata;

    // Outputs from DUT
    wire                                         load_busy;
    wire                                         load_done;
    wire                                         mem_req_valid;
    wire [MAIN_MEM_ADDR_WIDTH-1:0]               mem_req_addr;

    // SRAM interfaces (monitor these signals)
    wire [$clog2(TILE_SIZE*TILE_SIZE*8/MAIN_MEM_DATA_WIDTH_BITS)-1:0] sram_a_addr;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]                              sram_a_wdata;
    wire                                                             sram_a_we;

    wire [$clog2(TILE_SIZE*TILE_SIZE*8/MAIN_MEM_DATA_WIDTH_BITS)-1:0] sram_b_addr;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]                              sram_b_wdata;
    wire                                                             sram_b_we;


    //--------------------------------------------------------------------------
    // Instantiate the Device Under Test (DUT)
    //--------------------------------------------------------------------------
    // Ensure you have the pipelined loader saved as 'loader.v' in the same directory
    loader #(
        .MATRIX_SIZE               (MATRIX_SIZE),
        .TILE_SIZE                 (TILE_SIZE),
        .MAIN_MEM_ADDR_WIDTH       (MAIN_MEM_ADDR_WIDTH),
        .MAIN_MEM_DATA_WIDTH_BITS  (MAIN_MEM_DATA_WIDTH_BITS)
    ) uut (
        .clk                       (clk),
        .rst_n                     (rst_n),
        .load_req                  (load_req),
        .i_tile_idx                (i_tile_idx),
        .j_tile_idx                (j_tile_idx),
        .k_tile_idx                (k_tile_idx),
        .load_to_ping              (load_to_ping),
        .load_busy                 (load_busy),
        .load_done                 (load_done),
        .mem_req_valid             (mem_req_valid),
        .mem_req_ready             (mem_req_ready),
        .mem_resp_valid            (mem_resp_valid),
        .mem_resp_rdata            (mem_resp_rdata),
        .mem_req_addr              (mem_req_addr),
        .sram_a_addr               (sram_a_addr),
        .sram_a_wdata              (sram_a_wdata),
        .sram_a_we                 (sram_a_we),
        .sram_b_addr               (sram_b_addr),
        .sram_b_wdata              (sram_b_wdata),
        .sram_b_we                 (sram_b_we)
    );

    //--------------------------------------------------------------------------
    // Clock and Reset Generation
    //--------------------------------------------------------------------------
    initial begin
        clk = 1'b0;
        forever #(CLK_PERIOD / 2) clk = ~clk;
    end

    initial begin
        // Dump waves for debugging with gtkwave
        $dumpfile("loader_waveform.vcd");
        $dumpvars(0, tb_loader);

        // Generate reset pulse
        rst_n = 1'b0;
        #(CLK_PERIOD * 2);
        rst_n = 1'b1;
    end

    //--------------------------------------------------------------------------
    // Main Test Stimulus
    //--------------------------------------------------------------------------
    initial begin
        // Initialize all inputs
        load_req = 1'b0;
        i_tile_idx = 0;
        j_tile_idx = 0;
        k_tile_idx = 0;
        load_to_ping = 1'b0;

        // Wait for reset to complete
        @(posedge rst_n);
        @(posedge clk);
        
        $display("--------------------------------------------------");
        $display("%0t [TB] INFO: Test Case: Load tiles for i=1, j=2, k=0 to PING", $time);
        $display("--------------------------------------------------");

        // Apply a load request
        load_req <= 1'b1;
        i_tile_idx <= 1;
        j_tile_idx <= 2;
        k_tile_idx <= 0;
        load_to_ping <= 1'b1; // Load to PING
        @(posedge clk);
        load_req <= 1'b0; // De-assert request after one cycle

        // Wait until the loader is done
        wait (load_done == 1'b1);
        @(posedge clk);
        
        $display("--------------------------------------------------");
        $display("%0t [TB] INFO: Test Case PASSED. Loader has finished.", $time);
        $display("--------------------------------------------------");
        
        #(CLK_PERIOD * 10);
        $finish;
    end
    
    //--------------------------------------------------------------------------
    // Memory Model - Simulates main memory with a fixed latency
    //--------------------------------------------------------------------------
    always @(posedge clk) begin
        if (!rst_n) begin
            mem_req_ready <= 1'b1; // Memory is ready after reset
            mem_resp_valid <= 1'b0;
            mem_resp_rdata <= 0;
        end else begin
            // Default behavior
            mem_resp_valid <= 1'b0;
            mem_req_ready <= 1'b1; // Assume memory is always ready for a new request
            
            if (mem_req_valid && mem_req_ready) begin
                // Simulate memory access latency (e.g., 3 cycles)
                repeat (3) @(posedge clk);
                
                // Prepare and send response
                mem_resp_valid <= 1'b1;
                // Return some fake data, e.g., part of the address, for easy debugging
                mem_resp_rdata <= {32'hBA5EBA11, uut.mem_req_addr};
                
                @(posedge clk);
                // Response is valid for one cycle only
                mem_resp_valid <= 1'b0;
            end
        end
    end

    //--------------------------------------------------------------------------
    // SRAM Write Monitor - Concurrently checks for SRAM write activity
    //--------------------------------------------------------------------------
    initial begin // 第一个SRAM A监测进程
        forever @(posedge clk) begin
            if (sram_a_we) begin
                $display("%0t [TB] MONITOR: SRAM A write detected! Addr: %0d, Data: 0x%h", $time, sram_a_addr, sram_a_wdata);
            end
        end
    end

    initial begin // 第二个SRAM B监测进程
        forever @(posedge clk) begin
            if (sram_b_we) begin
                $display("%0t [TB] MONITOR: SRAM B write detected! Addr: %0d, Data: 0x%h", $time, sram_b_addr, sram_b_wdata);
            end
        end
    end

endmodule