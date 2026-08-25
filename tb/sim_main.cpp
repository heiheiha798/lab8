// sim_main.cpp
#include <verilated.h>
#include "Vtb_accelerator.h" // 包含顶层模块头文件
#include <iostream>
#include <iomanip> // 包含头文件以使用std::setw等格式化工具

int main(int argc, char **argv)
{
    std::cout << "SIM_CPP: Starting main()." << std::endl;
    VerilatedContext *m_contextp = new VerilatedContext;
    m_contextp->commandArgs(argc, argv);

    Vtb_accelerator *m_duvp = new Vtb_accelerator{m_contextp, "TOP"};
    std::cout << "SIM_CPP: DUT (Vtb_accelerator) instantiated." << std::endl;
    
    // --- 进度反馈相关变量 ---
    // 每隔1,000,000个时间单位 (1us) 打印一次进度
    const vluint64_t PROGRESS_UPDATE_INTERVAL_TIME = 1000000; 
    
    // 记录下一次打印进度的时间戳
    vluint64_t next_progress_update_time = PROGRESS_UPDATE_INTERVAL_TIME;

    std::cout << "SIM_CPP: Entering simulation loop..." << std::endl;
    
    while (!m_contextp->gotFinish())
    {
        // 每次只推进1个时间单位，让Verilog内部的时钟生成器工作
        m_contextp->timeInc(1);
        m_duvp->eval(); // 只需要调用eval()

        // 检查并打印进度
        if (m_contextp->time() >= next_progress_update_time) {
            
            // --- MODIFICATION: 修改打印格式 ---
            // 将以ps为单位的时间戳除以1000，得到ns
            vluint64_t time_in_ns = m_contextp->time() / 10000;
            
            std::cout << "[SIM_CPP PROGRESS] Time: " << std::setw(9) << time_in_ns 
                      << " cycle" << std::endl; // 单位改为 us 更合适
            
            // 更新到下一个打印时间点
            next_progress_update_time += PROGRESS_UPDATE_INTERVAL_TIME;
        }
    }
    
    vluint64_t final_time_in_ns = m_contextp->time() / 1000;
    std::cout << "SIM_CPP: Exited simulation loop. Final time: " << (final_time_in_ns - 55)/10 << " cycles" << std::endl;

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