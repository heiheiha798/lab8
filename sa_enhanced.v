`timescale 1ns / 1ps

//
// Filename: sa_enhanced.v
// REVISED FOR PARAMETRIC WRITE-BACK:
// Description: This version of the Systolic Array (SA) includes a parametric
// write-back path to SRAM C, controlled by the SRAM_C_WRITE_WIDTH parameter.
// It uses a 'generate' block to instantiate one of two hardware implementations:
// 1. A wide-bus, single-cycle-per-row write-back for high performance.
// 2. A narrow-bus, multi-cycle-per-row write-back for PPA optimization.
// The module still manages the K-iteration loop internally.
//

module sa_enhanced #(
    parameter SIZE = 16,
    parameter K_ITER_COUNT = 16,
    // --- NEW PARAMETER to control SRAM C write path ---
    parameter SRAM_C_WRITE_WIDTH = 512, 
    parameter INPUT_DATA_WIDTH = 8,
    parameter PE_ACCUM_DATA_WIDTH = 32
)(
    // --- Clock and Reset ---
    input wire clk,
    input wire rst_n,

    // --- Control from Compute Controller ---
    input wire start_tile_computation,
    input wire activate_pe_computation,

    // --- Data Input from Formatter/TB ---
    input wire [SIZE*INPUT_DATA_WIDTH-1:0] array_a_in,
    input wire [SIZE*INPUT_DATA_WIDTH-1:0] array_b_in,
    input wire [SIZE-1:0] array_a_valid_in_indywidual,
    input wire [SIZE-1:0] array_b_valid_in_indywidual,

    // --- Status to Compute Controller ---
    output reg tile_computation_done,
    output reg sa_busy,

    // --- SRAM C Interface (SA is master) ---
    // Port widths are now parametric based on SRAM_C_WRITE_WIDTH
    output reg [$clog2( (SIZE*SIZE*PE_ACCUM_DATA_WIDTH)/SRAM_C_WRITE_WIDTH )-1:0] sram_c_waddr_to_sram,
    output reg signed [SRAM_C_WRITE_WIDTH-1:0]                                   sram_c_wdata_to_sram,
    output reg                                                                   sram_c_we_to_sram
);
    // --- Local Parameters ---
    localparam ROW_WIDTH_BITS = SIZE * PE_ACCUM_DATA_WIDTH;

    // --- Internal Wires for PE Array (Unchanged) ---
    wire signed [INPUT_DATA_WIDTH-1:0]      a_data_wires [SIZE-1:0][SIZE:0];
    wire signed [INPUT_DATA_WIDTH-1:0]      b_data_wires [SIZE:0][SIZE-1:0];
    wire                                    a_valid_wires [SIZE-1:0][SIZE:0];
    wire                                    b_valid_wires [SIZE:0][SIZE-1:0];
    wire signed [PE_ACCUM_DATA_WIDTH-1:0]   pe_result_out_internal [SIZE-1:0][SIZE-1:0];
    wire                                    pe_result_valid_internal [SIZE-1:0][SIZE-1:0];

    // --- Internal Control Wires (Unchanged) ---
    wire clear_for_new_tile_pulse;
    wire start_systolic_pass_pulse;

    // --- Wires for Done Propagation (Unchanged) ---
    wire pe_row_propagate_done_chain [SIZE-1:0][SIZE:0];
    wire last_column_done_signals [SIZE-1:0];
    wire all_rows_calculated = last_column_done_signals[SIZE-1];

    // --- FSM State and Common Counters ---
    typedef enum logic [1:0] {
        SA_FSM_IDLE,
        SA_FSM_COMPUTE_START_K,
        SA_FSM_COMPUTE_WAIT_K,
        SA_FSM_WRITE_BACK
    } sa_fsm_state_e;
    sa_fsm_state_e sa_fsm_state_q, sa_fsm_state_d;
    
    reg [$clog2(K_ITER_COUNT)-1:0] k_iter_count_q, k_iter_count_d;
    reg [$clog2(SIZE)-1:0] wb_row_count_q, wb_row_count_d;

    // --- Pulse generation logic ---
    assign clear_for_new_tile_pulse = (sa_fsm_state_q == SA_FSM_IDLE) && (sa_fsm_state_d == SA_FSM_COMPUTE_START_K);
    // -- MODIFIED --
    // Changed from (sa_fsm_state_d == SA_FSM_COMPUTE_WAIT_K) to fix deadlock.
    // This now generates a pulse when the FSM is in the START_K state for one cycle.
    assign start_systolic_pass_pulse = (sa_fsm_state_q == SA_FSM_COMPUTE_START_K);

    //===============================================================
    //== PE Array Instantiation and Boundary Connections (Unchanged)
    //===============================================================
    genvar r_gen_local, c_gen_local;
    generate
        for (r_gen_local = 0; r_gen_local < SIZE; r_gen_local = r_gen_local + 1) begin : connect_a_to_pe_boundary
            assign a_data_wires[r_gen_local][0] = array_a_in[r_gen_local*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
            assign a_valid_wires[r_gen_local][0] = array_a_valid_in_indywidual[r_gen_local];
        end
        for (c_gen_local = 0; c_gen_local < SIZE; c_gen_local = c_gen_local + 1) begin : connect_b_to_pe_boundary
            assign b_data_wires[0][c_gen_local] = array_b_in[c_gen_local*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
            assign b_valid_wires[0][c_gen_local] = array_b_valid_in_indywidual[c_gen_local];
        end
    endgenerate

    generate
        for (r_gen_local = 0; r_gen_local < SIZE; r_gen_local = r_gen_local + 1) begin : pe_row_gen
            assign pe_row_propagate_done_chain[r_gen_local][0] = 1'b1;

            for (c_gen_local = 0; c_gen_local < SIZE; c_gen_local = c_gen_local + 1) begin : pe_col_gen
                pe #(
                    .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH),
                    .ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH),
                    .MAC_COUNT_TARGET(SIZE),
                    .ROW_IDX(r_gen_local),
                    .COL_IDX(c_gen_local)
                ) u_pe_inst (
                    .clk(clk), .rst_n(rst_n), .enable(activate_pe_computation),
                    .clear_for_new_tile(clear_for_new_tile_pulse),
                    .start_new_systolic_pass(start_systolic_pass_pulse),
                    .a_valid_in(a_valid_wires[r_gen_local][c_gen_local]), .a_data_in(a_data_wires[r_gen_local][c_gen_local]),
                    .a_valid_out(a_valid_wires[r_gen_local][c_gen_local+1]), .a_data_out(a_data_wires[r_gen_local][c_gen_local+1]),
                    .b_valid_in(b_valid_wires[r_gen_local][c_gen_local]), .b_data_in(b_data_wires[r_gen_local][c_gen_local]),
                    .b_valid_out(b_valid_wires[r_gen_local+1][c_gen_local]), .b_data_out(b_data_wires[r_gen_local+1][c_gen_local]),
                    .result_out(pe_result_out_internal[r_gen_local][c_gen_local]),
                    .result_valid(pe_result_valid_internal[r_gen_local][c_gen_local]),
                    .pe_row_propagate_done_in(pe_row_propagate_done_chain[r_gen_local][c_gen_local]),
                    .pe_row_propagate_done_out(pe_row_propagate_done_chain[r_gen_local][c_gen_local+1])
                );
            end
            assign last_column_done_signals[r_gen_local] = pe_row_propagate_done_chain[r_gen_local][SIZE];
        end
    endgenerate


    //======================================================================
    //== Parametric FSM and Write-Back Logic
    //======================================================================
    generate
        //----------------------------------------------------------------------
        // IMPLEMENTATION 1: WIDE/FAST PATH (e.g., 512-bit)
        //----------------------------------------------------------------------
        if (SRAM_C_WRITE_WIDTH == ROW_WIDTH_BITS) begin: gen_wide_writeback

            // --- Main SA Control FSM (Sequential Part) ---
            always @(posedge clk or negedge rst_n) begin
                if (!rst_n) begin
                    sa_fsm_state_q <= SA_FSM_IDLE;
                    sa_busy <= 1'b0;
                    tile_computation_done <= 1'b0;
                    k_iter_count_q <= 0;
                    wb_row_count_q <= 0;
                end else begin
                    sa_fsm_state_q <= sa_fsm_state_d;
                    sa_busy <= (sa_fsm_state_d != SA_FSM_IDLE);
                    k_iter_count_q <= k_iter_count_d;
                    wb_row_count_q <= wb_row_count_d;
                    
                    // Generate single-cycle done pulse for WIDE path
                    tile_computation_done <= (sa_fsm_state_q == SA_FSM_WRITE_BACK && wb_row_count_q == SIZE-1);
                end
            end

            // --- Main SA Control FSM (Combinational Part) ---
            always @(*) begin
                sa_fsm_state_d = sa_fsm_state_q;
                k_iter_count_d = k_iter_count_q;
                wb_row_count_d = wb_row_count_q;

                sram_c_waddr_to_sram   = 0;
                sram_c_wdata_to_sram   = 0;
                sram_c_we_to_sram      = 1'b0;

                case (sa_fsm_state_q)
                    SA_FSM_IDLE: if (start_tile_computation) begin sa_fsm_state_d = SA_FSM_COMPUTE_START_K; k_iter_count_d = 0; end
                    SA_FSM_COMPUTE_START_K: sa_fsm_state_d = SA_FSM_COMPUTE_WAIT_K;
                    SA_FSM_COMPUTE_WAIT_K: begin
                        if (all_rows_calculated) begin
                            if (k_iter_count_q == K_ITER_COUNT - 1) begin
                                sa_fsm_state_d = SA_FSM_WRITE_BACK; wb_row_count_d = 0;
                            end else begin
                                sa_fsm_state_d = SA_FSM_COMPUTE_START_K; k_iter_count_d = k_iter_count_q + 1;
                            end
                        end
                    end
                    SA_FSM_WRITE_BACK: begin
                        sram_c_we_to_sram = 1'b1;
                        sram_c_waddr_to_sram = wb_row_count_q;
                        
                        for (integer c_idx = 0; c_idx < SIZE; c_idx = c_idx + 1) begin
                            sram_c_wdata_to_sram[c_idx*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] = pe_result_out_internal[wb_row_count_q][c_idx];
                        end

                        if (wb_row_count_q == SIZE - 1) begin
                            sa_fsm_state_d = SA_FSM_IDLE;
                        end else begin
                            wb_row_count_d = wb_row_count_q + 1;
                        end
                    end
                endcase
            end
        end 
        //----------------------------------------------------------------------
        // IMPLEMENTATION 2: NARROW/EFFICIENT PATH (e.g., 64-bit)
        //----------------------------------------------------------------------
        else begin: gen_narrow_writeback

            localparam CHUNKS_PER_ROW = ROW_WIDTH_BITS / SRAM_C_WRITE_WIDTH;

            // NEW state for the narrow write-back path
            reg [$clog2(CHUNKS_PER_ROW)-1:0] wb_chunk_count_q, wb_chunk_count_d;
            reg signed [ROW_WIDTH_BITS-1:0] latched_pe_row_data_q; // Latch for the row being written in chunks

            // --- Main SA Control FSM (Sequential Part) ---
            always @(posedge clk or negedge rst_n) begin
                if (!rst_n) begin
                    sa_fsm_state_q <= SA_FSM_IDLE;
                    sa_busy <= 1'b0;
                    tile_computation_done <= 1'b0;
                    k_iter_count_q <= 0;
                    wb_row_count_q <= 0;
                    wb_chunk_count_q <= 0;
                    latched_pe_row_data_q <= 0;
                end else begin
                    sa_fsm_state_q <= sa_fsm_state_d;
                    sa_busy <= (sa_fsm_state_d != SA_FSM_IDLE);
                    k_iter_count_q <= k_iter_count_d;
                    wb_row_count_q <= wb_row_count_d;
                    wb_chunk_count_q <= wb_chunk_count_d;

                    // Latch the PE result row only at the beginning of writing its chunks
                    if ((sa_fsm_state_q == SA_FSM_COMPUTE_WAIT_K && sa_fsm_state_d == SA_FSM_WRITE_BACK) ||
                        (sa_fsm_state_q == SA_FSM_WRITE_BACK && wb_chunk_count_q == CHUNKS_PER_ROW-1 && wb_row_count_q != SIZE-1) ) begin
                        for (integer c_idx = 0; c_idx < SIZE; c_idx = c_idx + 1) begin
                            latched_pe_row_data_q[c_idx*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] <= pe_result_out_internal[wb_row_count_d][c_idx];
                        end
                    end
                    
                    // Generate single-cycle done pulse for NARROW path
                    tile_computation_done <= (sa_fsm_state_q == SA_FSM_WRITE_BACK && wb_row_count_q == SIZE-1 && wb_chunk_count_q == CHUNKS_PER_ROW-1);
                end
            end

            // --- Main SA Control FSM (Combinational Part) ---
            always @(*) begin
                sa_fsm_state_d = sa_fsm_state_q;
                k_iter_count_d = k_iter_count_q;
                wb_row_count_d = wb_row_count_q;
                wb_chunk_count_d = wb_chunk_count_q;

                sram_c_waddr_to_sram   = 0;
                sram_c_wdata_to_sram   = 0;
                sram_c_we_to_sram      = 1'b0;

                case (sa_fsm_state_q)
                    SA_FSM_IDLE: if (start_tile_computation) begin sa_fsm_state_d = SA_FSM_COMPUTE_START_K; k_iter_count_d = 0; end
                    SA_FSM_COMPUTE_START_K: sa_fsm_state_d = SA_FSM_COMPUTE_WAIT_K;
                    SA_FSM_COMPUTE_WAIT_K: begin
                        if (all_rows_calculated) begin
                            if (k_iter_count_q == K_ITER_COUNT - 1) begin
                                sa_fsm_state_d = SA_FSM_WRITE_BACK; wb_row_count_d = 0; wb_chunk_count_d = 0;
                            end else begin
                                sa_fsm_state_d = SA_FSM_COMPUTE_START_K; k_iter_count_d = k_iter_count_q + 1;
                            end
                        end
                    end
                    SA_FSM_WRITE_BACK: begin
                        sram_c_we_to_sram = 1'b1;
                        sram_c_waddr_to_sram = (wb_row_count_q * CHUNKS_PER_ROW) + wb_chunk_count_q;
                        sram_c_wdata_to_sram = latched_pe_row_data_q >> (wb_chunk_count_q * SRAM_C_WRITE_WIDTH);

                        if (wb_chunk_count_q == CHUNKS_PER_ROW - 1) begin // End of a row
                            wb_chunk_count_d = 0;
                            if (wb_row_count_q == SIZE - 1) begin // End of all rows
                                sa_fsm_state_d = SA_FSM_IDLE;
                            end else begin
                                wb_row_count_d = wb_row_count_q + 1; // Move to next row
                            end
                        end else begin
                            wb_chunk_count_d = wb_chunk_count_q + 1; // Move to next chunk
                        end
                    end
                endcase
            end
        end
    endgenerate

endmodule
