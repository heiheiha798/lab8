#!/bin/bash

LOG_FILE="output.txt"
> "${LOG_FILE}" # 清空旧日志

{
    set -e

    # --- 脚本配置区 ---
    DEFAULT_MATRIX_DIM=48
    MATRIX_DIM="${1:-${DEFAULT_MATRIX_DIM}}"

    DEFAULT_NUM_THREADS=1
    NUM_THREADS="${2:-${DEFAULT_NUM_THREADS}}"

    # --- 修改点：在这里控制 Verilator 的警告 ---
    # -Wall: 显示所有警告 (推荐在开发时使用)
    # "" (空字符串): 不显示任何可选警告 (用于获得干净的最终日志)
    # "-Wno-WIDTHEXPAND -Wno-UNUSEDSIGNAL": 只关闭特定的警告
    VERILATOR_FLAGS="-Wall"

    # 设置 OpenMP 环境变量
    export OMP_NUM_THREADS=${NUM_THREADS}

    echo "----------------------------------------"
    echo "脚本开始执行"
    echo "矩阵维度: ${MATRIX_DIM}x${MATRIX_DIM}"
    echo "线程数: ${NUM_THREADS}"
    echo "Verilator 警告标志: '${VERILATOR_FLAGS}'"
    echo "所有日志将同步输出到终端和文件: ${LOG_FILE}"
    echo "----------------------------------------"

    # --- 检查 MATRIX_DIM 是否为 16 的倍数 ---
    if (( MATRIX_DIM % 16 != 0 )); then
        echo "错误：请把matrix宽度修改为16倍数。" >&2
        exit 1
    else
        echo "提示：矩阵宽度 ${MATRIX_DIM} 是 16 的倍数。"
    fi

    echo ""
    echo "步骤 0: 正在更新脚本和 Verilog 文件中的矩阵维度参数..."
    echo "----------------------------------------"
    # 使用 sed 命令修改 InputGen.py 中的 MATRIX_DIM_TB
    # 注意：macOS 的 sed 命令需要 -i 后面跟一个空字符串（''）表示不创建备份文件
    sed -i '' "s/MATRIX_DIM_TB = [0-9]*/MATRIX_DIM_TB = ${MATRIX_DIM}/" InputGen.py
    echo "已更新 InputGen.py 中的 MATRIX_DIM_TB 为 ${MATRIX_DIM}"

    # 使用 sed 命令修改 CheckResult.py 中的 MATRIX_DIM_TB
    sed -i '' "s/MATRIX_DIM_TB = [0-9]*/MATRIX_DIM_TB = ${MATRIX_DIM}/" CheckResult.py
    echo "已更新 CheckResult.py 中的 MATRIX_DIM_TB 为 ${MATRIX_DIM}"

    # --- 新增：修改 tb_accelerator.v 中的 P_MATRIX_SIZE ---
    sed -i '' "s/\(parameter P_MATRIX_SIZE *= *\)[0-9]*;/\1${MATRIX_DIM};/" tb_accelerator.v
    echo "已更新 tb_accelerator.v 中的 P_MATRIX_SIZE 为 ${MATRIX_DIM}"
    echo "----------------------------------------"


    echo ""
    echo "步骤 1: 正在生成输入文件 (input_mem.csv)..."
    echo "----------------------------------------"
    # 传递 VERILATOR_FLAGS, 以防此步骤触发编译
    make generate_input MATRIX_DIM=${MATRIX_DIM} VERILATOR_FLAGS="${VERILATOR_FLAGS}"

    echo ""
    echo "步骤 2: 正在编译并运行仿真..."
    echo "----------------------------------------"
    # 传递 VERILATOR_FLAGS
    make run_sim MATRIX_DIM=${MATRIX_DIM} NUM_THREADS=${NUM_THREADS} VERILATOR_FLAGS="${VERILATOR_FLAGS}"

    echo ""
    echo "步骤 3: 正在重排硬件结果 (result_mem.csv)..."
    echo "----------------------------------------"
    python3 reorder_result_mem.py --matrix_dim ${MATRIX_DIM} --input_csv result_mem.csv --output_csv result_mem_reordered.csv
    cp result_mem.csv result_mem_original.csv
    mv result_mem_reordered.csv result_mem.csv
    echo "重排完成，result_mem.csv 已被更新。"

    echo ""
    echo "步骤 4: 正在检查重排后的仿真结果..."
    echo "----------------------------------------"
    # 传递 VERILATOR_FLAGS, 以防万一
    make check_result VERILATOR_FLAGS="${VERILATOR_FLAGS}"

    echo ""
    echo "----------------------------------------"
    echo "所有步骤成功完成！"
    echo "----------------------------------------"

} 2>&1 | tee -a "${LOG_FILE}"

# 检查管道命令的退出状态
if [ ${PIPESTATUS[0]} -ne 0 ]; then
    echo "脚本执行失败，请检查上面的日志。" >&2
    exit ${PIPESTATUS[0]}
fi

echo "脚本执行成功。详细日志已保存在文件: ${LOG_FILE}"
