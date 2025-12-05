// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline.h for the primary calling header

#include "Vpipeline__pch.h"
#include "Vpipeline___024root.h"

void Vpipeline___024root___ico_sequent__TOP__0(Vpipeline___024root* vlSelf);

void Vpipeline___024root___eval_ico(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_ico\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vpipeline___024root___ico_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

VL_INLINE_OPT void Vpipeline___024root___ico_sequent__TOP__0(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___ico_sequent__TOP__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_write 
        = ((IData)(vlSelfRef.reg_write) & (~ (IData)(vlSelfRef.block_target)));
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_update 
        = ((IData)(vlSelfRef.reg_update) & (~ (IData)(vlSelfRef.block_target)));
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_write 
        = ((IData)(vlSelfRef.reg_write) & (IData)(vlSelfRef.block_target));
    vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_update 
        = ((IData)(vlSelfRef.reg_update) & (IData)(vlSelfRef.block_target));
    vlSelfRef.pipeline__DOT__bus[0U][0U] = vlSelfRef.in_sample;
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

void Vpipeline___024root___eval_triggers__ico(Vpipeline___024root* vlSelf);

bool Vpipeline___024root___eval_phase__ico(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_phase__ico\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vpipeline___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vpipeline___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vpipeline___024root___eval_act(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_act\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vpipeline___024root___nba_sequent__TOP__0(Vpipeline___024root* vlSelf);

void Vpipeline___024root___eval_nba(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_nba\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vpipeline___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
}

VL_INLINE_OPT void Vpipeline___024root___nba_sequent__TOP__0(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___nba_sequent__TOP__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__is_reg;
    __Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__is_reg = 0;
    CData/*4:0*/ __Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__uaddr;
    __Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__uaddr = 0;
    SData/*15:0*/ __Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__value;
    __Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__value = 0;
    CData/*0:0*/ __Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__is_reg;
    __Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__is_reg = 0;
    CData/*4:0*/ __Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__uaddr;
    __Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__uaddr = 0;
    SData/*15:0*/ __Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__value;
    __Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__value = 0;
    SData/*15:0*/ __Vdly__pipeline__DOT__state;
    __Vdly__pipeline__DOT__state = 0;
    CData/*0:0*/ __Vdly__pipeline__DOT__mul__DOT__index;
    __Vdly__pipeline__DOT__mul__DOT__index = 0;
    SData/*8:0*/ __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state;
    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 0;
    CData/*0:0*/ __Vdly__pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done;
    __Vdly__pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done = 0;
    SData/*15:0*/ __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod;
    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod = 0;
    SData/*15:0*/ __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_latched;
    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_latched = 0;
    SData/*8:0*/ __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state;
    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 0;
    CData/*0:0*/ __Vdly__pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done;
    __Vdly__pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done = 0;
    SData/*15:0*/ __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod;
    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod = 0;
    SData/*15:0*/ __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_latched;
    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_latched = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v1;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v1 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v0;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v0 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v0;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v0 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v0;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v0;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v1;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v1;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v2;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v2;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v1;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v1 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v1;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v1;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v3;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v3 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v3;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v4;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v4 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v4;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v4 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v2;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v2 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v2;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v2 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v2;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v5;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v5 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v5;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v6;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v6 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v6;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v6 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v3;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v3 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v3;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v3 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v3;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v7;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v7 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v7;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v8;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v8 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v8;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v8 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v4;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v4 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v4;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v4 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v4;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v9;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v9 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v9;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v10;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v10 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v10;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v10 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v5;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v5 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v5;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v5 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v5;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v11;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v11 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v11;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v12;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v12 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v12;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v12 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v6;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v6 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v6;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v6 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v6;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v13;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v13 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v13;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v14;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v14 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v14;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v14 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v7;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v7 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v7;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v7 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v7;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v15;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v15 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v15;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v16;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v16 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v16;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v16 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v8;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v8 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v8;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v8 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v8;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v17;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v17 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v17;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v17 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v18;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v18 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v18;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v18 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v9;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v9 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v9;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v9 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v9;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v19;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v19 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v19;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v19 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v20;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v20 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v20;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v20 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v10;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v10 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v10;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v10 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v10;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v21;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v21 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v21;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v21 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v22;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v22 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v22;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v22 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v11;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v11 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v11;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v11 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v11;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v23;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v23 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v23;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v23 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v24;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v24 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v24;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v24 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v12;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v12 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v12;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v12 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v12;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v25;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v25 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v25;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v25 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v26;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v26 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v26;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v26 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v13;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v13 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v13;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v13 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v13;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v27;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v27 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v27;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v27 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v28;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v28 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v28;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v28 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v14;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v14 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v14;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v14 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v14;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v29;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v29 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v29;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v29 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v30;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v30 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v30;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v30 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v15;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v15 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v15;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v15 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v15;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v31;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v31 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v31;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v31 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v32;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v32 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v32;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v32 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v16;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v16 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v38;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v38 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v38;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v38 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v39;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v39 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v39;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v39 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v40;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v40 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v40;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v40 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v41;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v41 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v41;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v41 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21;
    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v43;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v43 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v43;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v43 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v44;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v44 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v45;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v45 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v46;
    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v46 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v22;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v22 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v1;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v1 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v0;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v0 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v0;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v0 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v0;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v0;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v1;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v1;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v2;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v2;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v1;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v1 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v1;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v1;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v3;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v3 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v3;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v4;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v4 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v4;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v4 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v2;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v2 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v2;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v2 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v2;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v5;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v5 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v5;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v6;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v6 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v6;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v6 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v3;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v3 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v3;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v3 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v3;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v7;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v7 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v7;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v8;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v8 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v8;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v8 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v4;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v4 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v4;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v4 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v4;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v9;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v9 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v9;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v10;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v10 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v10;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v10 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v5;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v5 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v5;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v5 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v5;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v11;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v11 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v11;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v12;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v12 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v12;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v12 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v6;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v6 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v6;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v6 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v6;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v13;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v13 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v13;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v14;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v14 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v14;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v14 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v7;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v7 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v7;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v7 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v7;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v15;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v15 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v15;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v16;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v16 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v16;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v16 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v8;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v8 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v8;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v8 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v8;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v17;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v17 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v17;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v17 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v18;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v18 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v18;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v18 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v9;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v9 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v9;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v9 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v9;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v19;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v19 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v19;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v19 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v20;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v20 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v20;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v20 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v10;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v10 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v10;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v10 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v10;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v21;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v21 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v21;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v21 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v22;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v22 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v22;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v22 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v11;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v11 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v11;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v11 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v11;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v23;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v23 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v23;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v23 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v24;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v24 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v24;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v24 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v12;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v12 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v12;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v12 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v12;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v25;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v25 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v25;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v25 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v26;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v26 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v26;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v26 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v13;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v13 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v13;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v13 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v13;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v27;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v27 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v27;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v27 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v28;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v28 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v28;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v28 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v14;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v14 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v14;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v14 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v14;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v29;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v29 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v29;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v29 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v30;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v30 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v30;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v30 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v15;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v15 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v15;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v15 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v15;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v31;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v31 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v31;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v31 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v32;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v32 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v32;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v32 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v16;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v16 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v38;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v38 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v38;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v38 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v39;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v39 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v39;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v39 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v40;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v40 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v40;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v40 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v41;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v41 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v41;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v41 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21 = 0;
    CData/*3:0*/ __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21;
    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v43;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v43 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v43;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v43 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v44;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v44 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v45;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v45 = 0;
    SData/*15:0*/ __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v46;
    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v46 = 0;
    CData/*0:0*/ __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v22;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v22 = 0;
    // Body
    __Vdly__pipeline__DOT__state = vlSelfRef.pipeline__DOT__state;
    __Vdly__pipeline__DOT__mul__DOT__index = vlSelfRef.pipeline__DOT__mul__DOT__index;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v1 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v1 = 0U;
    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state;
    __Vdly__pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done 
        = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done;
    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod;
    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_latched 
        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_latched;
    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state;
    __Vdly__pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done 
        = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done;
    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod;
    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_latched 
        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_latched;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v0 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v1 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v2 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v3 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v4 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v5 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v6 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v7 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v8 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v9 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v10 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v11 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v12 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v13 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v14 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v15 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v16 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v0 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v1 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v2 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v3 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v4 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v5 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v6 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v7 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v8 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v9 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v10 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v11 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v12 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v13 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v14 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v15 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v16 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v1 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v2 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v3 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v4 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v5 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v6 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v7 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v8 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v9 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v10 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v11 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v12 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v13 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v14 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v15 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v16 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v17 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v18 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v19 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v20 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v21 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v22 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v23 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v24 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v25 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v26 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v27 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v28 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v29 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v30 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v31 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v32 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v38 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v39 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v40 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v41 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v43 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v1 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v2 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v3 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v4 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v5 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v6 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v7 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v8 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v9 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v10 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v11 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v12 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v13 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v14 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v15 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v16 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v17 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v18 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v19 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v20 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v21 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v22 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v23 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v24 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v25 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v26 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v27 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v28 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v29 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v30 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v31 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v32 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v38 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v39 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v40 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v41 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v43 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v0 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v1 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v2 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v3 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v4 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v5 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v6 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v7 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v8 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v9 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v10 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v11 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v12 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v13 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v14 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v15 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v0 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v1 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v2 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v3 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v4 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v5 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v6 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v7 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v8 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v9 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v10 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v11 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v12 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v13 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v14 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v15 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v22 = 0U;
    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v22 = 0U;
    if (vlSelfRef.in_valid) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__i = 0x10U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__i = 0x10U;
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v0 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [0U];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v0 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [0U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [0U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [0U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v1 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [0U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v1 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [0U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [0U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v2 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [0U])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v2 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v1 = 1U;
            }
        }
        __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 0U;
        __Vdly__pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done = 0U;
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v1 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [1U];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v1 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [1U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [1U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [1U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v3 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [1U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v3 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [1U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [1U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v4 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [1U])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v4 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v2 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v2 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [2U];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v2 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [2U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [2U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [2U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v5 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [2U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v5 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [2U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [2U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v6 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [2U])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v6 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v3 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v3 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [3U];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v3 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [3U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [3U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [3U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v7 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [3U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v7 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [3U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [3U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v8 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [3U])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v8 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v4 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v4 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [4U];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v4 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [4U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [4U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [4U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v9 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [4U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v9 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [4U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [4U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v10 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [4U])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v10 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v5 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v5 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [5U];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v5 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [5U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [5U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [5U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v11 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [5U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v11 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [5U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [5U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v12 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [5U])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v12 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v6 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v6 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [6U];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v6 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [6U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [6U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [6U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v13 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [6U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v13 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [6U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [6U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v14 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [6U])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v14 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v7 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v7 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [7U];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v7 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [7U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [7U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [7U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v15 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [7U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v15 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [7U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [7U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v16 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [7U])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v16 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v8 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v8 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [8U];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v8 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [8U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [8U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [8U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v17 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [8U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v17 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [8U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [8U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v18 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [8U])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v18 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v9 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v9 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [9U];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v9 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [9U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [9U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [9U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v19 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [9U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v19 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [9U], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [9U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v20 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [9U])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v20 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v10 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v10 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [0xaU];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v10 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [0xaU]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [0xaU], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [0xaU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v21 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [0xaU]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v21 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [0xaU], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [0xaU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v22 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [0xaU])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v22 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v11 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v11 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [0xbU];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v11 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [0xbU]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [0xbU], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [0xbU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v23 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [0xbU]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v23 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [0xbU], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [0xbU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v24 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [0xbU])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v24 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v12 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v12 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [0xcU];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v12 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [0xcU]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [0xcU], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [0xcU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v25 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [0xcU]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v25 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [0xcU], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [0xcU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v26 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [0xcU])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v26 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v13 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v13 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [0xdU];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v13 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [0xdU]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [0xdU], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [0xdU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v27 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [0xdU]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v27 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [0xdU], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [0xdU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v28 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [0xdU])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v28 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v14 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v14 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [0xeU];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v14 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [0xeU]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [0xeU], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [0xeU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v29 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [0xeU]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v29 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [0xeU], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [0xeU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v30 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [0xeU])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v30 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v15 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v15 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in
            [0xfU];
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v15 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated
            [0xfU]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                           [0xfU], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [0xfU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v31 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                [0xfU]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v31 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates
                                  [0xfU], vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                  [0xfU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v32 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                              [0xfU])));
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v32 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v16 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v0 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [0U];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v0 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [0U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [0U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [0U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v1 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [0U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v1 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [0U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [0U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v2 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [0U])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v2 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v1 = 1U;
            }
        }
        __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 0U;
        __Vdly__pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done = 0U;
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v1 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [1U];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v1 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [1U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [1U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [1U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v3 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [1U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v3 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [1U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [1U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v4 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [1U])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v4 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v2 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v2 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [2U];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v2 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [2U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [2U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [2U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v5 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [2U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v5 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [2U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [2U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v6 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [2U])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v6 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v3 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v3 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [3U];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v3 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [3U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [3U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [3U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v7 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [3U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v7 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [3U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [3U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v8 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [3U])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v8 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v4 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v4 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [4U];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v4 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [4U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [4U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [4U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v9 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [4U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v9 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [4U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [4U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v10 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [4U])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v10 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v5 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v5 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [5U];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v5 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [5U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [5U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [5U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v11 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [5U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v11 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [5U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [5U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v12 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [5U])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v12 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v6 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v6 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [6U];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v6 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [6U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [6U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [6U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v13 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [6U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v13 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [6U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [6U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v14 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [6U])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v14 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v7 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v7 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [7U];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v7 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [7U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [7U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [7U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v15 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [7U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v15 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [7U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [7U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v16 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [7U])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v16 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v8 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v8 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [8U];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v8 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [8U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [8U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [8U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v17 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [8U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v17 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [8U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [8U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v18 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [8U])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v18 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v9 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v9 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [9U];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v9 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [9U]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [9U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [9U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v19 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [9U]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v19 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [9U], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [9U])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v20 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [9U])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v20 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v10 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v10 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [0xaU];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v10 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [0xaU]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [0xaU], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [0xaU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v21 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [0xaU]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v21 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [0xaU], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [0xaU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v22 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [0xaU])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v22 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v11 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v11 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [0xbU];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v11 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [0xbU]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [0xbU], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [0xbU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v23 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [0xbU]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v23 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [0xbU], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [0xbU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v24 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [0xbU])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v24 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v12 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v12 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [0xcU];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v12 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [0xcU]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [0xcU], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [0xcU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v25 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [0xcU]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v25 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [0xcU], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [0xcU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v26 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [0xcU])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v26 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v13 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v13 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [0xdU];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v13 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [0xdU]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [0xdU], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [0xdU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v27 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [0xdU]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v27 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [0xdU], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [0xdU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v28 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [0xdU])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v28 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v14 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v14 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [0xeU];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v14 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [0xeU]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [0xeU], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [0xeU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v29 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [0xeU]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v29 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [0xeU], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [0xeU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v30 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [0xeU])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v30 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v15 = 1U;
            }
        }
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v15 
            = vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in
            [0xfU];
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v15 = 1U;
        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated
            [0xfU]) {
            if (VL_LTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                           [0xfU], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [0xfU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v31 
                    = (0xffffU & (VL_EXTENDS_II(16,16, 
                                                vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                [0xfU]) 
                                  - (IData)(1U)));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v31 = 1U;
            } else if (VL_GTS_III(16, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates
                                  [0xfU], vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                  [0xfU])) {
                __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v32 
                    = (0xffffU & ((IData)(1U) + VL_EXTENDS_II(16,16, 
                                                              vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                              [0xfU])));
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v32 = 1U;
            } else {
                __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v16 = 1U;
            }
        }
    } else {
        if ((1U & (~ (IData)(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done)))) {
            if ((0U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr))) {
                __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 1U;
                __Vdly__pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done = 1U;
            } else if ((1U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr))) {
                if ((0U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a 
                        = ((0x200000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                            ? vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 5U))] : vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 5U))]);
                    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 2U;
                    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b 
                        = ((0x400000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                            ? vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 9U))] : vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 9U))]);
                } else if ((2U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 3U;
                } else if ((3U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    if ((0x1000000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)) {
                        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33 = 1U;
                    } else {
                        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16 = 1U;
                    }
                    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 1U;
                    __Vdly__pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done = 1U;
                }
                __Vdly__pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done = 1U;
            } else if ((2U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr))) {
                if ((0U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a 
                        = ((0x200000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                            ? vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 5U))] : vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 5U))]);
                    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 2U;
                    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b 
                        = ((0x400000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                            ? vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 9U))] : vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 9U))]);
                } else if ((2U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready) {
                        __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final;
                        __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 3U;
                    }
                    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                } else if ((3U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    if ((0x1000000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)) {
                        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34 = 1U;
                    } else {
                        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17 = 1U;
                    }
                    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 1U;
                    __Vdly__pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done = 1U;
                }
            } else if ((3U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr))) {
                if ((0U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a 
                        = ((0x200000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                            ? vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 5U))] : vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 5U))]);
                    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 2U;
                    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b 
                        = ((0x400000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                            ? vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 9U))] : vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 9U))]);
                } else if ((2U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready) {
                        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final;
                        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b 
                            = ((0x800000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                                ? vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                               [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                         >> 0xdU))]
                                : vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                               [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                         >> 0xdU))]);
                        __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 3U;
                    }
                    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                } else if ((3U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 4U;
                } else if ((4U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    if ((0x1000000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)) {
                        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35 = 1U;
                    } else {
                        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18 = 1U;
                    }
                    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 1U;
                    __Vdly__pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done = 1U;
                }
            } else if ((4U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr))) {
                if ((0x200000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)) {
                    if ((0x1000000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)) {
                        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36 
                            = (0xffffU & (VL_GTS_III(32, 0U, 
                                                     VL_EXTENDS_II(32,16, 
                                                                   vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                                   [
                                                                   (0xfU 
                                                                    & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                                       >> 5U))]))
                                           ? (- vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                              [(0xfU 
                                                & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                   >> 5U))])
                                           : vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                          [(0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                             >> 5U))]));
                        __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36 = 1U;
                    } else {
                        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19 
                            = (0xffffU & (VL_GTS_III(32, 0U, 
                                                     VL_EXTENDS_II(32,16, 
                                                                   vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                                                   [
                                                                   (0xfU 
                                                                    & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                                       >> 5U))]))
                                           ? (- vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                              [(0xfU 
                                                & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                   >> 5U))])
                                           : vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                          [(0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                             >> 5U))]));
                        __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19 = 1U;
                    }
                } else if ((0x1000000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)) {
                    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37 
                        = (0xffffU & (VL_GTS_III(32, 0U, 
                                                 VL_EXTENDS_II(32,16, 
                                                               vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                                                               [
                                                               (0xfU 
                                                                & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                                   >> 5U))]))
                                       ? (- vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                                          [(0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                             >> 5U))])
                                       : vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                                      [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                >> 5U))]));
                    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37 
                        = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                   >> 0x11U));
                    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37 = 1U;
                } else {
                    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20 
                        = (0xffffU & (VL_GTS_III(32, 0U, 
                                                 VL_EXTENDS_II(32,16, 
                                                               vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                                                               [
                                                               (0xfU 
                                                                & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                                   >> 5U))]))
                                       ? (- vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                                          [(0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                             >> 5U))])
                                       : vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs
                                      [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                >> 5U))]));
                    __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20 
                        = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                   >> 0x11U));
                    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20 = 1U;
                }
                __Vdly__pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done = 1U;
            } else if ((5U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr))) {
                if (((((((((0U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state)) 
                           | (1U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) 
                          | (2U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) 
                         | (3U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) 
                        | (4U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) 
                       | (5U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) 
                      | (6U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) 
                     | (7U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state)))) {
                    if ((0U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                        __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_latched 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs
                            [vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_unified_addr];
                        vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                            [0U];
                        vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs
                            [vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_unified_addr];
                        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                        __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 1U;
                    } else if ((1U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready) {
                            vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                [1U];
                            vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                            __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 2U;
                            vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                [5U];
                            __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v38 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final;
                            __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v38 = 1U;
                        } else {
                            vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                        }
                    } else if ((2U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready) {
                            vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                [9U];
                            vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final;
                            __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 3U;
                        }
                        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                    } else if ((3U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                        __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 4U;
                    } else if ((4U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                        vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                            [2U];
                        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                        __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 5U;
                        vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                            [6U];
                        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v39 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum;
                        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v39 = 1U;
                    } else if ((5U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                        if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready) {
                            vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                                [9U];
                            vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final;
                            __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 6U;
                        }
                        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                    } else if ((6U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                        __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 7U;
                    } else {
                        vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                            [3U];
                        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                        __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 8U;
                        vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                            [7U];
                        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v40 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum;
                        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v40 = 1U;
                    }
                } else if ((8U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready) {
                        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                            [9U];
                        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b 
                            = (0xffffU & (- (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final)));
                        __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 9U;
                    }
                    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                } else if ((9U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 0xaU;
                } else if ((0xaU == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                        [4U];
                    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 0xbU;
                    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                        [8U];
                    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v41 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum;
                    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v41 = 1U;
                } else if ((0xbU == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    if (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready) {
                        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                            [9U];
                        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b 
                            = (0xffffU & (- (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final)));
                        __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 0xcU;
                    }
                    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                } else if ((0xcU == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 0xdU;
                } else if ((0xdU == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state))) {
                    __Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__value 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum;
                    __Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__uaddr 
                        = (0x1fU & ((0x1000000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                                     ? ((IData)(0x10U) 
                                        + (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                   >> 0x11U)))
                                     : (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                >> 0x11U))));
                    __Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__is_reg 
                        = (1U & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                 >> 0x18U));
                    __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state = 1U;
                    __Vdly__pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done = 1U;
                    if (__Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__is_reg) {
                        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42 
                            = __Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__value;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42 
                            = (0xfU & (IData)(__Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__uaddr));
                        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42 = 1U;
                    } else {
                        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21 
                            = __Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__value;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21 
                            = (0xfU & (IData)(__Vtask_pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_write__0__uaddr));
                        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21 = 1U;
                    }
                    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v43 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                        [5U];
                    __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v43 = 1U;
                    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v44 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_latched;
                    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v45 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs
                        [7U];
                    __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v46 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum;
                }
            }
        }
        if ((1U & (~ (IData)(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done)))) {
            if ((0U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr))) {
                __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 1U;
                __Vdly__pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done = 1U;
            } else if ((1U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr))) {
                if ((0U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a 
                        = ((0x200000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                            ? vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                     >> 5U))] : vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                     >> 5U))]);
                    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 2U;
                    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b 
                        = ((0x400000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                            ? vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                     >> 9U))] : vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                     >> 9U))]);
                } else if ((2U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 3U;
                } else if ((3U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    if ((0x1000000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)) {
                        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33 = 1U;
                    } else {
                        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16 = 1U;
                    }
                    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 1U;
                    __Vdly__pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done = 1U;
                }
                __Vdly__pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done = 1U;
            } else if ((2U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr))) {
                if ((0U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a 
                        = ((0x200000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                            ? vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                     >> 5U))] : vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                     >> 5U))]);
                    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 2U;
                    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b 
                        = ((0x400000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                            ? vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                     >> 9U))] : vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                     >> 9U))]);
                } else if ((2U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready) {
                        __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final;
                        __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 3U;
                    }
                    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                } else if ((3U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    if ((0x1000000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)) {
                        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34 = 1U;
                    } else {
                        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17 = 1U;
                    }
                    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 1U;
                    __Vdly__pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done = 1U;
                }
            } else if ((3U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr))) {
                if ((0U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a 
                        = ((0x200000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                            ? vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                     >> 5U))] : vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                     >> 5U))]);
                    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 2U;
                    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b 
                        = ((0x400000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                            ? vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                     >> 9U))] : vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                           [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                     >> 9U))]);
                } else if ((2U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready) {
                        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final;
                        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b 
                            = ((0x800000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                                ? vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                               [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                         >> 0xdU))]
                                : vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                               [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                         >> 0xdU))]);
                        __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 3U;
                    }
                    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                } else if ((3U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 4U;
                } else if ((4U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    if ((0x1000000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)) {
                        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35 = 1U;
                    } else {
                        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18 = 1U;
                    }
                    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 1U;
                    __Vdly__pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done = 1U;
                }
            } else if ((4U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr))) {
                if ((0x200000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)) {
                    if ((0x1000000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)) {
                        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36 
                            = (0xffffU & (VL_GTS_III(32, 0U, 
                                                     VL_EXTENDS_II(32,16, 
                                                                   vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                                   [
                                                                   (0xfU 
                                                                    & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                                       >> 5U))]))
                                           ? (- vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                              [(0xfU 
                                                & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                   >> 5U))])
                                           : vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                          [(0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                             >> 5U))]));
                        __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36 = 1U;
                    } else {
                        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19 
                            = (0xffffU & (VL_GTS_III(32, 0U, 
                                                     VL_EXTENDS_II(32,16, 
                                                                   vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                                                   [
                                                                   (0xfU 
                                                                    & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                                       >> 5U))]))
                                           ? (- vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                              [(0xfU 
                                                & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                   >> 5U))])
                                           : vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                          [(0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                             >> 5U))]));
                        __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19 
                            = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U));
                        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19 = 1U;
                    }
                } else if ((0x1000000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)) {
                    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37 
                        = (0xffffU & (VL_GTS_III(32, 0U, 
                                                 VL_EXTENDS_II(32,16, 
                                                               vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                                                               [
                                                               (0xfU 
                                                                & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                                   >> 5U))]))
                                       ? (- vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                                          [(0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                             >> 5U))])
                                       : vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                                      [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                >> 5U))]));
                    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37 
                        = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                   >> 0x11U));
                    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37 = 1U;
                } else {
                    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20 
                        = (0xffffU & (VL_GTS_III(32, 0U, 
                                                 VL_EXTENDS_II(32,16, 
                                                               vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                                                               [
                                                               (0xfU 
                                                                & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                                   >> 5U))]))
                                       ? (- vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                                          [(0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                             >> 5U))])
                                       : vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs
                                      [(0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                >> 5U))]));
                    __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20 
                        = (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                   >> 0x11U));
                    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20 = 1U;
                }
                __Vdly__pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done = 1U;
            } else if ((5U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr))) {
                if (((((((((0U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state)) 
                           | (1U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) 
                          | (2U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) 
                         | (3U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) 
                        | (4U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) 
                       | (5U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) 
                      | (6U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) 
                     | (7U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state)))) {
                    if ((0U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                        __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_latched 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs
                            [vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_unified_addr];
                        vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                            [0U];
                        vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs
                            [vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_unified_addr];
                        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                        __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 1U;
                    } else if ((1U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready) {
                            vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                [1U];
                            vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                            __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 2U;
                            vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                [5U];
                            __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v38 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final;
                            __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v38 = 1U;
                        } else {
                            vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                        }
                    } else if ((2U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready) {
                            vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                [9U];
                            vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final;
                            __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 3U;
                        }
                        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                    } else if ((3U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                        __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 4U;
                    } else if ((4U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                        vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                            [2U];
                        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                        __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 5U;
                        vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                            [6U];
                        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v39 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum;
                        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v39 = 1U;
                    } else if ((5U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                        if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready) {
                            vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                                [9U];
                            vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b 
                                = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final;
                            __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 6U;
                        }
                        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                    } else if ((6U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                        __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 7U;
                    } else {
                        vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                            [3U];
                        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                        __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 8U;
                        vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                            [7U];
                        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v40 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum;
                        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v40 = 1U;
                    }
                } else if ((8U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready) {
                        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                            [9U];
                        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b 
                            = (0xffffU & (- (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final)));
                        __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 9U;
                    }
                    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                } else if ((9U == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 0xaU;
                } else if ((0xaU == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                        [4U];
                    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 1U;
                    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 0xbU;
                    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                        [8U];
                    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v41 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum;
                    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v41 = 1U;
                } else if ((0xbU == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    if (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready) {
                        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a 
                            = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                            [9U];
                        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b 
                            = (0xffffU & (- (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final)));
                        __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 0xcU;
                    }
                    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin = 0U;
                } else if ((0xcU == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 0xdU;
                } else if ((0xdU == (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state))) {
                    __Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__value 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum;
                    __Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__uaddr 
                        = (0x1fU & ((0x1000000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                                     ? ((IData)(0x10U) 
                                        + (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                   >> 0x11U)))
                                     : (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                >> 0x11U))));
                    __Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__is_reg 
                        = (1U & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                 >> 0x18U));
                    __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state = 1U;
                    __Vdly__pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done = 1U;
                    if (__Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__is_reg) {
                        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42 
                            = __Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__value;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42 
                            = (0xfU & (IData)(__Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__uaddr));
                        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42 = 1U;
                    } else {
                        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21 
                            = __Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__value;
                        __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21 
                            = (0xfU & (IData)(__Vtask_pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_write__1__uaddr));
                        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21 = 1U;
                    }
                    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v43 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                        [5U];
                    __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v43 = 1U;
                    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v44 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_latched;
                    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v45 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs
                        [7U];
                    __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v46 
                        = vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum;
                }
            }
        }
    }
    if (vlSelfRef.reset) {
        vlSelfRef.pipeline__DOT__mul__DOT__i = 2U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__i = 0x10U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__i = 0x10U;
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v1 = 1U;
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v1 = 1U;
        vlSelfRef.pipeline__DOT__sample_latched = 0U;
        __Vdly__pipeline__DOT__state = 0U;
        vlSelfRef.ready = 1U;
        vlSelfRef.pipeline__DOT__invalid = 0U;
        __Vdly__pipeline__DOT__mul__DOT__index = 1U;
        vlSelfRef.pipeline__DOT__mul_done = 0U;
        vlSelfRef.pipeline__DOT__mul_result = 0U;
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v22 = 1U;
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v22 = 1U;
    } else {
        if ((0U == (IData)(vlSelfRef.pipeline__DOT__state))) {
            vlSelfRef.ready = 1U;
            if (vlSelfRef.in_valid) {
                __Vdly__pipeline__DOT__state = 1U;
                vlSelfRef.pipeline__DOT__ctr = 0U;
                vlSelfRef.ready = 0U;
            }
        } else if ((1U == (IData)(vlSelfRef.pipeline__DOT__state))) {
            vlSelfRef.ready = ((IData)(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done) 
                               & (IData)(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done));
        } else if ((2U == (IData)(vlSelfRef.pipeline__DOT__state))) {
            vlSelfRef.pipeline__DOT__invalid = 1U;
            vlSelfRef.ready = 0U;
        } else {
            vlSelfRef.pipeline__DOT__invalid = 1U;
            __Vdly__pipeline__DOT__state = 2U;
        }
        vlSelfRef.pipeline__DOT__mul_result = VL_MULS_III(32, 
                                                          VL_EXTENDS_II(32,16, 
                                                                        vlSelfRef.pipeline__DOT____Vcellinp__mul__x
                                                                        [vlSelfRef.pipeline__DOT__mul__DOT__index]), 
                                                          VL_EXTENDS_II(32,16, 
                                                                        vlSelfRef.pipeline__DOT____Vcellinp__mul__y
                                                                        [vlSelfRef.pipeline__DOT__mul__DOT__index]));
        vlSelfRef.pipeline__DOT__mul_done = 0U;
        vlSelfRef.pipeline__DOT__mul_done = ((IData)(vlSelfRef.pipeline__DOT__mul_done) 
                                             | (3U 
                                                & ((IData)(1U) 
                                                   << (IData)(vlSelfRef.pipeline__DOT__mul__DOT__index))));
        __Vdly__pipeline__DOT__mul__DOT__index = ((1U 
                                                   & (~ (IData)(vlSelfRef.pipeline__DOT__mul__DOT__index))) 
                                                  || (1U 
                                                      & ((IData)(vlSelfRef.pipeline__DOT__mul__DOT__index) 
                                                         - (IData)(1U))));
    }
    if ((1U & (~ (IData)(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_write)))) {
        if (vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_update) {
            __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0 
                = vlSelfRef.reg_val;
            __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0 
                = vlSelfRef.reg_target;
            __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0 = 1U;
        }
    }
    if ((1U & (~ (IData)(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_write)))) {
        if (vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_update) {
            __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0 
                = vlSelfRef.reg_val;
            __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0 
                = vlSelfRef.reg_target;
            __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0 = 1U;
        }
    }
    if (vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_write) {
        __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0 
            = vlSelfRef.reg_val;
        __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0 
            = vlSelfRef.reg_target;
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0 = 1U;
    } else if (vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_update) {
        __VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v0 
            = vlSelfRef.reg_target;
        __VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v0 = 1U;
    }
    if (vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_write) {
        __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0 
            = vlSelfRef.reg_val;
        __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0 
            = vlSelfRef.reg_target;
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0 = 1U;
    } else if (vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_update) {
        __VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v0 
            = vlSelfRef.reg_target;
        __VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v0 = 1U;
    }
    vlSelfRef.pipeline__DOT__state = __Vdly__pipeline__DOT__state;
    vlSelfRef.pipeline__DOT__mul__DOT__index = __Vdly__pipeline__DOT__mul__DOT__index;
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state 
        = __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state;
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done 
        = __Vdly__pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done;
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod 
        = __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod;
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_latched 
        = __Vdly__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_latched;
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v0;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates__v1) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[0U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[1U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[2U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[3U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[4U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[5U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[6U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[7U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[8U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[9U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[0xaU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[0xbU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[0xcU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[0xdU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[0xeU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[0xfU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v0) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v0] = 1U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v1) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v2) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[1U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v3) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[2U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v4) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[3U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v5) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[4U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v6) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[5U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v7) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[6U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v8) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[7U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v9) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[8U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v10) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[9U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v11) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0xaU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v12) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0xbU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v13) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0xcU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v14) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0xdU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v15) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0xeU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated__v16) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0xfU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v0;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v1) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v1;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v2) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v2;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v3) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[1U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v3;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v4) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[1U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v4;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v5) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[2U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v5;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v6) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[2U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v6;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v7) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[3U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v7;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v8) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[3U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v8;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v9) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[4U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v9;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v10) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[4U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v10;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v11) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[5U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v11;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v12) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[5U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v12;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v13) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[6U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v13;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v14) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[6U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v14;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v15) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[7U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v15;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v16) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[7U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v16;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v17) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[8U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v17;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v18) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[8U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v18;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v19) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v19;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v20) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v20;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v21) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xaU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v21;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v22) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xaU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v22;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v23) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xbU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v23;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v24) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xbU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v24;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v25) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xcU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v25;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v26) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xcU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v26;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v27) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xdU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v27;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v28) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xdU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v28;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v29) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xeU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v29;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v30) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xeU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v30;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v31) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xfU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v31;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v32) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xfU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v32;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v33;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v34;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v35;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v36;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v37;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v38) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v38;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v39) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v39;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v40) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v40;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v41) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v41;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v42;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v43) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[6U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v43;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[5U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v44;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[8U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v45;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[7U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs__v46;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v0) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v0;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v1) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[1U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v1;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v2) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[2U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v2;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v3) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[3U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v3;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v4) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[4U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v4;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v5) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[5U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v5;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v6) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[6U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v6;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v7) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[7U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v7;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v8) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[8U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v8;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v9) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v9;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v10) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0xaU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v10;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v11) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0xbU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v11;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v12) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0xcU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v12;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v13) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0xdU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v13;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v14) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0xeU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v14;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v15) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0xfU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v15;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v16;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v17;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v18;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v19;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v20;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[__VdlyDim0__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v21;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs__v22) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[1U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[2U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[3U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[4U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[5U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[6U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[7U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[8U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[9U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0xaU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0xbU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0xcU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0xdU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0xeU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0xfU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[1U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[2U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[3U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[4U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[5U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[6U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[7U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[8U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[9U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xaU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xbU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xcU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xdU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xeU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0xfU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[1U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[2U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[3U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[4U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[5U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[6U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[7U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[8U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[9U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0xaU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0xbU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0xcU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0xdU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0xeU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state 
        = __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state;
    vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done 
        = __Vdly__pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done;
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod 
        = __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod;
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_latched 
        = __Vdly__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_latched;
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v0;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates__v1) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[0U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[1U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[2U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[3U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[4U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[5U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[6U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[7U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[8U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[9U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[0xaU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[0xbU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[0xcU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[0xdU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[0xeU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[0xfU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v0) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v0] = 1U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v1) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v2) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[1U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v3) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[2U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v4) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[3U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v5) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[4U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v6) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[5U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v7) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[6U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v8) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[7U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v9) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[8U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v10) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[9U] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v11) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0xaU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v12) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0xbU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v13) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0xcU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v14) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0xdU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v15) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0xeU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated__v16) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0xfU] = 0U;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v0;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v1) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v1;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v2) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v2;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v3) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[1U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v3;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v4) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[1U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v4;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v5) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[2U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v5;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v6) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[2U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v6;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v7) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[3U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v7;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v8) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[3U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v8;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v9) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[4U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v9;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v10) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[4U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v10;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v11) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[5U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v11;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v12) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[5U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v12;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v13) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[6U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v13;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v14) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[6U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v14;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v15) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[7U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v15;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v16) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[7U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v16;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v17) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[8U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v17;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v18) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[8U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v18;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v19) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v19;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v20) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v20;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v21) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xaU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v21;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v22) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xaU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v22;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v23) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xbU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v23;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v24) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xbU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v24;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v25) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xcU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v25;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v26) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xcU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v26;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v27) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xdU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v27;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v28) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xdU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v28;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v29) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xeU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v29;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v30) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xeU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v30;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v31) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xfU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v31;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v32) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xfU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v32;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v33;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v34;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v35;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v36;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v37;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v38) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v38;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v39) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v39;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v40) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v40;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v41) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v41;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v42;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v43) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[6U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v43;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[5U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v44;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[8U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v45;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[7U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs__v46;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v0) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v0;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v1) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[1U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v1;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v2) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[2U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v2;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v3) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[3U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v3;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v4) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[4U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v4;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v5) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[5U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v5;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v6) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[6U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v6;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v7) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[7U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v7;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v8) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[8U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v8;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v9) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[9U] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v9;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v10) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0xaU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v10;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v11) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0xbU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v11;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v12) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0xcU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v12;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v13) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0xdU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v13;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v14) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0xeU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v14;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v15) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0xfU] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v15;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v16;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v17;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v18;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v19;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v20;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[__VdlyDim0__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21] 
            = __VdlyVal__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v21;
    }
    if (__VdlySet__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs__v22) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[1U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[2U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[3U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[4U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[5U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[6U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[7U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[8U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[9U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0xaU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0xbU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0xcU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0xdU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0xeU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0xfU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[1U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[2U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[3U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[4U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[5U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[6U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[7U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[8U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[9U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xaU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xbU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xcU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xdU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xeU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0xfU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[1U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[2U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[3U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[4U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[5U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[6U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[7U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[8U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[9U] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0xaU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0xbU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0xcU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0xdU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0xeU] = 0U;
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.error = vlSelfRef.pipeline__DOT__invalid;
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready 
        = (1U & ((~ (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin)) 
                 & (IData)(vlSelfRef.pipeline__DOT__mul_done)));
    vlSelfRef.pipeline__DOT__mul_bus_x[0U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a;
    vlSelfRef.pipeline__DOT__mul_bus_y[0U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b;
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum 
        = (VL_LTS_III(17, 0xffffU, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum_ext)
            ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum_ext)
                          ? 0x8000U : (0xffffU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum_ext)));
    if (((IData)(vlSelfRef.instr_write) & (~ (IData)(vlSelfRef.block_target)))) {
        vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
            = vlSelfRef.instr_val;
    }
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
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready 
        = ((~ (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin)) 
           & ((IData)(vlSelfRef.pipeline__DOT__mul_done) 
              >> 1U));
    vlSelfRef.pipeline__DOT__mul_bus_x[1U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a;
    vlSelfRef.pipeline__DOT__mul_bus_y[1U] = vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b;
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum 
        = (VL_LTS_III(17, 0xffffU, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum_ext)
            ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum_ext)
                          ? 0x8000U : (0xffffU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum_ext)));
    if (((IData)(vlSelfRef.instr_write) & (IData)(vlSelfRef.block_target))) {
        vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
            = vlSelfRef.instr_val;
    }
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
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum_ext 
        = (0x1ffffU & (((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a) 
                                     << 1U)) | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a)) 
                       + ((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b) 
                                       << 1U)) | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b))));
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
    vlSelfRef.pipeline__DOT____Vcellinp__mul__x[0U] 
        = vlSelfRef.pipeline__DOT__mul_bus_x[0U];
    vlSelfRef.pipeline__DOT____Vcellinp__mul__x[1U] 
        = vlSelfRef.pipeline__DOT__mul_bus_x[1U];
    vlSelfRef.pipeline__DOT____Vcellinp__mul__y[0U] 
        = vlSelfRef.pipeline__DOT__mul_bus_y[0U];
    vlSelfRef.pipeline__DOT____Vcellinp__mul__y[1U] 
        = vlSelfRef.pipeline__DOT__mul_bus_y[1U];
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum_ext 
        = (0x1ffffU & (((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a) 
                                     << 1U)) | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a)) 
                       + ((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b) 
                                       << 1U)) | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b))));
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
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_unified_addr 
        = (0x1fU & ((0x200000U & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                     ? ((IData)(0x10U) + (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                  >> 5U)))
                     : (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                >> 5U))));
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_shifted 
        = VL_SHIFTRS_III(32,32,32, vlSelfRef.pipeline__DOT__mul_result, 
                         ((IData)(0xfU) - ((5U == (0x1fU 
                                                   & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr))
                                            ? 1U : 
                                           (0x1fU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                             >> 0x19U)))));
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_unified_addr 
        = (0x1fU & ((0x200000U & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                     ? ((IData)(0x10U) + (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                  >> 5U)))
                     : (0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                >> 5U))));
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_shifted 
        = VL_SHIFTRS_III(32,32,32, vlSelfRef.pipeline__DOT__mul_result, 
                         ((IData)(0xfU) - ((5U == (0x1fU 
                                                   & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr))
                                            ? 1U : 
                                           (0x1fU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                             >> 0x19U)))));
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
    vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final 
        = (VL_LTS_III(32, 0x7fffU, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_shifted)
            ? 0x7fffU : (VL_GTS_III(32, 0xffff8000U, vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_shifted)
                          ? 0x8000U : (0xffffU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_shifted)));
    vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final 
        = (VL_LTS_III(32, 0x7fffU, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_shifted)
            ? 0x7fffU : (VL_GTS_III(32, 0xffff8000U, vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_shifted)
                          ? 0x8000U : (0xffffU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_shifted)));
}

void Vpipeline___024root___eval_triggers__act(Vpipeline___024root* vlSelf);

bool Vpipeline___024root___eval_phase__act(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_phase__act\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vpipeline___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vpipeline___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vpipeline___024root___eval_phase__nba(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_phase__nba\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vpipeline___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpipeline___024root___dump_triggers__ico(Vpipeline___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vpipeline___024root___dump_triggers__nba(Vpipeline___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vpipeline___024root___dump_triggers__act(Vpipeline___024root* vlSelf);
#endif  // VL_DEBUG

void Vpipeline___024root___eval(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vpipeline___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("src/pipeline.v", 627, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vpipeline___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vpipeline___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("src/pipeline.v", 627, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vpipeline___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("src/pipeline.v", 627, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vpipeline___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vpipeline___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vpipeline___024root___eval_debug_assertions(Vpipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root___eval_debug_assertions\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY(((vlSelfRef.in_valid & 0xfeU)))) {
        Verilated::overWidthError("in_valid");}
    if (VL_UNLIKELY(((vlSelfRef.reset & 0xfeU)))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY(((vlSelfRef.block_target & 0xfeU)))) {
        Verilated::overWidthError("block_target");}
    if (VL_UNLIKELY(((vlSelfRef.reg_target & 0xf0U)))) {
        Verilated::overWidthError("reg_target");}
    if (VL_UNLIKELY(((vlSelfRef.instr_write & 0xfeU)))) {
        Verilated::overWidthError("instr_write");}
    if (VL_UNLIKELY(((vlSelfRef.reg_update & 0xfeU)))) {
        Verilated::overWidthError("reg_update");}
    if (VL_UNLIKELY(((vlSelfRef.reg_write & 0xfeU)))) {
        Verilated::overWidthError("reg_write");}
}
#endif  // VL_DEBUG
