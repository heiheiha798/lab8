---
## 项目目标回顾

设计一个使用BF16进行近似计算的SINT8矩阵乘法器（最终目标是512x512，当前我们实现并测试了一个16x16的BF16脉动阵列核心）。

---
## 设计层级与架构总结

### 1. BF16 算术单元 (Arithmetic Units)

* **bfloat16\_multiplier.v**
    * **功能**：执行两个BF16数的乘法。
    * **接口**：
        * **输入**：`num1 [15:0]`, `num2 [15:0]` (两个BF16操作数)
        * **输出**：`result [15:0]` (BF16乘法结果), `is_NaN` (结果是否为NaN), `is_infinity` (结果是否为无穷大), `is_zero` (结果是否为零)
    * **特性**：
        * 纯组合逻辑。
        * 处理特殊值（NaN, Inf, Zero），包括 Inf*0 = NaN。
        * 对次正规数输出采用Flush-to-Zero (FTZ)策略。
* **bfloat16\_adder.v**
    * **功能**：执行两个BF16数的加法（或有效减法）。
    * **接口**：
        * **输入**：`num1 [15:0]`, `num2 [15:0]` (两个BF16操作数)
        * **输出**：`result [15:0]` (BF16加法结果), `is_NaN`, `is_infinity`, `is_zero`
    * **特性**：
        * 纯组合逻辑。
        * 包含对阶、尾数加/减、规格化等复杂步骤。
        * 处理特殊值，包括 (+Inf) + (-Inf) = NaN。
        * 对次正规数输入视为零，输出也可能通过FTZ变为零。
        * 特殊处理 X+0=X。

### 2. 处理单元 (Processing Element - pe.v)

* **功能**：作为脉动阵列的基本计算单元，执行一个BF16乘加累加操作，并支持数据流的传递。设计用于输出固定的脉动阵列，每个PE计算目标结果矩阵的一个元素的部分和。
* **参数**：
    * `DATA_WIDTH` (设为16 for BF16)
    * `ACCUMULATION_CYCLES` (对于N*N矩阵乘法，PE计算一个点积需要N次累加，所以此参数应设为N)
* **接口 (修改后版本)**：
    * **全局信号**：
        * `clk`, `rst_n`
        * `enable`: PE使能信号。为高时，PE锁存输入数据，进行计算，并传递数据。
        * `clear_accumulator`: 清除内部累加器、mul\_result\_reg和相关状态。
    * **A 数据流**：
        * `a_data_in [DATA_WIDTH-1:0]`
        * `a_data_out [DATA_WIDTH-1:0]` (延迟一拍的 `a_data_in`)
    * **B 数据流**：
        * `b_data_in [DATA_WIDTH-1:0]`
        * `b_data_out [DATA_WIDTH-1:0]` (延迟一拍的 `b_data_in`)
    * **结果输出**：
        * `result_out [DATA_WIDTH-1:0]` (当前累加和)
        * `result_valid`: 单周期脉冲，当完成 `ACCUMULATION_CYCLES` 次有效累加后产生。
        * `pe_is_nan`, `pe_is_infinity`: 累加结果的NaN/Inf状态。
* **内部架构**：
    * 包含 `a_reg` 和 `b_reg` 分别锁存输入的A数据流和B数据流。
    * 实例化一个 `bfloat16_multiplier` (输入为 `a_reg`, `b_reg`)。
    * 乘法结果通过 `mul_result_reg` 进行一级流水。
    * 实例化一个 `bfloat16_adder` (输入为 `mul_result_reg`, `local_accumulator_reg`)。
    * 加法结果更新 `local_accumulator_reg`。
    * 包含一个 `accumulation_counter` 来跟踪累加次数并产生 `result_valid`。
    * 实现了粘性NaN。
    * **流水线延迟**：从A、B数据输入到其乘积项被累加到 `local_accumulator_reg` 大约有2个主要时钟周期的延迟。

### 3. 脉动阵列 (Systolic Array - systolic\_array.v)

* **功能**：实现一个 `SIZE` x `SIZE` 的输出固定脉动阵列，用于计算 C = A \* B。每个 PE\[r\]\[c\] 计算结果矩阵的元素 C\[r\]\[c\]。
* **参数**：
    * `SIZE` (阵列维度，例如16)
    * `DATA_WIDTH` (设为16)
