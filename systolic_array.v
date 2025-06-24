//
// Filename: systolic_array.v
// Description: Final, corrected version of the pure-computation systolic array.
//              It now includes an internal output controller to stream results
//              autonomously after computation is done, resolving the handshake deadlock.
//
`timescale 1ns / 1ps

module systolic_array #(
    parameter SIZE = 16,
    parameter INPUT_DATA_WIDTH = 8,
    parameter PE_ACCUM_DATA_WIDTH = 32
)(
    input wire clk,
    input wire rst_n,
    input wire clear_all_pe_accumulators,
    input wire conditionally_clear_pe_sums_level,
    input wire activate_pe_computation,
    input wire array_data_valid_in,
    input wire [SIZE*INPUT_DATA_WIDTH-1:0] array_a_in,
    input wire [SIZE*INPUT_DATA_WIDTH-1:0] array_b_in,

    output wire array_a_data_valid_out,
    output wire [SIZE*INPUT_DATA_WIDTH-1:0] array_a_out,
    output wire array_b_data_valid_out,
    output wire [SIZE*INPUT_DATA_WIDTH-1:0] array_b_out,

    output reg signed [SIZE*PE_ACCUM_DATA_WIDTH-1:0] tile_row_result_out,
    output reg                                tile_row_result_valid,
    output reg [$clog2(SIZE)-1:0]           sa_partial_sum_row_idx,

    output wire                               tile_all_pes_done_one_pass,
    input wire start_new_systolic_pass
);

    // --- Internal Wires (Unchanged) ---
    wire signed [INPUT_DATA_WIDTH-1:0]   a_data_wires [SIZE-1:0][SIZE:0];
    wire signed [INPUT_DATA_WIDTH-1:0]   b_data_wires [SIZE:0][SIZE-1:0];
    wire                                 a_valid_wires [SIZE-1:0][SIZE:0];
    wire                                 b_valid_wires [SIZE:0][SIZE-1:0];
    wire signed [PE_ACCUM_DATA_WIDTH-1:0] pe_result_out_internal [SIZE-1:0][SIZE-1:0];
    wire                                  pe_result_valid_internal [SIZE-1:0][SIZE-1:0];
    
    // --- PE Done Flags ---
    reg pe_done_flags [SIZE-1:0][SIZE-1:0];
    // --- MODIFIED: Changed from 'wire' to 'reg' as it's assigned in an always block ---
    reg all_pes_in_tile_done_reduction;
    
    genvar r_gen, c_gen;
    integer i_col_local; 

    //===============================================================
    //== [NEW] Internal Output Streaming Controller
    //===============================================================
    localparam FSM_OUT_IDLE      = 0;
    localparam FSM_OUT_STREAMING = 1;
    reg output_fsm_state;
    reg [$clog2(SIZE)-1:0] output_row_counter;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            output_fsm_state <= FSM_OUT_IDLE;
            output_row_counter <= 0;
            tile_row_result_valid <= 1'b0;
        end else if (start_new_systolic_pass) begin // Reset FSM and counter for a new pass
            output_fsm_state <= FSM_OUT_IDLE;
            output_row_counter <= 0;
            tile_row_result_valid <= 1'b0;
        end else begin
            case(output_fsm_state)
                FSM_OUT_IDLE: begin
                    // In IDLE, output is not valid.
                    tile_row_result_valid <= 1'b0;
                    if (all_pes_in_tile_done_reduction) begin
                        // All PEs done, prepare to stream the first row (row 0).
                        output_fsm_state <= FSM_OUT_STREAMING;
                        output_row_counter <= 0; // Set counter for row 0
                        tile_row_result_valid <= 1'b1; // **** MODIFICATION **** Assert valid for row 0 in the *next* cycle, when FSM is in STREAMING and counter is 0.
                    end
                end
                FSM_OUT_STREAMING: begin
                    // tile_row_result_valid is already high (set in IDLE->STREAMING or previous STREAMING cycle)
                    // The current output_row_counter value is used for this cycle's output data.
                    if (output_row_counter == SIZE - 1) begin
                        // This is the last row.
                        output_fsm_state <= FSM_OUT_IDLE;
                        tile_row_result_valid <= 1'b0; // De-assert valid when done with the last row
                    end else begin
                        // Not the last row, prepare for the next row.
                        output_row_counter <= output_row_counter + 1;
                        tile_row_result_valid <= 1'b1; // Keep valid asserted for the next row
                    end
                end
            endcase
        end
    end
    
    // Combinational assignments for output ports
    always @(*) begin
        sa_partial_sum_row_idx = output_row_counter; // sa_partial_sum_row_idx comb. follows output_row_counter
        for (i_col_local = 0; i_col_local < SIZE; i_col_local = i_col_local + 1) begin
            tile_row_result_out[i_col_local*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] = pe_result_out_internal[output_row_counter][i_col_local];
        end
    end

`ifdef DEBUG_SA_OUTPUT
    always @(posedge clk) begin
        if (rst_n && tile_row_result_valid) begin // tile_row_result_valid is the registered version of SA output valid
            $display("[%0t] [SA_INTERNAL_OUT] Row: %d, Valid: %b, Data[0]=%d, Data[1]=%d",
                     $time,
                     sa_partial_sum_row_idx, // This is output_row_counter
                     tile_row_result_valid,
                     tile_row_result_out[0*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH],
                     tile_row_result_out[1*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH]);
            // Add more elements if needed, e.g., tile_row_result_out[ (SIZE-1)*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH]
        end
    end
