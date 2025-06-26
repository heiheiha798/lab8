// sa_enhanced.v
// Description: Enhanced Systolic Array that integrates SRAM C accumulation.
//
`timescale 1ns / 1ps

module sa_enhanced #(
    parameter SIZE = 16,
    parameter INPUT_DATA_WIDTH = 8,
    parameter PE_ACCUM_DATA_WIDTH = 32,
    parameter ROW_WIDTH_BITS = SIZE * PE_ACCUM_DATA_WIDTH // Typically 16*32 = 512
)(
    // --- Clock and Reset ---
    input wire clk,
    input wire rst_n,

    // --- Control from Compute Controller ---
    input wire start_new_k_iteration,       // Starts a new K-iteration (calc + accum)
    input wire activate_pe_computation,    // Enables PE calculations during a K-iteration
    input wire k_tile_is_first,             // *** NEW ***: High if this is k=0 for a new C tile

    // --- Data Input from Formatter/TB ---
    input wire [SIZE*INPUT_DATA_WIDTH-1:0] array_a_in,
    input wire [SIZE*INPUT_DATA_WIDTH-1:0] array_b_in,
    input wire [SIZE-1:0] array_a_valid_in_indywidual, // 新增
    input wire [SIZE-1:0] array_b_valid_in_indywidual, // 新增

    // --- Status to Compute Controller ---
    output reg sa_k_iteration_accum_done,   // High for one cycle when a K-iter's accum is complete
    output reg sa_busy,                     // High when SA is busy with calculation or accumulation

    // --- SRAM C Port A Interface (SA is master) ---
    output reg [$clog2(SIZE)-1:0]           sram_c_raddr_A_to_sram,
    input wire [ROW_WIDTH_BITS-1:0]         sram_c_rdata_A_from_sram,
    output reg [$clog2(SIZE)-1:0]           sram_c_waddr_to_sram,
    output reg signed [ROW_WIDTH_BITS-1:0]  sram_c_wdata_to_sram,
    output reg                               sram_c_we_to_sram
);

    // --- Internal Wires for PE Array ---
    wire signed [INPUT_DATA_WIDTH-1:0]   a_data_wires [SIZE-1:0][SIZE:0];
    wire signed [INPUT_DATA_WIDTH-1:0]   b_data_wires [SIZE:0][SIZE-1:0];
    wire                                 a_valid_wires [SIZE-1:0][SIZE:0];
    wire                                 b_valid_wires [SIZE:0][SIZE-1:0];
    wire signed [PE_ACCUM_DATA_WIDTH-1:0] pe_result_out_internal [SIZE-1:0][SIZE-1:0];
    wire                                  pe_result_valid_internal [SIZE-1:0][SIZE-1:0]; // Original pulsed valid, still available from PE

    // --- PE Done Flags & Reduction (REVISED) ---
    reg all_pes_calc_done_for_pk_q;
    reg all_pes_calc_done_for_pk_comb; // Changed back to reg for always @(*) block

    // --- New Wires for Row-wise Done Propagation ---
    wire pe_row_propagate_done_chain [SIZE-1:0][SIZE:0]; // [row_idx][col_idx_PLUS_ONE]
                                                         // chain[r][0] is input to PE(r,0)'s chain logic
                                                         // chain[r][c+1] is output from PE(r,c)'s chain logic
    wire last_column_done_signals [SIZE-1:0]; // Collects output from the last PE in each row
    
    // *** NEW ***: Register to hold the k_tile_is_first status for the duration of the FSM cycle
    reg k_tile_is_first_reg;

    // --- Shadow Buffer for Pk ---
    reg signed [ROW_WIDTH_BITS-1:0] pk_shadow_buffer [0:SIZE-1];
    reg                             pk_shadow_buffer_loaded_q; // Flag: shadow buffer has valid Pk, and is ready for ACCUM stage
    reg                             pe_calculation_phase_complete_q; // Indicates PEs finished, Pk is ready for latching

    // --- Main SA Control FSM ---
    // 使用 SystemVerilog 枚举类型，以便在 $display 中使用 .name() 方法
    typedef enum logic [2:0] {
        SA_FSM_IDLE              = 3'd0,
        SA_FSM_CALCULATING_PK     = 3'd1,
        SA_FSM_LATCHING_PK        = 3'd2,
        SA_FSM_ACCUMULATING     = 3'd3,
        SA_FSM_WAIT_ACCUM_FINISH = 3'd4
    } sa_fsm_state_e;
    sa_fsm_state_e sa_fsm_state_q, sa_fsm_state_d;

    // --- Accumulation Sub-control ---
    reg [$clog2(SIZE)-1:0] accum_current_row_q, accum_current_row_d;
    // Accumulation pipeline stages for Read-Modify-Write
    typedef enum logic [1:0] {
        ACCUM_PIPE_IDLE = 2'b00,
        ACCUM_PIPE_SRAM_READ_ISSUED = 2'b01, // SRAM Read address sent
        ACCUM_PIPE_SRAM_DATA_BACK_ADD_WRITE_ISSUED = 2'b10 // SRAM Data received, Add performed, SRAM Write address/data sent
    } accum_pipe_state_e;
    accum_pipe_state_e accum_pipe_state_q, accum_pipe_state_d;

    reg signed [ROW_WIDTH_BITS-1:0] pk_row_for_accum_q; // Current Pk row from shadow buffer
    reg signed [ROW_WIDTH_BITS-1:0] sram_old_row_for_accum_q; // Old C_sram row read from SRAM
    reg accum_all_rows_done_for_current_pk_q; // Flag: All rows of current Pk in shadow buffer are accumulated


    // --- Row Adder ---
    wire signed [ROW_WIDTH_BITS-1:0] accumulated_row_val;
    genvar r_add_gen_local;
    generate
        for (r_add_gen_local = 0; r_add_gen_local < SIZE; r_add_gen_local = r_add_gen_local + 1) begin : row_adder_elements
            assign accumulated_row_val[r_add_gen_local*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] =
                   pk_row_for_accum_q[r_add_gen_local*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] +
                   sram_old_row_for_accum_q[r_add_gen_local*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH];
        end
    endgenerate

    //===============================================================
    //== PE Array Instantiation and Boundary Connections
    //===============================================================
    genvar r_gen_local, c_gen_local;

    // Connect array_a_in and array_b_in to the PE array boundaries
    generate
        for (r_gen_local = 0; r_gen_local < SIZE; r_gen_local = r_gen_local + 1) begin : connect_a_to_pe_boundary
            assign a_data_wires[r_gen_local][0] = array_a_in[r_gen_local*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
            assign a_valid_wires[r_gen_local][0] = array_a_valid_in_indywidual[r_gen_local]; // 使用独立的valid
        end
        for (c_gen_local = 0; c_gen_local < SIZE; c_gen_local = c_gen_local + 1) begin : connect_b_to_pe_boundary
            assign b_data_wires[0][c_gen_local] = array_b_in[c_gen_local*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
            assign b_valid_wires[0][c_gen_local] = array_b_valid_in_indywidual[c_gen_local]; // 使用独立的valid
        end
    endgenerate

    // Instantiate SIZE*SIZE PEs
    generate
        for (r_gen_local = 0; r_gen_local < SIZE; r_gen_local = r_gen_local + 1) begin : pe_row_gen
            // For the first PE in each row, its pe_row_propagate_done_in is effectively 1'b1
            // (meaning no PEs to its left need to be done)
            assign pe_row_propagate_done_chain[r_gen_local][0] = 1'b1;

            for (c_gen_local = 0; c_gen_local < SIZE; c_gen_local = c_gen_local + 1) begin : pe_col_gen
                pe #(
                    .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH),
                    .ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH),
                    .MAC_COUNT_TARGET(SIZE), // 假设 K_SIZE 是你的 MAC_COUNT_TARGET
                    .ROW_IDX(r_gen_local),     // 传递行索引
                    .COL_IDX(c_gen_local)      // 传递列索引
                ) u_pe_inst (
                    .clk(clk),
                    .rst_n(rst_n),
                    .enable(activate_pe_computation), // PE only active during calc phase -- THIS LINE WAS MODIFIED
                    .clear_accumulator(1'b0), // Not used directly from top
                    .conditionally_clear_sum(1'b1), // PE handles its Pk init based on start_new_k_iteration
                    .a_valid_in(a_valid_wires[r_gen_local][c_gen_local]),
                    .a_data_in(a_data_wires[r_gen_local][c_gen_local]),
                    .a_valid_out(a_valid_wires[r_gen_local][c_gen_local+1]),
                    .a_data_out(a_data_wires[r_gen_local][c_gen_local+1]),
                    .b_valid_in(b_valid_wires[r_gen_local][c_gen_local]),
                    .b_data_in(b_data_wires[r_gen_local][c_gen_local]),
                    .b_valid_out(b_valid_wires[r_gen_local+1][c_gen_local]),
                    .b_data_out(b_data_wires[r_gen_local+1][c_gen_local]),
                    .result_out(pe_result_out_internal[r_gen_local][c_gen_local]),
                    .result_valid(pe_result_valid_internal[r_gen_local][c_gen_local]),
                    .start_new_systolic_pass(start_new_k_iteration),

                    // Connect the done propagation chain
                    .pe_row_propagate_done_in(pe_row_propagate_done_chain[r_gen_local][c_gen_local]),
                    .pe_row_propagate_done_out(pe_row_propagate_done_chain[r_gen_local][c_gen_local+1])
                );
            end
            // Collect the done signal from the last PE of each row
            assign last_column_done_signals[r_gen_local] = pe_row_propagate_done_chain[r_gen_local][SIZE];
        end
    endgenerate

    always @(posedge clk) begin
        // 当SA FSM处于计算状态时，每个周期都打印一次“完成信号链”的输出
        // if(sa_fsm_state_q == SA_FSM_CALCULATING_PK) begin
        //     $display("[%0t] [SA_DONE_CHAIN] Done signals from each row: %p", $time, last_column_done_signals);
        // end
    end

    // --- Combinational logic for all_pes_calc_done_for_pk_comb (REVISED) ---
    // This now ANDs the SIZE signals from the last column of the done propagation chain
    always @(*) begin
        all_pes_calc_done_for_pk_comb = 1'b1; // Assume all done
        for (integer r_reduce = 0; r_reduce < SIZE; r_reduce = r_reduce + 1) begin
            // If any row is not done, then the overall done signal should be 0.
            // The 'if' statement ensures that if it's set to 0, it stays 0.
            if (!last_column_done_signals[r_reduce]) begin
                all_pes_calc_done_for_pk_comb = 1'b0;
            end
        end
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            all_pes_calc_done_for_pk_q <= 1'b0;
            pe_calculation_phase_complete_q <= 1'b0;
            k_tile_is_first_reg <= 1'b0; // *** NEW *** Initialize register
        end else begin
            all_pes_calc_done_for_pk_q <= all_pes_calc_done_for_pk_comb; // Register the combinational signal
            
            // *** MODIFIED ***: Latch k_tile_is_first status at the beginning of the iteration
            if (start_new_k_iteration) begin
                pe_calculation_phase_complete_q <= 1'b0;
                k_tile_is_first_reg <= k_tile_is_first; // Latch status from accelerator
                // if (k_tile_is_first) begin
                //     $display("[%0t] [SA_SEQ] k_tile_is_first_reg latched to 1 (new C tile first K).", $time);
                // end else begin
                //     $display("[%0t] [SA_SEQ] k_tile_is_first_reg latched to 0 (subsequent K for C tile).", $time);
                // end
            end else if (all_pes_calc_done_for_pk_comb && sa_fsm_state_q == SA_FSM_CALCULATING_PK) begin
                // if (pe_calculation_phase_complete_q == 1'b0) begin
                //     $display("[%0t] [PE_DONE] All PEs finished calculation for Pk (via chain). Asserting pe_calculation_phase_complete_q.", $time);
                // end
                pe_calculation_phase_complete_q <= 1'b1;
            end
        end
    end

    // --- Main SA Control FSM (Sequential Part) ---
    logic pk_shadow_buffer_loaded_next;
    logic sa_k_iteration_accum_done_next;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            sa_fsm_state_q <= SA_FSM_IDLE;
            sa_busy <= 1'b0;
            sa_k_iteration_accum_done <= 1'b0;
            pk_shadow_buffer_loaded_q <= 1'b0;
            accum_current_row_q <= 0;
            accum_pipe_state_q <= ACCUM_PIPE_IDLE;
            // accum_all_rows_done_for_current_pk_q is reset in its own block
        end else begin
            // <<< NEW/MODIFIED DISPLAY: Log state transitions >>>
            // if (sa_fsm_state_d != sa_fsm_state_q) begin
            //      $display("[%0t] [SA_FSM_SEQ] Main FSM State Change: %s -> %s", $time, sa_fsm_state_q.name(), sa_fsm_state_d.name());
            // end
            // if (accum_pipe_state_d != accum_pipe_state_q && sa_fsm_state_q == SA_FSM_ACCUMULATING) begin // Only log pipe changes when in ACCUM state
            //      $display("[%0t] [SA_FSM_SEQ] Accum Pipe State Change: %s -> %s (Row: %d)", $time, accum_pipe_state_q.name(), accum_pipe_state_d.name(), accum_current_row_q);
            // end

            sa_fsm_state_q <= sa_fsm_state_d;
            sa_busy <= (sa_fsm_state_d != SA_FSM_IDLE);

            // pk_shadow_buffer_loaded_q logic (log changes)
            pk_shadow_buffer_loaded_next = (sa_fsm_state_d == SA_FSM_LATCHING_PK) ? 1'b1 :
                                           (sa_fsm_state_q == SA_FSM_ACCUMULATING && accum_all_rows_done_for_current_pk_q && sa_fsm_state_d == SA_FSM_IDLE) ? 1'b0 :
                                           pk_shadow_buffer_loaded_q;
            // if (pk_shadow_buffer_loaded_next != pk_shadow_buffer_loaded_q) begin
            //     $display("[%0t] [SA_FSM_SEQ] pk_shadow_buffer_loaded_q: %b -> %b (MainFSM: %s->%s, all_done: %b)",
            //              $time, pk_shadow_buffer_loaded_q, pk_shadow_buffer_loaded_next,
            //              sa_fsm_state_q.name(), sa_fsm_state_d.name(), accum_all_rows_done_for_current_pk_q);
            // end
            pk_shadow_buffer_loaded_q <= pk_shadow_buffer_loaded_next;


            accum_current_row_q <= accum_current_row_d;
            accum_pipe_state_q <= accum_pipe_state_d;
            // accum_all_rows_done_for_current_pk_q updated in its own block

            // Latch Pk to shadow buffer
            if (sa_fsm_state_d == SA_FSM_LATCHING_PK) begin
                // $display("[%0t] [SA_FSM_SEQ] Latching Pk to shadow buffer.", $time);
                for (integer r_idx = 0; r_idx < SIZE; r_idx = r_idx + 1) begin
                    for (integer c_idx = 0; c_idx < SIZE; c_idx = c_idx + 1) begin
                        pk_shadow_buffer[r_idx][c_idx *PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] <= pe_result_out_internal[r_idx][c_idx];
                    end
                    // if (r_idx == 0) begin // Print only for the first row to reduce log clutter
                    //     $display("[%0t] [SA_LATCH_PK] after ShadowBuffer[0][0]=%d, [0][1]=%d, [0][2]=%d, [0][3]=%d",
                    //             $time,
                    //             pk_shadow_buffer[0][0*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH],
                    //             pk_shadow_buffer[0][1*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH],
                    //             pk_shadow_buffer[0][2*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH],
                    //             pk_shadow_buffer[0][3*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH]);
                    // end
                end
            end

            // Latch data for adder
            if (accum_pipe_state_q == ACCUM_PIPE_SRAM_READ_ISSUED && accum_pipe_state_d == ACCUM_PIPE_SRAM_DATA_BACK_ADD_WRITE_ISSUED) begin
                // $display("[%0t] [SA_FSM_SEQ] Latching SRAM_C read data for row %d for adder.", $time, accum_current_row_q);
                 sram_old_row_for_accum_q <= sram_c_rdata_A_from_sram; // SRAM data is now valid
                 pk_row_for_accum_q       <= pk_shadow_buffer[accum_current_row_q];
            end

            // sa_k_iteration_accum_done logic
            sa_k_iteration_accum_done_next = (sa_fsm_state_q == SA_FSM_ACCUMULATING && sa_fsm_state_d == SA_FSM_IDLE && accum_all_rows_done_for_current_pk_q);
            // if (sa_k_iteration_accum_done_next != sa_k_iteration_accum_done) begin
            //     $display("[%0t] [SA_FSM_SEQ] sa_k_iteration_accum_done: %b -> %b (MainFSM: %s->%s, all_done: %b)",
            //              $time, sa_k_iteration_accum_done, sa_k_iteration_accum_done_next,
            //              sa_fsm_state_q.name(), sa_fsm_state_d.name(), accum_all_rows_done_for_current_pk_q);
            // end
            sa_k_iteration_accum_done <= sa_k_iteration_accum_done_next;
        end
    end

    // --- Main SA Control FSM (Combinational Part) ---
    always @(*) begin
        sa_fsm_state_d = sa_fsm_state_q;
        sram_c_raddr_A_to_sram = accum_current_row_q; // Default read from current accum row
        sram_c_waddr_to_sram   = accum_current_row_q; // Default write to current accum row
        sram_c_wdata_to_sram   = 0; // Default
        sram_c_we_to_sram      = 1'b0; // Default

        accum_current_row_d = accum_current_row_q;
        accum_pipe_state_d = accum_pipe_state_q;

        // <<< NEW/MODIFIED DISPLAY: Log FSM inputs and decisions >>>
        // Uncomment this for very verbose FSM decision logging
        // $display("[%0t] [SA_FSM_COMB] Current MainFSM: %s, Current PipeState: %s, accum_all_done: %b, pk_shadow_loaded: %b, pe_calc_complete: %b, start_new_k: %b, k_is_first: %b",
        //           $time, sa_fsm_state_q.name(), accum_pipe_state_q.name(), accum_all_rows_done_for_current_pk_q, pk_shadow_buffer_loaded_q, pe_calculation_phase_complete_q, start_new_k_iteration, k_tile_is_first_reg);

        case (sa_fsm_state_q)
            SA_FSM_IDLE: begin
                if (start_new_k_iteration) begin
                    if (pk_shadow_buffer_loaded_q) begin // If Pk-1 accum is still ongoing (shadow buffer busy)
                        sa_fsm_state_d = SA_FSM_WAIT_ACCUM_FINISH; // Go to wait state, PEs start calc
                    end else begin
                        sa_fsm_state_d = SA_FSM_CALCULATING_PK;
                    end
                    // <<< NEW/MODIFIED DISPLAY >>>
                    // $display("[%0t] [SA_FSM_COMB_IDLE] start_new_k_iteration=1. pk_shadow_buffer_loaded_q=%b. Next MainFSM: %s", $time, pk_shadow_buffer_loaded_q, sa_fsm_state_d.name());
                end
            end
            SA_FSM_CALCULATING_PK: begin
                if (pe_calculation_phase_complete_q) begin // All PEs finished calculating Pk
                    if (pk_shadow_buffer_loaded_q) begin // If previous Pk-1 accum not done using buffer
                        sa_fsm_state_d = SA_FSM_WAIT_ACCUM_FINISH;
                    end else begin
                        sa_fsm_state_d = SA_FSM_LATCHING_PK;
                    end
                    // <<< NEW/MODIFIED DISPLAY >>>
                    // $display("[%0t] [SA_FSM_COMB_CALC] pe_calc_complete=1. pk_shadow_buffer_loaded_q=%b. Next MainFSM: %s", $time, pk_shadow_buffer_loaded_q, sa_fsm_state_d.name());
                end
            end
            SA_FSM_LATCHING_PK: begin // Single cycle state
                sa_fsm_state_d = SA_FSM_ACCUMULATING;
                // Initialize accumulation pipeline for row 0
                accum_current_row_d = 0;
                accum_pipe_state_d = ACCUM_PIPE_SRAM_READ_ISSUED;
                sram_c_raddr_A_to_sram = 0; // Issue read for row 0
                // <<< NEW/MODIFIED DISPLAY >>>
                // $display("[%0t] [SA_FSM_COMB_LATCH] Transitioning to ACCUMULATING. Next PipeState: %s, Next Row: %d, SRAM RdAddr: %d",
                //           $time, accum_pipe_state_d.name(), accum_current_row_d, sram_c_raddr_A_to_sram);
            end
            SA_FSM_ACCUMULATING: begin
                // <<< NEW/MODIFIED DISPLAY: Inside ACCUMULATING state >>>
                // $display("[%0t] [SA_FSM_COMB_ACCUM] Current PipeState: %s, Current Row: %d, accum_all_done: %b",
                //           $time, accum_pipe_state_q.name(), accum_current_row_q, accum_all_rows_done_for_current_pk_q);

                if (accum_all_rows_done_for_current_pk_q) begin // Check overall completion first
                    sa_fsm_state_d = SA_FSM_IDLE;
                    accum_pipe_state_d = ACCUM_PIPE_IDLE; // Ensure pipe is idle
                    // Default SRAM signals (we=0) should prevent further ops
                    // <<< NEW/MODIFIED DISPLAY >>>
                    // $display("[%0t] [SA_FSM_COMB_ACCUM] All rows done. Next MainFSM: IDLE. Next PipeState: IDLE.", $time);
                end else begin
                    sa_fsm_state_d = SA_FSM_ACCUMULATING; // Default to stay
                    case (accum_pipe_state_q)
                        ACCUM_PIPE_IDLE: begin // Should not happen if not all_rows_done
                            // This state implies we are starting a new row if not all done
                            accum_pipe_state_d = ACCUM_PIPE_SRAM_READ_ISSUED;
                            sram_c_raddr_A_to_sram = accum_current_row_q;
                            // <<< NEW/MODIFIED DISPLAY >>>
                            // $display("[%0t] [SA_FSM_COMB_ACCUM_PIPE_IDLE] Next PipeState: READ_ISSUED, SRAM RdAddr: %d (for row %d)",
                            //           $time, sram_c_raddr_A_to_sram, accum_current_row_q);
                        end
                        ACCUM_PIPE_SRAM_READ_ISSUED: begin
                            // Waiting for SRAM data. Next cycle data will be valid.
                            accum_pipe_state_d = ACCUM_PIPE_SRAM_DATA_BACK_ADD_WRITE_ISSUED;
                            // <<< NEW/MODIFIED DISPLAY >>>
                            // $display("[%0t] [SA_FSM_COMB_ACCUM_PIPE_READ_ISSUED] Next PipeState: DATA_BACK_ADD_WRITE_ISSUED.", $time);
                        end
                        ACCUM_PIPE_SRAM_DATA_BACK_ADD_WRITE_ISSUED: begin
                            // *** CORE LOGIC CHANGE ***
                            // Data was read, adder calculated, SRAM write is now being issued.
                            sram_c_waddr_to_sram = accum_current_row_q;
                            sram_c_we_to_sram    = 1'b1;
                            
                            if (k_tile_is_first_reg) begin // Check if this is the first K iteration
                                sram_c_wdata_to_sram = pk_row_for_accum_q; // Directly write Pk
                                // $display("[%0t] [SA_FSM_COMB_ACCUM_PIPE_WRITE_K0] Row %d DIRECT write Pk (K_IS_FIRST). SRAM WE=1. Pk[0]=%d", $time, accum_current_row_q, pk_row_for_accum_q[PE_ACCUM_DATA_WIDTH-1:0]);
                            end else begin
                                sram_c_wdata_to_sram = accumulated_row_val; // Normal accumulation: Pk + C_prev
                                // $display("[%0t] [SA_FSM_COMB_ACCUM_PIPE_WRITE] Row %d ACCUM write Pk+C. SRAM WE=1. Pk[0]=%d, C_old[0]=%d, Result[0]=%d", $time, accum_current_row_q, pk_row_for_accum_q[PE_ACCUM_DATA_WIDTH-1:0], sram_old_row_for_accum_q[PE_ACCUM_DATA_WIDTH-1:0], accumulated_row_val[PE_ACCUM_DATA_WIDTH-1:0]);
                            end
                            
                            // Move to next row or finish
                            if (accum_current_row_q == SIZE - 1) begin
                                accum_pipe_state_d = ACCUM_PIPE_IDLE; // Reset pipe for potential next K
                                // <<< NEW/MODIFIED DISPLAY >>>
                                // $display("[%0t] [SA_FSM_COMB_ACCUM_PIPE_WRITE] Last row (row %d) write issued. Next PipeState: IDLE. SRAM WE=1",
                                //           $time, accum_current_row_q);
                            end else begin
                                accum_current_row_d = accum_current_row_q + 1;
                                accum_pipe_state_d = ACCUM_PIPE_SRAM_READ_ISSUED; // Start next row read
                                sram_c_raddr_A_to_sram = accum_current_row_q + 1;
                                // <<< NEW/MODIFIED DISPLAY >>>
                                // $display("[%0t] [SA_FSM_COMB_ACCUM_PIPE_WRITE] Row %d write issued. Next PipeState: READ_ISSUED for row %d. SRAM WE=1, Next SRAM RdAddr: %d",
                                //           $time, accum_current_row_q, accum_current_row_d, sram_c_raddr_A_to_sram);
                            end
                        end
                    endcase
                end
            end
            SA_FSM_WAIT_ACCUM_FINISH: begin
                // PEs have finished Pk+1, but shadow buffer is still in use by Pk's accumulation
                if (!pk_shadow_buffer_loaded_q) begin // Shadow buffer is now free
                    sa_fsm_state_d = SA_FSM_LATCHING_PK; // Latch the Pk+1 that was waiting
                    // <<< NEW/MODIFIED DISPLAY >>>
                    // $display("[%0t] [SA_FSM_COMB_WAIT] pk_shadow_buffer_loaded_q is now 0. Next MainFSM: LATCHING_PK.", $time);
                end
            end
        endcase
    end

    // Manage accum_all_rows_done_for_current_pk_q more carefully
    always @(posedge clk or negedge rst_n) begin
        if(!rst_n) begin
            accum_all_rows_done_for_current_pk_q <= 1'b0;
        end else begin
            logic prev_accum_all_rows_done;
            prev_accum_all_rows_done = accum_all_rows_done_for_current_pk_q;

            if (sa_fsm_state_q == SA_FSM_LATCHING_PK && sa_fsm_state_d == SA_FSM_ACCUMULATING) begin // When starting accumulation
                // This means a new Pk is being latched, so the accumulation for this new Pk is not yet done.
                accum_all_rows_done_for_current_pk_q <= 1'b0;
            end else if (sa_fsm_state_q == SA_FSM_ACCUMULATING &&
                         accum_pipe_state_q == ACCUM_PIPE_SRAM_DATA_BACK_ADD_WRITE_ISSUED && // When write is issued
                         accum_current_row_q == SIZE - 1 && sram_c_we_to_sram == 1'b1) begin // For the last row, and we're actually writing
                accum_all_rows_done_for_current_pk_q <= 1'b1;
            end
            // No other conditions change it, so it holds its value until explicitly changed.

            // <<< NEW/MODIFIED DISPLAY: Log changes to accum_all_rows_done_for_current_pk_q >>>
            // if (prev_accum_all_rows_done != accum_all_rows_done_for_current_pk_q) begin
            //     $display("[%0t] [SA_ACCUM_FLAG] accum_all_rows_done_for_current_pk_q: %b -> %b (MainFSM: %s->%s, PipeState: %s, Row: %d, WE: %b)",
            //              $time, prev_accum_all_rows_done, accum_all_rows_done_for_current_pk_q,
            //              sa_fsm_state_q.name(), sa_fsm_state_d.name(), accum_pipe_state_q.name(), accum_current_row_q, sram_c_we_to_sram);
            // end
        end
    end

endmodule