// accelerator.v
`timescale 1ns / 1ps

module accelerator #(
    parameter MATRIX_DIM_GLOBAL = 32,
    parameter TILE_DIM_SYSTOLIC = 16,
    parameter RAM_DATA_WIDTH = 64,
    parameter RAM_ADDR_WIDTH = 17,
    parameter SINT8_BITS = 8,
    parameter BF16_BITS = 16
) (
    input wire clk,
    input wire rst_n,

    input wire start_computation,
    output wire computation_done,

    // RAM Interface
    output wire [RAM_ADDR_WIDTH-1:0] ram_address,
    output wire [RAM_DATA_WIDTH-1:0] ram_write_data,
    input  wire [RAM_DATA_WIDTH-1:0] ram_read_data,
    output wire                      ram_cs,
    output wire                      ram_web,

    input wire [RAM_ADDR_WIDTH-1:0] base_addr_a,
    input wire [RAM_ADDR_WIDTH-1:0] base_addr_b,
    input wire [RAM_ADDR_WIDTH-1:0] base_addr_c
);

    // Derived Parameters
    localparam SINT8_PER_RAM_WORD = RAM_DATA_WIDTH / SINT8_BITS;
    localparam BF16_PER_RAM_WORD  = RAM_DATA_WIDTH / BF16_BITS;

    localparam TILES_PER_ROW_COL_GLOBAL = MATRIX_DIM_GLOBAL / TILE_DIM_SYSTOLIC;
    localparam SAFE_TILES_PER_ROW_COL_GLOBAL = (TILES_PER_ROW_COL_GLOBAL == 0) ? 1 : TILES_PER_ROW_COL_GLOBAL;

    localparam WORDS_PER_SINT8_TILE_CALC = (TILE_DIM_SYSTOLIC * TILE_DIM_SYSTOLIC * SINT8_BITS) / RAM_DATA_WIDTH;
    localparam WORDS_PER_SINT8_TILE = (WORDS_PER_SINT8_TILE_CALC == 0 && (TILE_DIM_SYSTOLIC * TILE_DIM_SYSTOLIC * SINT8_BITS) > 0) ? 1 : WORDS_PER_SINT8_TILE_CALC;


    localparam WORDS_PER_BF16_TILE_CALC  = (TILE_DIM_SYSTOLIC * TILE_DIM_SYSTOLIC * BF16_BITS) / RAM_DATA_WIDTH;
    localparam WORDS_PER_BF16_TILE = (WORDS_PER_BF16_TILE_CALC == 0 && (TILE_DIM_SYSTOLIC * TILE_DIM_SYSTOLIC * BF16_BITS) > 0) ? 1 : WORDS_PER_BF16_TILE_CALC;


    localparam TILE_AREA = TILE_DIM_SYSTOLIC * TILE_DIM_SYSTOLIC;

    localparam MAX_WORDS_PER_TILE_CALC = (WORDS_PER_SINT8_TILE > WORDS_PER_BF16_TILE) ? WORDS_PER_SINT8_TILE : WORDS_PER_BF16_TILE;
    localparam SAFE_MAX_WORDS_PER_TILE = (MAX_WORDS_PER_TILE_CALC == 0) ? 1 : MAX_WORDS_PER_TILE_CALC;
    localparam RAM_TILE_WORD_COUNT_WIDTH = (SAFE_MAX_WORDS_PER_TILE <= 1) ? 1 : $clog2(SAFE_MAX_WORDS_PER_TILE);

    localparam LOOP_COUNTER_WIDTH = (SAFE_TILES_PER_ROW_COL_GLOBAL <= 1) ? 1 : $clog2(SAFE_TILES_PER_ROW_COL_GLOBAL);

    localparam NUM_PACKED_WORDS_PER_SA_ROW_CALC = (BF16_PER_RAM_WORD == 0) ? TILE_DIM_SYSTOLIC : (TILE_DIM_SYSTOLIC / BF16_PER_RAM_WORD);
    localparam NUM_PACKED_WORDS_PER_SA_ROW = (NUM_PACKED_WORDS_PER_SA_ROW_CALC == 0 && TILE_DIM_SYSTOLIC > 0) ? 1 : NUM_PACKED_WORDS_PER_SA_ROW_CALC;
    localparam _NUM_PACKED_WORDS_PER_SA_ROW_SAFE = (NUM_PACKED_WORDS_PER_SA_ROW == 0) ? 1 : NUM_PACKED_WORDS_PER_SA_ROW;
    localparam C_STORE_WORD_IN_ROW_IDX_WIDTH = (_NUM_PACKED_WORDS_PER_SA_ROW_SAFE <= 1) ? 1 : $clog2(_NUM_PACKED_WORDS_PER_SA_ROW_SAFE);

    localparam _TILE_DIM_SYSTOLIC_PLUS_1 = TILE_DIM_SYSTOLIC + 1;
    localparam SA_FEED_CYCLE_IDX_WIDTH = (_TILE_DIM_SYSTOLIC_PLUS_1 <= 1) ? 1 : $clog2(_TILE_DIM_SYSTOLIC_PLUS_1);
    localparam C_STORE_ROW_IDX_WIDTH = (_TILE_DIM_SYSTOLIC_PLUS_1 <= 1) ? 1 : $clog2(_TILE_DIM_SYSTOLIC_PLUS_1);
    localparam _SAFE_TILE_DIM_FOR_SELECT = (TILE_DIM_SYSTOLIC == 0) ? 1 : TILE_DIM_SYSTOLIC;
    localparam SA_SELECT_ROW_WIDTH = (_SAFE_TILE_DIM_FOR_SELECT <= 1) ? 1 : $clog2(_SAFE_TILE_DIM_FOR_SELECT);

    localparam SA_DATA_PATH_WIDTH = TILE_DIM_SYSTOLIC * BF16_BITS;
    localparam SAFE_SA_BUS_WIDTH = (SA_DATA_PATH_WIDTH == 0) ? 1 : SA_DATA_PATH_WIDTH;

    wire [SAFE_SA_BUS_WIDTH-1:0] sa_array_a_in_wire;
    wire [SAFE_SA_BUS_WIDTH-1:0] sa_array_b_in_wire;
    wire [SAFE_SA_BUS_WIDTH-1:0] sa_array_a_out_wire;
    wire [SAFE_SA_BUS_WIDTH-1:0] sa_array_b_out_wire;
    wire [SAFE_SA_BUS_WIDTH-1:0] sa_tile_row_result_out_wire;

    wire sa_array_data_valid_in_wire;
    wire sa_array_a_data_valid_out_wire;
    wire sa_array_b_data_valid_out_wire;
    wire sa_tile_row_result_valid_wire;
    wire sa_tile_all_pes_done_one_pass_wire;
    wire sa_tile_had_nan_wire;
    wire sa_tile_had_inf_wire;

    // FSM States
    localparam S_IDLE = 0;
    localparam S_INIT_CTL_LOOP = 1;
    localparam S_INIT_K_LOOP_PE_SETUP = 2;
    localparam S_LOAD_A_TILE_ADDR = 3;
    localparam S_LOAD_A_TILE_RAM_READ_REQ = 4;
    localparam S_LOAD_A_TILE_RAM_READ_WAIT = 5;
    localparam S_LOAD_A_TILE_CONVERT_STORE = 6;
    localparam S_LOAD_B_TILE_ADDR = 7;
    localparam S_LOAD_B_TILE_RAM_READ_REQ = 8;
    localparam S_LOAD_B_TILE_RAM_READ_WAIT = 9;
    localparam S_LOAD_B_TILE_CONVERT_STORE = 10;
    localparam S_SA_FEED_SETUP = 11;
    localparam S_SA_FEED_CYCLE = 12;
    localparam S_SA_WAIT_DONE = 13;
    localparam S_K_LOOP_INCREMENT = 14;
    localparam S_STORE_C_TILE_ADDR = 15;
    localparam S_STORE_C_TILE_SA_READ_SETUP = 16;
    localparam S_STORE_C_TILE_RAM_WRITE = 17;
    localparam S_CTL_LOOP_INCREMENT = 18;
    localparam S_FINISH = 19;
    localparam S_STORE_C_TILE_SA_READ_WAIT_VALID = 20;
    localparam S_LOAD_A_TILE_RAM_READ_WAIT2 = 21;
    localparam S_LOAD_B_TILE_RAM_READ_WAIT2 = 22;

    reg [5:0] current_state_reg, next_state_reg;

    reg [LOOP_COUNTER_WIDTH-1:0] r_c_idx_reg, r_c_idx_next;
    reg [LOOP_COUNTER_WIDTH-1:0] c_c_idx_reg, c_c_idx_next;
    reg [LOOP_COUNTER_WIDTH-1:0] k_idx_reg, k_idx_next;

    reg [RAM_ADDR_WIDTH-1:0] current_ram_addr_reg, current_ram_addr_next;
    reg [RAM_TILE_WORD_COUNT_WIDTH-1:0] ram_tile_word_count_reg, ram_tile_word_count_next;
    reg [RAM_DATA_WIDTH-1:0] ram_read_data_d1_reg;

    reg [BF16_BITS-1:0] a_tile_buffer_bf16 [0:TILE_AREA-1];
    reg [BF16_BITS-1:0] b_tile_buffer_bf16 [0:TILE_AREA-1];

    integer j_idx_loop;
    integer base_idx_in_buffer;
    integer base_idx_in_buffer_b;

    wire [SINT8_BITS-1:0] sint8_inputs_from_ram [0:SINT8_PER_RAM_WORD-1];
    wire [BF16_BITS-1:0] bf16_outputs_from_converter [0:SINT8_PER_RAM_WORD-1];

    reg [SA_FEED_CYCLE_IDX_WIDTH-1:0]   sa_feed_cycle_idx_reg, sa_feed_cycle_idx_next;
    reg [C_STORE_ROW_IDX_WIDTH-1:0]     c_store_row_read_idx_reg, c_store_row_read_idx_next;
    reg [C_STORE_WORD_IN_ROW_IDX_WIDTH-1:0] c_store_word_in_row_idx_reg, c_store_word_in_row_idx_next;

    reg ram_cs_reg, ram_cs_next;
    reg ram_web_reg, ram_web_next;
    reg [RAM_DATA_WIDTH-1:0] ram_write_data_reg, ram_write_data_next;

    reg sa_clear_accum_pulse_reg, sa_clear_accum_pulse_next;
    reg sa_cond_clear_sum_level_reg, sa_cond_clear_sum_level_next;
    reg sa_start_new_pass_pulse_reg, sa_start_new_pass_pulse_next;
    reg sa_activate_comp_reg, sa_activate_comp_next;
    reg sa_enable_output_reg, sa_enable_output_next;
    reg [SA_SELECT_ROW_WIDTH-1:0] sa_select_row_reg, sa_select_row_next;

    reg computation_done_pulse_reg, computation_done_pulse_next;
    reg [RAM_DATA_WIDTH-1:0] packed_c_word_comb;

    reg [SA_DATA_PATH_WIDTH-1:0] current_a_column_for_feed;
    reg [SA_DATA_PATH_WIDTH-1:0] current_b_row_for_feed;

    function [15*8-1:0] fsm_state_to_string (input [5:0] state_in); // Increased string length
        case(state_in)
            S_IDLE:                            fsm_state_to_string = "S_IDLE";
            S_INIT_CTL_LOOP:                   fsm_state_to_string = "S_INIT_CTL_LOOP";
            S_INIT_K_LOOP_PE_SETUP:            fsm_state_to_string = "S_INIT_K_L_PE_SETUP"; // Shorter for space
            S_LOAD_A_TILE_ADDR:                fsm_state_to_string = "S_LOAD_A_ADDR";
            S_LOAD_A_TILE_RAM_READ_REQ:        fsm_state_to_string = "S_LOAD_A_RAM_REQ";
            S_LOAD_A_TILE_RAM_READ_WAIT:       fsm_state_to_string = "S_LOAD_A_RAM_WAIT";
            S_LOAD_A_TILE_RAM_READ_WAIT2:      fsm_state_to_string = "S_LOAD_A_RAM_WAIT2";
            S_LOAD_A_TILE_CONVERT_STORE:       fsm_state_to_string = "S_LOAD_A_CONV_STR";
            S_LOAD_B_TILE_ADDR:                fsm_state_to_string = "S_LOAD_B_ADDR";
            S_LOAD_B_TILE_RAM_READ_REQ:        fsm_state_to_string = "S_LOAD_B_RAM_REQ";
            S_LOAD_B_TILE_RAM_READ_WAIT:       fsm_state_to_string = "S_LOAD_B_RAM_WAIT";
            S_LOAD_B_TILE_RAM_READ_WAIT2:      fsm_state_to_string = "S_LOAD_B_RAM_WAIT2";
            S_LOAD_B_TILE_CONVERT_STORE:       fsm_state_to_string = "S_LOAD_B_CONV_STR";
            S_SA_FEED_SETUP:                   fsm_state_to_string = "S_SA_FEED_SETUP";
            S_SA_FEED_CYCLE:                   fsm_state_to_string = "S_SA_FEED_CYCLE";
            S_SA_WAIT_DONE:                    fsm_state_to_string = "S_SA_WAIT_DONE";
            S_K_LOOP_INCREMENT:                fsm_state_to_string = "S_K_LOOP_INC";
            S_STORE_C_TILE_ADDR:               fsm_state_to_string = "S_STORE_C_ADDR";
            S_STORE_C_TILE_SA_READ_SETUP:      fsm_state_to_string = "S_STORE_C_SA_RD_SETUP";
            S_STORE_C_TILE_SA_READ_WAIT_VALID: fsm_state_to_string = "S_STORE_C_SA_RD_WAITV";
            S_STORE_C_TILE_RAM_WRITE:          fsm_state_to_string = "S_STORE_C_RAM_WR";
            S_CTL_LOOP_INCREMENT:              fsm_state_to_string = "S_CTL_LOOP_INC";
            S_FINISH:                          fsm_state_to_string = "S_FINISH";
            default:                           fsm_state_to_string = "UNKNOWN_STATE";
        endcase
    endfunction

    reg         prev_start_computation_dbg;
    reg [5:0]   prev_current_state_reg_dbg;
    reg         prev_sa_tile_all_pes_done_one_pass_wire_dbg;
    reg         prev_sa_tile_row_result_valid_wire_dbg;
    reg [RAM_DATA_WIDTH-1:0] prev_ram_read_data_d1_reg_dbg;

    initial begin
        prev_start_computation_dbg = 1'b0;
        prev_current_state_reg_dbg = S_IDLE;
        prev_sa_tile_all_pes_done_one_pass_wire_dbg = 1'b0;
        prev_sa_tile_row_result_valid_wire_dbg = 1'b0;
        prev_ram_read_data_d1_reg_dbg = {RAM_DATA_WIDTH{1'bx}};
    end

    generate
        genvar i_conv;
        for (i_conv = 0; i_conv < SINT8_PER_RAM_WORD; i_conv = i_conv + 1) begin : conv_gen
            assign sint8_inputs_from_ram[i_conv] = ram_read_data_d1_reg[(i_conv*SINT8_BITS) +: SINT8_BITS];
            sint8_to_bf16_converter u_sint8_to_bf16 (
                .sint8_in (sint8_inputs_from_ram[i_conv]),
                .bf16_out (bf16_outputs_from_converter[i_conv])
            );
        end
    endgenerate

    systolic_array #(
        .SIZE(TILE_DIM_SYSTOLIC),
        .DATA_WIDTH(BF16_BITS)
    ) u_systolic_array (
        .clk(clk),
        .rst_n(rst_n),
        .clear_all_pe_accumulators(sa_clear_accum_pulse_reg),
        .conditionally_clear_pe_sums_level(sa_cond_clear_sum_level_reg),
        .activate_pe_computation(sa_activate_comp_reg),
        .array_data_valid_in(sa_array_data_valid_in_wire),
        .array_a_in(sa_array_a_in_wire),
        .array_b_in(sa_array_b_in_wire),
        .select_output_row_idx(sa_select_row_reg),
        .enable_tile_row_output(sa_enable_output_reg),
        .start_new_systolic_pass(sa_start_new_pass_pulse_reg),
        .accelerator_is_computing(1'b0),
        .array_a_data_valid_out(sa_array_a_data_valid_out_wire),
        .array_a_out(sa_array_a_out_wire),
        .array_b_data_valid_out(sa_array_b_data_valid_out_wire),
        .array_b_out(sa_array_b_out_wire),
        .tile_row_result_out(sa_tile_row_result_out_wire),
        .tile_row_result_valid(sa_tile_row_result_valid_wire),
        .tile_all_pes_done_one_pass(sa_tile_all_pes_done_one_pass_wire),
        .tile_had_nan(sa_tile_had_nan_wire),
        .tile_had_inf(sa_tile_had_inf_wire)
    );

    assign ram_address = current_ram_addr_reg;
    assign ram_write_data = ram_write_data_reg;
    assign ram_cs = ram_cs_reg;
    assign ram_web = ram_web_reg;
    assign computation_done = computation_done_pulse_reg;
    integer r_disp_a_gen, c_disp_a_gen;
    integer r_disp_a, r_disp_b;
    integer r_disp_b_gen, c_disp_b_gen;
    integer conv_idx_a, conv_idx_b;
    integer r_debug_print;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state_reg <= S_IDLE;
            r_c_idx_reg <= {LOOP_COUNTER_WIDTH{1'b0}};
            c_c_idx_reg <= {LOOP_COUNTER_WIDTH{1'b0}};
            k_idx_reg <= {LOOP_COUNTER_WIDTH{1'b0}};
            current_ram_addr_reg <= {RAM_ADDR_WIDTH{1'b0}};
            ram_tile_word_count_reg <= {RAM_TILE_WORD_COUNT_WIDTH{1'b0}};
            ram_read_data_d1_reg <= {RAM_DATA_WIDTH{1'b0}};
            sa_feed_cycle_idx_reg <= {SA_FEED_CYCLE_IDX_WIDTH{1'b0}};
            c_store_row_read_idx_reg <= {C_STORE_ROW_IDX_WIDTH{1'b0}};
            c_store_word_in_row_idx_reg <= {C_STORE_WORD_IN_ROW_IDX_WIDTH{1'b0}};
            ram_cs_reg <= 1'b0;
            ram_web_reg <= 1'b1;
            ram_write_data_reg <= {RAM_DATA_WIDTH{1'b0}};
            sa_clear_accum_pulse_reg <= 1'b0;
            sa_cond_clear_sum_level_reg <= 1'b0;
            sa_start_new_pass_pulse_reg <= 1'b0;
            sa_activate_comp_reg <= 1'b0;
            sa_enable_output_reg <= 1'b0;
            sa_select_row_reg <= {SA_SELECT_ROW_WIDTH{1'b0}};
            computation_done_pulse_reg <= 1'b0;
            for (j_idx_loop = 0; j_idx_loop < TILE_AREA; j_idx_loop = j_idx_loop + 1) begin
                a_tile_buffer_bf16[j_idx_loop] <= {BF16_BITS{1'b0}};
                b_tile_buffer_bf16[j_idx_loop] <= {BF16_BITS{1'b0}};
            end
            // Initialize debug prev regs during reset
            prev_start_computation_dbg <= 1'b0;
            prev_current_state_reg_dbg <= S_IDLE;
            prev_sa_tile_all_pes_done_one_pass_wire_dbg <= 1'b0;
            prev_sa_tile_row_result_valid_wire_dbg <= 1'b0;
            prev_ram_read_data_d1_reg_dbg <= {RAM_DATA_WIDTH{1'bx}};
        end else begin
            current_state_reg <= next_state_reg;
            r_c_idx_reg <= r_c_idx_next;
            c_c_idx_reg <= c_c_idx_next;
            k_idx_reg <= k_idx_next;
            current_ram_addr_reg <= current_ram_addr_next;
            ram_tile_word_count_reg <= ram_tile_word_count_next;
            sa_feed_cycle_idx_reg <= sa_feed_cycle_idx_next;
            c_store_row_read_idx_reg <= c_store_row_read_idx_next;
            c_store_word_in_row_idx_reg <= c_store_word_in_row_idx_next;
            ram_cs_reg <= ram_cs_next;
            ram_web_reg <= ram_web_next;
            ram_write_data_reg <= ram_write_data_next;
            sa_clear_accum_pulse_reg <= sa_clear_accum_pulse_next;
            sa_cond_clear_sum_level_reg <= sa_cond_clear_sum_level_next;
            sa_start_new_pass_pulse_reg <= sa_start_new_pass_pulse_next;
            sa_activate_comp_reg <= sa_activate_comp_next;
            sa_enable_output_reg <= sa_enable_output_next;
            sa_select_row_reg <= sa_select_row_next;
            computation_done_pulse_reg <= computation_done_pulse_next;

            ram_read_data_d1_reg <= ram_read_data;


            // 处理 A Tile 加载和转换
            if (current_state_reg == S_LOAD_A_TILE_CONVERT_STORE) begin
                base_idx_in_buffer = ram_tile_word_count_reg * SINT8_PER_RAM_WORD;
                if (SINT8_PER_RAM_WORD > 0) begin
                    for (j_idx_loop = 0; j_idx_loop < SINT8_PER_RAM_WORD; j_idx_loop = j_idx_loop + 1) begin
                        if ((base_idx_in_buffer + j_idx_loop) < TILE_AREA) begin
                            a_tile_buffer_bf16[base_idx_in_buffer + j_idx_loop] <= bf16_outputs_from_converter[j_idx_loop];
                            // --- DEBUG PRINT for A_TILE_BUFFER element write ---
                            // if ((r_c_idx_reg == 0 && k_idx_reg == 0 && ram_tile_word_count_reg < 2) || // First A tile (A00), first few words
                            //     (r_c_idx_reg == 0 && k_idx_reg == 1 && ram_tile_word_count_reg < 2) ) begin // Second A tile (A01), first few words
                            //     $strobe("@%0t [ACCEL_A_BUF_WR] St:%s r_c=%d,k=%d word_idx=%d, elem_off=%d: SINT8[%d]=%d(%h) -> BF16=%h into a_tile_bf16[%d]",
                            //         $time, fsm_state_to_string(current_state_reg), r_c_idx_reg, k_idx_reg, ram_tile_word_count_reg, j_idx_loop,
                            //         j_idx_loop, sint8_inputs_from_ram[j_idx_loop], sint8_inputs_from_ram[j_idx_loop],
                            //         bf16_outputs_from_converter[j_idx_loop], base_idx_in_buffer + j_idx_loop);
                            // end
                        end
                    end
                end
                // if (WORDS_PER_SINT8_TILE > 0 && ram_tile_word_count_reg == WORDS_PER_SINT8_TILE - 1) begin // This is the last word being processed for the tile
                //     if ( (r_c_idx_reg == 0 && k_idx_reg == 0) || (r_c_idx_reg == 0 && k_idx_reg == 1) ) begin
                //          $strobe("@%0t [ACCEL_A_BUF_FULL] A_Tile_Buffer for r_c=%d, k=%d loaded. A[0]=%h, A[1]=%h, A[TD]=%h, A[TD+1]=%h", // TD = TILE_DIM_SYSTOLIC
                //             $time, r_c_idx_reg, k_idx_reg,
                //             (TILE_AREA > 0) ? a_tile_buffer_bf16[0] : 16'hXXXX,
                //             (TILE_AREA > 1) ? a_tile_buffer_bf16[1] : 16'hXXXX,
                //             (TILE_AREA > TILE_DIM_SYSTOLIC) ? a_tile_buffer_bf16[TILE_DIM_SYSTOLIC] : 16'hXXXX,
                //             (TILE_AREA > TILE_DIM_SYSTOLIC+1) ? a_tile_buffer_bf16[TILE_DIM_SYSTOLIC+1] : 16'hXXXX);
                //     end
                // end
            end
            // 处理 B Tile 加载和转换
            if (current_state_reg == S_LOAD_B_TILE_CONVERT_STORE) begin
                base_idx_in_buffer_b = ram_tile_word_count_reg * SINT8_PER_RAM_WORD;
                if (SINT8_PER_RAM_WORD > 0) begin
                    for (j_idx_loop = 0; j_idx_loop < SINT8_PER_RAM_WORD; j_idx_loop = j_idx_loop + 1) begin
                        if ((base_idx_in_buffer_b + j_idx_loop) < TILE_AREA) begin
                            b_tile_buffer_bf16[base_idx_in_buffer_b + j_idx_loop] <= bf16_outputs_from_converter[j_idx_loop];
                             // --- DEBUG PRINT for B_TILE_BUFFER element write ---
                            // if ((k_idx_reg == 0 && c_c_idx_reg == 0 && ram_tile_word_count_reg < 2) || // First B tile (B00)
                            //     (k_idx_reg == 0 && c_c_idx_reg == 1 && ram_tile_word_count_reg < 2) ) begin // Second B tile (B01)
                            //     $strobe("@%0t [ACCEL_B_BUF_WR] St:%s k=%d,c_c=%d word_idx=%d, elem_off=%d: SINT8[%d]=%d(%h) -> BF16=%h into b_tile_bf16[%d]",
                            //         $time, fsm_state_to_string(current_state_reg), k_idx_reg, c_c_idx_reg, ram_tile_word_count_reg, j_idx_loop,
                            //         j_idx_loop, sint8_inputs_from_ram[j_idx_loop], sint8_inputs_from_ram[j_idx_loop],
                            //         bf16_outputs_from_converter[j_idx_loop], base_idx_in_buffer_b + j_idx_loop);
                            // end
                        end
                    end
                end
                // if (WORDS_PER_SINT8_TILE > 0 && ram_tile_word_count_reg == WORDS_PER_SINT8_TILE - 1) begin
                //      if ((k_idx_reg == 0 && c_c_idx_reg == 0) || (k_idx_reg == 0 && c_c_idx_reg == 1) ) begin
                //         $strobe("@%0t [ACCEL_B_BUF_FULL] B_Tile_Buffer for k=%d, c_c=%d loaded. B[0]=%h, B[1]=%h, B[TD]=%h, B[TD+1]=%h",
                //             $time, k_idx_reg, c_c_idx_reg,
                //             (TILE_AREA > 0) ? b_tile_buffer_bf16[0] : 16'hXXXX,
                //             (TILE_AREA > 1) ? b_tile_buffer_bf16[1] : 16'hXXXX,
                //             (TILE_AREA > TILE_DIM_SYSTOLIC) ? b_tile_buffer_bf16[TILE_DIM_SYSTOLIC] : 16'hXXXX,
                //             (TILE_AREA > TILE_DIM_SYSTOLIC+1) ? b_tile_buffer_bf16[TILE_DIM_SYSTOLIC+1] : 16'hXXXX);
                //     end
                // end
            end

            // --- DEBUG PRINTS at end of cycle for general status ---
            if (rst_n) begin // Only print if not in reset
                // Print FSM state and key counters on change or frequently at start/specific conditions
                // if ( (start_computation && !prev_start_computation_dbg) || (current_state_reg != prev_current_state_reg_dbg) ||
                //      ($time < 200 * 10) || (computation_done_pulse_reg && !computation_done) || // Early in sim or near end
                //      (current_state_reg == S_INIT_K_LOOP_PE_SETUP) || // Key setup state
                //      (current_state_reg == S_K_LOOP_INCREMENT && k_idx_next == 0) || // End of K loop
                //      (current_state_reg == S_CTL_LOOP_INCREMENT) ) begin // End of C_C or R_C loop
                //     $strobe("@%0t [ACCEL_STATUS] CS:%s NS:%s | rc:%d,cc:%d,k:%d | ram_wc:%d,sa_fc:%d,c_sr:%d,c_swr:%d | SA_ACT:%b,SA_ENOUT:%b,SA_SEL:%d",
                //         $time, fsm_state_to_string(current_state_reg), fsm_state_to_string(next_state_reg),
                //         r_c_idx_reg, c_c_idx_reg, k_idx_reg,
                //         ram_tile_word_count_reg, sa_feed_cycle_idx_reg, c_store_row_read_idx_reg, c_store_word_in_row_idx_reg,
                //         sa_activate_comp_reg, sa_enable_output_reg, sa_select_row_reg);
                // end

                // RAM read data log (data available in ram_read_data_d1_reg for current cycle)
                // if ((current_state_reg == S_LOAD_A_TILE_CONVERT_STORE || current_state_reg == S_LOAD_B_TILE_CONVERT_STORE) &&
                //     (ram_read_data_d1_reg !== prev_ram_read_data_d1_reg_dbg || $time < 300*10) ) begin // Print on change or early
                //     $strobe("@%0t [ACCEL_RAM_RD_D1] St:%s AddrWas:%h, Data_d1_is_now: %h (for word_cnt %d of A/B tile r_c=%d,c_c=%d,k=%d)",
                //              $time, fsm_state_to_string(current_state_reg), current_ram_addr_reg, ram_read_data_d1_reg,
                //              ram_tile_word_count_reg, r_c_idx_reg, c_c_idx_reg, k_idx_reg);
                // end

                // if (sa_tile_all_pes_done_one_pass_wire != prev_sa_tile_all_pes_done_one_pass_wire_dbg && current_state_reg == S_SA_WAIT_DONE) begin
                //     $strobe("@%0t [ACCEL_SA_DONE] St:%s tile_all_pes_done changed to: %b (rc=%d,cc=%d,k=%d)",
                //             $time, fsm_state_to_string(current_state_reg), sa_tile_all_pes_done_one_pass_wire, r_c_idx_reg, c_c_idx_reg, k_idx_reg);
                // end
                // if (sa_tile_row_result_valid_wire != prev_sa_tile_row_result_valid_wire_dbg && sa_tile_row_result_valid_wire && current_state_reg == S_STORE_C_TILE_SA_READ_WAIT_VALID) begin
                //      $strobe("@%0t [ACCEL_SA_ROW_VLD] St:%s SA_Row_Valid for sel_row %d. C_Tile rc=%d,cc=%d. Data[0]=%h, Data[1]=%h",
                //         $time, fsm_state_to_string(current_state_reg), sa_select_row_reg, r_c_idx_reg, c_c_idx_reg,
                //         (SA_DATA_PATH_WIDTH>0)?sa_tile_row_result_out_wire[BF16_BITS-1:0]:16'hXXXX,
                //         (SA_DATA_PATH_WIDTH>=2*BF16_BITS)?sa_tile_row_result_out_wire[2*BF16_BITS-1:BF16_BITS]:16'hXXXX);
                // end

                // Update prev debug regs
                prev_start_computation_dbg <= start_computation;
                prev_current_state_reg_dbg <= current_state_reg;
                prev_sa_tile_all_pes_done_one_pass_wire_dbg <= sa_tile_all_pes_done_one_pass_wire;
                prev_sa_tile_row_result_valid_wire_dbg <= sa_tile_row_result_valid_wire;
                prev_ram_read_data_d1_reg_dbg <= ram_read_data_d1_reg;
            end

            // if (current_state_reg != S_IDLE) begin // Or just always print if needed
            //     $strobe("@%0t [ACCEL_CLK_END_STATUS] CS:%s | rc:%d,cc:%d,k:%d | sa_done:%b",
            //         $time, fsm_state_to_string(current_state_reg),
            //         r_c_idx_reg, c_c_idx_reg, k_idx_reg,
            //         sa_tile_all_pes_done_one_pass_wire);
            // end
            // if (current_state_reg != S_IDLE) begin
            //     $strobe("@%0t [ACCEL_SA_CTL_REGS] CS:%s | rc%d cc%d k%d | clear_pls:%b cond_clr:%b start_pass_pls:%b",
            //         $time, fsm_state_to_string(current_state_reg),
            //         r_c_idx_reg, c_c_idx_reg, k_idx_reg,
            //         sa_clear_accum_pulse_reg, sa_cond_clear_sum_level_reg, sa_start_new_pass_pulse_reg);
            // end
            // if (current_state_reg == S_STORE_C_TILE_RAM_WRITE) begin
            //     if ( (r_c_idx_reg == 0 && c_c_idx_reg == 0 && ram_tile_word_count_reg < 2) || // C00, first 2 words
            //          (r_c_idx_reg == 0 && c_c_idx_reg == 1 && ram_tile_word_count_reg < 2) ) begin // C01, first 2 words
            //         $strobe("@%0t [ACCEL_RAM_CTL_ACTUAL] St:%s | AddrReg:%h, DataReg:%h, CS_Reg:%b, WEB_Reg:%b (tile_wc:%d)",
            //             $time, fsm_state_to_string(current_state_reg),
            //             current_ram_addr_reg, ram_write_data_reg, 
            //             ram_cs_reg, ram_web_reg, ram_tile_word_count_reg);
            //     end
            // end
        end
    end

    // Combinational FSM logic
    always @(*) begin
        // Default assignments for next state regs (copy current state)
        next_state_reg = current_state_reg;
        r_c_idx_next = r_c_idx_reg;
        c_c_idx_next = c_c_idx_reg;
        k_idx_next = k_idx_reg;
        current_ram_addr_next = current_ram_addr_reg;
        ram_tile_word_count_next = ram_tile_word_count_reg;
        sa_feed_cycle_idx_next = sa_feed_cycle_idx_reg;
        c_store_row_read_idx_next = c_store_row_read_idx_reg;
        c_store_word_in_row_idx_next = c_store_word_in_row_idx_reg;

        // Default assignments for RAM control outputs
        ram_cs_next = 1'b0;
        ram_web_next = 1'b1; // Default to read
        ram_write_data_next = ram_write_data_reg;

        // Default assignments for SA control pulse signals & computation_done
        sa_clear_accum_pulse_next = 1'b0;
        sa_start_new_pass_pulse_next = 1'b0;
        computation_done_pulse_next = 1'b0;

        // Default assignments for SA control level signals - IMPORTANT: Default to OFF
        sa_cond_clear_sum_level_next = 1'b0;
        sa_activate_comp_next = 1'b0;      // Default to PEs OFF
        sa_enable_output_next = sa_enable_output_reg; // Keep holding for this one, or also default to 0 if safer
        sa_select_row_next = sa_select_row_reg;     // Keep holding for this one

        packed_c_word_comb = {RAM_DATA_WIDTH{1'b0}};


        case (current_state_reg)
            S_IDLE: begin
                // sa_activate_comp_next is already 0 by default
                sa_enable_output_next = 1'b0; // Ensure output is off
                if (start_computation) begin
                    next_state_reg = S_INIT_CTL_LOOP;
                end
            end
            S_INIT_CTL_LOOP: begin
                r_c_idx_next = {LOOP_COUNTER_WIDTH{1'b0}};
                c_c_idx_next = {LOOP_COUNTER_WIDTH{1'b0}};
                k_idx_next = {LOOP_COUNTER_WIDTH{1'b0}};
                // sa_activate_comp_next remains 0 (default)
                // sa_cond_clear_sum_level_next remains 0 (default)
                next_state_reg = S_INIT_K_LOOP_PE_SETUP;
            end
            S_INIT_K_LOOP_PE_SETUP: begin // State name "S_INIT_K_L_PE_SETUP" in your fsm_state_to_string
                sa_activate_comp_next = 1'b1;                   // Activate PEs for setup
                sa_cond_clear_sum_level_next = (k_idx_reg == 0);  // Set conditional clear level based on k
                sa_clear_accum_pulse_next = 1'b1;               // Assert pulse to clear PE accumulators/state
                sa_start_new_pass_pulse_next = 1'b1;            // Assert pulse to reset SA pass flags

                ram_tile_word_count_next = {RAM_TILE_WORD_COUNT_WIDTH{1'b0}};
                next_state_reg = S_LOAD_A_TILE_ADDR;
            end
            S_LOAD_A_TILE_ADDR: begin
                // Pulses (clear_accum, start_new_pass) end here due to default '0' at block start.
                // sa_cond_clear_sum_level_next is '0' due to default '0' at block start.
                sa_activate_comp_next = 1'b1; // KEEP PEs active for subsequent operations

                current_ram_addr_next = base_addr_a + (r_c_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + k_idx_reg) * WORDS_PER_SINT8_TILE;
                next_state_reg = S_LOAD_A_TILE_RAM_READ_REQ;
            end
            S_LOAD_A_TILE_RAM_READ_REQ: begin
                sa_activate_comp_next = 1'b1; // Keep PEs active
                if (WORDS_PER_SINT8_TILE == 0) begin
                     ram_tile_word_count_next = {RAM_TILE_WORD_COUNT_WIDTH{1'b0}};
                     next_state_reg = S_LOAD_B_TILE_ADDR;
                end else if (ram_tile_word_count_reg < WORDS_PER_SINT8_TILE) begin
                    ram_cs_next = 1'b1;
                    ram_web_next = 1'b1; // Read
                    current_ram_addr_next = (base_addr_a + (r_c_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + k_idx_reg) * WORDS_PER_SINT8_TILE) + ram_tile_word_count_reg;
                    next_state_reg = S_LOAD_A_TILE_RAM_READ_WAIT;
                    // if ((r_c_idx_reg==0 && k_idx_reg==0 && ram_tile_word_count_reg < 2) || (r_c_idx_reg==0 && k_idx_reg==1 && ram_tile_word_count_reg < 2) ) begin
                    //      $strobe("@%0t [ACCEL_RAM_A_RD_REQ] St:%s For Addr: %h (A_tile rc=%d,k=%d, word_cnt=%d)", $time,
                    //         fsm_state_to_string(current_state_reg), current_ram_addr_next,
                    //         r_c_idx_reg, k_idx_reg, ram_tile_word_count_reg);
                    // end
                end else begin
                    ram_tile_word_count_next = {RAM_TILE_WORD_COUNT_WIDTH{1'b0}};
                    next_state_reg = S_LOAD_B_TILE_ADDR;
                end
            end
            S_LOAD_A_TILE_RAM_READ_WAIT: begin
                sa_activate_comp_next = 1'b1; // Keep PEs active
                next_state_reg = S_LOAD_A_TILE_RAM_READ_WAIT2;
            end
            S_LOAD_A_TILE_RAM_READ_WAIT2: begin
                sa_activate_comp_next = 1'b1; // Keep PEs active
                next_state_reg = S_LOAD_A_TILE_CONVERT_STORE;
            end
            S_LOAD_A_TILE_CONVERT_STORE: begin
                sa_activate_comp_next = 1'b1; // Keep PEs active
                if (WORDS_PER_SINT8_TILE == 0) begin
                    ram_tile_word_count_next = {RAM_TILE_WORD_COUNT_WIDTH{1'b0}};
                    next_state_reg = S_LOAD_B_TILE_ADDR;
                end else begin
                    ram_tile_word_count_next = ram_tile_word_count_reg + 1;
                    if (ram_tile_word_count_next == WORDS_PER_SINT8_TILE) begin
                        ram_tile_word_count_next = {RAM_TILE_WORD_COUNT_WIDTH{1'b0}};
                        next_state_reg = S_LOAD_B_TILE_ADDR;
                    end else begin
                        next_state_reg = S_LOAD_A_TILE_RAM_READ_REQ;
                    end
                end
            end

            S_LOAD_B_TILE_ADDR: begin
                sa_activate_comp_next = 1'b1; // Keep PEs active
                current_ram_addr_next = base_addr_b + (k_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + c_c_idx_reg) * WORDS_PER_SINT8_TILE;
                next_state_reg = S_LOAD_B_TILE_RAM_READ_REQ;
            end
            S_LOAD_B_TILE_RAM_READ_REQ: begin
                sa_activate_comp_next = 1'b1; // Keep PEs active
                 if (WORDS_PER_SINT8_TILE == 0) begin
                     ram_tile_word_count_next = {RAM_TILE_WORD_COUNT_WIDTH{1'b0}};
                     next_state_reg = S_SA_FEED_SETUP;
                end else if (ram_tile_word_count_reg < WORDS_PER_SINT8_TILE) begin
                    ram_cs_next = 1'b1;
                    ram_web_next = 1'b1; // Read
                    current_ram_addr_next = (base_addr_b + (k_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + c_c_idx_reg) * WORDS_PER_SINT8_TILE) + ram_tile_word_count_reg;
                    next_state_reg = S_LOAD_B_TILE_RAM_READ_WAIT;
                    // if ((k_idx_reg==0 && c_c_idx_reg==0 && ram_tile_word_count_reg < 2) || (k_idx_reg==0 && c_c_idx_reg==1 && ram_tile_word_count_reg < 2)) begin
                    //      $strobe("@%0t [ACCEL_RAM_B_RD_REQ] St:%s For Addr: %h (B_tile k=%d,cc=%d, word_cnt=%d)", $time,
                    //         fsm_state_to_string(current_state_reg), current_ram_addr_next,
                    //         k_idx_reg, c_c_idx_reg, ram_tile_word_count_reg);
                    // end
                end else begin
                    ram_tile_word_count_next = {RAM_TILE_WORD_COUNT_WIDTH{1'b0}};
                    next_state_reg = S_SA_FEED_SETUP;
                end
            end
            S_LOAD_B_TILE_RAM_READ_WAIT: begin
                sa_activate_comp_next = 1'b1; // Keep PEs active
                next_state_reg = S_LOAD_B_TILE_RAM_READ_WAIT2;
            end
            S_LOAD_B_TILE_RAM_READ_WAIT2: begin
                sa_activate_comp_next = 1'b1; // Keep PEs active
                next_state_reg = S_LOAD_B_TILE_CONVERT_STORE;
            end
            S_LOAD_B_TILE_CONVERT_STORE: begin
                sa_activate_comp_next = 1'b1; // Keep PEs active
                if (WORDS_PER_SINT8_TILE == 0) begin
                    ram_tile_word_count_next = {RAM_TILE_WORD_COUNT_WIDTH{1'b0}};
                    next_state_reg = S_SA_FEED_SETUP;
                end else begin
                    ram_tile_word_count_next = ram_tile_word_count_reg + 1;
                    if (ram_tile_word_count_next == WORDS_PER_SINT8_TILE) begin
                        ram_tile_word_count_next = {RAM_TILE_WORD_COUNT_WIDTH{1'b0}};
                        next_state_reg = S_SA_FEED_SETUP;
                    end else begin
                        next_state_reg = S_LOAD_B_TILE_RAM_READ_REQ;
                    end
                end
            end

            S_SA_FEED_SETUP: begin
                sa_activate_comp_next = 1'b1; // PEs must be active for feeding
                sa_feed_cycle_idx_next = {SA_FEED_CYCLE_IDX_WIDTH{1'b0}};
                next_state_reg = S_SA_FEED_CYCLE;
            end
            S_SA_FEED_CYCLE: begin
                sa_activate_comp_next = 1'b1; // PEs must be active during feeding
                if (sa_feed_cycle_idx_reg == TILE_DIM_SYSTOLIC) begin
                    next_state_reg = S_SA_WAIT_DONE;
                end else begin
                    sa_feed_cycle_idx_next = sa_feed_cycle_idx_reg + 1;
                end
            end
            S_SA_WAIT_DONE: begin
                sa_activate_comp_next = 1'b1; // Keep PEs active while waiting for them to finish
                if (sa_tile_all_pes_done_one_pass_wire) begin
                    sa_activate_comp_next = 1'b0; // Deactivate PEs once this k-pass is done
                    next_state_reg = S_K_LOOP_INCREMENT;
                end
            end
            S_K_LOOP_INCREMENT: begin
                // sa_activate_comp_next is 0 if coming from S_SA_WAIT_DONE completion.
                // Or it will be set to 1 if going back to S_INIT_K_LOOP_PE_SETUP.
                // sa_cond_clear_sum_level_next is 0 by default.
                if (k_idx_reg == SAFE_TILES_PER_ROW_COL_GLOBAL - 1) begin // Done with all k for this C tile element
                    c_store_row_read_idx_next = {C_STORE_ROW_IDX_WIDTH{1'b0}};
                    ram_tile_word_count_next = {RAM_TILE_WORD_COUNT_WIDTH{1'b0}};
                    sa_activate_comp_next = 1'b0; // Ensure PEs are off before storing C
                    next_state_reg = S_STORE_C_TILE_ADDR;
                end else begin
                    k_idx_next = k_idx_reg + 1;
                    next_state_reg = S_INIT_K_LOOP_PE_SETUP; // This will set sa_activate_comp_next = 1'b1
                end
            end
            S_STORE_C_TILE_ADDR: begin
                sa_activate_comp_next = 1'b0;
                current_ram_addr_next = base_addr_c + (r_c_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + c_c_idx_reg) * WORDS_PER_BF16_TILE;
                next_state_reg = S_STORE_C_TILE_SA_READ_SETUP;
            end
            S_STORE_C_TILE_SA_READ_SETUP: begin
                sa_activate_comp_next = 1'b0;
                sa_enable_output_next = 1'b0; // Default for this path
                if (c_store_row_read_idx_reg < TILE_DIM_SYSTOLIC) begin
                    sa_enable_output_next = 1'b1;
                    sa_select_row_next = c_store_row_read_idx_reg[SA_SELECT_ROW_WIDTH-1:0];
                    next_state_reg = S_STORE_C_TILE_SA_READ_WAIT_VALID;
                end else begin
                    // sa_enable_output_next remains 0
                    next_state_reg = S_CTL_LOOP_INCREMENT;
                end
            end
            S_STORE_C_TILE_SA_READ_WAIT_VALID: begin
                sa_activate_comp_next = 1'b0;
                sa_enable_output_next = 1'b1; // Keep output enabled
                sa_select_row_next = sa_select_row_reg; // Keep row selected
                if (sa_tile_row_result_valid_wire) begin
                    c_store_word_in_row_idx_next = {C_STORE_WORD_IN_ROW_IDX_WIDTH{1'b0}};
                    next_state_reg = S_STORE_C_TILE_RAM_WRITE;
                end
            end
            S_STORE_C_TILE_RAM_WRITE: begin
                sa_activate_comp_next = 1'b0;
                sa_enable_output_next = 1'b1; // Keep output enabled
                sa_select_row_next = sa_select_row_reg; // Keep row selected
                // ... (rest of packing and RAM write logic) ...
                // (NO CHANGE TO THIS PART OF THE LOGIC FROM YOUR ORIGINAL)
                if (BF16_PER_RAM_WORD > 0) begin 
                    for (integer i = 0; i < BF16_PER_RAM_WORD; i = i + 1) begin
                        if ((c_store_word_in_row_idx_reg * BF16_PER_RAM_WORD + i) < TILE_DIM_SYSTOLIC) begin
                                packed_c_word_comb[(i*BF16_BITS) +: BF16_BITS] =
                                sa_tile_row_result_out_wire[( (c_store_word_in_row_idx_reg * BF16_PER_RAM_WORD + i) * BF16_BITS) +: BF16_BITS];
                        end else begin
                                packed_c_word_comb[(i*BF16_BITS) +: BF16_BITS] = {BF16_BITS{1'b0}}; 
                        end
                    end
                end
                ram_write_data_next = packed_c_word_comb;
                ram_cs_next = 1'b1;
                ram_web_next = 1'b0; 
                current_ram_addr_next = (base_addr_c + (r_c_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + c_c_idx_reg) * WORDS_PER_BF16_TILE) + ram_tile_word_count_reg; 
                ram_tile_word_count_next = ram_tile_word_count_reg + 1; 

                // if ( (r_c_idx_reg == 0 && c_c_idx_reg == 0 && ram_tile_word_count_reg < 8) || 
                //     (r_c_idx_reg == 0 && c_c_idx_reg == 1 && ram_tile_word_count_reg < 8) ) begin 
                //     $strobe("@%0t [ACCEL_RAM_C_WR_REQ] St:%s To Addr: %h (rc%d,cc%d), Data: %h (sel_row:%d, word_in_row:%d, tile_word_cnt:%d)", 
                //             $time, fsm_state_to_string(current_state_reg), current_ram_addr_next,
                //             r_c_idx_reg, c_c_idx_reg, ram_write_data_next,
                //             sa_select_row_reg, c_store_word_in_row_idx_reg, ram_tile_word_count_reg); 
                //     end

                if (NUM_PACKED_WORDS_PER_SA_ROW == 0) begin 
                     c_store_row_read_idx_next = c_store_row_read_idx_reg + 1;
                     next_state_reg = S_STORE_C_TILE_SA_READ_SETUP;
                end else if (c_store_word_in_row_idx_reg == NUM_PACKED_WORDS_PER_SA_ROW - 1) begin 
                    c_store_row_read_idx_next = c_store_row_read_idx_reg + 1; 
                    next_state_reg = S_STORE_C_TILE_SA_READ_SETUP;
                end else begin
                    c_store_word_in_row_idx_next = c_store_word_in_row_idx_reg + 1; 
                    next_state_reg = S_STORE_C_TILE_RAM_WRITE; 
                end
            end
            S_CTL_LOOP_INCREMENT: begin
                sa_activate_comp_next = 1'b0;
                sa_enable_output_next = 1'b0;
                if (c_c_idx_reg == SAFE_TILES_PER_ROW_COL_GLOBAL - 1) begin
                    c_c_idx_next = {LOOP_COUNTER_WIDTH{1'b0}};
                    if (r_c_idx_reg == SAFE_TILES_PER_ROW_COL_GLOBAL - 1) begin
                        next_state_reg = S_FINISH;
                    end else begin
                        r_c_idx_next = r_c_idx_reg + 1;
                        k_idx_next = {LOOP_COUNTER_WIDTH{1'b0}};
                        next_state_reg = S_INIT_K_LOOP_PE_SETUP; // This will set sa_activate_comp_next = 1'b1
                    end
                end else begin
                    c_c_idx_next = c_c_idx_reg + 1;
                    k_idx_next = {LOOP_COUNTER_WIDTH{1'b0}};
                    next_state_reg = S_INIT_K_LOOP_PE_SETUP; // This will set sa_activate_comp_next = 1'b1
                end
            end
            S_FINISH: begin
                sa_activate_comp_next = 1'b0;
                computation_done_pulse_next = 1'b1;
                next_state_reg = S_IDLE;
            end
            default: begin
                sa_activate_comp_next = 1'b0;
                next_state_reg = S_IDLE;
            end
        endcase
    end

    always @(*) begin
        integer i_extract; // Verilog-2001: integer 声明在块开始

        // 默认值，避免锁存器
        current_a_column_for_feed = {SA_DATA_PATH_WIDTH{1'b0}};
        current_b_row_for_feed  = {SA_DATA_PATH_WIDTH{1'b0}};

        if (current_state_reg == S_SA_FEED_CYCLE && sa_feed_cycle_idx_reg < TILE_DIM_SYSTOLIC) begin
            // 提取 A 的当前列 (由 sa_feed_cycle_idx_reg 指定列号)
            for (i_extract = 0; i_extract < TILE_DIM_SYSTOLIC; i_extract = i_extract + 1) begin
                if (TILE_AREA > 0) current_a_column_for_feed[(i_extract*BF16_BITS) +: BF16_BITS] =
                    a_tile_buffer_bf16[i_extract * TILE_DIM_SYSTOLIC + sa_feed_cycle_idx_reg];
            end

            // 提取 B 的当前行 (由 sa_feed_cycle_idx_reg 指定行号)
            for (i_extract = 0; i_extract < TILE_DIM_SYSTOLIC; i_extract = i_extract + 1) begin
                if (TILE_AREA > 0) current_b_row_for_feed[(i_extract*BF16_BITS) +: BF16_BITS] =
                    b_tile_buffer_bf16[sa_feed_cycle_idx_reg * TILE_DIM_SYSTOLIC + i_extract];
            end

            // --- DEBUG PRINT for SA Feed Data ---
            // if ( ( (r_c_idx_reg == 0 && c_c_idx_reg == 0 ) || // C00, for any k
            //     (r_c_idx_reg == 0 && c_c_idx_reg == 1 )    // C01, for any k
            //     ) && sa_feed_cycle_idx_reg < 3) begin // Print first few feed cycles for these C tiles
            //     $strobe("@%0t [ACCEL_SA_FEED] St:%s rc%d,cc%d,k%d | FeedCyc:%d, ValidIn:%b | A_in[0](col %d):%h B_in[0](row %d):%h",
            //         $time, fsm_state_to_string(current_state_reg), r_c_idx_reg, c_c_idx_reg, k_idx_reg,
            //         sa_feed_cycle_idx_reg, sa_array_data_valid_in_wire,
            //         sa_feed_cycle_idx_reg, (SA_DATA_PATH_WIDTH > 0) ? current_a_column_for_feed[BF16_BITS-1:0] : 16'hXXXX,
            //         sa_feed_cycle_idx_reg, (SA_DATA_PATH_WIDTH > 0) ? current_b_row_for_feed[BF16_BITS-1:0] : 16'hXXXX);
            // end
        end
    end

    assign sa_array_a_in_wire = (current_state_reg == S_SA_FEED_CYCLE && sa_feed_cycle_idx_reg < TILE_DIM_SYSTOLIC) ?
                                current_a_column_for_feed : // 直接使用提取出的列
                                {SAFE_SA_BUS_WIDTH{1'b0}};

    assign sa_array_b_in_wire = (current_state_reg == S_SA_FEED_CYCLE && sa_feed_cycle_idx_reg < TILE_DIM_SYSTOLIC) ?
                                current_b_row_for_feed :  // 直接使用提取出的行
                                {SAFE_SA_BUS_WIDTH{1'b0}};

    assign sa_array_data_valid_in_wire = (current_state_reg == S_SA_FEED_CYCLE) && (sa_feed_cycle_idx_reg < TILE_DIM_SYSTOLIC);

endmodule