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
    output wire                     pe_is_infinity,
    input wire                      conditionally_clear_sum // 新增输入 (电平信号，指示是否要清除累加器中的和)
);
    reg [DATA_WIDTH-1:0] a_reg;
    reg [DATA_WIDTH-1:0] b_reg;
    reg                      a_valid_reg; // Latched a_valid_in, used for propagating and for current cycle's MAC decision
    reg                      b_valid_reg; // Latched b_valid_in, used for propagating and for current cycle's MAC decision

    reg [DATA_WIDTH-1:0] local_accumulator_reg;
    reg [DATA_WIDTH-1:0] mul_result_reg;        // Holds the product of a_reg and b_reg from the *combinational* multiplier
    reg                      mul_valid_reg;       // Indicates if mul_result_reg holds a valid product *from the previous cycle's inputs*

    reg acc_is_nan_reg;
    reg acc_is_infinity_reg;
    reg acc_sign_if_inf_reg;

    reg [$clog2(MAC_COUNT_TARGET+1)-1:0] performed_mac_count;

    // This wire calculates the next MAC count based on current cycle's mul_valid_reg (which reflects previous cycle's data validity)
    // and current performed_mac_count.
    wire [$clog2(MAC_COUNT_TARGET+1)-1:0] next_performed_mac_count_w;

    reg result_valid_reg;           // Pulsed output, high for one cycle when MAC_COUNT_TARGET is reached
    reg pe_calculation_done_latch;  // Latches high when one full pass (MAC_COUNT_TARGET ops) is done

    // Combinational outputs from multiplier and adder
    wire [DATA_WIDTH-1:0] mul_output_data;    // Output of a_reg * b_reg
    wire                  mul_output_is_nan;
    wire                  mul_output_is_inf;

    wire [DATA_WIDTH-1:0] add_output_data;    // Output of mul_result_reg + local_accumulator_reg
    wire                  add_output_is_nan;
    wire                  add_output_is_inf;

    // This signal is just for strobe, not used in logic.
    // It indicates if a "full clear" (clear_accumulator && conditionally_clear_sum) is happening.
    wire k_is_0_related_pass_for_strobe;
    assign k_is_0_related_pass_for_strobe = (conditionally_clear_sum && clear_accumulator);


    bfloat16_multiplier u_bf16_mul (
        .num1   (a_reg), // Uses a_reg (latched a_data_in from *current* cycle start)
        .num2   (b_reg), // Uses b_reg (latched b_data_in from *current* cycle start)
        .result (mul_output_data),
        .is_NaN (mul_output_is_nan),
        .is_infinity (mul_output_is_inf),
        .is_zero ()
    );

    bfloat16_adder u_bf16_add (
        .num1   (mul_result_reg),      // Uses product from *previous* cycle's a_reg, b_reg
        .num2   (local_accumulator_reg), // Uses accumulator from *previous* cycle
        .result (add_output_data),
        .is_NaN (add_output_is_nan),
        .is_infinity (add_output_is_inf),
        .is_zero ()
    );

    // Propagate inputs to outputs (with one cycle delay due to a_reg/b_reg and a_valid_reg/b_valid_reg)
    assign a_valid_out = a_valid_reg; // a_valid_reg is latched a_valid_in
    assign b_valid_out = b_valid_reg; // b_valid_reg is latched b_valid_in
    assign a_data_out  = a_reg;       // a_reg is latched a_data_in
    assign b_data_out  = b_reg;       // b_reg is latched b_data_in

    // MAC counter update logic:
    // If not already done with this pass, AND a valid multiplication happened in the *previous* cycle (indicated by current mul_valid_reg),
    // AND we haven't reached the target count yet, then increment.
    assign next_performed_mac_count_w = (!pe_calculation_done_latch && mul_valid_reg && (performed_mac_count < MAC_COUNT_TARGET)) ?
                                        (performed_mac_count + 1) :
                                        performed_mac_count;

// --- DEBUG STROBE START ---
    // initial begin
    //     if (PE_ROW_ID < 2 && PE_COL_ID < 2) begin // Only for a few PEs to reduce log size
    //         $strobe("@%0t PE[%d][%d] Instantiated. MAC_COUNT_TARGET=%d, DATA_WIDTH=%d",
    //                 $time, PE_ROW_ID, PE_COL_ID, MAC_COUNT_TARGET, DATA_WIDTH);
    //     end
    // end
