`timescale 1ns / 1ps

module sint8_to_bf16_converter (
    input  wire signed [7:0]  sint8_in,
    output wire        [15:0] bf16_out
);
    wire sign_bit;
    wire [6:0] abs_val_unsigned; // Represents absolute value from 0 to 127
    wire [2:0] msb_pos;          // Position of MSB (0 for 1, 1 for 2-3, ..., 6 for 64-127)
    wire [7:0] bf16_exp_biased;
    wire [6:0] bf16_frac_final;

    assign sign_bit = sint8_in[7];

    assign abs_val_unsigned = (sint8_in == 8'h80) ? 7'd127 : // Map SINT8 -128 to abs 127
                              (sint8_in[7]) ? (~sint8_in[6:0] + 1'b1) :
                                              sint8_in[6:0];

    assign msb_pos = (abs_val_unsigned == 7'b0)      ? 3'd0 :
                     (abs_val_unsigned[6]) ? 3'd6 :
                     (abs_val_unsigned[5]) ? 3'd5 :
                     (abs_val_unsigned[4]) ? 3'd4 :
                     (abs_val_unsigned[3]) ? 3'd3 :
                     (abs_val_unsigned[2]) ? 3'd2 :
                     (abs_val_unsigned[1]) ? 3'd1 :
                                             3'd0;

    assign bf16_exp_biased = (abs_val_unsigned == 7'b0) ? 8'h00 : (msb_pos + 127);

    wire [6:0] raw_frac_bits; // Intermediate wire for clarity
    assign raw_frac_bits = (abs_val_unsigned == 7'b0) ? 7'b0 :
                           (abs_val_unsigned & ((1 << msb_pos) - 1));

    assign bf16_frac_final = (abs_val_unsigned == 7'b0) ? 7'b0 :
                             (raw_frac_bits << (7 - msb_pos));

    // Assign final bfloat16 output
    assign bf16_out = (sint8_in == 8'b00000000) ? 16'h0000 :         // If SINT8 is exactly 0, BF16 is +0.0
                      (sint8_in == 8'h80)       ? 16'hC2FE :         // SINT8 -128 -> BF16 -127.0 (example mapping)
                                                  {sign_bit, bf16_exp_biased, bf16_frac_final};
endmodule