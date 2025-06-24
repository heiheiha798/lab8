iverilog -o tb_sa_enhanced_accumulator_sim -Wall -g2012 \
    pe.v \
    sram_c_accum.v \
    sa_enhanced.v \
    tb_sa_enhanced_accumulator.v

vvp tb_sa_enhanced_accumulator_sim