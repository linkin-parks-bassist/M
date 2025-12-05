// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline.h for the primary calling header

#include "Vpipeline__pch.h"
#include "Vpipeline___024root.h"

VL_ATTR_COLD void Vpipeline___024root___eval_static__TOP(Vpipeline___024root* vlSelf);
VL_ATTR_COLD void Vpipeline___024root____Vm_traceActivitySetAll(Vpipeline___024root* vlSelf);

VL_ATTR_COLD void Vpipeline___024root___eval_static(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_static\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vpipeline___024root___eval_static__TOP(vlSelf);
    Vpipeline___024root____Vm_traceActivitySetAll(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vpipeline___024root___eval_static__TOP(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_static__TOP\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.pipeline__DOT__invalid = 0U;
    vlSelfRef.pipeline__DOT__mul__DOT__index = 1U;
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a = 0U;
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b = 0U;
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 0U;
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a = 0U;
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b = 0U;
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 0U;
}

VL_ATTR_COLD void Vpipeline___024root___eval_initial__TOP(Vpipeline___024root* vlSelf);

VL_ATTR_COLD void Vpipeline___024root___eval_initial(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_initial\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vpipeline___024root___eval_initial__TOP(vlSelf);
}

VL_ATTR_COLD void Vpipeline___024root___eval_initial__TOP(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_initial__TOP\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.pipeline__DOT__bus[0U][1U] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][2U] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][3U] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][4U] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][5U] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][6U] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][7U] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][8U] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][9U] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][0xaU] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][0xbU] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][0xcU] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][0xdU] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][0xeU] = 0U;
    vlSelfRef.pipeline__DOT__bus[0U][0xfU] = 0U;
}

