import numpy as np
import os
import math # For exp
import random # 导入 random 模块

# --- Testbench Parameters (matching testbench_top.v) ---
MATRIX_DIM_TB = 48
TILE_DIM_TB = 16
RAM_DATA_WIDTH_TB = 64
SINT8_BITS_TB = 8

DATA_TYPE_IN = np.int8 # SINT8 corresponds to np.int8

if MATRIX_DIM_TB % TILE_DIM_TB != 0:
    raise ValueError("MATRIX_DIM_TB must be divisible by TILE_DIM_TB.")

TILES_PER_ROW_COL_TB = MATRIX_DIM_TB // TILE_DIM_TB
SINT8_PER_MEM_WORD_TB = RAM_DATA_WIDTH_TB // SINT8_BITS_TB

# --- Helper Functions ---

def number_to_sint8_hex(number):
    """Converts a number to its signed 8-bit integer hexadecimal representation."""
    py_int_number = int(number)
    # The numpy array creation with DATA_TYPE_IN (np.int8) already handles wrapping,
    # so these explicit clamps might not be strictly necessary for values coming from the array,
    # but they ensure correctness for any input.
    if py_int_number > 127: py_int_number = 127
    elif py_int_number < -128: py_int_number = -128
    if py_int_number < 0:
        py_int_number = (1 << 8) + py_int_number
    return f'{py_int_number:02x}'

def convert_tile_to_hex_lines_row_major(tile_matrix):
    """
    Flattens a tile matrix in row-major order and converts it to hexadecimal lines.
    Used for Matrix A.
    """
    hex_lines = []
    # .flatten() defaults to 'C' order (row-major)
    flat_tile = tile_matrix.flatten()
    for i in range(0, len(flat_tile), SINT8_PER_MEM_WORD_TB):
        chunk = flat_tile[i : i + SINT8_PER_MEM_WORD_TB]
        # Reverse the chunk for little-endian byte ordering in hex word
        hex_word = "".join([number_to_sint8_hex(n) for n in reversed(chunk)])
        hex_lines.append(hex_word)
    return hex_lines

def convert_tile_to_hex_lines_col_major(tile_matrix):
    """
    Flattens a tile matrix in column-major order and converts it to hexadecimal lines.
    Used for Matrix B.
    """
    hex_lines = []
    # .flatten('F') uses 'F' (Fortran) order (column-major)
    flat_tile = tile_matrix.flatten('F')
    for i in range(0, len(flat_tile), SINT8_PER_MEM_WORD_TB):
        chunk = flat_tile[i : i + SINT8_PER_MEM_WORD_TB]
        # Reverse the chunk for little-endian byte ordering in hex word
        hex_word = "".join([number_to_sint8_hex(n) for n in reversed(chunk)])
        hex_lines.append(hex_word)
    return hex_lines


# --- Main Program ---
def main():
    print(f"Generating {MATRIX_DIM_TB}x{MATRIX_DIM_TB} SINT8 matrices for testbench.")

    # --- 1. Generate Matrix A (Random SINT8 values) ---
    # 生成范围在 -128 到 127 之间的随机整数
    matrix_a_orig = np.random.randint(-128, 128, size=(MATRIX_DIM_TB, MATRIX_DIM_TB), dtype=DATA_TYPE_IN)

    # --- 2. Generate Matrix B (Random SINT8 values) ---
    # 生成范围在 -128 到 127 之间的随机整数
    matrix_b_orig = np.random.randint(-128, 128, size=(MATRIX_DIM_TB, MATRIX_DIM_TB), dtype=DATA_TYPE_IN)
    # matrix_b_orig = np.random.randint(0, 2, size=(MATRIX_DIM_TB, MATRIX_DIM_TB), dtype=DATA_TYPE_IN)
    # matrix_b_orig[2][10] = 1
    # matrix_b_orig[0][16] = 1
    # matrix_b_orig[32][0] = 1


    # --- 3. Convert Matrices to SRAM memory file format ---
    # As per your request:
    # - Matrix A Tiles are stored in Row-Major order
    # - Matrix B Tiles are stored in Column-Major order

    print("\nProcessing Matrix A tiles (Row-Major)...")
    all_hex_lines_a = []
    # Since MATRIX_DIM_TB == TILE_DIM_TB, TILES_PER_ROW_COL_TB = 1
    # The loop will iterate only once for the entire matrix
    for tile_row_global_idx in range(TILES_PER_ROW_COL_TB):
        for tile_col_global_idx in range(TILES_PER_ROW_COL_TB):
            start_r = tile_row_global_idx * TILE_DIM_TB
            end_r = start_r + TILE_DIM_TB
            start_c = tile_col_global_idx * TILE_DIM_TB
            end_c = start_c + TILE_DIM_TB
            current_tile_a = matrix_a_orig[start_r:end_r, start_c:end_c]
            # Calling the row-major conversion function
            all_hex_lines_a.extend(convert_tile_to_hex_lines_row_major(current_tile_a))

    print("Processing Matrix B tiles (Column-Major)...")
    all_hex_lines_b = []
    for tile_row_global_idx in range(TILES_PER_ROW_COL_TB):
        for tile_col_global_idx in range(TILES_PER_ROW_COL_TB):
            start_r = tile_row_global_idx * TILE_DIM_TB
            end_r = start_r + TILE_DIM_TB
            start_c = tile_col_global_idx * TILE_DIM_TB
            end_c = start_c + TILE_DIM_TB
            current_tile_b = matrix_b_orig[start_r:end_r, start_c:end_c]
            # Calling the column-major conversion function
            all_hex_lines_b.extend(convert_tile_to_hex_lines_col_major(current_tile_b))

    output_file = "input_mem.csv"
    with open(output_file, "w") as f:
        print(f"\nWriting A matrix tiles to {output_file}...")
        for line in all_hex_lines_a:
            f.write(f"{line}\n")

        print(f"\nWriting B matrix tiles to {output_file}...")
        for line in all_hex_lines_b:
            f.write(f"{line}\n")

    print("\nSaving original matrices and expected result to .npy files...")
    np.save('matrix_a.npy', matrix_a_orig) # Save SINT8
    np.save('matrix_b.npy', matrix_b_orig) # Save SINT8

    # --- Calculate Expected C Matrix (Exact SINT32) ---
    # Note: This calculation uses the original matrices and is not affected by storage order.
    matrix_a_calc = matrix_a_orig.astype(np.int64) # Use int64 to prevent overflow during intermediate accumulation
    matrix_b_calc = matrix_b_orig.astype(np.int64)
    expected_c_exact_int64 = np.dot(matrix_a_calc, matrix_b_calc)
     
    if np.any(expected_c_exact_int64 > 2**31 - 1) or np.any(expected_c_exact_int64 < -(2**31)):
        print("Warning: Expected C matrix elements exceed SINT32 range during calculation!")
    expected_c_sint32 = expected_c_exact_int64.astype(np.int32) # Hardware accumulator is SINT32
    np.save('matrix_c_expected_sint32.npy', expected_c_sint32)

    print("\nScript finished successfully.")

if __name__ == "__main__":
    main()
