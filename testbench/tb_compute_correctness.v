//
// Filename: tb_compute_correctness.v
// Description: Testbench to verify computational correctness of the accelerator path.
//              MODIFIED: Simulates accumulation for C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0] + A[0][2]*B[2][0]
//                        using 16x16 tiles.
//
`timescale 1ns / 1ps

module tb_compute_correctness;

    // --- Parameters ---
    localparam TILE_SIZE                 = 16;
    localparam INPUT_DATA_WIDTH          = 8;
    localparam PE_ACCUM_DATA_WIDTH       = 32;
    localparam MAIN_MEM_DATA_WIDTH_BITS  = TILE_SIZE * PE_ACCUM_DATA_WIDTH; //512
    localparam ACCUM_PIPE_DELAY          = 2;
    localparam CLK_PERIOD                = 10;
    localparam BUS_DATA_WIDTH_SRAM_B     = 64; // For reading C SRAM via port B
    localparam WORDS_PER_ROW_SRAM_B      = MAIN_MEM_DATA_WIDTH_BITS / BUS_DATA_WIDTH_SRAM_B; // 512 / 64 = 8
    localparam TOTAL_WORDS_SRAM_B        = TILE_SIZE * WORDS_PER_ROW_SRAM_B; // 16 * 8 = 128
    localparam NUM_K_ITERATIONS          = 3; // For C00 = A00*B00 + A01*B10 + A02*B20

    // --- Testbench Control & Wires ---
    reg  clk;
    reg  rst_n;
    reg  compute_req;

    // --- Data Formatter Outputs (Unpacked and Packed) ---
    reg  signed [INPUT_DATA_WIDTH-1:0] skewed_a_to_sa_unpacked [0:TILE_SIZE-1];
    reg  signed [INPUT_DATA_WIDTH-1:0] skewed_b_to_sa_unpacked [0:TILE_SIZE-1];
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] skewed_a_to_sa_packed;
    wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] skewed_b_to_sa_packed;
    reg  formatter_valid_out_to_sa;

    // --- DUT Interface Wires ---
    wire compute_busy;
    wire compute_done;
    wire ctrl_start_new_systolic_pass;
    wire ctrl_activate_pe_computation;
    wire tile_all_pes_done_one_pass;

    // --- SA <-> Compute Controller Handshake ---
    wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] sa_partial_sum_out;
    wire sa_partial_sum_valid;
    wire [$clog2(TILE_SIZE)-1:0] sa_partial_sum_row_idx;

    // --- Compute Controller <-> Final Adder <-> C_SRAM ---
    wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] ctrl_c_data_to_sa;
    wire ctrl_enable_final_add;
    wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] ctrl_partial_sum_to_sa;
    wire signed [MAIN_MEM_DATA_WIDTH_BITS-1:0] sa_final_sum_in;

    // C_SRAM Interface wires
    wire [$clog2(TILE_SIZE)-1:0] c_accum_waddr;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0] c_accum_wdata;
    wire c_accum_we;
    wire [$clog2(TILE_SIZE)-1:0] c_accum_raddr_A; // Port A address from controller
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0] c_accum_rdata_A; // Port A data to controller

    // TB control for SRAM Port B read
    reg [$clog2(TOTAL_WORDS_SRAM_B)-1:0] tb_sram_c_raddr_B;
    wire [BUS_DATA_WIDTH_SRAM_B-1:0] tb_sram_c_rdata_B;

    // --- Data Storage for Verification ---
    // Store 3 tiles for A and 3 for B
    reg signed [INPUT_DATA_WIDTH-1:0]   a_tiles [0:NUM_K_ITERATIONS-1][TILE_SIZE-1:0][TILE_SIZE-1:0];
    reg signed [INPUT_DATA_WIDTH-1:0]   b_tiles [0:NUM_K_ITERATIONS-1][TILE_SIZE-1:0][TILE_SIZE-1:0];
    // Expected C is for one 16x16 tile (C00)
    reg signed [PE_ACCUM_DATA_WIDTH-1:0] expected_c_tile [TILE_SIZE-1:0][TILE_SIZE-1:0];
    // Actual C read from SRAM (one 16x16 tile)
    reg signed [PE_ACCUM_DATA_WIDTH-1:0] actual_c_from_sram [TILE_SIZE-1:0][TILE_SIZE-1:0];
    // Temporary storage for partial products A_tile * B_tile
    reg signed [PE_ACCUM_DATA_WIDTH-1:0] partial_product_tile [TILE_SIZE-1:0][TILE_SIZE-1:0];


    // --- Testbench internal variables ---
    integer r, c, k_loop_var, k_tile_iter;
    integer error_count;
    reg test_passed;
    reg compute_completed_flag;
    integer i; // General purpose iterator
    integer t_feed;
    integer sa_boundary_idx;
    integer a_feed_col_idx;
    integer b_feed_row_idx;
    reg signed [INPUT_DATA_WIDTH-1:0] val_a_to_feed;
    reg signed [INPUT_DATA_WIDTH-1:0] val_b_to_feed;
    integer sram_read_r;
    integer sram_read_k_word;
    integer sram_base_col_idx;
    reg [($clog2(TOTAL_WORDS_SRAM_B))-1:0] current_addr_b; // Temporary reg for display
    reg signed [PE_ACCUM_DATA_WIDTH-1:0] elem0, elem1; // Temp for display


    //======================================================================
    //== Packer Logic: Unpacked array (reg) to packed vector (wire)
    //======================================================================
    genvar gidx;
    generate
        for (gidx = 0; gidx < TILE_SIZE; gidx = gidx + 1) begin : packer
            assign skewed_a_to_sa_packed[(gidx+1)*INPUT_DATA_WIDTH-1 : gidx*INPUT_DATA_WIDTH] = skewed_a_to_sa_unpacked[gidx];
            assign skewed_b_to_sa_packed[(gidx+1)*INPUT_DATA_WIDTH-1 : gidx*INPUT_DATA_WIDTH] = skewed_b_to_sa_unpacked[gidx];
        end
    endgenerate


    //======================================================================
    //== DUT Instantiations
    //======================================================================
    systolic_array #(
        .SIZE(TILE_SIZE), .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH), .PE_ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH)
    ) i_sa (
        .clk(clk), .rst_n(rst_n),
        .clear_all_pe_accumulators(1'b0), // Let SA clear on start_new_systolic_pass
        .conditionally_clear_pe_sums_level(1'b1), // Enable conditional clear
        .activate_pe_computation(ctrl_activate_pe_computation),
        .array_data_valid_in(formatter_valid_out_to_sa),
        .array_a_in(skewed_a_to_sa_packed),
        .array_b_in(skewed_b_to_sa_packed),
        .tile_row_result_out(sa_partial_sum_out),
        .tile_row_result_valid(sa_partial_sum_valid),
        .sa_partial_sum_row_idx(sa_partial_sum_row_idx),
        .tile_all_pes_done_one_pass(tile_all_pes_done_one_pass),
        .start_new_systolic_pass(ctrl_start_new_systolic_pass),
        .array_a_data_valid_out(), .array_a_out(), .array_b_data_valid_out(), .array_b_out()
    );

    compute_controller #(
        .TILE_SIZE(TILE_SIZE), .PE_ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH), .ACCUM_PIPE_DELAY(ACCUM_PIPE_DELAY)
    ) i_comp (
        .clk(clk), .rst_n(rst_n),
        .compute_req(compute_req), .compute_busy(compute_busy), .compute_done(compute_done),
        .dut_ready_for_sa_partial_sum(),
        .sa_partial_sum_valid(sa_partial_sum_valid), .sa_partial_sum_in(sa_partial_sum_out),
        .sa_partial_sum_row_idx(sa_partial_sum_row_idx), .sa_final_sum_in(sa_final_sum_in),
        .sa_tile_all_pes_done_one_pass(tile_all_pes_done_one_pass),
        .ctrl_start_new_systolic_pass(ctrl_start_new_systolic_pass),
        .ctrl_activate_pe_computation(ctrl_activate_pe_computation),
        .ctrl_c_data_to_sa(ctrl_c_data_to_sa), .ctrl_enable_final_add(ctrl_enable_final_add),
        .ctrl_partial_sum_to_sa(ctrl_partial_sum_to_sa),
        .c_accum_raddr(c_accum_raddr_A), .c_accum_rdata(c_accum_rdata_A),
        .c_accum_waddr(c_accum_waddr), .c_accum_wdata(c_accum_wdata), .c_accum_we(c_accum_we)
    );

    sram_c_accum #(
        .NUM_ROWS(TILE_SIZE), .ELEM_PER_ROW(TILE_SIZE), .ELEM_WIDTH(PE_ACCUM_DATA_WIDTH),
        .BUS_DATA_WIDTH(BUS_DATA_WIDTH_SRAM_B)
    ) i_sram_c (
        .clk(clk), .rst_n(rst_n), .we(c_accum_we), .waddr(c_accum_waddr), .wdata(c_accum_wdata),
        .raddr_A(c_accum_raddr_A), .rdata_A(c_accum_rdata_A),
        .raddr_B(tb_sram_c_raddr_B), .rdata_B(tb_sram_c_rdata_B)
    );

    assign sa_final_sum_in = ctrl_enable_final_add ? (ctrl_partial_sum_to_sa + ctrl_c_data_to_sa) : {MAIN_MEM_DATA_WIDTH_BITS{1'b0}};

    //======================================================================
    //== Test Sequence
    //======================================================================
    initial begin
        clk = 0;
        forever begin
            #(CLK_PERIOD/2) clk = ~clk;
        end
    end

    initial begin
        // Initialize A and B tiles
        // For C00 = A00*B00 + A01*B10 + A02*B20
        // A_tiles[0] = A00, A_tiles[1] = A01, A_tiles[2] = A02
        // B_tiles[0] = B00, B_tiles[1] = B10, B_tiles[2] = B20
        for (k_tile_iter = 0; k_tile_iter < NUM_K_ITERATIONS; k_tile_iter = k_tile_iter + 1) begin
            for (r = 0; r < TILE_SIZE; r = r + 1) begin
                for (c = 0; c < TILE_SIZE; c = c + 1) begin
                    // Simple pattern: A_tile[k][r][c] = k_val + r_val + c_val + 1
                    // B_tile[k][r][c] = k_val + r_val + c_val + 2 (ensure different from A)
                    // Keep values small to avoid overflow with 3 accumulations for 8-bit inputs
                    a_tiles[k_tile_iter][r][c] = (k_tile_iter + r + c)%5 + 1;
                    b_tiles[k_tile_iter][r][c] = (k_tile_iter + r + c)%5 + 2;
                end
            end
        end
        $display("[%0t] [TB] A and B tiles Initialized.", $time);

        // Calculate expected_c_tile (C00)
        // Initialize expected_c_tile to 0
        for (r = 0; r < TILE_SIZE; r = r + 1) begin
            for (c = 0; c < TILE_SIZE; c = c + 1) begin
                expected_c_tile[r][c] = 0;
            end
        end

        // Accumulate products: expected_C00 = sum(A0k * Bk0)
        for (k_tile_iter = 0; k_tile_iter < NUM_K_ITERATIONS; k_tile_iter = k_tile_iter + 1) begin
            // Calculate current A_tile * B_tile product
            for (r = 0; r < TILE_SIZE; r = r + 1) begin
                for (c = 0; c < TILE_SIZE; c = c + 1) begin
                    partial_product_tile[r][c] = 0;
                    for (k_loop_var = 0; k_loop_var < TILE_SIZE; k_loop_var = k_loop_var + 1) begin
                        partial_product_tile[r][c] = partial_product_tile[r][c] +
                                                     (a_tiles[k_tile_iter][r][k_loop_var] * b_tiles[k_tile_iter][k_loop_var][c]);
                    end
                    // Add this partial product to the overall expected_c_tile
                    expected_c_tile[r][c] = expected_c_tile[r][c] + partial_product_tile[r][c];
                end
            end
        end
        $display("[%0t] [TB] Expected C_tile (C00) calculated.", $time);
    end


    initial begin
        rst_n = 1'b0;
        compute_req = 1'b0;
        formatter_valid_out_to_sa = 1'b0;
        tb_sram_c_raddr_B = 0;
        error_count = 0;
        test_passed = 1'b1;
        compute_completed_flag = 1'b0;

        for (i = 0; i < TILE_SIZE; i = i + 1) begin
            skewed_a_to_sa_unpacked[i] = 0;
            skewed_b_to_sa_unpacked[i] = 0;
        end

        $display("[%0t] [TB] Testbench Initialized.", $time);
        #(CLK_PERIOD * 5);
        rst_n = 1'b1;
        $display("[%0t] [TB] Reset Released. SRAM C should be zeroed.", $time);

        // --- Loop for K-iterations ---
        for (k_tile_iter = 0; k_tile_iter < NUM_K_ITERATIONS; k_tile_iter = k_tile_iter + 1) begin
            $display("[%0t] [TB_K_ITER_START] Starting K-iteration %0d / %0d", $time, k_tile_iter, NUM_K_ITERATIONS-1);

            @(posedge clk);
            compute_req = 1'b1;
            @(posedge clk);
            compute_req = 1'b0;

            $display("[%0t] [TB_K_ITER] compute_req pulsed for K-iter %0d. Waiting for start_pass...", $time, k_tile_iter);
            wait (ctrl_start_new_systolic_pass == 1'b1);
            $display("[%0t] [TB_K_ITER] ctrl_start_new_systolic_pass detected for K-iter %0d! Simulating data formatter...", $time, k_tile_iter);

            // Data Feeding (Skewing) for current A_tile and B_tile
            for (t_feed = 0; t_feed < (2*TILE_SIZE - 1); t_feed = t_feed + 1) begin
                formatter_valid_out_to_sa <= 1'b1;

                // Debug display for first few and last few feed cycles
                if (t_feed < 3 || t_feed > (2*TILE_SIZE-1 - 4)) begin
                    $display("------------------------------------------------------------------------------------");
                    $display("[%0t] [TB_FEED_CYCLE_START] K_iter=%0d, t_feed=%0d", $time, k_tile_iter, t_feed);
                end

                for (sa_boundary_idx = 0; sa_boundary_idx < TILE_SIZE; sa_boundary_idx = sa_boundary_idx + 1) begin
                    // Calculate A value from a_tiles[k_tile_iter]
                    a_feed_col_idx = t_feed - sa_boundary_idx;
                    if (a_feed_col_idx >= 0 && a_feed_col_idx < TILE_SIZE) begin
                        val_a_to_feed = a_tiles[k_tile_iter][sa_boundary_idx][a_feed_col_idx];
                    end else begin
                        val_a_to_feed = 0;
                    end
                    skewed_a_to_sa_unpacked[sa_boundary_idx] <= val_a_to_feed;

                    // Calculate B value from b_tiles[k_tile_iter]
                    b_feed_row_idx = t_feed - sa_boundary_idx;
                    if (b_feed_row_idx >= 0 && b_feed_row_idx < TILE_SIZE) begin
                        val_b_to_feed = b_tiles[k_tile_iter][b_feed_row_idx][sa_boundary_idx];
                    end else begin
                        val_b_to_feed = 0;
                    end
                    skewed_b_to_sa_unpacked[sa_boundary_idx] <= val_b_to_feed;
                end // end sa_boundary_idx loop

                @(posedge clk);

                // Debug display for data seen by SA
                if (t_feed < 3 || t_feed > (2*TILE_SIZE-1 - 4)) begin
                    $display("[%0t] [TB_FEED_SA_SEES] K_iter=%0d, t_feed=%0d (Data on bus)", $time, k_tile_iter, t_feed);
                    $display("                      formatter_valid_out_to_sa: %b", formatter_valid_out_to_sa);
                    // Optionally display some skewed_a/b values
                end
            end // End of t_feed loop

            formatter_valid_out_to_sa <= 1'b0;
            for (i = 0; i < TILE_SIZE; i = i + 1) begin
                skewed_a_to_sa_unpacked[i] <= 0;
                skewed_b_to_sa_unpacked[i] <= 0;
            end

            $display("[%0t] [TB_K_ITER] Data feeding for K-iter %0d finished. Waiting for compute_done...", $time, k_tile_iter);

            compute_completed_flag = 1'b0; // Reset flag before waiting
            fork : wait_for_one_k_iter_done
                begin
                    wait (compute_done == 1'b1);
                    compute_completed_flag = 1'b1;
                    $display("[%0t] [TB_K_ITER] compute_done was asserted for K-iter %0d!", $time, k_tile_iter);
                    disable wait_for_one_k_iter_done;
                end
                begin
                    #(CLK_PERIOD * (2*TILE_SIZE + TILE_SIZE + ACCUM_PIPE_DELAY + 50)); // Adjusted timeout for one tile pass
                    if (!compute_completed_flag) begin
                        $display("----------------------------------------------------------");
                        $error("[%0t] [TB_K_ITER_TIMEOUT] K-iter %0d: compute_done was NOT asserted.", $time, k_tile_iter);
                        $display("----------------------------------------------------------");
                        test_passed = 1'b0; $finish;
                    end
                end
            join
            $display("[%0t] [TB_K_ITER_END] K-iteration %0d completed. SRAM C should be updated.", $time, k_tile_iter);
        end // End of k_tile_iter loop

        $display("[%0t] [TB] All K-iterations finished. Reading final results from SRAM C...", $time);
        @(posedge clk);

        for (sram_read_r = 0; sram_read_r < TILE_SIZE; sram_read_r = sram_read_r + 1) begin
            for (sram_read_k_word = 0; sram_read_k_word < WORDS_PER_ROW_SRAM_B; sram_read_k_word = sram_read_k_word + 1) begin
                current_addr_b = sram_read_r * WORDS_PER_ROW_SRAM_B + sram_read_k_word;
                tb_sram_c_raddr_B = current_addr_b;

                // $display for Cycle 0
                // $display("[%0t] [TB_SRAM_READ_B] Cycle 0: Setting raddr_B = %d", $time, current_addr_b);

                @(posedge clk); // Cycle 1
                // $display for Cycle 1
                // $display("[%0t] [TB_SRAM_READ_B] Cycle 1: raddr_B=%d latched. rdata_B (prev)=%h", $time, tb_sram_c_raddr_B, tb_sram_c_rdata_B);

                @(posedge clk); // Cycle 2
                // $display for Cycle 2 (Extracted values)
                if (sram_read_r < 2 && sram_read_k_word < 2) begin // Limit extensive display
                     $display("[%0t] [TB_SRAM_READ_B] Cycle 2: raddr_B=%d. Valid rdata_B=%h. Extracting...",
                             $time, tb_sram_c_raddr_B, tb_sram_c_rdata_B);
                end

                sram_base_col_idx = sram_read_k_word * (BUS_DATA_WIDTH_SRAM_B / PE_ACCUM_DATA_WIDTH);

                if (sram_base_col_idx < TILE_SIZE) begin
                    elem0 = tb_sram_c_rdata_B[PE_ACCUM_DATA_WIDTH-1:0];
                    actual_c_from_sram[sram_read_r][sram_base_col_idx] = elem0;
                    if (sram_read_r < 2 && sram_base_col_idx < 4) begin // Limit display
                        $display("                      Extracted C[%0d][%0d] = %d (%h)", sram_read_r, sram_base_col_idx, elem0, elem0);
                    end
                end
                if (sram_base_col_idx + 1 < TILE_SIZE) begin
                    elem1 = tb_sram_c_rdata_B[BUS_DATA_WIDTH_SRAM_B-1 : PE_ACCUM_DATA_WIDTH];
                    actual_c_from_sram[sram_read_r][sram_base_col_idx+1] = elem1;
                     if (sram_read_r < 2 && (sram_base_col_idx+1) < 4) begin // Limit display
                        $display("                      Extracted C[%0d][%0d] = %d (%h)", sram_read_r, sram_base_col_idx+1, elem1, elem1);
                    end
                end
            end
        end
        $display("[%0t] [TB] Finished reading from SRAM C.", $time);

        // --- Content Check before final comparison (as per previous debug step) ---
        $display("------------------------------------------------------------------------------------");
        $display("[%0t] [TB_CONTENT_CHECK] Before final comparison (actual_c_from_sram content):", $time);
        $display("    actual_c_from_sram[0][0] = %10d (%h)", actual_c_from_sram[0][0], actual_c_from_sram[0][0]);
        $display("    actual_c_from_sram[0][1] = %10d (%h)", actual_c_from_sram[0][1], actual_c_from_sram[0][1]);
        $display("    actual_c_from_sram[0][2] = %10d (%h)", actual_c_from_sram[0][2], actual_c_from_sram[0][2]);
        $display("    actual_c_from_sram[0][3] = %10d (%h)", actual_c_from_sram[0][3], actual_c_from_sram[0][3]);
        $display("------------------------------------------------------------------------------------");

        $display("[%0t] [TB] Verifying results against accumulated expected_c_tile...", $time);
        error_count = 0;
        for (r = 0; r < TILE_SIZE; r = r + 1) begin
            for (c = 0; c < TILE_SIZE; c = c + 1) begin
                if (actual_c_from_sram[r][c] !== expected_c_tile[r][c]) begin
                    $display("[%0t] [TB_VERIFY_ERR] Mismatch at C_tile[0][0]'s element [%2d][%2d]: Expected_Accum = %d, Actual = %d",
                             $time, r, c, expected_c_tile[r][c], actual_c_from_sram[r][c]);
                    error_count = error_count + 1;
                    test_passed = 1'b0;
                end
            end
        end

        if (test_passed) begin
            $display("----------------------------------------------------------");
            $display("[%0t] [TB] SUCCESS: All computations for accumulated C_tile[0][0] are correct!", $time);
            $display("----------------------------------------------------------");
        end else begin
            $display("----------------------------------------------------------");
            $error("[%0t] [TB] FAILURE: %d mismatches found in accumulated C_tile[0][0].", $time, error_count);
            $display("----------------------------------------------------------");
        end
        $finish;
    end
endmodule