VL_ATTR_COLD void Vpipeline___024root___eval_final(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_final\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpipeline___024root___dump_triggers__stl(Vpipeline___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vpipeline___024root___eval_phase__stl(Vpipeline___024root* vlSelf);

VL_ATTR_COLD void Vpipeline___024root___eval_settle(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_settle\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x64U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vpipeline___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("src/pipeline.v", 627, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vpipeline___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpipeline___024root___dump_triggers__stl(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___dump_triggers__stl\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vpipeline___024root___stl_sequent__TOP__0(Vpipeline___024root* vlSelf);

VL_ATTR_COLD void Vpipeline___024root___eval_stl(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_stl\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vpipeline___024root___stl_sequent__TOP__0(vlSelf);
        Vpipeline___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD void Vpipeline___024root___stl_sequent__TOP__0(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___stl_sequent__TOP__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.error = vlSelfRef.pipeline__DOT__invalid;
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_unified_addr 
        = (0x1fU & ((0x200000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                     ? ((IData)(0x10U) + (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                  >> 5U)))
                     : (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                >> 5U))));
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_unified_addr 
        = (0x1fU & ((0x200000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                     ? ((IData)(0x10U) + (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                  >> 5U)))
                     : (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                >> 5U))));
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_write 
        = ((IData)(vlSelfRef.reg_write) & (~ (IData)(vlSelfRef.block_target)));
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_update 
        = ((IData)(vlSelfRef.reg_update) & (~ (IData)(vlSelfRef.block_target)));
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_write 
        = ((IData)(vlSelfRef.reg_write) & (IData)(vlSelfRef.block_target));
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_update 
        = ((IData)(vlSelfRef.reg_update) & (IData)(vlSelfRef.block_target));
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready 
        = (1U & ((~ (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin)) 
                 & (IData)(vlSelfRef.pipeline__DOT__mul_done)));
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready 
        = ((~ (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin)) 
           & ((IData)(vlSelfRef.pipeline__DOT__mul_done) 
              >> 1U));
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum_ext 
        = (0x1ffffU & (((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a) 
                                     << 1U)) | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a)) 
                       + ((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b) 
                                       << 1U)) | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b))));
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum_ext 
        = (0x1ffffU & (((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a) 
                                     << 1U)) | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a)) 
                       + ((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b) 
                                       << 1U)) | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b))));
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_shifted 
        = VL_SHIFTRS_III(32,32,32, vlSelfRef.pipeline__DOT__mul_result, 
                         ((IData)(0xfU) - ((5U == (0x1fU 
                                                   & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr))
                                            ? 1U : 
                                           (0x1fU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                             >> 0x19U)))));
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_shifted 
        = VL_SHIFTRS_III(32,32,32, vlSelfRef.pipeline__DOT__mul_result, 
                         ((IData)(0xfU) - ((5U == (0x1fU 
                                                   & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr))
                                            ? 1U : 
                                           (0x1fU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                             >> 0x19U)))));
    vlSelfRef.pipeline__DOT__mul_bus_y[0U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b;
    vlSelfRef.pipeline__DOT__mul_bus_y[1U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b;
    vlSelfRef.pipeline__DOT__mul_bus_x[0U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a;
    vlSelfRef.pipeline__DOT__mul_bus_x[1U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a;
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[1U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [1U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[2U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [2U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[3U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [3U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[4U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [4U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[5U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [5U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[6U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [6U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[7U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [7U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[8U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [8U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[9U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [9U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0xaU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0xaU];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0xbU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0xbU];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0xcU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0xcU];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0xdU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0xdU];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0xeU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0xeU];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0xfU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0xfU];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x10U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [0U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x11U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [1U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x12U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [2U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x13U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [3U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x14U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [4U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x15U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [5U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x16U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [6U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x17U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [7U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x18U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [8U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x19U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [9U];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x1aU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [0xaU];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x1bU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [0xbU];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x1cU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [0xcU];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x1dU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [0xdU];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x1eU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [0xeU];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0x1fU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
        [0xfU];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[1U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [1U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[2U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [2U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[3U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [3U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[4U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [4U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[5U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [5U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[6U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [6U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[7U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [7U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[8U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [8U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[9U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [9U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0xaU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0xaU];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0xbU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0xbU];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0xcU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0xcU];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0xdU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0xdU];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0xeU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0xeU];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0xfU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0xfU];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x10U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [0U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x11U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [1U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x12U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [2U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x13U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [3U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x14U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [4U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x15U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [5U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x16U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [6U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x17U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [7U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x18U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [8U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x19U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [9U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x1aU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [0xaU];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x1bU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [0xbU];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x1cU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [0xcU];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x1dU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [0xdU];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x1eU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [0xeU];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0x1fU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
        [0xfU];
    vlSelfRef.pipeline__DOT__bus[0U][0U] = vlSelfRef.in_sample;
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[0U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[1U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [1U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[2U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [2U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[3U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [3U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[4U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [4U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[5U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [5U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[6U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [6U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[7U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [7U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[8U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [8U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[9U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [9U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[0xaU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0xaU];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[0xbU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0xbU];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[0xcU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0xcU];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[0xdU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0xdU];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[0xeU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0xeU];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[0xfU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
        [0xfU];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[0U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[1U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [1U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[2U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [2U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[3U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [3U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[4U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [4U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[5U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [5U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[6U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [6U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[7U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [7U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[8U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [8U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[9U] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [9U];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[0xaU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0xaU];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[0xbU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0xbU];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[0xcU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0xcU];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[0xdU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0xdU];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[0xeU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0xeU];
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[0xfU] 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
        [0xfU];
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final 
        = (VL_LTS_III(32, 0x7fffU, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_shifted)
            ? 0x7fffU : (VL_GTS_III(32, 0xffff8000U, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_shifted)
                          ? 0x8000U : (0xffffU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_shifted)));
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final 
        = (VL_LTS_III(32, 0x7fffU, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_shifted)
            ? 0x7fffU : (VL_GTS_III(32, 0xffff8000U, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_shifted)
                          ? 0x8000U : (0xffffU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_shifted)));
    vlSelfRef.pipeline__DOT____Vcellinp__mul__y[0U] 
        = vlSelfRef.pipeline__DOT__mul_bus_y[0U];
    vlSelfRef.pipeline__DOT____Vcellinp__mul__y[1U] 
        = vlSelfRef.pipeline__DOT__mul_bus_y[1U];
    vlSelfRef.pipeline__DOT____Vcellinp__mul__x[0U] 
        = vlSelfRef.pipeline__DOT__mul_bus_x[0U];
    vlSelfRef.pipeline__DOT____Vcellinp__mul__x[1U] 
        = vlSelfRef.pipeline__DOT__mul_bus_x[1U];
    vlSelfRef.pipeline__DOT__bus[1U][0U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [0U];
    vlSelfRef.pipeline__DOT__bus[1U][1U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [1U];
    vlSelfRef.pipeline__DOT__bus[1U][2U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [2U];
    vlSelfRef.pipeline__DOT__bus[1U][3U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [3U];
    vlSelfRef.pipeline__DOT__bus[1U][4U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [4U];
    vlSelfRef.pipeline__DOT__bus[1U][5U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [5U];
    vlSelfRef.pipeline__DOT__bus[1U][6U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [6U];
    vlSelfRef.pipeline__DOT__bus[1U][7U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [7U];
    vlSelfRef.pipeline__DOT__bus[1U][8U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [8U];
    vlSelfRef.pipeline__DOT__bus[1U][9U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [9U];
    vlSelfRef.pipeline__DOT__bus[1U][0xaU] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [0xaU];
    vlSelfRef.pipeline__DOT__bus[1U][0xbU] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [0xbU];
    vlSelfRef.pipeline__DOT__bus[1U][0xcU] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [0xcU];
    vlSelfRef.pipeline__DOT__bus[1U][0xdU] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [0xdU];
    vlSelfRef.pipeline__DOT__bus[1U][0xeU] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [0xeU];
    vlSelfRef.pipeline__DOT__bus[1U][0xfU] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out
        [0xfU];
    vlSelfRef.pipeline__DOT__bus[2U][0U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [0U];
    vlSelfRef.pipeline__DOT__bus[2U][1U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [1U];
    vlSelfRef.pipeline__DOT__bus[2U][2U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [2U];
    vlSelfRef.pipeline__DOT__bus[2U][3U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [3U];
    vlSelfRef.pipeline__DOT__bus[2U][4U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [4U];
    vlSelfRef.pipeline__DOT__bus[2U][5U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [5U];
    vlSelfRef.pipeline__DOT__bus[2U][6U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [6U];
    vlSelfRef.pipeline__DOT__bus[2U][7U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [7U];
    vlSelfRef.pipeline__DOT__bus[2U][8U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [8U];
    vlSelfRef.pipeline__DOT__bus[2U][9U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [9U];
    vlSelfRef.pipeline__DOT__bus[2U][0xaU] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [0xaU];
    vlSelfRef.pipeline__DOT__bus[2U][0xbU] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [0xbU];
    vlSelfRef.pipeline__DOT__bus[2U][0xcU] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [0xcU];
    vlSelfRef.pipeline__DOT__bus[2U][0xdU] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [0xdU];
    vlSelfRef.pipeline__DOT__bus[2U][0xeU] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [0xeU];
    vlSelfRef.pipeline__DOT__bus[2U][0xfU] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out
        [0xfU];
    vlSelfRef.out_sample = vlSelfRef.pipeline__DOT__bus
        [2U][0U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.pipeline__DOT__bus[0U][0U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.pipeline__DOT__bus[0U][1U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.pipeline__DOT__bus[0U][2U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.pipeline__DOT__bus[0U][3U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.pipeline__DOT__bus[0U][4U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.pipeline__DOT__bus[0U][5U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.pipeline__DOT__bus[0U][6U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.pipeline__DOT__bus[0U][7U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.pipeline__DOT__bus[0U][8U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.pipeline__DOT__bus[0U][9U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.pipeline__DOT__bus[0U][0xaU];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.pipeline__DOT__bus[0U][0xbU];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.pipeline__DOT__bus[0U][0xcU];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.pipeline__DOT__bus[0U][0xdU];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.pipeline__DOT__bus[0U][0xeU];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.pipeline__DOT__bus[0U][0xfU];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.pipeline__DOT__bus[1U][0U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.pipeline__DOT__bus[1U][1U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.pipeline__DOT__bus[1U][2U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.pipeline__DOT__bus[1U][3U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.pipeline__DOT__bus[1U][4U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.pipeline__DOT__bus[1U][5U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.pipeline__DOT__bus[1U][6U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.pipeline__DOT__bus[1U][7U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.pipeline__DOT__bus[1U][8U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.pipeline__DOT__bus[1U][9U];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.pipeline__DOT__bus[1U][0xaU];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.pipeline__DOT__bus[1U][0xbU];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.pipeline__DOT__bus[1U][0xcU];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.pipeline__DOT__bus[1U][0xdU];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.pipeline__DOT__bus[1U][0xeU];
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.pipeline__DOT__bus[1U][0xfU];
}

VL_ATTR_COLD void Vpipeline___024root___eval_triggers__stl(Vpipeline___024root* vlSelf);

VL_ATTR_COLD bool Vpipeline___024root___eval_phase__stl(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_phase__stl\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vpipeline___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vpipeline___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpipeline___024root___dump_triggers__ico(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___dump_triggers__ico\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpipeline___024root___dump_triggers__act(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___dump_triggers__act\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpipeline___024root___dump_triggers__nba(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___dump_triggers__nba\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vpipeline___024root____Vm_traceActivitySetAll(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root____Vm_traceActivitySetAll\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
}

VL_ATTR_COLD void Vpipeline___024root___ctor_var_reset(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___ctor_var_reset\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->in_sample = VL_RAND_RESET_I(16);
    vlSelf->in_valid = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->out_sample = VL_RAND_RESET_I(16);
    vlSelf->ready = VL_RAND_RESET_I(1);
    vlSelf->block_target = VL_RAND_RESET_I(1);
    vlSelf->reg_target = VL_RAND_RESET_I(4);
    vlSelf->instr_val = VL_RAND_RESET_I(32);
    vlSelf->instr_write = VL_RAND_RESET_I(1);
    vlSelf->reg_val = VL_RAND_RESET_I(16);
    vlSelf->reg_update = VL_RAND_RESET_I(1);
    vlSelf->reg_write = VL_RAND_RESET_I(1);
    vlSelf->error = VL_RAND_RESET_I(1);
    vlSelf->pipeline__DOT__sample_latched = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__state = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__ctr = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__invalid = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 16; ++__Vi1) {
            vlSelf->pipeline__DOT__bus[__Vi0][__Vi1] = VL_RAND_RESET_I(16);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->pipeline__DOT__mul_bus_x[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->pipeline__DOT__mul_bus_y[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->pipeline__DOT__mul_result = VL_RAND_RESET_I(32);
    vlSelf->pipeline__DOT__mul_done = VL_RAND_RESET_I(2);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->pipeline__DOT____Vcellinp__mul__y[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->pipeline__DOT____Vcellinp__mul__x[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done = VL_RAND_RESET_I(1);
    vlSelf->pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_update = VL_RAND_RESET_I(1);
    vlSelf->pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_write = VL_RAND_RESET_I(1);
    vlSelf->pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a = VL_RAND_RESET_I(16);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done = VL_RAND_RESET_I(1);
    vlSelf->pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_update = VL_RAND_RESET_I(1);
    vlSelf->pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_write = VL_RAND_RESET_I(1);
    vlSelf->pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a = VL_RAND_RESET_I(16);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->pipeline__DOT__mul__DOT__index = VL_RAND_RESET_I(1);
    vlSelf->pipeline__DOT__mul__DOT__i = VL_RAND_RESET_I(32);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_unified_addr = VL_RAND_RESET_I(5);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_latched = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_b_latched = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_c_latched = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum_ext = VL_RAND_RESET_I(17);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_shifted = VL_RAND_RESET_I(32);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = VL_RAND_RESET_I(1);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready = VL_RAND_RESET_I(1);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = VL_RAND_RESET_I(9);
    vlSelf->pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__i = VL_RAND_RESET_I(32);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[__Vi0] = VL_RAND_RESET_I(16);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[__Vi0] = VL_RAND_RESET_I(16);
    }
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_unified_addr = VL_RAND_RESET_I(5);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_latched = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_b_latched = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_c_latched = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum_ext = VL_RAND_RESET_I(17);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_shifted = VL_RAND_RESET_I(32);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod = VL_RAND_RESET_I(16);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = VL_RAND_RESET_I(1);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready = VL_RAND_RESET_I(1);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = VL_RAND_RESET_I(9);
    vlSelf->pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__i = VL_RAND_RESET_I(32);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
