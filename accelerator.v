//
// Filename: accelerator.v
// Description: A fully integrated matrix multiplication accelerator.
// REVISED WITH K-DIMENSION LOOPING AND PIPELINING:
// - FSM is redesigned to handle a three-level loop (i, j, k).
// - Added k_tile_idx register to manage the inner loop.
// - Pipelined the loading of the (k+1)-th slice with the computation of the k-th slice.
// - `sa_enhanced` is now correctly controlled to accumulate results over all k iterations.
//
`timescale 1ns / 1ps

module accelerator #(
    // Architectural Parameters
    parameter MATRIX_SIZE               = 16,
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
    parameter SRAM_C_WRITE_WIDTH        = 512 
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
    input  wire                               omem_req_ready
);

    //--------------------------------------------------------------------------
    // Local Parameters & Derived Values
    //--------------------------------------------------------------------------
    localparam NUM_TILES_PER_DIM      = MATRIX_SIZE / TILE_SIZE;
    localparam K_ITER_COUNT           = NUM_TILES_PER_DIM; 
    localparam I_ITER_WIDTH           = (NUM_TILES_PER_DIM > 1) ? $clog2(NUM_TILES_PER_DIM) : 1;
    localparam J_ITER_WIDTH           = (NUM_TILES_PER_DIM > 1) ? $clog2(NUM_TILES_PER_DIM) : 1;
    // --- NEW: Width for the k-loop counter ---
    localparam K_ITER_WIDTH           = (K_ITER_COUNT > 1) ? $clog2(K_ITER_COUNT) : 1;

    localparam LOADER_SRAM_ADDR_WIDTH = $clog2(TILE_SIZE * TILE_SIZE * INPUT_DATA_WIDTH / MAIN_MEM_DATA_WIDTH_BITS);
    localparam DF_SRAM_ADDR_WIDTH     = TILE_SIZE * $clog2(TILE_SIZE);
    localparam DF_SRAM_DATA_WIDTH     = TILE_SIZE * INPUT_DATA_WIDTH;
    
    // SRAM C parameters derived from the new top-level parameter
    localparam SRAM_C_TOTAL_BITS      = TILE_SIZE * TILE_SIZE * ACCUM_DATA_WIDTH;
    localparam SRAM_C_DEPTH           = SRAM_C_TOTAL_BITS / SRAM_C_WRITE_WIDTH;
    localparam SRAM_C_ADDR_WIDTH      = $clog2(SRAM_C_DEPTH);
    
    localparam WRITER_SRAM_C_ADDR_WIDTH = $clog2(TILE_SIZE * TILE_SIZE * ACCUM_DATA_WIDTH / MAIN_MEM_DATA_WIDTH_BITS);

    //--------------------------------------------------------------------------
    // FSM State Definitions (REVISED)
    //--------------------------------------------------------------------------
    typedef enum logic [3:0] {
        S_IDLE,
        S_INIT_GEMM,
        S_START_TILE_COMP,   // Start computation for a C(i,j) tile
        S_LOAD_K_SLICE,      // Head of the k-loop, load A(i,k) and B(k,j)
        S_WAIT_LOAD_DONE,    // Wait for loader to finish loading one slice
        S_START_DF,          // Start data formatter for the loaded slice
        S_WAIT_TILE_DONE,    // After all k-slices are loaded, wait for SA to finish
        S_WRITE_TILE,        // Write final C(i,j) to memory
        S_WAIT_WRITE_DONE,
        S_FINISH
    } accel_fsm_state_t;
    accel_fsm_state_t current_state_q, next_state_d;

    //--------------------------------------------------------------------------
    // Internal Signals and Registers
    //--------------------------------------------------------------------------
    logic [I_ITER_WIDTH-1:0] i_tile_idx_q, i_tile_idx_d;
    logic [J_ITER_WIDTH-1:0] j_tile_idx_q, j_tile_idx_d;
    // --- NEW: K-dimension loop counter ---
    logic [K_ITER_WIDTH-1:0] k_tile_idx_q, k_tile_idx_d;

    logic load_ab_select_q,    load_ab_select_d;
    logic compute_ab_select_q, compute_ab_select_d;
    
    logic loader_req_pulse;
    logic df_start_pass_pulse;
    logic start_tile_computation_pulse;
    logic writer_req_pulse;
    logic sa_activate_pe_level;

    logic loader_done;
    logic tile_computation_done;
    logic writer_done;
    
    // Wires connecting SA to SRAM C (widths are now parametric)
    logic                               sram_c_we;
    logic [SRAM_C_ADDR_WIDTH-1:0]       sram_c_waddr;
    logic signed [SRAM_C_WRITE_WIDTH-1:0] sram_c_wdata;

    //--------------------------------------------------------------------------
    // Sub-module Instantiations (Connections are mostly unchanged)
    //--------------------------------------------------------------------------
    // --- Loader (Unchanged) ---
    logic [LOADER_SRAM_ADDR_WIDTH-1:0] loader_sram_a_addr, loader_sram_b_addr;
    logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] loader_sram_a_wdata, loader_sram_b_wdata;
    logic loader_sram_a_we, loader_sram_b_we;
    loader #(.MATRIX_SIZE(MATRIX_SIZE), .TILE_SIZE(TILE_SIZE), .MAIN_MEM_ADDR_WIDTH(MAIN_MEM_ADDR_WIDTH), .MAIN_MEM_DATA_WIDTH_BITS(MAIN_MEM_DATA_WIDTH_BITS), .BASE_ADDR_A(BASE_ADDR_A), .BASE_ADDR_B(BASE_ADDR_B))
        u_loader (.clk(clk), .rst_n(rst_n), .load_req(loader_req_pulse), .i_tile_idx(i_tile_idx_q), .j_tile_idx(j_tile_idx_q), .k_tile_idx(k_tile_idx_q), .load_to_ping(load_ab_select_q), .load_busy(), .load_done(loader_done), .mem_req_valid(imem_read_enb), .mem_req_ready(imem_req_ready), .mem_resp_valid(imem_resp_valid), .mem_resp_rdata(imem_data_in), .mem_req_addr(imem_addr), .sram_a_addr(loader_sram_a_addr), .sram_a_wdata(loader_sram_a_wdata), .sram_a_we(loader_sram_a_we), .sram_b_addr(loader_sram_b_addr), .sram_b_wdata(loader_sram_b_wdata), .sram_b_we(loader_sram_b_we));
    
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
    
    // --- SA (MODIFIED Instantiation) ---
    sa_enhanced #(
        .SIZE(TILE_SIZE),
        .K_ITER_COUNT(K_ITER_COUNT),
        .SRAM_C_WRITE_WIDTH(SRAM_C_WRITE_WIDTH), // <-- Pass the parameter down
        .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH), 
        .PE_ACCUM_DATA_WIDTH(ACCUM_DATA_WIDTH)
    ) u_sa_enhanced (
        .clk(clk), 
        .rst_n(rst_n), 
        .start_tile_computation(start_tile_computation_pulse), 
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
    
    // --- SRAM C (MODIFIED Instantiation) ---
    logic [WRITER_SRAM_C_ADDR_WIDTH-1:0] writer_sram_c_addr;
    logic [MAIN_MEM_DATA_WIDTH_BITS-1:0] sram_c_rdata_to_writer;
    sram_c #(
        .NUM_ENTRIES(SRAM_C_DEPTH),               // MODIFIED
        .ENTRY_WIDTH(SRAM_C_WRITE_WIDTH),         // MODIFIED
        .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS) 
    ) u_sram_c (
        .clk(clk), 
        .rst_n(rst_n),
        .we(sram_c_we),
        .waddr(sram_c_waddr),
        .wdata(sram_c_wdata),
        .raddr(writer_sram_c_addr),
        .rdata(sram_c_rdata_to_writer)
    );

    // --- Writer (Unchanged) ---
    writer #(.MATRIX_SIZE(MATRIX_SIZE), .TILE_SIZE(TILE_SIZE), .MAIN_MEM_ADDR_WIDTH(MAIN_MEM_ADDR_WIDTH), .MAIN_MEM_DATA_WIDTH_BITS(MAIN_MEM_DATA_WIDTH_BITS), .BASE_ADDR_C(BASE_ADDR_C))
        u_writer (.clk(clk), .rst_n(rst_n), .write_req(writer_req_pulse), .i_tile_idx(i_tile_idx_q), .j_tile_idx(j_tile_idx_q), .write_busy(), .write_done(writer_done), .mem_req_valid(omem_write_enb), .mem_req_wdata(omem_wdata), .mem_req_addr(omem_addr), .mem_req_ready(omem_req_ready), .mem_write_done(1'b1), .sram_c_addr(writer_sram_c_addr), .sram_c_rdata(sram_c_rdata_to_writer));
    
    //--------------------------------------------------------------------------
    // Ping-Pong MUX Logic for SRAM A/B (Unchanged)
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
    // Main Accelerator FSM - Sequential Logic (REVISED)
    //--------------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state_q   <= S_IDLE;
            i_tile_idx_q      <= '0;
            j_tile_idx_q      <= '0;
            k_tile_idx_q      <= '0; // NEW
            load_ab_select_q  <= 1'b0;
            compute_ab_select_q <= 1'b1;
        end else begin
            current_state_q   <= next_state_d;
            i_tile_idx_q      <= i_tile_idx_d;
            j_tile_idx_q      <= j_tile_idx_d;
            k_tile_idx_q      <= k_tile_idx_d; // NEW
            load_ab_select_q  <= load_ab_select_d;
            compute_ab_select_q <= compute_ab_select_d;
        end
    end

    //--------------------------------------------------------------------------
    // Main Accelerator FSM - Combinational Logic (REVISED)
    //--------------------------------------------------------------------------
    always_comb begin
        next_state_d = current_state_q;
        i_tile_idx_d = i_tile_idx_q;
        j_tile_idx_d = j_tile_idx_q;
        k_tile_idx_d = k_tile_idx_q; // NEW
        load_ab_select_d  = load_ab_select_q;
        compute_ab_select_d = compute_ab_select_q;
        
        loader_req_pulse = 1'b0;
        df_start_pass_pulse = 1'b0;
        start_tile_computation_pulse = 1'b0;
        writer_req_pulse = 1'b0;
        
        // SA is active during the entire computation phase of a tile
        sa_activate_pe_level = (current_state_q inside {S_START_TILE_COMP, S_LOAD_K_SLICE, S_WAIT_LOAD_DONE, S_START_DF, S_WAIT_TILE_DONE});

        busyb = (current_state_q == S_IDLE);
        done  = (current_state_q == S_FINISH);
        
        case (current_state_q)
            S_IDLE: if (comp_enb) next_state_d = S_INIT_GEMM;
            
            S_INIT_GEMM: begin
                i_tile_idx_d = 0; j_tile_idx_d = 0;
                load_ab_select_d = 0; compute_ab_select_d = 1;
                next_state_d = S_START_TILE_COMP;
            end

            // Start a new C(i,j) tile calculation. Reset SA and k-counter.
            S_START_TILE_COMP: begin
                start_tile_computation_pulse = 1'b1;
                k_tile_idx_d = 0;
                next_state_d = S_LOAD_K_SLICE;
            end

            // Head of the k-loop. Issue load request for A(i,k) and B(k,j).
            S_LOAD_K_SLICE: begin
                loader_req_pulse = 1'b1;
                next_state_d = S_WAIT_LOAD_DONE;
            end

            S_WAIT_LOAD_DONE: begin
                if (loader_done) begin
                    // Flip ping-pong buffers for compute to use the newly loaded data
                    compute_ab_select_d = load_ab_select_q;
                    load_ab_select_d = ~load_ab_select_q;
                    next_state_d = S_START_DF;
                end
            end

            // Start processing the k-slice and decide whether to load the next k-slice or wait for SA to finish.
            S_START_DF: begin
                df_start_pass_pulse = 1'b1;
                if (k_tile_idx_q == K_ITER_COUNT - 1) begin
                    // Last k-slice has been loaded and is starting computation.
                    // Now, wait for the entire tile computation to finish.
                    next_state_d = S_WAIT_TILE_DONE;
                end else begin
                    // Start loading the next k-slice while the current one is being processed.
                    k_tile_idx_d = k_tile_idx_q + 1;
                    next_state_d = S_LOAD_K_SLICE;
                end
            end
            
            // Wait for the SA to signal that the C(i,j) tile is fully computed.
            S_WAIT_TILE_DONE: begin
                if (tile_computation_done) begin
                    next_state_d = S_WRITE_TILE;
                end
            end
            
            S_WRITE_TILE: begin
                writer_req_pulse = 1'b1;
                next_state_d = S_WAIT_WRITE_DONE;
            end

            S_WAIT_WRITE_DONE: begin
                if (writer_done) begin
                    // Check if all (i,j) tiles are done
                    if (i_tile_idx_q == NUM_TILES_PER_DIM - 1 && j_tile_idx_q == NUM_TILES_PER_DIM - 1) begin
                        next_state_d = S_FINISH;
                    end else begin
                        // Move to the next tile in row-major order
                        if (j_tile_idx_q == NUM_TILES_PER_DIM - 1) begin
                            i_tile_idx_d = i_tile_idx_q + 1; j_tile_idx_d = 0;
                        end else begin
                            j_tile_idx_d = j_tile_idx_q + 1;
                        end
                        // Start computation for the new C(i,j) tile
                        next_state_d = S_START_TILE_COMP;
                    end
                end
            end

            S_FINISH: begin
                // done signal is combinatorially assigned
                next_state_d = S_IDLE;
            end

            default: next_state_d = S_IDLE;
        endcase
    end

endmodule