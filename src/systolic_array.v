`timescale 1ns / 1ps

module systolic_array #(
    parameter SIZE = 16,
    parameter DATA_WIDTH = 16
)(
    input wire clk,
    input wire rst_n,
    input wire clear_all_pe_accumulators,
    input wire conditionally_clear_pe_sums_level,
    input wire activate_pe_computation,
    input wire array_data_valid_in,
    input wire [SIZE*DATA_WIDTH-1:0] array_a_in,
    input wire [SIZE*DATA_WIDTH-1:0] array_b_in,
    input wire [$clog2(SIZE)-1:0] select_output_row_idx,
    input wire enable_tile_row_output,
    output wire array_a_data_valid_out,
    output wire [SIZE*DATA_WIDTH-1:0] array_a_out,
    output wire array_b_data_valid_out,
    output wire [SIZE*DATA_WIDTH-1:0] array_b_out,
    output reg  [SIZE*DATA_WIDTH-1:0] tile_row_result_out,
    output wire                       tile_row_result_valid,
    output wire                       tile_all_pes_done_one_pass,
    output wire                       tile_had_nan,
    output wire                       tile_had_inf,
    input wire accelerator_is_computing,
    input wire start_new_systolic_pass
);

    // Data wires
    wire [DATA_WIDTH-1:0] a_data_wires [SIZE-1:0][SIZE:0];
    wire [DATA_WIDTH-1:0] b_data_wires [SIZE:0][SIZE-1:0];
    wire                  a_valid_wires [SIZE-1:0][SIZE:0];
    wire                  b_valid_wires [SIZE:0][SIZE-1:0];

    // Boundary input registers for data
    reg [DATA_WIDTH-1:0] a_boundary_data_regs [SIZE-1:0][SIZE-1:0];
    reg [DATA_WIDTH-1:0] b_boundary_data_regs [SIZE-1:0][SIZE-1:0];
    reg                  a_boundary_valid_regs [SIZE-1:0][SIZE-1:0];
    reg                  b_boundary_valid_regs [SIZE-1:0][SIZE-1:0];

    // Internal PE signals
    wire [DATA_WIDTH-1:0] pe_result_out_internal [SIZE-1:0][SIZE-1:0];
    wire                  pe_result_valid_internal [SIZE-1:0][SIZE-1:0];
    wire                  pe_is_nan_internal [SIZE-1:0][SIZE-1:0];
    wire                  pe_is_infinity_internal [SIZE-1:0][SIZE-1:0];

    // Loop variables for procedural blocks
    integer r_loop, c_loop, i_loop;
    integer i_col_local; 
    // r_idx_local, c_idx_local will be used for while loops now, ensure they are reset correctly
    integer r_idx_local_while, c_idx_local_while;


    // Genvar for generate blocks
    genvar r_gen, c_gen;

    // PE Done Flags
    reg pe_done_flags [SIZE-1:0][SIZE-1:0];
    reg selected_row_all_pes_done;
    reg all_pes_in_tile_done_reduction; 
    reg tile_had_nan_comb;
    reg tile_had_inf_comb;

    // --- DEBUG ADDITIONS START ----
    reg prev_pe00_done_flag_dbg;
    reg prev_pe01_done_flag_dbg;
    reg prev_pe10_done_flag_dbg;
    reg prev_peLL_done_flag_dbg; 
    reg prev_all_done_reduction_dbg;
    reg prev_start_new_systolic_pass_dbg; // For rising edge detection
    reg prev_activate_pe_computation_dbg;

    initial begin
        if (SIZE > 0) prev_pe00_done_flag_dbg = 1'b0;
        if (SIZE > 1) prev_pe01_done_flag_dbg = 1'b0;
        if (SIZE > 1) prev_pe10_done_flag_dbg = 1'b0;
        if (SIZE > 0) prev_peLL_done_flag_dbg = 1'b0;
        prev_all_done_reduction_dbg = 1'b0;
        prev_start_new_systolic_pass_dbg = 1'b0;
        prev_activate_pe_computation_dbg = 1'b0;
        // $strobe("@%0t [SA_INIT] Systolic Array Instantiated with SIZE = %d, DATA_WIDTH = %d", $time, SIZE, DATA_WIDTH);
    end
    // --- DEBUG ADDITIONS END ----


    // --- 1. Input Data and Valid Skewing Logic (using for loops here is fine as it's standard synthesis construct) ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (r_loop = 0; r_loop < SIZE; r_loop = r_loop + 1) begin
                for (i_loop = 0; i_loop < SIZE; i_loop = i_loop + 1) begin
                    a_boundary_data_regs[r_loop][i_loop] <= {DATA_WIDTH{1'b0}};
                    a_boundary_valid_regs[r_loop][i_loop] <= 1'b0;
                end
            end
        end else if (activate_pe_computation) begin
            for (r_loop = 0; r_loop < SIZE; r_loop = r_loop + 1) begin
                a_boundary_data_regs[r_loop][0] <= array_a_in[r_loop*DATA_WIDTH +: DATA_WIDTH];
                a_boundary_valid_regs[r_loop][0] <= array_data_valid_in;
                for (i_loop = 1; i_loop <= r_loop; i_loop = i_loop + 1) begin
                    a_boundary_data_regs[r_loop][i_loop] <= a_boundary_data_regs[r_loop][i_loop-1];
                    a_boundary_valid_regs[r_loop][i_loop] <= a_boundary_valid_regs[r_loop][i_loop-1];
                end
            end
        end else begin 
             for (r_loop = 0; r_loop < SIZE; r_loop = r_loop + 1) begin
                for (i_loop = 0; i_loop < SIZE; i_loop = i_loop + 1) begin 
                    a_boundary_valid_regs[r_loop][i_loop] <= 1'b0;
                end
            end
        end
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (c_loop = 0; c_loop < SIZE; c_loop = c_loop + 1) begin
                for (i_loop = 0; i_loop < SIZE; i_loop = i_loop + 1) begin
                    b_boundary_data_regs[c_loop][i_loop] <= {DATA_WIDTH{1'b0}};
                    b_boundary_valid_regs[c_loop][i_loop] <= 1'b0;
                end
            end
        end else if (activate_pe_computation) begin
            for (c_loop = 0; c_loop < SIZE; c_loop = c_loop + 1) begin
                b_boundary_data_regs[c_loop][0] <= array_b_in[c_loop*DATA_WIDTH +: DATA_WIDTH];
                b_boundary_valid_regs[c_loop][0] <= array_data_valid_in;
                for (i_loop = 1; i_loop <= c_loop; i_loop = i_loop + 1) begin
                    b_boundary_data_regs[c_loop][i_loop] <= b_boundary_data_regs[c_loop][i_loop-1];
                    b_boundary_valid_regs[c_loop][i_loop] <= b_boundary_valid_regs[c_loop][i_loop-1];
                end
            end
        end else begin 
             for (c_loop = 0; c_loop < SIZE; c_loop = c_loop + 1) begin
                for (i_loop = 0; i_loop < SIZE; i_loop = i_loop + 1) begin 
                    b_boundary_valid_regs[c_loop][i_loop] <= 1'b0;
                end
            end
        end
    end

    // --- 2. Boundary Input Connections to PE Array (Data and Valid) ---
    // (generate blocks are fine)
    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : connect_a_to_pe_boundary
            assign a_data_wires[r_gen][0] = a_boundary_data_regs[r_gen][r_gen];
            assign a_valid_wires[r_gen][0] = a_boundary_valid_regs[r_gen][r_gen];
        end
        for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : connect_b_to_pe_boundary
            assign b_data_wires[0][c_gen] = b_boundary_data_regs[c_gen][c_gen];
            assign b_valid_wires[0][c_gen] = b_boundary_valid_regs[c_gen][c_gen];
        end
    endgenerate

    // --- 3. Core PE Array Instantiation ---
    // (generate blocks are fine)
    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : pe_row
            for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : pe_col
                // ... (PE instantiation remains the same) ...
                pe #(
                    .DATA_WIDTH(DATA_WIDTH),
                    .MAC_COUNT_TARGET(SIZE),
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
                    .result_valid(pe_result_valid_internal[r_gen][c_gen]),
                    .pe_is_nan(pe_is_nan_internal[r_gen][c_gen]),
                    .pe_is_infinity(pe_is_infinity_internal[r_gen][c_gen])
                );
            end
        end
    endgenerate

    // --- 4. Boundary Output Connections ---
    // (generate blocks are fine)
    assign array_a_data_valid_out = (SIZE > 0) ? a_valid_wires[0][SIZE] : 1'b0;
    assign array_b_data_valid_out = (SIZE > 0) ? b_valid_wires[SIZE][0] : 1'b0;
    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : connect_a_output_stream
            assign array_a_out[r_gen*DATA_WIDTH +: DATA_WIDTH] = a_data_wires[r_gen][SIZE];
        end
        for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : connect_b_output_stream
            assign array_b_out[c_gen*DATA_WIDTH +: DATA_WIDTH] = b_data_wires[SIZE][c_gen];
        end
    endgenerate

    // --- 5. Row Result Output Logic ---
    // (using for loop here in combinational block is fine)
    always @(*) begin
        if (enable_tile_row_output && select_output_row_idx < SIZE) begin
            for (i_col_local = 0; i_col_local < SIZE; i_col_local = i_col_local + 1) begin
                tile_row_result_out[i_col_local*DATA_WIDTH +: DATA_WIDTH] = pe_result_out_internal[select_output_row_idx][i_col_local];
            end
        end else begin
            tile_row_result_out = { (SIZE*DATA_WIDTH) {1'bz}};
        end
    end

    // --- 6. Tile Status Logic ---
    // (using for loop here in combinational block is fine)
    always@(*) begin
        selected_row_all_pes_done = 1'b1;
        if (enable_tile_row_output && select_output_row_idx < SIZE) begin
            for(i_col_local = 0; i_col_local < SIZE; i_col_local = i_col_local + 1) begin
                if(!pe_done_flags[select_output_row_idx][i_col_local]) begin
                    selected_row_all_pes_done = 1'b0;
                end
            end
        end else begin
            selected_row_all_pes_done = 1'b0;
        end
    end
    assign tile_row_result_valid = enable_tile_row_output && selected_row_all_pes_done;

    // --- MODIFIED: Update pe_done_flags using while loops ---
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // Initialize r_idx_local_while and c_idx_local_while for reset loop
            r_idx_local_while = 0;
            while (r_idx_local_while < SIZE) begin
                c_idx_local_while = 0;
                while (c_idx_local_while < SIZE) begin
                    pe_done_flags[r_idx_local_while][c_idx_local_while] <= 1'b0;
                    c_idx_local_while = c_idx_local_while + 1;
                end
                r_idx_local_while = r_idx_local_while + 1;
            end
        end else if (start_new_systolic_pass) begin
            // if (!prev_start_new_systolic_pass_dbg && start_new_systolic_pass) begin // Strobe on rising edge
            //     $strobe("@%0t [SA_PASS_CTRL] start_new_systolic_pass asserted. All pe_done_flags cleared.", $time);
            // end
            // Initialize r_idx_local_while and c_idx_local_while for this branch
            r_idx_local_while = 0;
            while (r_idx_local_while < SIZE) begin
                c_idx_local_while = 0;
                while (c_idx_local_while < SIZE) begin
                    pe_done_flags[r_idx_local_while][c_idx_local_while] <= 1'b0;
                    c_idx_local_while = c_idx_local_while + 1;
                end
                r_idx_local_while = r_idx_local_while + 1;
            end
        end else if (activate_pe_computation) begin 
            // Initialize r_idx_local_while and c_idx_local_while for this branch
            r_idx_local_while = 0;
            while (r_idx_local_while < SIZE) begin
                c_idx_local_while = 0;
                while (c_idx_local_while < SIZE) begin
                    // Strobe to check pe_result_valid_internal before the if
                    // if ( (r_idx_local_while == 0 && c_idx_local_while == 0 && $time >= 2820000 && $time <= 2850000) || // PE(0,0) around its first expected completion
                    //      (r_idx_local_while == SIZE-1 && c_idx_local_while == SIZE-1)) begin
                    //      $strobe("@%0t [SA_VALID_CHECK] r%0d c%0d (act:%b): pe_rv_in[%d][%d]=%b, cur_done_flag=%b",
                    //              $time, r_idx_local_while, c_idx_local_while, activate_pe_computation,
                    //              r_idx_local_while, c_idx_local_while, pe_result_valid_internal[r_idx_local_while][c_idx_local_while],
                    //              pe_done_flags[r_idx_local_while][c_idx_local_while]);
                    // end

                    if (pe_result_valid_internal[r_idx_local_while][c_idx_local_while]) begin 
                        // if (!pe_done_flags[r_idx_local_while][c_idx_local_while]) begin // Only strobe if it's changing to 1
                        //     if ((r_idx_local_while < 2 && c_idx_local_while < 2) || 
                        //         (r_idx_local_while == SIZE-1 && c_idx_local_while == SIZE-1 && SIZE > 0)) begin
                        //         $strobe("@%0t [SA_PE_DONE_SETTING] PE[%0d][%0d] result_valid_internal is HIGH. Setting pe_done_flags to 1.",
                        //                 $time, r_idx_local_while, c_idx_local_while); 
                        //     end
                        // end
                        pe_done_flags[r_idx_local_while][c_idx_local_while] <= 1'b1;
                    end
                    c_idx_local_while = c_idx_local_while + 1;
                end
                r_idx_local_while = r_idx_local_while + 1;
            end
        end
    end

    // Combinational logic to check if ALL PEs in the entire tile are done
    // (using for loop here in combinational block is fine)
    // Combinational logic to check if ALL PEs in the entire tile are done
    always@(*) begin
        integer r_loop_comb, c_loop_comb; // Declare loop variables LOCAL to this combinational block

        all_pes_in_tile_done_reduction = 1'b1; // Assume true initially
        if (SIZE == 0) begin 
            all_pes_in_tile_done_reduction = 1'b1; 
        end else begin
            // Use a for loop here since it's combinational logic and should be unrolled by synthesis/Verilator correctly.
            // The previous bug was specific to for loops in sequential (clocked) always blocks with integer loop variables.
            for (r_loop_comb = 0; r_loop_comb < SIZE; r_loop_comb = r_loop_comb + 1) begin
                for (c_loop_comb = 0; c_loop_comb < SIZE; c_loop_comb = c_loop_comb + 1) begin
                    if (!pe_done_flags[r_loop_comb][c_loop_comb]) begin
                        all_pes_in_tile_done_reduction = 1'b0;
                        // No 'break' in synthesizable Verilog for loops, but we can stop further checks
                        // by breaking the outer loop if all_pes_in_tile_done_reduction is already 0.
                        // However, for clarity and to ensure all paths are considered by linters/synthesis,
                        // it's often fine to let it complete.
                    end
                end
                if (!all_pes_in_tile_done_reduction) begin 
                    // This is an optimization for simulation or if synthesis can infer early exit.
                    // For Verilog, the outer loop will complete its iterations regardless of this 'break' comment.
                    // The effect is that once all_pes_in_tile_done_reduction is 0, it stays 0.
                end
            end
        end
    end
    assign tile_all_pes_done_one_pass = all_pes_in_tile_done_reduction;

    // tile_had_nan and tile_had_inf logic
    // (using for loop here in combinational block is fine)
    integer r_naninf, c_naninf; // Local integers for this block

    always@(*) begin
        tile_had_nan_comb = 1'b0;
        tile_had_inf_comb = 1'b0;
        for (r_naninf = 0; r_naninf < SIZE; r_naninf = r_naninf + 1) begin
            for (c_naninf = 0; c_naninf < SIZE; c_naninf = c_naninf + 1) begin
                if (pe_is_nan_internal[r_naninf][c_naninf]) tile_had_nan_comb = 1'b1;
                if (pe_is_infinity_internal[r_naninf][c_naninf]) tile_had_inf_comb = 1'b1;
            end
        end
    end
    assign tile_had_nan = tile_had_nan_comb;
    assign tile_had_inf = tile_had_inf_comb;

    // Debug signals update and strobes
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            prev_all_done_reduction_dbg <= 1'b0;
            prev_start_new_systolic_pass_dbg <= 1'b0;
            prev_activate_pe_computation_dbg <= 1'b0;

            if (SIZE > 0) prev_pe00_done_flag_dbg <= 1'b0;
            if (SIZE > 1) prev_pe01_done_flag_dbg <= 1'b0;
            if (SIZE > 1) prev_pe10_done_flag_dbg <= 1'b0;
            if (SIZE > 0) prev_peLL_done_flag_dbg <= 1'b0;
        end else begin
            // Strobe for critical control signals changing
            // if (activate_pe_computation != prev_activate_pe_computation_dbg ||
            //     start_new_systolic_pass != prev_start_new_systolic_pass_dbg ) begin // Strobe if any key control signal changes
            //      $strobe("@%0t [SA_CTRL_EVENT] activate_pe_comp:%b->%b, start_new_pass:%b->%b. (Other_ctrl: clr_all_acc:%b, cond_clr:%b, arr_data_vld:%b)",
            //             $time, 
            //             prev_activate_pe_computation_dbg, activate_pe_computation, 
            //             prev_start_new_systolic_pass_dbg, start_new_systolic_pass,
            //             clear_all_pe_accumulators, conditionally_clear_pe_sums_level, array_data_valid_in);
            // end

            // Strobe for all_pes_in_tile_done_reduction changing
            // if (all_pes_in_tile_done_reduction != prev_all_done_reduction_dbg && activate_pe_computation) begin 
            //     $strobe("@%0t [SA_ALL_DONE_CHG] all_pes_done_reduction changed from %b to %b. (act:%b)",
            //             $time, prev_all_done_reduction_dbg, all_pes_in_tile_done_reduction, activate_pe_computation);
            //     if (all_pes_in_tile_done_reduction == 1'b1 && SIZE > 0) begin
            //          $strobe("@%0t [SA_ALL_DONE_TRUE_SAMPLE] PE00=%b, PE01=%b, PE10=%b, PELL=%b", $time,
            //              pe_done_flags[0][0],
            //              (SIZE>1)?pe_done_flags[0][1]:1'bx,
            //              (SIZE>1)?pe_done_flags[1][0]:1'bx,
            //              pe_done_flags[SIZE-1][SIZE-1]);
            //     end
            // end
            
            // Strobe for individual pe_done_flags changing (for a few sample PEs)
            // if (SIZE > 0 && pe_done_flags[0][0] != prev_pe00_done_flag_dbg) begin 
            //     $strobe("@%0t [SA_FLAG_CHG_PE00] pe_done_flags[0][0] changed from %b to %b (act:%b, start_pass:%b)",
            //             $time, prev_pe00_done_flag_dbg, pe_done_flags[0][0], activate_pe_computation, start_new_systolic_pass);
            // end
            // Add for PE01, PE10, PELL similarly if needed, or keep focus on PE00
            // if (SIZE > 1 && pe_done_flags[0][1] != prev_pe01_done_flag_dbg) begin
            //      $strobe("@%0t [SA_FLAG_CHG_PE01] pe_done_flags[0][1] changed from %b to %b (act:%b, start_pass:%b)",
            //             $time, prev_pe01_done_flag_dbg, pe_done_flags[0][1], activate_pe_computation, start_new_systolic_pass);
            // end
            // if (SIZE > 0 && SIZE > 15 && pe_done_flags[SIZE-1][SIZE-1] != prev_peLL_done_flag_dbg) begin // Only if SIZE is large enough for PELL to be distinct
            //      $strobe("@%0t [SA_FLAG_CHG_PELL] pe_done_flags[%d][%d] changed from %b to %b (act:%b, start_pass:%b)",
            //             $time, SIZE-1, SIZE-1, prev_peLL_done_flag_dbg, pe_done_flags[SIZE-1][SIZE-1], activate_pe_computation, start_new_systolic_pass);
            // end


            // Update prev debug regs at the end of the cycle
            prev_all_done_reduction_dbg <= all_pes_in_tile_done_reduction;
            prev_start_new_systolic_pass_dbg <= start_new_systolic_pass;
            prev_activate_pe_computation_dbg <= activate_pe_computation;
            if (SIZE > 0) prev_pe00_done_flag_dbg <= pe_done_flags[0][0];
            if (SIZE > 1) prev_pe01_done_flag_dbg <= pe_done_flags[0][1];
            if (SIZE > 1) prev_pe10_done_flag_dbg <= pe_done_flags[1][0];
            if (SIZE > 0) prev_peLL_done_flag_dbg <= pe_done_flags[SIZE-1][SIZE-1];
        end
    end

endmodule