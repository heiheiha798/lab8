`timescale 1ns / 1ps

module testbench_top;

    localparam CLK_PERIOD = 10;

    localparam INPUT_MEM_WORDS_TB  = 64; // <<<<<<<<<< MODIFIED
    localparam INPUT_ADDR_WIDTH_TB = $clog2(INPUT_MEM_WORDS_TB);   // $clog2(64) = 6

    localparam RESULT_MEM_WORDS_TB = 64; // <<<<<<<<<< MODIFIED
    localparam RESULT_ADDR_WIDTH_TB = $clog2(RESULT_MEM_WORDS_TB); // $clog2(64) = 6

    reg clk = 0;
    reg rst;
    reg comp_enb;

    wire [15:0]                  accelerator_mem_addr;
    wire [63:0]                  accelerator_mem_data_in;
    wire                         accelerator_mem_read_enb;

    wire [15:0]                  accelerator_res_addr;
    wire [63:0]                  accelerator_res_data_out;
    wire                         accelerator_res_write_enb;

    wire                         accelerator_busyb;
    wire                         accelerator_done;
    wire [3:0]                   accelerator_current_state_dbg; // MODIFIED width from 2:0 to 3:0

    // Instantiate the accelerator
    // Ensure accelerator.v parameters (MATRIX_DIM, TILE_DIM) are set to 16 for this test
    accelerator u_accelerator (
        .clk           (clk),
        .rst           (rst),
        .comp_enb      (comp_enb),
        .busyb         (accelerator_busyb),
        .done          (accelerator_done),
        .mem_addr      (accelerator_mem_addr),
        .mem_data_in   (accelerator_mem_data_in),
        .mem_read_enb  (accelerator_mem_read_enb),
        .res_addr      (accelerator_res_addr),
        .res_data_out  (accelerator_res_data_out),
        .res_write_enb (accelerator_res_write_enb),
        .current_state_out (accelerator_current_state_dbg)
    );

    // Testbench's Input Memory Model
    ram #(
        .DATA_WIDTH(64),
        .ADDR_WIDTH(INPUT_ADDR_WIDTH_TB) // Uses its own calculated address width
    ) u_input_mem (
        .clk     (clk),
        .web     (1'b1), // Read-only by accelerator
        .address (accelerator_mem_addr[INPUT_ADDR_WIDTH_TB-1:0]), // Accelerator may generate wider addr
        .d       (64'd0),
        .q       (accelerator_mem_data_in),
        .cs      (accelerator_mem_read_enb) // Assumes cs is high for active access
    );

    // Testbench's Result Memory Model
    ram #(
        .DATA_WIDTH(64),
        .ADDR_WIDTH(RESULT_ADDR_WIDTH_TB) // Uses its own calculated address width
    ) u_res_mem (
        .clk     (clk),
        .web     (~accelerator_res_write_enb), // Write enable is active low for RAM
        .address (accelerator_res_addr[RESULT_ADDR_WIDTH_TB-1:0]), // Accelerator may generate wider addr
        .d       (accelerator_res_data_out),
        .q       (),
        .cs      (accelerator_res_write_enb) // Assumes cs is high for active access
    );

    integer i, result_file;
    integer dump_file_a, dump_file_b; // Moved here for Verilog-2001 compatibility with fork-join

    always #(CLK_PERIOD/2) clk = ~clk;

    initial begin
        // Main test sequence
        begin // This begin-end for the first block of the fork
            $timeformat(-9, 2, " ns", 10);
            $dumpfile("wave.vcd");
            $dumpvars(0, testbench_top);

            // Ensure input_mem.csv has 64 lines for 16x16 A and 16x16 B SINT8 data
            // Line 0 to 31: Matrix A (SINT8)
            // Line 32 to 63: Matrix B (SINT8)
            $readmemh("input_mem.csv", u_input_mem.mem);

            comp_enb = 1'b0;
            rst = 1'b1;
            # (CLK_PERIOD * 2);
            rst = 1'b0;
            # (CLK_PERIOD);

            $display("T=%t: --- Sending comp_enb pulse ---", $time);
            comp_enb = 1'b1;
            # (CLK_PERIOD);
            comp_enb = 1'b0;

            $display("T=%t: Waiting for 'done' signal from accelerator...", $time);
            wait (accelerator_done == 1'b1);
            $display("T=%t: Accelerator 'done' signal received. Computation complete.", $time);

            # (CLK_PERIOD * 2);

            $display("T=%t: Writing accelerator results to result_mem.csv ...", $time);
            result_file = $fopen("result_mem.csv", "w");
            for(i = 0; i < RESULT_MEM_WORDS_TB; i = i + 1) begin // Use RESULT_MEM_WORDS_TB
                $fwrite(result_file, "%h\n", u_res_mem.mem[i]);
            end
            $fclose(result_file);
            $display("T=%t: Results written. Simulation finished.", $time);
            $finish;
        end
    end
endmodule