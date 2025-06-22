// sim_main_synth.cpp
#include <verilated.h>
#include "Vtb_synth_accelerator.h" // 你的顶层模块名
#include "verilated_vcd_c.h"       // VCD 生成需要
#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "SIM_CPP: Starting main()." << std::endl;
    VerilatedContext *m_contextp = new VerilatedContext;
    m_contextp->commandArgs(argc, argv);

    Vtb_synth_accelerator *m_duvp = new Vtb_synth_accelerator{m_contextp, "TOP"};
    std::cout << "SIM_CPP: DUT (Vtb_synth_accelerator) instantiated." << std::endl;

    // --- VCD Tracing Setup ---
    Verilated::traceEverOn(true); // 全局启用跟踪功能
    VerilatedVcdC *tfp = new VerilatedVcdC;
    std::cout << "SIM_CPP: VerilatedVcdC object created (tfp) for VCD tracing." << std::endl;

    m_duvp->trace(tfp, 99); // 将 DUT 连接到 VCD, 99 表示最大深度
    std::cout << "SIM_CPP: m_duvp->trace(tfp, 99) called." << std::endl;

    tfp->open("waveform.vcd"); // 打开 VCD 文件
    if (tfp->isOpen())
    {
        std::cout << "SIM_CPP: waveform.vcd opened successfully." << std::endl;
    }
    else
    {
        std::cerr << "SIM_CPP: ERROR! Failed to open waveform.vcd." << std::endl;
        // 实际应用中可能需要更健壮的错误处理，例如退出程序
        delete tfp; // 清理已创建的对象
        delete m_duvp;
        delete m_contextp;
        return 1; // 表示错误退出
    }

    // --- Initial Dump ---
    // 建议在第一次 eval() 之后 dump(0)，以确保所有初始值传播完毕
    m_duvp->eval();                               // 第一次评估，传播初始值
    vluint64_t initial_time = m_contextp->time(); // time 应该是 0
    tfp->dump(initial_time);
    std::cout << "SIM_CPP: Initial dump at Verilator Time (m_contextp->time()): " << initial_time << std::endl;
    // tfp->flush(); // 可选：在初始 dump 后 flush 一次

    // --- Simulation Loop ---
    vluint64_t simulation_steps = 0;
    std::cout << "SIM_CPP: Entering simulation loop..." << std::endl;
    while (!m_contextp->gotFinish())
    {
        m_contextp->timeInc(1); // 推进 Verilator 的时间单位 (e.g., 1ps)
        m_duvp->eval();         // 评估模型

        // Dump VCD data
        if (tfp->isOpen())
        { // 再次检查，以防万一
            vluint64_t current_verilator_time = m_contextp->time();
            tfp->dump(current_verilator_time);
            tfp->flush(); // 尝试1：在每次 dump 后都 flush，用于诊断

            // 调试打印 Verilator 内部时间和仿真步数
            if (simulation_steps < 10 || (simulation_steps > 0 && simulation_steps % 10000 == 0))
            {
                std::cout << "SIM_CPP_TIME_DEBUG: SimStep: " << simulation_steps
                          << ", VerilatorTime (m_contextp->time()): " << current_verilator_time
                          << std::endl;
            }
        }
        simulation_steps++;

        // 超时逻辑
        if (simulation_steps > 80000000)
        { // 调整超时步数
            std::cerr << "SIM_CPP: Simulation timeout after " << simulation_steps << " steps! Forcing finish." << std::endl;
            if (m_contextp)
                m_contextp->gotFinish(true);
            break;
        }
    }
    std::cout << "SIM_CPP: Exited simulation loop. Total steps: " << simulation_steps
              << ". Final Verilator time (m_contextp->time()): " << (m_contextp ? m_contextp->time() : -1)
              << std::endl;

    // --- Cleanup VCD ---
    if (tfp)
    { // 确保 tfp 不是 nullptr
        if (tfp->isOpen())
        {
            std::cout << "SIM_CPP: Flushing and closing waveform.vcd." << std::endl;
            tfp->flush(); // 确保所有数据写入
            tfp->close(); // 关闭 VCD 文件
        }
        delete tfp; // 删除 VCD 对象
        tfp = nullptr;
        std::cout << "SIM_CPP: tfp object deleted." << std::endl;
    }

    // --- Cleanup DUT and Context ---
    std::cout << "SIM_CPP: Deleting DUT and context." << std::endl;
    if (m_duvp)
    {
        delete m_duvp;
        m_duvp = nullptr;
    }
    if (m_contextp)
    {
        // m_contextp->coveragep()->write("logs/coverage.dat"); // 如果启用了覆盖率
        delete m_contextp;
        m_contextp = nullptr;
    }

    std::cout << "SIM_CPP: main() finished." << std::endl;
    return 0;
}