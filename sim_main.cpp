// sim_main.cpp
#include <verilated.h>
#include "Vtb_accelerator.h" // --- MODIFIED: 包含新的顶层模块头文件
#include <iostream>

// --- MODIFIED: 仅在启用跟踪时包含 VCD 相关头文件 ---
#ifdef TRACE_ON
#include "verilated_vcd_c.h"
#endif

int main(int argc, char **argv)
{
    std::cout << "SIM_CPP: Starting main()." << std::endl;
    VerilatedContext *m_contextp = new VerilatedContext;
    m_contextp->commandArgs(argc, argv);

    // --- MODIFIED: 实例化新的顶层模块类 ---
    Vtb_accelerator *m_duvp = new Vtb_accelerator{m_contextp, "TOP"};
    std::cout << "SIM_CPP: DUT (Vtb_accelerator) instantiated." << std::endl;

// --- MODIFIED: 将所有 VCD 相关代码块条件化 ---
#ifdef TRACE_ON
    Verilated::traceEverOn(true);
    VerilatedVcdC *tfp = new VerilatedVcdC;
    std::cout << "SIM_CPP: VCD tracing is ON." << std::endl;
    m_duvp->trace(tfp, 99);
    tfp->open("waveform.vcd");
#endif

    vluint64_t simulation_steps = 0;
    std::cout << "SIM_CPP: Entering simulation loop..." << std::endl;
    while (!m_contextp->gotFinish())
    {
        // --- 仿真循环的核心 ---
        m_contextp->timeInc(1);
        m_duvp->eval();
        simulation_steps++;

#ifdef TRACE_ON
        if (tfp)
        {
            tfp->dump(m_contextp->time());
        }
#endif

    }
    std::cout << "SIM_CPP: Exited simulation loop. Total steps: " << simulation_steps << std::endl;

    // --- 清理 ---
#ifdef TRACE_ON
    if (tfp)
    {
        tfp->close();
        delete tfp;
        std::cout << "SIM_CPP: VCD trace file closed." << std::endl;
    }
#endif

    if (m_duvp)
    {
        delete m_duvp;
    }
    if (m_contextp)
    {
        delete m_contextp;
    }

    std::cout << "SIM_CPP: main() finished." << std::endl;
    return 0;
}