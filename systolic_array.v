//
// Filename: systolic_array.v
// Description: Final, corrected version of the pure-computation systolic array.
//              It now includes an internal output controller to stream results
//              autonomously after computation is done, resolving the handshake deadlock.
//
`timescale 1ns / 1ps

module systolic_array #(
    parameter SIZE = 16,
    parameter INPUT_DATA_WIDTH = 8,
    parameter PE_ACCUM_DATA_WIDTH = 32
)(
    input wire clk,
    input wire rst_n,
    input wire clear_all_pe_accumulators,
    input wire conditionally_clear_pe_sums_level,
    input wire activate_pe_computation,
    input wire array_data_valid_in,
    input wire [SIZE*INPUT_DATA_WIDTH-1:0] array_a_in,
    input wire [SIZE*INPUT_DATA_WIDTH-1:0] array_b_in,

    output wire array_a_data_valid_out,
    output wire [SIZE*INPUT_DATA_WIDTH-1:0] array_a_out,
    output wire array_b_data_valid_out,
    output wire [SIZE*INPUT_DATA_WIDTH-1:0] array_b_out,

    output reg signed [SIZE*PE_ACCUM_DATA_WIDTH-1:0] tile_row_result_out,
    output reg                                tile_row_result_valid,
    output reg [$clog2(SIZE)-1:0]           sa_partial_sum_row_idx,

    output wire                               tile_all_pes_done_one_pass,
    input wire start_new_systolic_pass
);

    // --- Internal Wires (Unchanged) ---
    wire signed [INPUT_DATA_WIDTH-1:0]   a_data_wires [SIZE-1:0][SIZE:0];
    wire signed [INPUT_DATA_WIDTH-1:0]   b_data_wires [SIZE:0][SIZE-1:0];
    wire                                 a_valid_wires [SIZE-1:0][SIZE:0];
    wire                                 b_valid_wires [SIZE:0][SIZE-1:0];
    wire signed [PE_ACCUM_DATA_WIDTH-1:0] pe_result_out_internal [SIZE-1:0][SIZE-1:0];
    wire                                  pe_result_valid_internal [SIZE-1:0][SIZE-1:0];
    
    // --- PE Done Flags ---
    reg pe_done_flags [SIZE-1:0][SIZE-1:0];
    // --- MODIFIED: Changed from 'wire' to 'reg' as it's assigned in an always block ---
    reg all_pes_in_tile_done_reduction;
    
    genvar r_gen, c_gen;
    integer i_col_local; 

    //===============================================================
    //== [NEW] Internal Output Streaming Controller
    //===============================================================
    localparam FSM_OUT_IDLE      = 0;
    localparam FSM_OUT_STREAMING = 1;
    reg output_fsm_state;
    reg [$clog2(SIZE)-1:0] output_row_counter;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            output_fsm_state <= FSM_OUT_IDLE;
            output_row_counter <= 0;
            tile_row_result_valid <= 1'b0;
        end else if (start_new_systolic_pass) begin
            output_fsm_state <= FSM_OUT_IDLE;
            output_row_counter <= 0;
            tile_row_result_valid <= 1'b0;
        end else begin
            case(output_fsm_state)
                FSM_OUT_IDLE: begin
                    tile_row_result_valid <= 1'b0;
                    if (all_pes_in_tile_done_reduction) begin
                        output_fsm_state <= FSM_OUT_STREAMING;
                        output_row_counter <= 0;
                    end
                end
                FSM_OUT_STREAMING: begin
                    tile_row_result_valid <= 1'b1;
                    if (output_row_counter == SIZE - 1) begin
                        output_fsm_state <= FSM_OUT_IDLE;
                        tile_row_result_valid <= 1'b0;
                    end else begin
                        output_row_counter <= output_row_counter + 1;
                    end
                end
            endcase
        end
    end
    
    always @(*) begin
        sa_partial_sum_row_idx = output_row_counter;
        for (i_col_local = 0; i_col_local < SIZE; i_col_local = i_col_local + 1) begin
            tile_row_result_out[i_col_local*PE_ACCUM_DATA_WIDTH +: PE_ACCUM_DATA_WIDTH] = pe_result_out_internal[output_row_counter][i_col_local];
        end
    end
    
    //===============================================================
    //== Unchanged Logic
    //===============================================================
    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : connect_a_to_pe_boundary
            assign a_data_wires[r_gen][0] = array_a_in[r_gen*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
            assign a_valid_wires[r_gen][0] = array_data_valid_in;
        end
        for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : connect_b_to_pe_boundary
            assign b_data_wires[0][c_gen] = array_b_in[c_gen*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH];
            assign b_valid_wires[0][c_gen] = array_data_valid_in;
        end
    endgenerate

    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : pe_row
            for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : pe_col
                pe #(.INPUT_DATA_WIDTH(INPUT_DATA_WIDTH), .ACCUM_DATA_WIDTH(PE_ACCUM_DATA_WIDTH), .MAC_COUNT_TARGET(SIZE)) 
                u_pe_inst (.clk(clk), .rst_n(rst_n), .enable(activate_pe_computation), .clear_accumulator(clear_all_pe_accumulators), .conditionally_clear_sum(conditionally_clear_pe_sums_level), .a_valid_in(a_valid_wires[r_gen][c_gen]), .a_data_in(a_data_wires[r_gen][c_gen]), .a_valid_out(a_valid_wires[r_gen][c_gen+1]), .a_data_out(a_data_wires[r_gen][c_gen+1]), .b_valid_in(b_valid_wires[r_gen][c_gen]), .b_data_in(b_data_wires[r_gen][c_gen]), .b_valid_out(b_valid_wires[r_gen+1][c_gen]), .b_data_out(b_data_wires[r_gen+1][c_gen]), .result_out(pe_result_out_internal[r_gen][c_gen]), .result_valid(pe_result_valid_internal[r_gen][c_gen]), .start_new_systolic_pass(start_new_systolic_pass));
            end
        end
    endgenerate

    assign array_a_data_valid_out = (SIZE > 0) ? a_valid_wires[0][SIZE] : 1'b0;
    assign array_b_data_valid_out = (SIZE > 0) ? b_valid_wires[SIZE][0] : 1'b0;
    generate
        for (r_gen = 0; r_gen < SIZE; r_gen = r_gen + 1) begin : connect_a_output_stream
            assign array_a_out[r_gen*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] = a_data_wires[r_gen][SIZE];
        end
        for (c_gen = 0; c_gen < SIZE; c_gen = c_gen + 1) begin : connect_b_output_stream
            assign array_b_out[c_gen*INPUT_DATA_WIDTH +: INPUT_DATA_WIDTH] = b_data_wires[SIZE][c_gen];
        end
    endgenerate

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (integer r = 0; r < SIZE; r = r + 1) begin
                for (integer c = 0; c < SIZE; c = c + 1) begin
                    pe_done_flags[r][c] <= 1'b0;
                end
            end
        end else if (start_new_systolic_pass) begin
            for (integer r = 0; r < SIZE; r = r + 1) begin
                for (integer c = 0; c < SIZE; c = c + 1) begin
                    pe_done_flags[r][c] <= 1'b0;
                end
            end
        end else if (activate_pe_computation) begin
            for (integer r = 0; r < SIZE; r = r + 1) begin
                for (integer c = 0; c < SIZE; c = c + 1) begin
                    if (pe_result_valid_internal[r][c]) begin
                        pe_done_flags[r][c] <= 1'b1;
                    end
                end
            end
        end
    end

    always@(*) begin
        all_pes_in_tile_done_reduction = 1'b1;
        if (SIZE > 0) begin
            for (integer r = 0; r < SIZE; r = r + 1) begin
                for (integer c = 0; c < SIZE; c = c + 1) begin
                    if (!pe_done_flags[r][c]) begin
                        all_pes_in_tile_done_reduction = 1'b0;
                    end
                end
            end
        end
    end
    assign tile_all_pes_done_one_pass = all_pes_in_tile_done_reduction;
endmodule