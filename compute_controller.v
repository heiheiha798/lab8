// Filename: compute_controller.v
// Description: Manages K-iterations for computing a single C_tile.
//              Coordinates data_formatter and sa_enhanced.
`timescale 1ns / 1ps

module compute_controller #(
    parameter TILE_SIZE = 16, // Matches SA and tile dimensions
    // This parameter defines how many (A_tile * B_tile) products are accumulated for one C_tile.
    // For a simple C_tile = A_tile * B_tile (no further K-dimension splitting), this would be 1.
    // For GEMM like C[i][j] = sum over k_batches (A[i][k_batch] * B[k_batch][j]), this would be num_k_batches.
    parameter TOTAL_K_ITERATIONS_PER_TILE = 32 // Example: K dimension is 512, TILE_SIZE_K is 16, so 512/16 = 32
)(
    input wire clk,
    input wire rst_n,

    // --- Interface with Accelerator (Top-Level FSM) ---
    input wire start_tile_computation,      // Asserted by Accelerator to start computing/accumulating one C_tile
                                            // Accelerator is responsible for ensuring input SRAMs (A,B) have
                                            // the *first* set of A_tile, B_tile data ready before asserting this,
                                            // and for managing ping-pong buffers for A, B, C.
                                            // Accelerator also provides addressing for Loader and Writer.
    output reg tile_computation_busy,       // High while this controller is working on a C_tile
    output reg tile_computation_done,       // Pulsed high for one cycle when all K-iterations for the C_tile are complete

    // --- Interface with Data Formatter ---
    output reg df_start_pass,               // To data_formatter.start_pass, pulsed to start sending one pair of (A_tile, B_tile)
    input wire df_pass_done,                // From data_formatter.pass_done

    // --- Interface with SA_Enhanced ---
    output reg sa_start_new_k_iteration,    // To sa_enhanced.start_new_k_iteration, pulsed
    output reg sa_activate_pe_computation,  // To sa_enhanced.activate_pe_computation, level
    input wire sa_k_iteration_accum_done    // From sa_enhanced.sa_k_iteration_accum_done
                                            // (sa_enhanced.sa_busy can be an optional input for more detailed status)
);

    //--------------------------------------------------------------------------
    // FSM States
    //--------------------------------------------------------------------------
    localparam FSM_WIDTH = 3;
    localparam S_IDLE               = {FSM_WIDTH{1'b0}};
    localparam S_INIT_K_ITER        = S_IDLE + 1;               // Initialize for a new K-iteration (could be first or subsequent)
    localparam S_START_DATA_SA      = S_INIT_K_ITER + 1;        // Pulse start signals to DF and SA
    localparam S_WAIT_DF_PASS_DONE  = S_START_DATA_SA + 1;      // Wait for Data Formatter to finish sending current A/B tiles
    localparam S_WAIT_SA_ACCUM_DONE = S_WAIT_DF_PASS_DONE + 1;  // Wait for SA to finish compute & accumulate for current Pk
    localparam S_K_ITER_DONE_CHECK  = S_WAIT_SA_ACCUM_DONE + 1; // Check if all K-iterations for the tile are complete

    //--------------------------------------------------------------------------
    // Internal Registers
    //--------------------------------------------------------------------------
    reg [FSM_WIDTH-1:0] current_state_q, next_state_d;
    reg [$clog2(TOTAL_K_ITERATIONS_PER_TILE):0] k_iter_count_q, k_iter_count_d; // Counts completed K-iterations

    //--------------------------------------------------------------------------
    // Sequential Logic: FSM State, K-iteration Counter, Outputs
    //--------------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state_q            <= S_IDLE;
            k_iter_count_q             <= 0;
            tile_computation_busy      <= 1'b0;
            tile_computation_done      <= 1'b0;
            df_start_pass              <= 1'b0;
            sa_start_new_k_iteration   <= 1'b0;
            sa_activate_pe_computation <= 1'b0;
        end else begin
            current_state_q            <= next_state_d;
            k_iter_count_q             <= k_iter_count_d;

            // tile_computation_busy is high if not IDLE
            tile_computation_busy      <= (next_state_d != S_IDLE);
            
            // tile_computation_done pulses for one cycle when transitioning from K_ITER_DONE_CHECK to IDLE
            tile_computation_done      <= (current_state_q == S_K_ITER_DONE_CHECK && next_state_d == S_IDLE);

            // df_start_pass pulses for one cycle
            df_start_pass              <= (current_state_q == S_INIT_K_ITER && next_state_d == S_START_DATA_SA);
            
            // sa_start_new_k_iteration pulses for one cycle
            sa_start_new_k_iteration   <= (current_state_q == S_INIT_K_ITER && next_state_d == S_START_DATA_SA);
            
            // sa_activate_pe_computation is high as long as we are processing K-iterations for the current tile
            sa_activate_pe_computation <= (next_state_d != S_IDLE && next_state_d != S_INIT_K_ITER); // Active during START, WAIT_DF, WAIT_SA, K_ITER_DONE_CHECK
        end
    end

    //--------------------------------------------------------------------------
    // Combinational Logic: FSM Next State and K-iteration Counter Update
    //--------------------------------------------------------------------------
    always @(*) begin
        next_state_d     = current_state_q;
        k_iter_count_d = k_iter_count_q;

        case (current_state_q)
            S_IDLE: begin
                if (start_tile_computation) begin
                    next_state_d = S_INIT_K_ITER;
                    k_iter_count_d = 0; // Reset for the new tile
                end
            end

            S_INIT_K_ITER: begin
                // This state ensures k_iter_count is set/incremented before starting DF/SA
                // Accelerator should ensure new A/B tile data is ready in SRAMs
                // or signal DataFormatter which banks to use for k_iter_count_q.
                // For now, assume DataFormatter knows (e.g., sequentially reads K slices).
                next_state_d = S_START_DATA_SA;
            end

            S_START_DATA_SA: begin
                // df_start_pass and sa_start_new_k_iteration are asserted by sequential block based on this transition.
                // These are single-cycle pulses.
                next_state_d = S_WAIT_DF_PASS_DONE;
            end

            S_WAIT_DF_PASS_DONE: begin
                if (df_pass_done) begin
                    // Data Formatter has finished sending A_tile[k_iter_count_q] and B_tile[k_iter_count_q]
                    next_state_d = S_WAIT_SA_ACCUM_DONE;
                end
            end

            S_WAIT_SA_ACCUM_DONE: begin
                if (sa_k_iteration_accum_done) begin
                    // SA has finished computing Pk for current A/B tiles and accumulated it into SRAM C.
                    next_state_d = S_K_ITER_DONE_CHECK;
                end
            end

            S_K_ITER_DONE_CHECK: begin
                if (k_iter_count_q == TOTAL_K_ITERATIONS_PER_TILE - 1) begin // All K-iterations for this tile are done
                    next_state_d = S_IDLE;
                    // tile_computation_done will be asserted by sequential block.
                end else begin // More K-iterations needed for this tile
                    k_iter_count_d = k_iter_count_q + 1;
                    next_state_d = S_INIT_K_ITER; // Prepare for the next K-iteration
                                                // Accelerator needs to ensure next A/B data is ready by now
                                                // or Data Formatter needs to know to fetch next K-slice.
                end
            end
            default: begin
                next_state_d = S_IDLE;
            end
        endcase
    end

endmodule