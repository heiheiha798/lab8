import numpy as np
import os

# --- 全局参数 ---
MATRIX_DIM = 32
TILE_DIM = 32
DATA_TYPE_IN = np.int8
SPARSITY_NON_ZERO_RATIO = 0.35 # 35% non-zero elements
RANDOM_SEED = 42 # For reproducible random numbers
SINT8_MIN_VAL = -10 # Min value for random non-zero SINT8
SINT8_MAX_VAL = 10  # Max value for random non-zero SINT8 (exclusive for np.random.randint high)

# 确保参数匹配
if MATRIX_DIM % TILE_DIM != 0:
    raise ValueError("MATRIX_DIM must be divisible by TILE_DIM")

TILES_PER_ROW_COL = MATRIX_DIM // TILE_DIM
SINT8_PER_MEM_WORD = 8

# --- 辅助函数 (基本不变) ---
def number_to_sint8_hex(number):
    """将一个整数转换为其8位有符号补码的2字符十六进制表示。"""
    py_int_number = int(number)
    # Clamp to SINT8 range just in case, though np.int8 should handle it
    if py_int_number > 127: py_int_number = 127
    elif py_int_number < -128: py_int_number = -128
        
    if py_int_number < 0:
        py_int_number = (1 << 8) + py_int_number 
    return f'{py_int_number:02x}'

def convert_matrix_to_tiled_hex(matrix_to_convert, is_transpose_a=False):
    """
    通用函数，将矩阵（A转置或B）按行主序分块写入。
    如果 is_transpose_a 为 True, 则先对输入矩阵进行转置。
    """
    if is_transpose_a:
        processed_matrix = matrix_to_convert.T
        # print("  Processing A_transpose...") # Keep prints minimal for this version
    else:
        processed_matrix = matrix_to_convert
        # print("  Processing B_original...")
        
    hex_lines = []
    for i_tile in range(TILES_PER_ROW_COL):
        for j_tile in range(TILES_PER_ROW_COL):
            start_row = i_tile * TILE_DIM
            start_col = j_tile * TILE_DIM
            tile = processed_matrix[start_row : start_row + TILE_DIM, start_col : start_col + TILE_DIM]
            tile_flat = tile.flatten()

            for i in range(0, len(tile_flat), SINT8_PER_MEM_WORD):
                chunk = tile_flat[i : i + SINT8_PER_MEM_WORD]
                hex_word = "".join([number_to_sint8_hex(n) for n in reversed(chunk)])
                hex_lines.append(hex_word)
    return hex_lines

def generate_sparse_random_matrix(rows, cols, dtype, non_zero_ratio, min_val, max_val, rng_gen):
    """生成一个具有指定非零元素比例的随机SINT8矩阵。"""
    matrix = np.zeros((rows, cols), dtype=dtype)
    num_elements = rows * cols
    num_non_zeros = int(num_elements * non_zero_ratio)

    # 生成非零值
    non_zero_values = rng_gen.integers(min_val, max_val, size=num_non_zeros, dtype=dtype)
    # 确保有一些负数，如果范围允许
    if min_val < 0 and max_val > 0:
        # Flip sign of roughly half of the non-zero values if they are positive
        # This is a simple way to introduce negative numbers
        for i in range(num_non_zeros // 2):
            if non_zero_values[i] > 0 : # Only flip positive to negative
                 non_zero_values[i] *= -1
            elif non_zero_values[i] == 0 and min_val < 0: # if it picked 0 and we want non-zero
                 non_zero_values[i] = rng_gen.integers(min_val, 0, dtype=dtype)


    # 随机选择非零元素的位置
    flat_indices = np.arange(num_elements)
    rng_gen.shuffle(flat_indices)
    non_zero_indices_flat = flat_indices[:num_non_zeros]

    # 将非零值放入矩阵
    current_non_zero_idx = 0
    for flat_idx in non_zero_indices_flat:
        r, c = np.unravel_index(flat_idx, (rows, cols))
        matrix[r, c] = non_zero_values[current_non_zero_idx]
        current_non_zero_idx += 1
        
    return matrix

# --- 主程序 ---
def main():
    print(f"Generating {MATRIX_DIM}x{MATRIX_DIM} sparse random SINT8 matrices.")
    print(f"Target non-zero ratio: {SPARSITY_NON_ZERO_RATIO*100}%")
    print(f"Random SINT8 values between: [{SINT8_MIN_VAL}, {SINT8_MAX_VAL-1}]") # Max_val is exclusive for randint
    
    rng = np.random.default_rng(seed=RANDOM_SEED) # Initialize random number generator

    # --- 1. 生成稀疏随机矩阵 A ---
    matrix_a_orig = generate_sparse_random_matrix(
        MATRIX_DIM, MATRIX_DIM, DATA_TYPE_IN, 
        SPARSITY_NON_ZERO_RATIO, SINT8_MIN_VAL, SINT8_MAX_VAL, rng
    )
    # print("\nMatrix A (Original Sparse Random SINT8):")
    # print(matrix_a_orig)

    # --- 2. 生成稀疏随机矩阵 B ---
    matrix_b_orig = generate_sparse_random_matrix(
        MATRIX_DIM, MATRIX_DIM, DATA_TYPE_IN,
        SPARSITY_NON_ZERO_RATIO, SINT8_MIN_VAL, SINT8_MAX_VAL, rng
    )
    # print("\nMatrix B (Original Sparse Random SINT8):")
    # print(matrix_b_orig)

    # --- 转换为硬件布局 ---
    # print("\nConverting matrices to hardware-specific tiled layouts...")
    hex_lines_for_buffer_a = convert_matrix_to_tiled_hex(matrix_a_orig, is_transpose_a=True)
    hex_lines_for_buffer_b = convert_matrix_to_tiled_hex(matrix_b_orig, is_transpose_a=False)
    
    output_file = "input_mem.csv"
    with open(output_file, "w") as f:
        for line in hex_lines_for_buffer_a:
            f.write(f"{line}\n")
        for line in hex_lines_for_buffer_b:
            f.write(f"{line}\n")

    # --- 保存原始矩阵以供验证 ---
    np.save('matrix_a.npy', matrix_a_orig)
    np.save('matrix_b.npy', matrix_b_orig)
    
    print(f"\nGenerated {output_file}, matrix_a.npy, and matrix_b.npy successfully.")

    # --- (可选) 计算并打印预期的C矩阵 (用于手动粗略检查) ---
    matrix_a_float = matrix_a_orig.astype(float) # Or np.float32
    matrix_b_float = matrix_b_orig.astype(float) # Or np.float32
    expected_c_float = np.dot(matrix_a_float, matrix_b_float)
    
    # print("\nExpected C matrix (float values, for reference):")
    # np.set_printoptions(threshold=np.inf, linewidth=np.inf, suppress=True, formatter={'float': '{:8.1f}'.format})
    # print(expected_c_float)
    # np.set_printoptions(threshold=1000, linewidth=75, suppress=False, formatter=None) # Reset
    
if __name__ == "__main__":
    main()