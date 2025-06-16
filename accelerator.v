// accelerator.v
`timescale 1ns / 1ps

module accelerator #(
    parameter MATRIX_DIM_GLOBAL = 32,
    parameter TILE_DIM_SYSTOLIC = 16,
    parameter RAM_DATA_WIDTH    = 64,
    parameter SINT8_BITS        = 8,
    parameter PE_ACCUM_BITS     = 32,
    parameter LOGIC_ADDR_WIDTH  = 18,   // Logical address width for A, B, C spaces
    parameter RC_READ_LATENCY_CYCLES = 2 // Expected read latency from internal RAM Controller
) (
    input wire clk,
    input wire rst_n,

    input wire start_computation,
    output wire computation_done,

    // Base addresses are LOGICAL base addresses
    input wire [LOGIC_ADDR_WIDTH-1:0] base_addr_a,
    input wire [LOGIC_ADDR_WIDTH-1:0] base_addr_b,
    input wire [LOGIC_ADDR_WIDTH-1:0] base_addr_c

    // Removed direct rc_* ports from module interface
    // If needed for synthesis with an external ram_controller later, they would be here.
    // For now, ram_controller is internal.
);

    // --- Derived Parameters (mostly unchanged) ---
    localparam SINT8_PER_RAM_WORD = (SINT8_BITS == 0) ? 0 : RAM_DATA_WIDTH / SINT8_BITS;
    localparam SINT32_PER_RAM_WORD = (PE_ACCUM_BITS == 0) ? 0 : RAM_DATA_WIDTH / PE_ACCUM_BITS;
    localparam TILES_PER_ROW_COL_GLOBAL = (TILE_DIM_SYSTOLIC == 0) ? 0 : MATRIX_DIM_GLOBAL / TILE_DIM_SYSTOLIC;
    localparam SAFE_TILES_PER_ROW_COL_GLOBAL = (TILES_PER_ROW_COL_GLOBAL == 0) ? 1 : TILES_PER_ROW_COL_GLOBAL;
    localparam WORDS_PER_SINT8_TILE_CALC = (TILE_DIM_SYSTOLIC*TILE_DIM_SYSTOLIC*SINT8_BITS)/RAM_DATA_WIDTH;
    localparam WORDS_PER_SINT8_TILE = (WORDS_PER_SINT8_TILE_CALC == 0 && (TILE_DIM_SYSTOLIC*TILE_DIM_SYSTOLIC*SINT8_BITS) > 0) ? 1 : WORDS_PER_SINT8_TILE_CALC;
    localparam WORDS_PER_SINT32_TILE_CALC  = (TILE_DIM_SYSTOLIC*TILE_DIM_SYSTOLIC*PE_ACCUM_BITS)/RAM_DATA_WIDTH;
    localparam WORDS_PER_SINT32_TILE = (WORDS_PER_SINT32_TILE_CALC == 0 && (TILE_DIM_SYSTOLIC*TILE_DIM_SYSTOLIC*PE_ACCUM_BITS) > 0) ? 1 : WORDS_PER_SINT32_TILE_CALC;
    localparam TILE_AREA = TILE_DIM_SYSTOLIC * TILE_DIM_SYSTOLIC;
    localparam MAX_WORDS_PER_TILE_CALC = (WORDS_PER_SINT8_TILE > WORDS_PER_SINT32_TILE) ? WORDS_PER_SINT8_TILE : WORDS_PER_SINT32_TILE;
    localparam SAFE_MAX_WORDS_PER_TILE = (MAX_WORDS_PER_TILE_CALC == 0) ? 1 : MAX_WORDS_PER_TILE_CALC;
    localparam RAM_TILE_WORD_COUNT_WIDTH = (SAFE_MAX_WORDS_PER_TILE <= 1) ? 1 : $clog2(SAFE_MAX_WORDS_PER_TILE);
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

    // --- FSM States (Copied from previous version, ensure names match logic) ---
    localparam S_IDLE = 0;
    localparam S_INIT_CTL_LOOP = 1;
    localparam S_INIT_K_LOOP_PE_SETUP = 2;
    localparam S_LOAD_A_TILE_ADDR = 3;
    localparam S_LOAD_A_TILE_RC_REQ = 4;
    localparam S_LOAD_A_TILE_RC_WAIT_READY = 5;
    localparam S_LOAD_A_TILE_STORE_DATA = 6;
    localparam S_LOAD_B_TILE_ADDR = 7;
    localparam S_LOAD_B_TILE_RC_REQ = 8;
    localparam S_LOAD_B_TILE_RC_WAIT_READY = 9;
    localparam S_LOAD_B_TILE_STORE_DATA = 10;
    localparam S_SA_FEED_SETUP = 11;
    localparam S_SA_FEED_CYCLE = 12;
    localparam S_SA_WAIT_DONE = 13;
    localparam S_K_LOOP_INCREMENT = 14;
    localparam S_STORE_C_TILE_ADDR = 15;
    localparam S_STORE_C_TILE_SA_READ_SETUP = 16;
    localparam S_STORE_C_TILE_RC_WRITE_REQ = 17;
    localparam S_CTL_LOOP_INCREMENT = 18;
    localparam S_FINISH = 19;
    localparam S_STORE_C_TILE_SA_READ_WAIT_VALID = 20;
    localparam S_STORE_C_TILE_RC_WRITE_WAIT_READY = 21;

    reg [5:0] current_state_reg, next_state_reg;

    // Loop counters and FSM-driven address register
    reg [LOOP_COUNTER_WIDTH-1:0] r_c_idx_reg, r_c_idx_next;
    reg [LOOP_COUNTER_WIDTH-1:0] c_c_idx_reg, c_c_idx_next;
    reg [LOOP_COUNTER_WIDTH-1:0] k_idx_reg, k_idx_next;
    reg [LOGIC_ADDR_WIDTH-1:0] current_fsm_logic_addr_r, current_fsm_logic_addr_next; // FSM's notion of target address
    reg [RAM_TILE_WORD_COUNT_WIDTH-1:0] ram_tile_word_count_reg, ram_tile_word_count_next;
    reg [RAM_DATA_WIDTH-1:0] latched_rc_read_data_r; // To store data when internal_rc_ready_w is high

    // Tile buffers
    reg signed [SINT8_BITS-1:0] a_tile_buffer_sint8 [0:TILE_AREA-1];
    reg signed [SINT8_BITS-1:0] b_tile_buffer_sint8 [0:TILE_AREA-1];

    integer j_idx_loop;
    integer base_idx_in_buffer;
    integer base_idx_in_buffer_b;

    // SA control signals
    reg [SA_FEED_CYCLE_IDX_WIDTH-1:0]   sa_feed_cycle_idx_reg, sa_feed_cycle_idx_next;
    reg [C_STORE_ROW_IDX_WIDTH-1:0]     c_store_row_read_idx_reg, c_store_row_read_idx_next;
    reg [C_STORE_WORD_IN_ROW_IDX_WIDTH-1:0] c_store_word_in_row_idx_reg, c_store_word_in_row_idx_next;

    // Registers for driving internal RAM Controller's LOGICAL interface
    reg fsm_rc_cs_r, fsm_rc_cs_next;
    reg fsm_rc_we_r, fsm_rc_we_next; // 1 for write, 0 for read
    reg [RAM_DATA_WIDTH-1:0] fsm_rc_write_data_r, fsm_rc_write_data_next;

    // Internal wires FROM internal RAM Controller TO FSM
    wire [RAM_DATA_WIDTH-1:0]   internal_rc_read_data_w;
    wire                        internal_rc_ready_w;

    // SA control pulse/level signals
    reg sa_clear_accum_pulse_reg, sa_clear_accum_pulse_next;
    reg sa_cond_clear_sum_level_reg, sa_cond_clear_sum_level_next;
    reg sa_start_new_pass_pulse_reg, sa_start_new_pass_pulse_next;
    reg sa_activate_comp_reg, sa_activate_comp_next;
    reg sa_enable_output_reg, sa_enable_output_next;
    reg [SA_SELECT_ROW_WIDTH-1:0] sa_select_row_reg, sa_select_row_next;

    reg computation_done_pulse_reg, computation_done_pulse_next;
    reg [RAM_DATA_WIDTH-1:0] packed_c_word_comb;

    // Data for SA feed
    reg [SAFE_SA_INPUT_BUS_WIDTH-1:0] current_a_column_for_feed;
    reg [SAFE_SA_INPUT_BUS_WIDTH-1:0] current_b_row_for_feed;

    // Systolic Array Wires
    wire [SAFE_SA_INPUT_BUS_WIDTH-1:0] sa_array_a_in_wire_systolic;
    wire [SAFE_SA_INPUT_BUS_WIDTH-1:0] sa_array_b_in_wire_systolic;
    wire [SAFE_SA_OUTPUT_BUS_WIDTH-1:0] sa_tile_row_result_out_wire;
    wire sa_array_data_valid_in_wire_systolic;
    wire sa_tile_row_result_valid_wire;
    wire sa_tile_all_pes_done_one_pass_wire;

    // Instantiate internal RAM Controller
    ram_controller_behavioral #(
        .LOGIC_ADDR_WIDTH(LOGIC_ADDR_WIDTH),
        .DATA_WIDTH(RAM_DATA_WIDTH),
        .READ_LATENCY_CYCLES(RC_READ_LATENCY_CYCLES)
    ) u_ram_controller (
        .clk(clk),
        .rst_n(rst_n),
        .logic_addr_i(current_fsm_logic_addr_r),   // Driven by FSM's address register
        .write_data_i(fsm_rc_write_data_r),        // Driven by FSM's write data register
        .cs_i(fsm_rc_cs_r),                        // Driven by FSM's CS register
        .we_i(fsm_rc_we_r),                        // Driven by FSM's WE register
        .read_data_o(internal_rc_read_data_w),     // To FSM logic
        .ready_o(internal_rc_ready_w)              // To FSM logic
    );

    // Instantiate Systolic Array
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
        // .accelerator_is_computing(...) // Removed as discussed
        .array_a_data_valid_out(),
        .array_a_out(),
        .array_b_data_valid_out(),
        .array_b_out(),
        .tile_row_result_out(sa_tile_row_result_out_wire),
        .tile_row_result_valid(sa_tile_row_result_valid_wire),
        .tile_all_pes_done_one_pass(sa_tile_all_pes_done_one_pass_wire)
    );

    assign computation_done = computation_done_pulse_reg;

    function [16*8-1:0] fsm_state_to_string (input [5:0] state_in); // Copied, ensure up-to-date
        case(state_in)
            S_IDLE:                            fsm_state_to_string = "S_IDLE";
            S_INIT_CTL_LOOP:                   fsm_state_to_string = "S_INIT_CTL_LOOP";
            S_INIT_K_LOOP_PE_SETUP:            fsm_state_to_string = "S_INIT_K_SETUP";
            S_LOAD_A_TILE_ADDR:                fsm_state_to_string = "S_LOAD_A_ADDR";
            S_LOAD_A_TILE_RC_REQ:              fsm_state_to_string = "S_LOAD_A_RC_REQ";
            S_LOAD_A_TILE_RC_WAIT_READY:       fsm_state_to_string = "S_LOAD_A_RC_WAIT";
            S_LOAD_A_TILE_STORE_DATA:          fsm_state_to_string = "S_LOAD_A_STORE";
            S_LOAD_B_TILE_ADDR:                fsm_state_to_string = "S_LOAD_B_ADDR";
            S_LOAD_B_TILE_RC_REQ:              fsm_state_to_string = "S_LOAD_B_RC_REQ";
            S_LOAD_B_TILE_RC_WAIT_READY:       fsm_state_to_string = "S_LOAD_B_RC_WAIT";
            S_LOAD_B_TILE_STORE_DATA:          fsm_state_to_string = "S_LOAD_B_STORE";
            S_SA_FEED_SETUP:                   fsm_state_to_string = "S_SA_FEED_SETUP";
            S_SA_FEED_CYCLE:                   fsm_state_to_string = "S_SA_FEED_CYCLE";
            S_SA_WAIT_DONE:                    fsm_state_to_string = "S_SA_WAIT_DONE";
            S_K_LOOP_INCREMENT:                fsm_state_to_string = "S_K_LOOP_INC";
            S_STORE_C_TILE_ADDR:               fsm_state_to_string = "S_STORE_C_ADDR";
            S_STORE_C_TILE_SA_READ_SETUP:      fsm_state_to_string = "S_STORE_C_SA_RD_SETUP";
            S_STORE_C_TILE_SA_READ_WAIT_VALID: fsm_state_to_string = "S_STORE_C_SA_RD_WAITV";
            S_STORE_C_TILE_RC_WRITE_REQ:       fsm_state_to_string = "S_STORE_C_RC_WR_REQ";
            S_STORE_C_TILE_RC_WRITE_WAIT_READY:fsm_state_to_string = "S_STORE_C_RC_WR_WAIT";
            S_CTL_LOOP_INCREMENT:              fsm_state_to_string = "S_CTL_LOOP_INC";
            S_FINISH:                          fsm_state_to_string = "S_FINISH";
            default:                           fsm_state_to_string = "UNKNOWN_STATE";
        endcase
    endfunction

    // Clocked FSM and Data Path Logic
     always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // ... (复位逻辑保持不变) ...
            current_state_reg <= S_IDLE;
            r_c_idx_reg <= '0; c_c_idx_reg <= '0; k_idx_reg <= '0;
            current_fsm_logic_addr_r <= '0;
            ram_tile_word_count_reg <= '0;
            latched_rc_read_data_r <= '0;
            sa_feed_cycle_idx_reg <= '0;
            c_store_row_read_idx_reg <= '0;
            c_store_word_in_row_idx_reg <= '0;
            fsm_rc_cs_r <= 1'b0;
            fsm_rc_we_r <= 1'b0; // Default read
            fsm_rc_write_data_r <= '0;
            sa_clear_accum_pulse_reg <= 1'b0;
            sa_cond_clear_sum_level_reg <= 1'b0;
            sa_start_new_pass_pulse_reg <= 1'b0;
            sa_activate_comp_reg <= 1'b0;
            sa_enable_output_reg <= 1'b0;
            sa_select_row_reg <= '0;
            computation_done_pulse_reg <= 1'b0;
            for (j_idx_loop = 0; j_idx_loop < TILE_AREA; j_idx_loop = j_idx_loop + 1) begin
                a_tile_buffer_sint8[j_idx_loop] <= '0;
                b_tile_buffer_sint8[j_idx_loop] <= '0;
            end
        end else begin
            // Update registers based on next values from combinational block
            current_state_reg <= next_state_reg;
            r_c_idx_reg <= r_c_idx_next;
            c_c_idx_reg <= c_c_idx_next;
            k_idx_reg <= k_idx_next;
            current_fsm_logic_addr_r <= current_fsm_logic_addr_next;
            ram_tile_word_count_reg <= ram_tile_word_count_next;
            sa_feed_cycle_idx_reg <= sa_feed_cycle_idx_next;
            c_store_row_read_idx_reg <= c_store_row_read_idx_next;
            c_store_word_in_row_idx_reg <= c_store_word_in_row_idx_next;
            fsm_rc_cs_r <= fsm_rc_cs_next;
            fsm_rc_we_r <= fsm_rc_we_next;
            fsm_rc_write_data_r <= fsm_rc_write_data_next;
            sa_clear_accum_pulse_reg <= sa_clear_accum_pulse_next;
            sa_cond_clear_sum_level_reg <= sa_cond_clear_sum_level_next;
            sa_start_new_pass_pulse_reg <= sa_start_new_pass_pulse_next;
            sa_activate_comp_reg <= sa_activate_comp_next;
            sa_enable_output_reg <= sa_enable_output_next;
            sa_select_row_reg <= sa_select_row_next;
            computation_done_pulse_reg <= computation_done_pulse_next;

            if (internal_rc_ready_w && !fsm_rc_we_r) begin
                latched_rc_read_data_r <= internal_rc_read_data_w;
            end

            if (current_state_reg == S_LOAD_A_TILE_STORE_DATA) begin
                base_idx_in_buffer = ram_tile_word_count_reg * SINT8_PER_RAM_WORD;
                if (SINT8_PER_RAM_WORD > 0) begin
                    for (j_idx_loop = 0; j_idx_loop < SINT8_PER_RAM_WORD; j_idx_loop = j_idx_loop + 1) begin
                        if ((base_idx_in_buffer + j_idx_loop) < TILE_AREA) begin
                            a_tile_buffer_sint8[base_idx_in_buffer + j_idx_loop] <= latched_rc_read_data_r[(j_idx_loop*SINT8_BITS) +: SINT8_BITS];
                        end
                    end
                end
            end
            
            if (current_state_reg == S_LOAD_B_TILE_STORE_DATA) begin
                base_idx_in_buffer_b = ram_tile_word_count_reg * SINT8_PER_RAM_WORD;
                if (SINT8_PER_RAM_WORD > 0) begin
                    for (j_idx_loop = 0; j_idx_loop < SINT8_PER_RAM_WORD; j_idx_loop = j_idx_loop + 1) begin
                        if ((base_idx_in_buffer_b + j_idx_loop) < TILE_AREA) begin
                            b_tile_buffer_sint8[base_idx_in_buffer_b + j_idx_loop] <= latched_rc_read_data_r[(j_idx_loop*SINT8_BITS) +: SINT8_BITS];
                        end
                    end
                end
            end

            // --- GENERAL FSM STROBE ---
            // This strobe uses 'current_state_reg' (state at beginning of this cycle for comb logic)
            // and 'next_state_reg' (state calculated by comb logic to be next)
            // and 'fsm_rc_cs_r', 'fsm_rc_we_r' (values driving controller *this* cycle)
            // and 'internal_rc_ready_w' (value received from controller *this* cycle)
            // if (start_computation || (current_state_reg != S_IDLE && current_state_reg != S_FINISH && current_state_reg != S_INIT_CTL_LOOP) || $time < 500000 ) begin // Adjusted time limit
            //      $strobe("@%0t [ACCEL_FSM_STATUS] CurSt: %s (NextSt_calc: %s) | Loops(rc,cc,k):%2d,%2d,%2d | TileWdCnt:%2d | ToRC(Addr:0x%h CS:%b WE:%b WrData:0x%h) | FromRC(Rdy:%b RdData:0x%h) | SA_Feed:%2d SA_Done:%b CSt(R:%2d W:%2d)",
            //         $time,
            //         fsm_state_to_string(current_state_reg),
            //         fsm_state_to_string(next_state_reg),
            //         r_c_idx_reg, c_c_idx_reg, k_idx_reg,
            //         ram_tile_word_count_reg,
            //         current_fsm_logic_addr_r, // Address sent to RC this cycle
            //         fsm_rc_cs_r,              // CS sent to RC this cycle
            //         fsm_rc_we_r,              // WE sent to RC this cycle
            //         fsm_rc_write_data_r,      // Write Data sent to RC this cycle
            //         internal_rc_ready_w,      // Ready received from RC this cycle
            //         internal_rc_read_data_w,  // Read Data received from RC this cycle (valid if ready & read)
            //         sa_feed_cycle_idx_reg,
            //         sa_tile_all_pes_done_one_pass_wire,
            //         c_store_row_read_idx_reg, c_store_word_in_row_idx_reg
            //     );
            // end

            // // --- TARGETED WAIT STATE STROBE ---
            // if (current_state_reg == S_LOAD_A_TILE_RC_WAIT_READY ||
            //     current_state_reg == S_LOAD_B_TILE_RC_WAIT_READY ||
            //     current_state_reg == S_STORE_C_TILE_RC_WRITE_WAIT_READY ||
            //     current_state_reg == S_SA_WAIT_DONE ||
            //     current_state_reg == S_STORE_C_TILE_SA_READ_WAIT_VALID) begin
            //     $strobe("@%0t [ACCEL_WAITING] In State: %s | internal_rc_ready_w: %b | sa_tile_all_pes_done: %b | sa_tile_row_result_valid: %b",
            //         $time,
            //         fsm_state_to_string(current_state_reg),
            //         internal_rc_ready_w,
            //         sa_tile_all_pes_done_one_pass_wire,
            //         sa_tile_row_result_valid_wire
            //     );
            // end

            // // --- STROBE FOR A_BUF_LOADED ---
            // if (current_state_reg == S_LOAD_A_TILE_STORE_DATA && ram_tile_word_count_next == WORDS_PER_SINT8_TILE) begin
            //     // This condition means: we were in STORE_DATA for the *second to last* word of the tile,
            //     // and next cycle ram_tile_word_count_reg will be (WORDS_PER_SINT8_TILE - 1),
            //     // and ram_tile_word_count_next (which is ram_tile_word_count_reg+1) will become WORDS_PER_SINT8_TILE.
            //     // So, the buffer is fully loaded based on ram_tile_word_count_reg values *up to* WORDS_PER_SINT8_TILE-1.
            //     $strobe("@%0t [ACCEL_A_BUF_LOADED] rc,k=%d,%d. A_buf[0]=%d (0x%h), A_buf[1]=%d (0x%h), A_buf[TILE_DIM]=%d (0x%h)",
            //         $time, r_c_idx_reg, k_idx_reg,
            //         a_tile_buffer_sint8[0], a_tile_buffer_sint8[0],
            //         (TILE_AREA > 1) ? a_tile_buffer_sint8[1] : {{SINT8_BITS}{1'bx}}, (TILE_AREA > 1) ? a_tile_buffer_sint8[1] : {{SINT8_BITS}{1'bx}},
            //         (TILE_AREA > TILE_DIM_SYSTOLIC) ? a_tile_buffer_sint8[TILE_DIM_SYSTOLIC] : {{SINT8_BITS}{1'bx}}, (TILE_AREA > TILE_DIM_SYSTOLIC) ? a_tile_buffer_sint8[TILE_DIM_SYSTOLIC] : {{SINT8_BITS}{1'bx}}
            //     );
            // end

            // // --- STROBE FOR B_BUF_LOADED ---
            // if (current_state_reg == S_LOAD_B_TILE_STORE_DATA && ram_tile_word_count_next == WORDS_PER_SINT8_TILE) begin
            //      $strobe("@%0t [ACCEL_B_BUF_LOADED] k,cc=%d,%d. B_buf[0]=%d, B_buf[TILE_AREA-TILE_DIM]=%d (last_row_first_col), B_buf[TILE_AREA-1]=%d (last_elem)",
            //         $time, k_idx_reg, c_c_idx_reg,
            //         b_tile_buffer_sint8[0],
            //         // For B[15][0] in a 16x16 tile (TILE_AREA=256, TILE_DIM_SYSTOLIC=16): index is 15*16 + 0 = 240
            //         // TILE_AREA - TILE_DIM_SYSTOLIC = 256 - 16 = 240
            //         (TILE_AREA >= TILE_DIM_SYSTOLIC) ? b_tile_buffer_sint8[TILE_AREA - TILE_DIM_SYSTOLIC] : {{SINT8_BITS}{1'bx}},
            //         (TILE_AREA > 0) ? b_tile_buffer_sint8[TILE_AREA-1] : {{SINT8_BITS}{1'bx}}
            //     );
            // end

            // // --- DETAILED STROBE FOR SA_FEED focusing on B ---
            // if (current_state_reg == S_SA_FEED_CYCLE && sa_feed_cycle_idx_reg < TILE_DIM_SYSTOLIC) begin
            //     if (sa_array_data_valid_in_wire_systolic) begin // Only strobe if data is considered valid for SA
            //         $strobe("@%0t [ACCEL_SA_FEED_B_DETAIL] Cycle(B_row_idx) %2d (k=%d): B_row_fed[0]=%3d, B_row_fed[%2d]=%3d",
            //             $time, sa_feed_cycle_idx_reg, k_idx_reg,
            //             (TILE_DIM_SYSTOLIC > 0 && SINT8_BITS > 0) ? current_b_row_for_feed[SINT8_BITS-1:0] : {{SINT8_BITS}{1'bx}},
            //             TILE_DIM_SYSTOLIC-1,
            //             (TILE_DIM_SYSTOLIC > 0 && SINT8_BITS > 0) ? current_b_row_for_feed[(TILE_DIM_SYSTOLIC*SINT8_BITS)-1 -: SINT8_BITS] : {{SINT8_BITS}{1'bx}}
            //         );
            //     end
            // end

            // // --- STROBE FOR SA_OUT_VALID ---
            // if (current_state_reg == S_STORE_C_TILE_SA_READ_WAIT_VALID && sa_tile_row_result_valid_wire) begin
            //      $strobe("@%0t [ACCEL_SA_OUT_VALID] Row %2d (rc,cc=%d,%d): C_out[0]=%d (0x%h), C_out[1]=%d (0x%h)",
            //         $time, sa_select_row_reg,
            //         r_c_idx_reg, c_c_idx_reg,
            //         sa_tile_row_result_out_wire[PE_ACCUM_BITS-1:0],
            //         sa_tile_row_result_out_wire[PE_ACCUM_BITS-1:0],
            //         (TILE_DIM_SYSTOLIC > 1 && SAFE_SA_OUTPUT_BUS_WIDTH >= 2*PE_ACCUM_BITS) ? sa_tile_row_result_out_wire[2*PE_ACCUM_BITS-1:PE_ACCUM_BITS] : {{PE_ACCUM_BITS}{1'bx}},
            //         (TILE_DIM_SYSTOLIC > 1 && SAFE_SA_OUTPUT_BUS_WIDTH >= 2*PE_ACCUM_BITS) ? sa_tile_row_result_out_wire[2*PE_ACCUM_BITS-1:PE_ACCUM_BITS] : {{PE_ACCUM_BITS}{1'bx}}
            //     );
            // end

            // // --- STROBES FOR C WRITE ---
            // if (current_state_reg == S_STORE_C_TILE_RC_WRITE_REQ) begin
            //     $strobe("@%0t [ACCEL_C_WR_SETUP] In S_STORE_C_TILE_RC_WRITE_REQ. Next cycle will drive RC with:", $time);
            //     $strobe("                   Addr_next: 0x%h, Data_next: 0x%h (packed: 0x%h), CS_next: %b, WE_next: %b",
            //         current_fsm_logic_addr_next,
            //         fsm_rc_write_data_next,
            //         packed_c_word_comb,
            //         fsm_rc_cs_next,
            //         fsm_rc_we_next
            //     );
            // end

            // if (current_state_reg == S_STORE_C_TILE_RC_WRITE_WAIT_READY) begin
            //     $strobe("@%0t [ACCEL_C_WR_WAIT] In S_STORE_C_TILE_RC_WRITE_WAIT_READY. Sent to RC (current _r values):", $time);
            //     $strobe("                   Addr_sent: 0x%h, Data_sent: 0x%h, CS_sent: %b, WE_sent: %b | Waiting for RC_Ready: %b",
            //         current_fsm_logic_addr_r,
            //         fsm_rc_write_data_r,
            //         fsm_rc_cs_r,
            //         fsm_rc_we_r,
            //         internal_rc_ready_w
            //     );
            // end
        end
    end

    // Combinational FSM logic
    always @(*) begin
        next_state_reg = current_state_reg;
        r_c_idx_next = r_c_idx_reg; c_c_idx_next = c_c_idx_reg; k_idx_next = k_idx_reg;
        current_fsm_logic_addr_next = current_fsm_logic_addr_r;
        ram_tile_word_count_next = ram_tile_word_count_reg;
        sa_feed_cycle_idx_next = sa_feed_cycle_idx_reg;
        c_store_row_read_idx_next = c_store_row_read_idx_reg;
        c_store_word_in_row_idx_next = c_store_word_in_row_idx_reg;
        fsm_rc_cs_next = 1'b0;
        fsm_rc_we_next = 1'b0; // Default read
        fsm_rc_write_data_next = fsm_rc_write_data_r;
        sa_clear_accum_pulse_next = 1'b0;
        sa_start_new_pass_pulse_next = 1'b0;
        computation_done_pulse_next = 1'b0;
        sa_cond_clear_sum_level_next = 1'b0;
        sa_activate_comp_next = 1'b0;
        sa_enable_output_next = sa_enable_output_reg;
        sa_select_row_next = sa_select_row_reg;
        packed_c_word_comb = {RAM_DATA_WIDTH{1'b0}};

        case (current_state_reg)
            S_IDLE: begin
                sa_enable_output_next = 1'b0;
                if (start_computation) next_state_reg = S_INIT_CTL_LOOP;
            end
            S_INIT_CTL_LOOP: begin
                r_c_idx_next = '0; c_c_idx_next = '0; k_idx_next = '0;
                next_state_reg = S_INIT_K_LOOP_PE_SETUP;
            end
            S_INIT_K_LOOP_PE_SETUP: begin
                sa_activate_comp_next = 1'b1;
                sa_cond_clear_sum_level_next = (k_idx_reg == 0);
                sa_clear_accum_pulse_next = 1'b1;
                sa_start_new_pass_pulse_next = 1'b1;
                ram_tile_word_count_next = '0;
                next_state_reg = S_LOAD_A_TILE_ADDR;
            end
            S_LOAD_A_TILE_ADDR: begin
                sa_activate_comp_next = 1'b1;
                current_fsm_logic_addr_next = base_addr_a + (r_c_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + k_idx_reg) * WORDS_PER_SINT8_TILE;
                next_state_reg = S_LOAD_A_TILE_RC_REQ;
            end
            S_LOAD_A_TILE_RC_REQ: begin
                sa_activate_comp_next = 1'b1;
                if (WORDS_PER_SINT8_TILE == 0) begin
                     ram_tile_word_count_next = '0; next_state_reg = S_LOAD_B_TILE_ADDR;
                end else if (ram_tile_word_count_reg < WORDS_PER_SINT8_TILE) begin
                    fsm_rc_cs_next = 1'b1; fsm_rc_we_next = 1'b0; // Read
                    current_fsm_logic_addr_next = (base_addr_a + (r_c_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + k_idx_reg) * WORDS_PER_SINT8_TILE) + ram_tile_word_count_reg;
                    next_state_reg = S_LOAD_A_TILE_RC_WAIT_READY;
                end else begin
                    ram_tile_word_count_next = '0; next_state_reg = S_LOAD_B_TILE_ADDR;
                end
            end
            S_LOAD_A_TILE_RC_WAIT_READY: begin
                sa_activate_comp_next = 1'b1;
                fsm_rc_cs_next = 1'b0; // Stop asserting request once in wait (or keep asserted if controller needs)
                if (internal_rc_ready_w) begin // Data is ready from controller
                    next_state_reg = S_LOAD_A_TILE_STORE_DATA;
                end else begin
                    fsm_rc_cs_next = fsm_rc_cs_r; // Keep CS as it was (likely high from REQ state)
                                                  // Or, if controller latches request, CS can go low.
                                                  // Assuming controller latches on first cycle of REQ.
                    next_state_reg = S_LOAD_A_TILE_RC_WAIT_READY;
                end
            end
            S_LOAD_A_TILE_STORE_DATA: begin
                sa_activate_comp_next = 1'b1;
                ram_tile_word_count_next = ram_tile_word_count_reg + 1; // Data was for current count, now inc.
                if (ram_tile_word_count_next == WORDS_PER_SINT8_TILE) begin
                    ram_tile_word_count_next = '0; next_state_reg = S_LOAD_B_TILE_ADDR;
                end else begin
                    next_state_reg = S_LOAD_A_TILE_RC_REQ;
                end
            end
            // ... (Similar changes for B tile loading) ...
            S_LOAD_B_TILE_ADDR: begin
                sa_activate_comp_next = 1'b1;
                current_fsm_logic_addr_next = base_addr_b + (k_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + c_c_idx_reg) * WORDS_PER_SINT8_TILE;
                next_state_reg = S_LOAD_B_TILE_RC_REQ;
            end
            S_LOAD_B_TILE_RC_REQ: begin
                sa_activate_comp_next = 1'b1;
                if (WORDS_PER_SINT8_TILE == 0) begin
                     ram_tile_word_count_next = '0; next_state_reg = S_SA_FEED_SETUP;
                end else if (ram_tile_word_count_reg < WORDS_PER_SINT8_TILE) begin
                    fsm_rc_cs_next = 1'b1; fsm_rc_we_next = 1'b0; // Read
                    current_fsm_logic_addr_next = (base_addr_b + (k_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + c_c_idx_reg) * WORDS_PER_SINT8_TILE) + ram_tile_word_count_reg;
                    next_state_reg = S_LOAD_B_TILE_RC_WAIT_READY;
                end else begin
                    ram_tile_word_count_next = '0; next_state_reg = S_SA_FEED_SETUP;
                end
            end
            S_LOAD_B_TILE_RC_WAIT_READY: begin
                sa_activate_comp_next = 1'b1;
                fsm_rc_cs_next = 1'b0;
                if (internal_rc_ready_w) begin
                    next_state_reg = S_LOAD_B_TILE_STORE_DATA;
                end else begin
                    fsm_rc_cs_next = fsm_rc_cs_r;
                    next_state_reg = S_LOAD_B_TILE_RC_WAIT_READY;
                end
            end
            S_LOAD_B_TILE_STORE_DATA: begin
                sa_activate_comp_next = 1'b1;
                ram_tile_word_count_next = ram_tile_word_count_reg + 1;
                if (ram_tile_word_count_next == WORDS_PER_SINT8_TILE) begin
                    ram_tile_word_count_next = '0; next_state_reg = S_SA_FEED_SETUP;
                end else begin
                    next_state_reg = S_LOAD_B_TILE_RC_REQ;
                end
            end
            // ... (SA feed and wait done as before) ...
            S_SA_FEED_SETUP: begin sa_activate_comp_next = 1'b1; sa_feed_cycle_idx_next = '0; next_state_reg = S_SA_FEED_CYCLE; end
            S_SA_FEED_CYCLE: begin sa_activate_comp_next = 1'b1; if (sa_feed_cycle_idx_reg == TILE_DIM_SYSTOLIC) next_state_reg = S_SA_WAIT_DONE; else sa_feed_cycle_idx_next = sa_feed_cycle_idx_reg + 1; end
            S_SA_WAIT_DONE: begin sa_activate_comp_next = 1'b1; if (sa_tile_all_pes_done_one_pass_wire) begin sa_activate_comp_next = 1'b0; next_state_reg = S_K_LOOP_INCREMENT; end end
            S_K_LOOP_INCREMENT: begin if (k_idx_reg == SAFE_TILES_PER_ROW_COL_GLOBAL - 1) begin c_store_row_read_idx_next = '0; ram_tile_word_count_next = '0; sa_activate_comp_next = 1'b0; next_state_reg = S_STORE_C_TILE_ADDR; end else begin k_idx_next = k_idx_reg + 1; next_state_reg = S_INIT_K_LOOP_PE_SETUP; end end
            S_STORE_C_TILE_ADDR: begin sa_activate_comp_next = 1'b0; current_fsm_logic_addr_next = base_addr_c + (r_c_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + c_c_idx_reg) * WORDS_PER_SINT32_TILE; next_state_reg = S_STORE_C_TILE_SA_READ_SETUP; end
            S_STORE_C_TILE_SA_READ_SETUP: begin sa_activate_comp_next = 1'b0; sa_enable_output_next = 1'b0; if (c_store_row_read_idx_reg < TILE_DIM_SYSTOLIC) begin sa_enable_output_next = 1'b1; sa_select_row_next = c_store_row_read_idx_reg[SA_SELECT_ROW_WIDTH-1:0]; next_state_reg = S_STORE_C_TILE_SA_READ_WAIT_VALID; end else begin next_state_reg = S_CTL_LOOP_INCREMENT; end end
            S_STORE_C_TILE_SA_READ_WAIT_VALID: begin sa_activate_comp_next = 1'b0; sa_enable_output_next = 1'b1; if (sa_tile_row_result_valid_wire) begin c_store_word_in_row_idx_next = '0; next_state_reg = S_STORE_C_TILE_RC_WRITE_REQ; end end
            S_STORE_C_TILE_RC_WRITE_REQ: begin
                sa_activate_comp_next = 1'b0; sa_enable_output_next = 1'b1;
                if (SINT32_PER_RAM_WORD > 0) begin integer i_pack; for (i_pack=0; i_pack<SINT32_PER_RAM_WORD; i_pack=i_pack+1) if((c_store_word_in_row_idx_reg * SINT32_PER_RAM_WORD + i_pack) < TILE_DIM_SYSTOLIC) packed_c_word_comb[(i_pack*PE_ACCUM_BITS)+:PE_ACCUM_BITS] = sa_tile_row_result_out_wire[((c_store_word_in_row_idx_reg*SINT32_PER_RAM_WORD+i_pack)*PE_ACCUM_BITS)+:PE_ACCUM_BITS]; else packed_c_word_comb[(i_pack*PE_ACCUM_BITS)+:PE_ACCUM_BITS] = '0; end
                fsm_rc_write_data_next = packed_c_word_comb;
                fsm_rc_cs_next = 1'b1; fsm_rc_we_next = 1'b1; // Write
                current_fsm_logic_addr_next = (base_addr_c + (r_c_idx_reg * SAFE_TILES_PER_ROW_COL_GLOBAL + c_c_idx_reg) * WORDS_PER_SINT32_TILE) + ram_tile_word_count_reg;
                next_state_reg = S_STORE_C_TILE_RC_WRITE_WAIT_READY;
            end
            S_STORE_C_TILE_RC_WRITE_WAIT_READY: begin
                sa_activate_comp_next = 1'b0; sa_enable_output_next = 1'b1;
                fsm_rc_cs_next = 1'b0;
                if (internal_rc_ready_w) begin // Write acknowledged by controller
                    sa_enable_output_next = 1'b0;
                    ram_tile_word_count_next = ram_tile_word_count_reg + 1;
                    if (NUM_PACKED_WORDS_PER_SA_ROW_C == 0) begin c_store_row_read_idx_next = c_store_row_read_idx_reg + 1; next_state_reg = S_STORE_C_TILE_SA_READ_SETUP; end
                    else if (c_store_word_in_row_idx_reg == NUM_PACKED_WORDS_PER_SA_ROW_C - 1) begin c_store_row_read_idx_next = c_store_row_read_idx_reg + 1; next_state_reg = S_STORE_C_TILE_SA_READ_SETUP; end
                    else begin c_store_word_in_row_idx_next = c_store_word_in_row_idx_reg + 1; next_state_reg = S_STORE_C_TILE_RC_WRITE_REQ; end
                end else begin
                    fsm_rc_cs_next = fsm_rc_cs_r;
                    next_state_reg = S_STORE_C_TILE_RC_WRITE_WAIT_READY;
                end
            end
            S_CTL_LOOP_INCREMENT: begin sa_activate_comp_next = 1'b0; sa_enable_output_next = 1'b0; if (c_c_idx_reg == SAFE_TILES_PER_ROW_COL_GLOBAL - 1) begin c_c_idx_next = '0; if (r_c_idx_reg == SAFE_TILES_PER_ROW_COL_GLOBAL - 1) next_state_reg = S_FINISH; else begin r_c_idx_next = r_c_idx_reg + 1; k_idx_next = '0; next_state_reg = S_INIT_K_LOOP_PE_SETUP; end end else begin c_c_idx_next = c_c_idx_reg + 1; k_idx_next = '0; next_state_reg = S_INIT_K_LOOP_PE_SETUP; end end
            S_FINISH: begin sa_activate_comp_next = 1'b0; computation_done_pulse_next = 1'b1; next_state_reg = S_IDLE; end
            default: begin sa_activate_comp_next = 1'b0; next_state_reg = S_IDLE; end
        endcase
    end

    // Combinational logic for SA feed (no changes needed here if buffers are SINT8)
    always @(*) begin
        integer i_extract; current_a_column_for_feed = {SAFE_SA_INPUT_BUS_WIDTH{1'b0}}; current_b_row_for_feed  = {SAFE_SA_INPUT_BUS_WIDTH{1'b0}};
        if (current_state_reg == S_SA_FEED_CYCLE && sa_feed_cycle_idx_reg < TILE_DIM_SYSTOLIC) begin
            for (i_extract = 0; i_extract < TILE_DIM_SYSTOLIC; i_extract = i_extract + 1) if (TILE_AREA > 0) current_a_column_for_feed[(i_extract*SINT8_BITS)+:SINT8_BITS] = a_tile_buffer_sint8[i_extract*TILE_DIM_SYSTOLIC + sa_feed_cycle_idx_reg];
            for (i_extract = 0; i_extract < TILE_DIM_SYSTOLIC; i_extract = i_extract + 1) if (TILE_AREA > 0) current_b_row_for_feed[(i_extract*SINT8_BITS)+:SINT8_BITS] = b_tile_buffer_sint8[sa_feed_cycle_idx_reg*TILE_DIM_SYSTOLIC + i_extract];
        end
    end
    assign sa_array_a_in_wire_systolic = (current_state_reg == S_SA_FEED_CYCLE && sa_feed_cycle_idx_reg < TILE_DIM_SYSTOLIC) ? current_a_column_for_feed : {SAFE_SA_INPUT_BUS_WIDTH{1'b0}};
    assign sa_array_b_in_wire_systolic = (current_state_reg == S_SA_FEED_CYCLE && sa_feed_cycle_idx_reg < TILE_DIM_SYSTOLIC) ? current_b_row_for_feed :  {SAFE_SA_INPUT_BUS_WIDTH{1'b0}};
    assign sa_array_data_valid_in_wire_systolic = (current_state_reg == S_SA_FEED_CYCLE) && (sa_feed_cycle_idx_reg < TILE_DIM_SYSTOLIC);

endmodule