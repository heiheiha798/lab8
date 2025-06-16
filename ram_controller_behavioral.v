// ram_controller.v (或者 ram_controller_behavioral.v - 确保文件名一致)
// Standard Verilog-2001 compatible version
module ram_controller_behavioral #(
    parameter LOGIC_ADDR_WIDTH = 18,
    parameter DATA_WIDTH       = 64,
    parameter READ_LATENCY_CYCLES = 2
) (
    input wire                          clk,
    input wire                          rst_n,
    input wire [LOGIC_ADDR_WIDTH-1:0]   logic_addr_i,
    input wire [DATA_WIDTH-1:0]         write_data_i,
    input wire                          cs_i,
    input wire                          we_i,       // 1 for write, 0 for read
    output reg [DATA_WIDTH-1:0]        read_data_o,
    output reg                         ready_o
);

    localparam STATE_IDLE = 1'b0;
    localparam STATE_BUSY = 1'b1;

    reg  current_state_rc, next_state_rc;

    reg [$clog2(READ_LATENCY_CYCLES+1)-1:0] busy_counter_rc;
    reg [$clog2(READ_LATENCY_CYCLES+1)-1:0] busy_counter_next_rc;

    reg [DATA_WIDTH-1:0] data_pipe [0:READ_LATENCY_CYCLES-1];
    reg                  we_pipe   [0:READ_LATENCY_CYCLES-1];

    reg [DATA_WIDTH-1:0] pseudo_ram [0:(1<<LOGIC_ADDR_WIDTH)-1];
    integer i;

    initial begin
        // Initialize all to a known non-zero pattern first for easier debug if readmemh fails
        for (i=0; i<(1<<LOGIC_ADDR_WIDTH); i=i+1) begin
            pseudo_ram[i] = {DATA_WIDTH{1'hx}}; // Initialize to all 'x'
        end
        // $display("[%0t RC_BEHAV] Initializing pseudo_ram with $readmemh from input_mem.csv...", $time);
        $readmemh("input_mem.csv", pseudo_ram); // Path is now direct
        // $display("[%0t RC_BEHAV] $readmemh from input_mem.csv attempt finished.", $time);

        // Verification print within ram_controller
        // $display("[%0t RC_BEHAV_VERIFY] After $readmemh in ram_controller:", $time);
        // for (i=0; i<4 && i<(1<<LOGIC_ADDR_WIDTH); i=i+1) begin
        //      $display("    RC pseudo_ram[0x%h] = %h", i, pseudo_ram[i]);
        // end
        // Example: Check where B might start for a 16x16 test (logical word offset 32)
        // if (LOGIC_ADDR_WIDTH >= 6) begin // Ensure address 32 is valid
        //     for (i=32; i<32+4 && i<(1<<LOGIC_ADDR_WIDTH); i=i+1) begin
        //          $display("    RC pseudo_ram[0x%h] = %h (expected start of B for 16x16)", i, pseudo_ram[i]);
        //     end
        // end
    end

    // Sequential logic for state, counter, and pipeline
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state_rc <= STATE_IDLE;
            busy_counter_rc  <= 0;
            ready_o          <= 1'b0;
            read_data_o      <= {DATA_WIDTH{1'b0}};
            for (i=0; i<READ_LATENCY_CYCLES; i=i+1) begin
                data_pipe[i] <= {DATA_WIDTH{1'b0}};
                we_pipe[i]   <= 1'b0;
            end
        end else begin
            current_state_rc <= next_state_rc;
            busy_counter_rc  <= busy_counter_next_rc;
            ready_o          <= 1'b0; // Default to 0, assert for one cycle

            // Shift the pipeline
            // This logic assumes a new operation (if any) loads into data_pipe[0]
            // and existing contents shift up.
            if (current_state_rc == STATE_BUSY || (current_state_rc == STATE_IDLE && cs_i)) begin
                for (i = READ_LATENCY_CYCLES-1; i > 0; i = i - 1) begin
                    data_pipe[i] <= data_pipe[i-1];
                    we_pipe[i]   <= we_pipe[i-1];
                end
                // Load first stage of pipeline if a new operation is starting now
                if ( (current_state_rc == STATE_IDLE && cs_i) ||                            // Starting from IDLE
                     (current_state_rc == STATE_BUSY && busy_counter_rc == 1 && cs_i) ) begin // Back-to-back new op
                    if (we_i) begin // Write
                        data_pipe[0] <= {DATA_WIDTH{1'bx}}; // Data not relevant for read_data_o
                        we_pipe[0]   <= 1'b1;
                    end else begin // Read
                        data_pipe[0] <= pseudo_ram[logic_addr_i]; // Read from RAM
                        we_pipe[0]   <= 1'b0;
                    end
                end else if (current_state_rc == STATE_BUSY) begin // Busy, not finishing and no new op this exact cycle to load into pipe[0]
                    // data_pipe[0] keeps its value from previous shift if no new load. Or set to 'x'.
                    // This part can be tricky with back-to-back; ensure pipe[0] gets new data correctly.
                end
            end

            // Assert ready_o when the operation at the end of the pipeline is complete
            if (current_state_rc == STATE_BUSY && busy_counter_rc == 1'b1) begin
                ready_o <= 1'b1;
                if (!we_pipe[READ_LATENCY_CYCLES-1]) begin
                    read_data_o <= data_pipe[READ_LATENCY_CYCLES-1];
                end else begin
                    read_data_o <= {DATA_WIDTH{1'bx}};
                end
            end

            // --- STROBE FOR RAM_CONTROLLER ---
            // if (cs_i || current_state_rc == STATE_BUSY || next_state_rc == STATE_BUSY ) begin
            //     if (cs_i && !we_i) begin // If it's a read request *this cycle*
            //         $strobe("@%0t [RC_STATE] Inputs(CS:%b WE:%b Addr:0x%h DataFromPseudoRAM:0x%h) | CurSt:%s NextSt:%s | BusyCnt:%d NextBusyCnt:%d | Ready_Out_Reg:%b ReadData_Out_Reg:0x%h | Pipe[0]:%h (WE:%b) Pipe[1]:%h (WE:%b)",
            //             $time, cs_i, we_i, logic_addr_i, pseudo_ram[logic_addr_i], // Print data being read
            //             (current_state_rc==STATE_IDLE?"IDLE":"BUSY"), (next_state_rc==STATE_IDLE?"IDLE":"BUSY"),
            //             busy_counter_rc, busy_counter_next_rc,
            //             ready_o,
            //             read_data_o,
            //             (READ_LATENCY_CYCLES > 0) ? data_pipe[0] : {DATA_WIDTH{1'bx}},
            //             (READ_LATENCY_CYCLES > 0) ? we_pipe[0]   : 1'bx,
            //             (READ_LATENCY_CYCLES > 1) ? data_pipe[1] : {DATA_WIDTH{1'bx}},
            //             (READ_LATENCY_CYCLES > 1) ? we_pipe[1]   : 1'bx
            //         );
            //     end else begin // Not a read request this cycle, or a write
            //         $strobe("@%0t [RC_STATE] Inputs(CS:%b WE:%b Addr:0x%h                 ) | CurSt:%s NextSt:%s | BusyCnt:%d NextBusyCnt:%d | Ready_Out_Reg:%b ReadData_Out_Reg:0x%h | Pipe[0]:%h (WE:%b) Pipe[1]:%h (WE:%b)",
            //             $time, cs_i, we_i, logic_addr_i,
            //             (current_state_rc==STATE_IDLE?"IDLE":"BUSY"), (next_state_rc==STATE_IDLE?"IDLE":"BUSY"),
            //             busy_counter_rc, busy_counter_next_rc,
            //             ready_o,
            //             read_data_o,
            //             (READ_LATENCY_CYCLES > 0) ? data_pipe[0] : {DATA_WIDTH{1'bx}},
            //             (READ_LATENCY_CYCLES > 0) ? we_pipe[0]   : 1'bx,
            //             (READ_LATENCY_CYCLES > 1) ? data_pipe[1] : {DATA_WIDTH{1'bx}},
            //             (READ_LATENCY_CYCLES > 1) ? we_pipe[1]   : 1'bx
            //         );
            //     end
            // end
            // --- END RC STROBE ---
        end
    end

    // Combinational logic for next state and counter
    always @(*) begin
        next_state_rc = current_state_rc;
        busy_counter_next_rc = busy_counter_rc;

        case(current_state_rc)
            STATE_IDLE: begin
                if (cs_i) begin
                    next_state_rc = STATE_BUSY;
                    busy_counter_next_rc = READ_LATENCY_CYCLES;
                    if (we_i) begin
                        pseudo_ram[logic_addr_i] = write_data_i;
                    end
                end
            end
            STATE_BUSY: begin
                if (busy_counter_rc == 1'b1) begin
                    if (cs_i) begin
                        next_state_rc = STATE_BUSY;
                        busy_counter_next_rc = READ_LATENCY_CYCLES;
                        if (we_i) begin
                            pseudo_ram[logic_addr_i] = write_data_i;
                        end
                    end else begin
                        next_state_rc = STATE_IDLE;
                        busy_counter_next_rc = 0;
                    end
                end else if (busy_counter_rc > 1'b1) begin
                    busy_counter_next_rc = busy_counter_rc - 1;
                    next_state_rc = STATE_BUSY;
                end else begin // busy_counter_rc is 0
                    next_state_rc = STATE_IDLE;
                    if(cs_i) begin // New request while supposedly idle (should have caught by cs_i in IDLE)
                        next_state_rc = STATE_BUSY;
                        busy_counter_next_rc = READ_LATENCY_CYCLES;
                        if(we_i) begin
                            pseudo_ram[logic_addr_i] = write_data_i;
                        end
                    end
                end
            end
        endcase
    end
endmodule