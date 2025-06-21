# Makefile for Verilator Simulation (for tb_synth_accelerator - NO VCD TRACE)

# --- Variables ---
NUM_THREADS ?= 12
VERILOG_SOURCES = tb_synth_accelerator.v accelerator.v systolic_array.v pe.v

TARGET_MODULE = tb_synth_accelerator
EXECUTABLE_NAME = V$(TARGET_MODULE)
CPP_WRAPPER = sim_main_synth.cpp

PYTHON = python3
INPUT_GEN_SCRIPT = InputGen.py
CHECK_RESULT_SCRIPT = CheckResult.py

VERILATOR_ROOT := /usr/share/verilator
VERILATOR_FLAGS ?= -Wall

# Check if VERILATOR_ROOT seems valid
ifeq ("$(wildcard $(VERILATOR_ROOT)/include/verilated.h)","")
    $(warning Cannot find verilated.h in $(VERILATOR_ROOT)/include. Check VERILATOR_ROOT path.)
endif

# --- 修改点 1: 修改默认目标 ---
# 将默认目标从 run 改为 compile，因为 run_sim 依赖输入文件，直接运行 make 可能不是我们想要的
all: compile

# --- Main Targets ---
compile_verilog: $(VERILOG_SOURCES) $(CPP_WRAPPER)
	@echo "### Verilating Verilog sources with $(NUM_THREADS) threads..."
	verilator -Wno-fatal $(VERILATOR_FLAGS) --top-module $(TARGET_MODULE) \
		-cc --timing -O3 --threads $(NUM_THREADS) \
		$(VERILOG_SOURCES) --exe $(CPP_WRAPPER)

compile_cpp: compile_verilog
	@echo "### Compiling C++ simulation executable in obj_dir..."
	$(MAKE) -C obj_dir -f $(EXECUTABLE_NAME).mk $(EXECUTABLE_NAME)

compile: compile_cpp

# --- 修改点 2: 新增一个只运行仿真的目标，并移除了检查步骤 ---
# 这个目标叫做 run_sim，它依赖于编译完成。
# 它只负责运行可执行文件，不再自动检查结果。
run_sim: compile
	@echo "### Running simulation: ./obj_dir/$(EXECUTABLE_NAME)"
	./obj_dir/$(EXECUTABLE_NAME)
	@echo "### Simulation finished. result_mem.csv has been generated."

# --- 修改点 3: 删除了旧的 run 目标 ---
# 我们不再需要那个会捆绑检查的 run 目标了。

generate_input:
	@echo "### Generating input_mem.csv for simulation..."
	$(PYTHON) $(INPUT_GEN_SCRIPT)

# check_result 目标保持不变，它做得很好，只负责检查
check_result:
	@echo "### Checking result..."
	$(PYTHON) CheckResult.py

clean:
	@echo "### Cleaning up generated files..."
	rm -rf obj_dir
	rm -f result_mem_tb.csv input_mem.csv result_mem.csv result_mem_original.csv
	rm -f matrix_a.npy matrix_b.npy matrix_c_expected_sint32.npy
	rm -rf __pycache__

# 注意：run_sim 不依赖 generate_input，因为我们将在 sh 脚本中确保顺序
.PHONY: all compile_verilog compile_cpp compile run_sim generate_input check_result clean