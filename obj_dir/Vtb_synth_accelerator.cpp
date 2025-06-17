// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_synth_accelerator__pch.h"

//============================================================
// Constructors

Vtb_synth_accelerator::Vtb_synth_accelerator(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_synth_accelerator__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_synth_accelerator::Vtb_synth_accelerator(const char* _vcname__)
    : Vtb_synth_accelerator(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_synth_accelerator::~Vtb_synth_accelerator() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_synth_accelerator___024root___eval_debug_assertions(Vtb_synth_accelerator___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_synth_accelerator___024root___eval_static(Vtb_synth_accelerator___024root* vlSelf);
void Vtb_synth_accelerator___024root___eval_initial(Vtb_synth_accelerator___024root* vlSelf);
void Vtb_synth_accelerator___024root___eval_settle(Vtb_synth_accelerator___024root* vlSelf);
void Vtb_synth_accelerator___024root___eval(Vtb_synth_accelerator___024root* vlSelf);

void Vtb_synth_accelerator::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_synth_accelerator::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_synth_accelerator___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_synth_accelerator___024root___eval_static(&(vlSymsp->TOP));
        Vtb_synth_accelerator___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_synth_accelerator___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_synth_accelerator___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_synth_accelerator::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty(); }

uint64_t Vtb_synth_accelerator::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_synth_accelerator::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_synth_accelerator___024root___eval_final(Vtb_synth_accelerator___024root* vlSelf);

VL_ATTR_COLD void Vtb_synth_accelerator::final() {
    Vtb_synth_accelerator___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_synth_accelerator::hierName() const { return vlSymsp->name(); }
const char* Vtb_synth_accelerator::modelName() const { return "Vtb_synth_accelerator"; }
unsigned Vtb_synth_accelerator::threads() const { return 12; }
void Vtb_synth_accelerator::prepareClone() const { contextp()->prepareClone(); }
void Vtb_synth_accelerator::atClone() const {
    vlSymsp->__Vm_threadPoolp = static_cast<VlThreadPool*>(contextp()->threadPoolpOnClone());
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vtb_synth_accelerator::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vtb_synth_accelerator::trace()' called on model that was Verilated without --trace option");
}
