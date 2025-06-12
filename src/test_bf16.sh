iverilog -o bfloat16_test bfloat16_multiplier.v bfloat16_adder.v bfloat16_arith_tb.v

vvp bfloat16_test > output.txt
