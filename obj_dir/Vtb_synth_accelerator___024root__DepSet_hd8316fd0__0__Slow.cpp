// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_synth_accelerator.h for the primary calling header

#include "Vtb_synth_accelerator__pch.h"
#include "Vtb_synth_accelerator__Syms.h"
#include "Vtb_synth_accelerator___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_synth_accelerator___024root___dump_triggers__stl(Vtb_synth_accelerator___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_synth_accelerator___024root___eval_triggers__stl(Vtb_synth_accelerator___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_synth_accelerator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_synth_accelerator___024root___eval_triggers__stl\n"); );
    // Body
    vlSelf->__VstlTriggered.set(0U, (IData)(vlSelf->__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_synth_accelerator___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

VL_ATTR_COLD void Vtb_synth_accelerator___024root___eval_postponed__TOP(Vtb_synth_accelerator___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_synth_accelerator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_synth_accelerator___024root___eval_postponed__TOP\n"); );
    // Body
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(0,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__0__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(1,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [1U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [1U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [1U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [1U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__1__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(2,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [2U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [2U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [2U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [2U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__2__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(3,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [3U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [3U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [3U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [3U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__3__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(4,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [4U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [4U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [4U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [4U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__4__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(5,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [5U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [5U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [5U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [5U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__5__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(6,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [6U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [6U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [6U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [6U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__6__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(7,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [7U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [7U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [7U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [7U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__7__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(8,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [8U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [8U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [8U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [8U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__8__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(9,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [9U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [9U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [9U][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [9U][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__9__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(10,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xaU][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xaU][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xaU][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xaU][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__10__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(11,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xbU][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xbU][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xbU][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xbU][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__11__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(12,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xcU][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xcU][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xcU][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xcU][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__12__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(13,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xdU][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xdU][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xdU][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xdU][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__13__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(14,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xeU][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xeU][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xeU][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xeU][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__14__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,0)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][0U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][0U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__0__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,1)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][1U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][1U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__1__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,2)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][2U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][2U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__2__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,3)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][3U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][3U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__3__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,4)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][4U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][4U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__4__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,5)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][5U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][5U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__5__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,6)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][6U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][6U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__6__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,7)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][7U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][7U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__7__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,8)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][8U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][8U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__8__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,9)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][9U],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][9U],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__9__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,10)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][0xaU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][0xaU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__10__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,11)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][0xbU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][0xbU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__11__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,12)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][0xcU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][0xcU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__12__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,13)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][0xdU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][0xdU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__13__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,14)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][0xeU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][0xeU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__14__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
    if (VL_UNLIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0)) {
        VL_WRITEF("@%0t [PE(15,15)] En:%b|Ain:%4d(v%b) Bin:%4d(v%b)|a_r:%4d b_r:%4d(valid_for_them:%b)|MulOut:%6d|AccProduct:%6d(valid:%b)|AccValue:%11d|MACs:%2# done:%b resVldWillBe:%b\n",
                  64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg),
                  8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_data_wires
                  [0xfU][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__a_valid_wires
                  [0xfU][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_data_wires
                  [0xfU][0xfU],1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__b_valid_wires
                  [0xfU][0xfU],8,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__a_reg,
                  8,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__b_reg),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__inputs_that_produced_a_b_regs_were_valid_reg,
                  16,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_output_data),
                  16,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_result_reg,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg),
                  32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__local_accumulator_reg,
                  5,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count),
                  1,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__pe_calculation_done_latch,
                  1,(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__mul_valid_reg) 
                      & (0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__performed_mac_count))) 
                     & (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT__next_performed_mac_count_w))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_row__BRA__15__KET____DOT__pe_col__BRA__15__KET____DOT__u_pe_inst__DOT____Vstrobe0 = 0U;
    }
}
