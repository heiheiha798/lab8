//
// Filename: tb_accelerator.v
// Description: A testbench for the accelerator, tailored for a file-based
//              verification flow. It uses a 64-bit wide memory model to
//              directly interface with hex-formatted CSV files.
//
`timescale 1ns / 1ps

module tb_accelerator;

    //======================================================================
    //== Test Parameters (与Python脚本和DUT保持一致)
    //======================================================================
    localparam MATRIX_SIZE               = 48;
    localparam TILE_SIZE                 = 16;
    
    localparam MAIN_MEM_ADDR_WIDTH       = 32;
    localparam MAIN_MEM_DATA_WIDTH_BITS  = 64;
    localparam MAIN_MEM_DATA_WIDTH_BYTES = MAIN_MEM_DATA_WIDTH_BITS / 8;

    // 内存基地址
    localparam BASE_ADDR_A               = 32'h10000000;
    localparam BASE_ADDR_B               = 32'h20000000;
    localparam BASE_ADDR_C               = 32'h30000000;

    // 仿真控制参数
    localparam CLK_PERIOD                = 10; // 10 ns = 100 MHz clock
    localparam MEM_READ_LATENCY          = 8;  // 主存读取延迟 (周期数)

    // --- 内存模型参数 (以64位字为单位) ---
    // A矩阵和B矩阵各占用的字数
    localparam WORDS_PER_MATRIX_A_OR_B   = (MATRIX_SIZE * MATRIX_SIZE) / MAIN_MEM_DATA_WIDTH_BYTES;
    // C矩阵占用的字数 (每个元素32位)
    localparam WORDS_PER_MATRIX_C        = (MATRIX_SIZE * MATRIX_SIZE * 4) / MAIN_MEM_DATA_WIDTH_BYTES;
    // 总字数，留些余量
    localparam MEM_TOTAL_WORDS           = WORDS_PER_MATRIX_A_OR_B * 2 + WORDS_PER_MATRIX_C + 128;

    // C矩阵在统一内存模型中的起始字地址
    localparam MEM_OFFSET_WORDS_C        = WORDS_PER_MATRIX_A_OR_B * 2;

    //======================================================================
    //== Signal Declarations
    //======================================================================
    reg  clk;
    reg  rst_n;
    reg  start;
    wire busy;
    wire done;

    // --- Connections to DUT ---
    wire                                imem_req_valid;
    reg                                 imem_req_ready;
    reg                                 imem_resp_valid;
    reg  [MAIN_MEM_DATA_WIDTH_BITS-1:0] imem_resp_rdata;
    wire [MAIN_MEM_ADDR_WIDTH-1:0]      imem_req_addr;

    wire                                omem_req_valid;
    wire [MAIN_MEM_DATA_WIDTH_BITS-1:0] omem_req_wdata;
    wire [MAIN_MEM_ADDR_WIDTH-1:0]      omem_req_addr;
    reg                                 omem_req_ready;
    
    // --- Testbench Internal Variables ---
    time    start_time;
    time    end_time;
    integer fid; // 文件句柄
    integer i;   // 通用循环变量

    //======================================================================
    //== DUT Instantiation
    //======================================================================
    accelerator #(
        .MATRIX_SIZE(MATRIX_SIZE),
        .TILE_SIZE(TILE_SIZE)
    ) dut (
        .clk(clk),
        .rst_n(rst_n),
        .start(start),
        .busy(busy),
        .done(done),
        .imem_req_valid(imem_req_valid),
        .imem_req_ready(imem_req_ready),
        .imem_resp_valid(imem_resp_valid),
        .imem_resp_rdata(imem_resp_rdata),
        .imem_req_addr(imem_req_addr),
        .omem_req_valid(omem_req_valid),
        .omem_req_wdata(omem_req_wdata),
        .omem_req_addr(omem_req_addr),
        .omem_req_ready(omem_req_ready)
    );

    //======================================================================
    //== Unified Memory Model (64-bit Word Addressable)
    //======================================================================
    
    // 将主存建模为64位宽的存储器数组，与文件格式完全对应
    reg [MAIN_MEM_DATA_WIDTH_BITS-1:0] unified_memory [0:MEM_TOTAL_WORDS-1];
    
    reg [MAIN_MEM_ADDR_WIDTH-1:0] imem_read_addr_reg;
    reg [MEM_READ_LATENCY:0]      imem_latency_shifter;
    
    // --- 内存读取逻辑 ---
    always @(posedge clk or negedge rst_n) begin
        if(!rst_n) begin
            imem_req_ready <= 1'b0;
            imem_resp_valid <= 1'b0;
            imem_latency_shifter <= 0;
        end else begin
            imem_req_ready <= (imem_latency_shifter == 0);

            imem_latency_shifter <= {imem_latency_shifter[MEM_READ_LATENCY-1:0], 1'b0};
            
            if (imem_req_valid && imem_req_ready) begin
                imem_read_addr_reg <= imem_req_addr;
                imem_latency_shifter[0] <= 1'b1;
            end
            
            imem_resp_valid <= imem_latency_shifter[MEM_READ_LATENCY];

            if(imem_latency_shifter[MEM_READ_LATENCY-1]) begin
                integer word_index;
                
                // 将DUT的字节地址转换为内存模型的字地址索引
                if (imem_read_addr_reg >= BASE_ADDR_B) begin
                    word_index = ((imem_read_addr_reg - BASE_ADDR_B) / MAIN_MEM_DATA_WIDTH_BYTES) + WORDS_PER_MATRIX_A_OR_B;
                end else begin
                    word_index = (imem_read_addr_reg - BASE_ADDR_A) / MAIN_MEM_DATA_WIDTH_BYTES;
                end
                
                // 直接从字内存中读取
                imem_resp_rdata <= unified_memory[word_index];
            end
        end
    end

    // --- 内存写入逻辑 ---
    always @(posedge clk) begin
        omem_req_ready <= 1'b1;
        if (omem_req_valid && omem_req_ready) begin
            integer word_index;
            // 将DUT的字节地址转换为内存模型的字地址索引
            word_index = ((omem_req_addr - BASE_ADDR_C) / MAIN_MEM_DATA_WIDTH_BYTES) + MEM_OFFSET_WORDS_C;
            
            // 直接写入字内存
            unified_memory[word_index] <= omem_req_wdata;
        end
    end

    //======================================================================
    //== Test Sequence
    //======================================================================
    
    // 时钟生成器
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end
    
    // 主测试序列
    initial begin
        $display("[%0t] [TB] Starting testbench...", $time);
        
        // 1. 从文件加载初始内存镜像
        $readmemh("input_mem.csv", unified_memory);
        $display("[%0t] [TB] Initial memory image 'input_mem.csv' loaded.", $time);
        
        // 2. 复位系统
        start = 1'b0;
        rst_n = 1'b0;
        #(CLK_PERIOD * 5);
        rst_n = 1'b1;
        $display("[%0t] [TB] Reset released.", $time);
        
        // 3. 启动加速器
        @(posedge clk);
        start = 1'b1;
        start_time = $time;
        @(posedge clk);
        start = 1'b0;
        $display("[%0t] [TB] Accelerator started. Waiting for completion...", $time);

        // 4. 等待DUT完成
        wait (done == 1'b1);
        end_time = $time;
        @(posedge clk); 
        $display("[%0t] [TB] Accelerator has asserted 'done' signal.", $time);
        
        // 5. 将结果内存转储到文件
        dump_output_memory_to_file("result_mem.csv");

        // 6. 报告性能并结束
        $display("------------------------------------------------------------------");
        $display("           Simulation finished successfully!");
        $display("           Total execution time: %0d clock cycles.", (end_time - start_time) / CLK_PERIOD);
        $display("           Results dumped to 'result_mem.csv' for external verification.");
        $display("------------------------------------------------------------------");
        
        $finish;
    end

    // --- 任务: 将输出内存转储到文件 ---
    task dump_output_memory_to_file;
        input string filename;
        begin
            $display("[%0t] [TB] Dumping output memory to file: %s", $time, filename);
            fid = $fopen(filename, "w");
            if (fid == 0) begin
                $error("[%0t] [TB] Could not open file %s for writing.", $time, filename);
                $finish;
            end

            // 逐字写入 C 矩阵区域
            for (i = 0; i < WORDS_PER_MATRIX_C; i = i + 1) begin
                // 使用 $fdisplayh 直接写入十六进制字符串，不带0x，符合Python脚本预期
                $fdisplayh(fid, unified_memory[MEM_OFFSET_WORDS_C + i]);
            end
            
            $fclose(fid);
            $display("[%0t] [TB] Memory dump complete.", $time);
        end
    endtask

endmodule