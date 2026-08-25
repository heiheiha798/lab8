import numpy as np
import argparse
import os

# --- 输出目录: 所有中间文件统一放到仓库根目录下的 output/ ---
REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUTPUT_DIR = os.path.join(REPO_ROOT, "output")

# 固定参数
TILE_DIM = 16
PE_ACCUM_BITS = 32   # 结果元素位宽
RAM_DATA_WIDTH = 64  # RAM字位宽
SINT32_PER_RAM_WORD = RAM_DATA_WIDTH // PE_ACCUM_BITS

if RAM_DATA_WIDTH % PE_ACCUM_BITS != 0:
    raise ValueError("RAM_DATA_WIDTH must be a multiple of PE_ACCUM_BITS.")


def parse_arguments():
    parser = argparse.ArgumentParser(description="Reorder tiled SINT32 matrix data from CSV to row-major CSV.")
    parser.add_argument('--matrix_dim', type=int, required=True,
                        help="Dimension of the square matrix. Must be a multiple of TILE_DIM.")
    parser.add_argument('--input_csv', type=str, default=os.path.join(OUTPUT_DIR, "result_mem.csv"),
                        help="Input CSV file name containing raw hardware output.")
    parser.add_argument('--output_csv', type=str, default=os.path.join(OUTPUT_DIR, "result_mem_reordered_sint32.csv"),
                        help="Output CSV file name for reordered data.")
    return parser.parse_args()

