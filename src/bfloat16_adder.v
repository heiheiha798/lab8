// =============================================================================
// Module: bfloat16_adder
// =============================================================================
module bfloat16_adder(
    input  wire [15:0] num1,
    input  wire [15:0] num2,
    output reg  [15:0] result,
    output wire        is_NaN,
    output wire        is_infinity,
    output wire        is_zero
);

    wire sign1 = num1[15];
    wire [7:0] exp1 = num1[14:7];
    wire [6:0] frac1 = num1[6:0];
    wire sign2 = num2[15];
    wire [7:0] exp2 = num2[14:7];
    wire [6:0] frac2 = num2[6:0];

    wire is_nan1_input      = (exp1 == 8'hFF) && (frac1 != 7'h0);
    wire is_nan2_input      = (exp2 == 8'hFF) && (frac2 != 7'h0);
    wire is_inf1_input      = (exp1 == 8'hFF) && (frac1 == 7'h0);
    wire is_inf2_input      = (exp2 == 8'hFF) && (frac2 == 7'h0);
    wire is_zero1_strict_input = (exp1 == 8'h00) && (frac1 == 7'h0);
    wire is_zero2_strict_input = (exp2 == 8'h00) && (frac2 == 7'h0);
    wire is_subnormal1_input = (exp1 == 8'h00) && (frac1 != 7'h0);
    wire is_subnormal2_input = (exp2 == 8'h00) && (frac2 != 7'h0);
    wire effective_is_zero1_input = is_zero1_strict_input || is_subnormal1_input;
    wire effective_is_zero2_input = is_zero2_strict_input || is_subnormal2_input;
    
    wire hide1 = !effective_is_zero1_input && (exp1 != 8'h00) && (exp1 != 8'hFF);
    wire hide2 = !effective_is_zero2_input && (exp2 != 8'h00) && (exp2 != 8'hFF);
    wire [10:0] mant1_ext = {hide1, frac1, 3'b000};
    wire [10:0] mant2_ext = {hide2, frac2, 3'b000};

    wire exp1_is_larger_strict = exp1 > exp2;
    wire exp2_is_larger_strict = exp2 > exp1;
    wire op1_is_larger_magnitude;
    assign op1_is_larger_magnitude = exp1_is_larger_strict ? 1'b1 :
                                     exp2_is_larger_strict ? 1'b0 :
                                     (frac1 >= frac2); 
    wire [7:0] exp_large_biased = op1_is_larger_magnitude ? exp1 : exp2;
    wire [7:0] exp_small_biased = op1_is_larger_magnitude ? exp2 : exp1;
    wire [10:0] mant_large_ext_val  = op1_is_larger_magnitude ? mant1_ext : mant2_ext; // Renamed to avoid confusion
    wire [10:0] mant_small_ext_val  = op1_is_larger_magnitude ? mant2_ext : mant1_ext; // Renamed
    wire sign_large_input = op1_is_larger_magnitude ? sign1 : sign2;
    wire sign_small_input = op1_is_larger_magnitude ? sign2 : sign1;
    wire [7:0] exp_diff;
    assign exp_diff = (exp_large_biased > exp_small_biased && exp_small_biased != 8'h00 && exp_large_biased != 8'hFF) ? 
                      (exp_large_biased - exp_small_biased) : 8'd0;
    wire [10:0] mant_small_shifted;
    assign mant_small_shifted = (exp_diff > 10) ? 11'd0 : 
                                (mant_small_ext_val >> exp_diff);
    wire effective_op_signs_differ = (sign_large_input != sign_small_input) && 
                                     !effective_is_zero1_input && !effective_is_zero2_input; 

    reg  [7:0] res_exp_biased_calc_reg;
    reg  [6:0] res_frac_calc_reg;
    reg  res_is_exactly_zero_arith_reg; // Arithmetic result is zero (A-B=0 or 0+0 FTZ)
    reg  result_sign_calc_reg;         
    
    wire [11:0] mant_eff_large_w = {1'b0, mant_large_ext_val}; 
    wire [11:0] mant_eff_small_w = {1'b0, mant_small_shifted};
    wire [11:0] mant_sum_abs_val_w; 
    assign mant_sum_abs_val_w = effective_op_signs_differ ? (mant_eff_large_w - mant_eff_small_w) :
                                                            (mant_eff_large_w + mant_eff_small_w);
    wire [3:0] lead_zeros_count_val_w; 
    assign lead_zeros_count_val_w = mant_sum_abs_val_w[10] ? 4'd0 : 
                                   mant_sum_abs_val_w[9]  ? 4'd1 :
                                   mant_sum_abs_val_w[8]  ? 4'd2 :
                                   mant_sum_abs_val_w[7]  ? 4'd3 :
                                   mant_sum_abs_val_w[6]  ? 4'd4 :
                                   mant_sum_abs_val_w[5]  ? 4'd5 :
                                   mant_sum_abs_val_w[4]  ? 4'd6 :
                                   mant_sum_abs_val_w[3]  ? 4'd7 :
                                   mant_sum_abs_val_w[2]  ? 4'd8 :
                                   mant_sum_abs_val_w[1]  ? 4'd9 :
                                   mant_sum_abs_val_w[0]  ? 4'd10 : 4'd11; 
    wire [11:0] mant_sub_shifted_norm_w = mant_sum_abs_val_w << lead_zeros_count_val_w;

    always @(*) begin
        res_exp_biased_calc_reg = 8'dx; 
        res_frac_calc_reg = 7'dx;
        res_is_exactly_zero_arith_reg = 1'b0; 
        result_sign_calc_reg = sign_large_input; 

        if (effective_op_signs_differ) begin 
            if (mant_sum_abs_val_w == 12'd0) begin 
                res_is_exactly_zero_arith_reg = 1'b1;
                res_exp_biased_calc_reg = 8'd0; 
                res_frac_calc_reg = 7'd0;   
                result_sign_calc_reg = 1'b0; 
            end else begin 
                if (mant_eff_large_w < mant_eff_small_w) result_sign_calc_reg = sign_small_input;
                else result_sign_calc_reg = sign_large_input;
                
                if (exp_large_biased == 8'h00) begin 
                     res_is_exactly_zero_arith_reg = 1'b1; 
                     res_exp_biased_calc_reg = 8'd0;
                     res_frac_calc_reg = 7'd0;
                end else if (exp_large_biased <= lead_zeros_count_val_w) begin 
                    res_is_exactly_zero_arith_reg = 1'b1;
                    res_exp_biased_calc_reg = 8'd0;
                    res_frac_calc_reg = 7'd0;
                end else begin 
                    res_exp_biased_calc_reg = exp_large_biased - lead_zeros_count_val_w;
                    res_frac_calc_reg = mant_sub_shifted_norm_w[9:3]; 
                end
            end
        end else begin 
            result_sign_calc_reg = sign_large_input; 
            if (mant_sum_abs_val_w[11]) begin 
                if (exp_large_biased == 8'hFF) begin 
                    res_exp_biased_calc_reg = 8'hFF; res_frac_calc_reg = 7'd0; 
                end else if (exp_large_biased == 8'hFE) begin // Overflow to Inf
                    res_exp_biased_calc_reg = 8'hFF; res_frac_calc_reg = 7'd0;        
                end else begin 
                    res_exp_biased_calc_reg = exp_large_biased + 1;
                    res_frac_calc_reg = mant_sum_abs_val_w[10:4]; 
                end
            end else begin 
                if (mant_sum_abs_val_w == 12'd0 && exp_large_biased == 8'h00 && hide1 == 1'b0 && hide2 == 1'b0) begin
                    res_is_exactly_zero_arith_reg = 1'b1;
                    res_exp_biased_calc_reg = 8'd0; res_frac_calc_reg = 7'd0;
                end else begin
                    res_exp_biased_calc_reg = exp_large_biased;
                    res_frac_calc_reg = mant_sum_abs_val_w[9:3]; 
                end
            end
        end
    end 

    wire result_is_nan_from_inputs_add = is_nan1_input || is_nan2_input || 
                                         (is_inf1_input && is_inf2_input && (sign1 != sign2)); 
    wire result_is_inf_from_inputs_add = (is_inf1_input || is_inf2_input) && 
                                         !(is_inf1_input && is_inf2_input && (sign1 != sign2));
    // Calculation causes overflow if calculated exponent is FF and it wasn't already Inf input
    wire calc_overflow_add = (res_exp_biased_calc_reg == 8'hFF) && !(is_inf1_input || is_inf2_input); 

    assign is_NaN      = result_is_nan_from_inputs_add;
    assign is_infinity = (result_is_inf_from_inputs_add || calc_overflow_add) && !is_NaN;
    // Zero if arithmetic result is zero, OR both inputs were zero (and not Inf/NaN)
    assign is_zero     = (res_is_exactly_zero_arith_reg || (effective_is_zero1_input && effective_is_zero2_input) )
                         && !is_NaN && !is_infinity;

    always @(*) begin
        result = 16'hXXXX; 
        if (is_NaN) begin
            result = 16'h7FC0; 
        end 
        else if (is_infinity) begin
            if (result_is_inf_from_inputs_add) begin // If input was Inf, use that sign
                if (is_inf1_input) result = {sign1, 8'hFF, 7'h00};
                else result = {sign2, 8'hFF, 7'h00}; // is_inf2_input must be true
            end else begin // Else, overflow from calculation, use calculated sign
                result = {result_sign_calc_reg, 8'hFF, 7'h00}; 
            end
        end
        // Order matters: if one input is zero and other is normal, result is normal.
        // This is handled by the main calculation path if FTZ makes mant_ext zero.
        // These explicit checks are for clarity or specific X+0=X behavior.
        else if (effective_is_zero1_input && !effective_is_zero2_input && !is_nan2_input && !is_inf2_input) begin 
            result = num2; // 0 + Y = Y
        end 
        else if (effective_is_zero2_input && !effective_is_zero1_input && !is_nan1_input && !is_inf1_input) begin 
            result = num1; // X + 0 = X
        end
        else if (is_zero) begin // Covers 0+0 and calculated zero like X+(-X)
            result = {result_sign_calc_reg, 8'h00, 7'h00}; 
        end
        else begin 
            result = {result_sign_calc_reg, res_exp_biased_calc_reg, res_frac_calc_reg};
        end
    end
endmodule