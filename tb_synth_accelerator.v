// tb_synth_accelerator.v
`timescale 1ns / 1ps

module tb_synth_accelerator;

    // --- Testbench Parameters ---
    localparam MATRIX_DIM_GLOBAL_TB_SIM = 512;   // For faster simulation, can be 16 or 32
    localparam TILE_DIM_SYSTOLIC_TB   = 16;
    localparam RAM_DATA_WIDTH_TB      = 64;
    localparam SINT8_BITS_TB          = 8;
    localparam PE_ACCUM_BITS_TB       = 32;
    localparam LOGIC_ADDR_WIDTH_TB    = 18; // For Main Memory Model
    localparam MM_READ_LATENCY_CYCLES_TB = 2; // Main Memory Read Latency

    localparam CLK_PERIOD_TB          = 1.13; // Clock period in ns

    // Derived parameters for memory layout and DUT instantiation
    localparam SINT8_PER_RAM_WORD_TB = (SINT8_BITS_TB == 0) ? 1 : RAM_DATA_WIDTH_TB / SINT8_BITS_TB; // Avoid div by zero
    localparam SINT32_PER_RAM_WORD_TB = (PE_ACCUM_BITS_TB == 0) ? 1 : RAM_DATA_WIDTH_TB / PE_ACCUM_BITS_TB;

    localparam TILE_SRAM_TOTAL_BITS_TB  = (TILE_DIM_SYSTOLIC_TB * TILE_DIM_SYSTOLIC_TB * SINT8_BITS_TB);
    localparam TILE_SRAM_WORDS_TB       = (TILE_SRAM_TOTAL_BITS_TB == 0 || RAM_DATA_WIDTH_TB == 0) ? 1 : (TILE_SRAM_TOTAL_BITS_TB + RAM_DATA_WIDTH_TB - 1) / RAM_DATA_WIDTH_TB;
    localparam TILE_SRAM_ADDR_WIDTH_DUT = (TILE_SRAM_WORDS_TB <= 1) ? 1 : $clog2(TILE_SRAM_WORDS_TB);

    // Main Memory Layout calculations for SIM dimension
    localparam TILES_PER_ROW_COL_SIM = (MATRIX_DIM_GLOBAL_TB_SIM == 0 || TILE_DIM_SYSTOLIC_TB == 0) ? 1 : MATRIX_DIM_GLOBAL_TB_SIM / TILE_DIM_SYSTOLIC_TB;
    localparam WORDS_PER_SINT8_TILE_TB_SIM = (TILE_DIM_SYSTOLIC_TB*TILE_DIM_SYSTOLIC_TB*SINT8_BITS_TB)/RAM_DATA_WIDTH_TB;
    localparam TOTAL_SINT8_WORDS_A_SIM  = WORDS_PER_SINT8_TILE_TB_SIM * TILES_PER_ROW_COL_SIM * TILES_PER_ROW_COL_SIM;
    localparam TOTAL_SINT8_WORDS_B_SIM  = TOTAL_SINT8_WORDS_A_SIM;

    localparam WORDS_PER_SINT32_TILE_TB_SIM  = (TILE_DIM_SYSTOLIC_TB*TILE_DIM_SYSTOLIC_TB*PE_ACCUM_BITS_TB)/RAM_DATA_WIDTH_TB;
    localparam TOTAL_SINT32_WORDS_C_SIM   = WORDS_PER_SINT32_TILE_TB_SIM * TILES_PER_ROW_COL_SIM * TILES_PER_ROW_COL_SIM;

    localparam [LOGIC_ADDR_WIDTH_TB-1:0] BASE_ADDR_A_MM_TB = 0;
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] BASE_ADDR_B_MM_TB = BASE_ADDR_A_MM_TB + TOTAL_SINT8_WORDS_A_SIM;
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] BASE_ADDR_C_MM_TB = BASE_ADDR_B_MM_TB + TOTAL_SINT8_WORDS_B_SIM;

    // --- Signals ---
    reg clk_tb;
    reg rst_n_tb;
    reg start_computation_tb;
    wire computation_done_tb;

    // DUT Interface Wires/Regs
    wire [LOGIC_ADDR_WIDTH_TB-1:0] mm_addr_o_w;
    wire [RAM_DATA_WIDTH_TB-1:0]   mm_wdata_o_w;
    wire                           mm_cs_o_w;
    wire                           mm_we_o_w;
    reg  [RAM_DATA_WIDTH_TB-1:0]   mm_rdata_i_tb;
    reg                            mm_ready_i_tb;

    wire                               tile_a_sram_cs_o_w;
    wire                               tile_a_sram_we_o_w;
    wire [TILE_SRAM_ADDR_WIDTH_DUT-1:0] tile_a_sram_addr_o_w; // Use calculated width for DUT
    wire [RAM_DATA_WIDTH_TB-1:0]       tile_a_sram_wdata_o_w;
    reg  [RAM_DATA_WIDTH_TB-1:0]       tile_a_sram_rdata_i_tb;

    wire                               tile_b_sram_cs_o_w;
    wire                               tile_b_sram_we_o_w;
    wire [TILE_SRAM_ADDR_WIDTH_DUT-1:0] tile_b_sram_addr_o_w; // Use calculated width for DUT
    wire [RAM_DATA_WIDTH_TB-1:0]       tile_b_sram_wdata_o_w;
    reg  [RAM_DATA_WIDTH_TB-1:0]       tile_b_sram_rdata_i_tb;

    // --- Instantiate Accelerator (DUT) ---
    accelerator #(
        .MATRIX_DIM_GLOBAL(MATRIX_DIM_GLOBAL_TB_SIM),
        .TILE_DIM_SYSTOLIC(TILE_DIM_SYSTOLIC_TB),
        .RAM_DATA_WIDTH(RAM_DATA_WIDTH_TB),
        .SINT8_BITS(SINT8_BITS_TB),
        .PE_ACCUM_BITS(PE_ACCUM_BITS_TB),
        .LOGIC_ADDR_WIDTH(LOGIC_ADDR_WIDTH_TB),
        // .TILE_SRAM_ADDR_WIDTH(TILE_SRAM_ADDR_WIDTH_DUT), // Pass if accelerator has it as param
        .MM_READ_LATENCY_CYCLES(MM_READ_LATENCY_CYCLES_TB)
    ) u_accelerator_inst (
        .clk(clk_tb), .rst_n(rst_n_tb),
        .start_computation(start_computation_tb), .computation_done(computation_done_tb),

        .mm_addr_o(mm_addr_o_w), .mm_wdata_o(mm_wdata_o_w), .mm_cs_o(mm_cs_o_w), .mm_we_o(mm_we_o_w),
        .mm_rdata_i(mm_rdata_i_tb), .mm_ready_i(mm_ready_i_tb),

        .base_addr_a_mm(BASE_ADDR_A_MM_TB),
        .base_addr_b_mm(BASE_ADDR_B_MM_TB),
        .base_addr_c_mm(BASE_ADDR_C_MM_TB),

        .tile_a_sram_cs_o(tile_a_sram_cs_o_w), .tile_a_sram_we_o(tile_a_sram_we_o_w),
        .tile_a_sram_addr_o(tile_a_sram_addr_o_w), .tile_a_sram_wdata_o(tile_a_sram_wdata_o_w),
        .tile_a_sram_rdata_i(tile_a_sram_rdata_i_tb),

        .tile_b_sram_cs_o(tile_b_sram_cs_o_w), .tile_b_sram_we_o(tile_b_sram_we_o_w),
        .tile_b_sram_addr_o(tile_b_sram_addr_o_w), .tile_b_sram_wdata_o(tile_b_sram_wdata_o_w),
        .tile_b_sram_rdata_i(tile_b_sram_rdata_i_tb)
    );

    // --- Main Memory Model ---
    localparam MAIN_MEM_SIZE_TB = 1 << LOGIC_ADDR_WIDTH_TB;
    reg [RAM_DATA_WIDTH_TB-1:0] main_memory_model_array [0:MAIN_MEM_SIZE_TB-1];
    reg [MM_READ_LATENCY_CYCLES_TB:0] mm_latency_count_tb; // Latency counter for reads
    reg [RAM_DATA_WIDTH_TB-1:0] mm_read_data_output_reg; // To stage read data

    initial begin
        integer k_mm;
        for (k_mm = 0; k_mm < MAIN_MEM_SIZE_TB; k_mm = k_mm + 1) begin
            main_memory_model_array[k_mm] = {RAM_DATA_WIDTH_TB{1'bx}}; // Initialize to X
        end
        $readmemh("input_mem.csv", main_memory_model_array);
    end

    always @(posedge clk_tb or negedge rst_n_tb) begin
        if (!rst_n_tb) begin
            mm_ready_i_tb <= 1'b0;
            mm_latency_count_tb <= 0;
            mm_read_data_output_reg <= {RAM_DATA_WIDTH_TB{1'b0}};
        end else begin
            mm_ready_i_tb <= 1'b0; // Default to not ready for the current cycle

            if (mm_latency_count_tb > 0) begin
                mm_latency_count_tb <= mm_latency_count_tb - 1;
                if (mm_latency_count_tb == 1) begin // Data will be ready next cycle
                    mm_ready_i_tb <= 1'b1;
                end
            end

            if (mm_cs_o_w && mm_latency_count_tb == 0 && !mm_ready_i_tb) begin // New valid request and memory is not busy
                if (mm_we_o_w) begin // Write operation
                    main_memory_model_array[mm_addr_o_w] <= mm_wdata_o_w;
                    // Simple 1-cycle ready for write acknowledge (can be 0 if write is posted)
                    mm_ready_i_tb <= 1'b1;
                end else begin // Read operation
                    mm_read_data_output_reg <= main_memory_model_array[mm_addr_o_w];
                    if (MM_READ_LATENCY_CYCLES_TB == 0) begin
                        mm_ready_i_tb <= 1'b1;
                    end else begin
                        mm_latency_count_tb <= MM_READ_LATENCY_CYCLES_TB; // Start latency countdown
                    end
                end
            end
        end
    end
    assign mm_rdata_i_tb = (mm_ready_i_tb && !mm_we_o_w && mm_cs_o_w) ? mm_read_data_output_reg : {RAM_DATA_WIDTH_TB{1'bz}};

    reg [RAM_DATA_WIDTH_TB-1:0] tile_a_sram_model_array [0:TILE_SRAM_WORDS_TB-1];
    reg [RAM_DATA_WIDTH_TB-1:0] tile_b_sram_model_array [0:TILE_SRAM_WORDS_TB-1];

    // --- Tile A SRAM Model (1-cycle read latency) ---
    always @(posedge clk_tb or negedge rst_n_tb) begin // Added rst_n_tb for completeness
        if (!rst_n_tb) begin
            tile_a_sram_rdata_i_tb <= {RAM_DATA_WIDTH_TB{1'b0}};
        end else begin
            if (tile_a_sram_cs_o_w) begin
                if (tile_a_sram_we_o_w) begin // Write operation
                    tile_a_sram_model_array[tile_a_sram_addr_o_w] <= tile_a_sram_wdata_o_w;
                    tile_a_sram_rdata_i_tb <= {RAM_DATA_WIDTH_TB{1'bx}}; // Output X during write
                end else begin // Read operation
                    tile_a_sram_rdata_i_tb <= tile_a_sram_model_array[tile_a_sram_addr_o_w];
                end
            end else begin // Not selected
                tile_a_sram_rdata_i_tb <= {RAM_DATA_WIDTH_TB{1'bx}}; // Output X when not selected (instead of Z)
            end
        end
    end

    // --- Tile B SRAM Model (1-cycle read latency) ---
    always @(posedge clk_tb or negedge rst_n_tb) begin // Added rst_n_tb
        if (!rst_n_tb) begin
            tile_b_sram_rdata_i_tb <= {RAM_DATA_WIDTH_TB{1'b0}};
        end else begin
            if (tile_b_sram_cs_o_w) begin
                if (tile_b_sram_we_o_w) begin // Write operation
                    tile_b_sram_model_array[tile_b_sram_addr_o_w] <= tile_b_sram_wdata_o_w;
                    tile_b_sram_rdata_i_tb <= {RAM_DATA_WIDTH_TB{1'bx}}; // Output X during write
                end else begin // Read operation
                    tile_b_sram_rdata_i_tb <= tile_b_sram_model_array[tile_b_sram_addr_o_w];
                end
            end else begin // Not selected
                tile_b_sram_rdata_i_tb <= {RAM_DATA_WIDTH_TB{1'bx}}; // Output X when not selected (instead of Z)
            end
        end
    end

    integer fid;
    integer k;
    reg start_time_reg_set;
    time start_sim_time;
    time end_sim_time;

    // --- Testbench Control Sequence ---
    initial begin
        // Original initializations from your new code
        clk_tb = 1'b0; // Start clock low for clarity in waveform
        rst_n_tb = 1'b0;
        start_computation_tb = 1'b0;
        mm_rdata_i_tb = {RAM_DATA_WIDTH_TB{1'b0}}; // Initialize driven regs
        mm_ready_i_tb = 1'b0;
        tile_a_sram_rdata_i_tb = {RAM_DATA_WIDTH_TB{1'b0}};
        tile_b_sram_rdata_i_tb = {RAM_DATA_WIDTH_TB{1'b0}};

        // Timing logic initializations from the example code
        start_time_reg_set = 1'b0;
        start_sim_time = 0;
        end_sim_time = 0;

        $timeformat(-9, 3, " ns", 10); // From the example code (3 decimal places for ns)

        // Original reset sequence from your new code
        #(CLK_PERIOD_TB * 2.5); // Hold reset for a few cycles
        rst_n_tb = 1'b1;
        #(CLK_PERIOD_TB * 0.5); // Ensure reset propagates
        $display("[%0t TB] Reset released.", $time); // Display message style from the example code

        // Original wait from your new code
        #(CLK_PERIOD_TB * 2);

        // Original start computation from your new code, augmented with timing logic & display from example
        $display("[%0t TB] Asserting start_computation.", $time); // Display message style from the example code
        start_computation_tb = 1'b1;
        start_sim_time = $time; // Record start time (Timing logic from example)
        start_time_reg_set = 1'b1; // Flag that start time is set (Timing logic from example)

        #(CLK_PERIOD_TB);
        start_computation_tb = 1'b0;
        $display("[%0t TB] De-asserted start_computation.", $time); // Display message style from the example code

        // Original wait for done from your new code, augmented with timing logic & display from example
        $display("[%0t TB] Waiting for computation_done_tb signal...", $time); // Display message style from the example code
        wait (computation_done_tb == 1'b1);
        end_sim_time = $time; // Record end time (Timing logic from example)
        $display("[%0t TB] computation_done_tb asserted by accelerator.", $time); // Display message style from the example code
        if (start_time_reg_set) begin // Calculate and display execution time (Timing logic from example)
             $display("[%0t TB] Execution time: %0t ns", $time, (end_sim_time - start_sim_time));
        end

        #(CLK_PERIOD_TB); // Original delay from your new code: Allow one more cycle for any final writes if needed
        
        // Original file dump from your new code, augmented with display messages from example's style
        // Assuming 'fid' and 'k' are declared appropriately (e.g., integer) elsewhere in your testbench module.
        fid = $fopen("result_mem.csv", "w");
        if (fid != 0) begin
            // This for loop structure (including 'break') is from YOUR new code and is UNCHANGED.
            for (k = 0; k < TOTAL_SINT32_WORDS_C_SIM; k = k + 1) begin
                if ((BASE_ADDR_C_MM_TB + k) < MAIN_MEM_SIZE_TB) begin
                    $fdisplay(fid, "%h", main_memory_model_array[BASE_ADDR_C_MM_TB + k]);
                end else begin
                    break; // Kept from your new code
                end
            end
            $fclose(fid);
            $display("[%0t TB] Result C matrix dumped to result_mem.csv.", $time); // Display message style from the example code
        end else begin
            // Added this 'else' block for robustness, consistent with example's logging style
            $display("[%0t TB] ERROR: Could not open result_mem.csv for writing.", $time);
        end

        // Original wait and finish from your new code, augmented with display from example's style
        #(CLK_PERIOD_TB * 10);
        $display("[%0t TB] Test finished.", $time); // Display message style from the example code
        $finish;
    end
    // Clock generator
    always # (CLK_PERIOD_TB / 2) clk_tb = ~clk_tb;

endmodule