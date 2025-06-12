import numpy as np
# import ml_dtypes # Not strictly needed for this specific verification
import os
# import struct # Not used in this version

# --- 全局参数 ---
MATRIX_DIM = 16
TILE_DIM = 16 # For this script, TILE_DIM defines the output block structure from CSV
DATA_TYPE_IN_NP = np.int8 # NumPy data type for loaded A and B matrices

# TILES_PER_ROW_COL determines how many TILE_DIMxTILE_DIM blocks fit in MATRIX_DIM
if MATRIX_DIM % TILE_DIM != 0:
    raise ValueError("MATRIX_DIM must be divisible by TILE_DIM for this script's logic")
TILES_PER_ROW_COL_RESULT = MATRIX_DIM // TILE_DIM # How many tiles in a row/col of the full result

# 每个结果块 (TILE_DIM x TILE_DIM) 占用的64位字数
# BF16输出 (16 bits/element), 64 bits/word => 4 BF16 elements per word
WORDS_PER_BF16_ELEMENTS = 4 # BF16 elements per 64-bit word
ELEMENTS_PER_TILE_ROW = TILE_DIM
WORDS_PER_TILE_ROW = TILE_DIM // WORDS_PER_BF16_ELEMENTS
WORDS_PER_RESULT_TILE_LOGIC = (TILE_DIM * TILE_DIM) // WORDS_PER_BF16_ELEMENTS


# --- 辅助函数 ---
def bfloat16_hex_to_float32(bf16_hex_str):
    """将单个BF16十六进制字符串转换为float32值。"""
    uint16_val = int(bf16_hex_str, 16)
    uint32_val = np.uint32(uint16_val) << 16  # Pad with 16 zeros for mantissa
    return uint32_val.view(np.float32)

def bfloat16_uint16_to_float32_array(bf16_uint16_array):
    """将一个NumPy数组的uint16 (bf16位模式) 转换为float32数组。"""
    bf16_uint16_array = np.asarray(bf16_uint16_array, dtype=np.uint16)
    float32_int_array = (bf16_uint16_array.astype(np.uint32) << 16)
    return float32_int_array.view(np.float32)

def read_hw_result_from_csv_direct(fileName="result_mem.csv"):
    """
    从CSV读取硬件结果 (BF16 hex)，并重组成完整的 MATRIX_DIM x MATRIX_DIM 的 float32 矩阵。
    假设CSV文件中的数据是C矩阵按行主序排列，每行4个BF16值，
    且硬件输出时，C[r][c+3]在高位，C[r][c]在低位。
    """
    hw_result_matrix_f32 = np.zeros((MATRIX_DIM, MATRIX_DIM), dtype=np.float32)
    
    try:
        with open(fileName, "r") as f:
            lines_hex = [line.strip() for line in f.readlines() if line.strip()]
    except FileNotFoundError:
        print(f"Error: {fileName} not found. Ensure the simulation ran and produced this file.")
        return None

    expected_lines = (MATRIX_DIM * MATRIX_DIM) // WORDS_PER_BF16_ELEMENTS
    if len(lines_hex) != expected_lines:
        print(f"Warning: {fileName} has {len(lines_hex)} lines, but {expected_lines} were expected for a {MATRIX_DIM}x{MATRIX_DIM} bfloat16 matrix.")
        if not lines_hex: return None

    bf16_values_flat_uint16 = []
    for line_hex_64bit in lines_hex:
        try:
            val_64bit_int = int(line_hex_64bit, 16)
        except ValueError:
            print(f"Warning: Could not parse hex line '{line_hex_64bit}' in {fileName}. Skipping line.")
            continue
        
        # 硬件输出 res_data_out = {res_val_3_reg, res_val_2_reg, res_val_1_reg, res_val_0_reg};
        # res_val_0_reg 是 C[r][c_base+0] (最低位)
        # res_val_3_reg 是 C[r][c_base+3] (最高位)
        # CSV 文件中，每行是 C[r][c_base+3]C[r][c_base+2]C[r][c_base+1]C[r][c_base+0]
        # 我们需要按 C[r][c_base+0], C[r][c_base+1], ...的顺序排列它们
        bf16_values_flat_uint16.append(np.uint16((val_64bit_int >>  0) & 0xFFFF)) # Element 0 (e.g., C[r][c_base+0])
        bf16_values_flat_uint16.append(np.uint16((val_64bit_int >> 16) & 0xFFFF)) # Element 1 (e.g., C[r][c_base+1])
        bf16_values_flat_uint16.append(np.uint16((val_64bit_int >> 32) & 0xFFFF)) # Element 2 (e.g., C[r][c_base+2])
        bf16_values_flat_uint16.append(np.uint16((val_64bit_int >> 48) & 0xFFFF)) # Element 3 (e.g., C[r][c_base+3])

    if len(bf16_values_flat_uint16) != MATRIX_DIM * MATRIX_DIM:
        print(f"Error: Parsed {len(bf16_values_flat_uint16)} BF16 values, but expected {MATRIX_DIM * MATRIX_DIM}.")
        return None
        
    # 将扁平化的BF16 uint16值转换为float32
    hw_result_flat_f32 = bfloat16_uint16_to_float32_array(np.array(bf16_values_flat_uint16, dtype=np.uint16))
    
    # 重塑为 MATRIX_DIM x MATRIX_DIM
    # CSV文件是按行主序生成的，所以直接reshape
    hw_result_matrix_f32 = hw_result_flat_f32.reshape((MATRIX_DIM, MATRIX_DIM))
    
    return hw_result_matrix_f32

