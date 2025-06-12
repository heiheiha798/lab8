`timescale 1ns / 1ps

module pe #(
    parameter DATA_WIDTH = 16,
    parameter MAC_COUNT_TARGET = 16, // Target number of MAC operations
    parameter integer PE_ROW_ID = -1,
    parameter integer PE_COL_ID = -1
)(
    input wire                      clk,
    input wire                      rst_n,
    input wire                      enable,             // General enable for the PE
    input wire                      clear_accumulator,  // Resets accumulator and MAC counter

    input wire                      a_valid_in,         // Indicates if a_data_in is valid
    input wire [DATA_WIDTH-1:0]     a_data_in,
    output wire                     a_valid_out,        // Propagates a_valid_in
    output wire [DATA_WIDTH-1:0]    a_data_out,

    input wire                      b_valid_in,         // Indicates if b_data_in is valid
    input wire [DATA_WIDTH-1:0]     b_data_in,
    output wire                     b_valid_out,        // Propagates b_valid_in
    output wire [DATA_WIDTH-1:0]    b_data_out,

    output wire [DATA_WIDTH-1:0]    result_out,
    output wire                     result_valid,       // Pulsed high when MAC_COUNT_TARGET MACs are done
    output wire                     pe_is_nan,
    output wire                     pe_is_infinity
);
    reg [DATA_WIDTH-1:0] a_reg;
    reg [DATA_WIDTH-1:0] b_reg;
    reg                      a_valid_reg;
    reg                      b_valid_reg;

    reg [DATA_WIDTH-1:0] local_accumulator_reg;
    reg [DATA_WIDTH-1:0] mul_result_reg;
    reg                      mul_valid_reg; // Indicates if mul_result_reg holds a valid product

    reg acc_is_nan_reg;
    reg acc_is_infinity_reg;
    reg acc_sign_if_inf_reg;

    reg [$clog2(MAC_COUNT_TARGET+1)-1:0] performed_mac_count;
    
    // Combinational wire to calculate the next value of performed_mac_count
    wire [$clog2(MAC_COUNT_TARGET+1)-1:0] next_performed_mac_count_w;

    reg result_valid_reg;
    reg pe_calculation_done_latch;

    wire [DATA_WIDTH-1:0] mul_output_data;
    wire                  mul_output_is_nan;
    wire                  mul_output_is_inf;

    wire [DATA_WIDTH-1:0] add_output_data;
    wire                  add_output_is_nan;
    wire                  add_output_is_inf;

    bfloat16_multiplier u_bf16_mul (
        .num1   (a_reg),
        .num2   (b_reg),
        .result (mul_output_data),
        .is_NaN (mul_output_is_nan),
        .is_infinity (mul_output_is_inf),
        .is_zero ()
    );

    bfloat16_adder u_bf16_add (
        .num1   (mul_result_reg),
        .num2   (local_accumulator_reg),
        .result (add_output_data),
        .is_NaN (add_output_is_nan),
        .is_infinity (add_output_is_inf),
        .is_zero ()
    );

    assign a_valid_out = a_valid_reg;
    assign b_valid_out = b_valid_reg;
    assign a_data_out = a_reg;
    assign b_data_out = b_reg;

    // Calculate the next value of performed_mac_count combinatorially
    // This will be used for the completion check and for updating performed_mac_count register.
    // It increments only if a valid multiplication result is being accumulated and target not yet reached.
    assign next_performed_mac_count_w = (!pe_calculation_done_latch && mul_valid_reg && (performed_mac_count < MAC_COUNT_TARGET)) ?
                                        (performed_mac_count + 1) :
                                        performed_mac_count;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            a_reg                   <= 0;
            b_reg                   <= 0;
            a_valid_reg             <= 1'b0;
            b_valid_reg             <= 1'b0;
            local_accumulator_reg   <= 0;
            mul_result_reg          <= 0;
            mul_valid_reg           <= 1'b0;
            acc_is_nan_reg          <= 1'b0;
            acc_is_infinity_reg     <= 1'b0;
            acc_sign_if_inf_reg     <= 1'b0;
            performed_mac_count     <= 0;
            result_valid_reg        <= 1'b0;
            pe_calculation_done_latch <= 1'b0;
        end else begin
            result_valid_reg <= 1'b0; // Default to low

            if (enable) begin
                a_reg <= a_data_in;
                b_reg <= b_data_in;
                a_valid_reg <= a_valid_in;
                b_valid_reg <= b_valid_in;
            end

            if (clear_accumulator) begin
`ifdef ENABLE_PE_DEBUG_DISPLAY
                if ( (PE_ROW_ID == 0 && (PE_COL_ID == 0 || PE_COL_ID == 1 || PE_COL_ID == 2 || PE_COL_ID == 3)) ||
                     (PE_ROW_ID == (MAC_COUNT_TARGET-1) && PE_COL_ID == (MAC_COUNT_TARGET-1)) ) begin
                    $display("PE_DBG[%0d][%0d] @%0t: CLEAR_ACC. Acc/mul/flags/MAC_count reset. DoneLatch reset. (MAC_TGT=%0d)",
                             PE_ROW_ID, PE_COL_ID, $time, MAC_COUNT_TARGET);
                end
