`timescale 1ns / 1ps

// 文件名应为 systolic_array_tb.v
module systolic_array_tb; // 模块名与文件名一致 (原为 systolic_array_tb_os)

    // Parameters for the DUT
    localparam TB_SIZE = 16; // <<<<<<<<<<<<<<<<<<<<<<<<<<< 修改为 16
    localparam TB_DATA_WIDTH = 16;

    // Testbench Parameters
    localparam CLK_PERIOD = 10;
    localparam STRING_MAX_LEN = 256;

    // DUT Interface Signals (matching new systolic_array.v)
    reg                               clk_tb;
    reg                               rst_n_tb;
    reg                               clear_all_pe_accumulators_tb;
    reg                               activate_pe_computation_tb;
    // 这些总线宽度现在需要根据 TB_SIZE=16 来调整
    reg  [TB_SIZE*TB_DATA_WIDTH-1:0]  array_a_in_tb;
    reg  [TB_SIZE*TB_DATA_WIDTH-1:0]  array_b_in_tb;
    reg  [$clog2(TB_SIZE)-1:0]        select_output_row_idx_tb; // $clog2(16) = 4
    reg                               enable_tile_row_output_tb;
    wire [TB_SIZE*TB_DATA_WIDTH-1:0]  array_a_out_tb;
    wire [TB_SIZE*TB_DATA_WIDTH-1:0]  array_b_out_tb;
    wire [TB_SIZE*TB_DATA_WIDTH-1:0]  tile_row_result_out_tb;
    wire                              tile_row_result_valid_tb;
    wire                              tile_all_pes_done_one_pass_tb;
    wire                              tile_had_nan_tb;
    wire                              tile_had_inf_tb;
    reg                               accelerator_is_computing_tb;

    // BF16 Constants
    localparam BF16_POS_ZERO   = 16'h0000;
    localparam BF16_POS_ONE    = 16'h3F80;
    localparam BF16_POS_TWO    = 16'h4000;

    integer test_count = 0;
    integer pass_count = 0;
    integer fail_count = 0;
    integer r, c, k_wave;
    integer r_out_idx, c_fill;
    integer k_cycle; // 已在上一版 TB 中添加

    // Test data matrices (BF16 format) - 现在是 16x16
    reg [TB_DATA_WIDTH-1:0] matrix_a_tb [TB_SIZE-1:0][TB_SIZE-1:0];
    reg [TB_DATA_WIDTH-1:0] matrix_b_tb [TB_SIZE-1:0][TB_SIZE-1:0];
    reg [TB_DATA_WIDTH-1:0] matrix_c_golden_bf16 [TB_SIZE-1:0][TB_SIZE-1:0];

    // Temporary variables for DUT output checking
    reg [TB_SIZE*TB_DATA_WIDTH-1:0] expected_row_data_bf16;
    reg [STRING_MAX_LEN*8-1:0]      testname_s;


    // Instantiate Systolic Array DUT
    systolic_array #(
        .SIZE(TB_SIZE),             // <<<<<<<<<<<<<<<<<<<<<<<<<<< 传递 TB_SIZE (16)
        .DATA_WIDTH(TB_DATA_WIDTH)
    ) dut_tile (
        .clk(clk_tb),
        .rst_n(rst_n_tb),
        .clear_all_pe_accumulators(clear_all_pe_accumulators_tb),
        .activate_pe_computation(activate_pe_computation_tb),
        .array_a_in(array_a_in_tb),
        .array_b_in(array_b_in_tb),
        .select_output_row_idx(select_output_row_idx_tb),
        .enable_tile_row_output(enable_tile_row_output_tb),
        .array_a_out(array_a_out_tb),
        .array_b_out(array_b_out_tb),
        .tile_row_result_out(tile_row_result_out_tb),
        .tile_row_result_valid(tile_row_result_valid_tb),
        .tile_all_pes_done_one_pass(tile_all_pes_done_one_pass_tb),
        .tile_had_nan(tile_had_nan_tb),
        .tile_had_inf(tile_had_inf_tb),
        .accelerator_is_computing(accelerator_is_computing_tb)
    );

    always #(CLK_PERIOD/2) clk_tb = ~clk_tb;

    // real_to_bfloat16 task (保持不变)
    task real_to_bfloat16;
        input real r_val; output reg [15:0] bf16_val;
        // ... (内容与你之前提供的版本相同) ...
        reg s; reg [7:0] biased_exp; reg [6:0] frac_val;
        real abs_r_val; real temp_frac; integer exp_int; integer i;
        begin
            s=(r_val<0.0); abs_r_val=s?-r_val:r_val;
            if(abs_r_val==0.0)begin bf16_val={s,8'h00,7'h00};disable real_to_bfloat16;end
            if(r_val==1.23456789e+50)begin bf16_val=16'h7FC0;disable real_to_bfloat16;end // NaN marker
            if(abs_r_val>3.389e38)begin bf16_val={s,8'hFF,7'h00};disable real_to_bfloat16;end // Inf
            exp_int=0;if(abs_r_val>=1.0)begin while(abs_r_val>=2.0)begin abs_r_val=abs_r_val/2.0;exp_int=exp_int+1;end end else begin : subnormal_loop_sa_tb_actual
            while(abs_r_val<1.0 && exp_int > -126)begin abs_r_val=abs_r_val*2.0;exp_int=exp_int-1;if(abs_r_val==0.0)disable subnormal_loop_sa_tb_actual;end end
            if(abs_r_val==0.0)begin bf16_val={s,8'h00,7'h00};disable real_to_bfloat16;end
            biased_exp=exp_int+127;
            if(biased_exp>=8'hFF)begin bf16_val={s,8'hFF,7'h00};disable real_to_bfloat16;end
            if(biased_exp<=8'h00 && !(abs_r_val > 0.0 && exp_int == -127)) begin bf16_val={s,8'h00,7'h00};disable real_to_bfloat16;end // FTZ for most cases
            temp_frac=abs_r_val;
            if(exp_int+127 > 0) temp_frac = abs_r_val - 1.0;

            frac_val=7'b0;
            for(i=6;i>=0;i=i-1)begin temp_frac=temp_frac*2.0;if(temp_frac>=1.0)begin frac_val[i]=1'b1;temp_frac=temp_frac-1.0;end end
            if (biased_exp <= 8'h00) biased_exp = 8'h00;
            bf16_val={s,biased_exp,frac_val};
        end
    endtask

    // apply_main_controls 任务 (保持不变)
    task apply_main_controls;
        input clear_acc, activate_comp;
        // ... (内容与你之前提供的版本相同) ...
        begin
            clear_all_pe_accumulators_tb = clear_acc;
            activate_pe_computation_tb   = activate_comp;
        end
    endtask

    // drive_wavefronts 任务 (基本不变，循环边界 TB_SIZE 已经更新)
    task drive_wavefronts;
        input integer current_k_wave;
        // ... (内容与你之前提供的版本相同) ...
        integer r_drive, c_drive; // 确保这些是 integer
        begin
            for (r_drive = 0; r_drive < TB_SIZE; r_drive = r_drive + 1) begin
                array_a_in_tb[r_drive*TB_DATA_WIDTH +: TB_DATA_WIDTH] = matrix_a_tb[r_drive][current_k_wave];
            end
            for (c_drive = 0; c_drive < TB_SIZE; c_drive = c_drive + 1) begin
                array_b_in_tb[c_drive*TB_DATA_WIDTH +: TB_DATA_WIDTH] = matrix_b_tb[current_k_wave][c_drive];
            end
            #(CLK_PERIOD);
        end
    endtask

    // check_tile_outputs 任务 (基本不变，总线宽度 TB_SIZE*TB_DATA_WIDTH 已经更新)
    task check_tile_outputs;
        input [TB_SIZE*TB_DATA_WIDTH-1:0] exp_row_res_data;
        input exp_valid_signal, exp_all_done_signal, exp_nan_flag, exp_inf_flag;
        input [STRING_MAX_LEN*8-1:0] current_testname;
        // ... (内容与你之前提供的版本相同) ...
        reg check_passed_local; // 确保是 reg
        begin
            test_count = test_count + 1;
            check_passed_local = 1'b1;

            if (enable_tile_row_output_tb) begin
                if (tile_row_result_out_tb !== exp_row_res_data) begin
                    $display("Test #%0d: %s - FAIL (tile_row_result_out)", test_count, current_testname);
                    $display("  Expected data: 0x%h", exp_row_res_data);
                    $display("  Actual data  : 0x%h", tile_row_result_out_tb);
                    check_passed_local = 1'b0;
                end
                if (tile_row_result_valid_tb !== exp_valid_signal) begin
                    $display("Test #%0d: %s - FAIL (tile_row_result_valid)", test_count, current_testname);
                    $display("  Expected valid: %b, Actual valid: %b", exp_valid_signal, tile_row_result_valid_tb);
                    check_passed_local = 1'b0;
                end
            end else if (exp_valid_signal == 1'b1) begin
                 $display("Test #%0d: %s - FAIL (enable_tile_row_output_tb is LOW but expected valid)", test_count, current_testname);
                 check_passed_local = 1'b0;
            end

            if (tile_all_pes_done_one_pass_tb !== exp_all_done_signal) begin
                $display("Test #%0d: %s - FAIL (tile_all_pes_done_one_pass)", test_count, current_testname);
                $display("  Expected all_done: %b, Actual all_done: %b", exp_all_done_signal, tile_all_pes_done_one_pass_tb);
                check_passed_local = 1'b0;
            end
            if (tile_had_nan_tb !== exp_nan_flag) begin
                $display("Test #%0d: %s - FAIL (tile_had_nan)", test_count, current_testname);
                $display("  Expected NaN: %b, Actual NaN: %b", exp_nan_flag, tile_had_nan_tb);
                check_passed_local = 1'b0;
            end
            if (tile_had_inf_tb !== exp_inf_flag) begin
                $display("Test #%0d: %s - FAIL (tile_had_inf)", test_count, current_testname);
                $display("  Expected Inf: %b, Actual Inf: %b", exp_inf_flag, tile_had_inf_tb);
                check_passed_local = 1'b0;
            end

            if (check_passed_local) begin
                $display("Test #%0d: %s - PASS", test_count, current_testname);
                pass_count = pass_count + 1;
            end else begin
                fail_count = fail_count + 1;
            end
        end
    endtask

    integer wait_cycles_after_input; // 移到 initial 块外部，使其成为模块级变量

    // Main test sequence
    initial begin
        clk_tb = 0;
        rst_n_tb = 0;
        clear_all_pe_accumulators_tb = 0;
        activate_pe_computation_tb = 0;
        array_a_in_tb = 0;
        array_b_in_tb = 0;
        select_output_row_idx_tb = 0;
        enable_tile_row_output_tb = 0;
        accelerator_is_computing_tb = 0;

        $display("==========================================================");
        $display("Starting Systolic Array Testbench (Output Stationary)");
        $display("TB_SIZE = %0d  (DUT SIZE will match this)", TB_SIZE); // 明确说明
        $display("==========================================================");

        // 1. Initialize Matrices A and B, Calculate Golden C
        // A=diag(2), B=diag(1) for TB_SIZE x TB_SIZE (now 16x16)
        for (r = 0; r < TB_SIZE; r = r + 1) begin
            for (c = 0; c < TB_SIZE; c = c + 1) begin
                if (r == c) begin
                    real_to_bfloat16(2.0, matrix_a_tb[r][c]);
                    real_to_bfloat16(1.0, matrix_b_tb[r][c]);
                    real_to_bfloat16(2.0, matrix_c_golden_bf16[r][c]); // C[r][r] = 2.0
                end else begin
                    matrix_a_tb[r][c] = BF16_POS_ZERO;
                    matrix_b_tb[r][c] = BF16_POS_ZERO;
                    matrix_c_golden_bf16[r][c] = BF16_POS_ZERO;
                end
            end
        end
        $display(" Matrices Initialized for %0dx%0d. A=diag(2), B=diag(1), Expected C=diag(2).", TB_SIZE, TB_SIZE);


        // 2. Reset DUT
        #(CLK_PERIOD * 2);
        rst_n_tb = 1;
        apply_main_controls(0,0);
        enable_tile_row_output_tb = 0;
        #(CLK_PERIOD);
        $sformat(testname_s, "Initial Reset State");
        check_tile_outputs({(TB_SIZE*TB_DATA_WIDTH){1'bz}}, 0, 0, 0, 0, testname_s);


        // 3. Perform Matrix Multiplication
        $display("\n--- Phase: Matrix Multiplication (%0dx%0d) ---", TB_SIZE, TB_SIZE);
        accelerator_is_computing_tb = 1;
        apply_main_controls(1,0); // Pulse clear
        #(CLK_PERIOD);
        apply_main_controls(0,1); // De-assert clear, assert activate

        for (k_wave = 0; k_wave < TB_SIZE; k_wave = k_wave + 1) begin
            // $display("  Driving wavefront k_wave = %0d", k_wave); // 可以取消注释以跟踪
            drive_wavefronts(k_wave);
        end

        array_a_in_tb = 0; // Stop feeding new data after all k_waves
        array_b_in_tb = 0;

        // Wait for computation to complete.
        // For output stationary C[r][c] = sum A[r][k]*B[k][c]
        // A[r][k] reaches PE[r][c] at time k (wavefront) + r (row skew) + c (col propagation in PE row)
        // B[k][c] reaches PE[r][c] at time k (wavefront) + c (col skew) + r (row propagation in PE col)
        // Last useful data (k=SIZE-1) reaches PE[SIZE-1][SIZE-1] at approx.
        // (SIZE-1) for k_wave + (SIZE-1) for row_skew + (SIZE-1) for col_prop_A
        // (SIZE-1) for k_wave + (SIZE-1) for col_skew + (SIZE-1) for row_prop_B
        // So, around 3*(SIZE-1) cycles for the last data pair A[S-1][S-1] and B[S-1][S-1] to meet at PE[S-1][S-1].
        // Then PE needs SIZE cycles for its internal accumulation.
        // Then 2 more cycles for result pipeline in PE.
        // Total approx = 3*(SIZE-1) + SIZE + 2 = 4*SIZE - 1.
        // We have spent TB_SIZE cycles for inputting.
        // Need to wait approx (3*TB_SIZE - 1) more cycles.
        // A simpler, more generous upper bound: The total pipeline depth is roughly
        // (skew_A_max + prop_A_max) OR (skew_B_max + prop_B_max) + PE_accumulation_cycles + PE_output_pipeline
        // ( (SIZE-1) + (SIZE-1) ) + SIZE + 2 = 2*SIZE - 2 + SIZE + 2 = 3*SIZE.
        // Since we already spent SIZE cycles for input, wait 2*SIZE more.
        wait_cycles_after_input = 2 * TB_SIZE + TB_SIZE/2; // Increased margin further for 16x16
        $display("  All wavefronts sent. Waiting %0d cycles for computation to complete.", wait_cycles_after_input);
        for (k_cycle = 0; k_cycle < wait_cycles_after_input; k_cycle = k_cycle + 1) begin
            #(CLK_PERIOD);
        end

        apply_main_controls(0,0); // Deactivate computation
        accelerator_is_computing_tb = 0;
        #(CLK_PERIOD);

        $sformat(testname_s, "After Computation, Before Readout");
        check_tile_outputs({(TB_SIZE*TB_DATA_WIDTH){1'bz}}, 0, 1'b1, 0, 0, testname_s); // Expect all PEs done

        // 4. Readout Results
        $display("\n--- Phase: Readout Results (%0dx%0d) ---", TB_SIZE, TB_SIZE);
        for (r_out_idx = 0; r_out_idx < TB_SIZE; r_out_idx = r_out_idx + 1) begin
            select_output_row_idx_tb = r_out_idx;
            enable_tile_row_output_tb = 1;
            #(CLK_PERIOD);

            for (c_fill = 0; c_fill < TB_SIZE; c_fill = c_fill + 1) begin
                expected_row_data_bf16[c_fill*TB_DATA_WIDTH +: TB_DATA_WIDTH] = matrix_c_golden_bf16[r_out_idx][c_fill];
            end

            $sformat(testname_s, "Readout Row %0d", r_out_idx);
            check_tile_outputs(expected_row_data_bf16, 1'b1, 1'b1, 0, 0, testname_s);

            enable_tile_row_output_tb = 0;
            // #(CLK_PERIOD); // Optional delay, not strictly needed if next cycle is another readout setup
        end
        select_output_row_idx_tb = 0;


        $display("----------------------------------------------------------");
        $display("Systolic Array (Output Stationary) Test Summary:");
        $display("Total Tests: %0d", test_count);
        $display("Passed:      %0d", pass_count);
        $display("Failed:      %0d", fail_count);
        $display("==========================================================");

        if (fail_count > 0) begin $display("NOTE: Systolic Array TB (OS) has failures!"); end
        else begin $display("Systolic Array TB (OS): All tests passed!"); end
        $finish;
    end

endmodule