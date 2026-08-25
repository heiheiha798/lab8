#!/bin/bash

# --- Location-independent: 无论从哪里调用，都先切到仓库根目录 ---
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${SCRIPT_DIR}/.."

# --- Configuration ---
TOP_MODULE_RTL="accelerator"

# --- RTL Source Files (设计 RTL 在 hdl/，综合用顶层在 syn/) ---
RTL_FILES=(
    "./hdl/pe.v"
    "./hdl/sa_enhanced.v"
    "./hdl/loader.v"
    "./hdl/data_formatter.v"
    "./hdl/writer.v"
    "./syn/accelerator_synth.v" # The synthesis-friendly top module
)

# --- Tool & Output Configuration ---
SYNTH_OUTPUT_DIR="./output_synth_V4"

# Path to the Synopsys Design Constraints file.
SDC_FILE="./syn/accelerator.sdc"

# Clock Configuration for STA.
CLK_FREQ_MHZ=893
CLK_PORT_NAME="clk" 

# --- Helper Functions ---
echocmd() {
  echo
  echo "----------------------------------------------------------------------"
  echo "--- $1"
  echo "----------------------------------------------------------------------"
}

# --- Script Execution ---

# Sanity check: Ensure the script is being run from the project root directory.
if [ ! -f "./syn/accelerator_synth.v" ]; then
    echo "Error: Top RTL file './syn/accelerator_synth.v' not found."
    echo "Please check the repository layout."
    exit 1
fi
if [ ! -d "./yosys-sta" ]; then
    echo "Error: The './yosys-sta' directory was not found."
    echo "Please run './tools/yosys_setup.sh' first to extract and initialize it."
    exit 1
fi

# 1. Start Synthesis and STA Process
echocmd "Starting Logic Synthesis and Static Timing Analysis (STA) for '${TOP_MODULE_RTL}'"

# Clean previous run's output directory for a fresh start.
rm -rf ${SYNTH_OUTPUT_DIR}
mkdir -p ${SYNTH_OUTPUT_DIR}

# Prepare a basic SDC file if one doesn't exist.
if [ ! -f "${SDC_FILE}" ]; then
    echo "SDC file '${SDC_FILE}' not found. Creating a basic one with a ${CLK_FREQ_MHZ}MHz clock."
    # Calculate clock period from frequency
    CLK_PERIOD=$(echo "1000.0 / ${CLK_FREQ_MHZ}" | bc)
    echo "create_clock -name ${CLK_PORT_NAME} -period ${CLK_PERIOD} [get_ports ${CLK_PORT_NAME}]" > ${SDC_FILE}
    # Add example input/output delay constraints and load
    echo "set_input_delay  0.5 -clock ${CLK_PORT_NAME} [all_inputs]" >> ${SDC_FILE}
    echo "set_output_delay 0.5 -clock ${CLK_PORT_NAME} [all_outputs]" >> ${SDC_FILE}
    echo "set_load 0.05 [all_outputs]" >> ${SDC_FILE}
    echo "Basic SDC file created. Please review and customize for your design's specific needs."
fi

# The 'make -C' command changes directory to ./yosys-sta, so we need to adjust
# all paths with a "../" prefix to point back to the project root.
ADJUSTED_RTL_FILES=""
for f in "${RTL_FILES[@]}"; do
    ADJUSTED_RTL_FILES="${ADJUSTED_RTL_FILES} ../${f}"
done

# Run the make command to perform synthesis and STA.
echocmd "Invoking yosys-sta Makefile..."
make -C ./yosys-sta sta \
    DESIGN=${TOP_MODULE_RTL} \
    SDC_FILE=../${SDC_FILE} \
    CLK_FREQ_MHZ=${CLK_FREQ_MHZ} \
    CLK_PORT_NAME=${CLK_PORT_NAME} \
    O=../${SYNTH_OUTPUT_DIR} \
    RTL_FILES="${ADJUSTED_RTL_FILES}"

# 2. Verify Results
echocmd "Verifying synthesis results..."

SYNTH_SUBDIR_NAME="${TOP_MODULE_RTL}-${CLK_FREQ_MHZ}MHz"
FINAL_NETLIST_PATH_SYN="${SYNTH_OUTPUT_DIR}/${SYNTH_SUBDIR_NAME}/${TOP_MODULE_RTL}.netlist.syn.v"
FINAL_NETLIST_PATH_FIXED="${SYNTH_OUTPUT_DIR}/${SYNTH_SUBDIR_NAME}/${TOP_MODULE_RTL}.netlist.fixed.v"

if [ -f "${FINAL_NETLIST_PATH_FIXED}" ] || [ -f "${FINAL_NETLIST_PATH_SYN}" ]; then
    echocmd "SUCCESS: Logic Synthesis and STA appear to be complete."
    echo "Outputs are located in: ${SYNTH_OUTPUT_DIR}/${SYNTH_SUBDIR_NAME}"
else
    echocmd "ERROR: Synthesized netlist not found."
    echo "Please check the logs in '${SYNTH_OUTPUT_DIR}/${SYNTH_SUBDIR_NAME}' for errors (e.g., yosys.log, sta.log)."
    exit 1
fi

echocmd "Script finished."
