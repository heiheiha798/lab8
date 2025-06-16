// testbench_top.v
`timescale 1ns / 1ps

module testbench_top;

    localparam MATRIX_DIM_GLOBAL_TB = 128;
    localparam TILE_DIM_SYSTOLIC_TB = 16;
    localparam RAM_DATA_WIDTH_TB    = 64;
    localparam RAM_ADDR_WIDTH_TB    = 17;
    localparam SINT8_BITS_TB        = 8;
    localparam BF16_BITS_TB         = 16; // 虽然在 TB 中可能未使用，但保留以与 accelerator 参数匹配

    localparam CLK_PERIOD           = 10; // ns, for 100MHz clock

    // Derived parameters for memory layout
    localparam SINT8_PER_RAM_WORD_TB = RAM_DATA_WIDTH_TB / SINT8_BITS_TB;
    // localparam BF16_PER_RAM_WORD_TB  = RAM_DATA_WIDTH_TB / BF16_BITS_TB; // 保留，以防未来使用

    localparam TILES_PER_ROW_COL_GLOBAL_TB = MATRIX_DIM_GLOBAL_TB / TILE_DIM_SYSTOLIC_TB;
    localparam TILES_PER_ROW_COL_GLOBAL_TB_SAFE = (TILES_PER_ROW_COL_GLOBAL_TB == 0) ? 1 : TILES_PER_ROW_COL_GLOBAL_TB;

    localparam WORDS_PER_SINT8_TILE_CALC_TB = (TILE_DIM_SYSTOLIC_TB * TILE_DIM_SYSTOLIC_TB * SINT8_BITS_TB) / RAM_DATA_WIDTH_TB;
    localparam WORDS_PER_SINT8_TILE_TB = (WORDS_PER_SINT8_TILE_CALC_TB == 0 && (TILE_DIM_SYSTOLIC_TB * TILE_DIM_SYSTOLIC_TB * SINT8_BITS_TB) > 0) ? 1 : WORDS_PER_SINT8_TILE_CALC_TB;

    localparam TOTAL_SINT8_WORDS_A_TB  = WORDS_PER_SINT8_TILE_TB * TILES_PER_ROW_COL_GLOBAL_TB_SAFE * TILES_PER_ROW_COL_GLOBAL_TB_SAFE;
    localparam TOTAL_SINT8_WORDS_B_TB  = TOTAL_SINT8_WORDS_A_TB;

    localparam WORDS_PER_BF16_TILE_CALC_TB  = (TILE_DIM_SYSTOLIC_TB * TILE_DIM_SYSTOLIC_TB * BF16_BITS_TB) / RAM_DATA_WIDTH_TB;
    localparam WORDS_PER_BF16_TILE_TB = (WORDS_PER_BF16_TILE_CALC_TB == 0 && (TILE_DIM_SYSTOLIC_TB * TILE_DIM_SYSTOLIC_TB * BF16_BITS_TB) > 0) ? 1 : WORDS_PER_BF16_TILE_CALC_TB;
    localparam TOTAL_BF16_WORDS_C_TB   = WORDS_PER_BF16_TILE_TB * TILES_PER_ROW_COL_GLOBAL_TB_SAFE * TILES_PER_ROW_COL_GLOBAL_TB_SAFE;

    // Base Addresses in RAM
    localparam [RAM_ADDR_WIDTH_TB-1:0] BASE_ADDR_A_TB = 0;
    localparam [RAM_ADDR_WIDTH_TB-1:0] BASE_ADDR_B_TB = BASE_ADDR_A_TB + TOTAL_SINT8_WORDS_A_TB;
    localparam [RAM_ADDR_WIDTH_TB-1:0] BASE_ADDR_C_TB = BASE_ADDR_B_TB + TOTAL_SINT8_WORDS_B_TB;
    localparam [RAM_ADDR_WIDTH_TB-1:0] END_ADDR_B_LOAD_TB = BASE_ADDR_A_TB + TOTAL_SINT8_WORDS_A_TB + TOTAL_SINT8_WORDS_B_TB - 1;


    // Testbench signals
    reg clk_tb;
    reg rst_n_tb;
    reg start_computation_tb;
    wire computation_done_tb;

    // Accelerator RAM interface signals
    wire [RAM_ADDR_WIDTH_TB-1:0] acc_ram_address_tb;
    wire [RAM_DATA_WIDTH_TB-1:0] acc_ram_write_data_tb;
    wire [RAM_DATA_WIDTH_TB-1:0] acc_ram_read_data_tb;
    wire                         acc_ram_cs_tb;
    wire                         acc_ram_web_tb;

    integer output_file_desc;
    integer i_loop;

    // Instantiate Accelerator
    accelerator #(
        .MATRIX_DIM_GLOBAL(MATRIX_DIM_GLOBAL_TB),
        .TILE_DIM_SYSTOLIC(TILE_DIM_SYSTOLIC_TB),
        .RAM_DATA_WIDTH(RAM_DATA_WIDTH_TB),
        .RAM_ADDR_WIDTH(RAM_ADDR_WIDTH_TB),
        .SINT8_BITS(SINT8_BITS_TB),
        .BF16_BITS(BF16_BITS_TB)
    ) u_accelerator (
        .clk(clk_tb),
        .rst_n(rst_n_tb),
        .start_computation(start_computation_tb),
        .computation_done(computation_done_tb),
        .ram_address(acc_ram_address_tb),
        .ram_write_data(acc_ram_write_data_tb),
        .ram_read_data(acc_ram_read_data_tb),
        .ram_cs(acc_ram_cs_tb),
        .ram_web(acc_ram_web_tb),
        .base_addr_a(BASE_ADDR_A_TB),
        .base_addr_b(BASE_ADDR_B_TB),
        .base_addr_c(BASE_ADDR_C_TB)
    );

    // Instantiate RAM
    ram #(
        .DATA_WIDTH(RAM_DATA_WIDTH_TB),
        .ADDR_WIDTH(RAM_ADDR_WIDTH_TB)
    ) u_ram (
        .clk(clk_tb),
        .address(acc_ram_address_tb),
        .d(acc_ram_write_data_tb),
        .q(acc_ram_read_data_tb),
        .cs(acc_ram_cs_tb),
        .web(acc_ram_web_tb)
    );

    // Clock generation
    always begin
        #(CLK_PERIOD/2) clk_tb = ~clk_tb;
    end

    // Main test sequence
    initial begin
        // 1. Initialize signals
        clk_tb = 0;
        rst_n_tb = 0;
        start_computation_tb = 0;

        // 2. Apply reset
        #(CLK_PERIOD * 2);
        rst_n_tb = 1;
        #(CLK_PERIOD);

        // 3. Load input data
        $readmemh("input_mem.csv", u_ram.mem, BASE_ADDR_A_TB, END_ADDR_B_LOAD_TB);
        #(CLK_PERIOD); // Allow one cycle for $readmemh to potentially settle

        // 4. Start computation
        start_computation_tb = 1;
        #(CLK_PERIOD);
        start_computation_tb = 0;

        // 5. Wait for computation to complete
        wait (computation_done_tb == 1);
        #(CLK_PERIOD); // Wait one more cycle after done asserted

        // 6. Dump result matrix C
        output_file_desc = $fopen("result_mem.csv", "w");
        if (output_file_desc == 0) begin
        end else begin
            for (i_loop = 0; i_loop < TOTAL_BF16_WORDS_C_TB; i_loop = i_loop + 1) begin
                // $display("[TB_DUMP] Dumping u_ram.mem[%h (dec %0d)] = %h to result_mem.csv",
                //     BASE_ADDR_C_TB + i_loop, BASE_ADDR_C_TB + i_loop, u_ram.mem[BASE_ADDR_C_TB + i_loop]);
                $fdisplay(output_file_desc, "%h", u_ram.mem[BASE_ADDR_C_TB + i_loop]);
            end
            $fclose(output_file_desc);
        end

        // 7. Finish simulation (Verilator's C++ wrapper handles $finish via Verilated::gotFinish())
        #(CLK_PERIOD * 10); // Allow some time for final operations if any before $finish
        $finish;
    end

endmodule
