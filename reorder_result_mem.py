import numpy as np
import argparse
import os

# 固定参数
TILE_DIM = 16
WORDS_PER_BF16_ELEMENTS = 4  # 每个64位RAM字包含4个bfloat16元素

def parse_arguments():
    parser = argparse.ArgumentParser(description="将分块矩阵数据从CSV重新排列为行主序CSV。")
    parser.add_argument('--matrix_dim', type=int, required=True, 
                        help="方阵的维度 (例如 32, 48)。必须是TILE_DIM的倍数。")
    parser.add_argument('--input_csv', type=str, default="result_mem.csv", 
                        help="包含硬件原始输出的输入CSV文件名。")
    parser.add_argument('--output_csv', type=str, default="result_mem_reordered.csv", 
                        help="用于保存重排后数据的输出CSV文件名。")
    return parser.parse_args()

def main():
    args = parse_arguments()
    MATRIX_DIM = args.matrix_dim
    input_file_name = args.input_csv
    output_file_name = args.output_csv

    if MATRIX_DIM % TILE_DIM != 0:
        raise ValueError(f"MATRIX_DIM ({MATRIX_DIM}) 必须是 TILE_DIM ({TILE_DIM}) 的整数倍。")

    NUM_TILES_PER_DIM = MATRIX_DIM // TILE_DIM

    # --- 步骤 1: 按硬件输出顺序从输入CSV读取所有bfloat16值 ---
    all_bf16_hw_order_uint16 = []
    try:
        with open(input_file_name, "r") as f:
            lines_hex_ram_words = [line.strip() for line in f.readlines() if line.strip()]
    except FileNotFoundError:
        print(f"错误: 输入文件 '{input_file_name}' 未找到。")
        return

    expected_ram_words = (MATRIX_DIM * MATRIX_DIM) // WORDS_PER_BF16_ELEMENTS
    if len(lines_hex_ram_words) != expected_ram_words:
        print(f"警告: {input_file_name} 文件包含 {len(lines_hex_ram_words)} 行 (RAM字), "
              f"但对于 {MATRIX_DIM}x{MATRIX_DIM} 矩阵，期望的是 {expected_ram_words} 行。")
        # 为调试目的允许继续处理，但这通常表示存在问题。

    for line_idx, line_hex_64bit in enumerate(lines_hex_ram_words):
        try:
            val_64bit_int = int(line_hex_64bit, 16)
        except ValueError:
            print(f"警告: 无法解析文件 {input_file_name} 中行索引 {line_idx} 处的十六进制行 '{line_hex_64bit}'。跳过此行。")
            all_bf16_hw_order_uint16.extend([np.uint16(0)] * WORDS_PER_BF16_ELEMENTS) # 若需要，用0填充缺失元素
            continue
        
        # 提取元素顺序: E0, E1, E2, E3，其中E0在64位字中是LSB对齐的
        elements_in_this_word_uint16 = [
            np.uint16((val_64bit_int >>  0) & 0xFFFF), # 元素 0 
            np.uint16((val_64bit_int >> 16) & 0xFFFF), # 元素 1
            np.uint16((val_64bit_int >> 32) & 0xFFFF), # 元素 2
            np.uint16((val_64bit_int >> 48) & 0xFFFF)  # 元素 3
        ]
        all_bf16_hw_order_uint16.extend(elements_in_this_word_uint16)

    expected_total_elements = MATRIX_DIM * MATRIX_DIM
    if len(all_bf16_hw_order_uint16) != expected_total_elements:
        print(f"错误: 解析得到 {len(all_bf16_hw_order_uint16)} 个BF16值, 但期望 {expected_total_elements} 个。")
        if len(all_bf16_hw_order_uint16) < expected_total_elements:
            print(f"用0填充缺失的 {expected_total_elements - len(all_bf16_hw_order_uint16)} 个元素。")
            all_bf16_hw_order_uint16.extend([np.uint16(0)] * (expected_total_elements - len(all_bf16_hw_order_uint16)))
        else: # 元素过多，截断
            print(f"截断多余的 {len(all_bf16_hw_order_uint16) - expected_total_elements} 个元素。")
            all_bf16_hw_order_uint16 = all_bf16_hw_order_uint16[:expected_total_elements]
        # 根据情况决定如何处理，例如，用零填充或直接返回错误

    # --- 步骤 2: 创建正确顺序（全局行主序）的uint16格式矩阵 ---
    golden_matrix_reshaped_uint16 = np.zeros((MATRIX_DIM, MATRIX_DIM), dtype=np.uint16)

    # --- 步骤 3: 填充 golden_matrix_reshaped_uint16 ---
    # 硬件CSV按顺序存储Tile: Tile(0,0), Tile(0,1), ..., Tile(N-1,N-1)。
    # 每个Tile内部也是行主序。
    current_hw_flat_idx = 0
    for glob_tile_r in range(NUM_TILES_PER_DIM):       # 遍历黄金矩阵中的Tile行
        for glob_tile_c in range(NUM_TILES_PER_DIM):   # 遍历黄金矩阵中的Tile列
            # 这是最终黄金矩阵中的第 (glob_tile_r, glob_tile_c) 个Tile。
            # 其数据来自硬件顺序扁平列表中的第 (glob_tile_r * NUM_TILES_PER_DIM + glob_tile_c) 个Tile。
            
            for r_in_tile in range(TILE_DIM):          # 遍历当前Tile内的行
                for c_in_tile in range(TILE_DIM):      # 遍历当前Tile内的列
                    # 计算在黄金矩阵中的目标全局行和列
                    dest_gr = glob_tile_r * TILE_DIM + r_in_tile
                    dest_gc = glob_tile_c * TILE_DIM + c_in_tile
                    
                    # 从硬件顺序的扁平列表中获取值
                    # all_bf16_hw_order_uint16 中元素的顺序是 Tile接Tile，Tile内部行主序。
                    if current_hw_flat_idx < len(all_bf16_hw_order_uint16):
                        src_val_uint16 = all_bf16_hw_order_uint16[current_hw_flat_idx]
                        golden_matrix_reshaped_uint16[dest_gr, dest_gc] = src_val_uint16
                    else:
                        # 如果源数据不足（例如由于解析警告导致填充不足），这里会出错
                        # 或者我们已经填充了 all_bf16_hw_order_uint16，这里不会越界
                        print(f"警告: 尝试访问索引 {current_hw_flat_idx} 超出 all_bf16_hw_order_uint16 的长度 ({len(all_bf16_hw_order_uint16)})。")
                        golden_matrix_reshaped_uint16[dest_gr, dest_gc] = np.uint16(0) # 明确填充0
                    
                    current_hw_flat_idx += 1
    
    if current_hw_flat_idx != expected_total_elements:
        # 如果初始解析时元素数量不匹配且未完全填充，这里会进一步提示
        print(f"错误/警告: 重排序过程中处理了 {current_hw_flat_idx} 个元素, 但期望处理 {expected_total_elements} 个。")


    # --- 步骤 4: 扁平化正确排序的矩阵 ---
    golden_flat_final_order_uint16 = golden_matrix_reshaped_uint16.flatten() # 行主序扁平化

    # --- 步骤 5: 转换回64位十六进制字并写入新的CSV文件 ---
    output_hex_lines = []
    num_elements_to_write = len(golden_flat_final_order_uint16)

    if num_elements_to_write % WORDS_PER_BF16_ELEMENTS != 0:
        # 如果 MATRIX_DIM*MATRIX_DIM 不是 WORDS_PER_BF16_ELEMENTS 的倍数，则会发生这种情况
        # (如果 TILE_DIM 是 WORDS_PER_BF16_ELEMENTS 的倍数，且 MATRIX_DIM 是 TILE_DIM 的倍数，则为真)
        print(f"警告: 总元素数 {num_elements_to_write} 不是 {WORDS_PER_BF16_ELEMENTS} 的倍数。将填充最后一个字。")
        padding_needed = WORDS_PER_BF16_ELEMENTS - (num_elements_to_write % WORDS_PER_BF16_ELEMENTS)
        golden_flat_final_order_uint16 = np.concatenate(
            (golden_flat_final_order_uint16, np.zeros(padding_needed, dtype=np.uint16))
        )
        num_elements_to_write = len(golden_flat_final_order_uint16)


    for i in range(0, num_elements_to_write, WORDS_PER_BF16_ELEMENTS):
        elements_to_pack = golden_flat_final_order_uint16[i : i + WORDS_PER_BF16_ELEMENTS]
        
        val_64bit = np.uint64(0)
        # 打包 E0 (LSB), E1, E2, E3 (MSB)
        val_64bit |= np.uint64(elements_to_pack[0])
        val_64bit |= (np.uint64(elements_to_pack[1]) << 16)
        val_64bit |= (np.uint64(elements_to_pack[2]) << 32)
        val_64bit |= (np.uint64(elements_to_pack[3]) << 48)
        
        hex_line = format(val_64bit, '016x')
        output_hex_lines.append(hex_line)

    try:
        with open(output_file_name, "w") as f:
            for line in output_hex_lines:
                f.write(line + "\n")
        print(f"成功重排数据并保存到 '{output_file_name}'。")
    except IOError:
        print(f"错误: 无法写入输出文件 '{output_file_name}'。")

if __name__ == "__main__":
    main()