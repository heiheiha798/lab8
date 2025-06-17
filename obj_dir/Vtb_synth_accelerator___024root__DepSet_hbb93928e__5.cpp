// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_synth_accelerator.h for the primary calling header

#include "Vtb_synth_accelerator__pch.h"
#include "Vtb_synth_accelerator___024root.h"

VL_INLINE_OPT void Vtb_synth_accelerator___024root___nba_sequent__TOP__523(Vtb_synth_accelerator___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_synth_accelerator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_synth_accelerator___024root___nba_sequent__TOP__523\n"); );
    // Body
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 1U;
    if (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_enable_output_reg) {
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [0U]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [1U]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [2U]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [3U]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [4U]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [5U]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [6U]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [7U]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [8U]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [9U]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [0xaU]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [0xbU]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [0xcU]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [0xdU]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [0xeU]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
        if ((1U & (~ vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__pe_done_flags
                   [vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg]
                   [0xfU]))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
        }
    } else {
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done = 0U;
    }
}

VL_INLINE_OPT void Vtb_synth_accelerator___024root___nba_comb__TOP__2(Vtb_synth_accelerator___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_synth_accelerator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_synth_accelerator___024root___nba_comb__TOP__2\n"); );
    // Init
    QData/*63:0*/ tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb;
    tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb = 0;
    // Body
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__r_c_idx_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__r_c_idx_reg;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_c_idx_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_c_idx_reg;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_reg;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_addr_o_next_comb 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_mm_addr_r;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_reg;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_a_col_element_idx_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_a_col_element_idx_r;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sint8_offset_in_word_a_for_unpack_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sint8_offset_in_word_a_for_unpack_r;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__a_element_idx_for_unpack_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__a_element_idx_for_unpack_r;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__do_unpack_a_pulse_next = 0U;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__b_sram_word_idx_in_row_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__b_sram_word_idx_in_row_r;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__b_sram_word_idx_for_unpack_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__b_sram_word_idx_for_unpack_r;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__do_unpack_b_pulse_next = 0U;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_total_cycles_count_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_total_cycles_count_reg;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_row_read_idx_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_row_read_idx_reg;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_cs_o_next_comb = 0U;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_we_o_next_comb = 0U;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_wdata_o_next_comb 
        = vlSelf->tb_synth_accelerator__DOT__mm_wdata_o_w;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_cs_o_next_comb = 0U;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_we_o_next_comb = 0U;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_addr_o_next_comb 
        = vlSelf->tb_synth_accelerator__DOT__tile_a_sram_addr_o_w;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_wdata_o_next_comb 
        = vlSelf->tb_synth_accelerator__DOT__tile_a_sram_wdata_o_w;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_cs_o_next_comb = 0U;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_we_o_next_comb = 0U;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_addr_o_next_comb 
        = vlSelf->tb_synth_accelerator__DOT__tile_b_sram_addr_o_w;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_wdata_o_next_comb 
        = vlSelf->tb_synth_accelerator__DOT__tile_b_sram_wdata_o_w;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_clear_accum_pulse_next = 0U;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_start_new_pass_pulse_next = 0U;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__computation_done_next_comb = 0U;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_cond_clear_sum_level_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_cond_clear_sum_level_reg;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_reg;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_enable_output_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_enable_output_reg;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg;
    tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb = 0ULL;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_a_col_filled_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_a_col_filled_r;
    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_b_row_filled_next 
        = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_b_row_filled_r;
    if (((((((((0U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg)) 
               | (1U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
              | (2U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
             | (3U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
            | (4U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
           | (5U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
          | (6U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
         | (7U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg)))) {
        if ((0U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_enable_output_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 0U;
            if (vlSelf->tb_synth_accelerator__DOT__start_computation_tb) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 1U;
            }
        } else if ((1U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__r_c_idx_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_c_idx_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 2U;
        } else if ((2U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_cond_clear_sum_level_next 
                = (1U & (~ (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_reg)));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_clear_accum_pulse_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_start_new_pass_pulse_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 3U;
        } else if ((3U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_addr_o_next_comb 
                = (0x3ffffU & VL_SHIFTL_III(18,32,32, 
                                            (VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__r_c_idx_reg), 1U) 
                                             + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_reg)), 5U));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 4U;
        } else if ((4U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            if ((0x20U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_reg))) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_cs_o_next_comb = 1U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_we_o_next_comb = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_addr_o_next_comb 
                    = (0x3ffffU & (VL_SHIFTL_III(18,32,32, 
                                                 (VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__r_c_idx_reg), 1U) 
                                                  + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_reg)), 5U) 
                                   + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_reg)));
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 5U;
            } else {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 7U;
            }
        } else if ((5U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_cs_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__mm_cs_o_w;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_addr_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__mm_addr_o_w;
            if (vlSelf->tb_synth_accelerator__DOT__mm_ready_i_tb) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_cs_o_next_comb = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 6U;
            } else {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 5U;
            }
        } else if ((6U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_cs_o_next_comb = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_we_o_next_comb = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_addr_o_next_comb 
                = (0x1fU & (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_reg));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_wdata_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__latched_mm_rdata_r;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_next 
                = (0x7fU & ((IData)(1U) + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_reg)));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 4U;
        } else {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_addr_o_next_comb 
                = (0x3ffffU & ((IData)(0x80U) + VL_SHIFTL_III(18,32,32, 
                                                              (VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_reg), 1U) 
                                                               + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_c_idx_reg)), 5U)));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 8U;
        }
    } else if (((((((((8U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg)) 
                      | (9U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
                     | (0xaU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
                    | (0xbU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
                   | (0x16U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
                  | (0x17U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
                 | (0x18U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
                | (0x19U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg)))) {
        if ((8U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            if ((0x20U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_reg))) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_cs_o_next_comb = 1U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_we_o_next_comb = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_addr_o_next_comb 
                    = (0x3ffffU & ((IData)(0x80U) + 
                                   (VL_SHIFTL_III(18,32,32, 
                                                  (VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_reg), 1U) 
                                                   + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_c_idx_reg)), 5U) 
                                    + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_reg))));
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 9U;
            } else {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0xbU;
            }
        } else if ((9U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_cs_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__mm_cs_o_w;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_addr_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__mm_addr_o_w;
            if (vlSelf->tb_synth_accelerator__DOT__mm_ready_i_tb) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_cs_o_next_comb = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0xaU;
            } else {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 9U;
            }
        } else if ((0xaU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_cs_o_next_comb = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_we_o_next_comb = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_addr_o_next_comb 
                = (0x1fU & (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_reg));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_wdata_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__latched_mm_rdata_r;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_next 
                = (0x7fU & ((IData)(1U) + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_reg)));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 8U;
        } else if ((0xbU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_total_cycles_count_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_a_col_element_idx_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__b_sram_word_idx_in_row_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_a_col_filled_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_b_row_filled_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x16U;
        } else if ((0x16U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_a_element_row_idx_local 
                = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_a_col_element_idx_r;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_cs_o_next_comb = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_we_o_next_comb = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x17U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_a_fixed_col_idx_local 
                = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_total_cycles_count_reg;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__element_linear_offset_a_local 
                = (VL_MULS_III(32, (IData)(0x10U), vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_a_element_row_idx_local) 
                   + vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_a_fixed_col_idx_local);
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sram_word_addr_a_local 
                = VL_DIVS_III(32, vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__element_linear_offset_a_local, (IData)(8U));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__offset_in_word_a_local 
                = VL_MODDIVS_III(32, vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__element_linear_offset_a_local, (IData)(8U));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_addr_o_next_comb 
                = (0x1fU & vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sram_word_addr_a_local);
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__a_element_idx_for_unpack_next 
                = (0xfU & vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_a_element_row_idx_local);
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sint8_offset_in_word_a_for_unpack_next 
                = (7U & vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__offset_in_word_a_local);
        } else if ((0x17U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_cs_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__tile_a_sram_cs_o_w;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_addr_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__tile_a_sram_addr_o_w;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x18U;
        } else if ((0x18U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_cs_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__tile_a_sram_cs_o_w;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_a_sram_addr_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__tile_a_sram_addr_o_w;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__do_unpack_a_pulse_next = 1U;
            if ((0xfU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_a_col_element_idx_r))) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_a_col_filled_next = 1U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x19U;
            } else {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_a_col_element_idx_next 
                    = (0xfU & ((IData)(1U) + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_a_col_element_idx_r)));
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x16U;
            }
        } else {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__base_sram_addr_for_row_b_local 
                = (0x1ffffffeU & VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_total_cycles_count_reg), 1U));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_addr_o_next_comb 
                = (0x1fU & (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__base_sram_addr_for_row_b_local 
                            + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__b_sram_word_idx_in_row_r)));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_cs_o_next_comb = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_we_o_next_comb = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__b_sram_word_idx_for_unpack_next 
                = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__b_sram_word_idx_in_row_r;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x1aU;
        }
    } else if (((((((((0x1aU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg)) 
                      | (0x1bU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
                     | (0x1cU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
                    | (0xcU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
                   | (0xdU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
                  | (0xeU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
                 | (0xfU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) 
                | (0x10U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg)))) {
        if ((0x1aU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_cs_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__tile_b_sram_cs_o_w;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_addr_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__tile_b_sram_addr_o_w;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x1bU;
        } else if ((0x1bU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_cs_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__tile_b_sram_cs_o_w;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__tile_b_sram_addr_o_next_comb 
                = vlSelf->tb_synth_accelerator__DOT__tile_b_sram_addr_o_w;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__do_unpack_b_pulse_next = 1U;
            if ((1U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__b_sram_word_idx_in_row_r))) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_b_row_filled_next = 1U;
                if (VL_LIKELY(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_a_col_filled_r)) {
                    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x1cU;
                } else {
                    VL_WRITEF("[%0t ACCEL_WARN CYC:%0d] In B_LATCH (all words done), but A_col not filled! Goto PRE_EXEC_CHECK.\n",
                              64,VL_TIME_UNITED_Q(1000),
                              -9,32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__cycle_count);
                    vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x1cU;
                }
            } else {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__b_sram_word_idx_in_row_next 
                    = (0x1fU & ((IData)(1U) + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__b_sram_word_idx_in_row_r)));
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x19U;
            }
        } else if ((0x1cU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg 
                = (((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_a_col_filled_r) 
                    & (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_b_row_filled_r))
                    ? 0xcU : 0x1cU);
        } else if ((0xcU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            if ((0xfU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_total_cycles_count_reg))) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0xdU;
            } else {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_total_cycles_count_next 
                    = (0x1fU & ((IData)(1U) + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_total_cycles_count_reg)));
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_a_col_filled_next = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__temp_b_row_filled_next = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_feed_a_col_element_idx_next = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__b_sram_word_idx_in_row_next = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x16U;
            }
        } else if ((0xdU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 1U;
            if (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__all_pes_in_tile_done_reduction) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0xeU;
            } else {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0xdU;
            }
        } else if ((0xeU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 0U;
            if (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_reg) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_next = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_row_read_idx_next = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0xfU;
            } else {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_next 
                    = (1U & ((IData)(1U) + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_reg)));
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 2U;
            }
        } else if ((0xfU == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_addr_o_next_comb 
                = (0x3ffffU & ((IData)(0x100U) + VL_SHIFTL_III(18,32,32, 
                                                               (VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__r_c_idx_reg), 1U) 
                                                                + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_c_idx_reg)), 7U)));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_row_read_idx_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x10U;
        } else {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 0U;
            if ((0x10U > (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_row_read_idx_reg))) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_enable_output_next = 1U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_next 
                    = (0xfU & (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_row_read_idx_reg));
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x14U;
            } else {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_enable_output_next = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x12U;
            }
        }
    } else if ((0x14U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 0U;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_enable_output_next = 1U;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_next 
            = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg;
        if (VL_UNLIKELY(((IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_enable_output_reg) 
                         & (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__selected_row_all_pes_done)))) {
            VL_WRITEF("[%0t ACCEL_C_READ CYC:%0d] Row %2# valid from SA. SA_Result_Bus = %x\n",
                      64,VL_TIME_UNITED_Q(1000),-9,
                      32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__cycle_count,
                      4,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg),
                      512,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__tile_row_result_out__out__strong__out0.data());
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x11U;
        } else {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x14U;
        }
    } else if (VL_UNLIKELY((0x11U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg)))) {
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 0U;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_enable_output_next = 1U;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_next 
            = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg;
        VL_WRITEF("[%0t ACCEL_PACK_INPUTS CYC:%0d] State:WRITE_REQ. SA_Enable_Reg=%b, SA_Select_Reg=%2#, SA_Result_Bus_RAW=%x, c_store_word_idx=%1#\n",
                  64,VL_TIME_UNITED_Q(1000),-9,32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__cycle_count,
                  1,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_enable_output_reg),
                  4,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg,
                  512,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__tile_row_result_out__out__strong__out0.data(),
                  3,(IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_cs_o_next_comb = 1U;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_we_o_next_comb = 1U;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_addr_o_next_comb 
            = (0x3ffffU & ((IData)(0x100U) + (VL_SHIFTL_III(18,32,32, 
                                                            (VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__r_c_idx_reg), 1U) 
                                                             + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_c_idx_reg)), 7U) 
                                              + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_reg))));
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x15U;
        tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb 
            = ((0xffffffff00000000ULL & tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb) 
               | (IData)((IData)(((0x10U > VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U))
                                   ? (((0U == (0x1fU 
                                               & VL_SHIFTL_III(9,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 6U)))
                                        ? 0U : (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__tile_row_result_out__out__strong__out0[
                                                (((IData)(0x1fU) 
                                                  + 
                                                  (0x1ffU 
                                                   & VL_SHIFTL_III(9,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 6U))) 
                                                 >> 5U)] 
                                                << 
                                                ((IData)(0x20U) 
                                                 - 
                                                 (0x1fU 
                                                  & VL_SHIFTL_III(9,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 6U))))) 
                                      | (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__tile_row_result_out__out__strong__out0[
                                         (0xfU & (VL_SHIFTL_III(9,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 6U) 
                                                  >> 5U))] 
                                         >> (0x1fU 
                                             & VL_SHIFTL_III(9,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 6U))))
                                   : 0U))));
        tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb 
            = ((0xffffffffULL & tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb) 
               | ((QData)((IData)(((0x10U > ((IData)(1U) 
                                             + VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U)))
                                    ? (((0U == (0x1fU 
                                                & VL_SHIFTL_III(9,32,32, 
                                                                ((IData)(1U) 
                                                                 + 
                                                                 VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U)), 5U)))
                                         ? 0U : (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__tile_row_result_out__out__strong__out0[
                                                 (((IData)(0x1fU) 
                                                   + 
                                                   (0x1ffU 
                                                    & VL_SHIFTL_III(9,32,32, 
                                                                    ((IData)(1U) 
                                                                     + 
                                                                     VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U)), 5U))) 
                                                  >> 5U)] 
                                                 << 
                                                 ((IData)(0x20U) 
                                                  - 
                                                  (0x1fU 
                                                   & VL_SHIFTL_III(9,32,32, 
                                                                   ((IData)(1U) 
                                                                    + 
                                                                    VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U)), 5U))))) 
                                       | (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__tile_row_result_out__out__strong__out0[
                                          (0xfU & (
                                                   VL_SHIFTL_III(9,32,32, 
                                                                 ((IData)(1U) 
                                                                  + 
                                                                  VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U)), 5U) 
                                                   >> 5U))] 
                                          >> (0x1fU 
                                              & VL_SHIFTL_III(9,32,32, 
                                                              ((IData)(1U) 
                                                               + 
                                                               VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U)), 5U))))
                                    : 0U))) << 0x20U));
        VL_WRITEF("[%0t ACCEL_MM_WDATA_PREP CYC:%0d] State:WRITE_REQ. BEFORE assignment to mm_wdata_o_next_comb, packed_c_word_comb = %x\n",
                  64,VL_TIME_UNITED_Q(1000),-9,32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__cycle_count,
                  64,tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb);
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_wdata_o_next_comb 
            = tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb;
        VL_WRITEF("[%0t ACCEL_MM_WDATA_PREP CYC:%0d] State:WRITE_REQ. AFTER assignment, mm_wdata_o_next_comb = %x\n",
                  64,VL_TIME_UNITED_Q(1000),-9,32,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__cycle_count,
                  64,vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_wdata_o_next_comb);
    } else if ((0x15U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 0U;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_enable_output_next = 1U;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_next 
            = vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_select_row_reg;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_cs_o_next_comb 
            = vlSelf->tb_synth_accelerator__DOT__mm_cs_o_w;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_addr_o_next_comb 
            = vlSelf->tb_synth_accelerator__DOT__mm_addr_o_w;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_we_o_next_comb 
            = vlSelf->tb_synth_accelerator__DOT__mm_we_o_w;
        if (vlSelf->tb_synth_accelerator__DOT__mm_ready_i_tb) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_cs_o_next_comb = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_we_o_next_comb = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_next 
                = (0x7fU & ((IData)(1U) + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__mm_word_count_reg)));
            if ((7U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg))) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_row_read_idx_next 
                    = (0x1fU & ((IData)(1U) + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_row_read_idx_reg)));
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_next = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x10U;
            } else {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_next 
                    = (7U & ((IData)(1U) + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg)));
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x11U;
            }
        } else {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x15U;
        }
    } else if ((0x12U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 0U;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_enable_output_next = 0U;
        if (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_c_idx_reg) {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_c_idx_next = 0U;
            if (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__r_c_idx_reg) {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0x13U;
            } else {
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__r_c_idx_next 
                    = (1U & ((IData)(1U) + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__r_c_idx_reg)));
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_next = 0U;
                vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 2U;
            }
        } else {
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_c_idx_next 
                = (1U & ((IData)(1U) + (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_c_idx_reg)));
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__k_idx_next = 0U;
            vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 2U;
        }
    } else if ((0x13U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg))) {
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 0U;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__computation_done_next_comb = 1U;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0U;
    } else {
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__sa_activate_comp_next = 0U;
        vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__next_state_reg = 0U;
    }
    if (((0x11U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg)) 
         | (0x14U == (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__current_state_reg)))) {
        tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb 
            = ((0xffffffff00000000ULL & tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb) 
               | (IData)((IData)(((0x10U > VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U))
                                   ? (((0U == (0x1fU 
                                               & VL_SHIFTL_III(9,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 6U)))
                                        ? 0U : (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__tile_row_result_out__out__strong__out0[
                                                (((IData)(0x1fU) 
                                                  + 
                                                  (0x1ffU 
                                                   & VL_SHIFTL_III(9,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 6U))) 
                                                 >> 5U)] 
                                                << 
                                                ((IData)(0x20U) 
                                                 - 
                                                 (0x1fU 
                                                  & VL_SHIFTL_III(9,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 6U))))) 
                                      | (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__tile_row_result_out__out__strong__out0[
                                         (0xfU & (VL_SHIFTL_III(9,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 6U) 
                                                  >> 5U))] 
                                         >> (0x1fU 
                                             & VL_SHIFTL_III(9,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 6U))))
                                   : 0U))));
        tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb 
            = ((0xffffffffULL & tb_synth_accelerator__DOT__u_accelerator_inst__DOT__packed_c_word_comb) 
               | ((QData)((IData)(((0x10U > ((IData)(1U) 
                                             + VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U)))
                                    ? (((0U == (0x1fU 
                                                & VL_SHIFTL_III(9,32,32, 
                                                                ((IData)(1U) 
                                                                 + 
                                                                 VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U)), 5U)))
                                         ? 0U : (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__tile_row_result_out__out__strong__out0[
                                                 (((IData)(0x1fU) 
                                                   + 
                                                   (0x1ffU 
                                                    & VL_SHIFTL_III(9,32,32, 
                                                                    ((IData)(1U) 
                                                                     + 
                                                                     VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U)), 5U))) 
                                                  >> 5U)] 
                                                 << 
                                                 ((IData)(0x20U) 
                                                  - 
                                                  (0x1fU 
                                                   & VL_SHIFTL_III(9,32,32, 
                                                                   ((IData)(1U) 
                                                                    + 
                                                                    VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U)), 5U))))) 
                                       | (vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__u_systolic_array__DOT__tile_row_result_out__out__strong__out0[
                                          (0xfU & (
                                                   VL_SHIFTL_III(9,32,32, 
                                                                 ((IData)(1U) 
                                                                  + 
                                                                  VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U)), 5U) 
                                                   >> 5U))] 
                                          >> (0x1fU 
                                              & VL_SHIFTL_III(9,32,32, 
                                                              ((IData)(1U) 
                                                               + 
                                                               VL_SHIFTL_III(32,32,32, (IData)(vlSelf->tb_synth_accelerator__DOT__u_accelerator_inst__DOT__c_store_word_in_row_idx_reg), 1U)), 5U))))
                                    : 0U))) << 0x20U));
    }
}