// --- DEBUG STROBE END ---

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            a_reg                   <= {DATA_WIDTH{1'b0}};
            b_reg                   <= {DATA_WIDTH{1'b0}};
            a_valid_reg             <= 1'b0; 
            b_valid_reg             <= 1'b0; 
            local_accumulator_reg   <= {DATA_WIDTH{1'b0}};
            mul_result_reg          <= {DATA_WIDTH{1'b0}};
            mul_valid_reg           <= 1'b0; 
            acc_is_nan_reg          <= 1'b0;
            acc_is_infinity_reg     <= 1'b0;
            acc_sign_if_inf_reg     <= 1'b0;
            performed_mac_count     <= 0;
            result_valid_reg        <= 1'b0;
            pe_calculation_done_latch <= 1'b0;
        end else begin
            result_valid_reg <= 1'b0; // Default to 0, pulse high for one cycle

            if (clear_accumulator) begin // This is a signal from SA controller, active for one cycle usually
                // --- DEBUG STROBE START ---
                // if (PE_ROW_ID < 1 && PE_COL_ID < 1) begin // Only for PE(0,0)
                //     $display("@%0t PE[%d][%d] Event:ClearAccumPulse. PE_Enable_In:%b, ClearAccum_In:%b, CondClearSum_In:%b. AccBeforeClearAttempt: %h",
                //             $time, PE_ROW_ID, PE_COL_ID,
                //             enable,                // Actual 'enable' input to PE
                //             clear_accumulator,     // Actual 'clear_accumulator' input to PE
                //             conditionally_clear_sum, // Actual 'conditionally_clear_sum' input to PE
                //             local_accumulator_reg);
                // end
                // --- DEBUG STROBE END ---
                // mul_result_reg          <= {DATA_WIDTH{1'b0}}; // Not strictly needed to clear here if mul_valid_reg is cleared
                mul_valid_reg           <= 1'b0; // No valid multiplication result available after clear
                performed_mac_count     <= 0;
                pe_calculation_done_latch <= 1'b0; // Start a new calculation pass

                if (conditionally_clear_sum) begin // If this is also active, clear the sum itself
                    local_accumulator_reg   <= {DATA_WIDTH{1'b0}};
                    acc_is_nan_reg          <= 1'b0;
                    acc_is_infinity_reg     <= 1'b0;
                    // acc_sign_if_inf_reg doesn't need reset if acc_is_infinity_reg is 0
                end
                // If conditionally_clear_sum is NOT active, local_accumulator_reg RETAINS its value.
                // This is for accumulating results over multiple K-passes.
            end else if (enable) begin
                // --- Latch current inputs for data path (a_reg, b_reg) and for propagating out (a_valid_reg, b_valid_reg) ---
                // These latched values will be used by the combinational multiplier in *this* cycle,
                // and the latched valids (a_valid_reg, b_valid_reg) will determine if a multiplication is valid
                // at the *start* of the *next* cycle for setting mul_valid_reg.
                a_reg <= a_data_in;
                b_reg <= b_data_in;
                a_valid_reg <= a_valid_in; 
                b_valid_reg <= b_valid_in; 

                // --- Multiplication Logic ---
                // Decide if the current a_reg, b_reg (latched from a_data_in, b_data_in at start of this cycle)
                // produced a valid multiplication. This decision is based on a_valid_in and b_valid_in from *this* cycle.
                // mul_valid_reg will be set at the end of *this* cycle, to be used in the *next* cycle's accumulation.
                if (a_valid_in && b_valid_in) begin // Use current inputs' valid signals
                    mul_result_reg <= mul_output_data; // mul_output_data is combinational from current a_reg, b_reg
                    mul_valid_reg  <= 1'b1;            
                end else begin
                    // mul_result_reg <= {DATA_WIDTH{1'b0}}; // Optional: clear if invalid, or just let it be stale
                    mul_valid_reg  <= 1'b0; 
                end

                // --- Accumulation logic ---
                // This happens one cycle *after* the multiplication whose result is in mul_result_reg.
                // The 'mul_valid_reg' in the condition is the value that was set at the *end* of the *previous* cycle,
                // based on *that previous cycle's* a_valid_in and b_valid_in.
                if (!pe_calculation_done_latch) begin // Only accumulate if this pass isn't done
                    if (mul_valid_reg) begin // If a valid product was latched in mul_result_reg in the *previous* cycle
                        // Accumulate: current mul_result_reg (from prev cycle's mult) + current local_accumulator_reg
                        if (add_output_is_nan)      begin local_accumulator_reg <= add_output_data; acc_is_nan_reg <= 1'b1; acc_is_infinity_reg <= 1'b0; end
                        else if (add_output_is_inf) begin local_accumulator_reg <= add_output_data; acc_is_nan_reg <= 1'b0; acc_is_infinity_reg <= 1'b1; acc_sign_if_inf_reg <= add_output_data[DATA_WIDTH-1]; end
                        else                        begin local_accumulator_reg <= add_output_data; acc_is_nan_reg <= 1'b0; acc_is_infinity_reg <= 1'b0; end
                        
                        performed_mac_count <= next_performed_mac_count_w; // Increment MAC counter
                    end 

                    // --- Result Valid and Done Latch Logic ---
                    // Check if the accumulation that just happened (or would have, if mul_valid_reg was high)
                    // makes us reach MAC_COUNT_TARGET.
                    // next_performed_mac_count_w uses the current cycle's mul_valid_reg (from prev cycle's inputs)
                    // and current performed_mac_count.
                    if (mul_valid_reg && (performed_mac_count < MAC_COUNT_TARGET) && (next_performed_mac_count_w == MAC_COUNT_TARGET)) begin
                        result_valid_reg <= 1'b1;          // Pulse high for one cycle
                        pe_calculation_done_latch <= 1'b1; // Latch that this pass is done
                        // --- DEBUG STROBE START ---
                        // if (PE_ROW_ID < 1 && PE_COL_ID < 1) begin // PE(0,0)
                        //     $strobe("@%0t PE[%d][%d] RESULT_VALID ASSERTED! Accumulator: %h, Final MAC_Count: %d (Target: %d). pe_calc_done_latch set.",
                        //            $time, PE_ROW_ID, PE_COL_ID, local_accumulator_reg, next_performed_mac_count_w, MAC_COUNT_TARGET);
                        // end
                        // --- DEBUG STROBE END ---
                    end
                end // end if (!pe_calculation_done_latch)
            end // end if (enable)

            // --- DEBUG STROBE START ---
            // More general per-cycle strobe for PE(0,0) when enabled
            // if (enable && PE_ROW_ID < 1 && PE_COL_ID < 1) begin
            //     $strobe("@%0t PE[%d][%d] CycleEnd | En:%b ClrAcc:%b CondClr:%b | a_in:%h(%b) b_in:%h(%b) | a_reg:%h b_reg:%h | a_v_reg:%b b_v_reg:%b | mul_v_reg_next:%b mul_res_next:%h | acc:%h MACs:%d->%d done_latch:%b | res_v_next:%b",
            //         $time, PE_ROW_ID, PE_COL_ID, enable, clear_accumulator, conditionally_clear_sum,
            //         a_data_in, a_valid_in, b_data_in, b_valid_in,             // Inputs this cycle
            //         a_reg, b_reg,                                             // Registers latched at start of this cycle
            //         a_valid_reg, b_valid_reg,                                 // Valid signals latched at start of this cycle
            //         (a_valid_in && b_valid_in), mul_output_data,              // What mul_valid_reg and mul_result_reg will be NEXT cycle
            //         local_accumulator_reg, performed_mac_count, next_performed_mac_count_w, pe_calculation_done_latch, // Accumulator and MAC count state
            //         (mul_valid_reg && (performed_mac_count < MAC_COUNT_TARGET) && (next_performed_mac_count_w == MAC_COUNT_TARGET)) // What result_valid_reg will be NEXT cycle
            //     );
            // end
            // --- DEBUG STROBE END ---

        end // end else if (!rst_n)
    end // end always

    assign result_out = local_accumulator_reg;
    assign result_valid = result_valid_reg; 
    assign pe_is_nan = acc_is_nan_reg;
    assign pe_is_infinity = acc_is_infinity_reg;

endmodule