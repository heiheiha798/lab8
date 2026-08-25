//
// Filename: accelerator_synth.v
// Description: A fully integrated matrix multiplication accelerator, prepared for logic synthesis.
//              SRAM instances have been removed and their interfaces are exposed as top-level ports.
// REVISED WITH K-DIMENSION LOOPING AND PIPELINING:
// - FSM is redesigned to handle a three-level loop (i, j, k).
// - Added k_tile_idx register to manage the inner loop.
// - Pipelined the loading of the (k+1)-th slice with the computation of the k-th slice.
// - `sa_enhanced` is now correctly controlled to accumulate results over all k iterations.
//
`timescale 1ns / 1ps

module accelerator #(
    // Architectural Parameters
    parameter MATRIX_SIZE               = 512,
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
    parameter BASE_ADDR_C               = 32'h30000000,
    
    // --- NEW PARAMETER to control SRAM C write path ---
    // Set to 512 for high performance, or 64 for low power/area.
    parameter SRAM_C_WRITE_WIDTH        = 256
) (
    // --- Top Controller Interface ---
    input  wire                               clk,
    input  wire                               rst_n,
    input  wire                               comp_enb,
    output logic                              busyb,
    output logic                              done,

    // --- Input Memory Interface (Read-only) ---
    output logic [MAIN_MEM_ADDR_WIDTH-1:0]    imem_addr,
    output logic                              imem_read_enb,
    input  wire [MAIN_MEM_DATA_WIDTH_BITS-1:0] imem_data_in,
    input  wire                               imem_req_ready,
    input  wire                               imem_resp_valid,

    // --- Result Memory Interface (Write-only) ---
    output logic [MAIN_MEM_ADDR_WIDTH-1:0]    omem_addr,
    output logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] omem_wdata,
    output logic                              omem_write_enb,
    input  wire                               omem_req_ready,

    //--------------------------------------------------------------------------
    // SRAM Interface Ports (Exposed for Synthesis)
    //--------------------------------------------------------------------------
    // --- SRAM A Ping Interface ---
    output logic                              sram_a_ping_we,
    output logic [$clog2(TILE_SIZE*TILE_SIZE*INPUT_DATA_WIDTH/MAIN_MEM_DATA_WIDTH_BITS)-1:0] sram_a_ping_waddr,
    output logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] sram_a_ping_wdata,
    output logic [TILE_SIZE*$clog2(TILE_SIZE)-1:0] sram_a_ping_raddr,
    input  wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_a_ping_rdata,

    // --- SRAM A Pong Interface ---
    output logic                              sram_a_pong_we,
    output logic [$clog2(TILE_SIZE*TILE_SIZE*INPUT_DATA_WIDTH/MAIN_MEM_DATA_WIDTH_BITS)-1:0] sram_a_pong_waddr,
    output logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] sram_a_pong_wdata,
    output logic [TILE_SIZE*$clog2(TILE_SIZE)-1:0] sram_a_pong_raddr,
    input  wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_a_pong_rdata,

    // --- SRAM B Ping Interface ---
    output logic                              sram_b_ping_we,
    output logic [$clog2(TILE_SIZE*TILE_SIZE*INPUT_DATA_WIDTH/MAIN_MEM_DATA_WIDTH_BITS)-1:0] sram_b_ping_waddr,
    output logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] sram_b_ping_wdata,
    output logic [TILE_SIZE*$clog2(TILE_SIZE)-1:0] sram_b_ping_raddr,
    input  wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_b_ping_rdata,

    // --- SRAM B Pong Interface ---
    output logic                              sram_b_pong_we,
    output logic [$clog2(TILE_SIZE*TILE_SIZE*INPUT_DATA_WIDTH/MAIN_MEM_DATA_WIDTH_BITS)-1:0] sram_b_pong_waddr,
    output logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] sram_b_pong_wdata,
    output logic [TILE_SIZE*$clog2(TILE_SIZE)-1:0] sram_b_pong_raddr,
    input  wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_b_pong_rdata,
    
    // --- SRAM C Interface ---
    output logic                               sram_c_we,
    output logic [$clog2((TILE_SIZE*TILE_SIZE*ACCUM_DATA_WIDTH)/SRAM_C_WRITE_WIDTH)-1:0] sram_c_waddr,
    output logic signed [SRAM_C_WRITE_WIDTH-1:0] sram_c_wdata,
    output logic [$clog2((TILE_SIZE*TILE_SIZE*ACCUM_DATA_WIDTH)/SRAM_C_WRITE_WIDTH)-1:0] writer_sram_c_addr,
    input  wire [SRAM_C_WRITE_WIDTH-1:0]       sram_c_rdata_to_writer
);

    //--------------------------------------------------------------------------
    // Local Parameters & Derived Values
    //--------------------------------------------------------------------------
    localparam NUM_TILES_PER_DIM      = MATRIX_SIZE / TILE_SIZE;
    localparam K_ITER_COUNT           = NUM_TILES_PER_DIM; 
    localparam I_ITER_WIDTH           = (NUM_TILES_PER_DIM > 1) ? $clog2(NUM_TILES_PER_DIM) : 1;
    localparam J_ITER_WIDTH           = (NUM_TILES_PER_DIM > 1) ? $clog2(NUM_TILES_PER_DIM) : 1;
    localparam K_ITER_WIDTH           = (K_ITER_COUNT > 1) ? $clog2(K_ITER_COUNT) : 1;

    localparam LOADER_SRAM_ADDR_WIDTH = $clog2(TILE_SIZE * TILE_SIZE * INPUT_DATA_WIDTH / MAIN_MEM_DATA_WIDTH_BITS);
    localparam DF_SRAM_DATA_WIDTH     = TILE_SIZE * INPUT_DATA_WIDTH;
    
    localparam SRAM_C_TOTAL_BITS      = TILE_SIZE * TILE_SIZE * ACCUM_DATA_WIDTH;
    localparam SRAM_C_DEPTH           = SRAM_C_TOTAL_BITS / SRAM_C_WRITE_WIDTH;
    localparam SRAM_C_ADDR_WIDTH      = $clog2(SRAM_C_DEPTH);

    //--------------------------------------------------------------------------
    // FSM State Definitions (REVISED)
    //--------------------------------------------------------------------------
    typedef enum logic [2:0] {
        S_IDLE,
        S_INIT_GEMM,
        S_START_TILE_COMP,
        S_LOAD_K_SLICE,
        S_WAIT_LOAD_DONE,
        S_START_DF,
        S_COMPUTE_DONE_WAIT_WRITE
    } accel_fsm_state_t;
    accel_fsm_state_t current_state_q, next_state_d;

    typedef enum logic [1:0] {
        W_IDLE,
        W_WRITE_TILE,    
        W_WAIT_WRITE_DONE
    } accel_write_fsm_state_t;
    accel_write_fsm_state_t write_state_q, write_next_state_d;

    //--------------------------------------------------------------------------
    // Internal Signals and Registers
    //--------------------------------------------------------------------------
    logic [I_ITER_WIDTH-1:0] i_tile_idx_q, i_tile_idx_d;
    logic [J_ITER_WIDTH-1:0] j_tile_idx_q, j_tile_idx_d;
    logic [K_ITER_WIDTH-1:0] k_tile_idx_q, k_tile_idx_d;

    logic [I_ITER_WIDTH-1:0] i_writer_idx_q, i_writer_idx_d;
    logic [J_ITER_WIDTH-1:0] j_writer_idx_q, j_writer_idx_d;
    reg  writer_overall_done_q;
    logic writer_overall_done_d;

    logic load_ab_select_q,    load_ab_select_d;
    logic compute_ab_select_q, compute_ab_select_d;
    
    logic loader_req_pulse;
    logic df_start_pass_pulse;
    logic writer_req_pulse;
    logic sa_activate_pe_level;

    logic loader_done;
    logic tile_computation_done;
    logic writer_done;

    logic delayed_clear_sa_pulse_d;
    reg  delayed_clear_sa_pulse_q;
    
    //--------------------------------------------------------------------------
    // Sub-module Instantiations
    //--------------------------------------------------------------------------
    logic [LOADER_SRAM_ADDR_WIDTH-1:0] loader_sram_a_addr, loader_sram_b_addr;
    logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] loader_sram_a_wdata, loader_sram_b_wdata;
    logic loader_sram_a_we, loader_sram_b_we;
    loader #(.MATRIX_SIZE(MATRIX_SIZE), .TILE_SIZE(TILE_SIZE), .MAIN_MEM_ADDR_WIDTH(MAIN_MEM_ADDR_WIDTH), .MAIN_MEM_DATA_WIDTH_BITS(MAIN_MEM_DATA_WIDTH_BITS), .BASE_ADDR_A(BASE_ADDR_A), .BASE_ADDR_B(BASE_ADDR_B))
        u_loader (.clk(clk), .rst_n(rst_n), .load_req(loader_req_pulse), .i_tile_idx(i_tile_idx_q), .j_tile_idx(j_tile_idx_q), .k_tile_idx(k_tile_idx_q), .load_to_ping(load_ab_select_q), .load_busy(), .load_done(loader_done), .mem_req_valid(imem_read_enb), .mem_req_ready(imem_req_ready), .mem_resp_valid(imem_resp_valid), .mem_resp_rdata(imem_data_in), .mem_req_addr(imem_addr), .sram_a_addr(loader_sram_a_addr), .sram_a_wdata(loader_sram_a_wdata), .sram_a_we(loader_sram_a_we), .sram_b_addr(loader_sram_b_addr), .sram_b_wdata(loader_sram_b_wdata), .sram_b_we(loader_sram_b_we));
    
    // --- SRAMs A & B & C are now external to this module ---
    // The instantiations have been removed. Their IOs are now top-level ports.
    
    logic [TILE_SIZE*$clog2(TILE_SIZE)-1:0] df_sram_a_addr, df_sram_b_addr;
    logic [DF_SRAM_DATA_WIDTH-1:0] df_sram_a_rdata, df_sram_b_rdata, df_skewed_a_out, df_skewed_b_out;
    logic [TILE_SIZE-1:0] df_skewed_a_valid_out, df_skewed_b_valid_out;
    data_formatter #(.TILE_SIZE(TILE_SIZE), .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH)) u_data_formatter (.clk(clk), .rst_n(rst_n), .start_pass(df_start_pass_pulse), .pass_done(), .sram_a_addr(df_sram_a_addr), .sram_a_rdata(df_sram_a_rdata), .sram_b_addr(df_sram_b_addr), .sram_b_rdata(df_sram_b_rdata), .skewed_a_out(df_skewed_a_out), .skewed_b_out(df_skewed_b_out), .data_valid_out(), .skewed_a_valid_out(df_skewed_a_valid_out), .skewed_b_valid_out(df_skewed_b_valid_out));
    
    sa_enhanced #(
        .SIZE(TILE_SIZE),
        .K_ITER_COUNT(K_ITER_COUNT),
        .SRAM_C_WRITE_WIDTH(SRAM_C_WRITE_WIDTH),
        .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH), 
        .PE_ACCUM_DATA_WIDTH(ACCUM_DATA_WIDTH)
    ) u_sa_enhanced (
        .clk(clk), 
        .rst_n(rst_n), 
        .start_tile_computation(delayed_clear_sa_pulse_q),
        .activate_pe_computation(sa_activate_pe_level), 
        .array_a_in(df_skewed_a_out), 
        .array_b_in(df_skewed_b_out), 
        .array_a_valid_in_indywidual(df_skewed_a_valid_out), 
        .array_b_valid_in_indywidual(df_skewed_b_valid_out), 
        .tile_computation_done(tile_computation_done),
        .sa_busy(), 
        .sram_c_waddr_to_sram(sram_c_waddr), 
        .sram_c_wdata_to_sram(sram_c_wdata), 
        .sram_c_we_to_sram(sram_c_we)
    );
    
    writer #(
        .MATRIX_SIZE(MATRIX_SIZE), 
        .TILE_SIZE(TILE_SIZE), 
        .MAIN_MEM_ADDR_WIDTH(MAIN_MEM_ADDR_WIDTH), 
        .MAIN_MEM_DATA_WIDTH_BITS(MAIN_MEM_DATA_WIDTH_BITS), 
        .BASE_ADDR_C(BASE_ADDR_C),
        .SRAM_C_WRITE_WIDTH(SRAM_C_WRITE_WIDTH),
        .PE_ACCUM_DATA_WIDTH(ACCUM_DATA_WIDTH)
    ) u_writer (
        .clk(clk), 
        .rst_n(rst_n), 
        .write_req(writer_req_pulse), 
        .i_tile_idx(i_writer_idx_q),
        .j_tile_idx(j_writer_idx_q),
        .write_busy(),
        .write_done(writer_done), 
        .mem_req_valid(omem_write_enb), 
        .mem_req_wdata(omem_wdata), 
        .mem_req_addr(omem_addr), 
        .mem_req_ready(omem_req_ready), 
        .mem_write_done(1'b1),
        .sram_c_addr(writer_sram_c_addr), 
        .sram_c_rdata(sram_c_rdata_to_writer)
    );
    
    //--------------------------------------------------------------------------
    // Ping-Pong MUX Logic for SRAM A/B
    //--------------------------------------------------------------------------
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
    
    //--------------------------------------------------------------------------
    // Main Accelerator FSM - Sequential Logic
    //--------------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state_q   <= S_IDLE;
            i_tile_idx_q      <= '0;
            j_tile_idx_q      <= '0;
            k_tile_idx_q      <= '0;
            load_ab_select_q  <= 1'b0;
            compute_ab_select_q <= 1'b1;
            delayed_clear_sa_pulse_q <= 1'b0;
        end else begin
            current_state_q   <= next_state_d;
            i_tile_idx_q      <= i_tile_idx_d;
            j_tile_idx_q      <= j_tile_idx_d;
            k_tile_idx_q      <= k_tile_idx_d;
            load_ab_select_q  <= load_ab_select_d;
            compute_ab_select_q <= compute_ab_select_d;
            delayed_clear_sa_pulse_q <= delayed_clear_sa_pulse_d;
        end
    end

    //--------------------------------------------------------------------------
    // Writer FSM - Sequential Logic
    //--------------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            write_state_q <= W_IDLE;
            i_writer_idx_q <= '0;
            j_writer_idx_q <= '0;
            writer_overall_done_q <= 1'b0;
        end else begin
            write_state_q <= write_next_state_d;
            i_writer_idx_q <= i_writer_idx_d;
            j_writer_idx_q <= j_writer_idx_d;
            writer_overall_done_q <= writer_overall_done_d;
        end
    end

    //--------------------------------------------------------------------------
    // Main Accelerator FSM - Combinational Logic
    //--------------------------------------------------------------------------
    always_comb begin
        next_state_d = current_state_q;
        i_tile_idx_d = i_tile_idx_q;
        j_tile_idx_d = j_tile_idx_q;
        k_tile_idx_d = k_tile_idx_q;
        load_ab_select_d  = load_ab_select_q;
        compute_ab_select_d = compute_ab_select_q;
        loader_req_pulse = 1'b0;
        df_start_pass_pulse = 1'b0;
        delayed_clear_sa_pulse_d = 1'b0;
        
        sa_activate_pe_level = (current_state_q == S_START_TILE_COMP ||
                                current_state_q == S_LOAD_K_SLICE ||
                                current_state_q == S_WAIT_LOAD_DONE ||
                                current_state_q == S_START_DF ||
                                current_state_q == S_COMPUTE_DONE_WAIT_WRITE);
        busyb = 1'b0; 
        done  = 1'b0;
        
        case (current_state_q)
            S_IDLE: begin
                if (comp_enb) next_state_d = S_INIT_GEMM;
            end
            
            S_INIT_GEMM: begin
                i_tile_idx_d = 0; j_tile_idx_d = 0;
                k_tile_idx_d = 0;
                load_ab_select_d = 0; compute_ab_select_d = 1;
                next_state_d = S_START_TILE_COMP;
            end

            S_START_TILE_COMP: begin
                k_tile_idx_d = 0;
                delayed_clear_sa_pulse_d = 1'b1;
                next_state_d = S_LOAD_K_SLICE;
            end

            S_LOAD_K_SLICE: begin
                loader_req_pulse = 1'b1;
                next_state_d = S_WAIT_LOAD_DONE;
            end

            S_WAIT_LOAD_DONE: begin
                if (loader_done) begin
                    compute_ab_select_d = load_ab_select_q;
                    load_ab_select_d = ~load_ab_select_q;
                    next_state_d = S_START_DF;
                end
            end

            S_START_DF: begin
                df_start_pass_pulse = 1'b1;
                if (k_tile_idx_q == K_ITER_COUNT - 1) begin
                    if (i_tile_idx_q == NUM_TILES_PER_DIM - 1 && j_tile_idx_q == NUM_TILES_PER_DIM - 1) begin
                        next_state_d = S_COMPUTE_DONE_WAIT_WRITE;
                    end else begin
                        if (j_tile_idx_q == NUM_TILES_PER_DIM - 1) begin
                            i_tile_idx_d = i_tile_idx_q + 1;
                            j_tile_idx_d = 0;
                        end else begin
                            j_tile_idx_d = j_tile_idx_q + 1;
                        end
                        k_tile_idx_d = 0;
                        next_state_d = S_START_TILE_COMP;
                    end
                end else begin
                    k_tile_idx_d = k_tile_idx_q + 1;
                    next_state_d = S_LOAD_K_SLICE;
                end
            end
            
            S_COMPUTE_DONE_WAIT_WRITE: begin
                // Computation FSM stays here until the entire process (including writing) is done.
            end

            default: next_state_d = S_IDLE;
        endcase
    end

    //--------------------------------------------------------------------------
    // Writer FSM - Combinational Logic
    //--------------------------------------------------------------------------
    always_comb begin
        write_next_state_d = write_state_q;
        writer_req_pulse = 1'b0;
        i_writer_idx_d = i_writer_idx_q;
        j_writer_idx_d = j_writer_idx_q;
        writer_overall_done_d = writer_overall_done_q;

        case (write_state_q)
            W_IDLE: begin
                if (tile_computation_done) begin
                    writer_req_pulse = 1'b1;
                    write_next_state_d = W_WAIT_WRITE_DONE;
                end
            end

            W_WAIT_WRITE_DONE: begin
                if (writer_done) begin
                    if (j_writer_idx_q == NUM_TILES_PER_DIM - 1) begin
                        i_writer_idx_d = i_writer_idx_q + 1;
                        j_writer_idx_d = 0;
                    end else begin
                        j_writer_idx_d = j_writer_idx_q + 1;
                    end
                    
                    write_next_state_d = W_IDLE;

                    if (i_writer_idx_q == NUM_TILES_PER_DIM - 1 && j_writer_idx_q == NUM_TILES_PER_DIM - 1) begin
                        writer_overall_done_d = 1'b1;
                    end
                end
            end

            default: write_next_state_d = W_IDLE;
        endcase
    end

    //--------------------------------------------------------------------------
    // Top-Level Control Signals
    //--------------------------------------------------------------------------
    assign busyb = comp_enb && !(done); 
    assign done = (current_state_q == S_COMPUTE_DONE_WAIT_WRITE) && writer_overall_done_q;

endmodule