def main():
    args = parse_arguments()
    MATRIX_DIM = args.matrix_dim
    input_file_name = args.input_csv
    output_file_name = args.output_csv

    if MATRIX_DIM % TILE_DIM != 0:
        raise ValueError(f"MATRIX_DIM ({MATRIX_DIM}) must be a multiple of TILE_DIM ({TILE_DIM}).")

    NUM_TILES_PER_DIM = MATRIX_DIM // TILE_DIM

    # --- 步骤 1: 从输入CSV读取所有SINT32值 (硬件输出顺序) ---
    all_sint32_hw_order = []
    try:
        with open(input_file_name, "r") as f:
            lines_hex_ram_words = [line.strip() for line in f.readlines() if line.strip()]
    except FileNotFoundError:
        print(f"错误: 输入文件 '{input_file_name}' 未找到。")
        return

    expected_ram_words = (MATRIX_DIM * MATRIX_DIM * PE_ACCUM_BITS) // RAM_DATA_WIDTH
    if (MATRIX_DIM * MATRIX_DIM * PE_ACCUM_BITS) % RAM_DATA_WIDTH != 0:
        expected_ram_words +=1

    if len(lines_hex_ram_words) != expected_ram_words:
        print(f"警告: {input_file_name} 文件包含 {len(lines_hex_ram_words)} 行 (RAM字), "
              f"但对于 {MATRIX_DIM}x{MATRIX_DIM} SINT32矩阵，期望的是 {expected_ram_words} 行。")

    for line_idx, line_hex_ram_word in enumerate(lines_hex_ram_words):
        try:
            val_ram_word_int = int(line_hex_ram_word, 16)
        except ValueError:
            print(f"警告: 无法解析文件 {input_file_name} 中行索引 {line_idx} 处的十六进制行 '{line_hex_ram_word}'。用0填充。")
            all_sint32_hw_order.extend([np.int32(0)] * SINT32_PER_RAM_WORD)
            continue

        elements_in_this_word = []
        for i in range(SINT32_PER_RAM_WORD):
            element_uint32 = (val_ram_word_int >> (i * PE_ACCUM_BITS)) & ((1 << PE_ACCUM_BITS) - 1)
            if element_uint32 >= (1 << (PE_ACCUM_BITS - 1)):
                element_sint32 = element_uint32 - (1 << PE_ACCUM_BITS)
            else:
                element_sint32 = element_uint32
            elements_in_this_word.append(np.int32(element_sint32))
        all_sint32_hw_order.extend(elements_in_this_word)

    expected_total_elements = MATRIX_DIM * MATRIX_DIM
    if len(all_sint32_hw_order) != expected_total_elements:
        print(f"错误: 解析得到 {len(all_sint32_hw_order)} 个SINT32值, 但期望 {expected_total_elements} 个。")
        if len(all_sint32_hw_order) < expected_total_elements:
            print(f"用0填充缺失的 {expected_total_elements - len(all_sint32_hw_order)} 个元素。")
            all_sint32_hw_order.extend([np.int32(0)] * (expected_total_elements - len(all_sint32_hw_order)))
        else:
            print(f"截断多余的 {len(all_sint32_hw_order) - expected_total_elements} 个元素。")
            all_sint32_hw_order = all_sint32_hw_order[:expected_total_elements]

    # --- 步骤 2: 创建正确顺序（全局行主序）的SINT32格式矩阵 ---
    golden_matrix_reshaped_sint32 = np.zeros((MATRIX_DIM, MATRIX_DIM), dtype=np.int32)

    # --- 步骤 3: 填充 golden_matrix_reshaped_sint32 ---
    # 硬件CSV按顺序存储Tile: Tile(0,0), Tile(0,1), ..., Tile(N-1,N-1)。
    # 每个Tile内部也是行主序。
    current_hw_flat_idx = 0
    for glob_tile_r in range(NUM_TILES_PER_DIM):
        for glob_tile_c in range(NUM_TILES_PER_DIM):
            for r_in_tile in range(TILE_DIM):
                for c_in_tile in range(TILE_DIM):
                    dest_gr = glob_tile_r * TILE_DIM + r_in_tile
                    dest_gc = glob_tile_c * TILE_DIM + c_in_tile
                    if current_hw_flat_idx < len(all_sint32_hw_order):
                        src_val_sint32 = all_sint32_hw_order[current_hw_flat_idx]
                        golden_matrix_reshaped_sint32[dest_gr, dest_gc] = src_val_sint32
                    else:
                        golden_matrix_reshaped_sint32[dest_gr, dest_gc] = np.int32(0)
                    current_hw_flat_idx += 1

    if current_hw_flat_idx != expected_total_elements:
        print(f"错误/警告: 重排序过程中处理了 {current_hw_flat_idx} 个元素, 但期望处理 {expected_total_elements} 个。")

    # --- 步骤 4: 扁平化正确排序的矩阵 ---
    golden_flat_final_order_sint32 = golden_matrix_reshaped_sint32.flatten()

    # --- 步骤 5: 转换回64位十六进制字并写入新的CSV文件 ---
    output_hex_lines = []
    num_elements_to_write = len(golden_flat_final_order_sint32)

    if num_elements_to_write % SINT32_PER_RAM_WORD != 0:
        print(f"警告: 总元素数 {num_elements_to_write} 不是 {SINT32_PER_RAM_WORD} 的倍数。将填充最后一个字。")
        padding_needed = SINT32_PER_RAM_WORD - (num_elements_to_write % SINT32_PER_RAM_WORD)
        padding_array = np.zeros(padding_needed, dtype=np.int32)
        golden_flat_final_order_sint32 = np.concatenate(
            (golden_flat_final_order_sint32, padding_array)
        )
        num_elements_to_write = len(golden_flat_final_order_sint32)

    for i in range(0, num_elements_to_write, SINT32_PER_RAM_WORD):
        elements_to_pack_sint32 = golden_flat_final_order_sint32[i : i + SINT32_PER_RAM_WORD]
        val_ram_word_py_int = 0
        for k in range(SINT32_PER_RAM_WORD):
            element_sint32 = int(elements_to_pack_sint32[k]) # Python int
            # 转换为无符号整数进行位移
            if element_sint32 < 0:
                element_uint32 = element_sint32 + (1 << PE_ACCUM_BITS)
            else:
                element_uint32 = element_sint32
            val_ram_word_py_int |= (element_uint32 << (k * PE_ACCUM_BITS))

        hex_line = format(val_ram_word_py_int, f'0{RAM_DATA_WIDTH//4}x') # 例如 '016x' for 64-bit
        output_hex_lines.append(hex_line)

    try:
        with open(output_file_name, "w") as f:
            for line in output_hex_lines:
                f.write(line + "\n")
        print(f"成功重排SINT32数据并保存到 '{output_file_name}'。")
    except IOError:
        print(f"错误: 无法写入输出文件 '{output_file_name}'。")

if __name__ == "__main__":
    main()