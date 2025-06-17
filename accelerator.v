// accelerator.v
`timescale 1ns / 1ps

module accelerator #(
    parameter MATRIX_DIM_GLOBAL = 32,
    parameter TILE_DIM_SYSTOLIC = 16,
    parameter RAM_DATA_WIDTH    = 64, // Width for Main Memory and Tile SRAMs
    parameter SINT8_BITS        = 8,
    parameter PE_ACCUM_BITS     = 32,
    parameter LOGIC_ADDR_WIDTH  = 18,   // For Main Memory addressing

    // Calculate words needed in Tile SRAM (assuming SINT8 elements)
    localparam TILE_SRAM_TOTAL_BITS  = (TILE_DIM_SYSTOLIC * TILE_DIM_SYSTOLIC * SINT8_BITS),
    localparam TILE_SRAM_WORDS_CALC  = (TILE_SRAM_TOTAL_BITS == 0 || RAM_DATA_WIDTH == 0) ? 1 : (TILE_SRAM_TOTAL_BITS + RAM_DATA_WIDTH - 1) / RAM_DATA_WIDTH, // Ceiling division
    localparam TILE_SRAM_WORDS       = (TILE_SRAM_WORDS_CALC == 0 && TILE_SRAM_TOTAL_BITS > 0) ? 1 : TILE_SRAM_WORDS_CALC,
    parameter TILE_SRAM_ADDR_WIDTH  = (TILE_SRAM_WORDS <= 1) ? 1 : $clog2(TILE_SRAM_WORDS),

    parameter MM_READ_LATENCY_CYCLES = 2 // Expected read latency from main memory controller (for FSM design)
) (
    input wire clk,
    input wire rst_n,

    input wire start_computation,
    output reg computation_done,

    // --- Main Memory Interface Ports ---
    output reg [LOGIC_ADDR_WIDTH-1:0] mm_addr_o,
    output reg [RAM_DATA_WIDTH-1:0]   mm_wdata_o,
    output reg                        mm_cs_o,
    output reg                        mm_we_o,
    input wire  [RAM_DATA_WIDTH-1:0]   mm_rdata_i,
    input wire                         mm_ready_i,

    input wire [LOGIC_ADDR_WIDTH-1:0] base_addr_a_mm,
    input wire [LOGIC_ADDR_WIDTH-1:0] base_addr_b_mm,
    input wire [LOGIC_ADDR_WIDTH-1:0] base_addr_c_mm,

    // --- Tile A SRAM Interface Ports ---
    output reg                               tile_a_sram_cs_o,
    output reg                               tile_a_sram_we_o,
    output reg [TILE_SRAM_ADDR_WIDTH-1:0]    tile_a_sram_addr_o,
    output reg [RAM_DATA_WIDTH-1:0]          tile_a_sram_wdata_o,
    input wire  [RAM_DATA_WIDTH-1:0]          tile_a_sram_rdata_i,

    // --- Tile B SRAM Interface Ports ---
    output reg                               tile_b_sram_cs_o,
    output reg                               tile_b_sram_we_o,
    output reg [TILE_SRAM_ADDR_WIDTH-1:0]    tile_b_sram_addr_o,
    output reg [RAM_DATA_WIDTH-1:0]          tile_b_sram_wdata_o,
    input wire  [RAM_DATA_WIDTH-1:0]          tile_b_sram_rdata_i
);

    // --- Derived Parameters ---
    localparam SINT8_PER_RAM_WORD = (SINT8_BITS == 0) ? 1 : RAM_DATA_WIDTH / SINT8_BITS; // Avoid div by zero if SINT8_BITS is 0
    localparam SINT32_PER_RAM_WORD = (PE_ACCUM_BITS == 0) ? 1 : RAM_DATA_WIDTH / PE_ACCUM_BITS;
    localparam TILES_PER_ROW_COL_GLOBAL = (TILE_DIM_SYSTOLIC == 0) ? 1 : MATRIX_DIM_GLOBAL / TILE_DIM_SYSTOLIC;
    localparam SAFE_TILES_PER_ROW_COL_GLOBAL = (TILES_PER_ROW_COL_GLOBAL == 0) ? 1 : TILES_PER_ROW_COL_GLOBAL;

    localparam WORDS_PER_SINT8_MM_TILE_CALC = (TILE_DIM_SYSTOLIC*TILE_DIM_SYSTOLIC*SINT8_BITS)/RAM_DATA_WIDTH;
    localparam WORDS_PER_SINT8_MM_TILE = (WORDS_PER_SINT8_MM_TILE_CALC == 0 && (TILE_DIM_SYSTOLIC*TILE_DIM_SYSTOLIC*SINT8_BITS) > 0) ? 1 : WORDS_PER_SINT8_MM_TILE_CALC;

    localparam WORDS_PER_SINT32_MM_TILE_CALC  = (TILE_DIM_SYSTOLIC*TILE_DIM_SYSTOLIC*PE_ACCUM_BITS)/RAM_DATA_WIDTH;
    localparam WORDS_PER_SINT32_MM_TILE = (WORDS_PER_SINT32_MM_TILE_CALC == 0 && (TILE_DIM_SYSTOLIC*TILE_DIM_SYSTOLIC*PE_ACCUM_BITS) > 0) ? 1 : WORDS_PER_SINT32_MM_TILE_CALC;

    localparam MM_TILE_WORD_COUNT_WIDTH = (WORDS_PER_SINT8_MM_TILE > WORDS_PER_SINT32_MM_TILE) ?
                                          ((WORDS_PER_SINT8_MM_TILE <=1)? 1 : $clog2(WORDS_PER_SINT8_MM_TILE)) :
                                          ((WORDS_PER_SINT32_MM_TILE <=1)? 1 : $clog2(WORDS_PER_SINT32_MM_TILE));


    localparam TILE_AREA = TILE_DIM_SYSTOLIC * TILE_DIM_SYSTOLIC;
    localparam LOOP_COUNTER_WIDTH = (SAFE_TILES_PER_ROW_COL_GLOBAL <= 1) ? 1 : $clog2(SAFE_TILES_PER_ROW_COL_GLOBAL);
    localparam _SINT32_PER_RAM_WORD_SAFE = (SINT32_PER_RAM_WORD == 0) ? 1 : SINT32_PER_RAM_WORD;
    localparam NUM_PACKED_WORDS_PER_SA_ROW_C_CALC = (TILE_DIM_SYSTOLIC == 0) ? 0 : (SINT32_PER_RAM_WORD == 0 && TILE_DIM_SYSTOLIC > 0) ? TILE_DIM_SYSTOLIC : (TILE_DIM_SYSTOLIC + _SINT32_PER_RAM_WORD_SAFE - 1) / _SINT32_PER_RAM_WORD_SAFE;
    localparam NUM_PACKED_WORDS_PER_SA_ROW_C = (NUM_PACKED_WORDS_PER_SA_ROW_C_CALC == 0 && TILE_DIM_SYSTOLIC > 0) ? 1 : NUM_PACKED_WORDS_PER_SA_ROW_C_CALC;
    localparam _NUM_PACKED_WORDS_PER_SA_ROW_C_SAFE = (NUM_PACKED_WORDS_PER_SA_ROW_C == 0) ? 1 : NUM_PACKED_WORDS_PER_SA_ROW_C;
    localparam C_STORE_WORD_IN_ROW_IDX_WIDTH = (_NUM_PACKED_WORDS_PER_SA_ROW_C_SAFE <= 1) ? 1 : $clog2(_NUM_PACKED_WORDS_PER_SA_ROW_C_SAFE);
    localparam _TILE_DIM_SYSTOLIC_PLUS_1 = TILE_DIM_SYSTOLIC + 1;
    localparam SA_FEED_CYCLE_IDX_WIDTH = (_TILE_DIM_SYSTOLIC_PLUS_1 <= 1) ? 1 : $clog2(_TILE_DIM_SYSTOLIC_PLUS_1);
    localparam C_STORE_ROW_IDX_WIDTH = (_TILE_DIM_SYSTOLIC_PLUS_1 <= 1) ? 1 : $clog2(_TILE_DIM_SYSTOLIC_PLUS_1);
    localparam _SAFE_TILE_DIM_FOR_SELECT = (TILE_DIM_SYSTOLIC == 0) ? 1 : TILE_DIM_SYSTOLIC;
    localparam SA_SELECT_ROW_WIDTH = (_SAFE_TILE_DIM_FOR_SELECT <= 1) ? 1 : $clog2(_SAFE_TILE_DIM_FOR_SELECT);
    localparam SA_INPUT_BUS_WIDTH = TILE_DIM_SYSTOLIC * SINT8_BITS;
    localparam SAFE_SA_INPUT_BUS_WIDTH = (SA_INPUT_BUS_WIDTH == 0) ? 1 : SA_INPUT_BUS_WIDTH;
    localparam SA_OUTPUT_BUS_WIDTH = TILE_DIM_SYSTOLIC * PE_ACCUM_BITS;
    localparam SAFE_SA_OUTPUT_BUS_WIDTH = (SA_OUTPUT_BUS_WIDTH == 0) ? 1 : SA_OUTPUT_BUS_WIDTH;

    // --- FSM States ---
    localparam S_IDLE = 0;
    localparam S_INIT_CTL_LOOP = 1;
    localparam S_INIT_K_LOOP_PE_SETUP = 2;
    localparam S_LOAD_A_MM_ADDR_SETUP = 3;
    localparam S_LOAD_A_MM_REQ = 4;
    localparam S_LOAD_A_MM_WAIT_READY = 5;
    localparam S_LOAD_A_TILE_SRAM_WRITE = 6;
    localparam S_LOAD_B_MM_ADDR_SETUP = 7;
    localparam S_LOAD_B_MM_REQ = 8;
    localparam S_LOAD_B_MM_WAIT_READY = 9;
    localparam S_LOAD_B_TILE_SRAM_WRITE = 10;
    localparam S_SA_FEED_SETUP = 11;
    localparam S_SA_FEED_CYCLE_EXEC = 12;
    localparam S_SA_WAIT_DONE = 13;
    localparam S_K_LOOP_INCREMENT = 14;
    localparam S_STORE_C_MM_ADDR_SETUP = 15;
    localparam S_STORE_C_TILE_SA_READ_SETUP = 16;
    localparam S_STORE_C_MM_WRITE_REQ = 17;
    localparam S_CTL_LOOP_INCREMENT = 18;
    localparam S_FINISH = 19;
    localparam S_STORE_C_TILE_SA_READ_WAIT_VALID = 20;
    localparam S_STORE_C_MM_WRITE_WAIT_READY = 21;
    // States for Tile SRAM 2-cycle visible read
    localparam S_SA_FEED_CYCLE_A_READ_REQ = 22;
    localparam S_SA_FEED_CYCLE_A_READ_WAIT1 = 23; // First wait cycle
    localparam S_SA_FEED_CYCLE_A_LATCH_AND_PROCESS = 24; // Second wait, latch, and setup unpack
    localparam S_SA_FEED_CYCLE_B_READ_REQ = 25;
    localparam S_SA_FEED_CYCLE_B_READ_WAIT1 = 26; // First wait cycle
    localparam S_SA_FEED_CYCLE_B_LATCH_AND_PROCESS = 27; // Second wait, latch, and setup unpack
    localparam S_SA_PRE_EXEC_CHECK = 28;
    localparam B_WORDS_PER_ROW = (TILE_DIM_SYSTOLIC + SINT8_PER_RAM_WORD - 1) / SINT8_PER_RAM_WORD;

    reg [5:0] current_state_reg, next_state_reg;

    // Loop counters and FSM-driven address registers
    reg [LOOP_COUNTER_WIDTH-1:0] r_c_idx_reg, r_c_idx_next;
    reg [LOOP_COUNTER_WIDTH-1:0] c_c_idx_reg, c_c_idx_next;
    reg [LOOP_COUNTER_WIDTH-1:0] k_idx_reg, k_idx_next;

    reg [LOGIC_ADDR_WIDTH-1:0] current_mm_addr_r, current_mm_addr_next;
    // Removed current_tile_a/b_sram_addr_r as addr_o will be directly driven by _next_comb
    // reg [TILE_SRAM_ADDR_WIDTH-1:0] current_tile_a_sram_addr_r, current_tile_a_sram_addr_next;
    // reg [TILE_SRAM_ADDR_WIDTH-1:0] current_tile_b_sram_addr_r, current_tile_b_sram_addr_next;

    reg [MM_TILE_WORD_COUNT_WIDTH-1:0] mm_word_count_reg, mm_word_count_next;
    reg [RAM_DATA_WIDTH-1:0] latched_mm_rdata_r;

    reg signed [SINT8_BITS-1:0] temp_a_col_for_sa [0:TILE_DIM_SYSTOLIC-1];
    reg signed [SINT8_BITS-1:0] temp_b_row_for_sa [0:TILE_DIM_SYSTOLIC-1];
    integer i;

    reg [SA_FEED_CYCLE_IDX_WIDTH-1:0]   sa_feed_total_cycles_count_reg, sa_feed_total_cycles_count_next; // Counts SA execution passes
    reg [C_STORE_ROW_IDX_WIDTH-1:0]     c_store_row_read_idx_reg, c_store_row_read_idx_next;
    reg [C_STORE_WORD_IN_ROW_IDX_WIDTH-1:0] c_store_word_in_row_idx_reg, c_store_word_in_row_idx_next;

    // Combinational signals for FSM to drive ports in the next cycle
    reg mm_cs_o_next_comb;
    reg mm_we_o_next_comb;
    reg [RAM_DATA_WIDTH-1:0] mm_wdata_o_next_comb;
    reg [LOGIC_ADDR_WIDTH-1:0] mm_addr_o_next_comb;

    reg tile_a_sram_cs_o_next_comb;
    reg tile_a_sram_we_o_next_comb;
    reg [TILE_SRAM_ADDR_WIDTH-1:0] tile_a_sram_addr_o_next_comb;
    reg [RAM_DATA_WIDTH-1:0] tile_a_sram_wdata_o_next_comb;

    reg tile_b_sram_cs_o_next_comb;
    reg tile_b_sram_we_o_next_comb;
    reg [TILE_SRAM_ADDR_WIDTH-1:0] tile_b_sram_addr_o_next_comb;
    reg [RAM_DATA_WIDTH-1:0] tile_b_sram_wdata_o_next_comb;

    // SA control pulse/level signals
    reg sa_clear_accum_pulse_reg, sa_clear_accum_pulse_next;
    reg sa_cond_clear_sum_level_reg, sa_cond_clear_sum_level_next;
    reg sa_start_new_pass_pulse_reg, sa_start_new_pass_pulse_next;
    reg sa_activate_comp_reg, sa_activate_comp_next;
    reg sa_enable_output_reg, sa_enable_output_next;
    reg [SA_SELECT_ROW_WIDTH-1:0] sa_select_row_reg, sa_select_row_next;

    reg [RAM_DATA_WIDTH-1:0] packed_c_word_comb;

    wire [SAFE_SA_INPUT_BUS_WIDTH-1:0] current_a_column_for_feed_wire;
    wire [SAFE_SA_INPUT_BUS_WIDTH-1:0] current_b_row_for_feed_wire;

    wire [SAFE_SA_INPUT_BUS_WIDTH-1:0] sa_array_a_in_wire_systolic;
    wire [SAFE_SA_INPUT_BUS_WIDTH-1:0] sa_array_b_in_wire_systolic;
    wire [SAFE_SA_OUTPUT_BUS_WIDTH-1:0] sa_tile_row_result_out_wire;
    wire sa_array_data_valid_in_wire_systolic;
    wire sa_tile_row_result_valid_wire;
    wire sa_tile_all_pes_done_one_pass_wire;

    // Registers for Tile SRAM data and unpack control
    reg [RAM_DATA_WIDTH-1:0] latched_tile_a_sram_rdata_r;
    reg [$clog2(TILE_DIM_SYSTOLIC)-1:0] sa_feed_a_col_element_idx_r, sa_feed_a_col_element_idx_next; // Current element in A column being processed
    reg [$clog2(SINT8_PER_RAM_WORD)-1:0] sint8_offset_in_word_a_for_unpack_r, sint8_offset_in_word_a_for_unpack_next; // Offset for the latched data
    reg [$clog2(TILE_DIM_SYSTOLIC)-1:0] a_element_idx_for_unpack_r, a_element_idx_for_unpack_next; // Element index for the latched data
    reg do_unpack_a_pulse_next, do_unpack_a_pulse_r; // To trigger unpack one cycle after latch

    reg [RAM_DATA_WIDTH-1:0] latched_tile_b_sram_rdata_r;
    reg [$clog2(TILE_SRAM_WORDS_CALC)-1:0] b_sram_word_idx_in_row_r, b_sram_word_idx_in_row_next; // 0 or 1 for 2-word read per B row
    reg [$clog2(TILE_SRAM_WORDS_CALC)-1:0] b_sram_word_idx_for_unpack_r, b_sram_word_idx_for_unpack_next; // Word index for the latched data
    reg do_unpack_b_pulse_next, do_unpack_b_pulse_r;

    reg computation_done_next_comb;
    reg temp_a_col_filled_r, temp_a_col_filled_next;
    reg temp_b_row_filled_r, temp_b_row_filled_next;

    systolic_array #(
        .SIZE(TILE_DIM_SYSTOLIC),
        .INPUT_DATA_WIDTH(SINT8_BITS),
        .PE_ACCUM_DATA_WIDTH(PE_ACCUM_BITS)
    ) u_systolic_array (
        .clk(clk),
        .rst_n(rst_n),
        .clear_all_pe_accumulators(sa_clear_accum_pulse_reg),
        .conditionally_clear_pe_sums_level(sa_cond_clear_sum_level_reg),
        .activate_pe_computation(sa_activate_comp_reg),
        .array_data_valid_in(sa_array_data_valid_in_wire_systolic),
        .array_a_in(sa_array_a_in_wire_systolic),
        .array_b_in(sa_array_b_in_wire_systolic),
        .select_output_row_idx(sa_select_row_reg),
        .enable_tile_row_output(sa_enable_output_reg),
        .start_new_systolic_pass(sa_start_new_pass_pulse_reg),
        .array_a_data_valid_out(), .array_a_out(), .array_b_data_valid_out(), .array_b_out(),
        .tile_row_result_out(sa_tile_row_result_out_wire),
        .tile_row_result_valid(sa_tile_row_result_valid_wire),
        .tile_all_pes_done_one_pass(sa_tile_all_pes_done_one_pass_wire)
    );

    function [16*8-1:0] fsm_state_to_string (input [5:0] state_in);
        case(state_in)
            S_IDLE:                            fsm_state_to_string = "S_IDLE";
            S_INIT_CTL_LOOP:                   fsm_state_to_string = "S_INIT_CTL_LOOP";
            S_INIT_K_LOOP_PE_SETUP:            fsm_state_to_string = "S_INIT_K_SETUP";
            S_LOAD_A_MM_ADDR_SETUP:            fsm_state_to_string = "S_LOAD_A_MM_ADDR";
            S_LOAD_A_MM_REQ:                   fsm_state_to_string = "S_LOAD_A_MM_REQ";
            S_LOAD_A_MM_WAIT_READY:            fsm_state_to_string = "S_LOAD_A_MM_WAIT";
            S_LOAD_A_TILE_SRAM_WRITE:          fsm_state_to_string = "S_LOAD_A_SRAM_WR";
            S_LOAD_B_MM_ADDR_SETUP:            fsm_state_to_string = "S_LOAD_B_MM_ADDR";
            S_LOAD_B_MM_REQ:                   fsm_state_to_string = "S_LOAD_B_MM_REQ";
            S_LOAD_B_MM_WAIT_READY:            fsm_state_to_string = "S_LOAD_B_MM_WAIT";
            S_LOAD_B_TILE_SRAM_WRITE:          fsm_state_to_string = "S_LOAD_B_SRAM_WR";
            S_SA_FEED_SETUP:                   fsm_state_to_string = "S_SA_FEED_SETUP";
            S_SA_FEED_CYCLE_A_READ_REQ:        fsm_state_to_string = "S_SA_A_RD_REQ";
            S_SA_FEED_CYCLE_A_READ_WAIT1:      fsm_state_to_string = "S_SA_A_RD_WAIT1";
            S_SA_FEED_CYCLE_A_LATCH_AND_PROCESS: fsm_state_to_string = "S_SA_A_LATCH_PROC";
            S_SA_FEED_CYCLE_B_READ_REQ:        fsm_state_to_string = "S_SA_B_RD_REQ";
            S_SA_FEED_CYCLE_B_READ_WAIT1:      fsm_state_to_string = "S_SA_B_RD_WAIT1";
            S_SA_FEED_CYCLE_B_LATCH_AND_PROCESS: fsm_state_to_string = "S_SA_B_LATCH_PROC";
            S_SA_PRE_EXEC_CHECK:               fsm_state_to_string = "S_SA_PRE_EXEC_CHK";
            S_SA_FEED_CYCLE_EXEC:              fsm_state_to_string = "S_SA_FEED_EXEC";
            S_SA_WAIT_DONE:                    fsm_state_to_string = "S_SA_WAIT_DONE";
            S_K_LOOP_INCREMENT:                fsm_state_to_string = "S_K_LOOP_INC";
            S_STORE_C_MM_ADDR_SETUP:           fsm_state_to_string = "S_STORE_C_MM_ADDR";
            S_STORE_C_TILE_SA_READ_SETUP:      fsm_state_to_string = "S_STORE_C_SA_RD_SETUP";
            S_STORE_C_TILE_SA_READ_WAIT_VALID: fsm_state_to_string = "S_STORE_C_SA_RD_WAITV";
            S_STORE_C_MM_WRITE_REQ:            fsm_state_to_string = "S_STORE_C_MM_WR_REQ";
            S_STORE_C_MM_WRITE_WAIT_READY:     fsm_state_to_string = "S_STORE_C_MM_WR_WAIT";
            S_CTL_LOOP_INCREMENT:              fsm_state_to_string = "S_CTL_LOOP_INC";
            S_FINISH:                          fsm_state_to_string = "S_FINISH";
            default:                           fsm_state_to_string = "UNKNOWN_STATE";
        endcase
    endfunction

    integer cycle_count; // For debug display

    // Clocked FSM and Data Path Logic
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state_reg <= S_IDLE;
            r_c_idx_reg <= '0; c_c_idx_reg <= '0; k_idx_reg <= '0;
            current_mm_addr_r <= '0;
            mm_addr_o <= '0;
            // current_tile_a_sram_addr_r <= '0; // Removed
            // current_tile_b_sram_addr_r <= '0; // Removed
            mm_word_count_reg <= '0;
            latched_mm_rdata_r <= '0;

            latched_tile_a_sram_rdata_r <= '0;
            sa_feed_a_col_element_idx_r <= '0;
            sint8_offset_in_word_a_for_unpack_r <= '0;
            a_element_idx_for_unpack_r <= '0;
            do_unpack_a_pulse_r <= 1'b0;

            latched_tile_b_sram_rdata_r <= '0;
            b_sram_word_idx_in_row_r <= 0;
            b_sram_word_idx_for_unpack_r <= 0;
            do_unpack_b_pulse_r <= 1'b0;

            mm_cs_o <= 1'b0; mm_we_o <= 1'b0; mm_wdata_o <= '0;
            tile_a_sram_cs_o <= 1'b0; tile_a_sram_we_o <= 1'b0; tile_a_sram_addr_o <= '0; tile_a_sram_wdata_o <= '0;
            tile_b_sram_cs_o <= 1'b0; tile_b_sram_we_o <= 1'b0; tile_b_sram_addr_o <= '0; tile_b_sram_wdata_o <= '0;

            sa_clear_accum_pulse_reg <= 1'b0; sa_cond_clear_sum_level_reg <= 1'b0; sa_start_new_pass_pulse_reg <= 1'b0;
            sa_activate_comp_reg <= 1'b0; sa_enable_output_reg <= 1'b0; sa_select_row_reg <= '0;
            computation_done <= 1'b0;

            sa_feed_total_cycles_count_reg <= '0;
            c_store_row_read_idx_reg <= '0; c_store_word_in_row_idx_reg <= '0;
            temp_a_col_filled_r <= 1'b0; temp_b_row_filled_r <= 1'b0;
            for (i = 0; i < TILE_DIM_SYSTOLIC; i = i + 1) begin
                temp_a_col_for_sa[i] <= '0; temp_b_row_for_sa[i] <= '0;
            end
            cycle_count <= 0;
        end else begin
            cycle_count <= cycle_count + 1; // Increment cycle count for debug

            current_state_reg <= next_state_reg;
            r_c_idx_reg <= r_c_idx_next; c_c_idx_reg <= c_c_idx_next; k_idx_reg <= k_idx_next;
            current_mm_addr_r <= current_mm_addr_next;
            mm_word_count_reg <= mm_word_count_next;

            sa_feed_a_col_element_idx_r <= sa_feed_a_col_element_idx_next;
            sint8_offset_in_word_a_for_unpack_r <= sint8_offset_in_word_a_for_unpack_next;
            a_element_idx_for_unpack_r <= a_element_idx_for_unpack_next;
            do_unpack_a_pulse_r <= do_unpack_a_pulse_next;

            b_sram_word_idx_in_row_r <= b_sram_word_idx_in_row_next;
            b_sram_word_idx_for_unpack_r <= b_sram_word_idx_for_unpack_next;
            do_unpack_b_pulse_r <= do_unpack_b_pulse_next;

            sa_feed_total_cycles_count_reg <= sa_feed_total_cycles_count_next;
            c_store_row_read_idx_reg <= c_store_row_read_idx_next;
            c_store_word_in_row_idx_reg <= c_store_word_in_row_idx_next;

            mm_cs_o <= mm_cs_o_next_comb; mm_we_o <= mm_we_o_next_comb;
            mm_wdata_o <= mm_wdata_o_next_comb; mm_addr_o  <= mm_addr_o_next_comb;

            tile_a_sram_cs_o <= tile_a_sram_cs_o_next_comb; tile_a_sram_we_o <= tile_a_sram_we_o_next_comb;
            tile_a_sram_addr_o <= tile_a_sram_addr_o_next_comb; tile_a_sram_wdata_o <= tile_a_sram_wdata_o_next_comb;

            tile_b_sram_cs_o <= tile_b_sram_cs_o_next_comb; tile_b_sram_we_o <= tile_b_sram_we_o_next_comb;
            tile_b_sram_addr_o <= tile_b_sram_addr_o_next_comb; tile_b_sram_wdata_o <= tile_b_sram_wdata_o_next_comb;

            sa_clear_accum_pulse_reg <= sa_clear_accum_pulse_next;
            sa_cond_clear_sum_level_reg <= sa_cond_clear_sum_level_next;
            sa_start_new_pass_pulse_reg <= sa_start_new_pass_pulse_next;
            sa_activate_comp_reg <= sa_activate_comp_next;
            sa_enable_output_reg <= sa_enable_output_next;
            sa_select_row_reg <= sa_select_row_next;
            computation_done <= computation_done_next_comb;
            temp_a_col_filled_r <= temp_a_col_filled_next;
            temp_b_row_filled_r <= temp_b_row_filled_next;

            // --- Latch data from Main Memory ---
            if (mm_ready_i && mm_cs_o && !mm_we_o) begin
                $display("[%0t MM_LATCH_DBG CYC:%0d] State: %s. MM_READ_READY! mm_addr_o=%h, mm_rdata_i=%h. WILL_LATCH to latched_mm_rdata_r.",
                         $time, cycle_count, fsm_state_to_string(current_state_reg), mm_addr_o, mm_rdata_i);
                latched_mm_rdata_r <= mm_rdata_i;
            end else if (mm_ready_i && mm_cs_o && mm_we_o) begin
                 $display("[%0t MM_LATCH_DBG CYC:%0d] State: %s. MM_WRITE_READY! mm_addr_o=%h, mm_wdata_o=%h.",
                         $time, cycle_count, fsm_state_to_string(current_state_reg), mm_addr_o, mm_wdata_o);
            end

            // --- Latch data from Tile A SRAM ---
            // Latch happens in S_SA_FEED_CYCLE_A_LATCH_AND_PROCESS state (which was S_SA_FEED_CYCLE_A_READ_WAIT1 in previous cycle)
            if (current_state_reg == S_SA_FEED_CYCLE_A_LATCH_AND_PROCESS && tile_a_sram_cs_o && !tile_a_sram_we_o) begin
                $display("[%0t LATCH_A_DEBUG CYC:%0d] In A_LATCH_PROC. tile_a_sram_rdata_i = %h. WILL_LATCH_TO latched_tile_a_sram_rdata_r. (CS_A=%b, WE_A=%b, Addr_A=%h)",
                         $time, cycle_count, tile_a_sram_rdata_i, tile_a_sram_cs_o, tile_a_sram_we_o, tile_a_sram_addr_o);
                latched_tile_a_sram_rdata_r <= tile_a_sram_rdata_i;
            end

            // --- Latch data from Tile B SRAM ---
            if (current_state_reg == S_SA_FEED_CYCLE_B_LATCH_AND_PROCESS && tile_b_sram_cs_o && !tile_b_sram_we_o) begin
                $display("[%0t LATCH_B_DEBUG CYC:%0d] In B_LATCH_PROC. tile_b_sram_rdata_i = %h. WILL_LATCH_TO latched_tile_b_sram_rdata_r. (CS_B=%b, WE_B=%b, Addr_B=%h)",
                         $time, cycle_count, tile_b_sram_rdata_i, tile_b_sram_cs_o, tile_b_sram_we_o, tile_b_sram_addr_o);
                latched_tile_b_sram_rdata_r <= tile_b_sram_rdata_i;
            end

            // --- Unpack data for Tile A column (triggered by do_unpack_a_pulse_r) ---
            if (do_unpack_a_pulse_r) begin // This pulse is set in _LATCH_AND_PROCESS, so unpack happens one cycle later
                if (a_element_idx_for_unpack_r < TILE_DIM_SYSTOLIC && SINT8_PER_RAM_WORD > 0) begin
                     if (sint8_offset_in_word_a_for_unpack_r < SINT8_PER_RAM_WORD) begin
                        $display("    UNPACK_A_DEBUG CYC:%0d: Setting temp_a_col_for_sa[%2d] from latched_A_rdata=%h with offset_A=%d (val=%h)",
                            cycle_count, a_element_idx_for_unpack_r, latched_tile_a_sram_rdata_r, sint8_offset_in_word_a_for_unpack_r,
                            latched_tile_a_sram_rdata_r[(sint8_offset_in_word_a_for_unpack_r * SINT8_BITS) +: SINT8_BITS]);
                        temp_a_col_for_sa[a_element_idx_for_unpack_r] <= latched_tile_a_sram_rdata_r[(sint8_offset_in_word_a_for_unpack_r * SINT8_BITS) +: SINT8_BITS];
                     end
                end
            end

            // --- Unpack data for Tile B row (triggered by do_unpack_b_pulse_r) ---
            if (do_unpack_b_pulse_r) begin
                if (SINT8_PER_RAM_WORD > 0) begin
                    for (i = 0; i < SINT8_PER_RAM_WORD; i = i + 1) begin
                        if (b_sram_word_idx_for_unpack_r == 0) begin // First word of the B row data
                            if (i < TILE_DIM_SYSTOLIC) begin // Ensure within bounds of temp_b_row_for_sa
                                $display("    UNPACK_B_DEBUG CYC:%0d: Setting temp_b_row_for_sa[%2d] (word_idx_unpack=%d, offset=%d) from latched_B_rdata=%h. Val=%h",
                                    cycle_count, i, b_sram_word_idx_for_unpack_r, i, latched_tile_b_sram_rdata_r, latched_tile_b_sram_rdata_r[(i * SINT8_BITS) +: SINT8_BITS]);
                                temp_b_row_for_sa[i] <= latched_tile_b_sram_rdata_r[(i * SINT8_BITS) +: SINT8_BITS];
                            end
                        end else begin // Second word of the B row data (if TILE_DIM > SINT8_PER_RAM_WORD)
                            if ((i + SINT8_PER_RAM_WORD) < TILE_DIM_SYSTOLIC) begin
                                $display("    UNPACK_B_DEBUG CYC:%0d: Setting temp_b_row_for_sa[%2d] (word_idx_unpack=%d, offset=%d) from latched_B_rdata=%h. Val=%h",
                                    cycle_count, (i + SINT8_PER_RAM_WORD), b_sram_word_idx_for_unpack_r, i, latched_tile_b_sram_rdata_r, latched_tile_b_sram_rdata_r[(i * SINT8_BITS) +: SINT8_BITS]);
                                temp_b_row_for_sa[i + SINT8_PER_RAM_WORD] <= latched_tile_b_sram_rdata_r[(i * SINT8_BITS) +: SINT8_BITS];
                            end
                        end
                    end
                end
            end

            // Display states and important signals
            $display("[%0t ACCEL_DBG CYC:%0d] State: %s (Next: %s)", $time, cycle_count, fsm_state_to_string(current_state_reg), fsm_state_to_string(next_state_reg));
             if (current_state_reg == S_SA_FEED_CYCLE_A_READ_REQ || current_state_reg == S_SA_FEED_CYCLE_A_READ_WAIT1 || current_state_reg == S_SA_FEED_CYCLE_A_LATCH_AND_PROCESS ) begin
                $display("  TileA_SRAM: Addr_o=%h CS=%b WE=%b | A_elem_idx_r=%2d | UnpackPulseA_r=%b IdxUnpackA_r=%2d OffsetUnpackA_r=%d | latched_A_rdata_r=%h | temp_A_filled_r=%b",
                    tile_a_sram_addr_o, tile_a_sram_cs_o, tile_a_sram_we_o,
                    sa_feed_a_col_element_idx_r,
                    do_unpack_a_pulse_r, a_element_idx_for_unpack_r, sint8_offset_in_word_a_for_unpack_r,
                    latched_tile_a_sram_rdata_r, temp_a_col_filled_r);
            end
            // Similar display for B if needed
            if (current_state_reg == S_SA_FEED_CYCLE_EXEC) begin
                 $display("  SA_EXECUTING CYC:%0d: SA_Pass_Count:%2d ValidIn:%b SA_Done:%b A_bus[7:0]=%h B_bus[7:0]=%h",
                    cycle_count, sa_feed_total_cycles_count_reg, sa_array_data_valid_in_wire_systolic, sa_tile_all_pes_done_one_pass_wire,
                    sa_array_a_in_wire_systolic[SINT8_BITS-1:0], sa_array_b_in_wire_systolic[SINT8_BITS-1:0]);
            end

        end
    end

    integer current_a_element_row_idx_local;    // For calculating Tile A SRAM address
    integer current_a_fixed_col_idx_local;    // For calculating Tile A SRAM address (current SA pass cycle)
    integer element_linear_offset_a_local;    // Linear offset of A element in tile
    integer sram_word_addr_a_local;           // Word address in Tile A SRAM
    integer offset_in_word_a_local;           // Byte offset within that SRAM word

    integer base_sram_addr_for_row_b_local;   // Base word address for a row in Tile B SRAM
    integer i_pack_local_debug; // Use a distinct name for local loop var

    // Combinational FSM logic
    always @(*) begin
        next_state_reg = current_state_reg;
        r_c_idx_next = r_c_idx_reg; c_c_idx_next = c_c_idx_reg; k_idx_next = k_idx_reg;
        current_mm_addr_next = current_mm_addr_r;
        mm_addr_o_next_comb = current_mm_addr_r;
        mm_word_count_next = mm_word_count_reg;

        sa_feed_a_col_element_idx_next = sa_feed_a_col_element_idx_r;
        sint8_offset_in_word_a_for_unpack_next = sint8_offset_in_word_a_for_unpack_r; // Default keep
        a_element_idx_for_unpack_next = a_element_idx_for_unpack_r;         // Default keep
        do_unpack_a_pulse_next = 1'b0; // Default low, set high only when triggering unpack

        b_sram_word_idx_in_row_next = b_sram_word_idx_in_row_r;
        b_sram_word_idx_for_unpack_next = b_sram_word_idx_for_unpack_r;       // Default keep
        do_unpack_b_pulse_next = 1'b0; // Default low

        sa_feed_total_cycles_count_next = sa_feed_total_cycles_count_reg;
        c_store_row_read_idx_next = c_store_row_read_idx_reg;
        c_store_word_in_row_idx_next = c_store_word_in_row_idx_reg;

        mm_cs_o_next_comb = 1'b0; mm_we_o_next_comb = 1'b0; mm_wdata_o_next_comb = mm_wdata_o;
        tile_a_sram_cs_o_next_comb = 1'b0; tile_a_sram_we_o_next_comb = 1'b0;
        tile_a_sram_addr_o_next_comb = tile_a_sram_addr_o; tile_a_sram_wdata_o_next_comb = tile_a_sram_wdata_o;
        tile_b_sram_cs_o_next_comb = 1'b0; tile_b_sram_we_o_next_comb = 1'b0;
        tile_b_sram_addr_o_next_comb = tile_b_sram_addr_o; tile_b_sram_wdata_o_next_comb = tile_b_sram_wdata_o;

        sa_clear_accum_pulse_next = 1'b0; sa_start_new_pass_pulse_next = 1'b0;
        computation_done_next_comb = 1'b0;
        sa_cond_clear_sum_level_next = sa_cond_clear_sum_level_reg;
        sa_activate_comp_next = sa_activate_comp_reg;
        sa_enable_output_next = sa_enable_output_reg;
        sa_select_row_next = sa_select_row_reg;
        packed_c_word_comb = {RAM_DATA_WIDTH{1'b0}};
        temp_a_col_filled_next = temp_a_col_filled_r;
        temp_b_row_filled_next = temp_b_row_filled_r;

        case (current_state_reg)
            S_IDLE: begin sa_enable_output_next = 1'b0; sa_activate_comp_next = 1'b0; if (start_computation) next_state_reg = S_INIT_CTL_LOOP; end
            S_INIT_CTL_LOOP: begin r_c_idx_next = '0; c_c_idx_next = '0; k_idx_next = '0; next_state_reg = S_INIT_K_LOOP_PE_SETUP; end
            S_INIT_K_LOOP_PE_SETUP: begin sa_activate_comp_next = 1'b1; sa_cond_clear_sum_level_next = (k_idx_reg == 0); sa_clear_accum_pulse_next = 1'b1; sa_start_new_pass_pulse_next = 1'b1; mm_word_count_next = '0; next_state_reg = S_LOAD_A_MM_ADDR_SETUP; end
            S_LOAD_A_MM_ADDR_SETUP: begin sa_activate_comp_next = 1'b1; mm_addr_o_next_comb = (base_addr_a_mm + (r_c_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + k_idx_reg) * WORDS_PER_SINT8_MM_TILE); mm_word_count_next = '0; next_state_reg = S_LOAD_A_MM_REQ; end
            S_LOAD_A_MM_REQ: begin sa_activate_comp_next = 1'b1; if (WORDS_PER_SINT8_MM_TILE == 0) begin next_state_reg = S_LOAD_B_MM_ADDR_SETUP; end else if (mm_word_count_reg < WORDS_PER_SINT8_MM_TILE) begin mm_cs_o_next_comb = 1'b1; mm_we_o_next_comb = 1'b0; mm_addr_o_next_comb = (base_addr_a_mm + (r_c_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + k_idx_reg) * WORDS_PER_SINT8_MM_TILE) + mm_word_count_reg; next_state_reg = S_LOAD_A_MM_WAIT_READY; end else begin next_state_reg = S_LOAD_B_MM_ADDR_SETUP; end end
            S_LOAD_A_MM_WAIT_READY: begin sa_activate_comp_next = 1'b1; mm_cs_o_next_comb = mm_cs_o; mm_addr_o_next_comb = mm_addr_o; if (mm_ready_i) begin mm_cs_o_next_comb = 1'b0; next_state_reg = S_LOAD_A_TILE_SRAM_WRITE; end else begin next_state_reg = S_LOAD_A_MM_WAIT_READY; end end
            S_LOAD_A_TILE_SRAM_WRITE: begin sa_activate_comp_next = 1'b1; tile_a_sram_cs_o_next_comb = 1'b1; tile_a_sram_we_o_next_comb = 1'b1; tile_a_sram_addr_o_next_comb = mm_word_count_reg; tile_a_sram_wdata_o_next_comb = latched_mm_rdata_r; mm_word_count_next = mm_word_count_reg + 1; next_state_reg = S_LOAD_A_MM_REQ; end
            S_LOAD_B_MM_ADDR_SETUP: begin sa_activate_comp_next = 1'b1; mm_addr_o_next_comb = (base_addr_b_mm + (k_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + c_c_idx_reg) * WORDS_PER_SINT8_MM_TILE); mm_word_count_next = '0; next_state_reg = S_LOAD_B_MM_REQ; end
            S_LOAD_B_MM_REQ: begin sa_activate_comp_next = 1'b1; if (WORDS_PER_SINT8_MM_TILE == 0) begin next_state_reg = S_SA_FEED_SETUP; end else if (mm_word_count_reg < WORDS_PER_SINT8_MM_TILE) begin mm_cs_o_next_comb = 1'b1; mm_we_o_next_comb = 1'b0; mm_addr_o_next_comb = (base_addr_b_mm + (k_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + c_c_idx_reg) * WORDS_PER_SINT8_MM_TILE) + mm_word_count_reg; next_state_reg = S_LOAD_B_MM_WAIT_READY; end else begin next_state_reg = S_SA_FEED_SETUP; end end
            S_LOAD_B_MM_WAIT_READY: begin sa_activate_comp_next = 1'b1; mm_cs_o_next_comb = mm_cs_o; mm_addr_o_next_comb = mm_addr_o; if (mm_ready_i) begin mm_cs_o_next_comb = 1'b0; next_state_reg = S_LOAD_B_TILE_SRAM_WRITE; end else begin next_state_reg = S_LOAD_B_MM_WAIT_READY; end end
            S_LOAD_B_TILE_SRAM_WRITE: begin sa_activate_comp_next = 1'b1; tile_b_sram_cs_o_next_comb = 1'b1; tile_b_sram_we_o_next_comb = 1'b1; tile_b_sram_addr_o_next_comb = mm_word_count_reg; tile_b_sram_wdata_o_next_comb = latched_mm_rdata_r; mm_word_count_next = mm_word_count_reg + 1; next_state_reg = S_LOAD_B_MM_REQ; end

            S_SA_FEED_SETUP: begin
                sa_activate_comp_next = 1'b1;
                sa_feed_total_cycles_count_next = '0;       // Current SA pass cycle (0 to TILE_DIM-1)
                sa_feed_a_col_element_idx_next = 0;         // Current element in A column being read (0 to TILE_DIM-1)
                b_sram_word_idx_in_row_next = 0;            // Current word index for B row being read (0 or 1)
                temp_a_col_filled_next = 1'b0;
                temp_b_row_filled_next = 1'b0;
                next_state_reg = S_SA_FEED_CYCLE_A_READ_REQ;
            end

            S_SA_FEED_CYCLE_A_READ_REQ: begin // Cycle N: Request read for A element
                sa_activate_comp_next = 1'b1;
                current_a_element_row_idx_local = sa_feed_a_col_element_idx_r; // Row of A element (0 to TILE_DIM-1)
                current_a_fixed_col_idx_local = sa_feed_total_cycles_count_reg; // Column of A element (current SA pass cycle)
                element_linear_offset_a_local = current_a_element_row_idx_local * TILE_DIM_SYSTOLIC + current_a_fixed_col_idx_local;

                sram_word_addr_a_local = element_linear_offset_a_local / SINT8_PER_RAM_WORD;
                offset_in_word_a_local = element_linear_offset_a_local % SINT8_PER_RAM_WORD;

                tile_a_sram_addr_o_next_comb = sram_word_addr_a_local;
                tile_a_sram_cs_o_next_comb = 1'b1;
                tile_a_sram_we_o_next_comb = 1'b0;

                // Store index and offset that correspond to this request for later use in LATCH_AND_PROCESS
                a_element_idx_for_unpack_next = current_a_element_row_idx_local;
                sint8_offset_in_word_a_for_unpack_next = offset_in_word_a_local;

                next_state_reg = S_SA_FEED_CYCLE_A_READ_WAIT1;
            end

            S_SA_FEED_CYCLE_A_READ_WAIT1: begin // Cycle N+1: First wait cycle for A data
                sa_activate_comp_next = 1'b1;
                tile_a_sram_cs_o_next_comb = tile_a_sram_cs_o; // Keep CS asserted (or de-assert if SRAM latches addr)
                tile_a_sram_addr_o_next_comb = tile_a_sram_addr_o; // Keep address
                // Data arrives at rdata_i at the END of this cycle
                next_state_reg = S_SA_FEED_CYCLE_A_LATCH_AND_PROCESS;
            end

            S_SA_FEED_CYCLE_A_LATCH_AND_PROCESS: begin // Cycle N+2: Latch A data, prepare for unpack next cycle
                sa_activate_comp_next = 1'b1;
                // Latching of tile_a_sram_rdata_i into latched_tile_a_sram_rdata_r happens in clocked block
                // based on current_state_reg being S_SA_FEED_CYCLE_A_LATCH_AND_PROCESS.
                // CS and Addr should still be valid from previous states if SRAM needs them.
                tile_a_sram_cs_o_next_comb = tile_a_sram_cs_o;
                tile_a_sram_addr_o_next_comb = tile_a_sram_addr_o;


                do_unpack_a_pulse_next = 1'b1; // Set pulse to unpack the latched data in the *next* cycle

                if (sa_feed_a_col_element_idx_r == TILE_DIM_SYSTOLIC - 1) begin // Done with current A column
                    temp_a_col_filled_next = 1'b1;
                    // sa_feed_a_col_element_idx_next = 0; // Reset for next A column later
                    next_state_reg = S_SA_FEED_CYCLE_B_READ_REQ; // Move to read B row
                end else begin
                    sa_feed_a_col_element_idx_next = sa_feed_a_col_element_idx_r + 1; // Next element in A column
                    next_state_reg = S_SA_FEED_CYCLE_A_READ_REQ;
                end
            end

            S_SA_FEED_CYCLE_B_READ_REQ: begin // Cycle M: Request read for B element
                sa_activate_comp_next = 1'b1;
                // B row is indexed by sa_feed_total_cycles_count_reg
                // We read TILE_DIM_SYSTOLIC / SINT8_PER_RAM_WORD words for B row.
                // Here, b_sram_word_idx_in_row_r is 0 for first word, 1 for second (if needed)
                base_sram_addr_for_row_b_local = (sa_feed_total_cycles_count_reg * TILE_DIM_SYSTOLIC) / SINT8_PER_RAM_WORD;
                tile_b_sram_addr_o_next_comb = base_sram_addr_for_row_b_local + b_sram_word_idx_in_row_r;
                tile_b_sram_cs_o_next_comb = 1'b1;
                tile_b_sram_we_o_next_comb = 1'b0;

                // Store word index that corresponds to this request
                b_sram_word_idx_for_unpack_next = b_sram_word_idx_in_row_r;

                next_state_reg = S_SA_FEED_CYCLE_B_READ_WAIT1;
            end

            S_SA_FEED_CYCLE_B_READ_WAIT1: begin // Cycle M+1: First wait for B data
                sa_activate_comp_next = 1'b1;
                tile_b_sram_cs_o_next_comb = tile_b_sram_cs_o;
                tile_b_sram_addr_o_next_comb = tile_b_sram_addr_o;
                next_state_reg = S_SA_FEED_CYCLE_B_LATCH_AND_PROCESS;
            end

            S_SA_FEED_CYCLE_B_LATCH_AND_PROCESS: begin // Cycle M+2: Latch B data, prepare for unpack
                sa_activate_comp_next = 1'b1;
                tile_b_sram_cs_o_next_comb = tile_b_sram_cs_o;
                tile_b_sram_addr_o_next_comb = tile_b_sram_addr_o;

                do_unpack_b_pulse_next = 1'b1;

                // Logic for multiple words for B if TILE_DIM_SYSTOLIC > SINT8_PER_RAM_WORD
                if (b_sram_word_idx_in_row_r == B_WORDS_PER_ROW - 1) begin // Done with all words for this B row
                    temp_b_row_filled_next = 1'b1;
                    // b_sram_word_idx_in_row_next = 0; // Reset for next B row later
                    if (temp_a_col_filled_r) begin // If A column is also ready
                        next_state_reg = S_SA_PRE_EXEC_CHECK;
                    end else begin // Should not happen if A fills first or concurrently
                        $display("[%0t ACCEL_WARN CYC:%0d] In B_LATCH (all words done), but A_col not filled! Goto PRE_EXEC_CHECK.", $time, cycle_count);
                        next_state_reg = S_SA_PRE_EXEC_CHECK; // Still go to check
                    end
                end else begin
                    b_sram_word_idx_in_row_next = b_sram_word_idx_in_row_r + 1; // Next word in B row
                    next_state_reg = S_SA_FEED_CYCLE_B_READ_REQ;
                end
            end

            S_SA_PRE_EXEC_CHECK: begin
                sa_activate_comp_next = 1'b1;
                if (temp_a_col_filled_r && temp_b_row_filled_r) begin
                    next_state_reg = S_SA_FEED_CYCLE_EXEC;
                end else begin
                    // Stay in this state, data is still being prepared by unpack pulses from previous LATCH states
                    next_state_reg = S_SA_PRE_EXEC_CHECK;
                end
            end

            S_SA_FEED_CYCLE_EXEC: begin
                sa_activate_comp_next = 1'b1;
                // Unpack pulses (do_unpack_a/b_pulse_r) should have fired in the previous cycle
                // So temp_a_col_for_sa and temp_b_row_for_sa are now filled with latest data for this SA pass

                if (sa_feed_total_cycles_count_reg == TILE_DIM_SYSTOLIC - 1) begin // Done all SA pass cycles for this (A,B) tile pair
                    next_state_reg = S_SA_WAIT_DONE;
                end else begin // More SA pass cycles needed for this (A,B) tile pair
                    sa_feed_total_cycles_count_next = sa_feed_total_cycles_count_reg + 1;
                    // Reset for the next SA pass cycle's data fetch
                    temp_a_col_filled_next = 1'b0;
                    temp_b_row_filled_next = 1'b0;
                    sa_feed_a_col_element_idx_next = 0; // Start reading A column from first element
                    b_sram_word_idx_in_row_next = 0;    // Start reading B row from first word
                    next_state_reg = S_SA_FEED_CYCLE_A_READ_REQ;
                end
            end

            S_SA_WAIT_DONE: begin sa_activate_comp_next = 1'b1; if (sa_tile_all_pes_done_one_pass_wire) begin sa_activate_comp_next = 1'b0; next_state_reg = S_K_LOOP_INCREMENT; end else begin next_state_reg = S_SA_WAIT_DONE; end end
            S_K_LOOP_INCREMENT: begin sa_activate_comp_next = 1'b0; if (k_idx_reg == SAFE_TILES_PER_ROW_COL_GLOBAL - 1) begin mm_word_count_next = '0; c_store_row_read_idx_next = '0; next_state_reg = S_STORE_C_MM_ADDR_SETUP; end else begin k_idx_next = k_idx_reg + 1; next_state_reg = S_INIT_K_LOOP_PE_SETUP; end end
            S_STORE_C_MM_ADDR_SETUP: begin sa_activate_comp_next = 1'b0; mm_addr_o_next_comb = (base_addr_c_mm + (r_c_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + c_c_idx_reg) * WORDS_PER_SINT32_MM_TILE); mm_word_count_next = '0; c_store_row_read_idx_next = '0; c_store_word_in_row_idx_next = '0; next_state_reg = S_STORE_C_TILE_SA_READ_SETUP; end
            S_STORE_C_TILE_SA_READ_SETUP: begin sa_activate_comp_next = 1'b0; if (c_store_row_read_idx_reg < TILE_DIM_SYSTOLIC) begin sa_enable_output_next = 1'b1; sa_select_row_next = c_store_row_read_idx_reg[SA_SELECT_ROW_WIDTH-1:0]; next_state_reg = S_STORE_C_TILE_SA_READ_WAIT_VALID; end else begin sa_enable_output_next = 1'b0; next_state_reg = S_CTL_LOOP_INCREMENT; end end
            S_STORE_C_TILE_SA_READ_WAIT_VALID: begin
                sa_activate_comp_next = 1'b0;
                sa_enable_output_next = 1'b1; 
                sa_select_row_next = sa_select_row_reg; 
                if (sa_tile_row_result_valid_wire) begin
                    $display("[%0t ACCEL_C_READ CYC:%0d] Row %d valid from SA. SA_Result_Bus = %h",
                             $time, cycle_count, sa_select_row_reg, sa_tile_row_result_out_wire);
                    next_state_reg = S_STORE_C_MM_WRITE_REQ;
                end else begin
                    next_state_reg = S_STORE_C_TILE_SA_READ_WAIT_VALID;
                end
            end
            S_STORE_C_MM_WRITE_REQ: begin
                sa_activate_comp_next = 1'b0;
                sa_enable_output_next = 1'b1; 
                sa_select_row_next = sa_select_row_reg; 

                $display("[%0t ACCEL_PACK_INPUTS CYC:%0d] State:WRITE_REQ. SA_Enable_Reg=%b, SA_Select_Reg=%d, SA_Result_Bus_RAW=%h, c_store_word_idx=%d",
                         $time, cycle_count, sa_enable_output_reg, sa_select_row_reg, sa_tile_row_result_out_wire, c_store_word_in_row_idx_reg);

                if (SINT32_PER_RAM_WORD > 0) begin
                    for (i_pack_local_debug=0; i_pack_local_debug < SINT32_PER_RAM_WORD; i_pack_local_debug=i_pack_local_debug+1) begin
                        if((c_store_word_in_row_idx_reg * SINT32_PER_RAM_WORD + i_pack_local_debug) < TILE_DIM_SYSTOLIC) begin
                            packed_c_word_comb[(i_pack_local_debug*PE_ACCUM_BITS)+:PE_ACCUM_BITS] = sa_tile_row_result_out_wire[((c_store_word_in_row_idx_reg * SINT32_PER_RAM_WORD + i_pack_local_debug)*PE_ACCUM_BITS)+:PE_ACCUM_BITS];
                        end else begin
                            packed_c_word_comb[(i_pack_local_debug*PE_ACCUM_BITS)+:PE_ACCUM_BITS] = {PE_ACCUM_BITS{1'b0}};
                        end
                    end
                end
                // --- END TEMPORARY: Packing logic ---

                $display("[%0t ACCEL_MM_WDATA_PREP CYC:%0d] State:WRITE_REQ. BEFORE assignment to mm_wdata_o_next_comb, packed_c_word_comb = %h",
                         $time, cycle_count, packed_c_word_comb);

                mm_wdata_o_next_comb = packed_c_word_comb;

                $display("[%0t ACCEL_MM_WDATA_PREP CYC:%0d] State:WRITE_REQ. AFTER assignment, mm_wdata_o_next_comb = %h",
                         $time, cycle_count, mm_wdata_o_next_comb);
                
                mm_cs_o_next_comb = 1'b1;
                mm_we_o_next_comb = 1'b1; // Write
                mm_addr_o_next_comb = (base_addr_c_mm + (r_c_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + c_c_idx_reg) * WORDS_PER_SINT32_MM_TILE) + mm_word_count_reg;
                next_state_reg = S_STORE_C_MM_WRITE_WAIT_READY;
            end
            S_STORE_C_MM_WRITE_WAIT_READY: begin sa_activate_comp_next = 1'b0; sa_enable_output_next = 1'b1; sa_select_row_next = sa_select_row_reg; mm_cs_o_next_comb = mm_cs_o; mm_we_o_next_comb = mm_we_o; mm_addr_o_next_comb = mm_addr_o; if (mm_ready_i) begin mm_cs_o_next_comb = 1'b0; mm_we_o_next_comb = 1'b0; mm_word_count_next = mm_word_count_reg + 1; if (NUM_PACKED_WORDS_PER_SA_ROW_C == 0) begin c_store_row_read_idx_next = c_store_row_read_idx_reg + 1; c_store_word_in_row_idx_next = '0; next_state_reg = S_STORE_C_TILE_SA_READ_SETUP; end else if (c_store_word_in_row_idx_reg == NUM_PACKED_WORDS_PER_SA_ROW_C - 1) begin c_store_row_read_idx_next = c_store_row_read_idx_reg + 1; c_store_word_in_row_idx_next = '0; next_state_reg = S_STORE_C_TILE_SA_READ_SETUP; end else begin c_store_word_in_row_idx_next = c_store_word_in_row_idx_reg + 1; next_state_reg = S_STORE_C_MM_WRITE_REQ; end end else begin next_state_reg = S_STORE_C_MM_WRITE_WAIT_READY; end end
            S_CTL_LOOP_INCREMENT: begin sa_activate_comp_next = 1'b0; sa_enable_output_next = 1'b0; if (c_c_idx_reg == SAFE_TILES_PER_ROW_COL_GLOBAL - 1) begin c_c_idx_next = '0; if (r_c_idx_reg == SAFE_TILES_PER_ROW_COL_GLOBAL - 1) begin next_state_reg = S_FINISH; end else begin r_c_idx_next = r_c_idx_reg + 1; k_idx_next = '0; next_state_reg = S_INIT_K_LOOP_PE_SETUP; end end else begin c_c_idx_next = c_c_idx_reg + 1; k_idx_next = '0; next_state_reg = S_INIT_K_LOOP_PE_SETUP; end end
            S_FINISH: begin sa_activate_comp_next = 1'b0; computation_done_next_comb = 1'b1; next_state_reg = S_IDLE; end
            default: begin sa_activate_comp_next = 1'b0; next_state_reg = S_IDLE; end
        endcase

        if (current_state_reg == S_STORE_C_MM_WRITE_REQ || current_state_reg == S_STORE_C_TILE_SA_READ_WAIT_VALID) begin
            if (SINT32_PER_RAM_WORD > 0) begin
                integer i_pack;
                for (i_pack=0; i_pack < SINT32_PER_RAM_WORD; i_pack=i_pack+1) begin
                    if((c_store_word_in_row_idx_reg * SINT32_PER_RAM_WORD + i_pack) < TILE_DIM_SYSTOLIC) begin
                        packed_c_word_comb[(i_pack*PE_ACCUM_BITS)+:PE_ACCUM_BITS] = sa_tile_row_result_out_wire[((c_store_word_in_row_idx_reg * SINT32_PER_RAM_WORD + i_pack)*PE_ACCUM_BITS)+:PE_ACCUM_BITS];
                    end else begin
                        packed_c_word_comb[(i_pack*PE_ACCUM_BITS)+:PE_ACCUM_BITS] = {PE_ACCUM_BITS{1'b0}};
                    end
                end
            end
        end
    end

    genvar i_feed;
    generate
        for (i_feed = 0; i_feed < TILE_DIM_SYSTOLIC; i_feed = i_feed + 1) begin : sa_feed_assignment
            if (SINT8_BITS > 0) begin
                assign current_a_column_for_feed_wire[(i_feed*SINT8_BITS)+:SINT8_BITS] = temp_a_col_for_sa[i_feed];
                assign current_b_row_for_feed_wire[(i_feed*SINT8_BITS)+:SINT8_BITS] = temp_b_row_for_sa[i_feed];
            end else begin
                assign current_a_column_for_feed_wire[(i_feed*SINT8_BITS)+:SINT8_BITS] = '0;
                assign current_b_row_for_feed_wire[(i_feed*SINT8_BITS)+:SINT8_BITS] = '0;
            end
        end
    endgenerate

    assign sa_array_a_in_wire_systolic = (current_state_reg == S_SA_FEED_CYCLE_EXEC) ? current_a_column_for_feed_wire : {SAFE_SA_INPUT_BUS_WIDTH{1'b0}};
    assign sa_array_b_in_wire_systolic = (current_state_reg == S_SA_FEED_CYCLE_EXEC) ? current_b_row_for_feed_wire :  {SAFE_SA_INPUT_BUS_WIDTH{1'b0}};
    assign sa_array_data_valid_in_wire_systolic = (current_state_reg == S_SA_FEED_CYCLE_EXEC);

endmodule