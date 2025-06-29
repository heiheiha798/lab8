import numpy as np
import os
import math # 仍然可以保留，以防未来需要其他数学运算

# --- Testbench/Hardware 参数 ---
MATRIX_DIM_TB = 48
PE_ACCUM_BITS_TB = 32
RAM_DATA_WIDTH_TB = 64

SINT32_PER_RAM_WORD_TB = RAM_DATA_WIDTH_TB // PE_ACCUM_BITS_TB
if RAM_DATA_WIDTH_TB % PE_ACCUM_BITS_TB != 0:
    raise ValueError("RAM_DATA_WIDTH_TB must be a multiple of PE_ACCUM_BITS_TB.")

def read_hw_result_sint32_direct(fileName="result_mem.csv", matrix_dim_arg=MATRIX_DIM_TB):
    all_sint32_elements_flat = []
    try:
        with open(fileName, "r") as f:
            lines_hex_ram_words = [line.strip() for line in f.readlines() if line.strip()]
    except FileNotFoundError:
        print(f"Error: {fileName} not found.")
        return None

    # For 16x16 SINT32 result: 16*16 = 256 elements.
    # Each 64-bit word stores 2 SINT32 elements. So, 256/2 = 128 RAM words.
    expected_ram_words_for_c = (matrix_dim_arg * matrix_dim_arg) // SINT32_PER_RAM_WORD_TB
    if (matrix_dim_arg * matrix_dim_arg) % SINT32_PER_RAM_WORD_TB != 0: # Should not happen if dim is reasonable
        expected_ram_words_for_c +=1

    if len(lines_hex_ram_words) != expected_ram_words_for_c:
        print(f"Warning: {fileName} has {len(lines_hex_ram_words)} lines (RAM words), "
              f"but {expected_ram_words_for_c} were expected for {matrix_dim_arg}x{matrix_dim_arg} SINT32 C matrix.")

    for line_idx, line_hex_ram_word in enumerate(lines_hex_ram_words):
        try:
            val_ram_word_int = int(line_hex_ram_word, 16)
        except ValueError:
            print(f"Warning: Could not parse hex line '{line_hex_ram_word}' at line index {line_idx}. Skipping line, filling with zeros.")
            all_sint32_elements_flat.extend([np.int32(0)] * SINT32_PER_RAM_WORD_TB)
            continue

        elements_in_this_word = []
        for i in range(SINT32_PER_RAM_WORD_TB):
            # Extract i-th SINT32 from the RAM word
            # Assumes element 0 is in lower bits, element 1 in higher bits for a 2-element word
            element_uint32 = (val_ram_word_int >> (i * PE_ACCUM_BITS_TB)) & ((1 << PE_ACCUM_BITS_TB) - 1)
            # Convert to signed SINT32
            if element_uint32 >= (1 << (PE_ACCUM_BITS_TB - 1)):
                element_sint32 = element_uint32 - (1 << PE_ACCUM_BITS_TB)
            else:
                element_sint32 = element_uint32
            elements_in_this_word.append(np.int32(element_sint32))
        all_sint32_elements_flat.extend(elements_in_this_word)

    expected_total_elements = matrix_dim_arg * matrix_dim_arg
    # Pad with zeros if not enough elements were parsed due to warnings
    if len(all_sint32_elements_flat) < expected_total_elements:
        print(f"Padding parsed SINT32 elements from {len(all_sint32_elements_flat)} to {expected_total_elements} with zeros.")
        all_sint32_elements_flat.extend([np.int32(0)] * (expected_total_elements - len(all_sint32_elements_flat)))
    elif len(all_sint32_elements_flat) > expected_total_elements:
        print(f"Trimming parsed SINT32 elements from {len(all_sint32_elements_flat)} to {expected_total_elements}.")
        all_sint32_elements_flat = all_sint32_elements_flat[:expected_total_elements]


    hw_result_flat_sint32 = np.array(all_sint32_elements_flat, dtype=np.int32)
    try:
        hw_result_matrix_sint32 = hw_result_flat_sint32.reshape((matrix_dim_arg, matrix_dim_arg))
    except ValueError as e:
        print(f"Error reshaping parsed SINT32 data ({len(hw_result_flat_sint32)} elements) to {matrix_dim_arg}x{matrix_dim_arg}: {e}.")
        return None
    return hw_result_matrix_sint32

