//
// Filename: tb_compute_controller_accum_pipe.v
// Description: Testbench for the reconstructed compute_controller_accum_pipe.
//              It simulates the on-chip C-Accumulator and the new accelerator
//              control flow, where the DUT is called in a loop over 'k' to
//              compute a single output tile.
//
`timescale 1ns / 1ps

module tb_compute_controller_accum_pipe;

    //======================================================================
    //== Testbench Parameters
    //======================================================================
    // -- DUT Parameters --
    localparam TILE_SIZE                = 16;
    localparam INPUT_DATA_WIDTH         = 8;
    localparam PE_ACCUM_DATA_WIDTH      = 32;
    localparam MAIN_MEM_DATA_WIDTH_BITS = TILE_SIZE * PE_ACCUM_DATA_WIDTH;
    localparam MATRIX_SIZE              = 48;
    localparam ACCUM_PIPE_DELAY         = 2;
    localparam FINAL_ADDER_LATENCY      = 1;

    // -- Simulation Parameters --
    localparam CLK_PERIOD = 10;
    localparam NUM_TILES_PER_DIM = MATRIX_SIZE / TILE_SIZE;

    // -- SA Simulation Parameters --
    localparam SA_PIPELINE_DELAY = TILE_SIZE * 2;
    localparam SA_TOTAL_LATENCY  = TILE_SIZE * 3 - 2;
    localparam VALID_GAP_CYCLES  = 2;

    //======================================================================
    //== Signal Declarations
    //======================================================================
    // -- TB Control Signals --
    reg clk;
    reg rst_n;
    reg compute_req;

    // -- DUT Interface Wires --
    wire compute_busy;
    wire compute_done;
    wire dut_ready_for_sa_partial_sum;
    wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] sa_partial_sum_in;
    wire [$clog2(TILE_SIZE)-1:0] sa_partial_sum_row_idx;
    wire sa_partial_sum_valid;
    wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] sa_final_sum_in;
    wire sa_tile_all_pes_done_one_pass;
    wire ctrl_start_new_systolic_pass;
    wire ctrl_activate_pe_computation;
    wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] ctrl_c_data_to_sa;
    wire ctrl_enable_final_add;
    wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] ctrl_partial_sum_to_sa;
    wire [$clog2(TILE_SIZE)-1:0] c_accum_raddr;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0] c_accum_rdata;
    wire [$clog2(TILE_SIZE)-1:0] c_accum_waddr;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0] c_accum_wdata;
    wire c_accum_we;
    wire [$clog2(TILE_SIZE)-1:0] sram_a_addr;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_a_rdata_flat;
    wire [$clog2(TILE_SIZE)-1:0] sram_b_addr;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_b_rdata_flat;

    // -- TB Internal Registers and Memories --
    reg [INPUT_DATA_WIDTH-1:0] simulated_sram_a [TILE_SIZE-1:0];
    reg [INPUT_DATA_WIDTH-1:0] simulated_sram_b [TILE_SIZE-1:0];
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0] simulated_c_accum [TILE_SIZE-1:0];

    // -- SA Simulator Internal State --
    reg sa_partial_sum_valid_sim;
    reg signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] sa_partial_sum_in_reg;
    reg [$clog2(TILE_SIZE)-1:0] sa_partial_sum_row_idx_sim;
    reg sa_tile_all_pes_done_one_pass_sim;
    reg [$clog2(SA_TOTAL_LATENCY + 10)-1:0] sa_sim_cycle_cnt;
    reg [$clog2(TILE_SIZE):0] sa_output_row_idx_cnt;
    reg [$clog2(VALID_GAP_CYCLES+1)-1:0] sa_gap_cnt;
    reg sa_output_is_ready_for_handshake;
    // Added for Verilog-2001 compatibility to explicitly size the replicated element
    reg signed [PE_ACCUM_DATA_WIDTH-1:0] replicated_element_val;

    // -- Verification State --
    integer error_count;
    integer k;
    time start_time, end_time;

    //======================================================================
    //== DUT Instantiation
    //======================================================================
    compute_controller #(
        .TILE_SIZE(TILE_SIZE),
        .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH),
        .PE_ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH),
        .MAIN_MEM_DATA_WIDTH_BITS(MAIN_MEM_DATA_WIDTH_BITS),
        .MATRIX_SIZE(MATRIX_SIZE),
        .ACCUM_PIPE_DELAY(ACCUM_PIPE_DELAY)
    ) uut (
        .clk(clk),
        .rst_n(rst_n),
        .compute_req(compute_req),
        .compute_busy(compute_busy),
        .compute_done(compute_done),
        .dut_ready_for_sa_partial_sum(dut_ready_for_sa_partial_sum),
        .sa_partial_sum_valid(sa_partial_sum_valid),
        .sa_partial_sum_in(sa_partial_sum_in),
        .sa_partial_sum_row_idx(sa_partial_sum_row_idx),
        .sa_final_sum_in(sa_final_sum_in),
        .sa_tile_all_pes_done_one_pass(sa_tile_all_pes_done_one_pass),
        .ctrl_start_new_systolic_pass(ctrl_start_new_systolic_pass),
        .ctrl_activate_pe_computation(ctrl_activate_pe_computation),
        .ctrl_c_data_to_sa(ctrl_c_data_to_sa),
        .ctrl_enable_final_add(ctrl_enable_final_add),
        .ctrl_partial_sum_to_sa(ctrl_partial_sum_to_sa),
        .c_accum_raddr(c_accum_raddr),
        .c_accum_rdata(c_accum_rdata),
        .c_accum_waddr(c_accum_waddr),
        .c_accum_wdata(c_accum_wdata),
        .c_accum_we(c_accum_we),
        .sram_a_addr(sram_a_addr),
        .sram_a_rdata_flat(sram_a_rdata_flat),
        .sram_b_addr(sram_b_addr),
        .sram_b_rdata_flat(sram_b_rdata_flat)
    );

    //======================================================================
    //== Main Stimulus & Tasks
    //======================================================================
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

    initial begin
        $dumpfile("compute_controller_accum_pipe.vcd");
        $dumpvars(0, tb_compute_controller_accum_pipe);

        initialize_sim();

        // --- Main Test: Compute one full C_ij tile by looping over k ---
        $display("------------------------------------------------------------------");
        $display("[%0t] [TB] Starting full tile accumulation test (k=0 to %0d)", $time, NUM_TILES_PER_DIM-1);
        $display("------------------------------------------------------------------");

        start_time = $time;

        for (k = 0; k < NUM_TILES_PER_DIM; k = k + 1) begin
            $display("[%0t] [TB] Requesting computation for k = %0d...", $time, k);
            compute_req <= 1'b1;
            @(posedge clk);
            compute_req <= 1'b0;
            wait (compute_done == 1'b1);
            @(posedge clk);
            $display("[%0t] [TB] Computation for k = %0d finished.", $time, k);
        end

        end_time = $time;
        // --- End of Main Test ---

        check_c_accum();

        if (error_count == 0) begin
            $display("[%0t] [TB] <<<<< SUCCESS: All test cases passed. >>>>>", $time);
            $display("           Total cycles for one C_ij tile computation: %0d cycles", (end_time - start_time) / CLK_PERIOD);
        end else begin
            $display("[%0t] [TB] <<<<< FAILURE: %0d errors found. >>>>>", $time, error_count);
        end

        #(CLK_PERIOD * 10);
        $finish;
    end

    task initialize_sim;
        begin
            rst_n = 1'b0;
            compute_req = 1'b0;
            error_count = 0;
            // Initialize registers to a known value to prevent 'x' propagation at start
            sa_partial_sum_in_reg = 0;
            sa_partial_sum_row_idx_sim = 0;

            for (integer r = 0; r < TILE_SIZE; r = r + 1) begin
                simulated_sram_a[r] = r + 1; // Simplified data
                simulated_sram_b[r] = r + 1; // Simplified data
                simulated_c_accum[r] = {MAIN_MEM_DATA_WIDTH_BITS{1'b0}}; // Initialize C-ACCUM to 0
            end

            #(CLK_PERIOD * 2);
            rst_n = 1'b1;
            @(posedge clk);
            $display("[%0t] [TB] System reset released. C-ACCUM is zeroed.", $time);
        end
    endtask

    task check_c_accum;
        integer local_errors;
        reg signed [PE_ACCUM_DATA_WIDTH-1:0] expected_element;
        reg [MAIN_MEM_DATA_WIDTH_BITS-1:0] expected_row, actual_row;
        begin
            local_errors = 0;
            $display("[%0t] [TB] Verifying final C-ACCUM contents...", $time);

            for (integer r = 0; r < TILE_SIZE; r = r + 1) begin
                // Expected result after all K loops: C[r][c] = (r+1)*TILE_SIZE * NUM_K_TILES
                expected_element = (r + 1) * TILE_SIZE * NUM_TILES_PER_DIM;

                for (integer c_elem = 0; c_elem < TILE_SIZE; c_elem = c_elem + 1) begin
                   expected_row[c_elem*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] = expected_element;
                end

                actual_row = simulated_c_accum[r];

                if (expected_row !== actual_row) begin
                    $error("[%0t] [TB] C-ACCUM CHECK FAILED for row %0d.", $time, r);
                    $error("      Expected[0]: %d (0x%h)", expected_element, expected_element);
                    $error("      Actual[0]:   %d (0x%h)", actual_row[PE_ACCUM_DATA_WIDTH-1:0], actual_row[PE_ACCUM_DATA_WIDTH-1:0]);
                    local_errors = local_errors + 1;
                end
            end

            if (local_errors == 0) begin
                $display("[%0t] [TB] C-ACCUM verification PASSED.", $time);
            end else begin
                $display("[%0t] [TB] C-ACCUM verification FAILED with %0d errors.", $time, local_errors);
                error_count = error_count + local_errors;
            end
        end
    endtask

    //======================================================================
    //== Simulated Peripherals
    //======================================================================

    // --- Connect DUT outputs to simulator inputs ---
    assign sa_partial_sum_valid        = sa_partial_sum_valid_sim;
    assign sa_partial_sum_in           = sa_partial_sum_in_reg;
    assign sa_partial_sum_row_idx      = sa_partial_sum_row_idx_sim;
    assign sa_tile_all_pes_done_one_pass = sa_tile_all_pes_done_one_pass_sim;
    // assign sa_final_sum_in             = sa_final_sum_in; // Directly connect from adder sim

    // --- A/B/C SRAM/ACCUM Simulators ---
    assign sram_a_rdata_flat = {TILE_SIZE{simulated_sram_a[sram_a_addr]}};
    assign sram_b_rdata_flat = {TILE_SIZE{simulated_sram_b[sram_b_addr]}};
    // C-ACCUM Dual-Port SRAM behavioral model
    assign c_accum_rdata = simulated_c_accum[c_accum_raddr]; // Read port
    always @(posedge clk) begin
        if (c_accum_we) begin
            simulated_c_accum[c_accum_waddr] <= c_accum_wdata; // Write port
        end
    end

    // --- Final Adder Simulator ---
    // The final adder's result is purely combinational in this model for simplicity,
    // but its result is used by the DUT's pipeline, which models the latency.
    assign sa_final_sum_in = ctrl_enable_final_add ? (ctrl_partial_sum_to_sa + ctrl_c_data_to_sa) : 0;

    // --- Realistic Systolic Array Simulator (with Gaps) ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            sa_sim_cycle_cnt <= 0;
            sa_output_row_idx_cnt <= 0;
            sa_partial_sum_valid_sim <= 1'b0;
            sa_tile_all_pes_done_one_pass_sim <= 1'b0;
            sa_partial_sum_row_idx_sim <= 0;
            sa_output_is_ready_for_handshake <= 1'b0;
            sa_gap_cnt <= 0;
        end else begin
            // 默认将valid拉低，仅在握手成功时拉高一周期
            sa_partial_sum_valid_sim <= 1'b0;

            if (ctrl_start_new_systolic_pass) begin
                sa_sim_cycle_cnt <= 0;
                sa_output_row_idx_cnt <= 0;
                sa_tile_all_pes_done_one_pass_sim <= 1'b0;
                sa_output_is_ready_for_handshake <= 1'b0;
                sa_gap_cnt <= 0;
            end else if (ctrl_activate_pe_computation) begin
                sa_sim_cycle_cnt <= sa_sim_cycle_cnt + 1;

                // [修正逻辑] Stage 1: 准备数据 (Data Prep)
                // 当满足输出条件时，先准备好数据，并进入“准备握手”状态
                if (sa_output_row_idx_cnt < TILE_SIZE && sa_gap_cnt == 0 && !sa_output_is_ready_for_handshake) begin
                    if (sa_sim_cycle_cnt >= (SA_PIPELINE_DELAY + sa_output_row_idx_cnt)) begin
                        sa_output_is_ready_for_handshake <= 1'b1;
                        // 在此更新数据，确保数据在下一个周期 'valid' 信号变高之前是稳定的
                        sa_partial_sum_row_idx_sim <= sa_output_row_idx_cnt;
                        replicated_element_val = (sa_output_row_idx_cnt + 1) * TILE_SIZE;
                        sa_partial_sum_in_reg <= {TILE_SIZE{replicated_element_val}};
                    end
                end

                // [修正逻辑] Stage 2: 执行握手 (Handshake)
                // 当处于“准备握手”状态且下游就绪时，正式发出 valid 信号
                if (sa_output_is_ready_for_handshake && dut_ready_for_sa_partial_sum) begin
                    sa_partial_sum_valid_sim <= 1'b1;

                    // 更新状态机，为下一行做准备
                    sa_output_row_idx_cnt <= sa_output_row_idx_cnt + 1;
                    sa_output_is_ready_for_handshake <= 1'b0;
                    sa_gap_cnt <= VALID_GAP_CYCLES;
                end

                if (sa_gap_cnt > 0) begin
                    sa_gap_cnt <= sa_gap_cnt - 1;
                end

                if (sa_sim_cycle_cnt == SA_TOTAL_LATENCY - 1) begin
                    sa_tile_all_pes_done_one_pass_sim <= 1'b1;
                end
            end
        end
    end

endmodule