`endif
                local_accumulator_reg   <= 0;
                mul_result_reg          <= 0;
                mul_valid_reg           <= 1'b0;
                acc_is_nan_reg          <= 1'b0;
                acc_is_infinity_reg     <= 1'b0;
                acc_sign_if_inf_reg     <= 1'b0;
                performed_mac_count     <= 0;
                pe_calculation_done_latch <= 1'b0;
            end else if (enable) begin
                // Stage 1: Latch multiplication result and its validity
                // This happens based on a_valid_reg and b_valid_reg from the *current* cycle start,
                // which were latched from a_valid_in and b_valid_in in the *previous* cycle.
                if (a_valid_reg && b_valid_reg) begin
                    mul_result_reg <= mul_output_data; // mul_output_data is combinational from a_reg, b_reg
                    mul_valid_reg  <= 1'b1;
                end else begin
                    mul_result_reg <= 0; 
                    mul_valid_reg  <= 1'b0;
                end

                // Stage 2: Accumulation and counter update
                if (!pe_calculation_done_latch) begin
                    if (mul_valid_reg) begin // If mul_result_reg (from prev cycle's mul) is valid
                        // Update accumulator
                        if (add_output_is_nan) begin
                            local_accumulator_reg <= add_output_data;
                            acc_is_nan_reg        <= 1'b1;
                            acc_is_infinity_reg   <= 1'b0;
                        end else if (add_output_is_inf) begin
                            local_accumulator_reg <= add_output_data;
                            acc_is_nan_reg        <= 1'b0;
                            acc_is_infinity_reg   <= 1'b1;
                            acc_sign_if_inf_reg   <= add_output_data[DATA_WIDTH-1];
                        end else begin
                            local_accumulator_reg <= add_output_data;
                            acc_is_nan_reg        <= 1'b0;
                            acc_is_infinity_reg   <= 1'b0;
                        end
                        
                        // Update the MAC counter using the pre-calculated next value
                        performed_mac_count <= next_performed_mac_count_w;
`ifdef ENABLE_PE_DEBUG_DISPLAY
                        if ( (PE_ROW_ID == 0 && (PE_COL_ID == 0 || PE_COL_ID == 1 || PE_COL_ID == 2 || PE_COL_ID == 3)) ||
                             (PE_ROW_ID == (MAC_COUNT_TARGET-1) && PE_COL_ID == (MAC_COUNT_TARGET-1)) ) begin
                            $display("PE_DBG_ACCUM[%0d][%0d] @%0t: En=%b DoneLatch=%b| MACsDone(cur)=%0d, MACsDone(next_calc)=%0d/%0d | a_R=%h(v%b) b_R=%h(v%b) | mul_R(old)=%h(v%b) acc_R(old)=%h | mul_out(new_mulR)=%h add_out(new_acc)=%h",
                                     PE_ROW_ID, PE_COL_ID, $time, enable, pe_calculation_done_latch,
                                     performed_mac_count, next_performed_mac_count_w, MAC_COUNT_TARGET, // Use performed_mac_count for "cur"
                                     a_reg, a_valid_reg, b_reg, b_valid_reg,
                                     mul_result_reg, mul_valid_reg, local_accumulator_reg,
                                     mul_output_data, add_output_data );
                        end
`endif
                    end // end if (mul_valid_reg) for accumulation

                    // Check for completion:
                    // Use mul_valid_reg (ensuring this cycle's accumulation was based on a valid product)
                    // Use performed_mac_count (value at start of this cycle) < MAC_COUNT_TARGET (ensures we only trigger once)
                    // Use next_performed_mac_count_w == MAC_COUNT_TARGET (ensures count *will be* target at end of this cycle)
                    if (mul_valid_reg && (performed_mac_count < MAC_COUNT_TARGET) && (next_performed_mac_count_w == MAC_COUNT_TARGET)) begin
                        result_valid_reg <= 1'b1;
                        pe_calculation_done_latch <= 1'b1;
`ifdef ENABLE_PE_DEBUG_DISPLAY
                        if ( (PE_ROW_ID == 0 && (PE_COL_ID == 0 || PE_COL_ID == 1 || PE_COL_ID == 2 || PE_COL_ID == 3)) ||
                             (PE_ROW_ID == (MAC_COUNT_TARGET-1) && PE_COL_ID == (MAC_COUNT_TARGET-1)) ) begin
                             $display("PE_DBG_VALID[%0d][%0d] @%0t: >>> MAC_COUNT_TARGET (%0d) Reached. DoneLatch_SET. AccVal NOW FROZEN at 0x%h <<<",
                                  PE_ROW_ID, PE_COL_ID, $time, next_performed_mac_count_w,
                                  add_output_data );
                        end
`endif
                    end
                end else begin // pe_calculation_done_latch is 1
`ifdef ENABLE_PE_DEBUG_DISPLAY
                    if ( (PE_ROW_ID == 0 && (PE_COL_ID == 0 || PE_COL_ID == 1 || PE_COL_ID == 2 || PE_COL_ID == 3)) ||
                         (PE_ROW_ID == (MAC_COUNT_TARGET-1) && PE_COL_ID == (MAC_COUNT_TARGET-1)) ) begin
                        $display("PE_DBG_PAUSED_ACC_FROZEN[%0d][%0d] @%0t: DoneLatch=%b| MACsDone=%0d | a_R=%h(v%b) b_R=%h(v%b) | mul_R(FROZEN_INPUT)=%h(v%b) acc_R(FROZEN)=0x%h | mul_out(new_mulR)=%h add_out(hypo)=%h",
                                 PE_ROW_ID, PE_COL_ID, $time, pe_calculation_done_latch,
                                 performed_mac_count,
                                 a_reg, a_valid_reg, b_reg, b_valid_reg,
                                 mul_result_reg, mul_valid_reg, local_accumulator_reg,
                                 mul_output_data, add_output_data );
                    end
`endif
                end // end if (!pe_calculation_done_latch) else
            end // end else if (enable)
        end // end else (!rst_n)
    end // end always

    assign result_out = local_accumulator_reg;
    assign result_valid = result_valid_reg;
    assign pe_is_nan = acc_is_nan_reg;
    assign pe_is_infinity = acc_is_infinity_reg;

endmodule