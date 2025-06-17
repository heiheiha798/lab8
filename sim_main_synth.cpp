#include "Vtb_synth_accelerator.h"
#include "verilated.h"
// #include "verilated_vcd_c.h" // REMOVED or COMMENTED OUT
#include <iostream>

vluint64_t main_time = 0; // Can still be used for $time if your Verilog uses it, or for loop limit

double sc_time_stamp() { // Called by $time in Verilog, keep if $time is used
    return main_time;
}

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Vtb_synth_accelerator* top = new Vtb_synth_accelerator;

    std::cout << "Simulation starting..." << std::endl;

    while (!Verilated::gotFinish()) {
        if (main_time > 200000000) { // Increased limit just in case, adjust as needed
             std::cerr << "Warning: Simulation time exceeded limit, forcing exit." << std::endl;
             break;
        }
        top->eval();
        // if (tfp) tfp->dump(main_time); // REMOVED
        main_time++; // Increment simulation step counter
    }

    // if (tfp) { ... } // REMOVED

    top->final();
    delete top;

    std::cout << "Simulation finished at time " << main_time << std::endl;
    return 0;
}