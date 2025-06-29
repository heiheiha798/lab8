# Makefile for Verilator Simulation

# --- Variables ---
# 从外部脚本传入，或使用默认值
MATRIX_DIM ?= 48
NUM_THREADS ?= 8

# --- MODIFIED: 更新 Verilog 源文件列表 ---
# 包含了所有设计模块和新的测试平台
VERILOG_SOURCES = \
	tb_accelerator.v \
	accelerator.v \
	loader.v \
	writer.v \
	data_formatter.v \
	sa_enhanced.v \
	pe.v \
	sram_banked.v \
	sram_c.v 

# --- MODIFIED: 更新顶层模块和 C++ Wrapper ---
TARGET_MODULE = tb_accelerator
EXECUTABLE_NAME = V$(TARGET_MODULE)
CPP_WRAPPER = sim_main.cpp # 保持 C++ 文件名不变

# --- Python 脚本 ---
PYTHON = python3
INPUT_GEN_SCRIPT = InputGen.py
CHECK_RESULT_SCRIPT = CheckResult.py
REORDER_SCRIPT = reorder_result_mem.py # Assuming this is still relevant for your CSV format

# --- Verilator 配置 ---
VERILATOR_FLAGS ?= -Wall
# --- MODIFIED: 新增 TRACE 选项 ---
# 在命令行中运行 `make TRACE=1` 来启用波形跟踪
TRACE ?= 0
ifeq ($(TRACE), 1)
	VERILATOR_FLAGS += --trace --trace-fst # Using FST for smaller/faster traces
	CPP_FLAGS = -DTRACE_ON
else
	CPP_FLAGS =
endif

# --- Main Targets ---
all: compile # Changed default to 'compile' as 'run_sim' depends on input files usually

compile_verilog: $(VERILOG_SOURCES) $(CPP_WRAPPER)
	@echo "### Verilating Verilog sources..."
	verilator -Wno-fatal $(VERILATOR_FLAGS) --top-module $(TARGET_MODULE) \
		-cc --timing -O3 --x-assign fast --x-initial fast --noassert --Mdir obj_dir \
		--threads $(NUM_THREADS) \
		$(VERILOG_SOURCES) --exe $(CPP_WRAPPER)

compile_cpp: compile_verilog
	@echo "### Compiling C++ simulation executable..."
	$(MAKE) -C obj_dir -f $(EXECUTABLE_NAME).mk $(EXECUTABLE_NAME) CXXFLAGS+="$(CPP_FLAGS)"

compile: compile_cpp

run_sim: compile # Ensure compilation before running
	@echo "### Running simulation: ./obj_dir/$(EXECUTABLE_NAME)"
	./obj_dir/$(EXECUTABLE_NAME)
	@echo "### Simulation finished. Assuming tb_accelerator produces necessary output files if any (e.g., from $finish or $display)."

# These Python script targets might need adjustment based on how tb_accelerator interacts with files
generate_input:
	@echo "### Generating input_mem.csv for simulation..."
	$(PYTHON) $(INPUT_GEN_SCRIPT) --matrix_dim $(MATRIX_DIM)

reorder_result:
	@echo "### Reordering hardware result..."
	$(PYTHON) $(REORDER_SCRIPT) --matrix_dim $(MATRIX_DIM) --input_csv result_mem.csv --output_csv result_mem_reordered.csv
	@if [ -f "result_mem.csv" ]; then cp result_mem.csv result_mem_original.csv; fi
	@if [ -f "result_mem_reordered.csv" ]; then mv result_mem_reordered.csv result_mem.csv; fi

check_result:
	@echo "### Checking result..."
	$(PYTHON) $(CHECK_RESULT_SCRIPT)

clean:
	@echo "### Cleaning up generated files..."
	rm -rf obj_dir
	rm -f input_mem.csv result_mem.csv result_mem_reordered.csv result_mem_original.csv # If these are still generated
	rm -f waveform.fst waveform.vcd # Adjusted for FST trace
	rm -f matrix_a.npy matrix_b.npy matrix_c_expected_sint32.npy # If these are still generated
	rm -rf __pycache__

.PHONY: all compile_verilog compile_cpp compile run_sim clean # Removed python script targets unless tb uses them
# generate_input reorder_result check_result