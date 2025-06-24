`timescale 1ns / 1ps

module tb_sa_enhanced_accumulator;

    // --- Parameters ---
    localparam SIZE = 16;
    localparam INPUT_DATA_WIDTH = 8;
    localparam PE_ACCUM_DATA_WIDTH = 32;
    localparam ROW_WIDTH_BITS = SIZE * PE_ACCUM_DATA_WIDTH;
    localparam CLK_PERIOD = 10;
    localparam NUM_K_ITERATIONS_TO_TEST = 32; // Test with 1 K-iteration

    // SRAM B Port parameters
    localparam BUS_DATA_WIDTH_SRAM_B = 512;
    localparam WORDS_PER_ROW_SRAM_B  = ROW_WIDTH_BITS / BUS_DATA_WIDTH_SRAM_B;
    localparam TOTAL_WORDS_SRAM_B    = SIZE * WORDS_PER_ROW_SRAM_B;


    // --- Testbench Signals ---
    reg clk;
    reg rst_n;

    // SA Control Inputs
    reg start_new_k_iteration;
    reg activate_pe_computation;

    // SA Data Inputs
    // reg array_data_valid_in; // This signal is removed from DUT
    reg [SIZE*INPUT_DATA_WIDTH-1:0] array_a_in_tb;
    reg [SIZE*INPUT_DATA_WIDTH-1:0] array_b_in_tb;
    reg [SIZE-1:0] array_a_valid_tb; // For the new indywidual valid port
    reg [SIZE-1:0] array_b_valid_tb; // For the new indywidual valid port

    // SA Status Outputs
    wire sa_k_iteration_accum_done;
    wire sa_busy;

    // SRAM C Interface wires
    wire [$clog2(SIZE)-1:0]           sram_c_raddr_A_from_sa;
    wire [ROW_WIDTH_BITS-1:0]         sram_c_rdata_A_to_sa;
    wire [$clog2(SIZE)-1:0]           sram_c_waddr_from_sa;
    wire signed [ROW_WIDTH_BITS-1:0]  sram_c_wdata_from_sa;
    wire                               sram_c_we_from_sa;

    // TB control for SRAM Port B read
    reg [$clog2(TOTAL_WORDS_SRAM_B)-1:0] tb_sram_c_raddr_B;
    wire [BUS_DATA_WIDTH_SRAM_B-1:0]     tb_sram_c_rdata_B;

    // --- Data Storage for Verification ---
    reg signed [INPUT_DATA_WIDTH-1:0]   a_tiles_tb [0:NUM_K_ITERATIONS_TO_TEST-1][SIZE-1:0][SIZE-1:0];
    reg signed [INPUT_DATA_WIDTH-1:0]   b_tiles_tb [0:NUM_K_ITERATIONS_TO_TEST-1][SIZE-1:0][SIZE-1:0];
    reg signed [PE_ACCUM_DATA_WIDTH-1:0] expected_c_tile_tb [SIZE-1:0][SIZE-1:0];
    reg signed [PE_ACCUM_DATA_WIDTH-1:0] actual_c_from_sram_tb [SIZE-1:0][SIZE-1:0];
    reg signed [PE_ACCUM_DATA_WIDTH-1:0] partial_product_tile_tb [SIZE-1:0][SIZE-1:0];


    // --- TB Internal Variables ---
    integer r, c, k_loop, k_iter;
    integer error_count;
    reg test_passed;
    integer t_feed;
    integer sa_boundary_idx_local;
    integer a_feed_col_idx_local;
    integer b_feed_row_idx_local;
    reg signed [INPUT_DATA_WIDTH-1:0] val_a_to_feed_local;
    reg signed [INPUT_DATA_WIDTH-1:0] val_b_to_feed_local;
    reg [SIZE*INPUT_DATA_WIDTH-1:0] skewed_a_packed_local;
    reg [SIZE*INPUT_DATA_WIDTH-1:0] skewed_b_packed_local;
    reg [SIZE-1:0] skewed_a_valid_packed_local;
    reg [SIZE-1:0] skewed_b_valid_packed_local;
    integer sram_read_r_local;
    integer sram_read_k_word_local;
    integer sram_base_col_idx_local;


    // --- DUT Instantiation (FIXED) ---
    sa_enhanced #(
        .SIZE(SIZE),
        .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH),
        .PE_ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH)
    ) dut_sa_enhanced (
        .clk(clk),
        .rst_n(rst_n),
        .start_new_k_iteration(start_new_k_iteration),
        .activate_pe_computation(activate_pe_computation),
        
        // --- Incompatible ports removed/updated ---
        // .array_data_valid_in(array_data_valid_in),                 // REMOVED
        // .array_a_valid_in(array_a_valid_tb),                      // REPLACED
        // .array_b_valid_in(array_b_valid_tb),                      // REPLACED
        .array_a_valid_in_indywidual(array_a_valid_tb),         // NEW CONNECTION
        .array_b_valid_in_indywidual(array_b_valid_tb),         // NEW CONNECTION

        .array_a_in(array_a_in_tb),
        .array_b_in(array_b_in_tb),

        .sa_k_iteration_accum_done(sa_k_iteration_accum_done),
        .sa_busy(sa_busy),
        .sram_c_raddr_A_to_sram(sram_c_raddr_A_from_sa),
        .sram_c_rdata_A_from_sram(sram_c_rdata_A_to_sa),
        .sram_c_waddr_to_sram(sram_c_waddr_from_sa),
        .sram_c_wdata_to_sram(sram_c_wdata_from_sa),
        .sram_c_we_to_sram(sram_c_we_from_sa)
    );

    sram_c_accum #(
        .NUM_ROWS(SIZE),
        .ELEM_PER_ROW(SIZE),
        .ELEM_WIDTH(PE_ACCUM_DATA_WIDTH),
        .BUS_DATA_WIDTH(BUS_DATA_WIDTH_SRAM_B)
    ) dut_sram_c (
        .clk(clk),
        .rst_n(rst_n),
        .we(sram_c_we_from_sa),
        .waddr(sram_c_waddr_from_sa),
        .wdata(sram_c_wdata_from_sa),
        .raddr_A(sram_c_raddr_A_from_sa),
        .rdata_A(sram_c_rdata_A_to_sa),
        .raddr_B(tb_sram_c_raddr_B),
        .rdata_B(tb_sram_c_rdata_B)
    );

    // Clock generation
    initial begin
        clk = 0;
        forever begin
            #(CLK_PERIOD/2) clk = ~clk;
        end
    end

    // Data initialization and expected result calculation
    initial begin
        for (k_iter = 0; k_iter < NUM_K_ITERATIONS_TO_TEST; k_iter = k_iter + 1) begin
            for (r = 0; r < SIZE; r = r + 1) begin
                for (c = 0; c < SIZE; c = c + 1) begin
                    a_tiles_tb[k_iter][r][c] = (k_iter + r + c)%7 + 1; 
                    b_tiles_tb[k_iter][r][c] = (k_iter + r + c)%7 + 2; 
                end
            end
        end
        $display("[%0t] [TB_INIT] A and B tiles Initialized.", $time);

        for (r = 0; r < SIZE; r = r + 1) begin
            for (c = 0; c < SIZE; c = c + 1) begin
                expected_c_tile_tb[r][c] = 0;
            end
        end

        for (k_iter = 0; k_iter < NUM_K_ITERATIONS_TO_TEST; k_iter = k_iter + 1) begin
            for (r = 0; r < SIZE; r = r + 1) begin
                for (c = 0; c < SIZE; c = c + 1) begin
                    partial_product_tile_tb[r][c] = 0;
                    for (k_loop = 0; k_loop < SIZE; k_loop = k_loop + 1) begin
                        partial_product_tile_tb[r][c] = partial_product_tile_tb[r][c] +
                                                     (a_tiles_tb[k_iter][r][k_loop] * b_tiles_tb[k_iter][k_loop][c]);
                    end
                    expected_c_tile_tb[r][c] = expected_c_tile_tb[r][c] + partial_product_tile_tb[r][c];
                end
            end
        end
        $display("[%0t] [TB_INIT] Expected C_tile (accumulated) calculated.", $time);
    end


    // Main test sequence
    initial begin
        rst_n = 1'b0;
        start_new_k_iteration = 1'b0;
        activate_pe_computation = 1'b0;
        // array_data_valid_in = 1'b0; // REMOVED
        array_a_in_tb = 0;
        array_b_in_tb = 0;
        array_a_valid_tb = 0;
        array_b_valid_tb = 0;
        tb_sram_c_raddr_B = 0;
        error_count = 0;
        test_passed = 1'b1;

        $display("[%0t] [TB] Testbench Initialized.", $time);
        #(CLK_PERIOD * 5);
        rst_n = 1'b1;
        $display("[%0t] [TB] Reset Released. SRAM C should be zeroed by sram_c_accum's reset.", $time);

        // Loop for K-iterations
        for (k_iter = 0; k_iter < NUM_K_ITERATIONS_TO_TEST; k_iter = k_iter + 1) begin
            $display("[%0t] [TB_K_ITER_DRV] Driving K-iteration %0d / %0d", $time, k_iter, NUM_K_ITERATIONS_TO_TEST-1);

            @(posedge clk);
            start_new_k_iteration = 1'b1;
            activate_pe_computation = 1'b1; 
            @(posedge clk);
            start_new_k_iteration = 1'b0;

            $display("[%0t] [TB_K_ITER_DRV] Feeding data for K-iter %0d...", $time, k_iter);
            for (t_feed = 0; t_feed < (2*SIZE - 1); t_feed = t_feed + 1) begin
                for (sa_boundary_idx_local = 0; sa_boundary_idx_local < SIZE; sa_boundary_idx_local = sa_boundary_idx_local + 1) begin
                    a_feed_col_idx_local = t_feed - sa_boundary_idx_local;
                    if (a_feed_col_idx_local >= 0 && a_feed_col_idx_local < SIZE) begin
                        val_a_to_feed_local = a_tiles_tb[k_iter][sa_boundary_idx_local][a_feed_col_idx_local];
                        skewed_a_valid_packed_local[sa_boundary_idx_local] = 1'b1; // A data valid
                    end else begin
                        val_a_to_feed_local = 0;
                        skewed_a_valid_packed_local[sa_boundary_idx_local] = 1'b0; // A data invalid (padding)
                    end
                    skewed_a_packed_local[sa_boundary_idx_local*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] = val_a_to_feed_local;

                    b_feed_row_idx_local = t_feed - sa_boundary_idx_local;
                    if (b_feed_row_idx_local >= 0 && b_feed_row_idx_local < SIZE) begin
                        val_b_to_feed_local = b_tiles_tb[k_iter][b_feed_row_idx_local][sa_boundary_idx_local];
                        skewed_b_valid_packed_local[sa_boundary_idx_local] = 1'b1; // B data valid
                    end else begin
                        val_b_to_feed_local = 0;
                        skewed_b_valid_packed_local[sa_boundary_idx_local] = 1'b0; // B data invalid (padding)
                    end
                    skewed_b_packed_local[sa_boundary_idx_local*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] = val_b_to_feed_local;
                end
                array_a_in_tb <= skewed_a_packed_local;
                array_b_in_tb <= skewed_b_packed_local;
                array_a_valid_tb <= skewed_a_valid_packed_local;
                array_b_valid_tb <= skewed_b_valid_packed_local;
                @(posedge clk);
            end
            // array_data_valid_in <= 1'b0; // REMOVED
            array_a_valid_tb <= 0; // Stop driving valid signals
            array_b_valid_tb <= 0; // Stop driving valid signals
            
            $display("[%0t] [TB_K_ITER_DRV] Data feeding for K-iter %0d finished. Waiting for sa_k_iteration_accum_done...", $time, k_iter);

            // Wait for SA to complete this K-iteration's accumulation
            fork : k_iteration_watchdog
                begin : done_watcher
                    wait (sa_k_iteration_accum_done == 1'b1);
                    $display("[%0t] [TB_K_ITER_DRV] sa_k_iteration_accum_done received for K-iter %0d.", $time, k_iter);
                    disable timeout_watcher;
                end
                begin : timeout_watcher
                    #(CLK_PERIOD * 200);
                    $error("[%0t] [TB_TIMEOUT] Timeout waiting for sa_k_iteration_accum_done for K-iter %0d", $time, k_iter);
                    test_passed = 1'b0;
                    $finish;
                end
            join : k_iteration_watchdog

            activate_pe_computation <= 1'b0;
            @(posedge clk);
        end

        // All K-iterations finished. Read final results from SRAM C via Port B.
        $display("[%0t] [TB] All K-iterations finished. Reading final results from SRAM C...", $time);
        @(posedge clk); 

        for (sram_read_r_local = 0; sram_read_r_local < SIZE; sram_read_r_local = sram_read_r_local + 1) begin
            for (sram_read_k_word_local = 0; sram_read_k_word_local < WORDS_PER_ROW_SRAM_B; sram_read_k_word_local = sram_read_k_word_local + 1) begin
                tb_sram_c_raddr_B = sram_read_r_local * WORDS_PER_ROW_SRAM_B + sram_read_k_word_local;
                @(posedge clk); 
                @(posedge clk); 
                
                sram_base_col_idx_local = sram_read_k_word_local * (BUS_DATA_WIDTH_SRAM_B / PE_ACCUM_DATA_WIDTH);
                for (integer elem_idx = 0; elem_idx < (BUS_DATA_WIDTH_SRAM_B / PE_ACCUM_DATA_WIDTH); elem_idx = elem_idx + 1) begin
                    if (sram_base_col_idx_local + elem_idx < SIZE) begin
                        actual_c_from_sram_tb[sram_read_r_local][sram_base_col_idx_local + elem_idx] =
                            tb_sram_c_rdata_B[elem_idx*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH];
                    end
                end
            end
        end
        $display("[%0t] [TB] Finished reading from SRAM C.", $time);

        $display("[%0t] [TB_CONTENT_CHECK] Before final comparison (actual_c_from_sram_tb content):", $time);
        $display("    actual_c_from_sram_tb[0][0] = %10d (%h)", actual_c_from_sram_tb[0][0], actual_c_from_sram_tb[0][0]);
        $display("    actual_c_from_sram_tb[0][1] = %10d (%h)", actual_c_from_sram_tb[0][1], actual_c_from_sram_tb[0][1]);
        $display("    actual_c_from_sram_tb[1][0] = %10d (%h)", actual_c_from_sram_tb[1][0], actual_c_from_sram_tb[1][0]);
        $display("    actual_c_from_sram_tb[1][1] = %10d (%h)", actual_c_from_sram_tb[1][1], actual_c_from_sram_tb[1][1]);

        $display("[%0t] [TB] Verifying results...", $time);
        error_count = 0;
        for (r = 0; r < SIZE; r = r + 1) begin
            for (c = 0; c < SIZE; c = c + 1) begin
                if (actual_c_from_sram_tb[r][c] !== expected_c_tile_tb[r][c]) begin
                    $display("[%0t] [TB_VERIFY_ERR] Mismatch at C[%2d][%2d]: Expected = %d, Actual = %d",
                             $time, r, c, expected_c_tile_tb[r][c], actual_c_from_sram_tb[r][c]);
                    error_count = error_count + 1;
                    test_passed = 1'b0;
                end
            end
        end

        if (test_passed) begin
            $display("----------------------------------------------------------");
            $display("[%0t] [TB] SUCCESS: All computations for SA enhanced (with accumulation) are correct!", $time);
            $display("----------------------------------------------------------");
        end else begin
            $display("----------------------------------------------------------");
            $error("[%0t] [TB] FAILURE: %d mismatches found.", $time, error_count);
            $display("----------------------------------------------------------");
        end
        $finish;
    end

endmodule
