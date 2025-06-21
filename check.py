import numpy as np
import os

# --- 全局参数 ---
TILE_DIM = 32
PE_ACCUM_BITS = 32
RAM_DATA_WIDTH = 64
SINT32_PER_RAM_WORD = RAM_DATA_WIDTH // PE_ACCUM_BITS
MATRIX_DIM = 512

# --- 文件名 ---
HW_OUTPUT_FILE = "result_mem.csv"
GOLDEN_FILE = "matrix_c_expected_sint32.npy"


def parse_and_reorder_hw_data(input_csv, matrix_dim):
    """
    解析硬件数据，并使用“列主序Tile + Tile内部转置”的逻辑进行重排。
    """
    print(f"正在从 '{input_csv}' 解析并按“列主序Tile + 内部转置”逻辑重排...")
    
    # --- 步骤 1: 解析CSV到一维列表 (不变) ---
    all_sint32_hw_order = []
    try:
        with open(input_csv, "r") as f:
            lines_hex_ram_words = [line.strip() for line in f.readlines() if line.strip()]
    except FileNotFoundError: return None
    for line_hex_ram_word in lines_hex_ram_words:
        try:
            val_ram_word_int = int(line_hex_ram_word, 16)
            for i in range(SINT32_PER_RAM_WORD):
                element_uint32 = (val_ram_word_int >> (i * PE_ACCUM_BITS)) & ((1 << PE_ACCUM_BITS) - 1)
                if element_uint32 >= (1 << (PE_ACCUM_BITS - 1)):
                    element_sint32 = element_uint32 - (1 << PE_ACCUM_BITS)
                else: element_sint32 = element_uint32
                all_sint32_hw_order.append(np.int32(element_sint32))
        except ValueError: all_sint32_hw_order.extend([np.int32(0)] * SINT32_PER_RAM_WORD)
    
    expected_elements = matrix_dim * matrix_dim
    if len(all_sint32_hw_order) != expected_elements:
        if len(all_sint32_hw_order) < expected_elements: all_sint32_hw_order.extend([np.int32(0)] * (expected_elements - len(all_sint32_hw_order)))
        else: all_sint32_hw_order = all_sint32_hw_order[:expected_elements]

    # --- 步骤 2: 创建目标矩阵并进行终极重排 ---
    reordered_matrix = np.zeros((matrix_dim, matrix_dim), dtype=np.int32)
    num_tiles_per_dim = matrix_dim // TILE_DIM
    elements_per_tile = TILE_DIM * TILE_DIM

    # 宏观Tile遍历顺序：列主序 (Column-Major)
    for glob_tile_c in range(num_tiles_per_dim):
        for glob_tile_r in range(num_tiles_per_dim):
            # 计算当前Tile在一维数据流中的起始和结束位置
            tile_start_idx = (glob_tile_c * num_tiles_per_dim + glob_tile_r) * elements_per_tile
            tile_end_idx = tile_start_idx + elements_per_tile
            
            # 从一维数据流中提取出当前Tile的数据
            tile_flat_data = all_sint32_hw_order[tile_start_idx:tile_end_idx]
            
            # 假定硬件输出的Tile内部是行主序，我们将其还原
            # 但如果硬件在写入时进行了转置，我们需要在这里转置回来！
            temp_tile_matrix = np.array(tile_flat_data).reshape((TILE_DIM, TILE_DIM))
            
            # ############# 核心修改：增加转置操作 #############
            final_tile_matrix = temp_tile_matrix.T
            # ####################################################

            # 将修正后的Tile块放回最终大矩阵的正确位置
            dest_r_start = glob_tile_r * TILE_DIM
            dest_r_end = dest_r_start + TILE_DIM
            dest_c_start = glob_tile_c * TILE_DIM
            dest_c_end = dest_c_start + TILE_DIM
            
            reordered_matrix[dest_r_start:dest_r_end, dest_c_start:dest_c_end] = final_tile_matrix
    
    print("数据重排完成。")
    return reordered_matrix


def main():
    try:
        golden_c_sint32 = np.load(GOLDEN_FILE)
    except FileNotFoundError:
        print(f"错误: 黄金标准文件 '{GOLDEN_FILE}' 未找到。")
        return

    hw_result_reordered = parse_and_reorder_hw_data(HW_OUTPUT_FILE, MATRIX_DIM)
    if hw_result_reordered is None: return

    original_print_options = np.get_printoptions()
    np.set_printoptions(linewidth=200, formatter={'int_kind': '{:9d}'.format})

    print("\n--- 开始最终验证 ---")
    is_match = np.array_equal(golden_c_sint32, hw_result_reordered)

    if is_match:
        print("\n>> PASSED: 重排后的硬件结果与黄金标准完全匹配！问题解决！")
    else:
        print("\n>> FAILED: '列主序Tile + Tile内部转置' 的假说依然不完全正确。")
        
        DISPLAY_SUB_DIM = min(MATRIX_DIM, 16)
        print("\nGolden (Expected) Matrix:")
        print(golden_c_sint32[:DISPLAY_SUB_DIM, :DISPLAY_SUB_DIM])
        print("\nHW (Reordered using Final Hypothesis) Matrix:")
        print(hw_result_reordered[:DISPLAY_SUB_DIM, :DISPLAY_SUB_DIM])
        
        # 如果依然失败，可以调用之前的Tile诊断函数
        # compare_matrices_tile_by_tile(golden_c_sint32, hw_result_reordered, TILE_DIM)

    np.set_printoptions(**original_print_options)


if __name__ == "__main__":
    main()