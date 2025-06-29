//
// Filename: data_formatter.v
// Description: A high-performance data formatter for the systolic array.
//              (REVISED Address Generation)
//
`timescale 1ns / 1ps

module data_formatter #(
    parameter TILE_SIZE         = 16,
    parameter INPUT_DATA_WIDTH  = 8
)(
    // --- Control Interface ---
    input wire                                  clk,
    input wire                                  rst_n,
    input wire                                  start_pass, // From Compute Controller
    output reg                                  pass_done,  // To Compute Controller

    // --- SRAM Read Interface (Banked) ---
    // sram_a_addr: For each bank of SRAM A, this provides the ROW ADDRESS to read.
    //              Bank index corresponds to A_tile's COLUMN index.
    output wire [TILE_SIZE*$clog2(TILE_SIZE)-1:0] sram_a_addr,
    input wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0]   sram_a_rdata, // Concatenated data from all banks of SRAM A

    // sram_b_addr: For each bank of SRAM B, this provides the ROW ADDRESS to read.
    //              Bank index corresponds to B_tile's ROW index.
    output wire [TILE_SIZE*$clog2(TILE_SIZE)-1:0] sram_b_addr,
    input wire [TILE_SIZE*INPUT_DATA_WIDTH-1:0]   sram_b_rdata, // Concatenated data from all banks of SRAM B

    // --- Systolic Array Feed Interface ---
    output reg [TILE_SIZE*INPUT_DATA_WIDTH-1:0]   skewed_a_out,
    output reg [TILE_SIZE*INPUT_DATA_WIDTH-1:0]   skewed_b_out,
    output reg                                    data_valid_out,         // Overall valid for the wavefront
    output reg [TILE_SIZE-1:0]                    skewed_a_valid_out,     // Individual valid for each A element
    output reg [TILE_SIZE-1:0]                    skewed_b_valid_out      // Individual valid for each B element
);

    //======================================================================
    //== Local Parameters and State Definitions
    //======================================================================
    localparam FSM_STATE_WIDTH   = 2;
    localparam S_IDLE            = {FSM_STATE_WIDTH{1'b0}};
    localparam S_STREAMING       = S_IDLE + 1;
    localparam S_DONE            = S_STREAMING + 1;

    localparam TIME_COUNTER_MAX   = 3 * TILE_SIZE - 2; // For a full pass
    localparam TIME_COUNTER_WIDTH = $clog2(TIME_COUNTER_MAX + 1);

    localparam SRAM_ADDR_WIDTH = $clog2(TILE_SIZE); // Width for a single bank's row address
    // PIPELINE_COMPENSATION:
    // Cycle 0 (T_addr_gen): Address sent from DF.
    // Cycle 1 (T_addr_gen + 1): Data available on sram_x_rdata input.
    // Cycle 2 (T_addr_gen + 2): Data latched into sram_x_rdata_reg_q.
    //                           skewed_x_out logic uses this data.
    //                           t_feed_equivalent = (T_addr_gen + 2) - PIPELINE_COMPENSATION.
    //                           If we want t_feed_equivalent = T_addr_gen, then PIPELINE_COMPENSATION = 2.
    localparam PIPELINE_COMPENSATION = 2;

    //======================================================================
    //== Internal Registers and Wires
    //======================================================================
    reg [FSM_STATE_WIDTH-1:0] current_state_q, next_state_d;
    reg [TIME_COUNTER_WIDTH-1:0] time_cnt_q, time_cnt_d; // This counter drives the effective time for address generation

    reg [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_a_rdata_reg_q;
    reg [TILE_SIZE*INPUT_DATA_WIDTH-1:0] sram_b_rdata_reg_q;

    wire [SRAM_ADDR_WIDTH-1:0] sram_a_addr_internal [0:TILE_SIZE-1];
    wire [SRAM_ADDR_WIDTH-1:0] sram_b_addr_internal [0:TILE_SIZE-1];

    //======================================================================
    //== FSM and Control Logic
    //======================================================================
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state_q <= S_IDLE;
        end else begin
            current_state_q <= next_state_d;
        end
    end

    always @(*) begin
        next_state_d      = current_state_q;
        pass_done       = 1'b0;
        data_valid_out  = 1'b0; // Default, will be overridden

        case (current_state_q)
            S_IDLE: begin
                if (start_pass) begin
                    next_state_d = S_STREAMING;
                end
            end
            S_STREAMING: begin
                // data_valid_out will be high when DF is streaming.
                // The actual validity of skewed_x_out depends on t_feed_equivalent and indices.
                data_valid_out = 1'b1;
                if (time_cnt_q == TIME_COUNTER_MAX) begin
                    next_state_d = S_DONE;
                end
            end
            S_DONE: begin
                pass_done = 1'b1;
                next_state_d = S_IDLE;
            end
            default: begin
                next_state_d = S_IDLE;
            end
        endcase
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            time_cnt_q <= 0;
        end else begin
            time_cnt_q <= time_cnt_d;
        end
    end

    always @(*) begin
        time_cnt_d = time_cnt_q;
        if (current_state_q == S_IDLE && next_state_d == S_STREAMING) begin
            time_cnt_d = 0; // Reset counter when starting a pass
        end else if (current_state_q == S_STREAMING) begin
            if (time_cnt_q < TIME_COUNTER_MAX) begin
                time_cnt_d = time_cnt_q + 1;
            end
        end
    end

    //======================================================================
    //== Datapath Logic
    //======================================================================

    // --- SRAM Address Generation (REVISED) ---
    //
    // **核心Bug修复**
    //
    // **问题**: 原始代码中的地址计算 `time_cnt_q - i_sram_bank_phys_idx` 是无符号减法。
    // 当流水线刚启动时，`time_cnt_q` 的值很小。对于物理Bank号 `i_sram_bank_phys_idx` 较大的SRAM Bank，
    // 这个减法会发生下溢 (e.g., 2 - 8)，结果是一个巨大的正数，而不是一个负数。
    // 这导致 `addr_in_bounds` 条件 `(time_cnt_q >= i_sram_bank_phys_idx)` 立即判为假，
    // 从而为这些Bank生成了无效地址'x'，使得SA无法获取正确的数据，导致计算结果为0。
    genvar i_sram_bank_phys_idx; // Physical SRAM bank index (0 to TILE_SIZE-1)
    generate
        for (i_sram_bank_phys_idx = 0; i_sram_bank_phys_idx < TILE_SIZE; i_sram_bank_phys_idx = i_sram_bank_phys_idx + 1) begin : addr_gen_loop
            // --- MODIFICATION START ---
            
            // 1. 声明一个 signed 类型的中间变量来存储地址计算结果。
            //    位宽应与 time_cnt_q 相同，以防止溢出并能表示负数。
            logic signed [TIME_COUNTER_WIDTH-1:0] signed_calculated_addr;

            logic addr_gen_active;
            logic addr_in_bounds;

            // 2. 使用 $signed() 进行有符号减法。
            assign signed_calculated_addr = $signed(time_cnt_q) - $signed(i_sram_bank_phys_idx);
            
            // 3. 边界检查逻辑现在基于有符号结果。
            //    一个有效的地址必须大于等于0且小于TILE_SIZE。
            assign addr_in_bounds = (signed_calculated_addr >= 0) && (signed_calculated_addr < TILE_SIZE);
            
            // addr_gen_active 的逻辑保持不变
            assign addr_gen_active = ((current_state_q == S_STREAMING) || (current_state_q == S_IDLE && next_state_d == S_STREAMING));

            // 4. 最终地址赋值。在确认地址有效后，将 signed 结果安全地转换为 unsigned 地址。
            //    我们只取其低位 [SRAM_ADDR_WIDTH-1:0]，因为 addr_in_bounds 保证了其值在正确范围内。
            assign sram_a_addr_internal[i_sram_bank_phys_idx] = (addr_gen_active && addr_in_bounds) ?
                                                            signed_calculated_addr[SRAM_ADDR_WIDTH-1:0] :
                                                            {SRAM_ADDR_WIDTH{1'bx}}; // 'x' for invalid address helps debugging

            assign sram_b_addr_internal[i_sram_bank_phys_idx] = (addr_gen_active && addr_in_bounds) ?
                                                            signed_calculated_addr[SRAM_ADDR_WIDTH-1:0] :
                                                            {SRAM_ADDR_WIDTH{1'bx}};
                                                            
            // --- MODIFICATION END ---
        end
    endgenerate

    // Concatenate internal bank addresses to form the module's output address buses
    genvar concat_idx;
    generate
        for (concat_idx = 0; concat_idx < TILE_SIZE; concat_idx = concat_idx + 1) begin : concat_addr_loop
            assign sram_a_addr[concat_idx*SRAM_ADDR_WIDTH +: SRAM_ADDR_WIDTH] = sram_a_addr_internal[concat_idx];
            assign sram_b_addr[concat_idx*SRAM_ADDR_WIDTH +: SRAM_ADDR_WIDTH] = sram_b_addr_internal[concat_idx];
        end
    endgenerate

    // --- SRAM Data Pipelining ---
    always @(posedge clk) begin
        // These registers (sram_x_rdata_reg_q) introduce one stage of the PIPELINE_COMPENSATION.
        // The SRAM itself introduces the other stage.
        sram_a_rdata_reg_q <= sram_a_rdata;
        sram_b_rdata_reg_q <= sram_b_rdata;
    end

    // --- Skewed Output Generation (REVISED data selection for B) ---
    always @(posedge clk or negedge rst_n) begin
        integer i_out_ch;         // Output channel index (0 to TILE_SIZE-1), SA's perspective
        integer target_col_A;     // Target COLUMN index for A_tile for channel i_out_ch
        integer target_row_B;     // Target ROW index for B_tile for channel i_out_ch
        integer t_feed_equivalent; // SA wavefront time, starts from 0

        if (!rst_n) begin
            skewed_a_out <= {TILE_SIZE*INPUT_DATA_WIDTH{1'b0}};
            skewed_b_out <= {TILE_SIZE*INPUT_DATA_WIDTH{1'b0}};
            skewed_a_valid_out <= {TILE_SIZE{1'b0}};
            skewed_b_valid_out <= {TILE_SIZE{1'b0}};
        end else begin
            if (data_valid_out) begin // True when FSM is in S_STREAMING
                                     // For correct data, should ideally be (time_cnt_q >= PIPELINE_COMPENSATION)
                t_feed_equivalent = time_cnt_q - PIPELINE_COMPENSATION;

                for (i_out_ch = 0; i_out_ch < TILE_SIZE; i_out_ch = i_out_ch + 1) begin
                    // --- For Matrix A ---
                    // SA channel 'i_out_ch' (SA row index) needs A_tile[i_out_ch][t_feed_equivalent - i_out_ch]
                    target_col_A = t_feed_equivalent - i_out_ch;

                    if (target_col_A >= 0 && target_col_A < TILE_SIZE && t_feed_equivalent >= 0) begin
                        // SRAM A: bank index is A_tile's COLUMN index.
                        // Data in sram_a_rdata_reg_q[bank 'target_col_A'] was read from A_tile's ROW 'i_out_ch'
                        // due to the revised address generation: sram_a_addr_internal[target_col_A] was set to 'i_out_ch'
                        // (where i_out_ch = t_feed_at_addr_gen - target_col_A, and t_feed_at_addr_gen = t_feed_equivalent)
                        skewed_a_out[i_out_ch*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] <= sram_a_rdata_reg_q[target_col_A*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
                        skewed_a_valid_out[i_out_ch]                                <= 1'b1;
                    end else begin
                        skewed_a_out[i_out_ch*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] <= {INPUT_DATA_WIDTH{1'b0}};
                        skewed_a_valid_out[i_out_ch]                                <= 1'b0;
                    end

                    // --- For Matrix B ---
                    // SA channel 'i_out_ch' (SA col index) needs B_tile[t_feed_equivalent - i_out_ch][i_out_ch]
                    target_row_B = t_feed_equivalent - i_out_ch; // This is the ROW of B_tile

                    if (target_row_B >= 0 && target_row_B < TILE_SIZE && t_feed_equivalent >= 0) begin
                        // SRAM B: bank index is B_tile's ROW index.
                        // Data in sram_b_rdata_reg_q[bank 'target_row_B'] was read from B_tile's COLUMN 'i_out_ch'
                        // due to the revised address generation: sram_b_addr_internal[target_row_B] was set to 'i_out_ch'
                        skewed_b_out[i_out_ch*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] <= sram_b_rdata_reg_q[target_row_B*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
                        skewed_b_valid_out[i_out_ch]                                <= 1'b1;
                    end else begin
                        skewed_b_out[i_out_ch*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] <= {INPUT_DATA_WIDTH{1'b0}};
                        skewed_b_valid_out[i_out_ch]                                <= 1'b0;
                    end
                end

                // Display when data is being sent out for this time step (after all channels are processed)
                if (t_feed_equivalent >= 0) begin
                    $display("%0t [DF SEND] 时间步t_f=%d: 发送A数据=0x%h, 发送B数据=0x%h", 
                             $time, 
                             t_feed_equivalent, 
                             skewed_a_out,
                             skewed_b_out);
                end
            end else begin // if not data_valid_out (i.e., not S_STREAMING)
                skewed_a_out <= {TILE_SIZE*INPUT_DATA_WIDTH{1'b0}};
                skewed_b_out <= {TILE_SIZE*INPUT_DATA_WIDTH{1'b0}};
                skewed_a_valid_out <= {TILE_SIZE{1'b0}};
                skewed_b_valid_out <= {TILE_SIZE{1'b0}};
            end
        end
    end

endmodule
