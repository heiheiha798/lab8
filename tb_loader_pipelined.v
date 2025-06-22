//
// Filename: tb_loader_pipelined.v
// Description: An advanced testbench for the pipelined loader module.
//              It features a NON-BLOCKING, pipelined memory model to test
//              the DUT under high-performance conditions.
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

    // Testbench control
    localparam CLK_PERIOD    = 10; // ns
    localparam MEM_LATENCY   = 3;  // Memory latency in clock cycles

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

    // Memory interface signals
    reg                                          mem_req_ready;
    reg                                          mem_resp_valid;
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0]           mem_resp_rdata;

    // Outputs from DUT
    wire                                         load_busy;
    wire                                         load_done;
    wire                                         mem_req_valid;
    wire [MAIN_MEM_ADDR_WIDTH-1:0]               mem_req_addr;

    // SRAM interfaces
    wire [$clog2(TILE_SIZE*TILE_SIZE*8/MAIN_MEM_DATA_WIDTH_BITS)-1:0] sram_a_addr;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]                              sram_a_wdata;
    wire                                                             sram_a_we;
    wire [$clog2(TILE_SIZE*TILE_SIZE*8/MAIN_MEM_DATA_WIDTH_BITS)-1:0] sram_b_addr;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]                              sram_b_wdata;
    wire                                                             sram_b_we;


    //--------------------------------------------------------------------------
    // Instantiate the Device Under Test (DUT)
    //--------------------------------------------------------------------------
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
        $dumpfile("loader_pipelined_waveform.vcd");
        $dumpvars(0, tb_loader_pipelined);

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
        load_to_ping <= 1'b1;
        @(posedge clk);
        load_req <= 1'b0;

        wait (load_done == 1'b1);
        @(posedge clk);
        
        $display("--------------------------------------------------");
        $display("%0t [TB] INFO: Test Case PASSED. Loader has finished.", $time);
        $display("--------------------------------------------------");
        
        #(CLK_PERIOD * 10);
        $finish;
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
            if (mem_req_valid && mem_req_ready) begin
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
                // 修改这一行：使用具体的十六进制数值替换 'PIPE_LINE'
                mem_resp_rdata <= {32'hBA5ED00D, addr_pipe_2}; // 使用具体的十六进制值
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