# --- 主程序 ---
def main():
    # 1. 加载原始输入矩阵 A 和 B (int8)
    try:
        matrix_a_orig_sint8 = np.load("matrix_a.npy")
        matrix_b_orig_sint8 = np.load("matrix_b.npy")
    except FileNotFoundError:
        print("Error: matrix_a.npy or matrix_b.npy not found. Run data generation script first.")
        return

    # 2. --- 计算黄金结果 C = A * B ---
    # 硬件内部使用BF16等效值进行计算。
    # 对于小的整数SINT8值，BF16可以精确表示，所以我们可以先将SINT8转为float进行计算。
    matrix_a_float = matrix_a_orig_sint8.astype(np.float32) # Use float32 for golden model
    matrix_b_float = matrix_b_orig_sint8.astype(np.float32)

    print("Calculating golden result C = A_orig * B_orig (using float32 precision)...")
    golden_result_f32 = np.dot(matrix_a_float, matrix_b_float)
    
    np.set_printoptions(threshold=np.inf, linewidth=np.inf, suppress=True, formatter={'float': '{:8.2f}'.format, 'int': '{:4d}'.format})

    print(f"\nMatrix A (original SINT8, {MATRIX_DIM}x{MATRIX_DIM}):\n{matrix_a_orig_sint8}")
    print(f"\nMatrix B (original SINT8, {MATRIX_DIM}x{MATRIX_DIM}):\n{matrix_b_orig_sint8}")
    print(f"\nGolden Result C (calculated as float32, {MATRIX_DIM}x{MATRIX_DIM}):\n{golden_result_f32}")
    print("-" * 40)

    # 3. --- 读取硬件结果 ---
    print("Reading hardware accelerator's result from result_mem.csv...")
    hw_result_f32 = read_hw_result_from_csv_direct(fileName="result_mem.csv")
    
    if hw_result_f32 is None:
        print("Could not parse hardware results. Aborting comparison.")
        return
        
    print(f"\nHW Accelerator Result C (from CSV, converted to float32, {MATRIX_DIM}x{MATRIX_DIM}):")
    # np.set_printoptions(formatter={'float': '{:8.2f}'.format}) # Ensure consistent float printing
    print(hw_result_f32)
    # np.set_printoptions(suppress=False, formatter=None) 


    # 4. --- 比较 ---
    if golden_result_f32.shape != hw_result_f32.shape:
        print(f"\nShape mismatch! Golden: {golden_result_f32.shape}, HW output: {hw_result_f32.shape}")
        return

    # 由于BF16的精度限制，直接比较可能会有微小差异。
    # 我们使用 np.allclose 来检查两个浮点数组是否在一定容差内接近。
    # BF16 的精度大约是 3-4 位十进制有效数字。
    # atol (absolute tolerance) 和 rtol (relative tolerance) 需要根据BF16的特性调整。
    # 对于BF16，尾数有7位，指数8位。
    # 一个简单的检查是看它们是否完全相等（对于整数到BF16的精确转换情况）
    # 或者差异是否非常小。
    
    # 对于我们当前的测试用例 (A=I, B=i+j), C=B。
    # SINT8 (0 to 30) 转换为 BF16 应该是精确的。
    # 所以，我们期望黄金结果 (float32(i+j)) 和硬件结果 (BF16(i+j) -> float32) 几乎完全相同。
    
    absolute_tolerance = 1e-5 # BF16转换引入的误差通常很小，对于精确转换的整数
    relative_tolerance = 1e-4 # 
    
    # 另一种方法是比较它们的整数BF16表示，如果可以从黄金浮点结果精确转回BF16的话。
    # 但直接比较转换后的float32更容易。

    diff = np.abs(golden_result_f32 - hw_result_f32)
    max_abs_diff = np.max(diff)
    avg_abs_diff = np.mean(diff)
    
    num_mismatches = np.sum(~np.isclose(golden_result_f32, hw_result_f32, rtol=relative_tolerance, atol=absolute_tolerance))

    print(f"\n>> Comparison Summary:")
    print(f">> Max Absolute Difference: {max_abs_diff:.4g}")
    print(f">> Average Absolute Difference: {avg_abs_diff:.4g}")
    print(f">> Number of elements with significant difference (rtol={relative_tolerance}, atol={absolute_tolerance}): {num_mismatches} / {golden_result_f32.size}")

    if num_mismatches == 0:
        print("\nCHECK PASSED! Hardware result matches golden result within specified tolerance.")
    else:
        print("\nCHECK FAILED! Hardware result differs from golden result.")
        print("  Indices of first few mismatches (golden vs hw):")
        mismatch_indices = np.where(~np.isclose(golden_result_f32, hw_result_f32, rtol=relative_tolerance, atol=absolute_tolerance))
        for i in range(min(10, len(mismatch_indices[0]))): # Print up to 10 mismatches
            r, c = mismatch_indices[0][i], mismatch_indices[1][i]
            print(f"    C[{r}][{c}]: Golden={golden_result_f32[r,c]:.4f}, HW={hw_result_f32[r,c]:.4f}, Diff={diff[r,c]:.4g}")

if __name__ == "__main__":
    main()