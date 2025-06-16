#include <verilated.h>
#include "Vtestbench_top.h"

int main(int argc, char **argv)
{
  VerilatedContext *m_contextp = new VerilatedContext;
  Vtestbench_top *m_duvp = new Vtestbench_top;

  while (!m_contextp->gotFinish())
  {
    m_duvp->eval();
    m_contextp->timeInc(1);
  }

  delete m_duvp;
  delete m_contextp;
  return 0;
}