//
// Filename: tb_accelerator_core_combined_v4.v
// Description: Testbench for the accelerator core components.
//              Uses latched signals in TB to reliably detect pulses.
//
`timescale 1ns / 1ps

module tb_accelerator_core_combined_v4;

    //======================================================================
    //== Parameters
    //======================================================================
    localparam TB_TILE_SIZE = 16;
    localparam TB_INPUT_DATA_WIDTH = 8;
    localparam TB_PE_ACCUM_DATA_WIDTH = 32;
    localparam TB_SA_CC_MEM_DATA_WIDTH_BITS = TB_TILE_SIZE * TB_PE_ACCUM_DATA_WIDTH;
    localparam TB_WRITER_MEM_DATA_WIDTH_BITS = 64;
    localparam TB_WRITER_MATRIX_SIZE = 48;
    localparam TB_ACCUM_PIPE_DELAY = 2;
    localparam TB_MAIN_MEM_ADDR_WIDTH = 32;
    localparam TB_CLK_PERIOD = 10;

    localparam C_SRAM_TOTAL_WORDS_64BIT = (TB_TILE_SIZE * TB_TILE_SIZE * TB_PE_ACCUM_DATA_WIDTH) / TB_WRITER_MEM_DATA_WIDTH_BITS;
    localparam NUM_TILES_PER_DIM_FOR_WRITER = TB_WRITER_MATRIX_SIZE / TB_TILE_SIZE;

    localparam SIM_TIMEOUT_CYCLES_COMPUTE = TB_CLK_PERIOD * ( (5 * TB_TILE_SIZE) + 200);
    localparam SIM_TIMEOUT_CYCLES_WRITE = TB_CLK_PERIOD * (C_SRAM_TOTAL_WORDS_64BIT + 50);

    //======================================================================
    //== Signal Declarations (reg, wire, integer)
    //======================================================================
    reg clk;
    reg rst_n;
    reg tb_compute_req;
    reg tb_clear_all_pe_accumulators;
    reg tb_conditionally_clear_pe_sums_level;
    reg tb_write_req;
    reg [((NUM_TILES_PER_DIM_FOR_WRITER > 1) ? ($clog2(NUM_TILES_PER_DIM_FOR_WRITER)-1) : 0) :0] tb_i_tile_idx;
    reg [((NUM_TILES_PER_DIM_FOR_WRITER > 1) ? ($clog2(NUM_TILES_PER_DIM_FOR_WRITER)-1) : 0) :0] tb_j_tile_idx;
    reg  tb_array_data_valid_in;
    reg signed [TB_TILE_SIZE*TB_INPUT_DATA_WIDTH-1:0] tb_array_a_in;
    reg signed [TB_TILE_SIZE*TB_INPUT_DATA_WIDTH-1:0] tb_array_b_in;
    reg tb_mem_req_ready;
    reg tb_mem_write_done_stub;

    // DUT Wires
    wire cc_compute_busy;
    wire cc_compute_done;
    wire cc_dut_ready_for_sa_partial_sum;
    wire cc_ctrl_start_new_systolic_pass;       // Original wire from DUT
    wire cc_ctrl_activate_pe_computation;      // Original wire from DUT
    wire signed [TB_SA_CC_MEM_DATA_WIDTH_BITS-1:0] cc_ctrl_c_data_to_sa;
    wire cc_ctrl_enable_final_add;
    wire signed [TB_SA_CC_MEM_DATA_WIDTH_BITS-1:0] cc_ctrl_partial_sum_to_sa;
    wire sa_tile_row_result_valid;
    wire signed [TB_SA_CC_MEM_DATA_WIDTH_BITS-1:0] sa_tile_row_result_out;
    wire [$clog2(TB_TILE_SIZE)-1:0] sa_sa_partial_sum_row_idx;
    wire sa_tile_all_pes_done_one_pass;
    wire signed [TB_SA_CC_MEM_DATA_WIDTH_BITS-1:0] tb_sa_final_sum_in;
    wire [$clog2(TB_TILE_SIZE)-1:0] cc_c_accum_raddr;
    wire [TB_SA_CC_MEM_DATA_WIDTH_BITS-1:0] cc_c_accum_rdata;
    wire [$clog2(TB_TILE_SIZE)-1:0] cc_c_accum_waddr;
    wire [TB_SA_CC_MEM_DATA_WIDTH_BITS-1:0] cc_c_accum_wdata;
    wire cc_c_accum_we;
    wire [$clog2(C_SRAM_TOTAL_WORDS_64BIT)-1:0] writer_sram_c_addr;
    wire [TB_WRITER_MEM_DATA_WIDTH_BITS-1:0] writer_sram_c_rdata;
    wire writer_write_busy;
    wire writer_write_done;
    wire writer_mem_req_valid;
    wire [TB_WRITER_MEM_DATA_WIDTH_BITS-1:0] writer_mem_req_wdata;
    wire [TB_MAIN_MEM_ADDR_WIDTH-1:0] writer_mem_req_addr;

    wire debug_cc_start_pulse_latched_output; // 新增: 连接到 compute_controller 的调试输出

    // Testbench internal latched signals (现在可以保留用于与DUT的调试输出对比)
    reg cc_ctrl_start_new_systolic_pass_tb_latched; // 重命名以区分
    reg cc_ctrl_activate_pe_computation_tb_latched;

    // Testbench data storage and counters
    reg signed [TB_INPUT_DATA_WIDTH-1:0] A_tile_data [0:TB_TILE_SIZE-1][0:TB_TILE_SIZE-1];
    reg signed [TB_INPUT_DATA_WIDTH-1:0] B_tile_data [0:TB_TILE_SIZE-1][0:TB_TILE_SIZE-1];
    reg signed [TB_PE_ACCUM_DATA_WIDTH-1:0] C_expected_tile_data [0:TB_TILE_SIZE-1][0:TB_TILE_SIZE-1];
    reg [TB_WRITER_MEM_DATA_WIDTH_BITS-1:0] mem_output_capture [0:C_SRAM_TOTAL_WORDS_64BIT-1];

    integer r, c, k_loop;
    integer cycle_feed_count;
    integer word_idx;
    integer errors;
    integer timeout_counter;

    //======================================================================
    //== DUT Instantiations
    //======================================================================
    compute_controller #(
        .TILE_SIZE(TB_TILE_SIZE), .PE_ACCUM_DATA_WIDTH(TB_PE_ACCUM_DATA_WIDTH),
        .MAIN_MEM_DATA_WIDTH_BITS(TB_SA_CC_MEM_DATA_WIDTH_BITS), .ACCUM_PIPE_DELAY(TB_ACCUM_PIPE_DELAY)
    ) u_compute_controller (
        .clk(clk), .rst_n(rst_n), .compute_req(tb_compute_req),
        .compute_busy(cc_compute_busy), .compute_done(cc_compute_done),
        .dut_ready_for_sa_partial_sum(cc_dut_ready_for_sa_partial_sum),
        .sa_partial_sum_valid(sa_tile_row_result_valid), .sa_partial_sum_in(sa_tile_row_result_out),
        .sa_partial_sum_row_idx(sa_sa_partial_sum_row_idx), .sa_final_sum_in(tb_sa_final_sum_in),
        .sa_tile_all_pes_done_one_pass(sa_tile_all_pes_done_one_pass),
        .ctrl_start_new_systolic_pass(cc_ctrl_start_new_systolic_pass), // DUT output
        .ctrl_activate_pe_computation(cc_ctrl_activate_pe_computation), // DUT output
        .ctrl_c_data_to_sa(cc_ctrl_c_data_to_sa), .ctrl_enable_final_add(cc_ctrl_enable_final_add),
        .ctrl_partial_sum_to_sa(cc_ctrl_partial_sum_to_sa),
        .c_accum_raddr(cc_c_accum_raddr), .c_accum_rdata(cc_c_accum_rdata),
        .c_accum_waddr(cc_c_accum_waddr), .c_accum_wdata(cc_c_accum_wdata), .c_accum_we(cc_c_accum_we),
        .debug_start_pulse_latched(debug_cc_start_pulse_latched_output) // 连接新的调试端口
    );

    systolic_array #(
        .SIZE(TB_TILE_SIZE), .INPUT_DATA_WIDTH(TB_INPUT_DATA_WIDTH), .PE_ACCUM_DATA_WIDTH(TB_PE_ACCUM_DATA_WIDTH)
    ) u_systolic_array (
        .clk(clk), .rst_n(rst_n), .clear_all_pe_accumulators(tb_clear_all_pe_accumulators),
        .conditionally_clear_pe_sums_level(tb_conditionally_clear_pe_sums_level),
        .activate_pe_computation(cc_ctrl_activate_pe_computation), // From DUT
        .array_data_valid_in(tb_array_data_valid_in), .array_a_in(tb_array_a_in), .array_b_in(tb_array_b_in),
        .array_a_data_valid_out(), .array_a_out(), .array_b_data_valid_out(), .array_b_out(),
        .tile_row_result_out(sa_tile_row_result_out), .tile_row_result_valid(sa_tile_row_result_valid),
        .sa_partial_sum_row_idx(sa_sa_partial_sum_row_idx),
        .tile_all_pes_done_one_pass(sa_tile_all_pes_done_one_pass),
        .start_new_systolic_pass(cc_ctrl_start_new_systolic_pass) // From DUT
    );

    sram_c_accum #(
        .NUM_ROWS(TB_TILE_SIZE), .ELEM_PER_ROW(TB_TILE_SIZE), .ELEM_WIDTH(TB_PE_ACCUM_DATA_WIDTH),
        .BUS_DATA_WIDTH(TB_WRITER_MEM_DATA_WIDTH_BITS)
    ) u_sram_c_accum (
        .clk(clk), .we(cc_c_accum_we), .waddr(cc_c_accum_waddr), .wdata(cc_c_accum_wdata),
        .raddr_A(cc_c_accum_raddr), .rdata_A(cc_c_accum_rdata),
        .raddr_B(writer_sram_c_addr), .rdata_B(writer_sram_c_rdata)
    );

    writer #(
        .MATRIX_SIZE(TB_WRITER_MATRIX_SIZE), .TILE_SIZE(TB_TILE_SIZE),
        .MAIN_MEM_ADDR_WIDTH(TB_MAIN_MEM_ADDR_WIDTH), .MAIN_MEM_DATA_WIDTH_BITS(TB_WRITER_MEM_DATA_WIDTH_BITS)
    ) u_writer (
        .clk(clk), .rst_n(rst_n), .write_req(tb_write_req), .i_tile_idx(tb_i_tile_idx), .j_tile_idx(tb_j_tile_idx),
        .write_busy(writer_write_busy), .write_done(writer_write_done),
        .mem_req_valid(writer_mem_req_valid), .mem_req_wdata(writer_mem_req_wdata), .mem_req_addr(writer_mem_req_addr),
        .mem_req_ready(tb_mem_req_ready), .mem_write_done(tb_mem_write_done_stub),
        .sram_c_addr(writer_sram_c_addr), .sram_c_rdata(writer_sram_c_rdata)
    );

    assign tb_sa_final_sum_in = cc_ctrl_enable_final_add ? (cc_ctrl_partial_sum_to_sa + cc_ctrl_c_data_to_sa) : 0;

    initial begin
        clk = 0;
        forever #(TB_CLK_PERIOD/2) clk = ~clk;
    end

    // Testbench synchronous latch for DUT signals (保留用于对比，不再是主要的检查点)
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cc_ctrl_start_new_systolic_pass_tb_latched <= 1'b0;
            cc_ctrl_activate_pe_computation_tb_latched <= 1'b0;
        end else begin
            cc_ctrl_start_new_systolic_pass_tb_latched <= cc_ctrl_start_new_systolic_pass;
            cc_ctrl_activate_pe_computation_tb_latched <= cc_ctrl_activate_pe_computation;
        end
    end

    initial begin
        $dumpfile("accelerator_core_combined_v4.vcd");
        $dumpvars(0, tb_accelerator_core_combined_v4);

        // Initialize all regs
        clk = 0; rst_n = 1'b0; tb_compute_req = 1'b0; tb_clear_all_pe_accumulators = 1'b0;
        tb_conditionally_clear_pe_sums_level = 1'b0; tb_write_req = 1'b0; tb_i_tile_idx = 0;
        tb_j_tile_idx = 0; tb_array_data_valid_in = 1'b0; tb_array_a_in = 0; tb_array_b_in = 0;
        tb_mem_req_ready = 1'b1; tb_mem_write_done_stub = 1'b0; errors = 0;
        cc_ctrl_start_new_systolic_pass_tb_latched = 1'b0; // 显式初始化 TB 锁存信号
        cc_ctrl_activate_pe_computation_tb_latched = 1'b0;


        $display("[%0t] TB: Initializing A and B tile data...", $time);
        for (r = 0; r < TB_TILE_SIZE; r = r + 1) begin
            for (k_loop = 0; k_loop < TB_TILE_SIZE; k_loop = k_loop + 1) begin
                if ((r+k_loop+1) > 127) A_tile_data[r][k_loop] = 127;
                else if ((r+k_loop+1) < -128) A_tile_data[r][k_loop] = -128;
                else A_tile_data[r][k_loop] = r + k_loop + 1;
            end
        end
        for (k_loop = 0; k_loop < TB_TILE_SIZE; k_loop = k_loop + 1) begin
            for (c = 0; c < TB_TILE_SIZE; c = c + 1) begin
                if ((k_loop-c+5) > 127) B_tile_data[k_loop][c] = 127;
                else if ((k_loop-c+5) < -128) B_tile_data[k_loop][c] = -128;
                else B_tile_data[k_loop][c] = k_loop - c + 5;
            end
        end
        for (r = 0; r < TB_TILE_SIZE; r = r + 1) begin
            for (c = 0; c < TB_TILE_SIZE; c = c + 1) begin
                C_expected_tile_data[r][c] = 0;
                for (k_loop = 0; k_loop < TB_TILE_SIZE; k_loop = k_loop + 1) begin
                    C_expected_tile_data[r][c] = C_expected_tile_data[r][c] + (A_tile_data[r][k_loop] * B_tile_data[k_loop][c]);
                end
            end
        end
        $display("[%0t] TB: Tile data initialization complete.", $time);


        #(TB_CLK_PERIOD * 2) rst_n = 1'b0;
        #(TB_CLK_PERIOD * 5) rst_n = 1'b1;
        $display("[%0t] TB: Reset released.", $time);
        #(TB_CLK_PERIOD); // Wait one cycle after reset release for stability

        $display("[%0t] TB: Issuing compute request for one tile (k=0 pass).", $time);
        tb_compute_req = 1'b1;
        tb_clear_all_pe_accumulators = 1'b1;
        tb_conditionally_clear_pe_sums_level = 1'b1;

        @(posedge clk); // CLK EDGE T: compute_controller sees req.
                        // cc_ctrl_start_new_systolic_pass (wire) becomes 1 this cycle.
                        // The 'always' block latches this into cc_ctrl_start_new_systolic_pass_tb_latched.
        tb_compute_req = 1'b0;

        @(posedge clk); // CLK EDGE T+1: Now check the latched value from cycle T.

        $display("[%0t] TB: Checking signals at T+1:", $time);
        $display("[%0t] TB:   cc_ctrl_start_new_systolic_pass (wire from DUT original pulse) = %b", $time, cc_ctrl_start_new_systolic_pass);
        $display("[%0t] TB:   debug_cc_start_pulse_latched_output (wire from DUT debug latch) = %b", $time, debug_cc_start_pulse_latched_output);
        $display("[%0t] TB:   cc_ctrl_start_new_systolic_pass_tb_latched (TB's own latch of original pulse) = %b", $time, cc_ctrl_start_new_systolic_pass_tb_latched);

        if (debug_cc_start_pulse_latched_output == 1'b1) begin
            $display("[%0t] TB: Detected DUT's DEBUG_LATCHED_PULSE HIGH. This confirms the start pulse was generated.", $time);
        end else begin
            $display("[%0t] TB CRITICAL ERROR: DUT's DEBUG_LATCHED_PULSE was NOT 1'b1! Simulation halting.", $time);
            errors = errors + 1;
            $finish;
        end
        
        // 可选：检查TB自身的锁存信号，以理解其行为，但这不再是主要通过条件
        if (cc_ctrl_start_new_systolic_pass_tb_latched == 1'b0) begin
             $display("[%0t] TB WARNING: TB's own latch of original pulse is 0, while DUT's debug latch is 1. This is expected if original pulse is single-cycle and TB samples at same time.", $time);
        end
        if (cc_ctrl_start_new_systolic_pass == 1'b1) begin
             $display("[%0t] TB WARNING: Original pulse wire is still 1 at T+1. This is unexpected for a single cycle pulse; ensure compute_controller is designed for single cycle.", $time);
        end


        tb_clear_all_pe_accumulators = 1'b0;
        tb_conditionally_clear_pe_sums_level = 1'b0;

        // Check latched cc_ctrl_activate_pe_computation.
        // This signal (cc_ctrl_activate_pe_computation) should have gone high at CLK EDGE T.
        // So, cc_ctrl_activate_pe_computation_tb_latched should be high when checked at CLK EDGE T+1.
        if (cc_ctrl_activate_pe_computation_tb_latched == 1'b1) begin
            $display("[%0t] TB: Detected LATCHED cc_ctrl_activate_pe_computation HIGH.", $time);
        end else begin
            $display("[%0t] TB CRITICAL ERROR: LATCHED cc_ctrl_activate_pe_computation was NOT 1'b1! Value: %b. Original wire value now: %b.", $time, cc_ctrl_activate_pe_computation_tb_latched, cc_ctrl_activate_pe_computation);
            errors = errors + 1;
            $finish;
        end
        
        $display("[%0t] TB: Feeding SA.", $time);
        tb_array_data_valid_in = 1'b1;
        for (cycle_feed_count = 0; cycle_feed_count < (2*TB_TILE_SIZE - 1) ; cycle_feed_count = cycle_feed_count + 1) begin
            if (cycle_feed_count < TB_TILE_SIZE) begin
                for (r = 0; r < TB_TILE_SIZE; r = r + 1) begin
                    tb_array_a_in[(r*TB_INPUT_DATA_WIDTH) +: TB_INPUT_DATA_WIDTH] = A_tile_data[r][cycle_feed_count];
                end
                for (c = 0; c < TB_TILE_SIZE; c = c + 1) begin
                    tb_array_b_in[(c*TB_INPUT_DATA_WIDTH) +: TB_INPUT_DATA_WIDTH] = B_tile_data[cycle_feed_count][c];
                end
            end
            @(posedge clk);
        end
        tb_array_data_valid_in = 1'b0;
        $display("[%0t] TB: Finished feeding data to Systolic Array.", $time);


        $display("[%0t] TB: Waiting for compute_done...", $time);
        timeout_counter = 0;
        while (cc_compute_done == 1'b0 && timeout_counter < SIM_TIMEOUT_CYCLES_COMPUTE) begin
            @(posedge clk);
            timeout_counter = timeout_counter + TB_CLK_PERIOD;
        end

        if (cc_compute_done == 1'b1) begin
            $display("[%0t] TB: Compute Controller asserted compute_done.", $time);
        end else begin
            $display("[%0t] TB ERROR: Compute Controller timed out waiting for compute_done. errors=%d", $time, errors);
            errors = errors + 1; $finish;
        end
        @(posedge clk);

        // Once compute is done, debug_cc_start_pulse_latched_output should reset.
        if (debug_cc_start_pulse_latched_output == 1'b0) begin
            $display("[%0t] TB: DEBUG_LATCHED_PULSE cleared as expected after compute_done.", $time);
        end else begin
            $display("[%0t] TB ERROR: DEBUG_LATCHED_PULSE did not clear after compute_done! Value: %b", $time, debug_cc_start_pulse_latched_output);
            errors = errors + 1;
        end

        $display("[%0t] TB: Issuing write request to Writer for tile (0,0).", $time);
        tb_i_tile_idx = 0; tb_j_tile_idx = 0;
        tb_write_req = 1'b1;
        @(posedge clk);
        tb_write_req = 1'b0;

        word_idx = 0; timeout_counter = 0;
        while (writer_write_done == 1'b0 && timeout_counter < SIM_TIMEOUT_CYCLES_WRITE) begin
             if (writer_mem_req_valid && tb_mem_req_ready) begin
                 if (word_idx < C_SRAM_TOTAL_WORDS_64BIT) begin
                    mem_output_capture[word_idx] = writer_mem_req_wdata;
                 end else begin
                    $display("[%0t] TB WARNING: Writer produced more words than expected!", $time);
                 end
                 word_idx = word_idx + 1;
             end
             @(posedge clk);
             timeout_counter = timeout_counter + TB_CLK_PERIOD;
        end

        if (writer_write_done) begin
            $display("[%0t] TB: Writer asserted write_done. Total words written: %d", $time, word_idx);
        end else begin
            $display("[%0t] TB ERROR: Writer did not complete (timeout). Words written: %d. errors=%d", $time, word_idx, errors);
            errors = errors + 1; $finish;
        end
        
        if (word_idx != C_SRAM_TOTAL_WORDS_64BIT) begin
            $display("[%0t] TB ERROR: Writer wrote %d words, expected %d words. errors=%d", $time, word_idx, C_SRAM_TOTAL_WORDS_64BIT, errors);
            errors = errors + 1;
        end else begin
            $display("[%0t] TB: Writer wrote the correct number of words.", $time);
            if (C_SRAM_TOTAL_WORDS_64BIT > 0) begin
                if (mem_output_capture[0][TB_PE_ACCUM_DATA_WIDTH-1:0] !== C_expected_tile_data[0][0]) begin
                    $display("[%0t] TB ERROR: Mismatch for C[0][0]. Expected 0x%h, Got 0x%h", $time, C_expected_tile_data[0][0], mem_output_capture[0][TB_PE_ACCUM_DATA_WIDTH-1:0]);
                    errors = errors + 1;
                end
                if (TB_TILE_SIZE > 1 && mem_output_capture[0][TB_WRITER_MEM_DATA_WIDTH_BITS-1:TB_PE_ACCUM_DATA_WIDTH] !== C_expected_tile_data[0][1]) begin
                     $display("[%0t] TB ERROR: Mismatch for C[0][1]. Expected 0x%h, Got 0x%h", $time, C_expected_tile_data[0][1], mem_output_capture[0][TB_WRITER_MEM_DATA_WIDTH_BITS-1:TB_PE_ACCUM_DATA_WIDTH]);
                    errors = errors + 1;
                end
            end
        end

        #(TB_CLK_PERIOD * 10);
        if (errors == 0) begin
            $display("----------------------------------------------------------");
            $display("[%0t] TB: SIMULATION PASSED SUCCESSFULLY.", $time);
            $display("----------------------------------------------------------");
        end else begin
            $display("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            $display("[%0t] TB: SIMULATION FAILED with %d errors.", $time, errors);
            $display("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        end
        $finish;
    end
endmodule