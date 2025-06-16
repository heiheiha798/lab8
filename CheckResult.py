import numpy as np
import os

# --- 全局参数 ---
MATRIX_DIM = 128
TILE_DIM = 16 
DATA_TYPE_IN_NP = np.int8

if MATRIX_DIM % TILE_DIM != 0:
    raise ValueError("MATRIX_DIM must be divisible by TILE_DIM for this script's logic")
TILES_PER_ROW_COL_HW = MATRIX_DIM // TILE_DIM # How many tiles in a row/col of the full matrix as stored/processed by HW

WORDS_PER_BF16_ELEMENTS = 4 
ELEMENTS_PER_TILE_ROW = TILE_DIM
WORDS_PER_TILE_ROW_IN_CSV = TILE_DIM // WORDS_PER_BF16_ELEMENTS # How many 64-bit RAM words for one row of a tile
WORDS_PER_RESULT_TILE_IN_CSV = (TILE_DIM * TILE_DIM) // WORDS_PER_BF16_ELEMENTS

# --- 辅助函数 ---
def bfloat16_hex_to_float32(bf16_hex_str):
    uint16_val = int(bf16_hex_str, 16)
    uint32_val = np.uint32(uint16_val) << 16
    return uint32_val.view(np.float32)

def bfloat16_uint16_to_float32_array(bf16_uint16_array):
    bf16_uint16_array = np.asarray(bf16_uint16_array, dtype=np.uint16)
    float32_int_array = (bf16_uint16_array.astype(np.uint32) << 16)
    return float32_int_array.view(np.float32)

