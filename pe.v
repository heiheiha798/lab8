// pe.v
`timescale 1ns / 1ps

module pe #(
    parameter INPUT_DATA_WIDTH = 8,
    parameter ACCUM_DATA_WIDTH = 32,
    parameter MAC_COUNT_TARGET = 16,
    parameter integer PE_ROW_ID = -1,
    parameter integer PE_COL_ID = -1
)(
    input wire                          clk,
    input wire                          rst_n,
    input wire                          enable,
    input wire                          clear_accumulator,
    input wire                          a_valid_in,
    input wire signed [INPUT_DATA_WIDTH-1:0] a_data_in,
    output wire                         a_valid_out,
    output wire signed [INPUT_DATA_WIDTH-1:0] a_data_out,
    input wire                          b_valid_in,
    input wire signed [INPUT_DATA_WIDTH-1:0] b_data_in,
    output wire                         b_valid_out,
    output wire signed [INPUT_DATA_WIDTH-1:0] b_data_out,
    output wire signed [ACCUM_DATA_WIDTH-1:0] result_out,
    output wire                         result_valid,
    input wire                          conditionally_clear_sum
);
    reg signed [INPUT_DATA_WIDTH-1:0] a_reg; // Holds a_data_in from PREVIOUS cycle
    reg signed [INPUT_DATA_WIDTH-1:0] b_reg; // Holds b_data_in from PREVIOUS cycle
    reg                               a_valid_for_output_reg; // For propagating valid signal
    reg                               b_valid_for_output_reg; // For propagating valid signal
    reg                               inputs_that_produced_a_b_regs_were_valid_reg;

    localparam MULT_RESULT_WIDTH = INPUT_DATA_WIDTH * 2;
    reg signed [MULT_RESULT_WIDTH-1:0] mul_result_reg; // Holds product of a_reg, b_reg (i.e., product of PREVIOUS cycle's inputs)
    reg                                mul_valid_reg;  // Indicates if data in mul_result_reg is valid

    reg signed [ACCUM_DATA_WIDTH-1:0] local_accumulator_reg;
    reg [$clog2(MAC_COUNT_TARGET+1)-1:0] performed_mac_count;
    wire [$clog2(MAC_COUNT_TARGET+1)-1:0] next_performed_mac_count_w;
    reg result_valid_reg;
    reg pe_calculation_done_latch;

    wire signed [MULT_RESULT_WIDTH-1:0] mul_output_data; // Combinational: a_reg * b_reg
    wire signed [ACCUM_DATA_WIDTH-1:0] add_output_data;

    assign mul_output_data = a_reg * b_reg;
    assign add_output_data = mul_result_reg + local_accumulator_reg;

    assign a_valid_out = a_valid_for_output_reg;
    assign b_valid_out = b_valid_for_output_reg;
    assign a_data_out  = a_reg; // a_reg is the latched input, so output is delayed by one cycle
    assign b_data_out  = b_reg; // b_reg is the latched input

    assign next_performed_mac_count_w = (!pe_calculation_done_latch && mul_valid_reg && (performed_mac_count < MAC_COUNT_TARGET)) ?
                                        (performed_mac_count + 1) :
                                        performed_mac_count;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            a_reg                   <= '0;
            b_reg                   <= '0;
            a_valid_for_output_reg  <= 1'b0;
            b_valid_for_output_reg  <= 1'b0;
            inputs_that_produced_a_b_regs_were_valid_reg <= 1'b0;
            local_accumulator_reg   <= '0;
            mul_result_reg          <= '0;
            mul_valid_reg           <= 1'b0;
            performed_mac_count     <= 0;
            result_valid_reg        <= 1'b0;
            pe_calculation_done_latch <= 1'b0;
        end else begin
            result_valid_reg <= 1'b0;

            if (clear_accumulator) begin
                mul_valid_reg           <= 1'b0;
                performed_mac_count     <= 0;
                pe_calculation_done_latch <= 1'b0;
                if (conditionally_clear_sum) begin
                    local_accumulator_reg   <= '0;
                end
            end else if (enable) begin
                a_reg <= a_data_in;
                b_reg <= b_data_in;
                inputs_that_produced_a_b_regs_were_valid_reg <= a_valid_in && b_valid_in;
                a_valid_for_output_reg <= a_valid_in;
                b_valid_for_output_reg <= b_valid_in;
                mul_result_reg <= mul_output_data; // Product of a_reg, b_reg (inputs from previous cycle)
                mul_valid_reg  <= inputs_that_produced_a_b_regs_were_valid_reg; // Validity of those inputs
                if (!pe_calculation_done_latch) begin
                    if (mul_valid_reg) begin // If product from previous cycle (now in mul_result_reg) is valid
                        local_accumulator_reg <= add_output_data; // add_output_data uses current mul_result_reg & local_accumulator_reg
                        performed_mac_count <= next_performed_mac_count_w;
                    end

                    if (mul_valid_reg && (performed_mac_count < MAC_COUNT_TARGET) && (next_performed_mac_count_w == MAC_COUNT_TARGET)) begin
                        result_valid_reg <= 1'b1;
                        pe_calculation_done_latch <= 1'b1;
                    end
                end

                // --- STROBE FOR PE ---
                // if (enable && ( (PE_ROW_ID == 0 && PE_COL_ID == 0) || (PE_ROW_ID == 15 && PE_COL_ID == 0) ) /* && (relevant_activity_condition) */ ) begin
                //      // The strobe needs to print values consistent with this new pipelining
                //      // a_r, b_r are inputs from previous cycle
                //      // mul_output_data is product of a_r, b_r
                //      // inputs_that_produced_a_b_regs_were_valid_reg is validity of a_r, b_r
                //      // mul_result_reg (AccIn) is product from 2 cycles ago
                //      // mul_valid_reg (MulVldRg) is validity from 2 cycles ago
                //     $strobe("@%0t [PE(%0d,%0d)] En:%b|Ain:%d(v%b) Bin:%d(v%b)|a_r:%d b_r:%d(valid_for_them:%b)|MulOut:%d|AccProduct:%d(valid:%b)|AccValue:%d|MACs:%d done:%b resVldWillBe:%b",
                //         $time, PE_ROW_ID, PE_COL_ID, enable,
                //         a_data_in, a_valid_in, b_data_in, b_valid_in, // Current port inputs
                //         a_reg, b_reg, inputs_that_produced_a_b_regs_were_valid_reg, // Values that produced current mul_output_data
                //         mul_output_data,            // Product of a_reg, b_reg
                //         mul_result_reg,             // Product to be accumulated this cycle (from prev. mul_output_data)
                //         mul_valid_reg,              // Validity of mul_result_reg
                //         local_accumulator_reg,      // Accumulator before this cycle's add
                //         performed_mac_count,
                //         pe_calculation_done_latch,
                //         (mul_valid_reg && (performed_mac_count < MAC_COUNT_TARGET) && (next_performed_mac_count_w == MAC_COUNT_TARGET))
                //     );
                // end
            end
        end
    end

    assign result_out = local_accumulator_reg;
    assign result_valid = result_valid_reg;

endmodule