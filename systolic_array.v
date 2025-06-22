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
                    .MAC_COUNT_TARGET(SIZE)
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
                    .result_valid(pe_result_valid_internal[r_gen][c_gen]),
                    .start_new_systolic_pass(start_new_systolic_pass)
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
            for (r_loop = 0; r_loop < SIZE; r_loop = r_loop + 1) begin // Use declared integer r_loop
                for (c_loop = 0; c_loop < SIZE; c_loop = c_loop + 1) begin // Use declared integer c_loop
                    pe_done_flags[r_loop][c_loop] <= 1'b0;
                end
            end
        end else if (start_new_systolic_pass) begin // Reset flags for a new computation pass
            for (r_loop = 0; r_loop < SIZE; r_loop = r_loop + 1) begin
                for (c_loop = 0; c_loop < SIZE; c_loop = c_loop + 1) begin
                    pe_done_flags[r_loop][c_loop] <= 1'b0;
                end
            end
        end else if (activate_pe_computation) begin // Only update done flags if computation is active
            for (r_loop = 0; r_loop < SIZE; r_loop = r_loop + 1) begin
                for (c_loop = 0; c_loop < SIZE; c_loop = c_loop + 1) begin
                    if (pe_result_valid_internal[r_loop][c_loop]) begin
                        pe_done_flags[r_loop][c_loop] <= 1'b1;
                    end
                end
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
endmodule
