// =============================================================================
// Module: bfloat16_multiplier
// =============================================================================
module bfloat16_multiplier(
    input  wire [15:0] num1,
    input  wire [15:0] num2,
    output reg  [15:0] result,
    output wire        is_NaN,      
    output wire        is_infinity, 
    output wire        is_zero      
);

    wire sign1 = num1[15];
    wire [7:0] exp1_in = num1[14:7];
    wire [6:0] frac1 = num1[6:0];
    wire sign2 = num2[15];
    wire [7:0] exp2_in = num2[14:7];
    wire [6:0] frac2 = num2[6:0];

    wire is_nan1_input      = (exp1_in == 8'hFF) && (frac1 != 7'h0);
    wire is_nan2_input      = (exp2_in == 8'hFF) && (frac2 != 7'h0);
    wire is_inf1_input      = (exp1_in == 8'hFF) && (frac1 == 7'h0);
    wire is_inf2_input      = (exp2_in == 8'hFF) && (frac2 == 7'h0);
    wire is_zero1_strict_input = (exp1_in == 8'h00) && (frac1 == 7'h0); 
    wire is_zero2_strict_input = (exp2_in == 8'h00) && (frac2 == 7'h0); 
    wire is_subnormal1_input = (exp1_in == 8'h00) && (frac1 != 7'h0);
    wire is_subnormal2_input = (exp2_in == 8'h00) && (frac2 != 7'h0);
    wire effective_is_zero1_input = is_zero1_strict_input || is_subnormal1_input;
    wire effective_is_zero2_input = is_zero2_strict_input || is_subnormal2_input;

    wire res_sign_calc = sign1 ^ sign2;

    wire hide1 = !effective_is_zero1_input && (exp1_in != 8'h00) && (exp1_in != 8'hFF);
    wire hide2 = !effective_is_zero2_input && (exp2_in != 8'h00) && (exp2_in != 8'hFF);
    wire [7:0] mant1 = {hide1, frac1}; 
    wire [7:0] mant2 = {hide2, frac2};
    
    wire [15:0] mant_prod = mant1 * mant2; 
    
    // --- Revised explicit exponent calculation ---
    wire signed [10:0] exp1_s11, exp2_s11, bias_s11;
    assign exp1_s11 = {3'b000, exp1_in}; // Zero extend 8-bit biased exp to 11 bits
    assign exp2_s11 = {3'b000, exp2_in};
    assign bias_s11 = 11'sd127;      

    wire signed [11:0] exp_sum_s12; 
    // Perform addition as signed with sufficient width
    assign exp_sum_s12 = {{1{exp1_s11[10]}}, exp1_s11} + {{1{exp2_s11[10]}}, exp2_s11}; 

    wire signed [11:0] exp_sum_biased_prenorm_s12;
    assign exp_sum_biased_prenorm_s12 = exp_sum_s12 - {{1{bias_s11[10]}}, bias_s11};

    wire signed [9:0] exp_sum_biased_prenorm;
    assign exp_sum_biased_prenorm = exp_sum_biased_prenorm_s12[9:0]; // Truncate to 10 bits
    // --- End of revised explicit exponent calculation ---
    
    wire needs_norm_shift = mant_prod[15]; 
    wire [15:0] mant_norm_shifted = needs_norm_shift ? (mant_prod >> 1) : mant_prod;
    
    wire signed [10:0] final_exp_biased_calc_intermediate_s11; 
    // Add 1 as an 11-bit signed number if shifting
    assign final_exp_biased_calc_intermediate_s11 = needs_norm_shift ? 
                                                  ({exp_sum_biased_prenorm[9], exp_sum_biased_prenorm} + 11'sd1) : 
                                                  {exp_sum_biased_prenorm[9], exp_sum_biased_prenorm};

    wire signed [9:0] final_exp_biased_calc;
    assign final_exp_biased_calc = final_exp_biased_calc_intermediate_s11[9:0]; // Truncate to 10 bits

    wire [6:0] res_frac_calc = mant_norm_shifted[13:7]; 

    wire result_is_nan_from_inputs = is_nan1_input || is_nan2_input || 
                                     ((is_inf1_input || is_inf2_input) && (effective_is_zero1_input || effective_is_zero2_input));
    wire result_is_inf_from_inputs = (is_inf1_input || is_inf2_input) && 
                                     !(effective_is_zero1_input || effective_is_zero2_input) &&
                                     !result_is_nan_from_inputs; 
    wire result_is_zero_from_inputs = effective_is_zero1_input || effective_is_zero2_input;

    wire signed [9:0] const_FE_s10 = 10'sd254; 
    wire signed [9:0] const_01_s10 = 10'sd1;   

    wire calc_overflow_val  = (final_exp_biased_calc > const_FE_s10) && !result_is_nan_from_inputs && !result_is_inf_from_inputs && !result_is_zero_from_inputs; 
    wire calc_underflow_val = (final_exp_biased_calc < const_01_s10) && !result_is_nan_from_inputs && !result_is_inf_from_inputs && !result_is_zero_from_inputs;
    
    wire calc_result_is_subnormal_ftz_val = (~mant_norm_shifted[14]) && 
                                        !result_is_nan_from_inputs &&
                                        !result_is_inf_from_inputs &&
                                        !result_is_zero_from_inputs &&
                                        !calc_overflow_val &&
                                        !calc_underflow_val;

    assign is_NaN      = result_is_nan_from_inputs;
    assign is_infinity = (result_is_inf_from_inputs || calc_overflow_val) && !is_NaN;
    assign is_zero     = (result_is_zero_from_inputs || calc_underflow_val || calc_result_is_subnormal_ftz_val) && !is_NaN && !is_infinity;

    always @(*) begin
        result = 16'hXXXX; 
        if (is_NaN) begin
            result = 16'h7FC0; 
        end 
        else if (is_infinity) begin
            result = {res_sign_calc, 8'hFF, 7'h00};
        end 
        else if (is_zero) begin 
            result = {res_sign_calc, 8'h00, 7'h00};
        end 
        else begin 
            result = {res_sign_calc, final_exp_biased_calc[7:0], res_frac_calc};
        end
    end
endmodule