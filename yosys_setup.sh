#!/bin/bash

tar xvzf yosys-sta.tar.gz
cd yosys-sta
echo "export PATH=$PATH:/data/share/oss-cad-suite/bin" >> ~/.bashrc
make init 
echo exit | ./bin/iEDA -v
