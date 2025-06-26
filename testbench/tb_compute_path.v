//
// Filename: tb_compute_path.v
// Description: Final, corrected version of the targeted testbench.
//              This version correctly instantiates the self-driving systolic
//              array and the compatible compute controller to test the handshake.
//
`timescale 1ns / 1ps

module tb_compute_path;

    // --- Parameters ---
    localparam TILE_SIZE                 = 16;
    localparam INPUT_DATA_WIDTH          = 8;
    localparam PE_ACCUM_DATA_WIDTH       = 32;
    localparam MAIN_MEM_DATA_WIDTH_BITS  = TILE_SIZE * PE_ACCUM_DATA_WIDTH;
    localparam ACCUM_PIPE_DELAY          = 2;
    localparam CLK_PERIOD                = 10;

    // --- Testbench Control & Wires ---
    reg  clk;
    reg  rst_n;
    reg  compute_req;

    // --- Simulated Data Formatter Outputs ---
    reg [TILE_SIZE*INPUT_DATA_WIDTH-1:0] skewed_a_to_sa;
    reg [TILE_SIZE*INPUT_DATA_WIDTH-1:0] skewed_b_to_sa;
    reg  formatter_valid_out_to_sa;
    
    // --- DUT Interface Wires ---
    wire compute_busy, compute_done;
    wire ctrl_start_new_systolic_pass, ctrl_activate_pe_computation;
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
    
    wire [$clog2(TILE_SIZE)-1:0] c_accum_waddr, c_accum_raddr;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0] c_accum_wdata, c_accum_rdata;
    wire c_accum_we;

    //======================================================================
    //== DUT Instantiations
    //======================================================================

    // --- MODIFIED: Systolic array instantiation is now corrected ---
    systolic_array #(
        .SIZE(TILE_SIZE), .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH), .PE_ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH)
    ) i_sa (
        .clk(clk), .rst_n(rst_n),
        .clear_all_pe_accumulators(1'b0),
        .conditionally_clear_pe_sums_level(1'b1),
        .activate_pe_computation(ctrl_activate_pe_computation),
        .array_data_valid_in(formatter_valid_out_to_sa),
        .array_a_in(skewed_a_to_sa),
        .array_b_in(skewed_b_to_sa),
        
        // Connect the SA's self-driven outputs to the corresponding wires
        .tile_row_result_out(sa_partial_sum_out),
        .tile_row_result_valid(sa_partial_sum_valid),
        .sa_partial_sum_row_idx(sa_partial_sum_row_idx), // <-- Correctly connected as an output

        .tile_all_pes_done_one_pass(tile_all_pes_done_one_pass),
        .start_new_systolic_pass(ctrl_start_new_systolic_pass)
    );
    
    // --- UNCHANGED: compute_controller instantiation is already correct ---
    compute_controller #(
        .TILE_SIZE(TILE_SIZE), .PE_ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH), .ACCUM_PIPE_DELAY(ACCUM_PIPE_DELAY)
    ) i_comp (
        .clk(clk), .rst_n(rst_n),
        .compute_req(compute_req), .compute_busy(compute_busy), .compute_done(compute_done),
        .dut_ready_for_sa_partial_sum(),
        .sa_partial_sum_valid(sa_partial_sum_valid),
        .sa_partial_sum_in(sa_partial_sum_out),
        .sa_partial_sum_row_idx(sa_partial_sum_row_idx), // <-- Correctly connected as an input
        .sa_final_sum_in(sa_final_sum_in),
        .sa_tile_all_pes_done_one_pass(tile_all_pes_done_one_pass),
        .ctrl_start_new_systolic_pass(ctrl_start_new_systolic_pass),
        .ctrl_activate_pe_computation(ctrl_activate_pe_computation),
        .ctrl_c_data_to_sa(ctrl_c_data_to_sa),
        .ctrl_enable_final_add(ctrl_enable_final_add),
        .ctrl_partial_sum_to_sa(ctrl_partial_sum_to_sa),
        .c_accum_raddr(c_accum_raddr), .c_accum_rdata(c_accum_rdata),
        .c_accum_waddr(c_accum_waddr), .c_accum_wdata(c_accum_wdata), .c_accum_we(c_accum_we)
    );
    
    // --- UNCHANGED: sram_c_accum instantiation is already correct ---
    sram_c_accum i_sram_c (
        .clk(clk),
        .we(c_accum_we),
        .waddr(c_accum_waddr),
        .wdata(c_accum_wdata),
        .raddr_A(c_accum_raddr),
        .rdata_A(c_accum_rdata),
        .raddr_B(7'b0),
        .rdata_B()
    );

    // Final adder model
    assign sa_final_sum_in = ctrl_enable_final_add ? (ctrl_partial_sum_to_sa + ctrl_c_data_to_sa) : 0;
    
    //======================================================================
    //== Test Sequence (Unchanged)
    //======================================================================
    integer i, t;

    initial begin clk = 0; forever #(CLK_PERIOD/2) clk = ~clk; end

    initial begin
        rst_n = 1'b0;
        compute_req = 1'b0;
        formatter_valid_out_to_sa = 1'b0;
        skewed_a_to_sa = 0;
        skewed_b_to_sa = 0;
        $display("[%0t] [TB] Testbench Initialized.", $time);
        #(CLK_PERIOD * 5);
        rst_n = 1'b1;
        $display("[%0t] [TB] Reset Released.", $time);
        
        @(posedge clk);
        compute_req = 1'b1;
        @(posedge clk);
        compute_req = 1'b0;
        
        $display("[%0t] [TB] Waiting for start_pass from compute_controller...", $time);
        wait (ctrl_start_new_systolic_pass == 1'b1);
        $display("[%0t] [TB] start_pass detected! Simulating data formatter...", $time);

        for (t = 0; t < (2*TILE_SIZE - 1); t = t + 1) begin
            formatter_valid_out_to_sa <= 1'b1;
            for (i = 0; i < TILE_SIZE; i = i + 1) begin
                skewed_a_to_sa[i*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] <= 1;
                skewed_b_to_sa[i*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] <= 1;
            end
            @(posedge clk);
        end
        formatter_valid_out_to_sa <= 1'b0;
        
        $display("[%0t] [TB] Data feeding finished. Waiting for compute_done...", $time);
        
        fork
            begin
                wait (compute_done == 1'b1);
                $display("----------------------------------------------------------");
                $display("[%0t] [TB] SUCCESS: compute_done was asserted!", $time);
                $display("           The handshake between SA and Controller works.");
                $display("----------------------------------------------------------");
                $finish;
            end
            begin
                #(CLK_PERIOD * 1000); // Timeout of 1000 cycles
                $display("----------------------------------------------------------");
                $error("[%0t] [TB] FAILURE: Test timed out. compute_done was NOT asserted.", $time);
                $display("           Deadlock likely in SA <-> Controller handshake.");
                $display("----------------------------------------------------------");
                $finish;
            end
        join
    end
    
    always @(posedge clk) begin
        if (sa_partial_sum_valid) begin
            $display("[%0t] [TB] Handshake: SA produced valid output for row %d", $time, sa_partial_sum_row_idx);
        end
    end

endmodule