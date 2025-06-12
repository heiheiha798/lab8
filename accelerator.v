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
    localparam MATRIX_DIM        = 32; // Set to 16 for 16x16, or 32 for 32x32
    localparam TILE_DIM          = 32; // Set to 16 for 16x16, or 32 for 32x32
    localparam SYSTOLIC_SIZE     = TILE_DIM;
    localparam DATA_WIDTH        = 16;
    localparam BUFFER_DATA_WIDTH = TILE_DIM * DATA_WIDTH;
    localparam BUFFER_ADDR_WIDTH = $clog2(TILE_DIM);

    localparam SINT8_PER_MEM_WORD = 64 / 8;
    localparam CHUNK_DATA_WIDTH = SINT8_PER_MEM_WORD * DATA_WIDTH; // Width of one converted memory read (128 bits)
    localparam ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE = BUFFER_DATA_WIDTH / CHUNK_DATA_WIDTH;

    localparam SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM = (TILE_DIM * TILE_DIM) / SINT8_PER_MEM_WORD;
    localparam BF16_WORDS_PER_RESULT_ROW = TILE_DIM * DATA_WIDTH / 64;
    localparam BF16_RESULT_WORDS_PER_TILE = TILE_DIM * BF16_WORDS_PER_RESULT_ROW;

    localparam TILES_PER_ROW_COL = MATRIX_DIM / TILE_DIM;
    localparam K_SLICES_TO_FEED = TILE_DIM;

    localparam S_IDLE            = 4'd0;
    localparam S_LOAD_A_BUF      = 4'd1;
    localparam S_LOAD_B_BUF      = 4'd2;
    localparam S_COMPUTE_SA      = 4'd3;
    localparam S_READ_SA_RESULTS = 4'd4;
    localparam S_WRITE_EXT_MEM   = 4'd5;
    localparam S_DONE            = 4'd6;

    reg [3:0] state, next_state;

    reg [$clog2(SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM)-1:0] load_ext_mem_word_count;
    reg [$clog2(K_SLICES_TO_FEED)-1:0]                         k_wave_feed_count;
    reg                                                        all_k_waves_fed;

    reg [$clog2(TILE_DIM)-1:0]                                 sa_result_read_row_count;
    reg [$clog2(BF16_RESULT_WORDS_PER_TILE)-1:0]               store_ext_mem_word_count;

    wire [BUFFER_DATA_WIDTH-1:0] sa_tile_row_result_out_wire;
    wire                         sa_tile_row_result_valid_wire;
    wire                         sa_all_pes_done_wire;
    wire                         sa_array_data_valid_signal;

    reg [DATA_WIDTH-1:0] result_buffer [TILE_DIM-1:0][TILE_DIM-1:0];

    // --- MODIFIED BUFFER LOADING LOGIC (Pure Verilog) ---
    // Registers to store intermediate chunks. We need at most 3 for ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE = 4.
    // If ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE = 2, only collected_chunk_0_reg is effectively used (like original first_128bit_chunk_reg).
    // If ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE = 1, none are used.
    reg [CHUNK_DATA_WIDTH-1:0]  collected_chunk_0_reg; // Stores the first chunk (if N_chunks > 1)
    reg [CHUNK_DATA_WIDTH-1:0]  collected_chunk_1_reg; // Stores the second chunk (if N_chunks > 2)
    reg [CHUNK_DATA_WIDTH-1:0]  collected_chunk_2_reg; // Stores the third chunk (if N_chunks > 3)

    wire [BUFFER_DATA_WIDTH-1:0] data_to_load_ram_input;
    // --- END OF MODIFIED BUFFER LOADING LOGIC DECLARATIONS ---

    wire [BUFFER_DATA_WIDTH-1:0] buf_a_dout;
    wire [BUFFER_DATA_WIDTH-1:0] buf_b_dout;

    wire sa_clear_all_accumulators_signal;
    wire sa_activate_computation_signal;

    wire buf_a_load_we_signal, buf_b_load_we_signal;
    wire [BUFFER_ADDR_WIDTH-1:0] buf_a_load_addr, buf_b_load_addr;
    wire [BUFFER_ADDR_WIDTH-1:0] buf_a_read_addr;
    wire [BUFFER_ADDR_WIDTH-1:0] buf_b_read_addr;

    wire [BUFFER_ADDR_WIDTH-1:0] current_buffer_line_addr;
    assign current_buffer_line_addr = load_ext_mem_word_count / ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE;

    assign buf_a_load_addr = current_buffer_line_addr;
    assign buf_b_load_addr = current_buffer_line_addr;

    assign buf_a_read_addr = k_wave_feed_count;
    assign buf_b_read_addr = k_wave_feed_count;

    wire [$clog2(SYSTOLIC_SIZE)-1:0] sa_select_output_row_idx_signal;
    wire                             sa_enable_tile_row_output_signal;

    systolic_array #(
        .SIZE(SYSTOLIC_SIZE),
        .DATA_WIDTH(DATA_WIDTH)
    ) u_systolic_array (
        .clk(clk),
        .rst_n(~rst),
        .clear_all_pe_accumulators(sa_clear_all_accumulators_signal),
        .activate_pe_computation(sa_activate_computation_signal),
        .array_data_valid_in(sa_array_data_valid_signal),
        .array_a_in(buf_a_dout),
        .array_b_in(buf_b_dout),
        .array_a_data_valid_out(),
        .array_a_out(),
        .array_b_data_valid_out(),
        .array_b_out(),
        .select_output_row_idx(sa_select_output_row_idx_signal),
        .enable_tile_row_output(sa_enable_tile_row_output_signal),
        .tile_row_result_out(sa_tile_row_result_out_wire),
        .tile_row_result_valid(sa_tile_row_result_valid_wire),
        .tile_all_pes_done_one_pass(sa_all_pes_done_wire),
        .tile_had_nan(),
        .tile_had_inf(),
        .accelerator_is_computing(sa_activate_computation_signal)
    );

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
    wire [CHUNK_DATA_WIDTH-1:0] current_128bit_chunk_from_conversion;
    assign current_128bit_chunk_from_conversion =
                                     {bf16_converted_array[7], bf16_converted_array[6],
                                      bf16_converted_array[5], bf16_converted_array[4],
                                      bf16_converted_array[3], bf16_converted_array[2],
                                      bf16_converted_array[1], bf16_converted_array[0]};

    // --- MODIFIED CHUNK COLLECTION LOGIC ---
    always @(posedge clk) begin
        if (rst) begin
            collected_chunk_0_reg <= {CHUNK_DATA_WIDTH{1'b0}};
            collected_chunk_1_reg <= {CHUNK_DATA_WIDTH{1'b0}};
            collected_chunk_2_reg <= {CHUNK_DATA_WIDTH{1'b0}};
        end else if (mem_read_enb && (state == S_LOAD_A_BUF || state == S_LOAD_B_BUF)) begin
            // Calculate the index of the current chunk within the buffer line
            // Example: if ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE is 4,
            // load_ext_mem_word_count values 0, 1, 2, 3 correspond to chunks 0, 1, 2, 3 for the first line.
            // Chunk 0 maps to (load_ext_mem_word_count % 4) == 0
            // Chunk 1 maps to (load_ext_mem_word_count % 4) == 1
            // Chunk 2 maps to (load_ext_mem_word_count % 4) == 2
            // Chunk 3 (the current_128bit_chunk_from_conversion when assembling) maps to (load_ext_mem_word_count % 4) == 3
            
            // This logic assumes ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE can be 1, 2, or 4.
            // Extend if other values are possible.

            if (ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE > 1) begin // Only collect if more than one chunk per line
                if ((load_ext_mem_word_count % ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE) == 0) begin
                    collected_chunk_0_reg <= current_128bit_chunk_from_conversion;
                end
            end

            if (ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE > 2) begin // Only collect for chunk 1 if more than two chunks per line
                if ((load_ext_mem_word_count % ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE) == 1) begin
                    collected_chunk_1_reg <= current_128bit_chunk_from_conversion;
                end
            end
            
            if (ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE > 3) begin // Only collect for chunk 2 if more than three chunks per line
                 if ((load_ext_mem_word_count % ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE) == 2) begin
                    collected_chunk_2_reg <= current_128bit_chunk_from_conversion;
                end
            end
        end
    end

    // --- MODIFIED DATA ASSEMBLY FOR RAM INPUT ---
    assign data_to_load_ram_input =
        // Condition: Are we at the last chunk needed to complete a buffer line?
        (load_ext_mem_word_count % ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE - 1) ?
            // Yes, assemble the line based on how many chunks are expected.
            (
                (ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == 1) ? current_128bit_chunk_from_conversion : // Single chunk fills the line
                (ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == 2) ? {current_128bit_chunk_from_conversion, collected_chunk_0_reg} : // Two chunks
                (ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == 4) ? {current_128bit_chunk_from_conversion, collected_chunk_2_reg, collected_chunk_1_reg, collected_chunk_0_reg} : // Four chunks
                // Add case for ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == 3 if needed:
                // (ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == 3) ? {current_128bit_chunk_from_conversion, collected_chunk_1_reg, collected_chunk_0_reg} :
                {BUFFER_DATA_WIDTH{1'bX}} // Default/Error case for unhandled N_chunks
            )
            : {BUFFER_DATA_WIDTH{1'bX}}; // Not the last chunk, so output X (write enable will be low)
    // --- END OF MODIFIED DATA ASSEMBLY ---


    // State machine logic
    integer r_loop_idx_int2, c_loop_idx_int2; // For result_buffer reset
    always @(posedge clk) begin
        if (rst) begin
            state <= S_IDLE;
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

            case(state)
                S_IDLE: begin
                end
                S_LOAD_A_BUF: begin
                    if (mem_read_enb) begin
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
                           all_k_waves_fed <= 1'b1;
                        end
                    end
                end
                S_READ_SA_RESULTS: begin
                    if (sa_tile_row_result_valid_wire) begin
                        for (c_loop_idx_int2 = 0; c_loop_idx_int2 < TILE_DIM; c_loop_idx_int2 = c_loop_idx_int2 + 1) begin
                            result_buffer[sa_result_read_row_count][c_loop_idx_int2] <= sa_tile_row_result_out_wire[c_loop_idx_int2*DATA_WIDTH +: DATA_WIDTH];
                        end
                        if (sa_result_read_row_count < TILE_DIM - 1) begin
                           sa_result_read_row_count <= sa_result_read_row_count + 1;
                        end
                    end
                end
                S_WRITE_EXT_MEM: begin
                    if(res_write_enb) begin
                        store_ext_mem_word_count <= store_ext_mem_word_count + 1;
                    end
                end
                S_DONE: begin
                end
                default: begin
                end
            endcase

            if (next_state != state) begin
                if (next_state == S_LOAD_A_BUF || next_state == S_LOAD_B_BUF) load_ext_mem_word_count <= 0;
                if (next_state == S_COMPUTE_SA) begin
                     k_wave_feed_count <= 0;
                     all_k_waves_fed   <= 1'b0;
                end
                if (next_state == S_READ_SA_RESULTS) sa_result_read_row_count <= 0;
                if (next_state == S_WRITE_EXT_MEM) store_ext_mem_word_count <= 0;
            end
        end
    end

    // Next state logic
    always @(*) begin
        next_state = state;
        case(state)
            S_IDLE:
                if (comp_enb) begin
                    next_state = S_LOAD_A_BUF;
                end
            S_LOAD_A_BUF:
                if (load_ext_mem_word_count == SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM - 1 &&
                    mem_read_enb &&
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
                if (sa_all_pes_done_wire) begin
                     next_state = S_READ_SA_RESULTS;
                end
            S_READ_SA_RESULTS:
                if (sa_result_read_row_count == TILE_DIM - 1 && sa_tile_row_result_valid_wire) begin
                    next_state = S_WRITE_EXT_MEM;
                end
            S_WRITE_EXT_MEM:
                if (store_ext_mem_word_count == BF16_RESULT_WORDS_PER_TILE - 1 && res_write_enb) begin
                    next_state = S_DONE;
                end
            S_DONE:
                next_state = S_IDLE;
            default:
                next_state = S_IDLE;
        endcase
    end

    localparam A_MEM_BASE = 0;
    localparam B_MEM_BASE = SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM;

    assign mem_read_enb = (state == S_LOAD_A_BUF && load_ext_mem_word_count < SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM) ||
                          (state == S_LOAD_B_BUF && load_ext_mem_word_count < SINT8_TILE_WORDS_PER_TILE_DIM_X_TILE_DIM);

    assign mem_addr = (state == S_LOAD_A_BUF) ? (A_MEM_BASE + load_ext_mem_word_count) :
                      (state == S_LOAD_B_BUF)  ? (B_MEM_BASE + load_ext_mem_word_count) :
                      16'hxxxx;

    assign buf_a_load_we_signal = (state == S_LOAD_A_BUF) && mem_read_enb &&
                                  (load_ext_mem_word_count % ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE - 1);
    assign buf_b_load_we_signal = (state == S_LOAD_B_BUF) && mem_read_enb &&
                                  (load_ext_mem_word_count % ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE == ACTUAL_EXT_MEM_READS_PER_BUFFER_LINE - 1);

    assign sa_clear_all_accumulators_signal = (state == S_COMPUTE_SA) && (k_wave_feed_count == 0 && !all_k_waves_fed);
    assign sa_activate_computation_signal = (state == S_COMPUTE_SA);
    assign sa_array_data_valid_signal = (state == S_COMPUTE_SA) && !all_k_waves_fed;

    assign sa_select_output_row_idx_signal = sa_result_read_row_count;
    assign sa_enable_tile_row_output_signal = (state == S_READ_SA_RESULTS);

    reg [DATA_WIDTH-1:0] res_val_0_reg, res_val_1_reg, res_val_2_reg, res_val_3_reg;
    wire [$clog2(TILE_DIM)-1:0] res_buf_row_idx_wire;
    wire [$clog2(TILE_DIM)-1:0] res_buf_base_col_idx_wire;

    assign res_buf_row_idx_wire = store_ext_mem_word_count / BF16_WORDS_PER_RESULT_ROW;
    assign res_buf_base_col_idx_wire = (store_ext_mem_word_count % BF16_WORDS_PER_RESULT_ROW) * 4;

    always @(*) begin
        res_val_0_reg = {DATA_WIDTH{1'bX}};
        res_val_1_reg = {DATA_WIDTH{1'bX}};
        res_val_2_reg = {DATA_WIDTH{1'bX}};
        res_val_3_reg = {DATA_WIDTH{1'bX}};
        if (state == S_WRITE_EXT_MEM || next_state == S_WRITE_EXT_MEM) begin
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
    assign res_addr = store_ext_mem_word_count;

    assign current_state_out = state;
    assign busyb = (state != S_IDLE && state != S_DONE);
    assign done = (state == S_DONE);

endmodule