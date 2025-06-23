import numpy as np
import os
import math # For exp
import random # 导入 random 模块

# --- Testbench 参数 (与 testbench_top.v 匹配) ---
MATRIX_DIM_TB = 48
TILE_DIM_TB = 16
RAM_DATA_WIDTH_TB = 64
SINT8_BITS_TB = 8

DATA_TYPE_IN = np.int8

if MATRIX_DIM_TB % TILE_DIM_TB != 0:
    raise ValueError("MATRIX_DIM_TB must be divisible by TILE_DIM_TB.")

TILES_PER_ROW_COL_TB = MATRIX_DIM_TB // TILE_DIM_TB
SINT8_PER_MEM_WORD_TB = RAM_DATA_WIDTH_TB // SINT8_BITS_TB

# --- 辅助函数 (number_to_sint8_hex, convert_tile_to_hex_lines_row_major) ---
# 这部分可以保持不变，因为它处理SINT8和基于SINT8_PER_MEM_WORD_TB的打包。
def number_to_sint8_hex(number):
    py_int_number = int(number)
    if py_int_number > 127: py_int_number = 127
    elif py_int_number < -128: py_int_number = -128
    if py_int_number < 0:
        py_int_number = (1 << 8) + py_int_number
    return f'{py_int_number:02x}'

def convert_tile_to_hex_lines_row_major(tile_matrix):
    hex_lines = []
    flat_tile = tile_matrix.flatten()
    for i in range(0, len(flat_tile), SINT8_PER_MEM_WORD_TB):
        chunk = flat_tile[i : i + SINT8_PER_MEM_WORD_TB]
        # 注意：这里假设 SINT8_PER_MEM_WORD_TB 是 8，并且每个字是 64 位。
        # SINT8_PER_MEM_WORD_TB = RAM_DATA_WIDTH_TB // SINT8_BITS_TB = 64 // 8 = 8
        # 所以是 8 个 SINT8 组成一个 64 位字。
        # 'reversed(chunk)' 是为了 LSB (Least Significant Bit) first 的顺序
        hex_word = "".join([number_to_sint8_hex(n) for n in reversed(chunk)])
        hex_lines.append(hex_word)
    return hex_lines

# --- 主程序 ---
def main():
    print(f"Generating {MATRIX_DIM_TB}x{MATRIX_DIM_TB} SINT8 matrices for testbench.")

    # 定义零的比例
    ZERO_PERCENTAGE = 0.35
    total_elements = MATRIX_DIM_TB * MATRIX_DIM_TB
    num_zeros = int(total_elements * ZERO_PERCENTAGE)

    # --- 1. 生成矩阵 A (随机 SINT8, 包含 35% 的 0) ---
    matrix_a_orig = np.random.randint(-128, 128, size=(MATRIX_DIM_TB, MATRIX_DIM_TB), dtype=DATA_TYPE_IN)
    # 随机选择 num_zeros 个索引将其设为 0
    zero_indices_a = np.random.choice(total_elements, num_zeros, replace=False)
    matrix_a_orig.ravel()[zero_indices_a] = 0 # 使用 ravel() 展平数组并设置元素

    # --- 2. 生成矩阵 B (随机 SINT8, 包含 35% 的 0) ---
    matrix_b_orig = np.random.randint(-128, 128, size=(MATRIX_DIM_TB, MATRIX_DIM_TB), dtype=DATA_TYPE_IN)
    # 随机选择 num_zeros 个索引将其设为 0
    zero_indices_b = np.random.choice(total_elements, num_zeros, replace=False)
    matrix_b_orig.ravel()[zero_indices_b] = 0

    all_hex_lines_a = []
    # 由于 MATRIX_DIM_TB == TILE_DIM_TB, TILES_PER_ROW_COL_TB = 1
    # 循环只会迭代一次
    for tile_row_global_idx in range(TILES_PER_ROW_COL_TB):
        for tile_col_global_idx in range(TILES_PER_ROW_COL_TB):
            start_r = tile_row_global_idx * TILE_DIM_TB
            end_r = start_r + TILE_DIM_TB
            start_c = tile_col_global_idx * TILE_DIM_TB
            end_c = start_c + TILE_DIM_TB
            current_tile_a = matrix_a_orig[start_r:end_r, start_c:end_c]
            all_hex_lines_a.extend(convert_tile_to_hex_lines_row_major(current_tile_a))

    all_hex_lines_b = []
    for tile_row_global_idx in range(TILES_PER_ROW_COL_TB):
        for tile_col_global_idx in range(TILES_PER_ROW_COL_TB):
            start_r = tile_row_global_idx * TILE_DIM_TB
            end_r = start_r + TILE_DIM_TB
            start_c = tile_col_global_idx * TILE_DIM_TB
            end_c = start_c + TILE_DIM_TB
            current_tile_b = matrix_b_orig[start_r:end_r, start_c:end_c]
            all_hex_lines_b.extend(convert_tile_to_hex_lines_row_major(current_tile_b))

    output_file = "input_mem.csv"
    with open(output_file, "w") as f:
        print(f"\nWriting A matrix tiles to {output_file}...")
        for line in all_hex_lines_a:
            f.write(f"{line}\n")

        print(f"\nWriting B matrix tiles to {output_file}...")
        for line in all_hex_lines_b:
            f.write(f"{line}\n")

    np.save('matrix_a.npy', matrix_a_orig) # 保存SINT8
    np.save('matrix_b.npy', matrix_b_orig) # 保存SINT8

    # --- 计算预期的C矩阵 (精确SINT32) ---
    matrix_a_calc = matrix_a_orig.astype(np.int64) # 使用int64以防中间累加溢出
    matrix_b_calc = matrix_b_orig.astype(np.int64)
    expected_c_exact_int64 = np.dot(matrix_a_calc, matrix_b_calc)
    
    # 检查SINT32范围，虽然对于16x16 SINT8输入，结果通常不会溢出SINT32
    if np.any(expected_c_exact_int64 > 2**31 - 1) or np.any(expected_c_exact_int64 < -(2**31)):
        print("Warning: Expected C matrix elements exceed SINT32 range during calculation!")
    expected_c_sint32 = expected_c_exact_int64.astype(np.int32) # 硬件累加器是SINT32
    np.save('matrix_c_expected_sint32.npy', expected_c_sint32)

if __name__ == "__main__":
    main()