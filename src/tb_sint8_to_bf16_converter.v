`timescale 1ns / 1ps

module tb_sint8_to_bf16_converter;

    // Parameters
    localparam DATA_WIDTH_SINT8 = 8;
    localparam DATA_WIDTH_BF16 = 16;
    localparam CLK_PERIOD = 10;

    // Testbench Signals
    reg  signed [DATA_WIDTH_SINT8-1:0] test_sint8_in;
    wire        [DATA_WIDTH_BF16-1:0] test_bf16_out;
    reg                               clk;
    reg                               rst; // Reset signal

    // Instantiate the Unit Under Test (UUT)
    sint8_to_bf16_converter uut (
        .sint8_in(test_sint8_in),
        .bf16_out(test_bf16_out)
    );

    // Clock generation
    always #(CLK_PERIOD/2) clk = ~clk;

    // Helper task for applying input and displaying output
    task apply_and_display;
        input signed [DATA_WIDTH_SINT8-1:0] val_in;
        begin
            test_sint8_in = val_in;
            #(CLK_PERIOD / 4); // Allow combinational logic to settle, though for $display it might not be strictly needed
                               // Using a small delay helps ensure value is propagated if a waveform is viewed.
            $display("Input SINT8: %4d (0x%2h) -> Output BF16: 0x%4h", test_sint8_in, test_sint8_in, test_bf16_out);
        end
    endtask

    // Test sequence
    initial begin
        $timeformat(-9, 2, " ns", 10);
        $display("-----------------------------------------------------");
        $display("Starting Testbench for sint8_to_bf16_converter");
        $display("-----------------------------------------------------");

        // Initialize
        clk = 0;
        rst = 1; // Assert reset
        test_sint8_in = 0; // Initialize to a known value
        #(CLK_PERIOD * 2);
        rst = 0;   // Deassert reset
        #(CLK_PERIOD);


        // Test specific values using the task
        // Positive values
        apply_and_display(0);    // SINT8 0
        apply_and_display(1);    // SINT8 1, Expected: 3f80 (1.0)
        apply_and_display(7);    // SINT8 7, Expected: 40e0 (7.0)
        apply_and_display(8);    // SINT8 8, Expected: 4100 (8.0)
        apply_and_display(15);   // SINT8 15, Expected: 4170 (15.0)
        apply_and_display(16);   // SINT8 16, Expected: 4180 (16.0)
        apply_and_display(31);   // SINT8 31, Expected: 41f8 (31.0)
        apply_and_display(32);   // SINT8 32, Expected: 4200 (32.0)
        apply_and_display(63);   // SINT8 63, Expected: 427c (63.0)
        apply_and_display(64);   // SINT8 64, Expected: 4280 (64.0)
        apply_and_display(127);  // SINT8 127, Expected: 42fe (127.0)

        // Negative values
        apply_and_display(-1);   // SINT8 -1, Expected: bf80 (-1.0)
        apply_and_display(-8);   // SINT8 -8, Expected: c100 (-8.0)
        apply_and_display(-16);  // SINT8 -16, Expected: c180 (-16.0)
        apply_and_display(-127); // SINT8 -127, Expected: c2fe (-127.0)
        apply_and_display(-128); // SINT8 -128, Expected by current code: c2fe (-127.0)


        $display("-----------------------------------------------------");
        $display("Testbench Finished");
        $display("-----------------------------------------------------");
        $finish;
    end

endmodule