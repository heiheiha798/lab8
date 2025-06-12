#include <verilated.h>
#include "Vtestbench_top.h"

int main(int argc, char **argv)
{
  // 构造环境对象和设计对象
  VerilatedContext *m_contextp = new VerilatedContext; // 环境
  Vtestbench_top *m_duvp = new Vtestbench_top;         // 设计

  // 主仿真循环
  while (!m_contextp->gotFinish())
  {
    // 刷新电路状态
    m_duvp->eval();
    m_contextp->timeInc(1); // 推进最小时间单位
  }

  // 释放内存
  delete m_duvp;
  delete m_contextp; // 删除环境对象

  return 0;
}