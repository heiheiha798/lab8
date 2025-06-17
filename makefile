# Makefile for Verilator Simulation (for tb_synth_accelerator - NO VCD TRACE)

# --- Variables ---
NUM_THREADS ?= 12 # 根据服务器 nproc 输出设置
VERILOG_SOURCES = tb_synth_accelerator.v accelerator.v systolic_array.v pe.v

TARGET_MODULE = tb_synth_accelerator
EXECUTABLE_NAME = V$(TARGET_MODULE)
CPP_WRAPPER = sim_main_synth.cpp

PYTHON = python3
INPUT_GEN_SCRIPT = InputGen.py
CHECK_RESULT_SCRIPT = CheckResult.py

VERILATOR_ROOT := /usr/share/verilator

# Check if VERILATOR_ROOT seems valid by checking for verilated.h
ifeq ("$(wildcard $(VERILATOR_ROOT)/include/verilated.h)","")
    $(warning Cannot find verilated.h in $(VERILATOR_ROOT)/include. Check VERILATOR_ROOT path.)
endif

# --- Default Target ---
all: run

# --- Main Targets ---
compile_verilog: $(VERILOG_SOURCES) $(CPP_WRAPPER)
	@echo "### Verilating Verilog sources with $(NUM_THREADS) threads..."
	verilator -Wno-fatal -Wall --top-module $(TARGET_MODULE) \
		-cc --timing -O3 --threads $(NUM_THREADS) \
		$(VERILOG_SOURCES) --exe $(CPP_WRAPPER)

compile_cpp: compile_verilog
	@echo "### Compiling C++ simulation executable in obj_dir..."
	$(MAKE) -C obj_dir -f $(EXECUTABLE_NAME).mk $(EXECUTABLE_NAME)

compile: compile_cpp

run: compile generate_input
	@echo "### Running simulation: ./obj_dir/$(EXECUTABLE_NAME)"
	./obj_dir/$(EXECUTABLE_NAME)
	@echo "### Simulation finished. result_mem_tb.csv should be in the current directory."
	@echo "### Comparing results..."
	$(PYTHON) $(CHECK_RESULT_SCRIPT)

generate_input:
	@echo "### Generating input_mem.csv for simulation..."
	$(PYTHON) $(INPUT_GEN_SCRIPT)

check_result:
	@echo "### Checking result..."
	$(PYTHON) CheckResult.py

clean:
	@echo "### Cleaning up generated files..."
	rm -rf obj_dir
	rm -f result_mem_tb.csv input_mem.csv
	rm -f matrix_a.npy matrix_b.npy matrix_c_expected_sint32.npy
	rm -rf __pycache__

.PHONY: all compile_verilog compile_cpp compile run generate_input clean