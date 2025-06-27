// ~/lab8/tb_gate_accelerator.v
`timescale 1ns / 1ps

module tb_gate_accelerator;

    // --- Testbench Parameters ---
    localparam MATRIX_DIM_GLOBAL_TB_SIM = 512;
    localparam TILE_DIM_SYSTOLIC_TB   = 16;
    localparam RAM_DATA_WIDTH_TB      = 64;
    localparam SINT8_BITS_TB          = 8;
    localparam PE_ACCUM_BITS_TB       = 32;
    localparam LOGIC_ADDR_WIDTH_TB    = 18; // Reduced for faster $readmemh warning resolution, ensure still covers A,B,C
    localparam MM_READ_LATENCY_CYCLES_TB = 2;
    localparam CLK_PERIOD_TB          = 10;

    // Derived parameters
    localparam SINT8_PER_RAM_WORD_TB = (SINT8_BITS_TB == 0) ? 1 : RAM_DATA_WIDTH_TB / SINT8_BITS_TB;
    localparam SINT32_PER_RAM_WORD_TB = (PE_ACCUM_BITS_TB == 0) ? 1 : RAM_DATA_WIDTH_TB / PE_ACCUM_BITS_TB;
    localparam TILE_SRAM_TOTAL_BITS_TB  = (TILE_DIM_SYSTOLIC_TB * TILE_DIM_SYSTOLIC_TB * SINT8_BITS_TB);
    localparam TILE_SRAM_WORDS_TB       = (TILE_SRAM_TOTAL_BITS_TB == 0 || RAM_DATA_WIDTH_TB == 0) ? 1 : (TILE_SRAM_TOTAL_BITS_TB + RAM_DATA_WIDTH_TB - 1) / RAM_DATA_WIDTH_TB;
    localparam TILE_SRAM_ADDR_WIDTH_DUT = (TILE_SRAM_WORDS_TB <= 1) ? 1 : $clog2(TILE_SRAM_WORDS_TB);
    localparam TILES_PER_ROW_COL_SIM = (MATRIX_DIM_GLOBAL_TB_SIM == 0 || TILE_DIM_SYSTOLIC_TB == 0) ? 1 : MATRIX_DIM_GLOBAL_TB_SIM / TILE_DIM_SYSTOLIC_TB;
    localparam WORDS_PER_SINT8_TILE_TB_SIM = (TILE_DIM_SYSTOLIC_TB*TILE_DIM_SYSTOLIC_TB*SINT8_BITS_TB)/RAM_DATA_WIDTH_TB;
    localparam TOTAL_SINT8_WORDS_A_SIM  = WORDS_PER_SINT8_TILE_TB_SIM * TILES_PER_ROW_COL_SIM * TILES_PER_ROW_COL_SIM;
    localparam TOTAL_SINT8_WORDS_B_SIM  = TOTAL_SINT8_WORDS_A_SIM;
    localparam WORDS_PER_SINT32_TILE_TB_SIM  = (TILE_DIM_SYSTOLIC_TB*TILE_DIM_SYSTOLIC_TB*PE_ACCUM_BITS_TB)/RAM_DATA_WIDTH_TB;
    localparam TOTAL_SINT32_WORDS_C_SIM   = WORDS_PER_SINT32_TILE_TB_SIM * TILES_PER_ROW_COL_SIM * TILES_PER_ROW_COL_SIM;
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] BASE_ADDR_A_MM_TB = 0;
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] BASE_ADDR_B_MM_TB = BASE_ADDR_A_MM_TB + TOTAL_SINT8_WORDS_A_SIM;
    localparam [LOGIC_ADDR_WIDTH_TB-1:0] BASE_ADDR_C_MM_TB = BASE_ADDR_B_MM_TB + TOTAL_SINT8_WORDS_B_SIM;
    localparam MAIN_MEM_SIZE_TB = 1 << LOGIC_ADDR_WIDTH_TB; // Adjusted based on new LOGIC_ADDR_WIDTH_TB

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
    wire [RAM_DATA_WIDTH_TB-1:0]   mm_rdata_i_tb;         // MODIFIED: reg to wire
    reg                            mm_ready_i_tb;

    wire                               tile_a_sram_cs_o_w;
    wire                               tile_a_sram_we_o_w;
    wire [TILE_SRAM_ADDR_WIDTH_DUT-1:0] tile_a_sram_addr_o_w;
    wire [RAM_DATA_WIDTH_TB-1:0]       tile_a_sram_wdata_o_w;
    reg  [RAM_DATA_WIDTH_TB-1:0]       tile_a_sram_rdata_i_tb;

    wire                               tile_b_sram_cs_o_w;
    wire                               tile_b_sram_we_o_w;
    wire [TILE_SRAM_ADDR_WIDTH_DUT-1:0] tile_b_sram_addr_o_w;
    wire [RAM_DATA_WIDTH_TB-1:0]       tile_b_sram_wdata_o_w;
    reg  [RAM_DATA_WIDTH_TB-1:0]       tile_b_sram_rdata_i_tb;

    // --- Instantiate Accelerator (DUT) ---
    // MODIFIED: Removed parameter overrides for gate-level simulation
    accelerator u_accelerator_inst (
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
    reg [RAM_DATA_WIDTH_TB-1:0] main_memory_model_array [0:MAIN_MEM_SIZE_TB-1];
    reg [MM_READ_LATENCY_CYCLES_TB:0] mm_latency_count_tb;
    reg [RAM_DATA_WIDTH_TB-1:0] mm_read_data_output_reg;
    integer k_mm;

    initial begin
        for (k_mm = 0; k_mm < MAIN_MEM_SIZE_TB; k_mm = k_mm + 1) begin
            main_memory_model_array[k_mm] = {RAM_DATA_WIDTH_TB{1'bx}};
        end
        $readmemh("input_mem.csv", main_memory_model_array);
    end

    always @(posedge clk_tb or negedge rst_n_tb) begin
        if (!rst_n_tb) begin
            mm_ready_i_tb <= 1'b0;
            mm_latency_count_tb <= 0;
            mm_read_data_output_reg <= {RAM_DATA_WIDTH_TB{1'b0}};
        end else begin
            mm_ready_i_tb <= 1'b0;
            if (mm_latency_count_tb > 0) begin
                mm_latency_count_tb <= mm_latency_count_tb - 1;
                if (mm_latency_count_tb == 1) begin
                    mm_ready_i_tb <= 1'b1;
                end
            end
            if (mm_cs_o_w && mm_latency_count_tb == 0 && !mm_ready_i_tb) begin
                if (mm_we_o_w) begin
                    main_memory_model_array[mm_addr_o_w] <= mm_wdata_o_w;
                    mm_ready_i_tb <= 1'b1;
                end else begin
                    mm_read_data_output_reg <= main_memory_model_array[mm_addr_o_w];
                    if (MM_READ_LATENCY_CYCLES_TB == 0) begin
                        mm_ready_i_tb <= 1'b1;
                    end else begin
                        mm_latency_count_tb <= MM_READ_LATENCY_CYCLES_TB;
                    end
                end
            end
        end
    end
    assign mm_rdata_i_tb = (mm_ready_i_tb && !mm_we_o_w && mm_cs_o_w) ? mm_read_data_output_reg : {RAM_DATA_WIDTH_TB{1'bx}};

    // --- Tile SRAM Models ---
    reg [RAM_DATA_WIDTH_TB-1:0] tile_a_sram_model_array [0:TILE_SRAM_WORDS_TB-1];
    reg [RAM_DATA_WIDTH_TB-1:0] tile_b_sram_model_array [0:TILE_SRAM_WORDS_TB-1];

    always @(posedge clk_tb or negedge rst_n_tb) begin
        if (!rst_n_tb) begin
            tile_a_sram_rdata_i_tb <= {RAM_DATA_WIDTH_TB{1'b0}};
        end else begin
            if (tile_a_sram_cs_o_w) begin
                if (tile_a_sram_we_o_w) begin
                    tile_a_sram_model_array[tile_a_sram_addr_o_w] <= tile_a_sram_wdata_o_w;
                    tile_a_sram_rdata_i_tb <= {RAM_DATA_WIDTH_TB{1'bx}};
                end else begin
                    tile_a_sram_rdata_i_tb <= tile_a_sram_model_array[tile_a_sram_addr_o_w];
                end
            end else begin
                tile_a_sram_rdata_i_tb <= {RAM_DATA_WIDTH_TB{1'bx}};
            end
        end
    end

    always @(posedge clk_tb or negedge rst_n_tb) begin
        if (!rst_n_tb) begin
            tile_b_sram_rdata_i_tb <= {RAM_DATA_WIDTH_TB{1'b0}};
        end else begin
            if (tile_b_sram_cs_o_w) begin
                if (tile_b_sram_we_o_w) begin
                    tile_b_sram_model_array[tile_b_sram_addr_o_w] <= tile_b_sram_wdata_o_w;
                    tile_b_sram_rdata_i_tb <= {RAM_DATA_WIDTH_TB{1'bx}};
                end else begin
                    tile_b_sram_rdata_i_tb <= tile_b_sram_model_array[tile_b_sram_addr_o_w];
                end
            end else begin
                tile_b_sram_rdata_i_tb <= {RAM_DATA_WIDTH_TB{1'bx}};
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
        // VCD dump setup
        $dumpfile("gate_sim_waves.vcd");
        $dumpvars(0, tb_gate_accelerator); // Dump all signals in this module and below

        clk_tb = 1'b0;
        rst_n_tb = 1'b0;
        start_computation_tb = 1'b0;
        // mm_rdata_i_tb initialization removed as it's a wire
        mm_ready_i_tb = 1'b0;
        tile_a_sram_rdata_i_tb = {RAM_DATA_WIDTH_TB{1'b0}};
        tile_b_sram_rdata_i_tb = {RAM_DATA_WIDTH_TB{1'b0}};
        start_time_reg_set = 1'b0;
        start_sim_time = 0;
        end_sim_time = 0;

        $timeformat(-9, 3, " ns", 10); // 3 decimal places for ns

        #(CLK_PERIOD_TB * 2.5);
        rst_n_tb = 1'b1;
        #(CLK_PERIOD_TB * 0.5);
        $display("[%0t TB] Reset released.", $time);

        #(CLK_PERIOD_TB * 2);

        $display("[%0t TB] Asserting start_computation.", $time);
        start_computation_tb = 1'b1;
        start_sim_time = $time; // Record start time more precisely
        start_time_reg_set = 1'b1;

        #(CLK_PERIOD_TB);
        start_computation_tb = 1'b0;
        $display("[%0t TB] De-asserted start_computation.", $time);

        $display("[%0t TB] Waiting for computation_done_tb signal...", $time);
        wait (computation_done_tb == 1'b1);
        end_sim_time = $time; // Record end time
        $display("[%0t TB] computation_done_tb asserted by accelerator.", $time);
        if (start_time_reg_set) begin
             $display("[%0t TB] Execution time: %0t ns", $time, (end_sim_time - start_sim_time));
        end

        #(CLK_PERIOD_TB); 
        
        fid = $fopen("result_mem.csv", "w");
        if (fid != 0) begin
            // MODIFIED: Corrected for loop for Verilog-2005 (no break)
            for (k = 0; (k < TOTAL_SINT32_WORDS_C_SIM) && ((BASE_ADDR_C_MM_TB + k) < MAIN_MEM_SIZE_TB); k = k + 1) begin
                $fdisplay(fid, "%h", main_memory_model_array[BASE_ADDR_C_MM_TB + k]);
            end
            $fclose(fid);
            $display("[%0t TB] Result C matrix dumped to result_mem.csv.", $time);
        end else begin
            $display("[%0t TB] ERROR: Could not open result_mem.csv for writing.", $time);
        end

        #(CLK_PERIOD_TB * 10);
        $display("[%0t TB] Test finished.", $time);
        $finish;
    end

    // Clock generator
    always # (CLK_PERIOD_TB / 2) clk_tb = ~clk_tb;

endmodule