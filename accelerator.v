`timescale 1ns / 1ps

module sint8_to_bf16_converter (
    input  wire signed [7:0]  sint8_in,
    output wire        [15:0] bf16_out
);
    wire sign_bit;
    wire [6:0] abs_val_unsigned; // Represents absolute value from 0 to 127
    wire [2:0] msb_pos;          // Position of MSB (0 for 1, 1 for 2-3, ..., 6 for 64-127)
    wire [7:0] bf16_exp_biased;
    wire [6:0] bf16_frac_final;

    assign sign_bit = sint8_in[7];

    assign abs_val_unsigned = (sint8_in == 8'h80) ? 7'd127 : // Map SINT8 -128 to abs 127
                              (sint8_in[7]) ? (~sint8_in[6:0] + 1'b1) :
                                              sint8_in[6:0];

    assign msb_pos = (abs_val_unsigned == 7'b0)      ? 3'd0 :
                     (abs_val_unsigned[6]) ? 3'd6 :
                     (abs_val_unsigned[5]) ? 3'd5 :
                     (abs_val_unsigned[4]) ? 3'd4 :
                     (abs_val_unsigned[3]) ? 3'd3 :
                     (abs_val_unsigned[2]) ? 3'd2 :
                     (abs_val_unsigned[1]) ? 3'd1 :
                                             3'd0;

    assign bf16_exp_biased = (abs_val_unsigned == 7'b0) ? 8'h00 : (msb_pos + 127);

    wire [6:0] raw_frac_bits; // Intermediate wire for clarity
    assign raw_frac_bits = (abs_val_unsigned == 7'b0) ? 7'b0 :
                           (abs_val_unsigned & ((1 << msb_pos) - 1));

    assign bf16_frac_final = (abs_val_unsigned == 7'b0) ? 7'b0 :
                             (raw_frac_bits << (7 - msb_pos));

    // Assign final bfloat16 output
    assign bf16_out = (sint8_in == 8'b00000000) ? 16'h0000 :         // If SINT8 is exactly 0, BF16 is +0.0
                      (sint8_in == 8'h80)       ? 16'hC2FE :         // SINT8 -128 -> BF16 -127.0 (example mapping)
                                                  {sign_bit, bf16_exp_biased, bf16_frac_final};
endmodule

module accelerator (
    input wire                           clk,
    input wire                           rst,
    input wire                           comp_enb,
    output wire                          busyb,
    output wire                          done,
    output wire [15:0]                   mem_addr,
    input wire  [63:0]                   mem_data_in,
    output wire                          mem_read_enb,
    output wire [15:0]                   res_addr,
    output wire [63:0]                   res_data_out,
    output wire                          res_write_enb,
    output wire [3:0]                    current_state_out
);
    localparam MATRIX_DIM        = 16;
    localparam TILE_DIM          = 16;
    localparam SYSTOLIC_SIZE     = TILE_DIM;
    localparam DATA_WIDTH        = 16;
    localparam BUFFER_DATA_WIDTH = TILE_DIM * DATA_WIDTH; // 16*16 = 256 bits
    localparam BUFFER_ADDR_WIDTH = $clog2(TILE_DIM);    // $clog2(16) = 4

    localparam SINT8_PER_MEM_WORD = 64 / 8; // 8 sint8 values per 64-bit external memory word
    localparam SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM = (TILE_DIM * TILE_DIM) / SINT8_PER_MEM_WORD; // (16*16)/8 = 32 words for a 16x16 SINT8 tile
    localparam BF16_WORDS_PER_RESULT_ROW = TILE_DIM * DATA_WIDTH / 64; // (16*16)/64 = 4 (64-bit) words for one row of BF16 results
    localparam BF16_RESULT_WORDS_PER_TILE = TILE_DIM * BF16_WORDS_PER_RESULT_ROW; // 16 rows * 4 words/row = 64 words

    localparam TILES_PER_ROW_COL = MATRIX_DIM / TILE_DIM; // Currently 1
    localparam K_SLICES_TO_FEED = TILE_DIM; // Number of K slices (waves) to feed from buffers

    localparam S_IDLE            = 4'd0;
    localparam S_LOAD_A_BUF      = 4'd1;
    localparam S_LOAD_B_BUF      = 4'd2;
    localparam S_COMPUTE_SA      = 4'd3;
    localparam S_READ_SA_RESULTS = 4'd4;
    localparam S_WRITE_EXT_MEM   = 4'd5;
    localparam S_DONE            = 4'd6;

    reg [3:0] state, next_state;

    // Tile iterators (if you were doing multiple tiles, not used in single tile version)
    // localparam TILE_IDX_WIDTH_TMP = (TILES_PER_ROW_COL==0) ? 1 : $clog2(TILES_PER_ROW_COL);
    // localparam TILE_IDX_WIDTH = (TILE_IDX_WIDTH_TMP==0) ? 1 : TILE_IDX_WIDTH_TMP;
    // reg [TILE_IDX_WIDTH-1 : 0] current_i_tile_idx;
    // reg [TILE_IDX_WIDTH-1 : 0] current_j_tile_idx;
    // reg [TILE_IDX_WIDTH-1 : 0] current_k_tile_idx;

    reg [$clog2(SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM)-1:0] load_ext_mem_word_count;
    reg [$clog2(K_SLICES_TO_FEED)-1:0]                         k_wave_feed_count; // Counts how many K-slices have been fed
    reg                                                        all_k_waves_fed;   // Flag indicating all K-slices are fed

    reg [$clog2(TILE_DIM)-1:0]                                 sa_result_read_row_count;
    reg [$clog2(BF16_RESULT_WORDS_PER_TILE)-1:0]               store_ext_mem_word_count;

    // Systolic array interface wires
    wire [BUFFER_DATA_WIDTH-1:0] sa_tile_row_result_out_wire;
    wire                         sa_tile_row_result_valid_wire;
    wire                         sa_all_pes_done_wire; // From systolic array, indicates all PEs finished MAC_COUNT_TARGET ops
    wire                         sa_array_data_valid_signal; // To systolic array

    reg [DATA_WIDTH-1:0] result_buffer [TILE_DIM-1:0][TILE_DIM-1:0];

    // Buffer loading logic (mostly unchanged)
    reg [SINT8_PER_MEM_WORD*DATA_WIDTH-1:0]  first_128bit_chunk_reg;
    wire [BUFFER_DATA_WIDTH-1:0]             data_to_load_ram_input;

    wire [BUFFER_DATA_WIDTH-1:0] buf_a_dout;
    wire [BUFFER_DATA_WIDTH-1:0] buf_b_dout;

    // Control signals to Systolic Array
    wire sa_clear_all_accumulators_signal;
    wire sa_activate_computation_signal; // General enable for computation in SA

    // Buffer control signals (mostly unchanged)
    wire buf_a_load_we_signal, buf_b_load_we_signal;
    wire [BUFFER_ADDR_WIDTH-1:0] buf_a_load_addr, buf_b_load_addr;
    wire [BUFFER_ADDR_WIDTH-1:0] buf_a_read_addr;
    wire [BUFFER_ADDR_WIDTH-1:0] buf_b_read_addr;

    localparam ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE = BUFFER_DATA_WIDTH / (SINT8_PER_MEM_WORD * DATA_WIDTH);
    wire [BUFFER_ADDR_WIDTH-1:0] current_buffer_line_addr;
    assign current_buffer_line_addr = load_ext_mem_word_count / ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE;

    assign buf_a_load_addr = current_buffer_line_addr;
    assign buf_b_load_addr = current_buffer_line_addr;

    assign buf_a_read_addr = k_wave_feed_count; // RAM read address is the current K-slice index
    assign buf_b_read_addr = k_wave_feed_count;

    // Systolic array outputs (if needed by other parts of accelerator, not directly used here)
    // wire [BUFFER_DATA_WIDTH-1:0] sa_array_a_out_internal;
    // wire [BUFFER_DATA_WIDTH-1:0] sa_array_b_out_internal;
    // wire                             sa_array_a_data_valid_out_internal;
    // wire                             sa_array_b_data_valid_out_internal;


    wire [$clog2(SYSTOLIC_SIZE)-1:0] sa_select_output_row_idx_signal;
    wire                             sa_enable_tile_row_output_signal;

    systolic_array #(
        .SIZE(SYSTOLIC_SIZE),
        .DATA_WIDTH(DATA_WIDTH)
    ) u_systolic_array (
        .clk(clk),
        .rst_n(~rst),
        .clear_all_pe_accumulators(sa_clear_all_accumulators_signal),
        .activate_pe_computation(sa_activate_computation_signal), // General enable for SA computation phase
        .array_data_valid_in(sa_array_data_valid_signal),     // NEW: Valid for current A/B data from buffers

        .array_a_in(buf_a_dout),
        .array_b_in(buf_b_dout),

        .array_a_data_valid_out(), // sa_array_a_data_valid_out_internal (connect if used)
        .array_a_out(),            // sa_array_a_out_internal (connect if used)
        .array_b_data_valid_out(), // sa_array_b_data_valid_out_internal (connect if used)
        .array_b_out(),            // sa_array_b_out_internal (connect if used)

        .select_output_row_idx(sa_select_output_row_idx_signal),
        .enable_tile_row_output(sa_enable_tile_row_output_signal),
        .tile_row_result_out(sa_tile_row_result_out_wire),
        .tile_row_result_valid(sa_tile_row_result_valid_wire),
        .tile_all_pes_done_one_pass(sa_all_pes_done_wire), // SA signals when all its PEs are done
        .tile_had_nan(),
        .tile_had_inf(),
        .accelerator_is_computing(sa_activate_computation_signal) // SA can use this to know if it's part of an active computation
    );

    // RAM Buffers (unchanged)
    ram #( .DATA_WIDTH(BUFFER_DATA_WIDTH), .ADDR_WIDTH(BUFFER_ADDR_WIDTH) ) buffer_a (
        .clk(clk), .cs(1'b1), .web(~buf_a_load_we_signal),
        .address( (state == S_LOAD_A_BUF) ? buf_a_load_addr : buf_a_read_addr ),
        .d(data_to_load_ram_input), .q(buf_a_dout)
    );
    ram #( .DATA_WIDTH(BUFFER_DATA_WIDTH), .ADDR_WIDTH(BUFFER_ADDR_WIDTH) ) buffer_b (
        .clk(clk), .cs(1'b1), .web(~buf_b_load_we_signal),
        .address( (state == S_LOAD_B_BUF) ? buf_b_load_addr : buf_b_read_addr ),
        .d(data_to_load_ram_input), .q(buf_b_dout)
    );

    // SINT8 to BF16 conversion logic (unchanged)
    wire signed [7:0] sint8_unpacked_array [0:SINT8_PER_MEM_WORD-1];
    wire [15:0]       bf16_converted_array [0:SINT8_PER_MEM_WORD-1];
    genvar gv_i_conv_loop_disp2;
    generate
        for (gv_i_conv_loop_disp2 = 0; gv_i_conv_loop_disp2 < SINT8_PER_MEM_WORD; gv_i_conv_loop_disp2 = gv_i_conv_loop_disp2 + 1) begin : sint8_converters_gen_block_disp2
            assign sint8_unpacked_array[gv_i_conv_loop_disp2] = mem_data_in[gv_i_conv_loop_disp2*8 +: 8];
            sint8_to_bf16_converter conv_inst (
                .sint8_in(sint8_unpacked_array[gv_i_conv_loop_disp2]),
                .bf16_out(bf16_converted_array[gv_i_conv_loop_disp2])
            );
        end
    endgenerate
    wire [SINT8_PER_MEM_WORD*DATA_WIDTH-1:0] current_128bit_chunk_from_conversion;
    assign current_128bit_chunk_from_conversion =
                                     {bf16_converted_array[7], bf16_converted_array[6],
                                      bf16_converted_array[5], bf16_converted_array[4],
                                      bf16_converted_array[3], bf16_converted_array[2],
                                      bf16_converted_array[1], bf16_converted_array[0]};
    always @(posedge clk) begin // first_128bit_chunk_reg logic (unchanged)
        if (rst) begin
            first_128bit_chunk_reg <= {(SINT8_PER_MEM_WORD*DATA_WIDTH){1'b0}};
        end else if (mem_read_enb && (state == S_LOAD_A_BUF || state == S_LOAD_B_BUF) ) begin
            if (load_ext_mem_word_count % ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == 0) begin
                first_128bit_chunk_reg <= current_128bit_chunk_from_conversion;
            end
        end
    end
    assign data_to_load_ram_input = (load_ext_mem_word_count % ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE - 1) ?
                                   { current_128bit_chunk_from_conversion , first_128bit_chunk_reg }
                                   : {BUFFER_DATA_WIDTH{1'bX}}; // Or assign 0 or hold, X is fine for simulation if WE is low.

    // State machine logic
    integer r_loop_idx_int2, c_loop_idx_int2; // For result_buffer reset
    always @(posedge clk) begin
        if (rst) begin
            state <= S_IDLE;
            // current_i_tile_idx <= {TILE_IDX_WIDTH{1'b0}}; // Not used for single tile
            // current_j_tile_idx <= {TILE_IDX_WIDTH{1'b0}};
            // current_k_tile_idx <= {TILE_IDX_WIDTH{1'b0}};
            load_ext_mem_word_count <= 0;
            k_wave_feed_count <= 0;
            all_k_waves_fed <= 1'b0;
            sa_result_read_row_count <= 0;
            store_ext_mem_word_count <= 0;
            for (r_loop_idx_int2 = 0; r_loop_idx_int2 < TILE_DIM; r_loop_idx_int2 = r_loop_idx_int2 + 1) begin
                for (c_loop_idx_int2 = 0; c_loop_idx_int2 < TILE_DIM; c_loop_idx_int2 = c_loop_idx_int2 + 1) begin
                    result_buffer[r_loop_idx_int2][c_loop_idx_int2] <= {DATA_WIDTH{1'b0}};
                end
            end
        end else begin
            state <= next_state;

            // Update counters based on current state
            case(state)
                S_IDLE: begin
                    // No action
                end
                S_LOAD_A_BUF: begin
                    if (mem_read_enb) begin // mem_read_enb is asserted for one cycle per read
                        load_ext_mem_word_count <= load_ext_mem_word_count + 1;
                    end
                end
                S_LOAD_B_BUF: begin
                    if (mem_read_enb) begin
                        load_ext_mem_word_count <= load_ext_mem_word_count + 1;
                    end
                end
                S_COMPUTE_SA: begin
                    if (!all_k_waves_fed) begin
                        if (k_wave_feed_count < K_SLICES_TO_FEED - 1) begin
                           k_wave_feed_count <= k_wave_feed_count + 1;
                        end else begin
                           // k_wave_feed_count will stay at K_SLICES_TO_FEED - 1
                           all_k_waves_fed <= 1'b1;
                        end
                    end
                    // sa_all_pes_done_wire will trigger state transition
                end
                S_READ_SA_RESULTS: begin
                    // This logic assumes row data becomes valid and is read one row at a time.
                    // The sa_tile_row_result_valid_wire should pulse when a row is ready from SA.
                    if (sa_tile_row_result_valid_wire) begin // If selected row data is valid from SA
                        for (c_loop_idx_int2 = 0; c_loop_idx_int2 < TILE_DIM; c_loop_idx_int2 = c_loop_idx_int2 + 1) begin
                            result_buffer[sa_result_read_row_count][c_loop_idx_int2] <= sa_tile_row_result_out_wire[c_loop_idx_int2*DATA_WIDTH +: DATA_WIDTH];
                        end
                        if (sa_result_read_row_count < TILE_DIM - 1) begin
                           sa_result_read_row_count <= sa_result_read_row_count + 1;
                        end
                        // Else: last row read, wait for state transition condition
                    end
                end
                S_WRITE_EXT_MEM: begin
                    if(res_write_enb) begin // res_write_enb is asserted for one cycle per write
                        store_ext_mem_word_count <= store_ext_mem_word_count + 1;
                    end
                end
                S_DONE: begin
                    // No specific action
                end
                default: begin
                    // No action
                end
            endcase

            // Counter resets on state transition (to ensure they start fresh for the new state)
            if (next_state != state) begin
                if (next_state == S_LOAD_A_BUF || next_state == S_LOAD_B_BUF) load_ext_mem_word_count <= 0;
                if (next_state == S_COMPUTE_SA) begin
                     k_wave_feed_count <= 0; // Reset to feed from the first K-slice
                     all_k_waves_fed   <= 1'b0;
                end
                if (next_state == S_READ_SA_RESULTS) sa_result_read_row_count <= 0; // Reset to read from the first row
                if (next_state == S_WRITE_EXT_MEM) store_ext_mem_word_count <= 0; // Reset to write from the first result word
            end
        end
    end

    // Next state logic
    always @(*) begin
        next_state = state; // Default: stay in current state
        case(state)
            S_IDLE:
                if (comp_enb) begin
                    next_state = S_LOAD_A_BUF;
                end
            S_LOAD_A_BUF:
                // Transition when the last word for buffer A is being written
                // This means mem_read_enb is high for the last word, and it's the last part of a buffer line
                if (load_ext_mem_word_count == SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM - 1 &&
                    mem_read_enb && // ensure this is the cycle the read is active
                    (load_ext_mem_word_count % ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE - 1)) begin
                    next_state = S_LOAD_B_BUF;
                end
            S_LOAD_B_BUF:
                if (load_ext_mem_word_count == SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM - 1 &&
                    mem_read_enb &&
                    (load_ext_mem_word_count % ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE - 1)) begin
                    next_state = S_COMPUTE_SA;
                end
            S_COMPUTE_SA:
                // Transition when the systolic array signals all PEs have completed their MACs
                if (sa_all_pes_done_wire) begin // And all_k_waves_fed is also implicitly true by then
                     next_state = S_READ_SA_RESULTS;
                end
            S_READ_SA_RESULTS:
                // Transition when the last row has been read into the result_buffer
                // sa_tile_row_result_valid_wire pulses when the selected row is ready.
                if (sa_result_read_row_count == TILE_DIM - 1 && sa_tile_row_result_valid_wire) begin
                    next_state = S_WRITE_EXT_MEM;
                end
            S_WRITE_EXT_MEM:
                // Transition when the last word of the result tile has been written to external memory
                if (store_ext_mem_word_count == BF16_RESULT_WORDS_PER_TILE - 1 && res_write_enb) begin
                    next_state = S_DONE;
                end
            S_DONE:
                // Stay in DONE until comp_enb is low, then can go to IDLE (or auto-IDLE)
                // For simplicity, let's assume it goes to IDLE if comp_enb is low,
                // or a new comp_enb pulse will restart from IDLE.
                // If comp_enb is a pulse, this state will be very short.
                // If comp_enb is a level, then need to wait for it to go low.
                // Current logic: comp_enb starts from IDLE.
                next_state = S_IDLE; // Automatically go to IDLE after one cycle in DONE
            default:
                next_state = S_IDLE;
        endcase
    end

    // Memory and Buffer Control Signals
    localparam A_MEM_BASE = 0;
    localparam B_MEM_BASE = SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM; // Example base address for B

    // mem_read_enb should be active for one cycle when a read is initiated
    // The load_ext_mem_word_count increments *after* the read.
    assign mem_read_enb = (state == S_LOAD_A_BUF && load_ext_mem_word_count < SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM) ||
                          (state == S_LOAD_B_BUF && load_ext_mem_word_count < SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM);

    assign mem_addr = (state == S_LOAD_A_BUF) ? (A_MEM_BASE + load_ext_mem_word_count) :
                      (state == S_LOAD_B_BUF)  ? (B_MEM_BASE + load_ext_mem_word_count) :
                      16'hxxxx; // Or a default non-active address

    // Buffer write enables are active when the second chunk for a line is read from memory
    assign buf_a_load_we_signal = (state == S_LOAD_A_BUF) && mem_read_enb &&
                                  (load_ext_mem_word_count % ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE - 1);
    assign buf_b_load_we_signal = (state == S_LOAD_B_BUF) && mem_read_enb &&
                                  (load_ext_mem_word_count % ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE - 1);

    // Systolic Array Control Signals
    assign sa_clear_all_accumulators_signal = (state == S_COMPUTE_SA) && (k_wave_feed_count == 0 && !all_k_waves_fed); // Clear only at the very start of S_COMPUTE_SA
    assign sa_activate_computation_signal = (state == S_COMPUTE_SA); // SA is active throughout the S_COMPUTE_SA state
    assign sa_array_data_valid_signal = (state == S_COMPUTE_SA) && !all_k_waves_fed; // Data from buffers is valid only while feeding K-slices

    // Result Read Control from Systolic Array
    assign sa_select_output_row_idx_signal = sa_result_read_row_count;
    assign sa_enable_tile_row_output_signal = (state == S_READ_SA_RESULTS);

    // Result Write Logic (mostly unchanged)
    reg [DATA_WIDTH-1:0] res_val_0_reg, res_val_1_reg, res_val_2_reg, res_val_3_reg;
    wire [$clog2(TILE_DIM)-1:0] res_buf_row_idx_wire;
    wire [$clog2(TILE_DIM)-1:0] res_buf_base_col_idx_wire;

    assign res_buf_row_idx_wire = store_ext_mem_word_count / BF16_WORDS_PER_RESULT_ROW;
    assign res_buf_base_col_idx_wire = (store_ext_mem_word_count % BF16_WORDS_PER_RESULT_ROW) * 4;

    always @(*) begin // Combinational logic for res_data_out
        res_val_0_reg = {DATA_WIDTH{1'bX}};
        res_val_1_reg = {DATA_WIDTH{1'bX}};
        res_val_2_reg = {DATA_WIDTH{1'bX}};
        res_val_3_reg = {DATA_WIDTH{1'bX}};
        // Ensure we are in the correct state for reading from result_buffer
        if (state == S_WRITE_EXT_MEM || next_state == S_WRITE_EXT_MEM) begin // Check current or next state for safety during transition
            if (res_buf_row_idx_wire < TILE_DIM && (res_buf_base_col_idx_wire + 3) < TILE_DIM) begin
                res_val_0_reg = result_buffer[res_buf_row_idx_wire][res_buf_base_col_idx_wire + 0];
                res_val_1_reg = result_buffer[res_buf_row_idx_wire][res_buf_base_col_idx_wire + 1];
                res_val_2_reg = result_buffer[res_buf_row_idx_wire][res_buf_base_col_idx_wire + 2];
                res_val_3_reg = result_buffer[res_buf_row_idx_wire][res_buf_base_col_idx_wire + 3];
            end
        end
    end
    assign res_data_out = {res_val_3_reg, res_val_2_reg, res_val_1_reg, res_val_0_reg};

    assign res_write_enb = (state == S_WRITE_EXT_MEM && store_ext_mem_word_count < BF16_RESULT_WORDS_PER_TILE);
    assign res_addr = store_ext_mem_word_count; // Base address for result tile in external memory

    // Accelerator Status Outputs
    assign current_state_out = state;
    assign busyb = (state != S_IDLE && state != S_DONE);
    assign done = (state == S_DONE); // Pulse for one cycle when done

endmodule