`timescale 1ns / 1ps

module systolic_array #(
    parameter SIZE = 16,                    // Size of one dimension of the PE array
    parameter INPUT_DATA_WIDTH = 8,       // Width of A and B data fed to PEs (SINT8)
    parameter PE_ACCUM_DATA_WIDTH = 32    // Width of accumulator inside each PE (SINT32)
)(
    input wire clk,
    input wire rst_n,
    input wire clear_all_pe_accumulators,         // Pulse to PEs' clear_accumulator
    input wire conditionally_clear_pe_sums_level, // Level to PEs' conditionally_clear_sum
    input wire activate_pe_computation,          // General enable for PEs
    input wire array_data_valid_in,             // Valid for array_a_in and array_b_in

    input wire [SIZE*INPUT_DATA_WIDTH-1:0] array_a_in, // All A inputs for the boundary
    input wire [SIZE*INPUT_DATA_WIDTH-1:0] array_b_in, // All B inputs for the boundary

    input wire [$clog2(SIZE)-1:0] select_output_row_idx, // Selects which row of results to output
    input wire enable_tile_row_output,           // Enables outputting the selected row

    output wire array_a_data_valid_out,         // Valid for array_a_out
    output wire [SIZE*INPUT_DATA_WIDTH-1:0] array_a_out, // A data exiting the array
    output wire array_b_data_valid_out,         // Valid for array_b_out
    output wire [SIZE*INPUT_DATA_WIDTH-1:0] array_b_out, // B data exiting the array

    output reg signed [SIZE*PE_ACCUM_DATA_WIDTH-1:0] tile_row_result_out, // Selected row of results (SINT32 per element)
    output wire                               tile_row_result_valid,   // Valid for tile_row_result_out
    output wire                               tile_all_pes_done_one_pass, // High when all PEs have completed one pass (MAC_COUNT_TARGET ops)

    input wire start_new_systolic_pass       // Signal to reset PE done flags for a new computation pass
);

    // Data wires within the array
    wire signed [INPUT_DATA_WIDTH-1:0]   a_data_wires [SIZE-1:0][SIZE:0];
    wire signed [INPUT_DATA_WIDTH-1:0]   b_data_wires [SIZE:0][SIZE-1:0];
    wire                                 a_valid_wires [SIZE-1:0][SIZE:0];
    wire                                 b_valid_wires [SIZE:0][SIZE-1:0];

    // Boundary input registers for skewing data
    reg signed [INPUT_DATA_WIDTH-1:0]    a_boundary_data_regs [SIZE-1:0][SIZE-1:0];
    reg signed [INPUT_DATA_WIDTH-1:0]    b_boundary_data_regs [SIZE-1:0][SIZE-1:0];
    reg                                  a_boundary_valid_regs [SIZE-1:0][SIZE-1:0];
    reg                                  b_boundary_valid_regs [SIZE-1:0][SIZE-1:0];

    // Internal PE signals
    wire signed [PE_ACCUM_DATA_WIDTH-1:0] pe_result_out_internal [SIZE-1:0][SIZE-1:0];
    wire                                  pe_result_valid_internal [SIZE-1:0][SIZE-1:0];
    // NaN/Infinity signals removed

    // Loop variables for procedural blocks
    integer r_loop, c_loop, i_loop;
    integer i_col_local;
    integer r_idx_local_while, c_idx_local_while;

    // Genvar for generate blocks
    genvar r_gen, c_gen;

    // PE Done Flags (indicates a PE has pulsed its result_valid for the current pass)
    reg pe_done_flags [SIZE-1:0][SIZE-1:0];
    reg selected_row_all_pes_done;      // True if all PEs in the selected output row are done
    reg all_pes_in_tile_done_reduction; // True if all PEs in the entire tile are done

    // --- 1. Input Data and Valid Skewing Logic ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (r_loop = 0; r_loop < SIZE; r_loop = r_loop + 1) begin
                for (i_loop = 0; i_loop < SIZE; i_loop = i_loop + 1) begin
                    a_boundary_data_regs[r_loop][i_loop] <= {INPUT_DATA_WIDTH{1'b0}};
                    a_boundary_valid_regs[r_loop][i_loop] <= 1'b0;
                end
            end
        end else if (activate_pe_computation) begin // Only skew new data when computation is active
            for (r_loop = 0; r_loop < SIZE; r_loop = r_loop + 1) begin
                a_boundary_data_regs[r_loop][0] <= array_a_in[r_loop*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
                a_boundary_valid_regs[r_loop][0] <= array_data_valid_in;
                for (i_loop = 1; i_loop <= r_loop; i_loop = i_loop + 1) begin // Skewing
                    a_boundary_data_regs[r_loop][i_loop] <= a_boundary_data_regs[r_loop][i_loop-1];
                    a_boundary_valid_regs[r_loop][i_loop] <= a_boundary_valid_regs[r_loop][i_loop-1];
                end
                // For elements not yet receiving skewed data in this cycle, make them invalid
                for (i_loop = r_loop + 1; i_loop < SIZE; i_loop = i_loop + 1) begin
                     a_boundary_data_regs[r_loop][i_loop] <= {INPUT_DATA_WIDTH{1'b0}}; // Or keep old, but valid is key
                     a_boundary_valid_regs[r_loop][i_loop] <= 1'b0;
                end
            end
        end else begin // If not activating computation, keep valids low to avoid accidental PE operations
             for (r_loop = 0; r_loop < SIZE; r_loop = r_loop + 1) begin
                for (i_loop = 0; i_loop < SIZE; i_loop = i_loop + 1) begin
                    // a_boundary_data_regs[r_loop][i_loop] <= a_boundary_data_regs[r_loop][i_loop]; // Retain data
                    a_boundary_valid_regs[r_loop][i_loop] <= 1'b0; // Ensure valids are low
                end
            end
        end
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (c_loop = 0; c_loop < SIZE; c_loop = c_loop + 1) begin
                for (i_loop = 0; i_loop < SIZE; i_loop = i_loop + 1) begin
                    b_boundary_data_regs[c_loop][i_loop] <= {INPUT_DATA_WIDTH{1'b0}};
                    b_boundary_valid_regs[c_loop][i_loop] <= 1'b0;
                end
            end
        end else if (activate_pe_computation) begin // Only skew new data when computation is active
            for (c_loop = 0; c_loop < SIZE; c_loop = c_loop + 1) begin
                b_boundary_data_regs[c_loop][0] <= array_b_in[c_loop*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
                b_boundary_valid_regs[c_loop][0] <= array_data_valid_in;
                for (i_loop = 1; i_loop <= c_loop; i_loop = i_loop + 1) begin // Skewing
                    b_boundary_data_regs[c_loop][i_loop] <= b_boundary_data_regs[c_loop][i_loop-1];
                    b_boundary_valid_regs[c_loop][i_loop] <= b_boundary_valid_regs[c_loop][i_loop-1];
                end
                 // For elements not yet receiving skewed data in this cycle, make them invalid
                for (i_loop = c_loop + 1; i_loop < SIZE; i_loop = i_loop + 1) begin
                     b_boundary_data_regs[c_loop][i_loop] <= {INPUT_DATA_WIDTH{1'b0}};
                     b_boundary_valid_regs[c_loop][i_loop] <= 1'b0;
                end
            end
        end else begin // If not activating computation, keep valids low
             for (c_loop = 0; c_loop < SIZE; c_loop = c_loop + 1) begin
                for (i_loop = 0; i_loop < SIZE; i_loop = i_loop + 1) begin
                    // b_boundary_data_regs[c_loop][i_loop] <= b_boundary_data_regs[c_loop][i_loop]; // Retain data
                    b_boundary_valid_regs[c_loop][i_loop] <= 1'b0; // Ensure valids are low
                end
            end
        end
    end

    // --- 2. Boundary Input Connections to PE Array (Data and Valid) ---
    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : connect_a_to_pe_boundary
            assign a_data_wires[r_gen][0] = (r_gen < SIZE) ? a_boundary_data_regs[r_gen][r_gen] : {INPUT_DATA_WIDTH{1'b0}};
            assign a_valid_wires[r_gen][0] = (r_gen < SIZE) ? a_boundary_valid_regs[r_gen][r_gen] : 1'b0;
        end
        for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : connect_b_to_pe_boundary
            assign b_data_wires[0][c_gen] = (c_gen < SIZE) ? b_boundary_data_regs[c_gen][c_gen] : {INPUT_DATA_WIDTH{1'b0}};
            assign b_valid_wires[0][c_gen] = (c_gen < SIZE) ? b_boundary_valid_regs[c_gen][c_gen] : 1'b0;
        end
    endgenerate

    // --- 3. Core PE Array Instantiation ---
    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : pe_row
            for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : pe_col
                pe #(
                    .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH),
                    .ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH),
                    .MAC_COUNT_TARGET(SIZE), // Each PE performs SIZE MACs for one pass of a tile
                    .PE_ROW_ID(r_gen),
                    .PE_COL_ID(c_gen)
                ) u_pe_inst (
                    .clk(clk),
                    .rst_n(rst_n),
                    .enable(activate_pe_computation),
                    .clear_accumulator(clear_all_pe_accumulators),
                    .conditionally_clear_sum(conditionally_clear_pe_sums_level),
                    .a_valid_in(a_valid_wires[r_gen][c_gen]),
                    .a_data_in(a_data_wires[r_gen][c_gen]),
                    .a_valid_out(a_valid_wires[r_gen][c_gen+1]),
                    .a_data_out(a_data_wires[r_gen][c_gen+1]),
                    .b_valid_in(b_valid_wires[r_gen][c_gen]),
                    .b_data_in(b_data_wires[r_gen][c_gen]),
                    .b_valid_out(b_valid_wires[r_gen+1][c_gen]),
                    .b_data_out(b_data_wires[r_gen+1][c_gen]),
                    .result_out(pe_result_out_internal[r_gen][c_gen]),
                    .result_valid(pe_result_valid_internal[r_gen][c_gen])
                    // NaN/Inf ports removed
                );
            end
        end
    endgenerate

    // --- 4. Boundary Output Connections ---
    assign array_a_data_valid_out = (SIZE > 0) ? a_valid_wires[0][SIZE] : 1'b0; // Example: valid from first row's exit
    assign array_b_data_valid_out = (SIZE > 0) ? b_valid_wires[SIZE][0] : 1'b0; // Example: valid from first col's exit
    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : connect_a_output_stream
            assign array_a_out[r_gen*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] = a_data_wires[r_gen][SIZE];
        end
        for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : connect_b_output_stream
            assign array_b_out[c_gen*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] = b_data_wires[SIZE][c_gen];
        end
    endgenerate

    // --- 5. Row Result Output Logic ---
    always @(*) begin
        if (enable_tile_row_output && select_output_row_idx < SIZE) begin
            for (i_col_local = 0; i_col_local < SIZE; i_col_local = i_col_local + 1) begin
                tile_row_result_out[i_col_local*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] = pe_result_out_internal[select_output_row_idx][i_col_local];
            end
        end else begin
            tile_row_result_out = { (SIZE*PE_ACCUM_DATA_WIDTH) {1'bz}};
        end
    end

    // --- 6. Tile Status Logic: PE Done Flags and Overall Tile Completion ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            r_idx_local_while = 0;
            while (r_idx_local_while < SIZE) begin
                c_idx_local_while = 0;
                while (c_idx_local_while < SIZE) begin
                    pe_done_flags[r_idx_local_while][c_idx_local_while] <= 1'b0;
                    c_idx_local_while = c_idx_local_while + 1;
                end
                r_idx_local_while = r_idx_local_while + 1;
            end
        end else if (start_new_systolic_pass) begin // Reset flags for a new computation pass
            r_idx_local_while = 0;
            while (r_idx_local_while < SIZE) begin
                c_idx_local_while = 0;
                while (c_idx_local_while < SIZE) begin
                    pe_done_flags[r_idx_local_while][c_idx_local_while] <= 1'b0;
                    c_idx_local_while = c_idx_local_while + 1;
                end
                r_idx_local_while = r_idx_local_while + 1;
            end
        end else if (activate_pe_computation) begin // Only update done flags if computation is active
            r_idx_local_while = 0;
            while (r_idx_local_while < SIZE) begin
                c_idx_local_while = 0;
                while (c_idx_local_while < SIZE) begin
                    // A PE is considered "done" for this pass when its result_valid pulses high
                    if (pe_result_valid_internal[r_idx_local_while][c_idx_local_while]) begin
                        pe_done_flags[r_idx_local_while][c_idx_local_while] <= 1'b1;
                    end
                    // Note: pe_done_flags remain latched high until start_new_systolic_pass
                    c_idx_local_while = c_idx_local_while + 1;
                end
                r_idx_local_while = r_idx_local_while + 1;
            end
        end
    end

    // Combinational logic to check if the selected row's PEs are all done
    always@(*) begin
        selected_row_all_pes_done = 1'b1; // Assume true
        if (enable_tile_row_output && select_output_row_idx < SIZE) begin
            for(i_col_local = 0; i_col_local < SIZE; i_col_local = i_col_local + 1) begin
                if(!pe_done_flags[select_output_row_idx][i_col_local]) begin
                    selected_row_all_pes_done = 1'b0;
                    // break; // Verilog doesn't have break in for-loops for synthesis
                end
            end
        end else begin
            selected_row_all_pes_done = 1'b0; // Not enabled or invalid row
        end
    end
    assign tile_row_result_valid = enable_tile_row_output && selected_row_all_pes_done;

    // Combinational logic to check if ALL PEs in the entire tile are done for the current pass
    always@(*) begin
        integer r_loop_comb, c_loop_comb;
        all_pes_in_tile_done_reduction = 1'b1; // Assume true
        if (SIZE == 0) begin
            all_pes_in_tile_done_reduction = 1'b1; // Or 1'b0 depending on definition for empty array
        end else begin
            for (r_loop_comb = 0; r_loop_comb < SIZE; r_loop_comb = r_loop_comb + 1) begin
                for (c_loop_comb = 0; c_loop_comb < SIZE; c_loop_comb = c_loop_comb + 1) begin
                    if (!pe_done_flags[r_loop_comb][c_loop_comb]) begin
                        all_pes_in_tile_done_reduction = 1'b0;
                        // No break needed, assignment will ensure it stays 0 if any PE is not done
                    end
                end
                if(!all_pes_in_tile_done_reduction) begin
                    // Optimization for simulation, won't synthesize to early exit typically
                end
            end
        end
    end
    assign tile_all_pes_done_one_pass = all_pes_in_tile_done_reduction;

    // --- STROBE FOR SYSTOLIC ARRAY BOUNDARY INPUTS ---
    // This always block is purely for simulation debugging.
    // It will strobe the data and valid signals being fed into the first row/column PEs
    // when the array is active and new data is asserted as valid.
    // always @(posedge clk) begin
    //     if (rst_n && activate_pe_computation && array_data_valid_in) begin
    //         Strobe inputs for PE(0,0)
    //         if (SIZE > 0) begin
    //             $strobe("@%0t [SA_BOUNDARY_IN] PE(0,0) <-- A_data: %d (v:%b), B_data: %d (v:%b)",
    //                 $time,
    //                 a_data_wires[0][0], a_valid_wires[0][0],
    //                 b_data_wires[0][0], b_valid_wires[0][0]
    //             );
    //         end

    //         // Strobe inputs for PE(SIZE-1, 0) for A, and PE(0, SIZE-1) for B
    //         // These are relevant for understanding data flow to other corners/edges.
    //         // For your B[15][0]=2 test case, PE(15,0) is important for B.
    //         // Data for B[15][0] will eventually reach b_data_in of PE(15,0)
    //         // after passing through PE(0,0), PE(1,0) ... PE(14,0).
    //         // The a_data_wires[SIZE-1][0] is the A input to PE(SIZE-1,0).
    //         // The b_data_wires[0][SIZE-1] is the B input to PE(0,SIZE-1).

    //         // We are primarily interested in what B data enters the array along the top edge
    //         // for the column that will eventually meet B[15][0] if it were propagating.
    //         // However, B[15][0] itself is fed through array_b_in[0*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH]
    //         // after appropriate skewing if accelerator feeds B column-wise and SA skews it.
    //         // Let's re-check how B is fed from accelerator:
    //         // accelerator.v: current_b_row_for_feed feeds sa_array_b_in_wire_systolic
    //         // sa_array_b_in_wire_systolic becomes array_b_in for systolic_array.
    //         // array_b_in is then skewed by b_boundary_data_regs.
    //         // b_data_wires[0][c_gen] = b_boundary_data_regs[c_gen][c_gen];

    //         // So, if B[15][0] = 2, and array_b_in represents rows of B to be skewed,
    //         // then array_b_in should contain the 15th row of B at some point.
    //         // The element b_boundary_data_regs[0][0] will get array_b_in[0*WIDTH...].
    //         // The element b_data_wires[0][0] (for PE(0,0)) will get data from array_b_in that was skewed for it.

    //         // Let's print the raw array_b_in to see what the SA is receiving from accelerator
    //         if (SIZE > 0) begin
    //             $strobe("@%0t [SA_RAW_B_IN] array_b_in[0]: %d, array_b_in[last_elem_of_first_word]: %d",
    //                 $time,
    //                 array_b_in[INPUT_DATA_WIDTH-1:0], // First SINT8 of array_b_in
    //                 (SIZE*INPUT_DATA_WIDTH >= (SIZE-1)*INPUT_DATA_WIDTH + INPUT_DATA_WIDTH) ? // Check bounds
    //                     array_b_in[(SIZE*INPUT_DATA_WIDTH-1) -: INPUT_DATA_WIDTH] : {{INPUT_DATA_WIDTH}{1'bx}} // Last SINT8 of array_b_in
    //             );
    //         end


    //         // Print what PE(15,0) gets for B. This will be delayed due to propagation.
    //         // This specific strobe might be better inside the PE itself as you've done.
    //         // For here, let's focus on what enters the array at the boundaries.
    //         if (SIZE > 15) begin // Specifically for 16x16 case to see last relevant boundary inputs
    //             // A input to PE(15,0)
    //             $strobe("@%0t [SA_BOUNDARY_IN] PE(15,0) <-- A_data: %d (v:%b)",
    //                 $time,
    //                 a_data_wires[15][0], a_valid_wires[15][0]
    //             );
    //             // B input to PE(0,15)
    //             $strobe("@%0t [SA_BOUNDARY_IN] PE(0,15) <-- B_data: %d (v:%b)",
    //                 $time,
    //                 b_data_wires[0][15], b_valid_wires[0][15]
    //             );
    //         end
    //     end
    // end
    // --- END STROBE ---

endmodule