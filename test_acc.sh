python InputGen.py

iverilog -o accel_test -DENABLE_PE_DEBUG_DISPLAY accelerator.v src/systolic_array.v src/pe.v src/bfloat16_multiplier.v src/bfloat16_adder.v mem.v testbench_top.v

vvp accel_test > output.txt

python CheckResult.py