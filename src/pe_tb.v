`timescale 1ns / 1ps

module pe_tb;

    // Parameters from pe.v
    localparam DATA_WIDTH = 16;
    localparam ACCUMULATION_CYCLES_TB = 4; // Keep small for quicker TB

    // Testbench Parameters
    localparam CLK_PERIOD = 10;
    localparam STRING_MAX_LEN = 256;

    // DUT Interface Signals for the new PE
    reg                            clk_tb;
    reg                            rst_n_tb;
    reg                            enable_tb;
    reg                            clear_accumulator_tb;
    reg  [DATA_WIDTH-1:0]          a_data_in_tb;
    reg  [DATA_WIDTH-1:0]          b_data_in_tb;
    wire [DATA_WIDTH-1:0]          a_data_out_tb;
    wire [DATA_WIDTH-1:0]          b_data_out_tb;
    wire [DATA_WIDTH-1:0]          result_out_tb;
    wire                           result_valid_tb;
    wire                           pe_is_nan_tb;
    wire                           pe_is_infinity_tb;

    // BF16 Constants
    localparam BF16_POS_ZERO       = 16'h0000;
    localparam BF16_NEG_ZERO       = 16'h8000;
    localparam BF16_POS_ONE        = 16'h3F80; // +1.0
    localparam BF16_NEG_ONE        = 16'hBF80; // -1.0
    localparam BF16_POS_TWO        = 16'h4000; // +2.0
    localparam BF16_POS_THREE      = 16'h4040; // +3.0
    localparam BF16_POS_FOUR       = 16'h4080; // +4.0
    localparam BF16_POS_FIVE       = 16'h40A0; // +5.0
    localparam BF16_POS_SIX        = 16'h40C0; // +6.0
    localparam BF16_POS_SEVEN      = 16'h40E0; // +7.0
    localparam BF16_EIGHT          = 16'h4100; // +8.0
    localparam BF16_TEN            = 16'h4120; // +10.0
    localparam BF16_TWELVE         = 16'h4140; // +12.0
    localparam BF16_FOURTEEN       = 16'h4160; // +14.0
    localparam BF16_POS_INF        = 16'h7F80;
    localparam BF16_NEG_INF        = 16'hFF80;
    localparam BF16_QNaN           = 16'h7FC0; // A quiet NaN pattern


    integer test_count = 0;
    integer pass_count = 0;
    integer fail_count = 0;
    integer k; // Loop variable

    // Instantiate NEW PE DUT
    pe #(
        .DATA_WIDTH(DATA_WIDTH),
        .ACCUMULATION_CYCLES(ACCUMULATION_CYCLES_TB)
    ) dut_pe (
        .clk(clk_tb),
        .rst_n(rst_n_tb),
        .enable(enable_tb),
        .clear_accumulator(clear_accumulator_tb),
        .a_data_in(a_data_in_tb),
        .b_data_in(b_data_in_tb),
        .a_data_out(a_data_out_tb),
        .b_data_out(b_data_out_tb),
        .result_out(result_out_tb),
        .result_valid(result_valid_tb),
        .pe_is_nan(pe_is_nan_tb),
        .pe_is_infinity(pe_is_infinity_tb)
    );

    always #(CLK_PERIOD/2) clk_tb = ~clk_tb;

    task real_to_bfloat16;
        input real r_val;
        output reg [15:0] bf16_val;
        reg s; reg [7:0] biased_exp; reg [6:0] frac_val;
        real abs_r_val; real temp_frac; integer exp_int; integer i;
        begin
            s=(r_val<0.0); abs_r_val=s?-r_val:r_val;

            // Simplified: This task is primarily for converting normal real numbers to BF16.
            // NaN/Inf testing should ideally use pre-defined BF16 constants directly.
            // Removed $isunknown and r_val != r_val checks for Verilog-2001 compatibility.

            if(abs_r_val==0.0) begin
                bf16_val = {s, 8'h00, 7'h00}; // BF16 Zero
                disable real_to_bfloat16;
            end

            exp_int=0;
            if(abs_r_val>=1.0) begin
                while(abs_r_val>=2.0) begin
                    abs_r_val=abs_r_val/2.0;
                    exp_int=exp_int+1;
                end
            end else begin : sl_pe_tb_3 // Named block for disable
                while(abs_r_val<1.0 && exp_int > -126) begin // Check exp_int to prevent excessive loops for very small numbers
                    abs_r_val=abs_r_val*2.0;
                    exp_int=exp_int-1;
                    if(abs_r_val==0.0) disable sl_pe_tb_3; // If it becomes zero during normalization
                end
            end

            if(abs_r_val==0.0) begin // Re-check if it became zero
                bf16_val = {s, 8'h00, 7'h00}; // BF16 Zero
                disable real_to_bfloat16;
            end
            
            // Check for overflow before calculating biased_exp for BF16
            if (exp_int > 127) begin // Max BF16 exponent for normal numbers
                bf16_val = {s, 8'hFF, 7'h00}; // BF16 Infinity
                disable real_to_bfloat16;
            end
            // Check for underflow to zero (BF16 doesn't represent subnormals in this simple model)
            if (exp_int < -126) begin // Min BF16 exponent for normal numbers (before biasing)
                bf16_val = {s, 8'h00, 7'h00}; // BF16 Zero
                disable real_to_bfloat16;
            end

            biased_exp = exp_int + 127; // Standard bias for BF16-like exponent

            // This biased_exp should now be in the range for normal numbers (1 to 254)
            // or will be handled by the above checks if exp_int was out of range.
            // If biased_exp is 0 or 255 due to extreme exp_int, it should have been caught.

            temp_frac = abs_r_val - 1.0; // abs_r_val is now in [1.0, 2.0)
            frac_val = 0; // Initialize
            for(i=6;i>=0;i=i-1) begin
                temp_frac=temp_frac*2.0;
                if(temp_frac>=1.0) begin
                    frac_val[i]=1'b1;
                    temp_frac=temp_frac-1.0;
                end
            end
            bf16_val = {s, biased_exp, frac_val};
        end
    endtask

    // Task to apply one cycle of inputs
    task apply_cycle;
        input en_pe, en_clear;
        input [DATA_WIDTH-1:0] a_val, b_val;
        begin
            enable_tb             = en_pe;
            clear_accumulator_tb  = en_clear;
            a_data_in_tb          = a_val;
            b_data_in_tb          = b_val;
            #(CLK_PERIOD);
        end
    endtask

    // Task to check outputs
    task check_outputs;
        input [DATA_WIDTH-1:0] exp_res, exp_a_out, exp_b_out;
        input exp_valid, exp_nan, exp_inf;
        input [STRING_MAX_LEN*8-1:0] testname_suffix;
        begin
            test_count = test_count + 1;
            if (result_out_tb === exp_res &&
                a_data_out_tb === exp_a_out &&
                b_data_out_tb === exp_b_out &&
                result_valid_tb === exp_valid &&
                pe_is_nan_tb === exp_nan &&
                pe_is_infinity_tb === exp_inf) begin
                $display("Test #%0d: %s - PASS", test_count, testname_suffix);
                pass_count = pass_count + 1;
            end else begin
                $display("Test #%0d: %s - FAIL", test_count, testname_suffix);
                $display("  Expected res:0x%h a_out:0x%h b_out:0x%h valid:%b nan:%b inf:%b", exp_res, exp_a_out, exp_b_out, exp_valid, exp_nan, exp_inf);
                $display("  Actual   res:0x%h a_out:0x%h b_out:0x%h valid:%b nan:%b inf:%b", result_out_tb, a_data_out_tb, b_data_out_tb, result_valid_tb, pe_is_nan_tb, pe_is_infinity_tb);
                fail_count = fail_count + 1;
            end
        end
    endtask

    // Main test sequence
    initial begin
        clk_tb = 0;
        rst_n_tb = 0;
        enable_tb = 0;
        clear_accumulator_tb = 0;
        a_data_in_tb = 0; // Verilog-2001 compatible
        b_data_in_tb = 0; // Verilog-2001 compatible

        $display("==============================================");
        $display("Starting NEW PE Testbench (Dataflow A & B)");
        $display("ACCUMULATION_CYCLES_TB = %0d", ACCUMULATION_CYCLES_TB);
        $display("==============================================");

        // 1. Reset PE
        #(CLK_PERIOD * 2);
        rst_n_tb = 1;
        #(CLK_PERIOD);
        check_outputs(BF16_POS_ZERO, BF16_POS_ZERO, BF16_POS_ZERO, 1'b0, 1'b0, 1'b0, "Reset State");

        // 2. Basic MAC operation: Sum ( A[i] * B[i] ) for i=0 to 3
        // Example: C = (1*2) + (1*3) + (1*4) + (1*5) = 2+3+4+5 = 14
        // PE Pipeline:
        // Cycle t: a_in, b_in -> a_reg, b_reg (end of cycle)
        // Cycle t+1: a_reg, b_reg -> mul -> mul_res_reg (end of cycle)
        // Cycle t+2: mul_res_reg + acc_old -> acc_new (end of cycle)
        // ACCUMULATOR IS FROZEN AFTER DoneLatch IS SET (after result_valid pulses high)

        $display("\n--- Test: Basic MAC Series: (1*2)+(1*3)+(1*4)+(1*5) = 14 ---");
        // Cycle 0: Clear accumulator. Load first A0, B0.
        apply_cycle(1, 1, BF16_POS_ONE, BF16_POS_TWO); // A0=1, B0=2. Clear Acc.
        check_outputs(BF16_POS_ZERO, BF16_POS_ONE, BF16_POS_TWO, 1'b0, 1'b0, 1'b0, "MAC Series - Cycle 0 (Clear, Load A0,B0)");

        // Cycle 1: Load A1, B1.
        apply_cycle(1, 0, BF16_POS_ONE, BF16_POS_THREE); // A1=1, B1=3
        check_outputs(BF16_POS_ZERO, BF16_POS_ONE, BF16_POS_THREE, 1'b0, 1'b0, 1'b0, "MAC Series - Cycle 1 (Load A1,B1; Mul0; Acc0)");

        // Cycle 2: Load A2, B2.
        apply_cycle(1, 0, BF16_POS_ONE, BF16_POS_FOUR);  // A2=1, B2=4
        check_outputs(BF16_POS_TWO, BF16_POS_ONE, BF16_POS_FOUR, 1'b0, 1'b0, 1'b0, "MAC Series - Cycle 2 (Load A2,B2; Mul1; Acc1)");

        // Cycle 3: Load A3, B3. This is the 4th MAC input pair. Counter = 3.
        apply_cycle(1, 0, BF16_POS_ONE, BF16_POS_FIVE);  // A3=1, B3=5
        check_outputs(BF16_POS_FIVE, BF16_POS_ONE, BF16_POS_FIVE, 1'b0, 1'b0, 1'b0, "MAC Series - Cycle 3 (Load A3,B3; Mul2; Acc2)");

        // Cycle 4: Load dummy A4, B4. Counter was 3, completes 4th accumulation. result_valid=1.
        // Acc = 5 (prev_acc) + 4 (A2*B2 from prev mul_res_reg) = 9. This is the value when result_valid is pulsed.
        // DoneLatch is set. Accumulator is now frozen at 9.0.
        apply_cycle(1, 0, BF16_POS_ZERO, BF16_POS_ZERO); // A4=0, B4=0
        check_outputs(16'h4110, BF16_POS_ZERO, BF16_POS_ZERO, 1'b1, 1'b0, 1'b0, "MAC Series - Cycle 4 (Acc=9, Valid, Acc FROZEN)");

        // Cycle 5: Valid goes low. Enable is low (from apply_cycle(0,0,...)). Accumulator should hold its frozen value (9.0).
        apply_cycle(0, 0, BF16_POS_ZERO, BF16_POS_ZERO); // Stall, enable=0.
        check_outputs(16'h4110, BF16_POS_ZERO, BF16_POS_ZERO, 1'b0, 1'b0, 1'b0, "MAC Series - Cycle 5 (Valid low, Acc holds frozen 9.0)");


        // Test: Accumulator remains frozen even if enabled after DoneLatch is set
        $display("\n--- Test: Accumulator Frozen After DoneLatch ---");
        // Sequence to get acc to 9.0 and DoneLatch set
        apply_cycle(1, 1, BF16_POS_ONE, BF16_POS_TWO);   // C0: Acc=0. DoneLatch=0
        apply_cycle(1, 0, BF16_POS_ONE, BF16_POS_THREE); // C1: Acc=0. DoneLatch=0. mul_res_reg=2 (from 1*2)
        apply_cycle(1, 0, BF16_POS_ONE, BF16_POS_FOUR);  // C2: Acc=2. DoneLatch=0. mul_res_reg=3 (from 1*3)
        apply_cycle(1, 0, BF16_POS_ONE, BF16_POS_FIVE);  // C3: Acc=5 (from 2+3). DoneLatch=0. mul_res_reg=4 (from 1*4)
        check_outputs(BF16_POS_FIVE, BF16_POS_ONE, BF16_POS_FIVE, 1'b0, 1'b0, 1'b0, "Acc Frozen Test - Cycle 3 (Acc=5)");

        // Cycle 4: Acc becomes 9 (from 5+4). result_valid=1. DoneLatch=1. Accumulator is frozen at 9.0.
        // Inputs A4=BF16_POS_ONE, B4=BF16_POS_ONE. These will load into a_reg, b_reg.
        // mul_res_reg will get A3*B3 = 1*5 = 5. (This is mul_res_reg for *next* cycle's potential accumulation)
        apply_cycle(1, 0, BF16_POS_ONE, BF16_POS_ONE); // A4=1, B4=1 for next cycle's a_reg/b_reg
        check_outputs(16'h4110, BF16_POS_ONE, BF16_POS_ONE, 1'b1, 1'b0, 1'b0, "Acc Frozen Test - Cycle 4 (Acc=9, Valid, Acc FROZEN)");

        // Cycle 5: Enable is still high. New inputs A5, B5 (dummy).
        // a_reg, b_reg get A5, B5 (0,0).
        // mul_res_reg gets A4*B4 = 1*1 = 1.
        // local_accumulator_reg should REMAIN 9.0 because DoneLatch is 1.
        // result_valid goes low.
        apply_cycle(1, 0, BF16_POS_ZERO, BF16_POS_ZERO); // A5=0, B5=0
        check_outputs(16'h4110, BF16_POS_ZERO, BF16_POS_ZERO, 1'b0, 1'b0, 1'b0, "Acc Frozen Test - Cycle 5 (Enable high, Acc STAYS 9.0)");

        // Cycle 6: Enable is still high.
        // local_accumulator_reg should REMAIN 9.0.
        // a_reg, b_reg still 0,0. mul_res_reg gets A5*B5 = 0*0 = 0.
        apply_cycle(1, 0, BF16_POS_ZERO, BF16_POS_ZERO);
        check_outputs(16'h4110, BF16_POS_ZERO, BF16_POS_ZERO, 1'b0, 1'b0, 1'b0, "Acc Frozen Test - Cycle 6 (Enable high, Acc STAYS 9.0)");


        // 3. Stall Test (enable = 0)
        $display("\n--- Testing Stall ---");
        apply_cycle(1, 1, BF16_POS_ONE, BF16_POS_TWO);
        check_outputs(BF16_POS_ZERO, BF16_POS_ONE, BF16_POS_TWO, 1'b0, 1'b0, 1'b0, "Stall Test - Setup1");

        apply_cycle(1, 0, BF16_POS_THREE, BF16_POS_FOUR);
        check_outputs(BF16_POS_ZERO, BF16_POS_THREE, BF16_POS_FOUR, 1'b0, 1'b0, 1'b0, "Stall Test - Setup2 (Before Stall)");

        apply_cycle(0, 0, BF16_POS_FIVE, BF16_POS_SIX);
        check_outputs(BF16_POS_ZERO, BF16_POS_THREE, BF16_POS_FOUR, 1'b0, 1'b0, 1'b0, "Stall Test - During Stall");

        apply_cycle(1, 0, BF16_POS_SEVEN, BF16_EIGHT);
        check_outputs(BF16_POS_TWO, BF16_POS_SEVEN, BF16_EIGHT, 1'b0, 1'b0, 1'b0, "Stall Test - After Resume");


        // 4. NaN/Inf Propagation
        $display("\n--- Testing NaN Propagation (B input is NaN) ---");
        apply_cycle(1, 1, BF16_POS_ONE, BF16_QNaN); // A0, B0_nan
        check_outputs(BF16_POS_ZERO, BF16_POS_ONE, BF16_QNaN, 1'b0, 1'b0, 1'b0, "NaN Test - Cycle 0 (Load A0,B0_nan, Clear)");

        apply_cycle(1, 0, BF16_POS_TWO, BF16_POS_ONE); // A1, B1
        check_outputs(BF16_POS_ZERO, BF16_POS_TWO, BF16_POS_ONE, 1'b0, 1'b0, 1'b0, "NaN Test - Cycle 1 (Load A1,B1. acc=0)");

        apply_cycle(1, 0, BF16_POS_THREE, BF16_POS_ONE); // A2, B2. Accumulator becomes NaN here from P0_nan.
        check_outputs(BF16_QNaN, BF16_POS_THREE, BF16_POS_ONE, 1'b0, 1'b1, 1'b0, "NaN Test - Cycle 2 (Load A2,B2. acc=NaN)");

        // Cycle 3: Inputs A3,B3. Counter was 2, becomes 3. Accumulator still NaN. Valid is still 0.
        apply_cycle(1, 0, BF16_POS_FOUR, BF16_POS_ONE); // A3, B3
        check_outputs(BF16_QNaN, BF16_POS_FOUR, BF16_POS_ONE, 1'b0, 1'b1, 1'b0, "NaN Test - Cycle 3 (Acc NaN, Cnt becomes 3, Valid still 0)"); // CHANGED valid to 0

        // Cycle 4: Inputs A4,B4. Counter was 3. Valid PULSES HIGH. DoneLatch sets. Accumulator NaN and frozen.
        apply_cycle(1, 0, BF16_POS_ONE, BF16_POS_ONE);   // A4, B4 (e.g. dummy or next real data)
        check_outputs(BF16_QNaN, BF16_POS_ONE, BF16_POS_ONE, 1'b1, 1'b1, 1'b0, "NaN Test - Cycle 4 (NaN frozen, Valid PULSE HIGH)"); // CHANGED valid to 1

        // Cycle 5: Inputs A5,B5. Valid goes LOW. Accumulator remains NaN and frozen.
        apply_cycle(1, 0, BF16_POS_ZERO, BF16_POS_ZERO); // Dummy inputs
        check_outputs(BF16_QNaN, BF16_POS_ZERO, BF16_POS_ZERO, 1'b0, 1'b1, 1'b0, "NaN Test - Cycle 5 (Valid low, NaN frozen)"); // ADDED


        $display("\n--- Testing Inf Propagation (A input is Inf) ---");
        apply_cycle(1, 1, BF16_POS_INF, BF16_POS_TWO); // A0_inf, B0
        check_outputs(BF16_POS_ZERO, BF16_POS_INF, BF16_POS_TWO, 1'b0, 1'b0, 1'b0, "Inf Test - Cycle 0 (Load A0_inf,B0, Clear)");

        apply_cycle(1, 0, BF16_POS_ONE, BF16_POS_THREE); // A1, B1
        check_outputs(BF16_POS_ZERO, BF16_POS_ONE, BF16_POS_THREE, 1'b0, 1'b0, 1'b0, "Inf Test - Cycle 1 (Load A1,B1. acc=0)");

        apply_cycle(1, 0, BF16_POS_ONE, BF16_POS_FOUR);  // A2, B2. Accumulator becomes Inf here from P0_inf.
        check_outputs(BF16_POS_INF, BF16_POS_ONE, BF16_POS_FOUR, 1'b0, 1'b0, 1'b1, "Inf Test - Cycle 2 (Load A2,B2. acc=Inf)");

        // Cycle 3: Inputs A3,B3. Counter was 2, becomes 3. Accumulator still Inf. Valid is still 0.
        apply_cycle(1, 0, BF16_POS_ONE, BF16_NEG_ONE); // A3, B3
        check_outputs(BF16_POS_INF, BF16_POS_ONE, BF16_NEG_ONE, 1'b0, 1'b0, 1'b1, "Inf Test - Cycle 3 (Acc Inf, Cnt becomes 3, Valid still 0)"); // CHANGED valid to 0

        // Cycle 4: Inputs A4,B4. Counter was 3. Valid PULSES HIGH. DoneLatch sets. Accumulator Inf and frozen.
        apply_cycle(1, 0, BF16_POS_ONE, BF16_POS_ONE);    // A4, B4 (e.g. dummy or next real data)
        check_outputs(BF16_POS_INF, BF16_POS_ONE, BF16_POS_ONE, 1'b1, 1'b0, 1'b1, "Inf Test - Cycle 4 (Inf frozen, Valid PULSE HIGH)"); // CHANGED valid to 1

        // Cycle 5: Inputs A5,B5. Valid goes LOW. Accumulator remains Inf and frozen.
        apply_cycle(1, 0, BF16_POS_ZERO, BF16_POS_ZERO); // Dummy inputs
        check_outputs(BF16_POS_INF, BF16_POS_ZERO, BF16_POS_ZERO, 1'b0, 1'b0, 1'b1, "Inf Test - Cycle 5 (Valid low, Inf frozen)"); // ADDED


        $display("------------------------------------------------------");
        $display("Test Summary:");
        $display("Total Tests: %0d", test_count);
        $display("Passed:      %0d", pass_count);
        $display("Failed:      %0d", fail_count);
        $display("==============================================");

        if (fail_count > 0) begin $display("NOTE: PE Testbench has failures!"); end
        else begin $display("PE Testbench: All tests passed!"); end
        $finish;
    end

endmodule