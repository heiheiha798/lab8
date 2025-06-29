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
    parameter SRAM_C_WRITE_WIDTH = 256, 
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

    // --- NEW: Wires for Halfway-Done Propagation ---
    wire mid_column_done_signals [SIZE-1:0]; // Signal indicating row 'r' is done up to the midpoint

    // --- FSM State and Common Counters ---
    // typedef enum logic [1:0] {
    //     SA_FSM_IDLE,
    //     SA_FSM_COMPUTE_START_K,
    //     SA_FSM_COMPUTE_WAIT_K,
    //     SA_FSM_WRITE_BACK
    // } sa_fsm_state_e;
    // sa_fsm_state_e sa_fsm_state_q, sa_fsm_state_d;
    
    // reg [$clog2(K_ITER_COUNT)-1:0] k_iter_count_q, k_iter_count_d;
    // reg [$clog2(SIZE)-1:0] wb_row_count_q, wb_row_count_d;

    typedef enum logic [2:0] { // Increased width to hold more states
        SA_FSM_IDLE,
        SA_FSM_COMPUTE_START_K,
        SA_FSM_COMPUTE_WAIT_K,
        SA_FSM_WRITE_BACK_FIRST_HALF,  // NEW STATE
        SA_FSM_WRITE_BACK_SECOND_HALF  // NEW STATE
        // Note: The original SA_FSM_WRITE_BACK state is effectively replaced by these two
    } sa_fsm_state_e;
    sa_fsm_state_e sa_fsm_state_q, sa_fsm_state_d;
    
    reg [$clog2(K_ITER_COUNT)-1:0] k_iter_count_q, k_iter_count_d;
    reg [$clog2(SIZE)-1:0] wb_row_count_q, wb_row_count_d;

    // --- Pulse generation logic ---
    assign clear_for_new_tile_pulse = 
        ((sa_fsm_state_q == SA_FSM_IDLE) && (sa_fsm_state_d == SA_FSM_COMPUTE_START_K)) ||  // Case 1: Initial start-up from external signal
        ((sa_fsm_state_q == SA_FSM_WRITE_BACK_SECOND_HALF) && (sa_fsm_state_d == SA_FSM_COMPUTE_START_K)); // Case 2: Auto-reload after finishing a tile
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
            // *** NEW: Tap into the halfway point of the done chain ***
            // This signal becomes true when PE(r_gen_local, SIZE/2 - 1) has finished its pass.
            assign mid_column_done_signals[r_gen_local] = pe_row_propagate_done_chain[r_gen_local][SIZE/2];
        end
    endgenerate


    //======================================================================
    //== Parametric FSM and Write-Back Logic
    //======================================================================
    generate
        //----------------------------------------------------------------------
        // IMPLEMENTATION 1: WIDE/FAST PATH (e.g., 512-bit)
        //----------------------------------------------------------------------
        // if (SRAM_C_WRITE_WIDTH == ROW_WIDTH_BITS) begin: gen_wide_writeback

        //     // --- Main SA Control FSM (Sequential Part) ---
        //     always @(posedge clk or negedge rst_n) begin
        //         if (!rst_n) begin
        //             sa_fsm_state_q <= SA_FSM_IDLE;
        //             sa_busy <= 1'b0;
        //             tile_computation_done <= 1'b0;
        //             k_iter_count_q <= 0;
        //             wb_row_count_q <= 0;
        //         end else begin
        //             sa_fsm_state_q <= sa_fsm_state_d;
        //             sa_busy <= (sa_fsm_state_d != SA_FSM_IDLE);
        //             k_iter_count_q <= k_iter_count_d;
        //             wb_row_count_q <= wb_row_count_d;
                    
        //             // Generate single-cycle done pulse. This happens when the writeback FSM is in its last cycle.
        //             tile_computation_done <= (sa_fsm_state_q == SA_FSM_WRITE_BACK && wb_row_count_q == SIZE-1);
        //         end
        //     end

        //     // --- Main SA Control FSM (Combinational Part) ---
        //     always_comb begin // Changed to always_comb for better synthesis and checking
        //         // Default assignments to prevent latches
        //         sa_fsm_state_d = sa_fsm_state_q;
        //         k_iter_count_d = k_iter_count_q;
        //         wb_row_count_d = wb_row_count_q;

        //         sram_c_waddr_to_sram   = '0;
        //         sram_c_wdata_to_sram   = '0;
        //         sram_c_we_to_sram      = 1'b0;

        //         case (sa_fsm_state_q)
        //             SA_FSM_IDLE: begin
        //                 if (start_tile_computation) begin
        //                     sa_fsm_state_d = SA_FSM_COMPUTE_START_K;
        //                     k_iter_count_d = 0;
        //                 end
        //             end
                    
        //             SA_FSM_COMPUTE_START_K: begin
        //                 sa_fsm_state_d = SA_FSM_COMPUTE_WAIT_K;
        //             end
                    
        //             SA_FSM_COMPUTE_WAIT_K: begin
        //                 // *** CRITICAL LOGIC FIX ***
        //                 // We must differentiate between intermediate k-iterations and the final one.
                        
        //                 if (k_iter_count_q < K_ITER_COUNT - 1) begin
        //                     // --- Case 1: Intermediate k-iterations ---
        //                     // We MUST wait for the ENTIRE array to finish the current pass
        //                     // before starting the next one to avoid corrupting data.
        //                     if (all_rows_calculated) begin // Wait for the last row to finish
        //                         sa_fsm_state_d = SA_FSM_COMPUTE_START_K;
        //                         k_iter_count_d = k_iter_count_q + 1;
        //                     end
        //                     // else: stay in SA_FSM_COMPUTE_WAIT_K
        //                 end else begin 
        //                     // --- Case 2: Final k-iteration (k == K_ITER_COUNT - 1) ---
        //                     // Here, we can start writing back as soon as the first row's
        //                     // final result is ready. This is the optimization you wanted.
        //                     if (last_column_done_signals[0]) begin // First row is done, start writing
        //                         sa_fsm_state_d = SA_FSM_WRITE_BACK;
        //                         wb_row_count_d = 0; // Start writing from row 0
        //                     end
        //                     // else: stay in SA_FSM_COMPUTE_WAIT_K
        //                 end
        //             end
                    
        //             SA_FSM_WRITE_BACK: begin
        //                 sram_c_we_to_sram = 1'b1;
        //                 sram_c_waddr_to_sram = wb_row_count_q;
                        
        //                 // This combinatorial loop is fine for synthesis and simulation.
        //                 // It describes how to pack the data for a given row.
        //                 for (integer c_idx = 0; c_idx < SIZE; c_idx = c_idx + 1) begin
        //                     sram_c_wdata_to_sram[c_idx*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] = pe_result_out_internal[wb_row_count_q][c_idx];
        //                 end

        //                 if (wb_row_count_q == SIZE - 1) begin
        //                     // Finished writing the last row of the tile
        //                     sa_fsm_state_d = SA_FSM_IDLE;
        //                 end else begin
        //                     // Move to the next row to write.
        //                     // The writeback proceeds one row per clock cycle, perfectly pipelined
        //                     // with the PE results becoming available.
        //                     wb_row_count_d = wb_row_count_q + 1;
        //                 end
        //             end

        //             default: begin
        //                 sa_fsm_state_d = SA_FSM_IDLE;
        //             end

        //         endcase
        //     end
        // end
        //----------------------------------------------------------------------
        // IMPLEMENTATION 2: NARROW/PPA-OPTIMIZED PATH ("ZIG-ZAG" WRITEBACK)
        //----------------------------------------------------------------------
        // else 
        if (SRAM_C_WRITE_WIDTH == (ROW_WIDTH_BITS / 2)) begin: gen_narrow_writeback

            localparam HALF_SIZE = SIZE / 2;

            // FSM状态定义 - 保持不变，但逻辑用途有细微变化
            // SA_FSM_WRITE_BACK_FIRST_HALF: 写回所有行的前半部分
            // SA_FSM_WRITE_BACK_SECOND_HALF: 写回所有行的后半部分
            
            // --- NEW: A counter to track which half-column pass we are on ---
            reg wb_pass_q, wb_pass_d; // 0 for first half, 1 for second half

            // --- Main SA Control FSM (Sequential Part) ---
            always @(posedge clk or negedge rst_n) begin
                if (!rst_n) begin
                    sa_fsm_state_q <= SA_FSM_IDLE;
                    sa_busy <= 1'b0;
                    tile_computation_done <= 1'b0;
                    k_iter_count_q <= 0;
                    wb_row_count_q <= 0;
                    wb_pass_q <= 1'b0; // Start with the first pass (writing first halves)
                end else begin
                    sa_fsm_state_q <= sa_fsm_state_d;
                    sa_busy <= (sa_fsm_state_d != SA_FSM_IDLE);
                    k_iter_count_q <= k_iter_count_d;
                    wb_row_count_q <= wb_row_count_d;
                    wb_pass_q <= wb_pass_d;
                    
                    // Done pulse is generated when we are in the second pass and writing the last row.
                    tile_computation_done <= (sa_fsm_state_q == SA_FSM_WRITE_BACK_SECOND_HALF && wb_row_count_q == SIZE - 1);
                end
            end

            // --- Main SA Control FSM (Combinational Part) ---
            always_comb begin
                // Default assignments
                sa_fsm_state_d = sa_fsm_state_q;
                k_iter_count_d = k_iter_count_q;
                wb_row_count_d = wb_row_count_q;
                wb_pass_d = wb_pass_q;
                sram_c_waddr_to_sram = '0;
                sram_c_wdata_to_sram = '0;
                sram_c_we_to_sram    = 1'b0;

                case (sa_fsm_state_q)
                    SA_FSM_IDLE: begin
                        if (start_tile_computation) begin
                            sa_fsm_state_d = SA_FSM_COMPUTE_START_K;
                            k_iter_count_d = 0;
                            wb_pass_d = 0; // Reset for the new tile
                        end
                    end

                    SA_FSM_COMPUTE_START_K: begin
                        sa_fsm_state_d = SA_FSM_COMPUTE_WAIT_K;
                    end
                    
                    SA_FSM_COMPUTE_WAIT_K: begin
                        if (k_iter_count_q < K_ITER_COUNT - 1) begin
                            // Intermediate k-iterations: MUST wait for the whole array
                            if (all_rows_calculated) begin
                                sa_fsm_state_d = SA_FSM_COMPUTE_START_K;
                                k_iter_count_d = k_iter_count_q + 1;
                            end
                        end else begin 
                            // Final k-iteration: Start writing based on which pass we are in.
                            if (wb_pass_q == 0) begin // Pass 0: Waiting to start writing first halves
                                if (mid_column_done_signals[0]) begin // First row's first half is ready
                                    sa_fsm_state_d = SA_FSM_WRITE_BACK_FIRST_HALF;
                                    wb_row_count_d = 0; // Start writing from row 0
                                end
                            end else begin // Pass 1: Waiting to start writing second halves
                                if (last_column_done_signals[0]) begin // First row's second half is ready
                                    sa_fsm_state_d = SA_FSM_WRITE_BACK_SECOND_HALF;
                                    wb_row_count_d = 0; // Start writing from row 0 again
                                end
                            end
                        end
                    end
                    
                    SA_FSM_WRITE_BACK_FIRST_HALF: begin
                        // Writing the first half of all rows (from row 0 to SIZE-1)
                        sram_c_we_to_sram = 1'b1;
                        // Address for the first half of row 'r' is 'r*2'
                        sram_c_waddr_to_sram = {wb_row_count_q, 1'b0}; 
                        
                        // Pack the first half of the current row's results
                        for (integer c_idx = 0; c_idx < HALF_SIZE; c_idx = c_idx + 1) begin
                            sram_c_wdata_to_sram[c_idx*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] = pe_result_out_internal[wb_row_count_q][c_idx];
                        end

                        if (wb_row_count_q == SIZE - 1) begin
                            // Finished writing all first halves. Now, wait for the second halves to be ready.
                            wb_pass_d = 1; // Move to the second pass
                            sa_fsm_state_d = SA_FSM_COMPUTE_WAIT_K; // Go back to wait for the trigger for the second pass
                        end else begin
                            // Move to the next row's first half
                            wb_row_count_d = wb_row_count_q + 1;
                        end
                    end

                    SA_FSM_WRITE_BACK_SECOND_HALF: begin
                        // Writing the second half of all rows (from row 0 to SIZE-1)
                        sram_c_we_to_sram = 1'b1;
                        // Address for the second half of row 'r' is 'r*2 + 1'
                        sram_c_waddr_to_sram = {wb_row_count_q, 1'b1}; 

                        // Pack the second half of the current row's results
                        for (integer c_idx = 0; c_idx < HALF_SIZE; c_idx = c_idx + 1) begin
                            sram_c_wdata_to_sram[c_idx*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] = pe_result_out_internal[wb_row_count_q][c_idx + HALF_SIZE];
                        end

                        if (wb_row_count_q == SIZE - 1) begin
                            // Finished writing the whole tile
                            sa_fsm_state_d = SA_FSM_COMPUTE_START_K;
                            k_iter_count_d = 0;
                            wb_pass_d      = 0; 
                        end else begin
                            // Move to the next row's second half
                            wb_row_count_d = wb_row_count_q + 1;
                        end
                    end

                    default: sa_fsm_state_d = SA_FSM_IDLE;
                endcase
            end
        end
        else begin: gen_unsupported_wb_width
            // Good practice: add an error for unsupported configurations
            // synthesis translate_off
            always @(*) begin
                $error("Unsupported SRAM_C_WRITE_WIDTH. In this design, it must be either (SIZE*PE_ACCUM_DATA_WIDTH) or half of that.");
            end
            // synthesis translate_on
        end
    endgenerate

    always @(posedge clk) begin
        if (sa_busy) begin // 只在繁忙时打印，避免刷屏
            $display("%0t [SA_ENHANCED] FSM_State: %s, k_iter: %d, wb_row: %d, all_rows_calc: %b, mid_column_done_signals: %b, tile_done: %b", 
                     $time, sa_fsm_state_q.name(), k_iter_count_q, wb_row_count_q, all_rows_calculated, mid_column_done_signals[0], tile_computation_done);
        end
    end

endmodule
