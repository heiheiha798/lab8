#!/bin/bash

set -e
LOG_FILE="output.txt" # 定义日志文件名

# 默认矩阵维度
DEFAULT_MATRIX_DIM=32 # 如果不提供参数，则使用此值
MATRIX_DIM="${1:-${DEFAULT_MATRIX_DIM}}" # 从第一个命令行参数获取，如果未提供则使用默认值

# 新增：默认线程数
DEFAULT_NUM_THREADS=12 # 默认使用 12 个线程
NUM_THREADS="${2:-${DEFAULT_NUM_THREADS}}" # 从第二个命令行参数获取线程数

# 新增：设置 OpenMP 环境变量，这会告诉编译后的仿真程序在运行时使用多少线程
export OMP_NUM_THREADS=${NUM_THREADS}

echo "----------------------------------------"
echo "使用矩阵维度: ${MATRIX_DIM}x${MATRIX_DIM}"
echo "使用线程数: ${NUM_THREADS}" # 新增日志
echo "----------------------------------------"

echo "步骤 1: 正在生成输入文件 (input_mem.csv)..."
echo "----------------------------------------"
make generate_input MATRIX_DIM=${MATRIX_DIM}

echo ""
echo "----------------------------------------"
echo "步骤 2: 正在编译并运行仿真 (日志将保存到 ${LOG_FILE})..."
echo "----------------------------------------"
# 新增：将 NUM_THREADS 传递给 make 命令
make run MATRIX_DIM=${MATRIX_DIM} NUM_THREADS=${NUM_THREADS} > "${LOG_FILE}" 2>&1

echo ""
echo "----------------------------------------"
echo "步骤 2.5: 正在重排硬件结果 (result_mem.csv -> result_mem_reordered.csv)..."
echo "----------------------------------------"
python3 reorder_result_mem.py --matrix_dim ${MATRIX_DIM} --input_csv result_mem.csv --output_csv result_mem_reordered.csv
mv result_mem_reordered.csv result_mem.csv

echo ""
echo "----------------------------------------"
echo "步骤 3: 正在检查仿真结果..."
echo "----------------------------------------"
make check_result 

echo ""
echo "----------------------------------------"
echo "所有步骤成功完成！仿真日志已保存到 ${LOG_FILE}"
echo "----------------------------------------"