def read_hw_result_from_csv_direct(fileName="result_mem.csv"):
    hw_result_matrix_f32_from_csv = np.zeros((MATRIX_DIM, MATRIX_DIM), dtype=np.float32)
    
    try:
        with open(fileName, "r") as f:
            lines_hex_ram_words = [line.strip() for line in f.readlines() if line.strip()]
    except FileNotFoundError:
        print(f"Error: {fileName} not found.")
        return None

    expected_ram_words_for_c = (MATRIX_DIM * MATRIX_DIM) // WORDS_PER_BF16_ELEMENTS
    if len(lines_hex_ram_words) != expected_ram_words_for_c:
        print(f"Warning: {fileName} has {len(lines_hex_ram_words)} lines (RAM words), but {expected_ram_words_for_c} were expected for C matrix.")
        # return None # Allow partial processing for debugging

    # This will store all BF16 values in the exact order they appear in the flattened C matrix (row-major)
    all_bf16_elements_flat_uint16 = [] 
    
    # Debug: Print mapping for specific C matrix elements to RAM words and their content
    # C[0][16] (Global addressing)
    # Tile containing C[0][16] is C_tile[0][1] (rc_tile=0, cc_tile=1)
    # Within this tile, it's element (row=0, col=0) because 16 = 1*TILE_DIM + 0
    # RAM address calculation: base_c + (rc_tile * TILES_PER_ROW_COL_HW + cc_tile) * WORDS_PER_RESULT_TILE_IN_CSV 
    #                          + (row_in_tile * WORDS_PER_TILE_ROW_IN_CSV) 
    #                          + (col_in_tile // WORDS_PER_BF16_ELEMENTS)
    # Element within that RAM word: col_in_tile % WORDS_PER_BF16_ELEMENTS

    # Let's calculate the flat index in lines_hex_ram_words for C[0][16] and C[1][0]
    # C[0][16]: global_row=0, global_col=16
    # This is the (0 * MATRIX_DIM + 16)-th element in a fully flattened C matrix.
    flat_idx_c0_16 = 0 * MATRIX_DIM + 16
    csv_line_idx_c0_16 = flat_idx_c0_16 // WORDS_PER_BF16_ELEMENTS
    element_pos_in_word_c0_16 = flat_idx_c0_16 % WORDS_PER_BF16_ELEMENTS

    # C[1][0]: global_row=1, global_col=0
    flat_idx_c1_0 = 1 * MATRIX_DIM + 0
    csv_line_idx_c1_0 = flat_idx_c1_0 // WORDS_PER_BF16_ELEMENTS
    element_pos_in_word_c1_0 = flat_idx_c1_0 % WORDS_PER_BF16_ELEMENTS

    print(f"\n--- CSV Parsing Debug ---")
    print(f"Targeting C[0][16]: Expected flat_idx={flat_idx_c0_16}, CSV line_idx={csv_line_idx_c0_16}, element_pos_in_word={element_pos_in_word_c0_16}")
    print(f"Targeting C[1][0]: Expected flat_idx={flat_idx_c1_0}, CSV line_idx={csv_line_idx_c1_0}, element_pos_in_word={element_pos_in_word_c1_0}")


    for line_idx, line_hex_64bit in enumerate(lines_hex_ram_words):
        try:
            val_64bit_int = int(line_hex_64bit, 16)
        except ValueError:
            print(f"Warning: Could not parse hex line '{line_hex_64bit}' in {fileName} at line index {line_idx}. Skipping line.")
            continue
        
        # Extract elements in the order: E0, E1, E2, E3 where E0 is LSB-aligned
        elements_in_this_word_uint16 = [
            np.uint16((val_64bit_int >>  0) & 0xFFFF), # Element 0 (e.g., C[r][c_base+0])
            np.uint16((val_64bit_int >> 16) & 0xFFFF), # Element 1 (e.g., C[r][c_base+1])
            np.uint16((val_64bit_int >> 32) & 0xFFFF), # Element 2 (e.g., C[r][c_base+2])
            np.uint16((val_64bit_int >> 48) & 0xFFFF)  # Element 3 (e.g., C[r][c_base+3])
        ]
        all_bf16_elements_flat_uint16.extend(elements_in_this_word_uint16)

        # Debug print for the specific lines we are interested in
        if line_idx == csv_line_idx_c0_16:
            extracted_bf16_for_c0_16 = elements_in_this_word_uint16[element_pos_in_word_c0_16]
            converted_float_c0_16 = bfloat16_uint16_to_float32_array([extracted_bf16_for_c0_16])[0]
            print(f"  CSV line {line_idx} (for C[0][16]): Raw='{line_hex_64bit}', Extracted E{element_pos_in_word_c0_16}=0x{extracted_bf16_for_c0_16:04x} -> {converted_float_c0_16:.4f}")
        
        if line_idx == csv_line_idx_c1_0:
            extracted_bf16_for_c1_0 = elements_in_this_word_uint16[element_pos_in_word_c1_0]
            converted_float_c1_0 = bfloat16_uint16_to_float32_array([extracted_bf16_for_c1_0])[0]
            print(f"  CSV line {line_idx} (for C[1][0]): Raw='{line_hex_64bit}', Extracted E{element_pos_in_word_c1_0}=0x{extracted_bf16_for_c1_0:04x} -> {converted_float_c1_0:.4f}")


    expected_total_elements = MATRIX_DIM * MATRIX_DIM
    if len(all_bf16_elements_flat_uint16) != expected_total_elements:
        print(f"Error: Parsed {len(all_bf16_elements_flat_uint16)} BF16 values, but expected {expected_total_elements}.")
        # Potentially fill remaining with zeros or handle error
        if len(all_bf16_elements_flat_uint16) < expected_total_elements:
            all_bf16_elements_flat_uint16.extend([np.uint16(0)] * (expected_total_elements - len(all_bf16_elements_flat_uint16)))
        else: # Too many elements, truncate
            all_bf16_elements_flat_uint16 = all_bf16_elements_flat_uint16[:expected_total_elements]
        # return None
        
    hw_result_flat_f32 = bfloat16_uint16_to_float32_array(np.array(all_bf16_elements_flat_uint16, dtype=np.uint16))
    
    try:
        hw_result_matrix_f32_from_csv = hw_result_flat_f32.reshape((MATRIX_DIM, MATRIX_DIM))
    except ValueError as e:
        print(f"Error reshaping parsed data: {e}")
        return None
    
    print(f"--- End CSV Parsing Debug ---")
    return hw_result_matrix_f32_from_csv

