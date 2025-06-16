# Makefile for Verilator Simulation

# --- Variables ---
# 新增：线程数变量，可以从命令行覆盖 (e.g., make NUM_THREADS=8)
NUM_THREADS ?= 12

VERILOG_SOURCES = testbench_top.v accelerator.v src/sint8_to_bf16_converter.v src/systolic_array.v src/pe.v src/bfloat16_multiplier.v src/bfloat16_adder.v mem.v
TARGET_NAME = Vtestbench_top
CPP_WRAPPER = sim_main.cpp
PYTHON = python3
VERILATOR_ROOT_PATH = /home/admin_linux/miniconda3/envs/hw/share/verilator

# --- Default Target ---
all: run

# --- Main Targets ---
compile:
	@echo "### Compiling Verilog with Verilator using $(NUM_THREADS) threads..."
	# 新增：-O3 优化, --threads $(NUM_THREADS) 开启多线程编译
	verilator -Wno-fatal -Wall -cc --timing --trace -O3 --threads $(NUM_THREADS) -Isrc $(VERILOG_SOURCES) --exe $(CPP_WRAPPER)
	
	@echo "### Compiling C++ simulation executable in obj_dir with OpenMP support..."
	# 新增：为 C++ 编译器和链接器添加 -fopenmp 标志以启用多线程运行时支持
	$(MAKE) -C obj_dir -f $(TARGET_NAME).mk \
		VM_CPPFLAGS="-I$(VERILATOR_ROOT_PATH)/include -I$(VERILATOR_ROOT_PATH)/include/vltstd -fopenmp" \
		VM_LDFLAGS="-fopenmp" \
		$(TARGET_NAME)

run: compile generate_input
	@echo "### Running simulation..."
	./obj_dir/$(TARGET_NAME)
	@echo "### Simulation finished. result_mem.csv should be in the current directory."

# --- Utility Targets ---
generate_input:
	@echo "### Generating input_mem.csv..."
	$(PYTHON) InputGen.py

check_result:
	@echo "### Checking result..."
	$(PYTHON) CheckResult.py

clean:
	@echo "### Cleaning up generated files..."
	rm -rf obj_dir wave.vcd result_mem.csv input_mem.csv in.npy __pycache__ V$(TARGET_NAME)

.PHONY: all compile run generate_input check_result clean
