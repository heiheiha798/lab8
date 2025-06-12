`timescale 1ns / 1ps

module systolic_array #(
    parameter SIZE = 16,
    parameter DATA_WIDTH = 16
)(
    input wire clk,
    input wire rst_n,
    input wire clear_all_pe_accumulators,
    input wire activate_pe_computation,     // General enable for computation phase
    input wire array_data_valid_in,         // NEW: Indicates if array_a_in and array_b_in are valid this cycle

    input wire [SIZE*DATA_WIDTH-1:0] array_a_in,
    input wire [SIZE*DATA_WIDTH-1:0] array_b_in,

    input wire [$clog2(SIZE)-1:0] select_output_row_idx,
    input wire enable_tile_row_output,

    output wire array_a_data_valid_out,     // NEW: Valid signal for array_a_out
    output wire [SIZE*DATA_WIDTH-1:0] array_a_out,
    output wire array_b_data_valid_out,     // NEW: Valid signal for array_b_out
    output wire [SIZE*DATA_WIDTH-1:0] array_b_out,

    output reg  [SIZE*DATA_WIDTH-1:0] tile_row_result_out,
    output wire                       tile_row_result_valid, // Valid for the selected output row
    output wire                       tile_all_pes_done_one_pass, // All PEs have completed their MAC_COUNT_TARGET
    output wire                       tile_had_nan,
    output wire                       tile_had_inf,
    input wire accelerator_is_computing // Keep for now, might be redundant with activate_pe_computation
);

    // Data wires
    wire [DATA_WIDTH-1:0] a_data_wires [SIZE-1:0][SIZE:0];
    wire [DATA_WIDTH-1:0] b_data_wires [SIZE:0][SIZE-1:0];

    // Valid signal wires (mirroring data wires)
    wire                  a_valid_wires [SIZE-1:0][SIZE:0];
    wire                  b_valid_wires [SIZE:0][SIZE-1:0];

    // Boundary input registers for data
    reg [DATA_WIDTH-1:0] a_boundary_data_regs [SIZE-1:0][SIZE-1:0]; // Renamed for clarity
    reg [DATA_WIDTH-1:0] b_boundary_data_regs [SIZE-1:0][SIZE-1:0]; // Renamed for clarity

    // Boundary input registers for valid signals
    reg                  a_boundary_valid_regs [SIZE-1:0][SIZE-1:0];
    reg                  b_boundary_valid_regs [SIZE-1:0][SIZE-1:0];

    // Internal PE signals
    wire [DATA_WIDTH-1:0] pe_result_out_internal [SIZE-1:0][SIZE-1:0];
    wire                  pe_result_valid_internal [SIZE-1:0][SIZE-1:0]; // This is the pulse when a PE finishes
    wire                  pe_is_nan_internal [SIZE-1:0][SIZE-1:0];
    wire                  pe_is_infinity_internal [SIZE-1:0][SIZE-1:0];

    // Loop variables
    integer r_loop, c_loop, i_loop;
    integer i_col_local, r_idx_local, c_idx_local;

    // Genvar
    genvar r_gen, c_gen;

    // --- 1. Input Data and Valid Skewing Logic ---
    // Skewing for A data and A valid
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (r_loop = 0; r_loop < SIZE; r_loop = r_loop + 1) begin
                for (i_loop = 0; i_loop < SIZE; i_loop = i_loop + 1) begin
                    a_boundary_data_regs[r_loop][i_loop] <= {DATA_WIDTH{1'b0}};
                    a_boundary_valid_regs[r_loop][i_loop] <= 1'b0;
                end
            end
        end else if (activate_pe_computation) begin // Skewing active only during computation phase
            for (r_loop = 0; r_loop < SIZE; r_loop = r_loop + 1) begin
                // Load first stage of skew registers
                a_boundary_data_regs[r_loop][0] <= array_a_in[r_loop*DATA_WIDTH +: DATA_WIDTH];
                a_boundary_valid_regs[r_loop][0] <= array_data_valid_in; // Assuming a single valid for both A and B rows/cols from input

                // Shift data and valid through skew registers
                for (i_loop = 1; i_loop <= r_loop; i_loop = i_loop + 1) begin
                    a_boundary_data_regs[r_loop][i_loop] <= a_boundary_data_regs[r_loop][i_loop-1];
                    a_boundary_valid_regs[r_loop][i_loop] <= a_boundary_valid_regs[r_loop][i_loop-1];
                end
            end
        end else begin // If not activating computation, ensure valids don't persist misleadingly
            for (r_loop = 0; r_loop < SIZE; r_loop = r_loop + 1) begin
                for (i_loop = 0; i_loop < SIZE; i_loop = i_loop + 1) begin
                    // Or hold previous values if that's the desired idle behavior
                    a_boundary_valid_regs[r_loop][i_loop] <= 1'b0;
                end
            end
        end
    end

    // Skewing for B data and B valid
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (c_loop = 0; c_loop < SIZE; c_loop = c_loop + 1) begin
                for (i_loop = 0; i_loop < SIZE; i_loop = i_loop + 1) begin
                    b_boundary_data_regs[c_loop][i_loop] <= {DATA_WIDTH{1'b0}};
                    b_boundary_valid_regs[c_loop][i_loop] <= 1'b0;
                end
            end
        end else if (activate_pe_computation) begin // Skewing active only during computation phase
            for (c_loop = 0; c_loop < SIZE; c_loop = c_loop + 1) begin
                // Load first stage of skew registers
                b_boundary_data_regs[c_loop][0] <= array_b_in[c_loop*DATA_WIDTH +: DATA_WIDTH];
                b_boundary_valid_regs[c_loop][0] <= array_data_valid_in; // Assuming a single valid

                // Shift data and valid through skew registers
                for (i_loop = 1; i_loop <= c_loop; i_loop = i_loop + 1) begin
                    b_boundary_data_regs[c_loop][i_loop] <= b_boundary_data_regs[c_loop][i_loop-1];
                    b_boundary_valid_regs[c_loop][i_loop] <= b_boundary_valid_regs[c_loop][i_loop-1];
                end
            end
        end else begin // If not activating computation, ensure valids don't persist misleadingly
             for (c_loop = 0; c_loop < SIZE; c_loop = c_loop + 1) begin
                for (i_loop = 0; i_loop < SIZE; i_loop = i_loop + 1) begin
                    b_boundary_valid_regs[c_loop][i_loop] <= 1'b0;
                end
            end
        end
    end

    // --- 2. Boundary Input Connections to PE Array (Data and Valid) ---
    generate
        // Connect A data and valid to the first column of PEs
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : connect_a_to_pe_boundary
            assign a_data_wires[r_gen][0] = a_boundary_data_regs[r_gen][r_gen];
            assign a_valid_wires[r_gen][0] = a_boundary_valid_regs[r_gen][r_gen];
        end
        // Connect B data and valid to the first row of PEs
        for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : connect_b_to_pe_boundary
            assign b_data_wires[0][c_gen] = b_boundary_data_regs[c_gen][c_gen];
            assign b_valid_wires[0][c_gen] = b_boundary_valid_regs[c_gen][c_gen];
        end
    endgenerate

    // --- 3. Core PE Array Instantiation ---
    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : pe_row
            for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : pe_col
                pe #(
                    .DATA_WIDTH(DATA_WIDTH),
                    .MAC_COUNT_TARGET(SIZE),    // Each PE performs SIZE MAC operations
                    .PE_ROW_ID(r_gen),
                    .PE_COL_ID(c_gen)
                ) u_pe_inst (
                    .clk(clk),
                    .rst_n(rst_n),
                    .enable(activate_pe_computation), // PE is active if the array is active
                    .clear_accumulator(clear_all_pe_accumulators),

                    .a_valid_in(a_valid_wires[r_gen][c_gen]),
                    .a_data_in(a_data_wires[r_gen][c_gen]),
                    .a_valid_out(a_valid_wires[r_gen][c_gen+1]),
                    .a_data_out(a_data_wires[r_gen][c_gen+1]),

                    .b_valid_in(b_valid_wires[r_gen][c_gen]),
                    .b_data_in(b_data_wires[r_gen][c_gen]),
                    .b_valid_out(b_valid_wires[r_gen+1][c_gen]),
                    .b_data_out(b_data_wires[r_gen+1][c_gen]),

                    .result_out(pe_result_out_internal[r_gen][c_gen]),
                    .result_valid(pe_result_valid_internal[r_gen][c_gen]), // Pulse when this PE is done
                    .pe_is_nan(pe_is_nan_internal[r_gen][c_gen]),
                    .pe_is_infinity(pe_is_infinity_internal[r_gen][c_gen])
                );
            end
        end
    endgenerate

    // --- 4. Boundary Output Connections for A and B Data and Valid Streams ---
    // Collect A data and valid from the last column of PEs
    // For simplicity, array_a_data_valid_out can be a reduction (OR or AND)
    // or just the valid from a specific PE, e.g., PE[0][SIZE-1]'s a_valid_out.
    // Here, let's just take one valid signal as representative. A more robust
    // system might require all output valids to be high or a counter.
    // For now, let's assume the valid signal propagates with the data.
    // The last PE in row r_gen will output its a_valid_out at a_valid_wires[r_gen][SIZE]
    // A single array_a_data_valid_out could be, for example, a_valid_wires[0][SIZE]
    // or an OR reduction if any output row is valid.
    // Let's make it simple for now: valid if the first row's output data is valid.
    // This part needs careful consideration based on how downstream modules use these valids.
    // A simple approach: output valid is just the valid signal accompanying the last piece of data.
    assign array_a_data_valid_out = a_valid_wires[0][SIZE]; // Example: valid of A data from PE[0][SIZE-1]
    assign array_b_data_valid_out = b_valid_wires[SIZE][0]; // Example: valid of B data from PE[SIZE-1][0]

    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : connect_a_output_stream
            assign array_a_out[r_gen*DATA_WIDTH +: DATA_WIDTH] = a_data_wires[r_gen][SIZE];
        end
        for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : connect_b_output_stream
            assign array_b_out[c_gen*DATA_WIDTH +: DATA_WIDTH] = b_data_wires[SIZE][c_gen];
        end
    endgenerate

    // --- 5. Row Result Output Logic (Unchanged, relies on pe_done_flags) ---
    always @(*) begin
        if (enable_tile_row_output) begin
            for (i_col_local = 0; i_col_local < SIZE; i_col_local = i_col_local + 1) begin
                tile_row_result_out[i_col_local*DATA_WIDTH +: DATA_WIDTH] = pe_result_out_internal[select_output_row_idx][i_col_local];
            end
        end else begin
            tile_row_result_out = { (SIZE*DATA_WIDTH) {1'bz}};
        end
    end

    // --- 6. Tile Status Logic ---
    // pe_done_flags tracks if a PE has pulsed its result_valid, meaning it completed its MAC_COUNT_TARGET ops.
    reg pe_done_flags [SIZE-1:0][SIZE-1:0];
    reg selected_row_all_pes_done; // Changed name for clarity

    // Combinational logic to check if all PEs in the currently selected output row are done
    always@(*) begin
        selected_row_all_pes_done = 1'b1; // Assume done
        if (enable_tile_row_output) begin // Only if we are trying to output this row
            for(i_col_local = 0; i_col_local < SIZE; i_col_local = i_col_local + 1) begin
                if(!pe_done_flags[select_output_row_idx][i_col_local]) begin
                    selected_row_all_pes_done = 1'b0;
                    // break; // Verilog doesn't have break in always@(*) for synthesis
                end
            end
        end else begin
            selected_row_all_pes_done = 1'b0; // If not enabling output, row is not considered "validly outputtable"
        end
    end
    assign tile_row_result_valid = enable_tile_row_output && selected_row_all_pes_done;

    // Sequential logic to latch when each PE pulses its result_valid
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (r_idx_local = 0; r_idx_local < SIZE; r_idx_local = r_idx_local + 1) begin
                for (c_idx_local = 0; c_idx_local < SIZE; c_idx_local = c_idx_local + 1) begin
                    pe_done_flags[r_idx_local][c_idx_local] <= 1'b0;
                end
            end
        end else if (clear_all_pe_accumulators) begin // Reset done flags when clearing PEs
            for (r_idx_local = 0; r_idx_local < SIZE; r_idx_local = r_idx_local + 1) begin
                for (c_idx_local = 0; c_idx_local < SIZE; c_idx_local = c_idx_local + 1) begin
                    pe_done_flags[r_idx_local][c_idx_local] <= 1'b0;
                end
            end
        end else if (activate_pe_computation) begin // Only update flags during computation phase
            for (r_idx_local = 0; r_idx_local < SIZE; r_idx_local = r_idx_local + 1) begin
                for (c_idx_local = 0; c_idx_local < SIZE; c_idx_local = c_idx_local + 1) begin
                    // If a PE signals its result is valid, latch that it's done for this pass.
                    // Don't clear the flag until clear_all_pe_accumulators.
                    if (pe_result_valid_internal[r_idx_local][c_idx_local]) begin
                        pe_done_flags[r_idx_local][c_idx_local] <= 1'b1;
                    end
                end
            end
        end
    end

    // Combinational logic to check if ALL PEs in the entire tile are done
    reg all_pes_in_tile_done_reduction;
    always@(*) begin
        all_pes_in_tile_done_reduction = 1'b1; // Assume all done
        for (r_idx_local = 0; r_idx_local < SIZE; r_idx_local = r_idx_local + 1) begin
            for (c_idx_local = 0; c_idx_local < SIZE; c_idx_local = c_idx_local + 1) begin
                if (!pe_done_flags[r_idx_local][c_idx_local]) begin
                    all_pes_in_tile_done_reduction = 1'b0;
                    // Could add break-like logic here for optimization if needed,
                    // by setting loop indices to their max, but for clarity, let it run.
                end
            end
            if (!all_pes_in_tile_done_reduction) begin
                // break outer loop (conceptual)
            end
        end
    end
    assign tile_all_pes_done_one_pass = all_pes_in_tile_done_reduction;

    // tile_had_nan and tile_had_inf logic (unchanged, but now based on PE's internal state after MAC_COUNT_TARGET ops)
    reg tile_had_nan_comb;
    reg tile_had_inf_comb;
    always@(*) begin
        tile_had_nan_comb = 1'b0;
        tile_had_inf_comb = 1'b0;
        for (r_idx_local = 0; r_idx_local < SIZE; r_idx_local = r_idx_local + 1) begin
            for (c_idx_local = 0; c_idx_local < SIZE; c_idx_local = c_idx_local + 1) begin
                if (pe_is_nan_internal[r_idx_local][c_idx_local]) tile_had_nan_comb = 1'b1;
                if (pe_is_infinity_internal[r_idx_local][c_idx_local]) tile_had_inf_comb = 1'b1;
            end
        end
    end
    assign tile_had_nan = tile_had_nan_comb;
    assign tile_had_inf = tile_had_inf_comb;

endmodule