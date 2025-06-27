// tb_top_data_pipeline.v
`timescale 1ns / 1ps

module tb_top_data_pipeline;

    // A function to calculate ceiling log base 2
    function integer clog2;
        input integer value;
        begin
            if (value <= 0) clog2 = 0; // Or handle error
            else begin
                value = value - 1;
                for (clog2 = 0; value > 0; clog2 = clog2 + 1)
                    value = value >> 1;
            end
        end
    endfunction

    // Parameters from DUTs - ensure they match
    parameter MATRIX_SIZE_TB            = 48;
    parameter TILE_SIZE_TB              = 16;
    
    parameter MAIN_MEM_ADDR_WIDTH_TB    = 32;
    parameter MAIN_MEM_DATA_WIDTH_BITS_TB = 64; // Loader bus width

    parameter BASE_ADDR_A_TB            = 32'h10000000;
    parameter BASE_ADDR_B_TB            = 32'h20000000;

    parameter INPUT_DATA_WIDTH_TB       = 8;  // For data_formatter, SRAM element width

    // Testbench specific parameters
    localparam NUM_TILES_PER_DIM_TB = MATRIX_SIZE_TB / TILE_SIZE_TB;
    localparam A_B_TILE_BYTES_TB    = TILE_SIZE_TB * TILE_SIZE_TB * (INPUT_DATA_WIDTH_TB/8);
    localparam WORDS_PER_TILE_TB    = A_B_TILE_BYTES_TB / (MAIN_MEM_DATA_WIDTH_BITS_TB / 8);

    localparam MAIN_MEM_SIZE_WORDS_TB  = WORDS_PER_TILE_TB * 2 ; // For one A tile and one B tile for now

    localparam LOADER_SRAM_ADDR_WIDTH = clog2(WORDS_PER_TILE_TB); // e.g., clog2(16*16 / (64/8)) = clog2(32) = 5
    localparam DF_SRAM_ADDR_WIDTH   = TILE_SIZE_TB * clog2(TILE_SIZE_TB); // e.g., 16*clog2(16) = 16*4 = 64
    localparam DF_SRAM_DATA_WIDTH   = TILE_SIZE_TB * INPUT_DATA_WIDTH_TB; // e.g., 16*8 = 128
    
    // NEW LOCALPARAMS FOR CLOG2 WIDTHS
    localparam TILE_IDX_WIDTH_TB = clog2(NUM_TILES_PER_DIM_TB);

    // Clock and Reset
    reg clk;
    reg rst_n;

    // --- Loader Interface Signals ---
    reg                                          load_req_tb;
    reg [TILE_IDX_WIDTH_TB-1:0]                i_tile_idx_tb; // 使用 localparam 定义的宽度
    reg [TILE_IDX_WIDTH_TB-1:0]                j_tile_idx_tb; // 使用 localparam 定义的宽度
    reg [TILE_IDX_WIDTH_TB-1:0]                k_tile_idx_tb; // 使用 localparam 定义的宽度
    reg                                          load_to_ping_tb; // Controls loader's target SRAM set
    wire                                         load_busy_tb;
    wire                                         load_done_tb;

    // --- Main Memory Interface (Loader <-> TB Memory Model) ---
    wire                                         mem_req_valid_ld;
    reg                                          mem_req_ready_ld;
    reg                                          mem_resp_valid_ld;
    reg  [MAIN_MEM_DATA_WIDTH_BITS_TB-1:0]       mem_resp_rdata_ld;
    wire [MAIN_MEM_ADDR_WIDTH_TB-1:0]            mem_req_addr_ld;

    // --- Loader SRAM Write Outputs (to be demuxed) ---
    wire [LOADER_SRAM_ADDR_WIDTH-1:0]            sram_a_waddr_from_loader;
    wire [MAIN_MEM_DATA_WIDTH_BITS_TB-1:0]       sram_a_wdata_from_loader;
    wire                                         sram_a_we_from_loader;
    wire [LOADER_SRAM_ADDR_WIDTH-1:0]            sram_b_waddr_from_loader;
    wire [MAIN_MEM_DATA_WIDTH_BITS_TB-1:0]       sram_b_wdata_from_loader;
    wire                                         sram_b_we_from_loader;

    // --- SRAM A Ping-Pong Instances ---
    reg  sram_a_ping_we_tb, sram_a_pong_we_tb;
    reg  [LOADER_SRAM_ADDR_WIDTH-1:0] sram_a_ping_waddr_tb, sram_a_pong_waddr_tb;
    reg  [MAIN_MEM_DATA_WIDTH_BITS_TB-1:0] sram_a_ping_wdata_tb, sram_a_pong_wdata_tb;
    wire [DF_SRAM_ADDR_WIDTH-1:0]     sram_a_ping_raddr_tb, sram_a_pong_raddr_tb; // From DF
    wire [DF_SRAM_DATA_WIDTH-1:0]     sram_a_ping_rdata_tb, sram_a_pong_rdata_tb; // To DF

    // --- SRAM B Ping-Pong Instances ---
    reg  sram_b_ping_we_tb, sram_b_pong_we_tb;
    reg  [LOADER_SRAM_ADDR_WIDTH-1:0] sram_b_ping_waddr_tb, sram_b_pong_waddr_tb;
    reg  [MAIN_MEM_DATA_WIDTH_BITS_TB-1:0] sram_b_ping_wdata_tb, sram_b_pong_wdata_tb;
    wire [DF_SRAM_ADDR_WIDTH-1:0]     sram_b_ping_raddr_tb, sram_b_pong_raddr_tb; // From DF
    wire [DF_SRAM_DATA_WIDTH-1:0]     sram_b_ping_rdata_tb, sram_b_pong_rdata_tb; // To DF

    // --- Data Formatter Interface Signals ---
    reg                                   start_pass_df_tb;
    reg                                   process_from_ping_tb; // Controls DF's source SRAM set
    wire                                  pass_done_df;
    wire [DF_SRAM_ADDR_WIDTH-1:0]         sram_a_addr_to_srams; // DF output to be muxed
    wire [DF_SRAM_ADDR_WIDTH-1:0]         sram_b_addr_to_srams; // DF output to be muxed
    reg  [DF_SRAM_DATA_WIDTH-1:0]         sram_a_rdata_to_df;   // Muxed input to DF
    reg  [DF_SRAM_DATA_WIDTH-1:0]         sram_b_rdata_to_df;   // Muxed input to DF

    wire [TILE_SIZE_TB*INPUT_DATA_WIDTH_TB-1:0] skewed_a_out_df;
    wire [TILE_SIZE_TB*INPUT_DATA_WIDTH_TB-1:0] skewed_b_out_df;
    wire                                  data_valid_out_df;      // Overall valid from DF
    wire [TILE_SIZE_TB-1:0]               skewed_a_valid_out_df;  // Individual valid from DF
    wire [TILE_SIZE_TB-1:0]               skewed_b_valid_out_df;  // Individual valid from DF

    // Internal TB signals and storage
    reg [MAIN_MEM_DATA_WIDTH_BITS_TB-1:0] main_memory_storage [0:MAIN_MEM_SIZE_WORDS_TB-1];
    reg signed [INPUT_DATA_WIDTH_TB-1:0] A_tile_golden [0:TILE_SIZE_TB-1][0:TILE_SIZE_TB-1];
    reg signed [INPUT_DATA_WIDTH_TB-1:0] B_tile_golden [0:TILE_SIZE_TB-1][0:TILE_SIZE_TB-1];

    // Main Memory Model delayed signals
    reg [MAIN_MEM_ADDR_WIDTH_TB-1:0] mem_req_addr_ld_dly;
    reg                              mem_req_accepted_dly;
    reg [MAIN_MEM_ADDR_WIDTH_TB-1:0] effective_addr_reg;

    // Verification Logic signals
    integer errors_count;
    integer cycle_count;
    integer current_time_cnt_for_df_check;
    reg expected_a_should_be_valid; 
    reg expected_b_should_be_valid; 


    //==================================================================
    // DUT Instantiations
    //==================================================================

    loader #(
        .MATRIX_SIZE(MATRIX_SIZE_TB),
        .TILE_SIZE(TILE_SIZE_TB),
        .MAIN_MEM_ADDR_WIDTH(MAIN_MEM_ADDR_WIDTH_TB),
        .MAIN_MEM_DATA_WIDTH_BITS(MAIN_MEM_DATA_WIDTH_BITS_TB),
        .BASE_ADDR_A(BASE_ADDR_A_TB),
        .BASE_ADDR_B(BASE_ADDR_B_TB)
    ) u_loader (
        .clk(clk),
        .rst_n(rst_n),
        .load_req(load_req_tb),
        .i_tile_idx(i_tile_idx_tb),
        .j_tile_idx(j_tile_idx_tb),
        .k_tile_idx(k_tile_idx_tb),
        .load_to_ping(load_to_ping_tb), // Input to loader
        .load_busy(load_busy_tb),
        .load_done(load_done_tb),
        .mem_req_valid(mem_req_valid_ld),
        .mem_req_ready(mem_req_ready_ld),
        .mem_resp_valid(mem_resp_valid_ld),
        .mem_resp_rdata(mem_resp_rdata_ld),
        .mem_req_addr(mem_req_addr_ld),
        .sram_a_addr(sram_a_waddr_from_loader),
        .sram_a_wdata(sram_a_wdata_from_loader),
        .sram_a_we(sram_a_we_from_loader),
        .sram_b_addr(sram_b_waddr_from_loader),
        .sram_b_wdata(sram_b_wdata_from_loader),
        .sram_b_we(sram_b_we_from_loader)
    );

    // --- SRAM A Ping ---
    sram_banked #(
        .IS_SRAM_A(1'b1),
        .NUM_BANKS(TILE_SIZE_TB),
        .BANK_DEPTH(TILE_SIZE_TB),
        .BANK_DATA_WIDTH(INPUT_DATA_WIDTH_TB),
        .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS_TB)
    ) u_sram_a_ping (
        .clk(clk),
        .we(sram_a_ping_we_tb),
        .waddr(sram_a_ping_waddr_tb),
        .wdata(sram_a_ping_wdata_tb),
        .raddr(sram_a_ping_raddr_tb), // From DF Mux
        .rdata(sram_a_ping_rdata_tb)  // To DF Mux
    );

    // --- SRAM A Pong ---
    sram_banked #(
        .IS_SRAM_A(1'b1),
        .NUM_BANKS(TILE_SIZE_TB),
        .BANK_DEPTH(TILE_SIZE_TB),
        .BANK_DATA_WIDTH(INPUT_DATA_WIDTH_TB),
        .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS_TB)
    ) u_sram_a_pong (
        .clk(clk),
        .we(sram_a_pong_we_tb),
        .waddr(sram_a_pong_waddr_tb),
        .wdata(sram_a_pong_wdata_tb),
        .raddr(sram_a_pong_raddr_tb), // From DF Mux
        .rdata(sram_a_pong_rdata_tb)  // To DF Mux
    );

    // --- SRAM B Ping ---
    sram_banked #(
        .IS_SRAM_A(1'b0), // This is SRAM B
        .NUM_BANKS(TILE_SIZE_TB),
        .BANK_DEPTH(TILE_SIZE_TB),
        .BANK_DATA_WIDTH(INPUT_DATA_WIDTH_TB),
        .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS_TB)
    ) u_sram_b_ping (
        .clk(clk),
        .we(sram_b_ping_we_tb),
        .waddr(sram_b_ping_waddr_tb),
        .wdata(sram_b_ping_wdata_tb),
        .raddr(sram_b_ping_raddr_tb), // From DF Mux
        .rdata(sram_b_ping_rdata_tb)  // To DF Mux
    );

    // --- SRAM B Pong ---
    sram_banked #(
        .IS_SRAM_A(1'b0), // This is SRAM B
        .NUM_BANKS(TILE_SIZE_TB),
        .BANK_DEPTH(TILE_SIZE_TB),
        .BANK_DATA_WIDTH(INPUT_DATA_WIDTH_TB),
        .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS_TB)
    ) u_sram_b_pong (
        .clk(clk),
        .we(sram_b_pong_we_tb),
        .waddr(sram_b_pong_waddr_tb),
        .wdata(sram_b_pong_wdata_tb),
        .raddr(sram_b_pong_raddr_tb), // From DF Mux
        .rdata(sram_b_pong_rdata_tb)  // To DF Mux
    );

    data_formatter #(
        .TILE_SIZE(TILE_SIZE_TB),
        .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH_TB)
    ) u_data_formatter (
        .clk(clk),
        .rst_n(rst_n),
        .start_pass(start_pass_df_tb),
        .pass_done(pass_done_df),
        .sram_a_addr(sram_a_addr_to_srams), // To Mux
        .sram_a_rdata(sram_a_rdata_to_df),  // From Mux
        .sram_b_addr(sram_b_addr_to_srams), // To Mux
        .sram_b_rdata(sram_b_rdata_to_df),  // From Mux
        .skewed_a_out(skewed_a_out_df),
        .skewed_b_out(skewed_b_out_df),
        .data_valid_out(data_valid_out_df),
        .skewed_a_valid_out(skewed_a_valid_out_df),
        .skewed_b_valid_out(skewed_b_valid_out_df)
    );

    //==================================================================
    // Ping-Pong Muxing Logic
    //==================================================================

    // Demux Loader SRAM writes based on load_to_ping_tb
    always @(*) begin
        if (load_to_ping_tb) begin // Loader writes to PING buffers
            sram_a_ping_we_tb    = sram_a_we_from_loader;
            sram_a_ping_waddr_tb = sram_a_waddr_from_loader;
            sram_a_ping_wdata_tb = sram_a_wdata_from_loader;
            sram_a_pong_we_tb    = 1'b0;
            sram_a_pong_waddr_tb = {LOADER_SRAM_ADDR_WIDTH{1'bz}};
            sram_a_pong_wdata_tb = {MAIN_MEM_DATA_WIDTH_BITS_TB{1'bz}};

            sram_b_ping_we_tb    = sram_b_we_from_loader;
            sram_b_ping_waddr_tb = sram_b_waddr_from_loader;
            sram_b_ping_wdata_tb = sram_b_wdata_from_loader;
            sram_b_pong_we_tb    = 1'b0;
            sram_b_pong_waddr_tb = {LOADER_SRAM_ADDR_WIDTH{1'bz}};
            sram_b_pong_wdata_tb = {MAIN_MEM_DATA_WIDTH_BITS_TB{1'bz}};
        end else begin // Loader writes to PONG buffers
            sram_a_pong_we_tb    = sram_a_we_from_loader;
            sram_a_pong_waddr_tb = sram_a_waddr_from_loader;
            sram_a_pong_wdata_tb = sram_a_wdata_from_loader;
            sram_a_ping_we_tb    = 1'b0;
            sram_a_ping_waddr_tb = {LOADER_SRAM_ADDR_WIDTH{1'bz}};
            sram_a_ping_wdata_tb = {MAIN_MEM_DATA_WIDTH_BITS_TB{1'bz}};

            sram_b_pong_we_tb    = sram_b_we_from_loader;
            sram_b_pong_waddr_tb = sram_b_waddr_from_loader;
            sram_b_pong_wdata_tb = sram_b_wdata_from_loader;
            sram_b_ping_we_tb    = 1'b0;
            sram_b_ping_waddr_tb = {LOADER_SRAM_ADDR_WIDTH{1'bz}};
            sram_b_ping_wdata_tb = {MAIN_MEM_DATA_WIDTH_BITS_TB{1'bz}};
        end
    end

    // Mux Data Formatter SRAM accesses based on process_from_ping_tb
    assign sram_a_ping_raddr_tb = process_from_ping_tb ? sram_a_addr_to_srams : {DF_SRAM_ADDR_WIDTH{1'bz}};
    assign sram_a_pong_raddr_tb = !process_from_ping_tb ? sram_a_addr_to_srams : {DF_SRAM_ADDR_WIDTH{1'bz}};
    assign sram_b_ping_raddr_tb = process_from_ping_tb ? sram_b_addr_to_srams : {DF_SRAM_ADDR_WIDTH{1'bz}};
    assign sram_b_pong_raddr_tb = !process_from_ping_tb ? sram_b_addr_to_srams : {DF_SRAM_ADDR_WIDTH{1'bz}};

    always @(*) begin
        if (process_from_ping_tb) begin // DF reads from PING buffers
            sram_a_rdata_to_df = sram_a_ping_rdata_tb;
            sram_b_rdata_to_df = sram_b_ping_rdata_tb;
        end else begin // DF reads from PONG buffers
            sram_a_rdata_to_df = sram_a_pong_rdata_tb;
            sram_b_rdata_to_df = sram_b_pong_rdata_tb;
        end
    end

    //==================================================================
    // Clock and Reset Generation
    //==================================================================
    initial begin
        clk = 1'b0;
        forever #5 clk = ~clk; // 10ns period, 100MHz
    end

    initial begin
        rst_n = 1'b0;
        #20; // Hold reset for 2 cycles
        rst_n = 1'b1;
    end

    //==================================================================
    // Main Memory Model (1-cycle read latency)
    //==================================================================
    integer mem_idx_tb;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            mem_resp_valid_ld <= 1'b0;
            mem_resp_rdata_ld <= {MAIN_MEM_DATA_WIDTH_BITS_TB{1'b0}};
            mem_req_accepted_dly <= 1'b0;
        end else begin
            if (mem_req_valid_ld && mem_req_ready_ld) begin
                mem_req_addr_ld_dly  <= mem_req_addr_ld;
                mem_req_accepted_dly <= 1'b1;
            end else begin
                mem_req_accepted_dly <= 1'b0;
            end

            if (mem_req_accepted_dly) begin
                effective_addr_reg = mem_req_addr_ld_dly;
                mem_resp_valid_ld <= 1'b1;
                if (effective_addr_reg >= BASE_ADDR_A_TB && effective_addr_reg < (BASE_ADDR_A_TB + A_B_TILE_BYTES_TB)) begin
                    mem_idx_tb = (effective_addr_reg - BASE_ADDR_A_TB) / (MAIN_MEM_DATA_WIDTH_BITS_TB / 8);
                    if (mem_idx_tb >= 0 && mem_idx_tb < WORDS_PER_TILE_TB) begin
                         mem_resp_rdata_ld <= main_memory_storage[mem_idx_tb];
                    end else begin
                         mem_resp_rdata_ld <= {MAIN_MEM_DATA_WIDTH_BITS_TB{1'bx}};
                         $display("%0t [TB-MEM] ERROR: Index %0d out of bounds for A-tile memory storage.", $time, mem_idx_tb);
                    end
                end else if (effective_addr_reg >= BASE_ADDR_B_TB && effective_addr_reg < (BASE_ADDR_B_TB + A_B_TILE_BYTES_TB)) begin
                    mem_idx_tb = (effective_addr_reg - BASE_ADDR_B_TB) / (MAIN_MEM_DATA_WIDTH_BITS_TB / 8) + WORDS_PER_TILE_TB;
                     if (mem_idx_tb >= WORDS_PER_TILE_TB && mem_idx_tb < MAIN_MEM_SIZE_WORDS_TB) begin
                        mem_resp_rdata_ld <= main_memory_storage[mem_idx_tb];
                    end else begin
                         mem_resp_rdata_ld <= {MAIN_MEM_DATA_WIDTH_BITS_TB{1'bx}};
                         $display("%0t [TB-MEM] ERROR: Index %0d out of bounds for B-tile memory storage.", $time, mem_idx_tb);
                    end
                end else begin
                    mem_resp_rdata_ld <= {MAIN_MEM_DATA_WIDTH_BITS_TB{1'bx}};
                    $display("%0t [TB-MEM] WARNING: Read from unmapped address 0x%h", $time, effective_addr_reg);
                end
            end else begin
                mem_resp_valid_ld <= 1'b0;
            end
        end
    end

    //==================================================================
    // Test Sequence
    //==================================================================
    integer word_idx_init, byte_offset_init, row_calc_init, col_calc_init;
    reg [MAIN_MEM_DATA_WIDTH_BITS_TB-1:0] current_data_word_init;

    initial begin
        errors_count = 0;
        cycle_count = 0;
        process_from_ping_tb = 1'b0;

        $readmemh("input_mem.csv", main_memory_storage);
        $display("[%0t] [TB] INFO: Memory content loaded from input_mem.csv", $time);

        // Populate A_tile_golden
        for (row_calc_init = 0; row_calc_init < TILE_SIZE_TB; row_calc_init = row_calc_init + 1) begin
            for (col_calc_init = 0; col_calc_init < TILE_SIZE_TB; col_calc_init = col_calc_init + 1) begin
                word_idx_init = (row_calc_init * TILE_SIZE_TB + col_calc_init) / (MAIN_MEM_DATA_WIDTH_BITS_TB/8);
                byte_offset_init = (row_calc_init * TILE_SIZE_TB + col_calc_init) % (MAIN_MEM_DATA_WIDTH_BITS_TB/8);
                current_data_word_init = main_memory_storage[word_idx_init];
                A_tile_golden[row_calc_init][col_calc_init] = (current_data_word_init >> (byte_offset_init * INPUT_DATA_WIDTH_TB)) & ((1 << INPUT_DATA_WIDTH_TB) - 1);
            end
        end
        $display("[%0t] [TB] INFO: A_tile_golden populated.", $time);

        // Populate B_tile_golden
        for (row_calc_init = 0; row_calc_init < TILE_SIZE_TB; row_calc_init = row_calc_init + 1) begin
            for (col_calc_init = 0; col_calc_init < TILE_SIZE_TB; col_calc_init = col_calc_init + 1) begin
                word_idx_init = (row_calc_init * TILE_SIZE_TB + col_calc_init) / (MAIN_MEM_DATA_WIDTH_BITS_TB/8);
                byte_offset_init = (row_calc_init * TILE_SIZE_TB + col_calc_init) % (MAIN_MEM_DATA_WIDTH_BITS_TB/8);
                current_data_word_init = main_memory_storage[WORDS_PER_TILE_TB + word_idx_init];
                B_tile_golden[row_calc_init][col_calc_init] = (current_data_word_init >> (byte_offset_init * INPUT_DATA_WIDTH_TB)) & ((1 << INPUT_DATA_WIDTH_TB) - 1);
            end
        end
        $display("[%0t] [TB] INFO: B_tile_golden populated.", $time);

        wait (rst_n === 1'b1);
        #10;

        // --- Phase 1: Load to PING buffers ---
        $display("[%0t] [TB] INFO: Starting loader operation to PING buffers.", $time);
        load_req_tb     = 1'b1;
        i_tile_idx_tb   = 0;
        j_tile_idx_tb   = 0;
        k_tile_idx_tb   = 0;
        load_to_ping_tb = 1'b1; // Load to PING
        mem_req_ready_ld= 1'b1;

        wait (load_done_tb === 1'b1);
        $display("[%0t] [TB] INFO: Loader (to PING) finished.", $time);
        load_req_tb = 1'b0;
        @(posedge clk);

        // --- Phase 2: Process from PING buffers ---
        $display("[%0t] [TB] INFO: Starting data formatter operation from PING buffers.", $time);
        process_from_ping_tb = 1'b1; // DF and SA use PING
        start_pass_df_tb = 1'b1;
        @(posedge clk);
        start_pass_df_tb = 1'b0;

        wait (pass_done_df === 1'b1);
        $display("[%0t] [TB] INFO: Data formatter operation finished.", $time);
        
        #100; // Allow some time for final signals to settle or for observation

        if (errors_count == 0) begin
            $display("*******************************************");
            $display("*** TEST PASSED!               ***");
            $display("*******************************************");
        end else begin
            $display("*******************************************");
            $display("*** TEST FAILED!               ***");
            $display("*** Errors: %0d                         ***", errors_count);
            $display("*******************************************");
        end
        $finish;
    end

    //==================================================================
    // Verification Logic (Checks Data Formatter Output)
    //==================================================================
    integer check_idx_verify, k_val_a_verify, k_val_b_verify, effective_time_cnt_for_output;
    reg signed [INPUT_DATA_WIDTH_TB-1:0] expected_val_a_verify, actual_val_a_verify;
    reg signed [INPUT_DATA_WIDTH_TB-1:0] expected_val_b_verify, actual_val_b_verify;
    
    always @(posedge clk) begin
        if (!rst_n) begin
            cycle_count <= 0;
        end else begin
            cycle_count <= cycle_count + 1;
    
            // Check only when data_formatter's FSM is in the streaming state
            if (u_data_formatter.current_state_q == u_data_formatter.S_STREAMING) begin
                current_time_cnt_for_df_check = u_data_formatter.time_cnt_q; // 这是DF time_cnt_q寄存器的当前值

                // 计算DF输出逻辑实际使用的time_cnt值
                // 当DF的time_cnt_q寄存器当前值为T，其输出是基于上一个周期的time_cnt_q (T-1)计算的
                effective_time_cnt_for_output = current_time_cnt_for_df_check - 1;
    
                // 只有当 effective_time_cnt_for_output >= 0 时，才进行有意义的检查
                if (effective_time_cnt_for_output >= 0) begin
                    for (check_idx_verify = 0; check_idx_verify < TILE_SIZE_TB; check_idx_verify = check_idx_verify + 1) begin
                        // --- 修正 k_val_a_verify 和 k_val_b_verify 的计算 ---
                        k_val_a_verify = effective_time_cnt_for_output - check_idx_verify;
                        k_val_b_verify = effective_time_cnt_for_output - check_idx_verify;

                        // --- 修正 expected_x_should_be_valid 的判断 ---
                        expected_a_should_be_valid = (k_val_a_verify >= 0 && k_val_a_verify < TILE_SIZE_TB &&
                                                      effective_time_cnt_for_output >= u_data_formatter.PIPELINE_COMPENSATION);
                        expected_b_should_be_valid = (k_val_b_verify >= 0 && k_val_b_verify < TILE_SIZE_TB &&
                                                      effective_time_cnt_for_output >= u_data_formatter.PIPELINE_COMPENSATION);

                        // VALID_MISMATCH 检查 (使用修正后的 expected_a_should_be_valid)
                        if (skewed_a_valid_out_df[check_idx_verify] != expected_a_should_be_valid) begin
                            $display("[%0t][Cycle %3d][DF_VALID] ERROR A_VALID_MISMATCH: df_reg_tc=%d, eff_tc=%d, ch/row=%d. Exp valid: %b, Got valid: %b (k_calc_tb=%d)",
                                     $time, cycle_count, current_time_cnt_for_df_check, effective_time_cnt_for_output, check_idx_verify,
                                     expected_a_should_be_valid, skewed_a_valid_out_df[check_idx_verify], k_val_a_verify);
                            errors_count = errors_count + 1;
                        end
                        if (skewed_b_valid_out_df[check_idx_verify] != expected_b_should_be_valid) begin
                            $display("[%0t][Cycle %3d][DF_VALID] ERROR B_VALID_MISMATCH: df_reg_tc=%d, eff_tc=%d, ch/col=%d. Exp valid: %b, Got valid: %b (k_calc_tb=%d)",
                                     $time, cycle_count, current_time_cnt_for_df_check, effective_time_cnt_for_output, check_idx_verify,
                                     expected_b_should_be_valid, skewed_b_valid_out_df[check_idx_verify], k_val_b_verify);
                            errors_count = errors_count + 1;
                        end

                        // DATA_MISMATCH 检查 (仅在TB和DUT都认为有效时，并使用修正后的 k_val_a_verify)
                        if (skewed_a_valid_out_df[check_idx_verify] && expected_a_should_be_valid) begin
                            expected_val_a_verify = A_tile_golden[check_idx_verify][k_val_a_verify]; // 使用修正后的 k_val_a_verify
                            actual_val_a_verify   = skewed_a_out_df[check_idx_verify*INPUT_DATA_WIDTH_TB +: INPUT_DATA_WIDTH_TB];
                            if (actual_val_a_verify !== expected_val_a_verify) begin
                                $display("[%0t][Cycle %3d][DF_VALID] ERROR A_DATA: df_reg_tc=%d, eff_tc=%d, ch/row=%d. Exp: A[%d][%d]=%d(0x%x), Got: %d(0x%x)",
                                         $time, cycle_count, current_time_cnt_for_df_check, effective_time_cnt_for_output, check_idx_verify,
                                         check_idx_verify, k_val_a_verify, expected_val_a_verify, expected_val_a_verify, actual_val_a_verify, actual_val_a_verify);
                                errors_count = errors_count + 1;
                            end
                        end
                        if (skewed_b_valid_out_df[check_idx_verify] && expected_b_should_be_valid) begin
                            expected_val_b_verify = B_tile_golden[k_val_b_verify][check_idx_verify]; // 使用修正后的 k_val_b_verify
                            actual_val_b_verify   = skewed_b_out_df[check_idx_verify*INPUT_DATA_WIDTH_TB +: INPUT_DATA_WIDTH_TB];
                            if (actual_val_b_verify !== expected_val_b_verify) begin
                                $display("[%0t][Cycle %3d][DF_VALID] ERROR B_DATA: df_reg_tc=%d, eff_tc=%d, ch/col=%d. Exp: B[%d][%d]=%d(0x%x), Got: %d(0x%x)",
                                         $time, cycle_count, current_time_cnt_for_df_check, effective_time_cnt_for_output, check_idx_verify,
                                         k_val_b_verify, check_idx_verify, expected_val_b_verify, expected_val_b_verify, actual_val_b_verify, actual_val_b_verify);
                                errors_count = errors_count + 1;
                            end
                        end
                    end
                end else begin // effective_time_cnt_for_output < 0, 意味着 DF 的输出逻辑还没有基于一个稳定的 time_cnt >= 0 开始工作
                    // 在这种情况下，所有输出都应该是无效的
                    for (check_idx_verify = 0; check_idx_verify < TILE_SIZE_TB; check_idx_verify = check_idx_verify + 1) begin
                        if (skewed_a_valid_out_df[check_idx_verify] != 1'b0) begin
                             $display("[%0t][Cycle %3d][DF_VALID] ERROR A_VALID_MISMATCH (early): df_reg_tc=%d, eff_tc=%d, ch/row=%d. Exp valid: 0, Got valid: %b",
                                      $time, cycle_count, current_time_cnt_for_df_check, effective_time_cnt_for_output, check_idx_verify, skewed_a_valid_out_df[check_idx_verify]);
                            errors_count = errors_count + 1;
                        end
                        if (skewed_b_valid_out_df[check_idx_verify] != 1'b0) begin
                             $display("[%0t][Cycle %3d][DF_VALID] ERROR B_VALID_MISMATCH (early): df_reg_tc=%d, eff_tc=%d, ch/col=%d. Exp valid: 0, Got valid: %b",
                                      $time, cycle_count, current_time_cnt_for_df_check, effective_time_cnt_for_output, check_idx_verify, skewed_b_valid_out_df[check_idx_verify]);
                            errors_count = errors_count + 1;
                        end
                    end
                end
            end
        end
    end

endmodule