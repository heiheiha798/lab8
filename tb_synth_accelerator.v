// tb_synth_accelerator_v3.v
`timescale 1ns / 1ps

module tb_synth_accelerator;

    // --- Testbench Parameters ---
    localparam MATRIX_DIM_GLOBAL_TB_SIM = 32;   // For faster simulation
    localparam TILE_DIM_SYSTOLIC_TB   = 16;
    localparam RAM_DATA_WIDTH_TB      = 64;
    localparam SINT8_BITS_TB          = 8;
    localparam PE_ACCUM_BITS_TB       = 32;
    localparam LOGIC_ADDR_WIDTH_TB    = 23;     // Match DUT's LOGIC_ADDR_WIDTH

    localparam MM_READ_LATENCY_CYCLES_TB = 2;   // Main Memory Read Latency
    localparam MM_WRITE_LATENCY_CYCLES_TB = 0;  // Main Memory Write Latency (0 = ready in same cycle)

    localparam CLK_PERIOD_TB          = 1.13; // Clock period in ns
    localparam BYTES_PER_RAM_WORD_TB = RAM_DATA_WIDTH_TB / 8;

    // Main Memory Layout calculations for SIM dimension (Word Addressable for TB Memory)
    localparam TILES_PER_ROW_COL_SIM = (MATRIX_DIM_GLOBAL_TB_SIM == 0 || TILE_DIM_SYSTOLIC_TB == 0) ? 1 : MATRIX_DIM_GLOBAL_TB_SIM / TILE_DIM_SYSTOLIC_TB;

    localparam WORDS_PER_SINT8_TILE_TB_SIM = (TILE_DIM_SYSTOLIC_TB * TILE_DIM_SYSTOLIC_TB * SINT8_BITS_TB + RAM_DATA_WIDTH_TB - 1) / RAM_DATA_WIDTH_TB;
    localparam TOTAL_SINT8_WORDS_A_SIM  = WORDS_PER_SINT8_TILE_TB_SIM * TILES_PER_ROW_COL_SIM * TILES_PER_ROW_COL_SIM;
    localparam TOTAL_SINT8_WORDS_B_SIM  = TOTAL_SINT8_WORDS_A_SIM;

    localparam WORDS_PER_SINT32_TILE_TB_SIM  = (TILE_DIM_SYSTOLIC_TB * TILE_DIM_SYSTOLIC_TB * PE_ACCUM_BITS_TB + RAM_DATA_WIDTH_TB - 1) / RAM_DATA_WIDTH_TB;
    localparam TOTAL_SINT32_WORDS_C_SIM   = WORDS_PER_SINT32_TILE_TB_SIM * TILES_PER_ROW_COL_SIM * TILES_PER_ROW_COL_SIM;

    // Base addresses in Main Memory (WORD ADDRESSES for TB memory model)
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] BASE_ADDR_A_MM_TB_WORD = 0;
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] BASE_ADDR_B_MM_TB_WORD = BASE_ADDR_A_MM_TB_WORD + TOTAL_SINT8_WORDS_A_SIM;
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] BASE_ADDR_C_MM_TB_WORD = BASE_ADDR_B_MM_TB_WORD + TOTAL_SINT8_WORDS_B_SIM;
    localparam MAX_ADDR_MM_TB_WORD      = BASE_ADDR_C_MM_TB_WORD + TOTAL_SINT32_WORDS_C_SIM;


    // Base addresses to pass to DUT (BYTE ADDRESSES)
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] DUT_BASE_ADDR_A_MM = BASE_ADDR_A_MM_TB_WORD * BYTES_PER_RAM_WORD_TB;
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] DUT_BASE_ADDR_B_MM = BASE_ADDR_B_MM_TB_WORD * BYTES_PER_RAM_WORD_TB;
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] DUT_BASE_ADDR_C_MM = BASE_ADDR_C_MM_TB_WORD * BYTES_PER_RAM_WORD_TB;

    // --- Signals ---
    reg clk_tb;
    reg rst_n_tb;
    reg start_computation_tb;
    wire computation_done_tb;

    // DUT Interface Wires for Main Memory
    wire [LOGIC_ADDR_WIDTH_TB-1:0] mm_addr_o_dut_byte; // DUT outputs byte address
    wire [RAM_DATA_WIDTH_TB-1:0]   mm_wdata_o_dut;
    wire                           mm_cs_o_dut;
    wire                           mm_we_o_dut;
    reg  [RAM_DATA_WIDTH_TB-1:0]   mm_rdata_i_tb;      // To DUT
    reg                            mm_ready_i_tb;      // To DUT

    // --- Instantiate Accelerator (DUT) ---
    // Ensure parameters passed to DUT match its internal expectations or are parameterized within DUT as well
    accelerator #(
        .MATRIX_DIM_GLOBAL(MATRIX_DIM_GLOBAL_TB_SIM),
        .TILE_DIM_SYSTOLIC(TILE_DIM_SYSTOLIC_TB),
        .RAM_DATA_WIDTH(RAM_DATA_WIDTH_TB),
        .SINT8_BITS(SINT8_BITS_TB),
        .PE_ACCUM_BITS(PE_ACCUM_BITS_TB),
        .LOGIC_ADDR_WIDTH(LOGIC_ADDR_WIDTH_TB)
        // Internal SRAM parameters are local to the DUT
    ) u_accelerator_inst (
        .clk(clk_tb), .rst_n(rst_n_tb),
        .start_computation(start_computation_tb), .computation_done(computation_done_tb),
        .mm_addr_o(mm_addr_o_dut_byte), .mm_wdata_o(mm_wdata_o_dut),
        .mm_cs_o(mm_cs_o_dut), .mm_we_o(mm_we_o_dut),
        .mm_rdata_i(mm_rdata_i_tb), .mm_ready_i(mm_ready_i_tb),
        .base_addr_a_mm(DUT_BASE_ADDR_A_MM),
        .base_addr_b_mm(DUT_BASE_ADDR_B_MM),
        .base_addr_c_mm(DUT_BASE_ADDR_C_MM)
        // Tile SRAM ports are removed as they are internal to DUT now
    );

    // --- Main Memory Model (Word Addressable by TB) ---
    localparam MAIN_MEM_WORDS_TB = (MAX_ADDR_MM_TB_WORD > 0) ? MAX_ADDR_MM_TB_WORD : 2048; // Ensure some size
    reg [RAM_DATA_WIDTH_TB-1:0] main_memory_model_array [0:MAIN_MEM_WORDS_TB-1];

    reg [(MM_READ_LATENCY_CYCLES_TB > 0 ? $clog2(MM_READ_LATENCY_CYCLES_TB+1) : 1)-1:0] mm_read_latency_count_tb;
    reg [(MM_WRITE_LATENCY_CYCLES_TB > 0 ? $clog2(MM_WRITE_LATENCY_CYCLES_TB+1) : 1)-1:0] mm_write_latency_count_tb;

    reg [RAM_DATA_WIDTH_TB-1:0] mm_read_data_output_reg; // Staged read data
    wire [LOGIC_ADDR_WIDTH_TB-1:0] mm_addr_o_tb_word;   // DUT's byte address converted to TB's word address

    assign mm_addr_o_tb_word = mm_addr_o_dut_byte / BYTES_PER_RAM_WORD_TB;

    initial begin
        integer k_mm;
        for (k_mm = 0; k_mm < MAIN_MEM_WORDS_TB; k_mm = k_mm + 1) begin
            main_memory_model_array[k_mm] = {RAM_DATA_WIDTH_TB{1'bx}};
        end
        // Load A and B data. Ensure input_mem.csv has enough lines for A and B.
        // The addresses here are WORD addresses for the main_memory_model_array.
        $readmemh("input_mem.csv", main_memory_model_array, BASE_ADDR_A_MM_TB_WORD, BASE_ADDR_B_MM_TB_WORD + TOTAL_SINT8_WORDS_B_SIM - 1);
        $display("[%0t TB_INFO] Main memory initialized from input_mem.csv. Loaded A up to word %h, B up to word %h.",
                  $time, BASE_ADDR_A_MM_TB_WORD + TOTAL_SINT8_WORDS_A_SIM - 1, BASE_ADDR_B_MM_TB_WORD + TOTAL_SINT8_WORDS_B_SIM - 1);
    end

    always @(posedge clk_tb or negedge rst_n_tb) begin
        if (!rst_n_tb) begin
            mm_ready_i_tb <= 1'b0;
            mm_read_latency_count_tb <= 0;
            mm_write_latency_count_tb <= 0;
            mm_read_data_output_reg <= {RAM_DATA_WIDTH_TB{1'b0}};
        end else begin
            mm_ready_i_tb <= 1'b0; // Default to not ready for this cycle

            if (mm_read_latency_count_tb > 0) begin
                mm_read_latency_count_tb <= mm_read_latency_count_tb - 1;
                if (mm_read_latency_count_tb == 1) begin // Data will be ready at the end of this cycle (bus next cycle)
                    mm_ready_i_tb <= 1'b1;
                end
            end

            if (mm_write_latency_count_tb > 0) begin
                mm_write_latency_count_tb <= mm_write_latency_count_tb - 1;
                if (mm_write_latency_count_tb == 1) begin // Write will "complete" at end of this cycle
                    mm_ready_i_tb <= 1'b1;
                end
            end

            // New memory request from DUT, and memory is not busy with a previous operation's latency
            if (mm_cs_o_dut && mm_read_latency_count_tb == 0 && mm_write_latency_count_tb == 0 && !mm_ready_i_tb) begin
                if (mm_addr_o_tb_word >= MAIN_MEM_WORDS_TB) begin
                    $error("[%0t TB_ERR] MM Address out of bounds: word_addr %h (DUT byte_addr %h)", $time, mm_addr_o_tb_word, mm_addr_o_dut_byte);
                end else if (mm_we_o_dut) begin // Write operation
                    main_memory_model_array[mm_addr_o_tb_word] <= mm_wdata_o_dut;
                    $display("[%0t TB_MEM_INFO] Cycle %0d: MM Write Req: word_addr %h (byte %h), data %h", $time, u_accelerator_inst.cycle_count_dbg, mm_addr_o_tb_word, mm_addr_o_dut_byte, mm_wdata_o_dut);
                    if (MM_WRITE_LATENCY_CYCLES_TB == 0) begin
                        mm_ready_i_tb <= 1'b1; // Ready in the same cycle for 0 latency write
                    end else begin
                        mm_write_latency_count_tb <= MM_WRITE_LATENCY_CYCLES_TB; // Start latency countdown
                    end
                end else begin // Read operation
                    mm_read_data_output_reg <= main_memory_model_array[mm_addr_o_tb_word];
                    $display("[%0t TB_MEM_INFO] Cycle %0d: MM Read Req: word_addr %h (byte %h). Expect data %h", $time, u_accelerator_inst.cycle_count_dbg, mm_addr_o_tb_word, mm_addr_o_dut_byte, main_memory_model_array[mm_addr_o_tb_word]);
                    if (MM_READ_LATENCY_CYCLES_TB == 0) begin
                        mm_ready_i_tb <= 1'b1; // Ready in the same cycle for 0 latency read
                    end else begin
                        mm_read_latency_count_tb <= MM_READ_LATENCY_CYCLES_TB; // Start latency countdown
                    end
                end
            end
        end
    end
    // Read data is valid on mm_rdata_i_tb when mm_ready_i_tb is high for a read operation
    // and the latency counter has reached zero (meaning data is now available from mm_read_data_output_reg)
    assign mm_rdata_i_tb = (mm_ready_i_tb && mm_cs_o_dut && !mm_we_o_dut && mm_read_latency_count_tb == 0) ? mm_read_data_output_reg : {RAM_DATA_WIDTH_TB{1'bz}};


    // --- Tile SRAM Models are REMOVED as they are now internal to accelerator.v ---

    integer fid;
    integer k_file_loop;
    time start_sim_time;
    time end_sim_time;
    integer total_sim_cycles;

    // --- Testbench Control Sequence ---
    initial begin

        clk_tb = 1'b0;
        rst_n_tb = 1'b0;
        start_computation_tb = 1'b0;
        mm_rdata_i_tb = {RAM_DATA_WIDTH_TB{1'b0}}; // Initialize driven regs
        mm_ready_i_tb = 1'b0;

        start_sim_time = 0;
        end_sim_time = 0;
        total_sim_cycles = 0;

        $timeformat(-9, 3, " ns", 10);

        #(CLK_PERIOD_TB * 2.5); // Hold reset
        rst_n_tb = 1'b1;
        #(CLK_PERIOD_TB * 0.5); // Ensure reset propagates
        $display("[%0t TB_INFO] Reset released.", $time);

        #(CLK_PERIOD_TB * 2);

        $display("[%0t TB_INFO] Asserting start_computation.", $time);
        start_computation_tb = 1'b1;
        start_sim_time = $time;

        #(CLK_PERIOD_TB);
        start_computation_tb = 1'b0; // Pulse start_computation for one cycle
        $display("[%0t TB_INFO] De-asserted start_computation.", $time);

        $display("[%0t TB_INFO] Waiting for computation_done_tb signal from DUT...", $time);
        wait (computation_done_tb == 1'b1);
        end_sim_time = $time;
        $display("[%0t TB_INFO] computation_done_tb asserted by accelerator.", $time);
        total_sim_cycles = (end_sim_time - start_sim_time) / CLK_PERIOD_TB;
        $display("[%0t TB_INFO] Execution time: %0t ns (%0d cycles)", $time, (end_sim_time - start_sim_time), total_sim_cycles );


        #(CLK_PERIOD_TB); // Allow one more cycle for DUT to settle if needed or for final MM writes to complete.

        fid = $fopen("result_mem.csv", "w");
        if (fid != 0) begin
            $display("[%0t TB_INFO] Dumping C matrix from MM word_addr %h (byte %h) to result_mem.csv.", $time, BASE_ADDR_C_MM_TB_WORD, DUT_BASE_ADDR_C_MM);
            for (k_file_loop = 0; k_file_loop < TOTAL_SINT32_WORDS_C_SIM; k_file_loop = k_file_loop + 1) begin
                if ((BASE_ADDR_C_MM_TB_WORD + k_file_loop) < MAIN_MEM_WORDS_TB) begin
                    $fdisplay(fid, "%h", main_memory_model_array[BASE_ADDR_C_MM_TB_WORD + k_file_loop]);
                end else begin
                    $error("[%0t TB_ERR] Attempting to dump C beyond memory model size at word_addr %h.", $time, BASE_ADDR_C_MM_TB_WORD + k_file_loop);
                    break;
                end
            end
            $fclose(fid);
            $display("[%0t TB_INFO] Result C matrix (expected %0d words) dumped to result_mem.csv.", $time, TOTAL_SINT32_WORDS_C_SIM);
        end else begin
            $error("[%0t TB_ERR] Could not open result_mem.csv for writing.", $time);
        end

        #(CLK_PERIOD_TB * 10);
        $display("[%0t TB_INFO] Test finished.", $time);
        $finish;
    end

    // Clock generator
    always # (CLK_PERIOD_TB / 2) clk_tb = ~clk_tb;

endmodule