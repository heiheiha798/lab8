# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Make include file with class lists
#
# This file lists generated Verilated files, for including in higher level makefiles.
# See Vtb_synth_accelerator.mk for the caller.

### Switches...
# C11 constructs required?  0/1 (always on now)
VM_C11 = 1
# Timing enabled?  0/1
VM_TIMING = 1
# Coverage output mode?  0/1 (from --coverage)
VM_COVERAGE = 0
# Parallel builds?  0/1 (from --output-split)
VM_PARALLEL_BUILDS = 1
# Tracing output mode?  0/1 (from --trace/--trace-fst)
VM_TRACE = 0
# Tracing output mode in VCD format?  0/1 (from --trace)
VM_TRACE_VCD = 0
# Tracing output mode in FST format?  0/1 (from --trace-fst)
VM_TRACE_FST = 0

### Object file lists...
# Generated module classes, fast-path, compile with highest optimization
VM_CLASSES_FAST += \
	Vtb_synth_accelerator \
	Vtb_synth_accelerator___024root__DepSet_hd8316fd0__0 \
	Vtb_synth_accelerator___024root__DepSet_hbb93928e__0 \
	Vtb_synth_accelerator___024root__DepSet_hbb93928e__1 \
	Vtb_synth_accelerator___024root__DepSet_hbb93928e__2 \
	Vtb_synth_accelerator___024root__DepSet_hbb93928e__3 \
	Vtb_synth_accelerator___024root__DepSet_hbb93928e__4 \
	Vtb_synth_accelerator___024root__DepSet_hbb93928e__5 \

# Generated module classes, non-fast-path, compile with low/medium optimization
VM_CLASSES_SLOW += \
	Vtb_synth_accelerator___024root__Slow \
	Vtb_synth_accelerator___024root__DepSet_hd8316fd0__0__Slow \
	Vtb_synth_accelerator___024root__DepSet_hbb93928e__0__Slow \
	Vtb_synth_accelerator___024root__DepSet_hbb93928e__1__Slow \

# Generated support classes, fast-path, compile with highest optimization
VM_SUPPORT_FAST += \

# Generated support classes, non-fast-path, compile with low/medium optimization
VM_SUPPORT_SLOW += \
	Vtb_synth_accelerator__Syms \

# Global classes, need linked once per executable, fast-path, compile with highest optimization
VM_GLOBAL_FAST += \
	verilated \
	verilated_timing \
	verilated_threads \

# Global classes, need linked once per executable, non-fast-path, compile with low/medium optimization
VM_GLOBAL_SLOW += \


# Verilated -*- Makefile -*-
