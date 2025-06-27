//
// Filename: accelerator.v
// Description: A fully integrated matrix multiplication accelerator.
//              (SERIAL WRITER VERSION) This version uses a single SRAM_C buffer
//              and performs computation and write-back sequentially.
//              It retains the ping-pong buffers for input SRAMs A and B.
//
`timescale 1ns / 1ps

module accelerator #(
    // Architectural Parameters
    parameter MATRIX_SIZE               = 16, // --- MODIFIED ---: Set to 16 for this case
    parameter TILE_SIZE                 = 16,

    // Data Type Parameters
    parameter INPUT_DATA_WIDTH          = 8,
    parameter ACCUM_DATA_WIDTH          = 32,

    // External Memory Interface Parameters
    parameter MAIN_MEM_ADDR_WIDTH       = 32,
    parameter MAIN_MEM_DATA_WIDTH_BITS  = 64,

    // Base Addresses in Main Memory
    parameter BASE_ADDR_A               = 32'h10000000,
    parameter BASE_ADDR_B               = 32'h20000000,
    parameter BASE_ADDR_C               = 32'h30000000
) (
    // --- Top Controller Interface ---
    input  wire                                 clk,
    input  wire                                 rst_n,
    input  wire                                 comp_enb,
    output logic                                busyb,
    output logic                                done,

    // --- Input Memory Interface (Read-only) ---
    output logic [MAIN_MEM_ADDR_WIDTH-1:0]      imem_addr,
    output logic                                imem_read_enb,
    input  wire [MAIN_MEM_DATA_WIDTH_BITS-1:0]  imem_data_in,
    input  wire                                 imem_req_ready,
    input  wire                                 imem_resp_valid,

    // --- Result Memory Interface (Write-only) ---
    output logic [MAIN_MEM_ADDR_WIDTH-1:0]      omem_addr,
    output logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] omem_wdata,
    output logic                                omem_write_enb,
    input  wire                                 omem_req_ready
);

    //--------------------------------------------------------------------------
    // Local Parameters & Derived Values
    //--------------------------------------------------------------------------
    localparam NUM_TILES_PER_DIM = MATRIX_SIZE / TILE_SIZE; // Will be 1
    localparam K_ITER_MAX        = NUM_TILES_PER_DIM;       // Will be 1
    localparam J_ITER_MAX        = NUM_TILES_PER_DIM;       // Will be 1
    localparam I_ITER_MAX        = NUM_TILES_PER_DIM;       // Will be 1

    localparam LOADER_SRAM_ADDR_WIDTH   = $clog2(TILE_SIZE * TILE_SIZE * INPUT_DATA_WIDTH / MAIN_MEM_DATA_WIDTH_BITS);
    localparam DF_SRAM_ADDR_WIDTH       = TILE_SIZE * $clog2(TILE_SIZE);
    localparam DF_SRAM_DATA_WIDTH       = TILE_SIZE * INPUT_DATA_WIDTH;
    localparam SA_SRAM_C_ROW_WIDTH      = TILE_SIZE * ACCUM_DATA_WIDTH;
    localparam WRITER_SRAM_C_ADDR_WIDTH = $clog2(TILE_SIZE * TILE_SIZE * ACCUM_DATA_WIDTH / MAIN_MEM_DATA_WIDTH_BITS);

    //--------------------------------------------------------------------------
    // FSM State Definitions
    //--------------------------------------------------------------------------
    typedef enum logic [3:0] {
        S_IDLE,
        S_INIT_GEMM,
        S_LOAD_FIRST,
        S_WAIT_LOAD_FIRST,
        S_START_DF,
        S_PIPE_DELAY,
        S_START_SA,
        S_WAIT_SA_AND_LOAD,
        S_WRITE_TILE,
        S_WAIT_WRITE_DONE,
        S_FINISH
    } accel_fsm_state_t;
    accel_fsm_state_t current_state_q, next_state_d;

    //--------------------------------------------------------------------------
    // Internal Signals and Registers
    //--------------------------------------------------------------------------
    logic [$clog2(I_ITER_MAX)-1:0] i_tile_idx_q, i_tile_idx_d;
    logic [$clog2(J_ITER_MAX)-1:0] j_tile_idx_q, j_tile_idx_d;
    logic [$clog2(K_ITER_MAX)-1:0] k_tile_idx_q, k_tile_idx_d;
    
    logic [$clog2(K_ITER_MAX)-1:0] k_tile_idx_for_load;

    logic load_ab_select_q,  load_ab_select_d;
    logic compute_ab_select_q, compute_ab_select_d;
    // --- DELETED ---: Signals for SRAM_C ping-pong selection
    // logic compute_c_select_q,  compute_c_select_d;
    // logic write_c_select_q,    write_c_select_d;

    logic loader_req_pulse;
    logic df_start_pass_pulse;
    logic sa_start_k_iter_pulse;
    logic writer_req_pulse;

    logic sa_activate_pe_level;
    logic k_tile_is_first_for_sa;

    logic loader_done;
    logic sa_k_iter_done;
    logic writer_done;
    
    logic load_done_flag_q,    load_done_flag_d;
    logic compute_done_flag_q, compute_done_flag_d;
    
    reg [1:0] pipe_delay_cnt_q, pipe_delay_cnt_d;

    //--------------------------------------------------------------------------
    // Sub-module Instantiations
    //--------------------------------------------------------------------------
    // --- Loader (Unchanged) ---
    logic [LOADER_SRAM_ADDR_WIDTH-1:0] loader_sram_a_addr, loader_sram_b_addr;
    logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] loader_sram_a_wdata, loader_sram_b_wdata;
    logic loader_sram_a_we, loader_sram_b_we;
    loader #(.MATRIX_SIZE(MATRIX_SIZE), .TILE_SIZE(TILE_SIZE), .MAIN_MEM_ADDR_WIDTH(MAIN_MEM_ADDR_WIDTH), .MAIN_MEM_DATA_WIDTH_BITS(MAIN_MEM_DATA_WIDTH_BITS), .BASE_ADDR_A(BASE_ADDR_A), .BASE_ADDR_B(BASE_ADDR_B))
        u_loader (.clk(clk), .rst_n(rst_n), .load_req(loader_req_pulse), .i_tile_idx(i_tile_idx_q), .j_tile_idx(j_tile_idx_q), .k_tile_idx(k_tile_idx_for_load), .load_to_ping(load_ab_select_q), .load_busy(), .load_done(loader_done), .mem_req_valid(imem_read_enb), .mem_req_ready(imem_req_ready), .mem_resp_valid(imem_resp_valid), .mem_resp_rdata(imem_data_in), .mem_req_addr(imem_addr), .sram_a_addr(loader_sram_a_addr), .sram_a_wdata(loader_sram_a_wdata), .sram_a_we(loader_sram_a_we), .sram_b_addr(loader_sram_b_addr), .sram_b_wdata(loader_sram_b_wdata), .sram_b_we(loader_sram_b_we));
    
    // --- SRAMs A & B (Ping-Pong, Unchanged) ---
    logic sram_a_ping_we, sram_a_pong_we, sram_b_ping_we, sram_b_pong_we;
    logic [LOADER_SRAM_ADDR_WIDTH-1:0] sram_a_ping_waddr, sram_a_pong_waddr, sram_b_ping_waddr, sram_b_pong_waddr;
    logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] sram_a_ping_wdata, sram_a_pong_wdata, sram_b_ping_wdata, sram_b_pong_wdata;
    logic [DF_SRAM_ADDR_WIDTH-1:0] sram_a_ping_raddr, sram_a_pong_raddr, sram_b_ping_raddr, sram_b_pong_raddr;
    logic [DF_SRAM_DATA_WIDTH-1:0] sram_a_ping_rdata, sram_a_pong_rdata, sram_b_ping_rdata, sram_b_pong_rdata;
    sram_banked #(.IS_SRAM_A(1'b1), .NUM_BANKS(TILE_SIZE), .BANK_DEPTH(TILE_SIZE), .BANK_DATA_WIDTH(INPUT_DATA_WIDTH), .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS)) sram_a_ping (.clk(clk), .we(sram_a_ping_we), .waddr(sram_a_ping_waddr), .wdata(sram_a_ping_wdata), .raddr(sram_a_ping_raddr), .rdata(sram_a_ping_rdata));
    sram_banked #(.IS_SRAM_A(1'b1), .NUM_BANKS(TILE_SIZE), .BANK_DEPTH(TILE_SIZE), .BANK_DATA_WIDTH(INPUT_DATA_WIDTH), .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS)) sram_a_pong (.clk(clk), .we(sram_a_pong_we), .waddr(sram_a_pong_waddr), .wdata(sram_a_pong_wdata), .raddr(sram_a_pong_raddr), .rdata(sram_a_pong_rdata));
    sram_banked #(.IS_SRAM_A(1'b0), .NUM_BANKS(TILE_SIZE), .BANK_DEPTH(TILE_SIZE), .BANK_DATA_WIDTH(INPUT_DATA_WIDTH), .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS)) sram_b_ping (.clk(clk), .we(sram_b_ping_we), .waddr(sram_b_ping_waddr), .wdata(sram_b_ping_wdata), .raddr(sram_b_ping_raddr), .rdata(sram_b_ping_rdata));
    sram_banked #(.IS_SRAM_A(1'b0), .NUM_BANKS(TILE_SIZE), .BANK_DEPTH(TILE_SIZE), .BANK_DATA_WIDTH(INPUT_DATA_WIDTH), .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS)) sram_b_pong (.clk(clk), .we(sram_b_pong_we), .waddr(sram_b_pong_waddr), .wdata(sram_b_pong_wdata), .raddr(sram_b_pong_raddr), .rdata(sram_b_pong_rdata));
    
    // --- Data Formatter (Unchanged) ---
    logic [DF_SRAM_ADDR_WIDTH-1:0] df_sram_a_addr, df_sram_b_addr;
    logic [DF_SRAM_DATA_WIDTH-1:0] df_sram_a_rdata, df_sram_b_rdata, df_skewed_a_out, df_skewed_b_out;
    logic [TILE_SIZE-1:0] df_skewed_a_valid_out, df_skewed_b_valid_out;
    data_formatter #(.TILE_SIZE(TILE_SIZE), .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH)) u_data_formatter (.clk(clk), .rst_n(rst_n), .start_pass(df_start_pass_pulse), .pass_done(), .sram_a_addr(df_sram_a_addr), .sram_a_rdata(df_sram_a_rdata), .sram_b_addr(df_sram_b_addr), .sram_b_rdata(df_sram_b_rdata), .skewed_a_out(df_skewed_a_out), .skewed_b_out(df_skewed_b_out), .data_valid_out(), .skewed_a_valid_out(df_skewed_a_valid_out), .skewed_b_valid_out(df_skewed_b_valid_out));
    
    // --- SA (Unchanged) ---
    logic [$clog2(TILE_SIZE)-1:0] sa_sram_c_raddr_A, sa_sram_c_waddr;
    logic signed [SA_SRAM_C_ROW_WIDTH-1:0] sa_sram_c_rdata_A, sa_sram_c_wdata;
    logic sa_sram_c_we;
    sa_enhanced #(.SIZE(TILE_SIZE), .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH), .PE_ACCUM_DATA_WIDTH(ACCUM_DATA_WIDTH)) u_sa_enhanced (.clk(clk), .rst_n(rst_n), .start_new_k_iteration(sa_start_k_iter_pulse), .activate_pe_computation(sa_activate_pe_level), .k_tile_is_first(k_tile_is_first_for_sa), .array_a_in(df_skewed_a_out), .array_b_in(df_skewed_b_out), .array_a_valid_in_indywidual(df_skewed_a_valid_out), .array_b_valid_in_indywidual(df_skewed_b_valid_out), .sa_k_iteration_accum_done(sa_k_iter_done), .sa_busy(), .sram_c_raddr_A_to_sram(sa_sram_c_raddr_A), .sram_c_rdata_A_from_sram(sa_sram_c_rdata_A), .sram_c_waddr_to_sram(sa_sram_c_waddr), .sram_c_wdata_to_sram(sa_sram_c_wdata), .sram_c_we_to_sram(sa_sram_c_we));
    
    // --- SRAM C (--- MODIFIED ---: Single Buffer Only) ---
    logic sram_c_ping_we;
    logic [$clog2(TILE_SIZE)-1:0] sram_c_ping_waddr, sram_c_ping_raddr_A;
    logic [SA_SRAM_C_ROW_WIDTH-1:0] sram_c_ping_wdata, sram_c_ping_rdata_A;
    logic [WRITER_SRAM_C_ADDR_WIDTH-1:0] sram_c_ping_raddr_B;
    logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] sram_c_ping_rdata_B;
    sram_c_accum #(.NUM_ROWS(TILE_SIZE), .ELEM_PER_ROW(TILE_SIZE), .ELEM_WIDTH(ACCUM_DATA_WIDTH), .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS)) 
        sram_c_ping (.clk(clk), .rst_n(rst_n), .we(sram_c_ping_we), .waddr(sram_c_ping_waddr), .wdata(sram_c_ping_wdata), .raddr_A(sram_c_ping_raddr_A), .rdata_A(sram_c_ping_rdata_A), .raddr_B(sram_c_ping_raddr_B), .rdata_B(sram_c_ping_rdata_B));
    
    // --- DELETED ---: sram_c_pong instantiation removed
    // sram_c_accum #(...) sram_c_pong (...);

    // --- Writer (Unchanged) ---
    logic [WRITER_SRAM_C_ADDR_WIDTH-1:0] writer_sram_c_addr;
    logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] writer_sram_c_rdata;
    writer #(.MATRIX_SIZE(MATRIX_SIZE), .TILE_SIZE(TILE_SIZE), .MAIN_MEM_ADDR_WIDTH(MAIN_MEM_ADDR_WIDTH), .MAIN_MEM_DATA_WIDTH_BITS(MAIN_MEM_DATA_WIDTH_BITS), .BASE_ADDR_C(BASE_ADDR_C)) u_writer (.clk(clk), .rst_n(rst_n), .write_req(writer_req_pulse), .i_tile_idx(i_tile_idx_q), .j_tile_idx(j_tile_idx_q), .write_busy(), .write_done(writer_done), .mem_req_valid(omem_write_enb), .mem_req_wdata(omem_wdata), .mem_req_addr(omem_addr), .mem_req_ready(omem_req_ready), .mem_write_done(1'b1), .sram_c_addr(writer_sram_c_addr), .sram_c_rdata(writer_sram_c_rdata));
    
    //--------------------------------------------------------------------------
    // Ping-Pong MUX Logic (--- MODIFIED --- for single SRAM_C)
    //--------------------------------------------------------------------------
    // Input SRAMs A/B logic remains unchanged
    assign sram_a_ping_we = (load_ab_select_q == 0) ? loader_sram_a_we : 1'b0;
    assign sram_a_pong_we = (load_ab_select_q == 1) ? loader_sram_a_we : 1'b0;
    assign sram_a_ping_waddr = loader_sram_a_addr; assign sram_a_ping_wdata = loader_sram_a_wdata;
    assign sram_a_pong_waddr = loader_sram_a_addr; assign sram_a_pong_wdata = loader_sram_a_wdata;
    assign sram_b_ping_we = (load_ab_select_q == 0) ? loader_sram_b_we : 1'b0;
    assign sram_b_pong_we = (load_ab_select_q == 1) ? loader_sram_b_we : 1'b0;
    assign sram_b_ping_waddr = loader_sram_b_addr; assign sram_b_ping_wdata = loader_sram_b_wdata;
    assign sram_b_pong_waddr = loader_sram_b_addr; assign sram_b_pong_wdata = loader_sram_b_wdata;
    assign sram_a_ping_raddr = df_sram_a_addr; assign sram_a_pong_raddr = df_sram_a_addr;
    assign df_sram_a_rdata = (compute_ab_select_q == 0) ? sram_a_ping_rdata : sram_a_pong_rdata;
    assign sram_b_ping_raddr = df_sram_b_addr; assign sram_b_pong_raddr = df_sram_b_addr;
    assign df_sram_b_rdata = (compute_ab_select_q == 0) ? sram_b_ping_rdata : sram_b_pong_rdata;
    
    // SRAM C logic is now direct-mapped, no MUXing needed
    assign sram_c_ping_we = sa_sram_c_we;
    assign sram_c_ping_waddr = sa_sram_c_waddr; 
    assign sram_c_ping_wdata = sa_sram_c_wdata;
    assign sram_c_ping_raddr_A = sa_sram_c_raddr_A;
    assign sa_sram_c_rdata_A = sram_c_ping_rdata_A;
    assign sram_c_ping_raddr_B = writer_sram_c_addr;
    assign writer_sram_c_rdata = sram_c_ping_rdata_B;

    assign k_tile_is_first_for_sa = (k_tile_idx_q == 0);
    assign k_tile_idx_for_load = (current_state_q == S_LOAD_FIRST) ? '0 : k_tile_idx_q + 1;
    
    //--------------------------------------------------------------------------
    // Main Accelerator FSM - Sequential Logic (--- MODIFIED ---)
    //--------------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state_q <= S_IDLE;
            i_tile_idx_q <= '0; j_tile_idx_q <= '0; k_tile_idx_q <= '0;
            load_ab_select_q <= 1'b0; compute_ab_select_q <= 1'b1;
            // --- DELETED ---
            // compute_c_select_q <= 1'b0; write_c_select_q <= 1'b1;
            load_done_flag_q <= 1'b0; compute_done_flag_q <= 1'b0;
            pipe_delay_cnt_q <= '0;
        end else begin
            current_state_q <= next_state_d;
            i_tile_idx_q <= i_tile_idx_d; j_tile_idx_q <= j_tile_idx_d; k_tile_idx_q <= k_tile_idx_d;
            load_ab_select_q <= load_ab_select_d; compute_ab_select_q <= compute_ab_select_d;
            // --- DELETED ---
            // compute_c_select_q <= compute_c_select_d; write_c_select_q <= write_c_select_d;
            load_done_flag_q <= load_done_flag_d; compute_done_flag_q <= compute_done_flag_d;
            pipe_delay_cnt_q <= pipe_delay_cnt_d;
        end
    end

    //--------------------------------------------------------------------------
    // Main Accelerator FSM - Combinational Logic (--- MODIFIED ---)
    //--------------------------------------------------------------------------
    always_comb begin
        next_state_d = current_state_q;
        i_tile_idx_d = i_tile_idx_q; j_tile_idx_d = j_tile_idx_q; k_tile_idx_d = k_tile_idx_q;
        load_ab_select_d = load_ab_select_q; compute_ab_select_d = compute_ab_select_q;
        // --- DELETED ---
        // compute_c_select_d = compute_c_select_q; write_c_select_d = write_c_select_q;
        load_done_flag_d = load_done_flag_q; compute_done_flag_d = compute_done_flag_q;
        pipe_delay_cnt_d = pipe_delay_cnt_q;
        
        loader_req_pulse = 1'b0; df_start_pass_pulse = 1'b0; sa_start_k_iter_pulse = 1'b0; writer_req_pulse = 1'b0;
        
        sa_activate_pe_level = (current_state_q == S_START_SA || current_state_q == S_WAIT_SA_AND_LOAD);

        busyb = (current_state_q == S_IDLE);
        done = (current_state_q == S_FINISH);
        
        if (loader_done) load_done_flag_d = 1'b1;
        if (sa_k_iter_done) compute_done_flag_d = 1'b1;

        case (current_state_q)
            S_IDLE: if (comp_enb) next_state_d = S_INIT_GEMM;
            
            S_INIT_GEMM: begin
                i_tile_idx_d = 0; j_tile_idx_d = 0; k_tile_idx_d = 0;
                load_ab_select_d = 0; compute_ab_select_d = 1;
                // --- DELETED ---
                // compute_c_select_d = 0; write_c_select_d = 1;
                next_state_d = S_LOAD_FIRST;
            end

            S_LOAD_FIRST: begin
                loader_req_pulse = 1'b1;
                load_done_flag_d = 1'b0;
                next_state_d = S_WAIT_LOAD_FIRST;
            end

            S_WAIT_LOAD_FIRST: begin
                if (load_done_flag_q) begin
                    compute_ab_select_d = load_ab_select_q;
                    load_ab_select_d = ~load_ab_select_q;
                    k_tile_idx_d = 0;
                    next_state_d = S_START_DF;
                end
            end

            S_START_DF: begin
                df_start_pass_pulse = 1'b1;
                // For 16x16, K_ITER_MAX is 1. The condition (k_tile_idx_q < K_ITER_MAX - 1) will be false.
                // No prefetch will be issued, which is correct for a single k-iteration.
                if (k_tile_idx_q < K_ITER_MAX - 1) loader_req_pulse = 1'b1;
                load_done_flag_d = 1'b0;
                compute_done_flag_d = 1'b0;
                pipe_delay_cnt_d = 0;
                next_state_d = S_PIPE_DELAY;
            end
            
            S_PIPE_DELAY: begin
                if (pipe_delay_cnt_q == 2'd1) begin
                    next_state_d = S_START_SA;
                end else begin
                    pipe_delay_cnt_d = pipe_delay_cnt_q + 1;
                end
            end
            
            S_START_SA: begin
                sa_start_k_iter_pulse = 1'b1;
                next_state_d = S_WAIT_SA_AND_LOAD;
            end
            
            S_WAIT_SA_AND_LOAD: begin
                logic load_task_finished = (k_tile_idx_q == K_ITER_MAX - 1) ? 1'b1 : load_done_flag_q;
                if (compute_done_flag_q && load_task_finished) begin
                     if (k_tile_idx_q == K_ITER_MAX - 1) begin
                        // --- DELETED ---: No need to select which SRAM_C to write from.
                        // write_c_select_d = compute_c_select_q;
                        next_state_d = S_WRITE_TILE;
                     end else begin
                        // This 'else' block will not be entered for 16x16 matrix size.
                        k_tile_idx_d = k_tile_idx_q + 1;
                        compute_ab_select_d = load_ab_select_q;
                        load_ab_select_d = ~load_ab_select_q;
                        next_state_d = S_START_DF;
                     end
                end
            end
            
            S_WRITE_TILE: begin
                writer_req_pulse = 1'b1;
                next_state_d = S_WAIT_WRITE_DONE;
            end

            S_WAIT_WRITE_DONE: begin
                if (writer_done) begin
                    // For 16x16, I_ITER_MAX/J_ITER_MAX are 1. This condition will be true.
                    if (i_tile_idx_q == I_ITER_MAX - 1 && j_tile_idx_q == J_ITER_MAX - 1) begin
                        next_state_d = S_FINISH;
                    end else begin
                        // This 'else' block will not be entered for 16x16 matrix size.
                        if (j_tile_idx_q == J_ITER_MAX - 1) begin
                            i_tile_idx_d = i_tile_idx_q + 1; j_tile_idx_d = 0;
                        end else begin
                            j_tile_idx_d = j_tile_idx_q + 1;
                        end
                        k_tile_idx_d = 0;
                        // --- DELETED ---: No need to flip the SRAM_C buffer
                        // compute_c_select_d = ~compute_c_select_q;
                        next_state_d = S_LOAD_FIRST;
                    end
                end
            end

            S_FINISH: begin
                done = 1'b1;
                next_state_d = S_IDLE;
            end

            default: next_state_d = S_IDLE;
        endcase
    end

endmodule