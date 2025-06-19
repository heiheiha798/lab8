#!/bin/bash

# Script to run ONLY Logic Synthesis and STA for the accelerator
# Execute this script from the ~/lab8 directory

# --- Configuration ---
TOP_MODULE_RTL="accelerator"

# RTL Source Files (paths relative to ~/lab8, but will be used with ../ from yosys-sta dir)
PE_FILE="./pe.v"
SYSTOLIC_ARRAY_FILE="./systolic_array.v"
ACCELERATOR_RTL_FILE="./accelerator.v"
# Note: The makefile command will internally prepend "../" to these paths
# when executed from the yosys-sta directory.

# Synthesis Output Directory (relative to ~/lab8)
SYNTH_OUTPUT_DIR="./output_synth_wsl"

# SDC File (path relative to ~/lab8)
SDC_FILE="./accelerator.sdc"

# Clock Configuration
CLK_FREQ_MHZ=885
CLK_PORT_NAME="clk" # Clock port name in the top RTL module

# --- Helper Functions ---
echocmd() {
  echo
  echo "----------------------------------------------------------------------"
  echo "--- $1"
  echo "----------------------------------------------------------------------"
}

# --- Script Execution ---
# Ensure we are in the lab8 directory (or adjust paths accordingly)
if [ ! -f "accelerator.v" ]; then
    echo "Error: This script must be run from the ~/lab8 directory, where accelerator.v is present."
    exit 1
fi
if [ ! -d "./yosys-sta" ]; then
    echo "Error: ./yosys-sta directory not found. Please ensure it's in the current path."
    exit 1
fi


# 1. Logic Synthesis and Static Timing Analysis (using yosys-sta Makefile)
echocmd "Starting Logic Synthesis and Static Timing Analysis (STA)"

# Clean previous synthesis run for this specific output directory (optional, but good practice)
# Note: The yosys-sta Makefile might have its own clean targets,
# but cleaning the output directory from here ensures a fresh start for *this script's* output.
rm -rf ${SYNTH_OUTPUT_DIR}
mkdir -p ${SYNTH_OUTPUT_DIR} # Ensure base output directory exists, yosys-sta makefile will create subdir

# Prepare SDC file if it doesn't exist (basic clock definition)
if [ ! -f "${SDC_FILE}" ]; then
    echo "SDC file '${SDC_FILE}' not found. Creating a basic one with clock definition."
    echo "create_clock -name ${CLK_PORT_NAME} -period [expr 1000.0/${CLK_FREQ_MHZ}] [get_ports ${CLK_PORT_NAME}]" > ${SDC_FILE}
    # You might want to add:
    # echo "set_input_delay 2.0 -clock ${CLK_PORT_NAME} [all_inputs]" >> ${SDC_FILE}
    # echo "set_output_delay 2.0 -clock ${CLK_PORT_NAME} [all_outputs]" >> ${SDC_FILE}
    echo "Basic SDC file created. Please review and customize if needed."
fi

# Run the make command for STA (which includes synthesis)
# The paths for SDC_FILE and RTL_FILES are adjusted with ../ because 'make -C' changes directory.
# The path for O (output) is also adjusted with ../ so that the output directory
# is created relative to the current script's location (~/lab8), not inside yosys-sta.
make -C ./yosys-sta sta \
    DESIGN=${TOP_MODULE_RTL} \
    SDC_FILE=../${SDC_FILE} \
    CLK_FREQ_MHZ=${CLK_FREQ_MHZ} \
    CLK_PORT_NAME=${CLK_PORT_NAME} \
    O=../${SYNTH_OUTPUT_DIR} \
    RTL_FILES="../${PE_FILE} ../${SYSTOLIC_ARRAY_FILE} ../${ACCELERATOR_RTL_FILE}"

# Check if synthesis was successful
# The yosys-sta makefile is expected to create a subdirectory like accelerator-100MHz
SYNTH_SUBDIR_NAME="${TOP_MODULE_RTL}-${CLK_FREQ_MHZ}MHz"
FINAL_NETLIST_PATH_SYN="${SYNTH_OUTPUT_DIR}/${SYNTH_SUBDIR_NAME}/${TOP_MODULE_RTL}.netlist.syn.v"
FINAL_NETLIST_PATH_FIXED="${SYNTH_OUTPUT_DIR}/${SYNTH_SUBDIR_NAME}/${TOP_MODULE_RTL}.netlist.fixed.v"

if [ -f "${FINAL_NETLIST_PATH_FIXED}" ] || [ -f "${FINAL_NETLIST_PATH_SYN}" ]; then
    echo "Logic Synthesis and STA appear to be successful."
    echo "Outputs are in: ${SYNTH_OUTPUT_DIR}/${SYNTH_SUBDIR_NAME}"
else
    echo "Error: Synthesized netlist not found after make sta."
    echo "Please check logs in ${SYNTH_OUTPUT_DIR}/${SYNTH_SUBDIR_NAME} (e.g., yosys.log, sta.log)."
    exit 1
fi

echocmd "Logic Synthesis and STA finished."