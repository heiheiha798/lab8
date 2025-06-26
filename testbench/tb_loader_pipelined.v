//
// Filename: tb_loader_pipelined.v
// Description: An advanced testbench for the pipelined loader module.
//              It features a NON-BLOCKING, pipelined memory model to test
//              the DUT under high-performance conditions.
//              Integrated with sram_banked modules for A and B tiles.
//
`timescale 1ns / 1ps

module tb_loader_pipelined;

    //--------------------------------------------------------------------------
    // Parameters
    //--------------------------------------------------------------------------
    localparam MATRIX_SIZE               = 48;
    localparam TILE_SIZE                 = 16;
    localparam MAIN_MEM_ADDR_WIDTH       = 32;
    localparam MAIN_MEM_DATA_WIDTH_BITS  = 64;

    // SRAM_banked parameters (must match sram_banked.v defaults or adjusted as needed)
    localparam SRAM_NUM_BANKS           = 16;
    localparam SRAM_BANK_DEPTH          = 16;
    localparam SRAM_BANK_DATA_WIDTH     = 8;
    localparam SRAM_BUS_DATA_WIDTH      = 64; // Matches MAIN_MEM_DATA_WIDTH_BITS

    // Testbench control
    localparam CLK_PERIOD    = 10; // ns
    localparam MEM_LATENCY   = 3;  // Memory latency in clock cycles

    //--------------------------------------------------------------------------
    // Signal Declarations
    //--------------------------------------------------------------------------
    // Inputs to DUT (Loader)
    reg                                          clk;
    reg                                          rst_n;
    reg                                          load_req;
    reg [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      i_tile_idx;
    reg [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      j_tile_idx;
    reg [$clog2(MATRIX_SIZE/TILE_SIZE)-1:0]      k_tile_idx;
    reg                                          load_to_ping;

    // Memory interface signals (connected to Loader)
    reg                                          mem_req_ready;
    reg                                          mem_resp_valid;
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0]           mem_resp_rdata;

    // Outputs from DUT (Loader)
    wire                                         load_busy;
    wire                                         load_done;
    wire                                         mem_req_valid;
    wire [MAIN_MEM_ADDR_WIDTH-1:0]               mem_req_addr;

    // SRAM interfaces from Loader (these will connect to sram_banked inputs)
    // The address width for SRAM is derived from (TILE_SIZE*TILE_SIZE*INPUT_DATA_WIDTH/MAIN_MEM_DATA_WIDTH_BITS)
    // where INPUT_DATA_WIDTH is 8 bits (for SINT8).
    localparam SRAM_WADDR_WIDTH = $clog2((TILE_SIZE * TILE_SIZE * SRAM_BANK_DATA_WIDTH) / MAIN_MEM_DATA_WIDTH_BITS);

    wire [SRAM_WADDR_WIDTH-1:0] sram_a_addr;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]         sram_a_wdata;
    wire                                         sram_a_we;

    wire [SRAM_WADDR_WIDTH-1:0] sram_b_addr;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]         sram_b_wdata;
    wire                                         sram_b_we;

    // SRAM read data outputs (from sram_banked, not used by Loader in this testbench)
    wire [SRAM_NUM_BANKS*SRAM_BANK_DATA_WIDTH-1:0] sram_a_rdata;
    wire [SRAM_NUM_BANKS*SRAM_BANK_DATA_WIDTH-1:0] sram_b_rdata;
    
    // SRAM read address inputs (for sram_banked, will connect to Data_Formatter in full system)
    // For this testbench, we will connect them to a constant value as Loader doesn't read from SRAMs.
    wire [SRAM_NUM_BANKS*$clog2(SRAM_BANK_DEPTH)-1:0] sram_a_raddr;
    wire [SRAM_NUM_BANKS*$clog2(SRAM_BANK_DEPTH)-1:0] sram_b_raddr;
    
    // Connect SRAM read addresses to a constant zero for this testbench
    assign sram_a_raddr = 0;
    assign sram_b_raddr = 0;


    //--------------------------------------------------------------------------
    // Instantiate the Device Under Test (DUT) - Loader
    //--------------------------------------------------------------------------
    loader #(
        .MATRIX_SIZE               (MATRIX_SIZE),
        .TILE_SIZE                 (TILE_SIZE),
        .MAIN_MEM_ADDR_WIDTH       (MAIN_MEM_ADDR_WIDTH),
        .MAIN_MEM_DATA_WIDTH_BITS  (MAIN_MEM_DATA_WIDTH_BITS)
    ) uut_loader ( // Changed instance name to uut_loader for clarity
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
    // Instantiate the SRAM Banked Modules (A-Tile and B-Tile)
    //--------------------------------------------------------------------------
    // SRAM for A-Tile (Ping buffer)
    sram_banked #(
        .NUM_BANKS          (SRAM_NUM_BANKS),
        .BANK_DEPTH         (SRAM_BANK_DEPTH),
        .BANK_DATA_WIDTH    (SRAM_BANK_DATA_WIDTH),
        .BUS_DATA_WIDTH     (SRAM_BUS_DATA_WIDTH)
    ) sram_a_tile (
        .clk                (clk),
        .we                 (sram_a_we),
        .waddr              (sram_a_addr),
        .wdata              (sram_a_wdata),
        .raddr              (sram_a_raddr),
        .rdata              (sram_a_rdata)
    );

    // SRAM for B-Tile (Pong buffer)
    sram_banked #(
        .NUM_BANKS          (SRAM_NUM_BANKS),
        .BANK_DEPTH         (SRAM_BANK_DEPTH),
        .BANK_DATA_WIDTH    (SRAM_BANK_DATA_WIDTH),
        .BUS_DATA_WIDTH     (SRAM_BUS_DATA_WIDTH)
    ) sram_b_tile (
        .clk                (clk),
        .we                 (sram_b_we),
        .waddr              (sram_b_addr),
        .wdata              (sram_b_wdata),
        .raddr              (sram_b_raddr),
        .rdata              (sram_b_rdata)
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
        $dumpfile("loader_pipelined_sram_waveform.vcd"); // Changed waveform file name
        // Dump all signals in the current module instance (tb_loader_pipelined)
        // and also the signals within the uut_loader and sram_a_tile/sram_b_tile instances.
        $dumpvars(0, tb_loader_pipelined.uut_loader);
        $dumpvars(0, tb_loader_pipelined.sram_a_tile);
        $dumpvars(0, tb_loader_pipelined.sram_b_tile);
        $dumpvars(0, tb_loader_pipelined); // Dump top-level signals

        rst_n = 1'b0;
        #(CLK_PERIOD * 2);
        rst_n = 1'b1;
    end

    //--------------------------------------------------------------------------
    // Main Test Stimulus
    //--------------------------------------------------------------------------
    initial begin
        load_req = 1'b0;
        i_tile_idx = 0; j_tile_idx = 0; k_tile_idx = 0;
        load_to_ping = 1'b0;

        @(posedge rst_n);
        @(posedge clk);
        
        $display("--------------------------------------------------");
        $display("%0t [TB] INFO: Test Case: Using PIPELINED memory model.", $time);
        $display("%0t [TB] INFO: Expecting cycle count to be close to ideal (~67 cycles).", $time);
        $display("--------------------------------------------------");

        load_req <= 1'b1;
        i_tile_idx <= 1; j_tile_idx <= 2; k_tile_idx <= 0;
        load_to_ping <= 1'b1; // Load to PING (A-Tile)
        @(posedge clk);
        load_req <= 1'b0; // De-assert request after one cycle

        // Wait until the loader is done
        // THIS IS THE CRITICAL LINE: If load_done never becomes 1, simulation won't stop.
        wait (load_done == 1'b1);
        @(posedge clk); // Give one more cycle for signals to settle after load_done

        $display("--------------------------------------------------");
        $display("%0t [TB] INFO: Test Case PASSED. Loader has finished.", $time);
        $display("--------------------------------------------------");
        
        #(CLK_PERIOD * 10); // Wait a bit more to observe final states
        $finish; // Terminate simulation
    end
    
    //--------------------------------------------------------------------------
    // NON-BLOCKING, PIPELINED Memory Model
    //--------------------------------------------------------------------------
    // Manual declaration of pipeline registers to avoid iverilog's array indexing limitations
    reg [MAIN_MEM_ADDR_WIDTH-1:0] addr_pipe_0;
    reg [MAIN_MEM_ADDR_WIDTH-1:0] addr_pipe_1;
    reg [MAIN_MEM_ADDR_WIDTH-1:0] addr_pipe_2; // For MEM_LATENCY = 3

    reg                           valid_pipe_0;
    reg                           valid_pipe_1;
    reg                           valid_pipe_2; // For MEM_LATENCY = 3

    always @(posedge clk) begin
        if (!rst_n) begin
            mem_req_ready <= 1'b1;
            mem_resp_valid <= 1'b0;
            mem_resp_rdata <= 0;
            
            // Initialize pipeline registers
            addr_pipe_0 <= 0;
            addr_pipe_1 <= 0;
            addr_pipe_2 <= 0;

            valid_pipe_0 <= 1'b0;
            valid_pipe_1 <= 1'b0;
            valid_pipe_2 <= 1'b0;
        end else begin
            // --- Stage 0: Accept new request from DUT ---
            // mem_req_ready is always high in this testbench, meaning memory is always ready to accept requests
            if (mem_req_valid && mem_req_ready) begin // This condition is effectively just mem_req_valid
                addr_pipe_0 <= mem_req_addr;
                valid_pipe_0 <= 1'b1;
            end else begin
                valid_pipe_0 <= 1'b0;
            end

            // --- Stages 1 to LATENCY-1: Shift existing requests down the pipeline ---
            addr_pipe_1 <= addr_pipe_0;
            valid_pipe_1 <= valid_pipe_0;

            addr_pipe_2 <= addr_pipe_1;
            valid_pipe_2 <= valid_pipe_1;

            // --- Drive memory response from the last pipeline stage ---
            mem_resp_valid <= valid_pipe_2; 
            if (valid_pipe_2) begin 
                // Return some fake data, e.g., part of the address, for easy debugging
                mem_resp_rdata <= {32'hBA5ED00D, uut_loader.mem_req_addr}; // Use uut_loader instance name
            end else begin
                mem_resp_rdata <= 0; // Clear data when not valid
            end
        end
    end

    //--------------------------------------------------------------------------
    // SRAM Write Monitor - Concurrently checks for SRAM write activity
    //--------------------------------------------------------------------------
    initial begin
        forever @(posedge clk) begin
            if (sram_a_we) begin
                $display("%0t [TB] MONITOR: SRAM A write detected! Addr: %0d, Data: 0x%h", $time, sram_a_addr, sram_a_wdata);
            end
        end
    end

    initial begin
        forever @(posedge clk) begin
            if (sram_b_we) begin
                $display("%0t [TB] MONITOR: SRAM B write detected! Addr: %0d, Data: 0x%h", $time, sram_b_addr, sram_b_wdata);
            end
        end
    end

endmodule