* **接口 (修改后版本)**：
    * **全局信号**：
        * `clk`, `rst_n`
        * `clear_all_pe_accumulators`: 全局清除所有PE的累加器。
        * `activate_pe_computation`: 全局使能所有PE的计算和数据流动。
    * **数据输入 (波前数据 Wavefronts)**：
        * `array_a_in [SIZE*DATA_WIDTH-1:0]`: 提供A矩阵的当前 "k波前" 数据，即 {A\[0\]\[k\], A\[1\]\[k\], ..., A\[SIZE-1\]\[k\]}。
        * `array_b_in [SIZE*DATA_WIDTH-1:0]`: 提供B矩阵的当前 "k波前" 数据，即 {B\[k\]\[0\], B\[k\]\[1\], ..., B\[k\]\[SIZE-1\]}。
    * **结果读出控制**：
        * `select_output_row_idx`: 选择要读出的结果矩阵的行号。
        * `enable_tile_row_output`: 使能所选行的结果输出。
    * **数据输出**：
        * `array_a_out [SIZE*DATA_WIDTH-1:0]`: 从阵列右侧流出的A数据（经过扭曲和传播）。
        * `array_b_out [SIZE*DATA_WIDTH-1:0]`: 从阵列底部流出的B数据（经过扭曲和传播）。
        * `tile_row_result_out [SIZE*DATA_WIDTH-1:0]`: 所选行的计算结果。
        * `tile_row_result_valid`: 指示 `tile_row_result_out` 是否有效。
    * **状态输出**：
        * `tile_all_pes_done_one_pass`: 所有PE是否都完成了一轮计算。
        * `tile_had_nan`, `tile_had_inf`: 阵列中是否有PE产生NaN或Inf。
* **内部架构和数据流**：
    * **PE例化**：例化 `SIZE` x `SIZE` 个 `pe` 模块。PE的 `ACCUMULATION_CYCLES` 参数被设为 `SIZE`。
    * **数据扭曲 (Skewing)**：
        * 在阵列的输入边界，使用移位寄存器链对 `array_a_in` 的每一行数据和 `array_b_in` 的每一列数据进行延迟。
        * A\[r\]\[k\] 波前数据在送入 PE\[r\]\[0\] 之前被延迟 r 个周期。
        * B\[k\]\[c\] 波前数据在送入 PE\[0\]\[c\] 之前被延迟 c 个周期。
        * 扭曲逻辑仅在 `activate_pe_computation` 有效时工作。
    * **A数据流**：经过扭曲后，从左边界（`a_data_wires[r][0]`）进入第 r 行PE，然后水平向右传播至 `a_data_wires[r][SIZE]`。
    * **B数据流**：经过扭曲后，从上边界（`b_data_wires[0][c]`）进入第 c 列PE，然后垂直向下传播至 `b_data_wires[SIZE][c]`。
    * 这种扭曲和传播确保了 A\[r\]\[k\] 和 B\[k\]\[c\] 能够在 PE\[r\]\[c\] 相遇，以计算 C\[r\]\[c\] 的对应乘积项。
    * **控制信号分发**：`clear_all_pe_accumulators` 和 `activate_pe_computation` 直接广播给所有PE。
    * **结果和状态收集**：
        * 收集所有PE的 `result_out`, `result_valid`, `pe_is_nan`, `pe_is_infinity`。
        * `pe_done_flags` 记录每个PE是否已完成其 `SIZE` 次累加。
        * `tile_row_result_valid` 基于所选行所有PE的 `pe_done_flags`。
        * `tile_all_pes_done_one_pass` 基于所有PE的 `pe_done_flags`。
        * NaN/Inf状态进行全局“或”汇总。

---
## 整体设计架构总结

该设计采用自底向上的构建方法：

首先实现底层的BF16乘法器和加法器作为核心算术单元。

基于这些算术单元构建了一个通用的处理单元（**PE**），该PE能够：
* 接收两个BF16数据流（A和B）。
* 将它们相乘。
* 将乘积与内部累加器的值相加。
* 在预设的累加次数完成后，输出累加结果和有效信号。
* 同时将输入的A和B数据流向下游PE传递（各延迟一拍）。

最后，将这些PE组织成一个二维的**脉动阵列**（Systolic Array）。该阵列通过：
* 在输入边界对A和B数据流进行精确的**时序扭曲 (skewing)**。
* 让扭曲后的A数据水平流动。
* 让扭曲后的B数据垂直流动。

实现了**输出固定 (Output Stationary)** 的计算模式，即阵列中的 PE\[r\]\[c\] 最终计算并存储结果矩阵 C 的元素 C\[r\]\[c\]。

提供了全局控制信号用于初始化和启动/停止计算。

提供了结果读出机制和状态监控。

这种架构利用了脉动阵列的并行性和流水线特性，通过规则的数据流动和本地计算，高效地执行矩阵乘法。BF16数据类型的使用是为了在保持一定计算精度的同时，减少数据位宽，从而可能降低硬件资源消耗和功耗，并提高数据吞吐。