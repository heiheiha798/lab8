#!/bin/bash

# --- Location-independent: 无论从哪里调用，都先切到仓库根目录 ---
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${SCRIPT_DIR}/.."

# 解压 yosys-sta 工具链到仓库根目录 (生成 ./yosys-sta)
tar xvzf tools/yosys-sta.tar.gz
cd yosys-sta
echo "export PATH=$PATH:/data/share/oss-cad-suite/bin" >> ~/.bashrc
make init 
echo exit | ./bin/iEDA -v
