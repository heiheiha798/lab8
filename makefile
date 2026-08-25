# Makefile for Verilator Simulation

# --- Variables ---
# 从外部脚本传入，或使用默认值
MATRIX_DIM ?= 48
NUM_THREADS ?= 8

# --- 中间/生成文件统一输出目录 (已 gitignore) ---
OUTPUT_DIR ?= output

# --- MODIFIED: 更新 Verilog 源文件列表 ---
# 包含了所有设计模块和新的测试平台
# 设计 RTL 位于 hdl/，测试平台位于 tb/
VERILOG_SOURCES = \
	tb/tb_accelerator.v \
	hdl/accelerator.v \
	hdl/loader.v \
	hdl/writer.v \
	hdl/data_formatter.v \
	hdl/sa_enhanced.v \
	hdl/pe.v \
	hdl/sram_banked.v \
	hdl/sram_c.v 

# --- MODIFIED: 更新顶层模块和 C++ Wrapper ---
TARGET_MODULE = tb_accelerator
EXECUTABLE_NAME = V$(TARGET_MODULE)
CPP_WRAPPER = tb/sim_main.cpp # 保持 C++ 文件名不变

# --- Python 脚本 (位于 utils/) ---
PYTHON = python3
INPUT_GEN_SCRIPT = utils/InputGen.py
CHECK_RESULT_SCRIPT = utils/CheckResult.py
REORDER_SCRIPT = utils/reorder_result_mem.py # Assuming this is still relevant for your CSV format

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
	@echo "### Running simulation from $(OUTPUT_DIR)/ : ../obj_dir/$(EXECUTABLE_NAME)"
	mkdir -p $(OUTPUT_DIR)
	cd $(OUTPUT_DIR) && ../obj_dir/$(EXECUTABLE_NAME)
	@echo "### Simulation finished. Assuming tb_accelerator produces necessary output files if any (e.g., from $finish or $display)."

# These Python script targets might need adjustment based on how tb_accelerator interacts with files
generate_input:
	@echo "### Generating input_mem.csv for simulation ($(OUTPUT_DIR)/)..."
	mkdir -p $(OUTPUT_DIR)
	$(PYTHON) $(INPUT_GEN_SCRIPT) --matrix_dim $(MATRIX_DIM)

reorder_result:
	@echo "### Reordering hardware result..."
	mkdir -p $(OUTPUT_DIR)
	$(PYTHON) $(REORDER_SCRIPT) --matrix_dim $(MATRIX_DIM) --input_csv $(OUTPUT_DIR)/result_mem.csv --output_csv $(OUTPUT_DIR)/result_mem_reordered.csv
	@if [ -f "$(OUTPUT_DIR)/result_mem.csv" ]; then cp $(OUTPUT_DIR)/result_mem.csv $(OUTPUT_DIR)/result_mem_original.csv; fi
	@if [ -f "$(OUTPUT_DIR)/result_mem_reordered.csv" ]; then mv $(OUTPUT_DIR)/result_mem_reordered.csv $(OUTPUT_DIR)/result_mem.csv; fi

check_result:
	@echo "### Checking result..."
	$(PYTHON) $(CHECK_RESULT_SCRIPT)

clean:
	@echo "### Cleaning up generated files..."
	rm -rf obj_dir
	rm -rf output
	rm -f waveform.fst waveform.vcd # Adjusted for FST trace
	rm -rf __pycache__

.PHONY: all compile_verilog compile_cpp compile run_sim clean # Removed python script targets unless tb uses them
# generate_input reorder_result check_result