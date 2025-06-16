import numpy as np
import os

# --- 全局参数 ---
MATRIX_DIM = 128
TILE_DIM = 16 # 保持瓦片维度，因为硬件设计是基于瓦片的
DATA_TYPE_IN = np.int8

# 确保参数匹配 (如果 TILE_DIM 仍然相关于如何写入文件)
if MATRIX_DIM % TILE_DIM != 0:
    raise ValueError("MATRIX_DIM must be divisible by TILE_DIM for tiled writing, if still used.")

TILES_PER_ROW_COL = MATRIX_DIM // TILE_DIM # 如果按瓦片写入，则需要
SINT8_PER_MEM_WORD = 8

# --- 辅助函数 ---
def number_to_sint8_hex(number):
    """将一个整数转换为其8位有符号补码的2字符十六进制表示。"""
    py_int_number = int(number)
    # Clamp to SINT8 range
    if py_int_number > 127: py_int_number = 127
    elif py_int_number < -128: py_int_number = -128

    if py_int_number < 0:
        # 2's complement for negative numbers
        py_int_number = (1 << 8) + py_int_number
    return f'{py_int_number:02x}'

def convert_matrix_to_tiled_hex_row_major(matrix_to_convert):
    """
    将整个矩阵按行主序（非瓦片化，但仍然按SINT8_PER_MEM_WORD分块）转换为十六进制行。
    这是为了确保数据在 input_mem.csv 中是连续的，与硬件的线性读取方式匹配。
    """
    hex_lines = []
    flat_matrix = matrix_to_convert.flatten() # 将整个矩阵展平

    for i in range(0, len(flat_matrix), SINT8_PER_MEM_WORD):
        chunk = flat_matrix[i : i + SINT8_PER_MEM_WORD]
        # RAM通常是小端存储字节，所以数组中靠后的元素在字的低位
        hex_word = "".join([number_to_sint8_hex(n) for n in reversed(chunk)])
        hex_lines.append(hex_word)
    return hex_lines

# --- 主程序 ---
def main():
    print(f"Generating {MATRIX_DIM}x{MATRIX_DIM} specific SINT8 matrices.")

    # --- 1. 生成矩阵 A (规则变化的 SINT8 矩阵) ---
    matrix_a_orig = np.zeros((MATRIX_DIM, MATRIX_DIM), dtype=DATA_TYPE_IN)
    current_val = 0
    for r in range(MATRIX_DIM):
        for c in range(MATRIX_DIM):
            matrix_a_orig[r, c] = current_val
            current_val += 1
            if current_val > 127: # SINT8 上溢处理
                current_val = -128

    # --- 2. 生成矩阵 B (B[0,0]=1,其余为0) ---
    matrix_b_orig = np.zeros((MATRIX_DIM, MATRIX_DIM), dtype=DATA_TYPE_IN)
    matrix_b_orig[0, 0] = 1
    matrix_b_orig[1, 0] = 2

    # --- 转换为硬件布局 (按行主序写入整个矩阵) ---
    # 硬件的读取逻辑是按瓦片进行的，但写入input_mem.csv时，
    # 我们需要确保A的第一个瓦片A[0,0]的数据先写入，然后是A[0,1]的数据，等等。
    # 这意味着我们需要先将整个A矩阵按瓦片顺序重组，然后再写入。
    # 或者，更简单的方法是，硬件在读取时自行处理瓦片地址计算，
    # 我们只需按全局行主序将A和B写入文件。
    #
    # 鉴于硬件的 `base_addr_a + (r_c_idx * NUM_TILES + k_idx) * WORDS_PER_TILE`
    # 这种寻址方式，它期望的是矩阵A的不同瓦片在内存中是连续排列的。
    # A_tile[r_tile_idx][c_tile_idx]
    # 内存布局:
    # A_tile[0][0]
    # A_tile[0][1]
    # ...
    # A_tile[0][TILES_PER_ROW_COL-1]
    # A_tile[1][0]
    # ...

    all_hex_lines_a = []
    for tile_row_idx in range(TILES_PER_ROW_COL):
        for tile_col_idx in range(TILES_PER_ROW_COL):
            start_r = tile_row_idx * TILE_DIM
            end_r = start_r + TILE_DIM
            start_c = tile_col_idx * TILE_DIM
            end_c = start_c + TILE_DIM
            
            current_tile_a = matrix_a_orig[start_r:end_r, start_c:end_c]
            all_hex_lines_a.extend(convert_matrix_to_tiled_hex_row_major(current_tile_a))

    all_hex_lines_b = []
    for tile_row_idx in range(TILES_PER_ROW_COL):
        for tile_col_idx in range(TILES_PER_ROW_COL):
            start_r = tile_row_idx * TILE_DIM
            end_r = start_r + TILE_DIM
            start_c = tile_col_idx * TILE_DIM
            end_c = start_c + TILE_DIM

            current_tile_b = matrix_b_orig[start_r:end_r, start_c:end_c]
            all_hex_lines_b.extend(convert_matrix_to_tiled_hex_row_major(current_tile_b))


    output_file = "input_mem.csv"
    with open(output_file, "w") as f:
        print(f"\nWriting A matrix tiles to {output_file}...")
        for line_idx, line in enumerate(all_hex_lines_a):
            f.write(f"{line}\n")
            # if line_idx < 5 or line_idx > len(all_hex_lines_a) - 5 : # 打印开头和结尾几行A的数据
            #     print(f"  A_line {line_idx}: {line}")
        print(f"Finished writing A. Wrote {len(all_hex_lines_a)} lines for A.")

        print(f"\nWriting B matrix tiles to {output_file}...")
        for line_idx, line in enumerate(all_hex_lines_b):
            f.write(f"{line}\n")
            # if line_idx < 5 or line_idx > len(all_hex_lines_b) - 5 : # 打印开头和结尾几行B的数据
            #     print(f"  B_line {line_idx}: {line}")
        print(f"Finished writing B. Wrote {len(all_hex_lines_b)} lines for B.")


    # --- 保存原始矩阵以供验证 ---
    np.save('matrix_a.npy', matrix_a_orig)
    np.save('matrix_b.npy', matrix_b_orig)

    print(f"\nGenerated {output_file}, matrix_a.npy, and matrix_b.npy successfully.")

    # --- (可选) 计算并打印预期的C矩阵 (用于手动粗略检查) ---
    matrix_a_float = matrix_a_orig.astype(np.float32) # 使用更高精度进行黄金结果计算
    matrix_b_float = matrix_b_orig.astype(np.float32)
    expected_c_float = np.dot(matrix_a_float, matrix_b_float)

    print("\nExpected C matrix (float values, showing top-left 4x4 for reference):")
    # np.set_printoptions(threshold=np.inf, linewidth=np.inf, suppress=True, formatter={'float': '{:8.1f}'.format})
    print(expected_c_float[:4,:4])
    # np.set_printoptions(threshold=1000, linewidth=75, suppress=False, formatter=None) # Reset

if __name__ == "__main__":
    main()