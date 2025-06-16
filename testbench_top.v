// testbench_top.v
`timescale 1ns / 1ps

module testbench_top;

    localparam MATRIX_DIM_GLOBAL_TB = 512;
    localparam TILE_DIM_SYSTOLIC_TB = 16;
    localparam RAM_DATA_WIDTH_TB    = 64;
    localparam SINT8_BITS_TB        = 8;
    localparam PE_ACCUM_BITS_TB     = 32;
    localparam LOGIC_ADDR_WIDTH_TB  = 18; // To match ram_controller and accelerator
    localparam RC_READ_LATENCY_CYCLES_TB = 2; // To match ram_controller and accelerator

    localparam CLK_PERIOD           = 10;

    // Derived parameters for memory layout (using LOGICAL view for sizes)
    localparam SINT8_PER_RAM_WORD_TB = (SINT8_BITS_TB == 0) ? 0 : RAM_DATA_WIDTH_TB / SINT8_BITS_TB;
    localparam SINT32_PER_RAM_WORD_TB = (PE_ACCUM_BITS_TB == 0) ? 0 : RAM_DATA_WIDTH_TB / PE_ACCUM_BITS_TB;
    localparam TILES_PER_ROW_COL_GLOBAL_TB = (TILE_DIM_SYSTOLIC_TB == 0) ? 0 : MATRIX_DIM_GLOBAL_TB / TILE_DIM_SYSTOLIC_TB;
    localparam TILES_PER_ROW_COL_GLOBAL_TB_SAFE = (TILES_PER_ROW_COL_GLOBAL_TB == 0) ? 1 : TILES_PER_ROW_COL_GLOBAL_TB;
    localparam WORDS_PER_SINT8_TILE_CALC_TB = (TILE_DIM_SYSTOLIC_TB*TILE_DIM_SYSTOLIC_TB*SINT8_BITS_TB)/RAM_DATA_WIDTH_TB;
    localparam WORDS_PER_SINT8_TILE_TB = (WORDS_PER_SINT8_TILE_CALC_TB==0 && (TILE_DIM_SYSTOLIC_TB*TILE_DIM_SYSTOLIC_TB*SINT8_BITS_TB)>0)?1:WORDS_PER_SINT8_TILE_CALC_TB;
    localparam TOTAL_SINT8_WORDS_A_TB  = WORDS_PER_SINT8_TILE_TB * TILES_PER_ROW_COL_GLOBAL_TB_SAFE * TILES_PER_ROW_COL_GLOBAL_TB_SAFE;
    localparam TOTAL_SINT8_WORDS_B_TB  = TOTAL_SINT8_WORDS_A_TB;
    localparam WORDS_PER_SINT32_TILE_CALC_TB  = (TILE_DIM_SYSTOLIC_TB*TILE_DIM_SYSTOLIC_TB*PE_ACCUM_BITS_TB)/RAM_DATA_WIDTH_TB;
    localparam WORDS_PER_SINT32_TILE_TB = (WORDS_PER_SINT32_TILE_CALC_TB==0 && (TILE_DIM_SYSTOLIC_TB*TILE_DIM_SYSTOLIC_TB*PE_ACCUM_BITS_TB)>0)?1:WORDS_PER_SINT32_TILE_CALC_TB;
    localparam TOTAL_SINT32_WORDS_C_TB   = WORDS_PER_SINT32_TILE_TB * TILES_PER_ROW_COL_GLOBAL_TB_SAFE * TILES_PER_ROW_COL_GLOBAL_TB_SAFE;

    localparam [LOGIC_ADDR_WIDTH_TB-1:0] BASE_ADDR_A_LOGIC_TB = 0;
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] BASE_ADDR_B_LOGIC_TB = BASE_ADDR_A_LOGIC_TB + TOTAL_SINT8_WORDS_A_TB;
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] BASE_ADDR_C_LOGIC_TB = BASE_ADDR_B_LOGIC_TB + TOTAL_SINT8_WORDS_B_TB;
    // END_ADDR_B_LOAD_LOGIC_TB is not used by $readmemh if it loads whole file into ram_controller's pseudo_ram

    reg clk_tb;
    reg rst_n_tb;
    reg start_computation_tb;
    wire computation_done_tb;

    integer output_file_desc;
    integer i_loop_tb;

    accelerator #(
        .MATRIX_DIM_GLOBAL(MATRIX_DIM_GLOBAL_TB),
        .TILE_DIM_SYSTOLIC(TILE_DIM_SYSTOLIC_TB),
        .RAM_DATA_WIDTH(RAM_DATA_WIDTH_TB),
        .SINT8_BITS(SINT8_BITS_TB),
        .PE_ACCUM_BITS(PE_ACCUM_BITS_TB),
        .LOGIC_ADDR_WIDTH(LOGIC_ADDR_WIDTH_TB),
        .RC_READ_LATENCY_CYCLES(RC_READ_LATENCY_CYCLES_TB)
    ) u_accelerator (
        .clk(clk_tb),
        .rst_n(rst_n_tb),
        .start_computation(start_computation_tb),
        .computation_done(computation_done_tb),
        .base_addr_a(BASE_ADDR_A_LOGIC_TB),
        .base_addr_b(BASE_ADDR_B_LOGIC_TB),
        .base_addr_c(BASE_ADDR_C_LOGIC_TB)
    );

    always begin
        #(CLK_PERIOD/2) clk_tb = ~clk_tb;
    end

    initial begin
        clk_tb = 0;
        rst_n_tb = 0;
        start_computation_tb = 0;

        #(CLK_PERIOD * 2);
        rst_n_tb = 1;
        #(CLK_PERIOD);
        $display("[%0t TB] Reset released.", $time);

        // $readmemh is now inside ram_controller_behavioral.v's initial block.
        // We wait for ram_controller's internal $display to confirm.
        // $display("[%0t TB] Verifying pseudo_ram content via hierarchical access...", $time);
        // // Print first few words of A
        // for (i_loop_tb = 0; i_loop_tb < 4 && i_loop_tb < (1<<LOGIC_ADDR_WIDTH_TB); i_loop_tb = i_loop_tb + 1) begin
        //     $display("[%0t TB] Accel.RC.pseudo_ram[A_base + 0x%h] = %h", $time, i_loop_tb, testbench_top.u_accelerator.u_ram_controller.pseudo_ram[BASE_ADDR_A_LOGIC_TB + i_loop_tb]);
        // end
        // // Print first few words of B
        // for (i_loop_tb = 0; i_loop_tb < 4 && i_loop_tb < (1<<LOGIC_ADDR_WIDTH_TB); i_loop_tb = i_loop_tb + 1) begin
        //     $display("[%0t TB] Accel.RC.pseudo_ram[B_base + 0x%h] = %h", $time, i_loop_tb, testbench_top.u_accelerator.u_ram_controller.pseudo_ram[BASE_ADDR_B_LOGIC_TB + i_loop_tb]);
        // end
        // // Print LAST few words of B (for 16x16, B uses 32 words, addresses BASE_ADDR_B_LOGIC_TB to BASE_ADDR_B_LOGIC_TB + 31)
        // // Example: print words 28, 29, 30, 31 of B's logical space
        // if (TOTAL_SINT8_WORDS_B_TB >= 4) begin // Ensure we don't go out of bounds for small B
        //     for (i_loop_tb = TOTAL_SINT8_WORDS_B_TB - 4; i_loop_tb < TOTAL_SINT8_WORDS_B_TB && (BASE_ADDR_B_LOGIC_TB + i_loop_tb) < (1<<LOGIC_ADDR_WIDTH_TB); i_loop_tb = i_loop_tb + 1) begin
        //         $display("[%0t TB] Accel.RC.pseudo_ram[B_base_logical + 0x%h (actual 0x%h)] = %h", $time, i_loop_tb, BASE_ADDR_B_LOGIC_TB + i_loop_tb, testbench_top.u_accelerator.u_ram_controller.pseudo_ram[BASE_ADDR_B_LOGIC_TB + i_loop_tb]);
        //     end
        // end


        // $display("[%0t TB] Asserting start_computation.", $time);
        start_computation_tb = 1;
        #(CLK_PERIOD);
        start_computation_tb = 0;
        // $display("[%0t TB] De-asserted start_computation.", $time);

        // $display("[%0t TB] Waiting for computation_done_tb...", $time);
        wait (computation_done_tb == 1);
        // $display("[%0t TB] computation_done_tb asserted by accelerator.", $time);
        #(CLK_PERIOD);

        output_file_desc = $fopen("result_mem.csv", "w");
        if (output_file_desc == 0) begin
            // $display("[%0t TB] Error: Could not open result_mem.csv for writing.", $time);
        end else begin
            // $display("[%0t TB] Dumping C matrix from RAM Controller's pseudo_ram to result_mem.csv...", $time);
            for (i_loop_tb = 0; i_loop_tb < TOTAL_SINT32_WORDS_C_TB; i_loop_tb = i_loop_tb + 1) begin
                if ((BASE_ADDR_C_LOGIC_TB + i_loop_tb) < (1<<LOGIC_ADDR_WIDTH_TB)) begin
                    $fdisplay(output_file_desc, "%h", testbench_top.u_accelerator.u_ram_controller.pseudo_ram[BASE_ADDR_C_LOGIC_TB + i_loop_tb]);
                end else begin
                    // $display("[%0t TB] Error: Address out of bounds during C dump: %h", $time, BASE_ADDR_C_LOGIC_TB + i_loop_tb);
                    break;
                end
            end
            $fclose(output_file_desc);
            // $display("[%0t TB] Finished dumping C matrix.", $time);
        end

        #(CLK_PERIOD * 10);
        $display("[%0t TB] Test finished.", $time);
        $finish;
    end
endmodule