# --- 主程序 ---
def main():
    # ... (加载 A, B 和计算 golden_result_f32 的部分不变) ...
    try:
        matrix_a_orig_sint8 = np.load("matrix_a.npy")
        matrix_b_orig_sint8 = np.load("matrix_b.npy")
    except FileNotFoundError:
        print("Error: matrix_a.npy or matrix_b.npy not found. Run data generation script first.")
        return

    matrix_a_float = matrix_a_orig_sint8.astype(np.float32) 
    matrix_b_float = matrix_b_orig_sint8.astype(np.float32)

    print("Calculating golden result C = A_orig * B_orig (using float32 precision)...")
    golden_result_f32 = np.dot(matrix_a_float, matrix_b_float)
    
    DISPLAY_SUB_DIM = MATRIX_DIM
    original_print_options = np.get_printoptions() 
    np.set_printoptions(threshold=DISPLAY_SUB_DIM*DISPLAY_SUB_DIM + 1, linewidth=DISPLAY_SUB_DIM * 10, suppress=True, formatter={'float': '{:8.2f}'.format, 'int': '{:4d}'.format})

    print(f"\nMatrix A (original SINT8, showing top-left {DISPLAY_SUB_DIM}x{DISPLAY_SUB_DIM} of {MATRIX_DIM}x{MATRIX_DIM}):")
    print(matrix_a_orig_sint8[:DISPLAY_SUB_DIM, :DISPLAY_SUB_DIM])

    print(f"\nMatrix B (original SINT8, showing top-left {DISPLAY_SUB_DIM}x{DISPLAY_SUB_DIM} of {MATRIX_DIM}x{MATRIX_DIM}):")
    print(matrix_b_orig_sint8[:DISPLAY_SUB_DIM, :DISPLAY_SUB_DIM])

    print(f"\nGolden Result C (calculated as float32, showing top-left {DISPLAY_SUB_DIM}x{DISPLAY_SUB_DIM} of {MATRIX_DIM}x{MATRIX_DIM}):")
    print(golden_result_f32[:DISPLAY_SUB_DIM, :DISPLAY_SUB_DIM]) 
    print("-" * 40)

    print("Reading hardware accelerator's result from result_mem.csv...")
    hw_result_f32 = read_hw_result_from_csv_direct(fileName="result_mem.csv")
    
    if hw_result_f32 is None:
        print("Could not parse hardware results. Aborting comparison.")
        return
        
    print(f"\nHW Accelerator Result C (from CSV, converted to float32, showing top-left {DISPLAY_SUB_DIM}x{DISPLAY_SUB_DIM} of {MATRIX_DIM}x{MATRIX_DIM}):")
    print(hw_result_f32[:DISPLAY_SUB_DIM, :DISPLAY_SUB_DIM]) 

    # --- Python Debug Print (after reshape) ---
    print("\n--- Python Direct Access Debug ---")
    print(f"Python: hw_result_f32[0, 16] directly after reshape = {hw_result_f32[0, 16]:.4f}")
    print(f"Python: hw_result_f32[1, 0] directly after reshape = {hw_result_f32[1, 0]:.4f}")
    print(f"Python: hw_result_f32[0, 0] directly after reshape = {hw_result_f32[0, 0]:.4f}")
    print(f"Python: hw_result_f32[2, 0] directly after reshape = {hw_result_f32[2, 0]:.4f}")
    print("--- End Python Direct Access Debug ---")


    if golden_result_f32.shape != hw_result_f32.shape:
        print(f"\nShape mismatch! Golden: {golden_result_f32.shape}, HW output: {hw_result_f32.shape}")
        return

    absolute_tolerance = 1e-5 
    relative_tolerance = 1e-4 
    
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
        for i in range(min(10, len(mismatch_indices[0]))): 
            r, c = mismatch_indices[0][i], mismatch_indices[1][i]
            print(f"    C[{r}][{c}]: Golden={golden_result_f32[r,c]:.4f}, HW={hw_result_f32[r,c]:.4f}, Diff={diff[r,c]:.4g}")

    np.set_printoptions(**original_print_options) # 恢复原始打印选项

if __name__ == "__main__":
    main()