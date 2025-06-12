`timescale 1ns / 1ps

module bfloat16_arith_tb;

    // Parameters
    localparam CLK_PERIOD = 10; // ns
    localparam STRING_MAX_LEN = 256; 
    localparam BF16_POS_MAX_NORM   = 16'h7F7F; // +Max Normal  (S=0, E=FE, F=7F)
    localparam BF16_NEG_MAX_NORM   = 16'hFF7F; // -Max Normal  (S=1, E=FE, F=7F)
    localparam BF16_POS_MIN_NORM   = 16'h0080; // +Min Normal  (S=0, E=01, F=00)
    localparam BF16_NEG_MIN_NORM   = 16'h8080; // -Min Normal  (S=1, E=01, F=00)
    localparam BF16_POS_TWO        = 16'h4000; // +2.0         (S=0, E=80, F=00)
    localparam BF16_NEG_TWO        = 16'hC000; // -2.0         (S=1, E=80, F=00)
    localparam BF16_POS_HALF       = 16'h3F00; // +0.5         (S=0, E=7E, F=00)
    localparam BF16_POS_ONE        = 16'h3F80; // +1.0         (S=0, E=7F, F=00)
    localparam BF16_NEG_ONE        = 16'hBF80; // -1.0         (S=1, E=7F, F=00)
    localparam BF16_POS_ZERO       = 16'h0000;
    localparam BF16_NEG_ZERO       = 16'h8000; // Though often treated as +0
    localparam BF16_POS_INF        = 16'h7F80;
    localparam BF16_NEG_INF        = 16'hFF80;
    localparam BF16_QNaN           = 16'h7FC0; // Quiet NaN (example)
    localparam BF16_ONE_PLUS_EPS   = 16'h3F81;
    
    // Testbench signals
    reg  [15:0] tb_num1;
    reg  [15:0] tb_num2;
    wire [15:0] tb_mul_result;
    wire        tb_mul_is_NaN;
    wire        tb_mul_is_infinity;
    wire        tb_mul_is_zero;

    wire [15:0] tb_add_result;
    wire        tb_add_is_NaN;
    wire        tb_add_is_infinity;
    wire        tb_add_is_zero;

    reg  [15:0] tb_expected_result;
    reg         tb_expected_is_NaN;    
    reg         tb_expected_is_infinity; 
    reg         tb_expected_is_zero;     

    integer test_count = 0;
    integer pass_count = 0;
    integer fail_count = 0;

    bfloat16_multiplier dut_mul (
        .num1(tb_num1),
        .num2(tb_num2),
        .result(tb_mul_result),
        .is_NaN(tb_mul_is_NaN),
        .is_infinity(tb_mul_is_infinity),
        .is_zero(tb_mul_is_zero)
    );

    bfloat16_adder dut_add (
        .num1(tb_num1),
        .num2(tb_num2),
        .result(tb_add_result),
        .is_NaN(tb_add_is_NaN),
        .is_infinity(tb_add_is_infinity),
        .is_zero(tb_add_is_zero)
    );

    task real_to_bfloat16;
        input real r_val;
        output reg [15:0] bf16_val;
        reg s;
        reg [7:0] biased_exp;
        reg [6:0] frac_val;
        real abs_r_val;
        real temp_frac;
        integer exp_int;
        integer i;
        begin
            s = (r_val < 0.0);
            abs_r_val = s ? -r_val : r_val;

            if (abs_r_val == 0.0) begin
                bf16_val = {s, 8'h00, 7'h00};
                disable real_to_bfloat16; 
            end

            if (r_val == 1.23456789e+50) begin
                bf16_val = 16'h7FC0; 
                disable real_to_bfloat16;
            end
            if (abs_r_val > 3.389e38) begin
                bf16_val = {s, 8'hFF, 7'h00}; 
                disable real_to_bfloat16;
            end

            exp_int = 0;
            if (abs_r_val >= 1.0) begin
                while (abs_r_val >= 2.0) begin
                    abs_r_val = abs_r_val / 2.0;
                    exp_int = exp_int + 1;
                end
            end else begin : subnormal_loop 
                while (abs_r_val < 1.0 && exp_int > -126) begin
                    abs_r_val = abs_r_val * 2.0;
                    exp_int = exp_int - 1;
                    if (abs_r_val == 0.0) begin
                        disable subnormal_loop; 
                    end
                end
            end
            
            if (abs_r_val == 0.0) begin
                bf16_val = {s, 8'h00, 7'h00};
                disable real_to_bfloat16;
            end

            biased_exp = exp_int + 127;

            if (biased_exp >= 8'hFF) begin
                bf16_val = {s, 8'hFF, 7'h00};
                disable real_to_bfloat16;
            end
            if (biased_exp <= 8'h00) begin
                bf16_val = {s, 8'h00, 7'h00};
                disable real_to_bfloat16;
            end

            temp_frac = abs_r_val - 1.0;
            frac_val = 7'b0;
            for (i = 6; i >= 0; i = i - 1) begin
                temp_frac = temp_frac * 2.0;
                if (temp_frac >= 1.0) begin
                    frac_val[i] = 1'b1;
                    temp_frac = temp_frac - 1.0;
                end
            end
            bf16_val = {s, biased_exp, frac_val};
        end
    endtask

    task bfloat16_to_string_reg;
        input [15:0] val;
        output reg [STRING_MAX_LEN*8-1:0] s_out;
        reg [7:0] sign_char_reg; 
        reg [23:0] type_str_reg; 
        reg [7:0] c6, c5, c4, c3, c2, c1, c0; // CORRECTED: These are 8-bit to hold ASCII chars
        begin 
            if (val[15]) sign_char_reg = "-"; else sign_char_reg = "+";
            s_out = ""; 

            if (val[14:7] == 8'hFF) begin
                if (val[6:0] == 7'h0) type_str_reg = "Inf"; else type_str_reg = "NaN";
                $sformat(s_out, "%s%s (0x%4h)", sign_char_reg, type_str_reg, val);
            end else if (val[14:7] == 8'h00 && val[6:0] == 7'h0) begin
                type_str_reg = "Zero";
                $sformat(s_out, "%s%s (0x%4h)", sign_char_reg, type_str_reg, val);
            end else if (val[14:7] == 8'h00 && val[6:0] != 7'h0) begin
                type_str_reg = "Subnormal(FTZ)";
                $sformat(s_out, "%s%s (Exp:0x%2h, Frac:0x%2h) => maps to Zero (0x%4h)",
                              sign_char_reg, type_str_reg, val[14:7], val[6:0], {val[15], 15'h0});
            end else begin 
                c6 = val[6] ? 8'h31 : 8'h30; 
                c5 = val[5] ? 8'h31 : 8'h30;
                c4 = val[4] ? 8'h31 : 8'h30;
                c3 = val[3] ? 8'h31 : 8'h30;
                c2 = val[2] ? 8'h31 : 8'h30;
                c1 = val[1] ? 8'h31 : 8'h30;
                c0 = val[0] ? 8'h31 : 8'h30;
                // Using %d for exponent val[14:7] as it's an integer value
                $sformat(s_out, "%s1.%c%c%c%c%c%c%c * 2^(%d-127) (S:%b E:0x%2h F_bits:0x%2h) Raw:0x%4h",
                              sign_char_reg, c6,c5,c4,c3,c2,c1,c0,
                              val[14:7], val[15], val[14:7], val[6:0], val);
            end
        end
    endtask

    task run_test;
        input [STRING_MAX_LEN*8-1:0] test_name;
        input [3*8-1:0] op_type; 
        input real r_in1, r_in2;
        input real r_exp_val;
        input [15:0] direct_exp_bf16;
        input reg use_direct_exp; 
        reg [STRING_MAX_LEN*8-1:0] s_in1_reg, s_in2_reg, s_res_reg, s_exp_reg;
        reg [15:0] actual_result_reg;
        reg actual_is_NaN_reg, actual_is_infinity_reg, actual_is_zero_reg;
        reg test_passed_reg;
        begin
            test_count = test_count + 1;
            $display("------------------------------------------------------");
            $display("Test #%0d: %s (%s)", test_count, test_name, op_type);

            real_to_bfloat16(r_in1, tb_num1);
            real_to_bfloat16(r_in2, tb_num2);

            bfloat16_to_string_reg(tb_num1, s_in1_reg);
            bfloat16_to_string_reg(tb_num2, s_in2_reg);
            $display("Input 1: %s (%f)", s_in1_reg, r_in1);
            $display("Input 2: %s (%f)", s_in2_reg, r_in2);

            if (use_direct_exp) tb_expected_result = direct_exp_bf16;
            else real_to_bfloat16(r_exp_val, tb_expected_result);
            
            tb_expected_is_NaN = (tb_expected_result[14:7] == 8'hFF && tb_expected_result[6:0] != 7'h0);
            tb_expected_is_infinity = (tb_expected_result[14:7] == 8'hFF && tb_expected_result[6:0] == 7'h0);
            tb_expected_is_zero = (tb_expected_result[14:0] == 15'h0); 

            #CLK_PERIOD;

            if (op_type == "MUL") begin
                actual_result_reg = tb_mul_result;
                actual_is_NaN_reg = tb_mul_is_NaN;
                actual_is_infinity_reg = tb_mul_is_infinity;
                actual_is_zero_reg = tb_mul_is_zero;
            end else if (op_type == "ADD") begin
                actual_result_reg = tb_add_result;
                actual_is_NaN_reg = tb_add_is_NaN;
                actual_is_infinity_reg = tb_add_is_infinity;
                actual_is_zero_reg = tb_add_is_zero;
            end else begin
                $display("ERROR: Unknown op_type '%s'", op_type);
                fail_count = fail_count + 1;
                disable run_test; 
            end

            bfloat16_to_string_reg(actual_result_reg, s_res_reg);
            bfloat16_to_string_reg(tb_expected_result, s_exp_reg);
            $display("Actual  : %s", s_res_reg);
            $display("Expected: %s", s_exp_reg);

            test_passed_reg = 1'b1;
            if (actual_result_reg !== tb_expected_result) begin
                if (! ( (tb_expected_result[14:0] == 15'h0) && (actual_result_reg[14:0] == 15'h0) ) ) begin
                     $display("MISMATCH: Result data. Actual: 0x%h, Expected: 0x%h", actual_result_reg, tb_expected_result);
                     test_passed_reg = 1'b0;
                end
            end
            if (actual_is_NaN_reg !== tb_expected_is_NaN) begin
                $display("MISMATCH: is_NaN flag. Actual: %b, Expected: %b", actual_is_NaN_reg, tb_expected_is_NaN);
                test_passed_reg = 1'b0;
            end
            if (actual_is_infinity_reg !== tb_expected_is_infinity) begin
                $display("MISMATCH: is_infinity flag. Actual: %b, Expected: %b", actual_is_infinity_reg, tb_expected_is_infinity);
                test_passed_reg = 1'b0;
            end
            if (actual_is_zero_reg !== tb_expected_is_zero) begin
                $display("MISMATCH: is_zero flag. Actual: %b, Expected: %b", actual_is_zero_reg, tb_expected_is_zero);
                test_passed_reg = 1'b0;
            end

            if (test_passed_reg) begin $display("Status: PASS"); pass_count = pass_count + 1; end
            else begin $display("Status: FAIL"); fail_count = fail_count + 1; end
        end
    endtask

    task run_test_direct_bf16;
        input [STRING_MAX_LEN*8-1:0] test_name;
        input [3*8-1:0] op_type; 
        input [15:0] bf16_in1, bf16_in2; // Direct BF16 inputs
        input [15:0] expected_bf16_result;
        input reg expected_NaN_flag;
        input reg expected_Inf_flag;
        input reg expected_Zero_flag;

        // Local variables
        reg [STRING_MAX_LEN*8-1:0] s_in1_reg, s_in2_reg, s_res_reg, s_exp_reg;
        reg [15:0] actual_result_reg;
        reg actual_is_NaN_reg, actual_is_infinity_reg, actual_is_zero_reg;
        reg test_passed_reg;
        begin
            test_count = test_count + 1;
            $display("------------------------------------------------------");
            $display("Test #%0d: %s (%s) [Direct BF16]", test_count, test_name, op_type);

            tb_num1 = bf16_in1;
            tb_num2 = bf16_in2;

            bfloat16_to_string_reg(tb_num1, s_in1_reg);
            bfloat16_to_string_reg(tb_num2, s_in2_reg);
            $display("Input 1: %s (0x%4h)", s_in1_reg, tb_num1);
            $display("Input 2: %s (0x%4h)", s_in2_reg, tb_num2);

            tb_expected_result      = expected_bf16_result;
            tb_expected_is_NaN      = expected_NaN_flag;
            tb_expected_is_infinity = expected_Inf_flag;
            tb_expected_is_zero     = expected_Zero_flag;
            
            #CLK_PERIOD;

            if (op_type == "MUL") begin
                actual_result_reg        = tb_mul_result;
                actual_is_NaN_reg        = tb_mul_is_NaN;
                actual_is_infinity_reg   = tb_mul_is_infinity;
                actual_is_zero_reg       = tb_mul_is_zero;
            end else if (op_type == "ADD") begin
                actual_result_reg        = tb_add_result;
                actual_is_NaN_reg        = tb_add_is_NaN;
                actual_is_infinity_reg   = tb_add_is_infinity;
                actual_is_zero_reg       = tb_add_is_zero;
            end else begin
                $display("ERROR: Unknown op_type '%s'", op_type);
                fail_count = fail_count + 1;
                disable run_test_direct_bf16; 
            end

            bfloat16_to_string_reg(actual_result_reg, s_res_reg);
            bfloat16_to_string_reg(tb_expected_result, s_exp_reg);
            $display("Actual  : %s", s_res_reg);
            $display("Expected: %s", s_exp_reg);

            test_passed_reg = 1'b1;
            if (actual_result_reg !== tb_expected_result) begin
                if (! ( (tb_expected_result[14:0] == 15'h0) && (actual_result_reg[14:0] == 15'h0) ) ) begin
                     $display("MISMATCH: Result data. Actual: 0x%h, Expected: 0x%h", actual_result_reg, tb_expected_result);
                     test_passed_reg = 1'b0;
                end
            end
            if (actual_is_NaN_reg !== tb_expected_is_NaN) begin
                $display("MISMATCH: is_NaN flag. Actual: %b, Expected: %b", actual_is_NaN_reg, tb_expected_is_NaN);
                test_passed_reg = 1'b0;
            end
            if (actual_is_infinity_reg !== tb_expected_is_infinity) begin
                $display("MISMATCH: is_infinity flag. Actual: %b, Expected: %b", actual_is_infinity_reg, tb_expected_is_infinity);
                test_passed_reg = 1'b0;
            end
            if (actual_is_zero_reg !== tb_expected_is_zero) begin
                $display("MISMATCH: is_zero flag. Actual: %b, Expected: %b", actual_is_zero_reg, tb_expected_is_zero);
                test_passed_reg = 1'b0;
            end

            if (test_passed_reg) begin $display("Status: PASS"); pass_count = pass_count + 1; end
            else begin $display("Status: FAIL"); fail_count = fail_count + 1; end
        end
    endtask

    initial begin
        $display("==============================================");
        $display("Starting BFloat16 Arithmetic Testbench");
        $display("==============================================");

        $display("\n--- Testing bfloat16_multiplier ---");
        run_test("Mul: 0.0 * 5.0",         "MUL", 0.0, 5.0,   0.0,   16'h0, 0);
        run_test("Mul: -0.0 * 5.0",        "MUL", -0.0, 5.0,  -0.0,  16'h8000, 1);
        run_test("Mul: 5.0 * 0.0",         "MUL", 5.0, 0.0,   0.0,   16'h0, 0);
        run_test("Mul: Inf * 5.0",         "MUL", 3.4e38, 5.0, 3.4e38, 16'h7F80, 1); 
        run_test("Mul: 5.0 * -Inf",        "MUL", 5.0, -3.4e38, -3.4e38, 16'hFF80, 1); 
        run_test("Mul: Inf * 0.0",         "MUL", 3.4e38, 0.0, 1.23456789e+50, 16'h7FC0, 1); 
        run_test("Mul: Inf * Inf",         "MUL", 3.4e38, 3.4e38, 3.4e38, 16'h7F80, 1); 
        run_test("Mul: Inf * -Inf",        "MUL", 3.4e38, -3.4e38, -3.4e38, 16'hFF80, 1);
        run_test("Mul: NaN * 5.0",         "MUL", 1.23456789e+50, 5.0, 1.23456789e+50, 16'h7FC0, 1);
        run_test("Mul: NaN * Inf",         "MUL", 1.23456789e+50, 3.4e38, 1.23456789e+50, 16'h7FC0, 1);
        run_test("Mul: 2.0 * 3.0",         "MUL", 2.0, 3.0,   6.0,   16'h0, 0);
        run_test("Mul: -2.0 * 3.0",        "MUL", -2.0, 3.0,  -6.0,  16'h0, 0);
        run_test("Mul: -2.0 * -3.0",       "MUL", -2.0, -3.0,  6.0,   16'h0, 0);
        run_test("Mul: 0.5 * 0.25",        "MUL", 0.5, 0.25,  0.125, 16'h0, 0);
        run_test("Mul: 1.0 * 7.5",         "MUL", 1.0, 7.5,   7.5,   16'h0, 0);
        run_test("Mul: 128.0 * 2.0",       "MUL", 128.0, 2.0, 256.0, 16'h0, 0);
        run_test("Mul: 2.0e30 * 2.0e10",   "MUL", 2.0e30, 2.0e10, 3.4e38, 16'h7F80, 1); 
        run_test("Mul: 1.0e-20 * 1.0e-20", "MUL", 1.0e-20, 1.0e-20, 0.0, 16'h0000, 1); 
        run_test("Mul: 1.175e-38 * 0.5",   "MUL", 1.175e-38, 0.5, 0.0, 16'h0000, 1); 

        $display("\n--- Testing bfloat16_adder ---");
        run_test("Add: 0.0 + 5.0",         "ADD", 0.0, 5.0,    5.0,    16'h0, 0);
        run_test("Add: -0.0 + 5.0",        "ADD", -0.0, 5.0,   5.0,    16'h0, 0);
        run_test("Add: 5.0 + 0.0",         "ADD", 5.0, 0.0,    5.0,    16'h0, 0);
        run_test("Add: Inf + 5.0",         "ADD", 3.4e38, 5.0,  3.4e38,  16'h7F80, 1); 
        run_test("Add: 5.0 + (-Inf)",      "ADD", 5.0, -3.4e38, -3.4e38, 16'hFF80, 1); 
        run_test("Add: Inf + (-Inf)",      "ADD", 3.4e38, -3.4e38, 1.23456789e+50, 16'h7FC0, 1); 
        run_test("Add: Inf + Inf",         "ADD", 3.4e38, 3.4e38,  3.4e38,  16'h7F80, 1); 
        run_test("Add: NaN + 5.0",         "ADD", 1.23456789e+50, 5.0,  1.23456789e+50,  16'h7FC0, 1);
        run_test("Add: NaN + Inf",         "ADD", 1.23456789e+50, 3.4e38, 1.23456789e+50, 16'h7FC0, 1);
        run_test("Add: 2.0 + 3.0",         "ADD", 2.0, 3.0,    5.0,    16'h0, 0);
        run_test("Add: -2.0 + (-3.0)",     "ADD", -2.0, -3.0,  -5.0,   16'h0, 0);
        run_test("Add: 5.0 + (-3.0)",      "ADD", 5.0, -3.0,   2.0,    16'h0, 0);
        run_test("Add: 3.0 + (-5.0)",      "ADD", 3.0, -5.0,  -2.0,   16'h0, 0);
        run_test("Add: 3.5 + (-3.5)",      "ADD", 3.5, -3.5,   0.0,    16'h0000, 1); 
        run_test("Add: 1.0 + 0.0001",      "ADD", 1.0, 0.0001, 1.0001, 16'h0, 0); 
        run_test("Add: 12345.0 + 0.125",   "ADD", 12345.0, 0.125, 12345.125, 16'h0, 0);
        run_test("Add: 8.5 + (-8.0)",      "ADD", 8.5, -8.0,   0.5,    16'h0, 0);
        run_test("Add: 3.0e30 + 3.0e30",   "ADD", 3.0e30, 3.0e30, 6.0e30, 16'h0, 0);
        run_test("Add: 1.0078125 + 0.00390625", "ADD", 1.0078125, 0.00390625, 1.01171875, 16'h0, 0);
        run_test("Add: 0.0 + 0.0",         "ADD", 0.0, 0.0,    0.0,    16'h0, 0);
        run_test("Add: -0.0 + 0.0",        "ADD", -0.0, 0.0,   0.0,    16'h0, 0); // Expect +0
        run_test("Add: 0.0 + (-0.0)",      "ADD", 0.0, -0.0,   0.0,    16'h0, 0); // Expect +0
        run_test("Add: -0.0 + (-0.0)",     "ADD", -0.0, -0.0, -0.0,   16'h8000, 1); // Expect -0 (use direct for specific signed zero)

        $display("\n--- Edge Case Tests for Multiplier ---");
        run_test_direct_bf16("Mul: MIN_NORM_P * MIN_NORM_P (Direct)", "MUL", 
                                 BF16_POS_MIN_NORM, BF16_POS_MIN_NORM, 
                                 BF16_POS_ZERO, 1'b0, 1'b0, 1'b1);
        tb_num1 = BF16_POS_MAX_NORM; // 直接赋值 tb_num1 和 tb_num2
        tb_num2 = BF16_POS_TWO;
        // 然后调用 run_test_direct_bf16，但需要传递这些值
        run_test_direct_bf16("Mul: MAX_NORM_P * POS_TWO (Direct)", "MUL", 
                                 BF16_POS_MAX_NORM, BF16_POS_TWO, 
                                 BF16_POS_INF, 1'b0, 1'b1, 1'b0); 

        // MIN_NORM * 0.5 should underflow to zero
        run_test_direct_bf16("Mul: MIN_NORM_P * POS_HALF (Direct)", "MUL",
                                 BF16_POS_MIN_NORM, BF16_POS_HALF,
                                 BF16_POS_ZERO, 1'b0, 1'b0, 1'b1);

        $display("\n--- Edge Case Tests for Adder ---");
        // MAX_NORM + MIN_NORM -> MAX_NORM
        run_test_direct_bf16("Add: MAX_NORM_P + MIN_NORM_P (Direct)", "ADD",
                                 BF16_POS_MAX_NORM, BF16_POS_MIN_NORM, 
                                 BF16_POS_MAX_NORM, 1'b0, 1'b0, 1'b0);

        // MAX_NORM + MAX_NORM -> Inf
        run_test_direct_bf16("Add: MAX_NORM_P + MAX_NORM_P (Overflow) (Direct)", "ADD",
                                 BF16_POS_MAX_NORM, BF16_POS_MAX_NORM, 
                                 BF16_POS_INF, 1'b0, 1'b1, 1'b0);
        
        // MIN_NORM + (-MIN_NORM) -> +Zero
        run_test_direct_bf16("Add: MIN_NORM_P + NEG_MIN_NORM (Exact Zero) (Direct)", "ADD",
                                 BF16_POS_MIN_NORM, BF16_NEG_MIN_NORM, 
                                 BF16_POS_ZERO, 1'b0, 1'b0, 1'b1);

        // MAX_NORM + 1.0 -> MAX_NORM
        run_test_direct_bf16("Add: MAX_NORM_P + POS_ONE (Massive Align) (Direct)", "ADD",
                                 BF16_POS_MAX_NORM, BF16_POS_ONE, 
                                 BF16_POS_MAX_NORM, 1'b0, 1'b0, 1'b0);

        // Cancellation: (1.0 + eps) - 1.0 -> eps_val (which is 2^-7)
        // BF16_ONE_PLUS_EPS is defined at module level now
        // Expected result 16'h3800 (S=0, E=0x78 (120), F=0 -> 1.0 * 2^(120-127) = 1.0 * 2^-7)
        run_test_direct_bf16("Add: (1.0+eps) - 1.0 (Cancellation) (Direct)", "ADD",
                                 BF16_ONE_PLUS_EPS, BF16_NEG_ONE,
                                 16'h3C00, 1'b0, 1'b0, 1'b0); // is_zero should be 0 for this non-zero result
    
        $display("------------------------------------------------------");
        $display("Test Summary:");
        $display("Total Tests: %0d", test_count);
        $display("Passed:      %0d", pass_count);
        $display("Failed:      %0d", fail_count);
        $display("==============================================");

        if (fail_count > 0) begin $display("NOTE: There were test failures!"); end
        else begin $display("All tests passed!"); end
        $finish;
    end
endmodule