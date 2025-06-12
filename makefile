# Makefile for Verilator Simulation

# --- Variables ---
TARGET = Vtestbench_top
PYTHON = python3

# --- Default Target ---
# 'make' or 'make all' will run the full simulation
all: run

# --- Main Targets ---

compile:
	@echo "### Compiling Verilog with Verilator..."
	verilator -Wno-fatal -cc --timing -Isrc testbench_top.v --exe sim_main.cpp
	@echo "### Compiling C++ simulation executable..."
	$(MAKE) -C obj_dir -f $(TARGET).mk $(TARGET)

run: compile
	@echo "### Running simulation..."
	./obj_dir/$(TARGET)
	@echo "### Simulation finished. wave.vcd and result_mem.csv generated."

# --- Utility Targets ---

# Generate input data
generate_input:
	@echo "### Generating input_mem.csv..."
	$(PYTHON) InputGen.py

# Check the result against the golden reference
check_result:
	@echo "### Checking result..."
	$(PYTHON) CheckResult.py

# Clean up all generated filesw
clean:
	@echo "### Cleaning up generated files..."
	rm -rf obj_dir wave.vcd result_mem.csv input_mem.csv in.npy __pycache__

.PHONY: all compile run generate_input check_result clean