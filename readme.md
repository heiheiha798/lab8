
# Use *Verilator* for Fast Verilog Simulation

## Install Verilator
[https://verilator.org/guide/latest/install.html#git-install](https://verilator.org/guide/latest/install.html#git-install)

## Tutorial
This example refers to [https://blog.csdn.net/weixin_44699856/article/details/130253574](https://blog.csdn.net/weixin_44699856/article/details/130253574)

### Step 1:
Write a cpp wrapper (```sim_main.cpp```) :
```c++
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vtestbench_top.h"
 
int main(int argc, char** argv){
//构造环境对象，设计对象，波形对象
  VerilatedContext* m_contextp = new VerilatedContext;//环境
  VerilatedVcdC*    m_tracep   = new VerilatedVcdC;//波形
  Vtestbench_top*     m_duvp     = new Vtestbench_top;//注意这里需要用“Vtestbench_top”
//波形配置
  m_contextp->traceEverOn(true);//环境里打开波形开关
  m_duvp->trace(m_tracep,3);//深度为3
  m_tracep->open("wave.vcd");//打开要存数据的vcd文件
//写入数据到波形文件里
  while (!m_contextp->gotFinish()){
  //刷新电路状态
    m_duvp->eval();
  //dump数据
    m_tracep->dump(m_contextp->time());
  //增加仿真时间
    m_contextp->timeInc(1);
  }
//记得关闭trace对象以保存文件里的数据
  m_tracep->close();
//释放内存
  delete m_duvp;
  return 0;
}
```

### Step 2
Compile the wrapper:
```bash
verilator -cc -trace --timing testbench_top.v -exe sim_main.cpp
```
It should generate a new folder named "obj_dir".

### Step 3:

```bash
cp input_mem.csv ./obj_dir/
cd obj_dir
make -f Vtestbench_top.mk
./Vtestbench_top
```

### Note
Verilator requires more strict Verilog syntax style than iverilog.
