#!/bin/bash

# Script to run ONLY Logic Synthesis and STA for the accelerator
# Execute this script from the ~/lab8 directory

# --- Configuration ---
TOP_MODULE_RTL="accelerator"

# RTL Source Files (paths relative to ~/lab8, but will be used with ../ from yosys-sta dir)
PE_FILE="./pe.v"
# Removed: SYSTOLIC_ARRAY_FILE="./systolic_array.v" as it's replaced by sa_enhanced.v
ACCELERATOR_RTL_FILE="./accelerator.v"

# Updated list of all necessary RTL files for synthesis (excluding SRAM behavioral models)
# These will be passed to Yosys for synthesis.
LOADER_FILE="./loader.v"
DATA_FORMATTER_FILE="./data_formatter.v"
SA_ENHANCED_FILE="./sa_enhanced.v" # This is your updated systolic array module
WRITER_FILE="./writer.v"

# IMPORTANT: sram_banked.v and sram_c_accum.v are behavioral SRAM models.
# They are excluded from RTL_FILES because they are conditionally compiled out
# in accelerator.v when SYNTHESIS is defined.
# If these files were included here, Yosys would try to synthesize them into standard cells,
# which is what we want to avoid for black-boxing SRAMs.
RTL_FILES_LIST=(
    "${ACCELERATOR_RTL_FILE}"
    "${LOADER_FILE}"
    "${DATA_FORMATTER_FILE}"
    "${SA_ENHANCED_FILE}"
    "${PE_FILE}"
    "${WRITER_FILE}"
)

# Convert the array to a space-separated string, prepending "../" for make -C
RTL_FILES=""
for file in "${RTL_FILES_LIST[@]}"; do
    RTL_FILES+="../${file} "
done
# Remove trailing space
RTL_FILES=$(echo "${RTL_FILES}" | xargs)


# Synthesis Output Directory (relative to ~/lab8)
SYNTH_OUTPUT_DIR="./output_synth_wsl"

# SDC File (path relative to ~/lab8)
SDC_FILE="./accelerator.sdc"

# Clock Configuration
CLK_FREQ_MHZ=909 # Changed to 100MHz for initial test as per user request
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

# Prepare SDC file if it doesn't exist (basic clock definition and I/O delays)
if [ ! -f "${SDC_FILE}" ]; then
    echo "SDC file '${SDC_FILE}' not found. Creating a basic one with clock and I/O definitions."
    {
        echo "# Clock Definition"
        echo "create_clock -name ${CLK_PORT_NAME} -period [expr 1000.0/${CLK_FREQ_MHZ}] [get_ports ${CLK_PORT_NAME}]"
        echo
        echo "# --- Clock Uncertainty and Transition ---"
        echo "# These are typical values, adjust if you have better estimates"
        echo "set_clock_uncertainty 0.1 [get_clocks ${CLK_PORT_NAME}]"
        echo "set_clock_transition 0.1 [get_clocks ${CLK_PORT_NAME}]"
        echo
        echo "# --- Input Delays ---"
        echo "# Assume inputs change 30% after the clock edge at the driving chip"
        echo "set clk_period [get_property period [get_clocks ${CLK_PORT_NAME}]]"
        echo "set input_delay_val [expr 0.3 * \$clk_period]"
        echo "set_input_delay \$input_delay_val -clock ${CLK_PORT_NAME} [all_inputs]"
        echo "# Reset is often treated as asynchronous or has looser timing"
        echo "set_input_delay [expr 0.5 * \$clk_period] -clock ${CLK_PORT_NAME} [get_ports rst_n]"
        echo
        echo "# --- Output Delays ---"
        echo "# Assume the chip being driven by this output needs the data 30% before its clock edge"
        echo "set output_delay_val [expr 0.3 * \$clk_period]"
        echo "set_output_delay \$output_delay_val -clock ${CLK_PORT_NAME} [all_outputs]"
        echo
        echo "# --- Operating Conditions & Wire Load Models (Placeholder) ---"
        echo "# These should be provided by your PDK/library, but if not, yosys-sta might have defaults."
        echo "# Example: set_operating_conditions -max slow"
        echo "# Example: set_wire_load_model -name 16000 -library slow"
    } > ${SDC_FILE}
    echo "Basic SDC file created. Please review and customize if needed, especially for SRAM ports."
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
    RTL_FILES="${RTL_FILES}" \
    VERILOG_DEFINES="SYNTHESIS" # <--- THIS IS THE KEY ADDITION to define SYNTHESIS macro

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