`endif
    
    //===============================================================
    //== Unchanged Logic
    //===============================================================
    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : connect_a_to_pe_boundary
            assign a_data_wires[r_gen][0] = array_a_in[r_gen*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
            assign a_valid_wires[r_gen][0] = array_data_valid_in;
        end
        for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : connect_b_to_pe_boundary
            assign b_data_wires[0][c_gen] = array_b_in[c_gen*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
            assign b_valid_wires[0][c_gen] = array_data_valid_in;
        end
    endgenerate

    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : pe_row
            for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : pe_col
                pe #(.INPUT_DATA_WIDTH(INPUT_DATA_WIDTH), .ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH), .MAC_COUNT_TARGET(SIZE)) 
                u_pe_inst (.clk(clk), .rst_n(rst_n), .enable(activate_pe_computation), .clear_accumulator(clear_all_pe_accumulators), .conditionally_clear_sum(conditionally_clear_pe_sums_level), .a_valid_in(a_valid_wires[r_gen][c_gen]), .a_data_in(a_data_wires[r_gen][c_gen]), .a_valid_out(a_valid_wires[r_gen][c_gen+1]), .a_data_out(a_data_wires[r_gen][c_gen+1]), .b_valid_in(b_valid_wires[r_gen][c_gen]), .b_data_in(b_data_wires[r_gen][c_gen]), .b_valid_out(b_valid_wires[r_gen+1][c_gen]), .b_data_out(b_data_wires[r_gen+1][c_gen]), .result_out(pe_result_out_internal[r_gen][c_gen]), .result_valid(pe_result_valid_internal[r_gen][c_gen]), .start_new_systolic_pass(start_new_systolic_pass));
            end
        end
    endgenerate

    assign array_a_data_valid_out = (SIZE > 0) ? a_valid_wires[0][SIZE] : 1'b0;
    assign array_b_data_valid_out = (SIZE > 0) ? b_valid_wires[SIZE][0] : 1'b0;
    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : connect_a_output_stream
            assign array_a_out[r_gen*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] = a_data_wires[r_gen][SIZE];
        end
        for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : connect_b_output_stream
            assign array_b_out[c_gen*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] = b_data_wires[SIZE][c_gen];
        end
    endgenerate

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (integer r = 0; r < SIZE; r = r + 1) begin
                for (integer c = 0; c < SIZE; c = c + 1) begin
                    pe_done_flags[r][c] <= 1'b0;
                end
            end
        end else if (start_new_systolic_pass) begin // Reset done flags for new pass
            for (integer r = 0; r < SIZE; r = r + 1) begin
                for (integer c = 0; c < SIZE; c = c + 1) begin
                    pe_done_flags[r][c] <= 1'b0;
                end
            end
        end else if (activate_pe_computation) begin // Only set done flags when computation is active
            for (integer r = 0; r < SIZE; r = r + 1) begin
                for (integer c = 0; c < SIZE; c = c + 1) begin
                    if (pe_result_valid_internal[r][c]) begin
                        pe_done_flags[r][c] <= 1'b1;
                    end
                end
            end
        end
    end

    always@(*) begin
        all_pes_in_tile_done_reduction = 1'b1;
        if (SIZE > 0) begin // Avoid loop if SIZE is 0
            for (integer r = 0; r < SIZE; r = r + 1) begin
                for (integer c = 0; c < SIZE; c = c + 1) begin
                    if (!pe_done_flags[r][c]) begin
                        all_pes_in_tile_done_reduction = 1'b0;
                        // No need to continue if one PE is not done
                        // break; // Verilog 'break' is only for 'for' loops in procedural blocks, not generate/always_comb
                    end
                end
                // if (!all_pes_in_tile_done_reduction) break; // See comment above
            end
        end
    end
    assign tile_all_pes_done_one_pass = all_pes_in_tile_done_reduction;

`ifdef DEBUG_SA_OUTPUT_CTRL
    // Previous state registers for change detection of key signals
    reg prev_all_pes_in_tile_done_reduction;
    reg prev_output_fsm_state;
    reg prev_tile_row_result_valid;
    reg [$clog2(SIZE)-1:0] prev_output_row_counter;

    initial begin
        prev_all_pes_in_tile_done_reduction = 1'b0;
        prev_output_fsm_state = FSM_OUT_IDLE;
        prev_tile_row_result_valid = 1'b0;
        prev_output_row_counter = 0;
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            prev_all_pes_in_tile_done_reduction <= 1'b0;
            prev_output_fsm_state <= FSM_OUT_IDLE;
            prev_tile_row_result_valid <= 1'b0;
            prev_output_row_counter <= 0;
        end else begin
            // Capture current values to become previous values for the next cycle
            prev_all_pes_in_tile_done_reduction <= all_pes_in_tile_done_reduction;
            prev_output_fsm_state <= output_fsm_state;     // output_fsm_state is a reg updated by the FSM block
            prev_tile_row_result_valid <= tile_row_result_valid; // tile_row_result_valid is a reg updated by FSM
            prev_output_row_counter <= output_row_counter; // output_row_counter is a reg updated by FSM
        end
    end

    always @(posedge clk) begin
        if (rst_n) begin
            // When all_pes_done changes
            if (prev_all_pes_in_tile_done_reduction !== all_pes_in_tile_done_reduction) begin
                $display("[%0t] [SA_DBG_CTRL] all_pes_in_tile_done_reduction changed from %b to %b",
                         $time, prev_all_pes_in_tile_done_reduction, all_pes_in_tile_done_reduction);
            end

            // When FSM state changes OR when in IDLE and all_pes_done is high (about to transition)
            if (prev_output_fsm_state !== output_fsm_state || (output_fsm_state == FSM_OUT_IDLE && all_pes_in_tile_done_reduction && !prev_all_pes_in_tile_done_reduction)) begin
                // Added !prev_all_pes_in_tile_done_reduction to only catch the rising edge of all_pes_done when in IDLE
                $display("[%0t] [SA_DBG_CTRL_FSM_CHG] FSM state: %s (was %s). all_pes_done: %b. output_row_counter (at clk edge): %d. tile_row_result_valid (at clk edge): %b",
                         $time,
                         (output_fsm_state == FSM_OUT_IDLE ? "IDLE" : "STREAMING"),
                         (prev_output_fsm_state == FSM_OUT_IDLE ? "IDLE" : "STREAMING"),
                         all_pes_in_tile_done_reduction,
                         output_row_counter, // Value of output_row_counter at the beginning of this clock cycle
                         tile_row_result_valid // Value of tile_row_result_valid at the beginning of this clock cycle
                        );
            end

            if (tile_row_result_valid) begin // Print whenever valid is high for detailed tracing
                // This will print the state of output_row_counter and sa_partial_sum_row_idx
                // as they are at the beginning of the clock cycle where tile_row_result_valid is high.
                $display("[%0t] [SA_DBG_CTRL_OUT_VALID_HIGH] Current_FSM_State: %s, tile_row_result_valid: %b (was %b)",
                         $time, (output_fsm_state == FSM_OUT_IDLE ? "IDLE" : "STREAMING"), tile_row_result_valid, prev_tile_row_result_valid);
                $display("                      Outputting for sa_partial_sum_row_idx: %d (derived from output_row_counter: %d)",
                         sa_partial_sum_row_idx, output_row_counter);
                $display("                      Data[0]=%d, Data[1]=%d",
                         tile_row_result_out[0*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH],
                         tile_row_result_out[1*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH]);
            end else if (prev_tile_row_result_valid === 1'b1 && tile_row_result_valid === 1'b0) begin // Falling edge
                $display("[%0t] [SA_DBG_CTRL_OUT_VALID_FALL] tile_row_result_valid changed from 1 to 0. FSM_State: %s, output_row_counter: %d",
                          $time, (output_fsm_state == FSM_OUT_IDLE ? "IDLE" : "STREAMING"), output_row_counter);
            end
        end
    end
`endif // DEBUG_SA_OUTPUT_CTRL

endmodule