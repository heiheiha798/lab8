iverilog -o systolic_test systolic_array.v pe.v bfloat16_multiplier.v bfloat16_adder.v systolic_array_tb.v

vvp systolic_test > output.txt
