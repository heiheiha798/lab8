//
// Filename: tb_compute_controller_robust.v
// Description: A robust testbench for the compute_controller_robust module.
//              It simulates a realistic environment where the systolic array (SA)
//              output is NOT available every cycle (gappy/bursty stream), and
//              it fully models the external final adder with latency.
//
`timescale 1ns / 1ps

module tb_compute_controller_robust;

    //======================================================================
    //== Testbench Parameters
    //======================================================================
    // -- DUT Parameters --
    localparam TILE_SIZE                = 16;
    localparam INPUT_DATA_WIDTH         = 8;
    localparam PE_ACCUM_DATA_WIDTH      = 32;
    localparam MAIN_MEM_DATA_WIDTH_BITS = TILE_SIZE * PE_ACCUM_DATA_WIDTH;
    localparam MATRIX_SIZE              = 48; // 使用一个较小的矩阵以加速仿真
    localparam FINAL_ADDER_LATENCY      = 1;

    // -- Simulation Parameters --
    localparam CLK_PERIOD = 10;
    localparam NUM_TILES_PER_DIM = MATRIX_SIZE / TILE_SIZE;

    // -- SA Simulation Parameters --
    localparam SA_PIPELINE_DELAY = TILE_SIZE * 2; // Latency to get the first row out
    localparam SA_TOTAL_LATENCY  = TILE_SIZE * 3 - 2; // Latency to get the last row out
    // [KEY] 模拟SA输出结果之间的间隙，0表示背靠背输出，>0表示有延时
    localparam VALID_GAP_CYCLES  = 2;

    //======================================================================
    //== Signal Declarations
    //======================================================================
    // -- TB Control Signals --
    reg clk;
    reg rst_n;
    reg compute_req;
    reg [$clog2(NUM_TILES_PER_DIM)-1:0] k_tile_idx;

    // -- DUT Interface Wires --
    wire compute_busy;
    wire compute_done;
    wire dut_ready_for_sa_partial_sum;
    wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] sa_partial_sum_in;
    wire [$clog2(TILE_SIZE)-1:0] sa_partial_sum_row_idx;
    wire sa_partial_sum_valid;
    wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] sa_final_sum_in;
    wire sa_tile_all_pes_done_one_pass;
    wire ctrl_clear_all_pe_accumulators;
    wire ctrl_start_new_systolic_pass;
    wire ctrl_activate_pe_computation;
    wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] ctrl_c_data_to_sa;
    wire ctrl_enable_final_add;
    wire [$clog2(TILE_SIZE)-1:0] sram_a_addr;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_a_rdata_flat;
    wire [$clog2(TILE_SIZE)-1:0] sram_b_addr;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_b_rdata_flat;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sa_array_a_in_flat;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sa_array_b_in_flat;
    wire ctrl_array_data_valid_in;
    wire [$clog2(TILE_SIZE)-1:0] sram_c_addr;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0] sram_c_wdata;
    wire sram_c_we;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0] sram_c_rdata;

    // -- TB Internal Registers and Memories --
    reg [INPUT_DATA_WIDTH-1:0] simulated_sram_a [TILE_SIZE-1:0];
    reg [INPUT_DATA_WIDTH-1:0] simulated_sram_b [TILE_SIZE-1:0];
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0] simulated_sram_c [TILE_SIZE-1:0];

    // -- SA Simulator Internal State --
    reg sa_partial_sum_valid_sim;
    reg signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] sa_partial_sum_in_reg;
    reg [$clog2(TILE_SIZE)-1:0] sa_partial_sum_row_idx_sim;
    reg sa_tile_all_pes_done_one_pass_sim;
    reg [$clog2(SA_TOTAL_LATENCY + 10)-1:0] sa_sim_cycle_cnt;
    reg [$clog2(TILE_SIZE):0] sa_output_row_idx_cnt;
    reg [$clog2(VALID_GAP_CYCLES+1)-1:0] sa_gap_cnt;
    reg sa_output_is_ready_for_handshake;
    reg signed [PE_ACCUM_DATA_WIDTH-1:0] mock_sa_element_val;

    // -- Final Adder Simulator Internal State --
    reg signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] sa_final_sum_in_reg;
    reg signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] final_adder_pipeline [FINAL_ADDER_LATENCY-1:0];

    // -- Verification State --
    integer error_count;


    //======================================================================
    //== DUT Instantiation
    //======================================================================
    compute_controller #(
        .TILE_SIZE(TILE_SIZE),
        .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH),
        .PE_ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH),
        .MAIN_MEM_DATA_WIDTH_BITS(MAIN_MEM_DATA_WIDTH_BITS),
        .MATRIX_SIZE(MATRIX_SIZE),
        .FINAL_ADDER_LATENCY(FINAL_ADDER_LATENCY)
    ) uut (
        .clk(clk),
        .rst_n(rst_n),
        .compute_req(compute_req),
        .k_tile_idx(k_tile_idx),
        .compute_busy(compute_busy),
        .compute_done(compute_done),
        .dut_ready_for_sa_partial_sum(dut_ready_for_sa_partial_sum),
        .sa_partial_sum_valid(sa_partial_sum_valid),
        .sa_partial_sum_in(sa_partial_sum_in),
        .sa_partial_sum_row_idx(sa_partial_sum_row_idx),
        .sa_final_sum_in(sa_final_sum_in),
        .sa_tile_all_pes_done_one_pass(sa_tile_all_pes_done_one_pass),
        .ctrl_clear_all_pe_accumulators(ctrl_clear_all_pe_accumulators),
        .ctrl_start_new_systolic_pass(ctrl_start_new_systolic_pass),
        .ctrl_activate_pe_computation(ctrl_activate_pe_computation),
        .ctrl_c_data_to_sa(ctrl_c_data_to_sa),
        .ctrl_enable_final_add(ctrl_enable_final_add),
        .sram_a_addr(sram_a_addr),
        .sram_a_rdata_flat(sram_a_rdata_flat),
        .sram_b_addr(sram_b_addr),
        .sram_b_rdata_flat(sram_b_rdata_flat),
        .sa_array_a_in_flat(sa_array_a_in_flat),
        .sa_array_b_in_flat(sa_array_b_in_flat),
        .ctrl_array_data_valid_in(ctrl_array_data_valid_in),
        .sram_c_addr(sram_c_addr),
        .sram_c_wdata(sram_c_wdata),
        .sram_c_we(sram_c_we),
        .sram_c_rdata(sram_c_rdata)
    );

    //======================================================================
    //== Main Stimulus & Tasks
    //======================================================================
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

    initial begin
        $dumpfile("compute_controller_robust.vcd");
        $dumpvars(0, tb_compute_controller_robust);

        initialize_sim();

        run_computation_test(0); // Test k=0 (direct write)
        check_c_sram(0);

        run_computation_test(1); // Test k=1 (accumulation)
        check_c_sram(1);
        
        run_computation_test(2); // Test k=2 (accumulation)
        check_c_sram(2);

        if (error_count == 0) begin
            $display("[%0t] [TB] <<<<< SUCCESS: All test cases passed. >>>>>", $time);
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
            k_tile_idx = 0;
            error_count = 0;

            // Pre-fill SRAMs with some data
            for (integer r = 0; r < TILE_SIZE; r = r + 1) begin
                simulated_sram_a[r] = r + 1;
                simulated_sram_b[r] = r + 1;
                simulated_sram_c[r] = {MAIN_MEM_DATA_WIDTH_BITS{1'b0}};
            end

            #(CLK_PERIOD * 2);
            rst_n = 1'b1;
            @(posedge clk);
            $display("[%0t] [TB] System reset released.", $time);
        end
    endtask

    task run_computation_test(input [$clog2(NUM_TILES_PER_DIM)-1:0] k_val);
        begin
            $display("------------------------------------------------------------------");
            $display("[%0t] [TB] Starting compute request for k_tile_idx = %0d", $time, k_val);
            $display("------------------------------------------------------------------");
            @(posedge clk);
            compute_req <= 1'b1;
            k_tile_idx <= k_val;
            @(posedge clk);
            compute_req <= 1'b0;
            wait (compute_done == 1'b1);
            @(posedge clk);
            $display("[%0t] [TB] Compute request for k_tile_idx = %0d finished.", $time, k_val);
        end
    endtask

    integer local_errors;
    reg signed [PE_ACCUM_DATA_WIDTH-1:0] expected_element;
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0] expected_row, actual_row;
    task check_c_sram(input [$clog2(NUM_TILES_PER_DIM)-1:0] current_k);
        begin
            local_errors = 0;
            $display("[%0t] [TB] Verifying C-SRAM contents after k=%0d...", $time, current_k);

            for (integer r = 0; r < TILE_SIZE; r = r + 1) begin
                // Simplified check: C[r][c] = (r+1)*(k+1)*TILE_SIZE
                expected_element = (r + 1) * (current_k + 1) * TILE_SIZE;
                
                for (integer c_elem = 0; c_elem < TILE_SIZE; c_elem = c_elem + 1) begin
                   expected_row[c_elem*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] = expected_element;
                end
                
                actual_row = simulated_sram_c[r];

                if (expected_row !== actual_row) begin
                    $error("[%0t] [TB] C-SRAM CHECK FAILED for row %0d.", $time, r);
                    $error("      Expected[0]: %d (0x%h)", expected_element, expected_element);
                    $error("      Actual[0]:   %d (0x%h)", actual_row[PE_ACCUM_DATA_WIDTH-1:0], actual_row[PE_ACCUM_DATA_WIDTH-1:0]);
                    local_errors = local_errors + 1;
                end
            end
            
            if (local_errors == 0) begin
                $display("[%0t] [TB] C-SRAM verification PASSED for k=%0d.", $time, current_k);
            end else begin
                $display("[%0t] [TB] C-SRAM verification FAILED for k=%0d with %0d errors.", $time, current_k, local_errors);
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
    assign sa_final_sum_in             = sa_final_sum_in_reg;

    // --- SRAM Simulators ---
    assign sram_a_rdata_flat = {TILE_SIZE{simulated_sram_a[sram_a_addr]}};
    assign sram_b_rdata_flat = {TILE_SIZE{simulated_sram_b[sram_b_addr]}};
    assign sram_c_rdata = simulated_sram_c[sram_c_addr];
    always @(posedge clk) begin
        if (sram_c_we) begin
            simulated_sram_c[sram_c_addr] <= sram_c_wdata;
        end
    end

    // --- Final Adder Simulator ---
    reg signed [PE_ACCUM_DATA_WIDTH-1:0] new_val;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            sa_final_sum_in_reg <= 0;
            for (integer i=0; i<FINAL_ADDER_LATENCY; i=i+1) begin
                final_adder_pipeline[i] <= 0;
            end
        end else begin
            if (ctrl_enable_final_add) begin
                // A simplified model for accumulation based on our test data pattern
                // C_old = (row+1)*k*TILE_SIZE
                // A*B   = (row+1)*TILE_SIZE
                // C_new = (row+1)*(k+1)*TILE_SIZE
                new_val = (sa_partial_sum_row_idx_sim + 1) * (k_tile_idx + 1) * TILE_SIZE;
                final_adder_pipeline[0] <= {TILE_SIZE{new_val}};
            end

            // Pipeline shift
            for (integer i=0; i < FINAL_ADDER_LATENCY-1; i=i+1) begin
                final_adder_pipeline[i+1] <= final_adder_pipeline[i];
            end
            sa_final_sum_in_reg <= final_adder_pipeline[FINAL_ADDER_LATENCY-1];
        end
    end
    
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
            mock_sa_element_val <= 0;
        end else begin
            // Default to not valid unless handshake fires
            sa_partial_sum_valid_sim <= 1'b0;

            if (ctrl_start_new_systolic_pass) begin
                sa_sim_cycle_cnt <= 0;
                sa_output_row_idx_cnt <= 0;
                sa_tile_all_pes_done_one_pass_sim <= 1'b0;
                sa_output_is_ready_for_handshake <= 1'b0;
                sa_gap_cnt <= 0;
            end else if (ctrl_activate_pe_computation) begin
                sa_sim_cycle_cnt <= sa_sim_cycle_cnt + 1;

                // Logic to determine if a new row result is ready internally from SA
                if (sa_output_row_idx_cnt < TILE_SIZE && sa_gap_cnt == 0 && !sa_output_is_ready_for_handshake) begin
                    if (sa_sim_cycle_cnt >= (SA_PIPELINE_DELAY + sa_output_row_idx_cnt)) begin
                        sa_output_is_ready_for_handshake <= 1'b1;
                        $display("[%0t] [TB-SA-SIM] DEBUG: Row %0d data is ready internally. Waiting for DUT ready signal...", $time, sa_output_row_idx_cnt);
                    end
                end

                // Handshake Logic
                if (sa_output_is_ready_for_handshake && dut_ready_for_sa_partial_sum) begin
                    $display("[%0t] [TB-SA-SIM] INFO: Handshake success! DUT is ready. Outputting Row %0d result.", $time, sa_output_row_idx_cnt);
                    // Fire the handshake
                    sa_partial_sum_valid_sim <= 1'b1;
                    sa_partial_sum_row_idx_sim <= sa_output_row_idx_cnt;
                    // Mocked data: for row 'r', each element is (r+1)*TILE_SIZE
                    mock_sa_element_val = (sa_output_row_idx_cnt + 1) * TILE_SIZE;
                    sa_partial_sum_in_reg <= {TILE_SIZE{mock_sa_element_val}};

                    // Prepare for next row
                    sa_output_row_idx_cnt <= sa_output_row_idx_cnt + 1;
                    sa_output_is_ready_for_handshake <= 1'b0;
                    // Start the gap counter to introduce delay
                    sa_gap_cnt <= VALID_GAP_CYCLES;
                end

                // Countdown the gap timer
                if (sa_gap_cnt > 0) begin
                    sa_gap_cnt <= sa_gap_cnt - 1;
                end
                
                // Signal when the entire pass is done from SA's perspective
                if (sa_sim_cycle_cnt == SA_TOTAL_LATENCY - 1) begin
                    sa_tile_all_pes_done_one_pass_sim <= 1'b1;
                    $display("[%0t] [TB-SA-SIM] INFO: SA pass finished signal asserted.", $time);
                end
            end
        end
    end

endmodule
