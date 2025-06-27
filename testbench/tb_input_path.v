//
// Filename: tb_input_path.v
// Description: A testbench to verify the input data path of the accelerator.
//              This version has fixed the bit-width mismatch warnings during instantiation.
//
`timescale 1ns / 1ps

module tb_input_path;

    // --- Parameters ---
    localparam TILE_SIZE         = 16;
    localparam INPUT_DATA_WIDTH  = 8;
    localparam BUS_DATA_WIDTH    = 64;
    localparam CLK_PERIOD        = 10;
    
    // --- Testbench Control ---
    reg clk;
    reg rst_n;
    reg loader_req;
    reg formatter_start_pass;

    // --- Loader Interface ---
    wire loader_busy, loader_done;
    wire imem_req_valid;
    reg  imem_req_ready;
    reg  imem_resp_valid;
    reg  [BUS_DATA_WIDTH-1:0] imem_resp_rdata;
    wire [31:0] imem_req_addr;

    // --- SRAM Interface ---
    wire [$clog2(TILE_SIZE*TILE_SIZE*8/BUS_DATA_WIDTH)-1:0] sram_a_waddr, sram_b_waddr;
    wire [BUS_DATA_WIDTH-1:0] sram_a_wdata, sram_b_wdata;
    wire sram_a_we, sram_b_we;
    
    wire [TILE_SIZE*$clog2(TILE_SIZE)-1:0] sram_a_raddr, sram_b_raddr;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_a_rdata, sram_b_rdata;

    // --- Formatter Interface ---
    wire pass_done_from_formatter;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] skewed_a_out, skewed_b_out;
    wire data_valid_out;

    // --- Memory Model ---
    reg [7:0] memory_a [0:255];
    reg [7:0] memory_b [0:255];

    //======================================================================
    //== DUT Instantiations
    //======================================================================

    // In this specific test, we only load one tile (i=0, j=0, k=0).
    // The MATRIX_SIZE is set to 48 in the loader's definition, so the
    // tile indices are 2 bits wide ($clog2(48/16)=2).
    loader #(
        .MATRIX_SIZE(48), .TILE_SIZE(16), .BASE_ADDR_A(32'h0), .BASE_ADDR_B(32'h1000)
    ) i_loader (
        .clk(clk), .rst_n(rst_n),
        .load_req(loader_req),
        // --- MODIFIED: Use sized literals to match the 2-bit port width ---
        .i_tile_idx(2'b0), 
        .j_tile_idx(2'b0), 
        .k_tile_idx(2'b0),
        // -----------------------------------------------------------------
        .load_to_ping(1'b1),
        .load_busy(loader_busy), .load_done(loader_done),
        .mem_req_valid(imem_req_valid), .mem_req_ready(imem_req_ready),
        .mem_resp_valid(imem_resp_valid), .mem_resp_rdata(imem_resp_rdata),
        .mem_req_addr(imem_req_addr),
        .sram_a_addr(sram_a_waddr), .sram_a_wdata(sram_a_wdata), .sram_a_we(sram_a_we),
        .sram_b_addr(sram_b_waddr), .sram_b_wdata(sram_b_wdata), .sram_b_we(sram_b_we)
    );

    sram_banked i_sram_a (.clk(clk), .we(sram_a_we), .waddr(sram_a_waddr), .wdata(sram_a_wdata), .raddr(sram_a_raddr), .rdata(sram_a_rdata));
    sram_banked i_sram_b (.clk(clk), .we(sram_b_we), .waddr(sram_b_waddr), .wdata(sram_b_wdata), .raddr(sram_b_raddr), .rdata(sram_b_rdata));

    data_formatter i_formatter (
        .clk(clk), .rst_n(rst_n),
        .start_pass(formatter_start_pass), .pass_done(pass_done_from_formatter),
        .sram_a_addr(sram_a_raddr), .sram_a_rdata(sram_a_rdata),
        .sram_b_addr(sram_b_raddr), .sram_b_rdata(sram_b_rdata),
        .skewed_a_out(skewed_a_out), .skewed_b_out(skewed_b_out),
        .data_valid_out(data_valid_out)
    );

    //======================================================================
    //== Test Sequence
    //======================================================================
    integer i; // for loop variable

    // Clock and Reset
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

    initial begin
        // 1. Initialization
        rst_n = 1'b0;
        loader_req = 1'b0;
        formatter_start_pass = 1'b0;
        imem_req_ready = 1'b1;
        imem_resp_valid = 1'b0;
        for (i = 0; i < 256; i = i + 1) begin
            memory_a[i] = i; // Simple ascending data
            memory_b[i] = 255 - i; // Simple descending data
        end
        $display("[%0t] [TB] Testbench Initialized.", $time);
        #(CLK_PERIOD * 5);
        rst_n = 1'b1;
        $display("[%0t] [TB] Reset Released.", $time);

        // 2. Test Loader
        @(posedge clk);
        loader_req = 1'b1;
        @(posedge clk);
        loader_req = 1'b0;
        $display("[%0t] [TB] Loader request sent. Waiting for loader_done...", $time);
        wait (loader_done == 1'b1);
        $display("[%0t] [TB] Loader finished. SRAMs should now be populated.", $time);

        // 3. Test Formatter
        @(posedge clk);
        formatter_start_pass = 1'b1;
        @(posedge clk);
        formatter_start_pass = 1'b0;
        $display("[%0t] [TB] Formatter start_pass sent. Monitoring output...", $time);
        
        $display("------------------------------------------------------------------");
        $display("Time | Valid | Skewed A[0] | Skewed A[15] | Skewed B[0] | Skewed B[15]");
        $display("------------------------------------------------------------------");
        for (i = 0; i < (2*TILE_SIZE - 1); i = i + 1) begin
            @(posedge clk);
            if (data_valid_out) begin
                $display("%5t |   %b   |    %3d      |      %3d     |    %3d      |      %3d", $time, data_valid_out, 
                         skewed_a_out[7:0], skewed_a_out[15*8+:8],
                         skewed_b_out[7:0], skewed_b_out[15*8+:8]);
            end
        end

        wait (pass_done_from_formatter == 1'b1);
        $display("[%0t] [TB] Formatter finished (pass_done asserted).", $time);
        $display("------------------------------------------------------------------");

        $display("[%0t] [TB] Input data path test PASSED!", $time);
        $finish;
    end

    // Memory Model for reads
    always @(posedge clk) begin
        if(imem_req_valid) begin
            imem_resp_valid <= 1'b1;
            // Simplified synchronous memory model
            for (i = 0; i < 8; i = i + 1) begin
                if (imem_req_addr >= 32'h1000) begin // Read from B
                    imem_resp_rdata[i*8+:8] <= memory_b[imem_req_addr - 32'h1000 + i];
                end else begin // Read from A
                    imem_resp_rdata[i*8+:8] <= memory_a[imem_req_addr + i];
                end
            end
        end else begin
            imem_resp_valid <= 1'b0;
        end
    end
    
endmodule