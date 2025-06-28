//
// Filename: tb_accelerator.v
// Description: Top-level testbench for the complete matrix multiplication accelerator.
//              It simulates a single-port main memory, loads initial data from
//              a file, drives the accelerator, and writes the final results
//              back to a file for verification.
//
`timescale 1ns / 1ps

module tb_accelerator;

    //--------------------------------------------------------------------------
    // Testbench Parameters
    //--------------------------------------------------------------------------
    // Match these with the DUT parameters
    parameter P_MATRIX_SIZE               = 48;
    parameter P_TILE_SIZE                 = 16;
    parameter P_MAIN_MEM_ADDR_WIDTH       = 32;
    parameter P_MAIN_MEM_DATA_WIDTH_BITS  = 64;
    parameter P_SRAM_C_WRITE_WIDTH        = 512;

    // Base addresses must match the DUT
    parameter P_BASE_ADDR_A               = 32'h10000000;
    parameter P_BASE_ADDR_B               = 32'h20000000;
    parameter P_BASE_ADDR_C               = 32'h30000000;

    // Testbench control
    parameter CLK_PERIOD                  = 10; // 100MHz clock
    parameter TIMEOUT_CYCLES              = P_MATRIX_SIZE * P_MATRIX_SIZE * P_MATRIX_SIZE * 2; // Generous timeout

    //--------------------------------------------------------------------------
    // Memory Model Parameters
    //--------------------------------------------------------------------------
    localparam NUM_TILES_PER_DIM  = P_MATRIX_SIZE / P_TILE_SIZE;
    localparam BYTES_PER_WORD     = P_MAIN_MEM_DATA_WIDTH_BITS / 8;
    // Calculate memory size needed for A, B, and C matrices
    localparam A_B_MATRIX_SIZE_BYTES = P_MATRIX_SIZE * P_MATRIX_SIZE * 1; // SINT8
    localparam C_MATRIX_SIZE_BYTES   = P_MATRIX_SIZE * P_MATRIX_SIZE * 4; // SINT32
    
    localparam A_B_MATRIX_SIZE_WORDS = A_B_MATRIX_SIZE_BYTES / BYTES_PER_WORD;
    localparam C_MATRIX_SIZE_WORDS   = C_MATRIX_SIZE_BYTES / BYTES_PER_WORD;

    // Total memory size for simulation. Needs to be large enough for the address space.
    // We will use offsets from base addresses for simplicity.
    localparam MEM_A_START_IDX = 0;
    localparam MEM_B_START_IDX = A_B_MATRIX_SIZE_WORDS;
    localparam MEM_C_START_IDX = A_B_MATRIX_SIZE_WORDS * 2;
    localparam MEM_TOTAL_WORDS = MEM_C_START_IDX + C_MATRIX_SIZE_WORDS;

    //--------------------------------------------------------------------------
    // Signals and Wires
    //--------------------------------------------------------------------------
    reg  clk;
    reg  rst_n;
    reg  tb_comp_enb;

    wire tb_busyb;
    wire tb_done;

    // DUT Memory Interface
    wire [P_MAIN_MEM_ADDR_WIDTH-1:0]      dut_imem_addr;
    wire                                  dut_imem_read_enb;
    reg  [P_MAIN_MEM_DATA_WIDTH_BITS-1:0] dut_imem_data_in;
    // Modified: dut_imem_req_ready is now always 1'b1.
    wire                                  dut_imem_req_ready;
    reg                                   dut_imem_resp_valid;

    wire [P_MAIN_MEM_ADDR_WIDTH-1:0]      dut_omem_addr;
    wire [P_MAIN_MEM_DATA_WIDTH_BITS-1:0] dut_omem_wdata;
    wire                                  dut_omem_write_enb;
    // Modified: dut_omem_req_ready is now always 1'b1.
    wire                                  dut_omem_req_ready;

    //--------------------------------------------------------------------------
    // DUT Instantiation
    //--------------------------------------------------------------------------
    accelerator #(
        .MATRIX_SIZE(P_MATRIX_SIZE),
        .TILE_SIZE(P_TILE_SIZE),
        .MAIN_MEM_ADDR_WIDTH(P_MAIN_MEM_ADDR_WIDTH),
        .MAIN_MEM_DATA_WIDTH_BITS(P_MAIN_MEM_DATA_WIDTH_BITS),
        .BASE_ADDR_A(P_BASE_ADDR_A),
        .BASE_ADDR_B(P_BASE_ADDR_B),
        .BASE_ADDR_C(P_BASE_ADDR_C),
        .SRAM_C_WRITE_WIDTH(P_SRAM_C_WRITE_WIDTH)
    ) dut (
        .clk(clk),
        .rst_n(rst_n),
        .comp_enb(tb_comp_enb),
        .busyb(tb_busyb),
        .done(tb_done),
        .imem_addr(dut_imem_addr),
        .imem_read_enb(dut_imem_read_enb),
        .imem_data_in(dut_imem_data_in),
        .imem_req_ready(dut_imem_req_ready),
        .imem_resp_valid(dut_imem_resp_valid),
        .omem_addr(dut_omem_addr),
        .omem_wdata(dut_omem_wdata),
        .omem_write_enb(dut_omem_write_enb),
        .omem_req_ready(dut_omem_req_ready)
    );

    //--------------------------------------------------------------------------
    // Main Memory Model (Modified for ideal pipelined behavior)
    //--------------------------------------------------------------------------
    reg [P_MAIN_MEM_DATA_WIDTH_BITS-1:0] main_memory_storage [0:MEM_TOTAL_WORDS-1];

    // --- Input Memory (imem) Signals ---
    // dut_imem_req_ready is always 1'b1, meaning the memory is always ready to accept read requests.
    // --- Input Memory (imem) Signals ---
    assign dut_imem_req_ready = 1'b1;

    // Behavioral model for Input Memory (imem) - Corrected 1 cycle latency
    reg [P_MAIN_MEM_ADDR_WIDTH-1:0] imem_addr_s1;       // Stage 1 latched address
    reg                             imem_req_accepted_s1; // Stage 1 request accepted flag
    integer read_idx;

    // Stage 1: Latch incoming request
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            imem_req_accepted_s1 <= 1'b0;
            imem_addr_s1         <= '0;
        end else begin
            if (dut_imem_read_enb && dut_imem_req_ready) begin
                imem_addr_s1         <= dut_imem_addr;
                imem_req_accepted_s1 <= 1'b1;
                // $display("[%0t] [TB-IMEM] Read Accepted. Latched Addr: 0x%h (Data available next cycle)", $time, dut_imem_addr);
            end else begin
                imem_req_accepted_s1 <= 1'b0;
            end
        end
    end

    // Stage 2: Drive response (data and valid)
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            dut_imem_resp_valid <= 1'b0;
            dut_imem_data_in    <= '0;
        end else begin
            if (imem_req_accepted_s1) begin // If a request was latched in the previous cycle
                dut_imem_resp_valid <= 1'b1;
                // Determine memory region and calculate index
                if (imem_addr_s1 >= P_BASE_ADDR_A && imem_addr_s1 < P_BASE_ADDR_B) begin
                    read_idx = (imem_addr_s1 - P_BASE_ADDR_A) / BYTES_PER_WORD;
                    dut_imem_data_in <= main_memory_storage[MEM_A_START_IDX + read_idx];
                    // $display("[%0t] [TB-IMEM] Data Driven. Addr: 0x%h, Data: 0x%h", $time, imem_addr_s1, main_memory_storage[MEM_A_START_IDX + read_idx]);
                end else if (imem_addr_s1 >= P_BASE_ADDR_B && imem_addr_s1 < P_BASE_ADDR_C) begin
                    read_idx = (imem_addr_s1 - P_BASE_ADDR_B) / BYTES_PER_WORD;
                    dut_imem_data_in <= main_memory_storage[MEM_B_START_IDX + read_idx];
                    // $display("[%0t] [TB-IMEM] Data Driven. Addr: 0x%h, Data: 0x%h", $time, imem_addr_s1, main_memory_storage[MEM_B_START_IDX + read_idx]);
                end else begin
                    $error("[%0t] [TB-IMEM] ERROR: Read from unknown or unhandled address 0x%h", $time, imem_addr_s1);
                    dut_imem_data_in <= {P_MAIN_MEM_DATA_WIDTH_BITS{1'bx}};
                end
            end else begin
                dut_imem_resp_valid <= 1'b0;
                dut_imem_data_in    <= '0; // Or keep previous value if desired when not valid
            end
        end
    end


    // --- Output Memory (omem) Signals ---
    // dut_omem_req_ready is always 1'b1, meaning the memory is always ready to accept write requests.
    assign dut_omem_req_ready = 1'b1;

    // Behavioral model for Output Memory (omem) - accepts one request per cycle, writes immediately
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // No specific reg to reset as omem_req_ready is always 1
        end else begin
            if (dut_omem_write_enb && dut_omem_req_ready) begin // dut_omem_req_ready is always 1
                integer write_idx;
                // Ensure address is within C matrix bounds
                if (dut_omem_addr >= P_BASE_ADDR_C && dut_omem_addr < (P_BASE_ADDR_C + C_MATRIX_SIZE_BYTES)) begin
                    write_idx = (dut_omem_addr - P_BASE_ADDR_C) / BYTES_PER_WORD;
                    main_memory_storage[MEM_C_START_IDX + write_idx] <= dut_omem_wdata;
                    // $display("[%0t] [TB-OMEM] Write Accepted & Stored. Addr: 0x%h, Data: 0x%h, Index: %d",
                    //          $time, dut_omem_addr, dut_omem_wdata, MEM_C_START_IDX + write_idx);
                end else begin
                    $error("[%0t] [TB-OMEM] ERROR: Write to out-of-bounds address 0x%h for C matrix", $time, dut_omem_addr);
                end
            end
        end
    end


    //--------------------------------------------------------------------------
    // Test Sequence and Control
    //--------------------------------------------------------------------------
    initial begin
        clk = 1'b0;
        forever #(CLK_PERIOD / 2) clk = ~clk;
    end

    integer out_file_handle;
    integer i;

    initial begin
        // --- Initialization ---
        rst_n       <= 1'b0;
        tb_comp_enb <= 1'b0;

        $display("==============================================");
        $display("[%0t] [TB] Testbench starting...", $time);
        $display("==============================================");

        // Load input data from file into simulated memory
        // A & B matrices are concatenated in the file.
        $readmemh("input_mem.csv", main_memory_storage, MEM_A_START_IDX, (MEM_C_START_IDX-1));
        $display("[%0t] [TB] Loaded 'input_mem.csv' into memory model.", $time);

        // --- Reset Sequence ---
        #(CLK_PERIOD * 5);
        rst_n <= 1'b1;
        $display("[%0t] [TB] Reset released.", $time);
        wait (rst_n === 1'b1);
        @(posedge clk);
        
        // --- Start Accelerator ---
        $display("[%0t] [TB] Asserting comp_enb to start accelerator.", $time);
        tb_comp_enb <= 1'b1;
        @(posedge clk);
        tb_comp_enb <= 1'b0;

        // --- Wait for Completion with Timeout ---
        $display("[%0t] [TB] Waiting for accelerator to finish (tb_done=1)...", $time);
        fork
            // begin : timeout_watcher
            //     #(CLK_PERIOD * TIMEOUT_CYCLES);
            //     $error("[%0t] [TB] TIMEOUT! Accelerator did not finish within %0d cycles.", $time, TIMEOUT_CYCLES);
            //     $finish;
            // end
            begin : done_watcher
                wait (tb_done == 1'b1);
                $display("[%0t] [TB] Accelerator finished (tb_done asserted).", $time);
                // disable timeout_watcher;
            end
        join

        // --- Write Results to File ---
        @(posedge clk);
        $display("[%0t] [TB] Writing results from memory model to 'result_mem.csv'...", $time);
        out_file_handle = $fopen("result_mem.csv", "w");
        if (out_file_handle == 0) begin
            $error("Could not open result_mem.csv for writing.");
            $finish;
        end
        for (i = 0; i < C_MATRIX_SIZE_WORDS; i = i + 1) begin
            $fdisplay(out_file_handle, "%h", main_memory_storage[MEM_C_START_IDX + i]);
        end
        $fclose(out_file_handle);
        $display("[%0t] [TB] Results written to 'result_mem.csv'.", $time);

        // --- Final Result ---
        $display("==============================================");
        $display("[%0t] [TB] TEST SCENARIO COMPLETED.", $time);
        $display("==============================================");
        $finish;
    end

endmodule