# --- 主程序 ---
def main():
    hw_result_file = "result_mem.csv"

    try:
        matrix_a_sint8 = np.load("matrix_a.npy")
        matrix_b_sint8 = np.load("matrix_b.npy")
        golden_c_sint32 = np.load("matrix_c_expected_sint32.npy")
    except FileNotFoundError:
        print("Error: matrix_a.npy, matrix_b.npy, or matrix_c_expected_sint32.npy not found. Run data generation script first.")
        return

    DISPLAY_SUB_DIM = MATRIX_DIM_TB
    original_print_options = np.get_printoptions()
    np.set_printoptions(threshold=max(1024, DISPLAY_SUB_DIM*DISPLAY_SUB_DIM + 1),
                        linewidth=max(400, DISPLAY_SUB_DIM * 10), # Wider for SINT32
                        suppress=True,
                        formatter={'int_kind': '{:9d}'.format}) # Format for SINT32

    print(f"\nMatrix A (SINT8 loaded from .npy):")
    print(matrix_a_sint8[:DISPLAY_SUB_DIM, :DISPLAY_SUB_DIM])
    print(f"\nMatrix B (SINT8 loaded from .npy):")
    print(matrix_b_sint8[:DISPLAY_SUB_DIM, :DISPLAY_SUB_DIM])
    print(f"\nGolden Result C (SINT32 loaded from .npy):")
    print(golden_c_sint32[:DISPLAY_SUB_DIM, :DISPLAY_SUB_DIM])
    print("-" * 40)

    hw_result_sint32 = read_hw_result_sint32_direct(fileName=hw_result_file, matrix_dim_arg=MATRIX_DIM_TB)

    if hw_result_sint32 is None:
        print("Could not parse hardware results. Aborting comparison.")
        np.set_printoptions(**original_print_options)
        return

    print(f"\nHW Accelerator Result C (SINT32 parsed from '{hw_result_file}'):")
    print(hw_result_sint32[:DISPLAY_SUB_DIM, :DISPLAY_SUB_DIM])

    if golden_c_sint32.shape != hw_result_sint32.shape:
        print(f"\nShape mismatch! Golden SINT32: {golden_c_sint32.shape}, HW SINT32 output: {hw_result_sint32.shape}")
        np.set_printoptions(**original_print_options)
        return

    diff_sq = (hw_result_sint32.astype(np.float64) - golden_c_sint32.astype(np.float64))**2
    sse_hw_vs_golden_sint32 = np.sum(diff_sq)
    
    print(f"\n>> Accuracy Metrics (vs SINT32 Golden):")
    print(f">> SSE (HW SINT32 vs Golden SINT32): {sse_hw_vs_golden_sint32:.6e}")
    print("-" * 20)

    num_mismatches = np.sum(golden_c_sint32 != hw_result_sint32)
    total_elements = golden_c_sint32.size

    print(f"\n>> Comparison Summary (HW SINT32 vs Golden SINT32):")
    if num_mismatches == 0:
        print(">> PASSED: Hardware SINT32 result exactly matches the golden SINT32 result.")
    else:
        print(f">> FAILED: Found {num_mismatches} mismatched SINT32 elements out of {total_elements}.")
        mismatch_indices = np.where(golden_c_sint32 != hw_result_sint32)
        if len(mismatch_indices[0]) > 0:
            first_mismatch_row = mismatch_indices[0][0]
            first_mismatch_col = mismatch_indices[1][0]
            print(f"   First SINT32 mismatch at C[{first_mismatch_row}][{first_mismatch_col}]: "
                  f"Golden = {golden_c_sint32[first_mismatch_row, first_mismatch_col]}, "
                  f"HW = {hw_result_sint32[first_mismatch_row, first_mismatch_col]}")
    print("-" * 20)
    np.set_printoptions(**original_print_options)

if __name__ == "__main__":
    main()