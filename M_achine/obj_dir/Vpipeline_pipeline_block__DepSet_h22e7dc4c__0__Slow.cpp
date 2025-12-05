// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline.h for the primary calling header

#include "Vpipeline__pch.h"
#include "Vpipeline_pipeline_block.h"

VL_ATTR_COLD void Vpipeline_pipeline_block___eval_static__TOP__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___eval_static__TOP__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__summand_a = 0U;
    vlSelfRef.__PVT__summand_b = 0U;
    vlSelfRef.__PVT__state = 0U;
}

VL_ATTR_COLD void Vpipeline_pipeline_block___stl_sequent__TOP__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___stl_sequent__TOP__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
    vlSelfRef.ch_out[0U] = vlSelfRef.__PVT__ch_regs
        [0U];
    vlSelfRef.ch_out[1U] = vlSelfRef.__PVT__ch_regs
        [1U];
    vlSelfRef.ch_out[2U] = vlSelfRef.__PVT__ch_regs
        [2U];
    vlSelfRef.ch_out[3U] = vlSelfRef.__PVT__ch_regs
        [3U];
    vlSelfRef.ch_out[4U] = vlSelfRef.__PVT__ch_regs
        [4U];
    vlSelfRef.ch_out[5U] = vlSelfRef.__PVT__ch_regs
        [5U];
    vlSelfRef.ch_out[6U] = vlSelfRef.__PVT__ch_regs
        [6U];
    vlSelfRef.ch_out[7U] = vlSelfRef.__PVT__ch_regs
        [7U];
    vlSelfRef.ch_out[8U] = vlSelfRef.__PVT__ch_regs
        [8U];
    vlSelfRef.ch_out[9U] = vlSelfRef.__PVT__ch_regs
        [9U];
    vlSelfRef.ch_out[0xaU] = vlSelfRef.__PVT__ch_regs
        [0xaU];
    vlSelfRef.ch_out[0xbU] = vlSelfRef.__PVT__ch_regs
        [0xbU];
    vlSelfRef.ch_out[0xcU] = vlSelfRef.__PVT__ch_regs
        [0xcU];
    vlSelfRef.ch_out[0xdU] = vlSelfRef.__PVT__ch_regs
        [0xdU];
    vlSelfRef.ch_out[0xeU] = vlSelfRef.__PVT__ch_regs
        [0xeU];
    vlSelfRef.ch_out[0xfU] = vlSelfRef.__PVT__ch_regs
        [0xfU];
}

VL_ATTR_COLD void Vpipeline_pipeline_block___ctor_var_reset(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___ctor_var_reset\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->tick = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->ch_in[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->ch_out[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->instr_val = VL_RAND_RESET_I(32);
    vlSelf->instr_write = VL_RAND_RESET_I(1);
    vlSelf->reg_val = VL_RAND_RESET_I(16);
    vlSelf->reg_target = VL_RAND_RESET_I(4);
    vlSelf->reg_write = VL_RAND_RESET_I(1);
    vlSelf->mul_req_a = VL_RAND_RESET_I(16);
    vlSelf->mul_req_b = VL_RAND_RESET_I(16);
    vlSelf->mul_result = VL_RAND_RESET_I(32);
    vlSelf->mul_done = VL_RAND_RESET_I(1);
    vlSelf->done = VL_RAND_RESET_I(1);
    vlSelf->__PVT__instr = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->__PVT__ch_regs[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->__PVT__regs[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->__PVT__summand_a = VL_RAND_RESET_I(16);
    vlSelf->__PVT__summand_b = VL_RAND_RESET_I(16);
    vlSelf->__PVT__sum_ext = VL_RAND_RESET_I(17);
    vlSelf->__PVT__sum = VL_RAND_RESET_I(16);
    vlSelf->__PVT__prod = VL_RAND_RESET_I(16);
    vlSelf->__PVT__state = VL_RAND_RESET_I(9);
    vlSelf->__PVT__i = VL_RAND_RESET_I(32);
}
