// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_synth_accelerator.h for the primary calling header

#include "Vtb_synth_accelerator__pch.h"
#include "Vtb_synth_accelerator__Syms.h"
#include "Vtb_synth_accelerator___024root.h"

void Vtb_synth_accelerator___024root___ctor_var_reset(Vtb_synth_accelerator___024root* vlSelf);

Vtb_synth_accelerator___024root::Vtb_synth_accelerator___024root(Vtb_synth_accelerator__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , __VdlySched{*symsp->_vm_contextp__}
    , __Vm_mtaskstate_513(0x6cU)
    , __Vm_mtaskstate_523(2U)
    , __Vm_mtaskstate_517(0x2fU)
    , __Vm_mtaskstate_507(2U)
    , __Vm_mtaskstate_508(2U)
    , __Vm_mtaskstate_515(2U)
    , __Vm_mtaskstate_510(1U)
    , __Vm_mtaskstate_519(2U)
    , __Vm_mtaskstate_261(0xedU)
    , __Vm_mtaskstate_522(1U)
    , __Vm_mtaskstate_524(1U)
    , __Vm_mtaskstate_516(2U)
    , __Vm_mtaskstate_521(2U)
    , __Vm_mtaskstate_274(0xd9U)
    , __Vm_mtaskstate_514(1U)
    , __Vm_mtaskstate_520(3U)
    , __Vm_mtaskstate_final__nba(0xcU)
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vtb_synth_accelerator___024root___ctor_var_reset(this);
}

void Vtb_synth_accelerator___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vtb_synth_accelerator___024root::~Vtb_synth_accelerator___024root() {
}