void Vtb_synth_accelerator___024root___timing_resume(Vtb_synth_accelerator___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_synth_accelerator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_synth_accelerator___024root___timing_resume\n"); );
    // Body
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hab3387cb__0.resume("@([changed] tb_synth_accelerator.computation_done_tb)");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VdlySched.resume();
    }
}

void Vtb_synth_accelerator___024root___timing_commit(Vtb_synth_accelerator___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_synth_accelerator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_synth_accelerator___024root___timing_commit\n"); );
    // Body
    if ((! (4ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hab3387cb__0.commit("@([changed] tb_synth_accelerator.computation_done_tb)");
    }
}

void Vtb_synth_accelerator___024root___eval_triggers__act(Vtb_synth_accelerator___024root* vlSelf);
void Vtb_synth_accelerator___024root___eval_act(Vtb_synth_accelerator___024root* vlSelf);

bool Vtb_synth_accelerator___024root___eval_phase__act(Vtb_synth_accelerator___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_synth_accelerator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_synth_accelerator___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<3> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_synth_accelerator___024root___eval_triggers__act(vlSelf);
    Vtb_synth_accelerator___024root___timing_commit(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vtb_synth_accelerator___024root___timing_resume(vlSelf);
        Vtb_synth_accelerator___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

void Vtb_synth_accelerator___024root___eval_nba(Vtb_synth_accelerator___024root* vlSelf);

bool Vtb_synth_accelerator___024root___eval_phase__nba(Vtb_synth_accelerator___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_synth_accelerator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_synth_accelerator___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtb_synth_accelerator___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_synth_accelerator___024root___dump_triggers__nba(Vtb_synth_accelerator___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_synth_accelerator___024root___dump_triggers__act(Vtb_synth_accelerator___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void Vtb_synth_accelerator___024root___eval_postponed(Vtb_synth_accelerator___024root* vlSelf);

void Vtb_synth_accelerator___024root___eval(Vtb_synth_accelerator___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_synth_accelerator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_synth_accelerator___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vtb_synth_accelerator___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("tb_synth_accelerator.v", 4, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vtb_synth_accelerator___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("tb_synth_accelerator.v", 4, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vtb_synth_accelerator___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vtb_synth_accelerator___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
    Vtb_synth_accelerator___024root___eval_postponed(vlSelf);
}

#ifdef VL_DEBUG
void Vtb_synth_accelerator___024root___eval_debug_assertions(Vtb_synth_accelerator___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_synth_accelerator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_synth_accelerator___024root___eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG
