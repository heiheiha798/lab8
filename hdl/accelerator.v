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
    input  wire                               omem_req_ready
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
    // localparam DF_SRAM_ADDR_WIDTH     = $clog2(TILE_SIZE * TILE_SIZE); // Corrected: should be $clog2(TILE_SIZE * TILE_SIZE) for 2D address, but DF uses indexed access, so DF_SRAM_ADDR_WIDTH = TILE_SIZE * $clog2(TILE_SIZE) seems wrong. It should be $clog2(TILE_SIZE) for row/col index. Let's assume it's correct for now based on DF module.
    localparam DF_SRAM_DATA_WIDTH     = TILE_SIZE * INPUT_DATA_WIDTH;
    
    // SRAM C parameters derived from the new top-level parameter
    localparam SRAM_C_TOTAL_BITS      = TILE_SIZE * TILE_SIZE * ACCUM_DATA_WIDTH;
    localparam SRAM_C_DEPTH           = SRAM_C_TOTAL_BITS / SRAM_C_WRITE_WIDTH;
    localparam SRAM_C_ADDR_WIDTH      = $clog2(SRAM_C_DEPTH);
    
    // localparam WRITER_SRAM_C_ADDR_WIDTH = $clog2(TILE_SIZE * TILE_SIZE * ACCUM_DATA_WIDTH / MAIN_MEM_DATA_WIDTH_BITS);

    //--------------------------------------------------------------------------
    // FSM State Definitions (REVISED)
    //--------------------------------------------------------------------------
    typedef enum logic [2:0] {
        S_IDLE,
        S_INIT_GEMM,
        S_START_TILE_COMP,   // Start computation for a C(i,j) tile
        S_LOAD_K_SLICE,      // Head of the k-loop, load A(i,k) and B(k,j)
        S_WAIT_LOAD_DONE,    // Wait for loader to finish loading one slice
        S_START_DF,          // Start data formatter for the loaded slice
        S_COMPUTE_DONE_WAIT_WRITE // NEW: Computation is finished, wait for write-back
    } accel_fsm_state_t;
    accel_fsm_state_t current_state_q, next_state_d;

    // --- NEW Write-Back FSM State Definitions ---
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

    // --- NEW: Registers for Writer FSM's tile indices ---
    logic [I_ITER_WIDTH-1:0] i_writer_idx_q, i_writer_idx_d;
    logic [J_ITER_WIDTH-1:0] j_writer_idx_q, j_writer_idx_d;
    // --- NEW: Signal to indicate all writes are done ---
    reg  writer_overall_done_q; // Registered output
    logic writer_overall_done_d; // Combinational input for writer_overall_done_q

    logic load_ab_select_q,    load_ab_select_d;
    logic compute_ab_select_q, compute_ab_select_d;
    
    logic loader_req_pulse;
    logic df_start_pass_pulse;
    logic writer_req_pulse; // For the writer module
    logic sa_activate_pe_level;

    logic loader_done;
    logic tile_computation_done; // From sa_enhanced, indicates one C(i,j) tile is accumulated
    logic writer_done;           // From writer, indicates one C(i,j) tile is written to main mem

    // --- NEW: 用于生成延时清零脉冲的信号 ---
    logic delayed_clear_sa_pulse_d; // 组合逻辑输出
    reg  delayed_clear_sa_pulse_q;  // 寄存器输出，实现一周期脉冲
    
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
    logic [TILE_SIZE*$clog2(TILE_SIZE)-1:0] sram_a_ping_raddr, sram_a_pong_raddr, sram_b_ping_raddr, sram_b_pong_raddr;
    logic [DF_SRAM_DATA_WIDTH-1:0] sram_a_ping_rdata, sram_a_pong_rdata, sram_b_ping_rdata, sram_b_pong_rdata;
    sram_banked #(.IS_SRAM_A(1'b1), .NUM_BANKS(TILE_SIZE), .BANK_DEPTH(TILE_SIZE), .BANK_DATA_WIDTH(INPUT_DATA_WIDTH), .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS)) sram_a_ping (.clk(clk), .we(sram_a_ping_we), .waddr(sram_a_ping_waddr), .wdata(sram_a_ping_wdata), .raddr(sram_a_ping_raddr), .rdata(sram_a_ping_rdata));
    sram_banked #(.IS_SRAM_A(1'b1), .NUM_BANKS(TILE_SIZE), .BANK_DEPTH(TILE_SIZE), .BANK_DATA_WIDTH(INPUT_DATA_WIDTH), .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS)) sram_a_pong (.clk(clk), .we(sram_a_pong_we), .waddr(sram_a_pong_waddr), .wdata(sram_a_pong_wdata), .raddr(sram_a_pong_raddr), .rdata(sram_a_pong_rdata));
    sram_banked #(.IS_SRAM_A(1'b0), .NUM_BANKS(TILE_SIZE), .BANK_DEPTH(TILE_SIZE), .BANK_DATA_WIDTH(INPUT_DATA_WIDTH), .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS)) sram_b_ping (.clk(clk), .we(sram_b_ping_we), .waddr(sram_b_ping_waddr), .wdata(sram_b_ping_wdata), .raddr(sram_b_ping_raddr), .rdata(sram_b_ping_rdata));
    sram_banked #(.IS_SRAM_A(1'b0), .NUM_BANKS(TILE_SIZE), .BANK_DEPTH(TILE_SIZE), .BANK_DATA_WIDTH(INPUT_DATA_WIDTH), .BUS_DATA_WIDTH(MAIN_MEM_DATA_WIDTH_BITS)) sram_b_pong (.clk(clk), .we(sram_b_pong_we), .waddr(sram_b_pong_waddr), .wdata(sram_b_pong_wdata), .raddr(sram_b_pong_raddr), .rdata(sram_b_pong_rdata));
    
    // --- Data Formatter (Unchanged) ---
    logic [TILE_SIZE*$clog2(TILE_SIZE)-1:0] df_sram_a_addr, df_sram_b_addr;
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
        .start_tile_computation(delayed_clear_sa_pulse_q), // This pulse clears SA results for a new (i,j) tile
        .activate_pe_computation(sa_activate_pe_level), 
        .array_a_in(df_skewed_a_out), 
        .array_b_in(df_skewed_b_out), 
        .array_a_valid_in_indywidual(df_skewed_a_valid_out), 
        .array_b_valid_in_indywidual(df_skewed_b_valid_out), 
        .tile_computation_done(tile_computation_done), // SA asserts this when a C(i,j) tile is fully computed
        .sa_busy(), 
        .sram_c_waddr_to_sram(sram_c_waddr), 
        .sram_c_wdata_to_sram(sram_c_wdata), 
        .sram_c_we_to_sram(sram_c_we)
    );
    
    // --- SRAM C (MODIFIED Instantiation) ---
    logic [SRAM_C_ADDR_WIDTH-1:0]        writer_sram_c_addr;
    logic [SRAM_C_WRITE_WIDTH-1:0]       sram_c_rdata_to_writer;
    sram_c #(
        .NUM_ENTRIES(SRAM_C_DEPTH),
        .ENTRY_WIDTH(SRAM_C_WRITE_WIDTH)
        // BUS_DATA_WIDTH 参数已删除
    ) u_sram_c (
        .clk(clk), 
        .rst_n(rst_n),
        .we(sram_c_we),
        .waddr(sram_c_waddr),
        .wdata(sram_c_wdata),
        // raddr 和 rdata 端口连接的信号线已在第2步中修正
        .raddr(writer_sram_c_addr),
        .rdata(sram_c_rdata_to_writer)
    );

    // --- Writer (MODIFIED Connections) ---
    writer #(
        .MATRIX_SIZE(MATRIX_SIZE), 
        .TILE_SIZE(TILE_SIZE), 
        .MAIN_MEM_ADDR_WIDTH(MAIN_MEM_ADDR_WIDTH), 
        .MAIN_MEM_DATA_WIDTH_BITS(MAIN_MEM_DATA_WIDTH_BITS), 
        .BASE_ADDR_C(BASE_ADDR_C),
        // 传递新的参数
        .SRAM_C_WRITE_WIDTH(SRAM_C_WRITE_WIDTH),
        .PE_ACCUM_DATA_WIDTH(ACCUM_DATA_WIDTH)
    ) u_writer (
        .clk(clk), 
        .rst_n(rst_n), 
        .write_req(writer_req_pulse), 
        .i_tile_idx(i_writer_idx_q),
        .j_tile_idx(j_writer_idx_q),
        .write_busy(), // 通常悬空
        .write_done(writer_done), 
        .mem_req_valid(omem_write_enb), 
        .mem_req_wdata(omem_wdata), 
        .mem_req_addr(omem_addr), 
        .mem_req_ready(omem_req_ready), 
        .mem_write_done(1'b1), // 通常连接到高电平，因为writer自己管理流水线
        // sram_c_addr 和 sram_c_rdata 端口连接的信号线已在第2步中修正
        .sram_c_addr(writer_sram_c_addr), 
        .sram_c_rdata(sram_c_rdata_to_writer)
    );
    
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
    // Writer FSM - Sequential Logic (NEW)
    //--------------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            write_state_q <= W_IDLE;
            i_writer_idx_q <= '0;
            j_writer_idx_q <= '0;
            writer_overall_done_q <= 1'b0; // Initialize overall done flag
        end else begin
            write_state_q <= write_next_state_d;
            i_writer_idx_q <= i_writer_idx_d;
            j_writer_idx_q <= j_writer_idx_d;
            writer_overall_done_q <= writer_overall_done_d;
        end
    end

    //--------------------------------------------------------------------------
    // Main Accelerator FSM - Combinational Logic (REVISED)
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
        
        // SA is active during the entire computation phase of a tile (any state from START_TILE_COMP to START_DF)
        sa_activate_pe_level = (current_state_q inside {S_START_TILE_COMP, S_LOAD_K_SLICE, S_WAIT_LOAD_DONE, S_START_DF, S_COMPUTE_DONE_WAIT_WRITE});

        // Default busy and done signals (will be overwritten by overall logic below)
        busyb = 1'b0; 
        done  = 1'b0;
        
        case (current_state_q)
            S_IDLE: begin
                if (comp_enb) next_state_d = S_INIT_GEMM;
            end
            
            S_INIT_GEMM: begin
                i_tile_idx_d = 0; j_tile_idx_d = 0;
                k_tile_idx_d = 0; // Ensure k is reset for the very first tile
                load_ab_select_d = 0; compute_ab_select_d = 1;
                next_state_d = S_START_TILE_COMP;
            end

            // Start a new C(i,j) tile calculation. Reset SA and k-counter.
            S_START_TILE_COMP: begin
                k_tile_idx_d = 0; // Reset k-counter for this (i,j) tile
                delayed_clear_sa_pulse_d = 1'b1; // Pulse to clear/reset SA
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

            // Start processing the k-slice.
            // Decide whether to load the next k-slice or transition to the next (i,j) tile.
            S_START_DF: begin
                df_start_pass_pulse = 1'b1;
                if (k_tile_idx_q == K_ITER_COUNT - 1) begin
                    // This was the last k-slice for the current (i,j) tile.
                    // The SA's accumulation for this (i,j) tile is now complete.
                    // Decide next (i,j) tile for *computation*.
                    if (i_tile_idx_q == NUM_TILES_PER_DIM - 1 && j_tile_idx_q == NUM_TILES_PER_DIM - 1) begin
                        // All (i,j) tiles have had their last k-slice computation initiated.
                        next_state_d = S_COMPUTE_DONE_WAIT_WRITE; // Computation FSM's task is complete
                    end else begin
                        // Move to the next (i,j) tile in row-major order
                        if (j_tile_idx_q == NUM_TILES_PER_DIM - 1) begin
                            i_tile_idx_d = i_tile_idx_q + 1;
                            j_tile_idx_d = 0;
                        end else begin
                            j_tile_idx_d = j_tile_idx_q + 1;
                        end
                        k_tile_idx_d = 0; // Reset k for the new (i,j) tile
                        next_state_d = S_START_TILE_COMP; // Start computation for the new C(i,j) tile
                    end
                end else begin
                    // Not the last k-slice, continue with next k.
                    k_tile_idx_d = k_tile_idx_q + 1;
                    next_state_d = S_LOAD_K_SLICE; // Start loading the next k-slice (pipelined)
                end
            end
            
            S_COMPUTE_DONE_WAIT_WRITE: begin
                // Computation FSM has completed all its tasks.
                // It will stay in this state until the entire process (including writing) is done.
            end

            default: next_state_d = S_IDLE;
        endcase
    end

    //--------------------------------------------------------------------------
    // Writer FSM - Combinational Logic (NEW)
    //--------------------------------------------------------------------------
    always_comb begin
        write_next_state_d = write_state_q;
        writer_req_pulse = 1'b0;
        i_writer_idx_d = i_writer_idx_q;
        j_writer_idx_d = j_writer_idx_q;
        writer_overall_done_d = writer_overall_done_q; // Default to hold current state

        case (write_state_q)
            W_IDLE: begin
                // Trigger write if SA has completed a tile's computation (tile_computation_done)
                // And we are not yet done with all writes.
                if (tile_computation_done) begin
                    writer_req_pulse = 1'b1;
                    write_next_state_d = W_WAIT_WRITE_DONE;
                end
            end

            // W_WRITE_TILE state could be explicitly used if writer_req_pulse needed to be asserted for multiple cycles.
            // For a single pulse, we can directly transition to W_WAIT_WRITE_DONE after asserting it in W_IDLE.
            // If writer_req_pulse needs to be asserted longer (e.g. if writer requires it for a full cycle), 
            // you might need a dedicated W_WRITE_TILE state. For simplicity, we assume single pulse is enough.
            // writer_req_pulse is directly assigned in W_IDLE and then held low once state transitions.

            W_WAIT_WRITE_DONE: begin
                if (writer_done) begin
                    // Increment writer indices
                    if (j_writer_idx_q == NUM_TILES_PER_DIM - 1) begin
                        i_writer_idx_d = i_writer_idx_q + 1;
                        j_writer_idx_d = 0;
                    end else begin
                        j_writer_idx_d = j_writer_idx_q + 1;
                    end
                    
                    write_next_state_d = W_IDLE; // Go back to idle to wait for next tile to be ready

                    // Check if this was the last tile that needed writing
                    if (i_writer_idx_q == NUM_TILES_PER_DIM - 1 && j_writer_idx_q == NUM_TILES_PER_DIM - 1) begin
                        writer_overall_done_d = 1'b1; // Mark write-back as fully done
                    end
                end
            end

            default: write_next_state_d = W_IDLE;
        endcase
    end

    //--------------------------------------------------------------------------
    // Top-Level Control Signals
    //--------------------------------------------------------------------------
    // Busy when comp_enb is active AND the overall process is not done.
    // Or, if comp_enb is not active, but the system is still flushing pending writes.
    assign busyb = comp_enb && !(done); 

    // Done when computation FSM has completed its task (S_COMPUTE_DONE_WAIT_WRITE)
    // AND writer FSM has completed all write-back operations (writer_overall_done_q is high).
    assign done = (current_state_q == S_COMPUTE_DONE_WAIT_WRITE) && writer_overall_done_q;

endmodule