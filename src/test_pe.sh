iverilog -o pe_test pe.v bfloat16_multiplier.v bfloat16_adder.v pe_tb.v

vvp pe_test > output.txt