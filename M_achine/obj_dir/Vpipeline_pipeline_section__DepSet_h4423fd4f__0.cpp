// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline.h for the primary calling header

#include "Vpipeline__pch.h"
#include "Vpipeline_pipeline_section.h"

VL_INLINE_OPT void Vpipeline_pipeline_section___act_sequent__TOP__pipeline__DOT__sections__BRA__0__KET____DOT__section_inst__1(Vpipeline_pipeline_section* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_section___act_sequent__TOP__pipeline__DOT__sections__BRA__0__KET____DOT__section_inst__1\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__bus[0U][0U] = vlSelfRef.ch_in[0U];
    vlSelfRef.__PVT__bus[0U][1U] = vlSelfRef.ch_in[1U];
    vlSelfRef.__PVT__bus[0U][2U] = vlSelfRef.ch_in[2U];
    vlSelfRef.__PVT__bus[0U][3U] = vlSelfRef.ch_in[3U];
    vlSelfRef.__PVT__bus[0U][4U] = vlSelfRef.ch_in[4U];
    vlSelfRef.__PVT__bus[0U][5U] = vlSelfRef.ch_in[5U];
    vlSelfRef.__PVT__bus[0U][6U] = vlSelfRef.ch_in[6U];
    vlSelfRef.__PVT__bus[0U][7U] = vlSelfRef.ch_in[7U];
    vlSelfRef.__PVT__bus[0U][8U] = vlSelfRef.ch_in[8U];
    vlSelfRef.__PVT__bus[0U][9U] = vlSelfRef.ch_in[9U];
    vlSelfRef.__PVT__bus[0U][0xaU] = vlSelfRef.ch_in
        [0xaU];
    vlSelfRef.__PVT__bus[0U][0xbU] = vlSelfRef.ch_in
        [0xbU];
    vlSelfRef.__PVT__bus[0U][0xcU] = vlSelfRef.ch_in
        [0xcU];
    vlSelfRef.__PVT__bus[0U][0xdU] = vlSelfRef.ch_in
        [0xdU];
    vlSelfRef.__PVT__bus[0U][0xeU] = vlSelfRef.ch_in
        [0xeU];
    vlSelfRef.__PVT__bus[0U][0xfU] = vlSelfRef.ch_in
        [0xfU];
}

VL_INLINE_OPT void Vpipeline_pipeline_section___act_comb__TOP__pipeline__DOT__sections__BRA__0__KET____DOT__section_inst__0(Vpipeline_pipeline_section* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_section___act_comb__TOP__pipeline__DOT__sections__BRA__0__KET____DOT__section_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[1U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[1U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[1U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[1U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[1U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[1U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[1U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[1U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[1U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[1U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[1U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[1U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[1U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[1U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[1U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[1U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[2U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[2U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[2U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[2U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[2U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[2U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[2U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[2U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[2U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[2U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[2U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[2U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[2U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[2U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[2U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[2U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[3U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[3U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[3U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[3U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[3U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[3U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[3U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[3U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[3U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[3U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[3U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[3U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[3U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[3U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[3U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[3U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[4U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[4U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[4U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[4U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[4U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[4U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[4U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[4U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[4U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[4U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[4U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[4U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[4U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[4U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[4U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[4U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[5U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[5U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[5U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[5U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[5U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[5U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[5U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[5U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[5U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[5U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[5U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[5U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[5U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[5U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[5U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[5U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[6U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[6U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[6U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[6U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[6U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[6U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[6U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[6U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[6U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[6U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[6U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[6U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[6U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[6U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[6U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[6U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[7U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[7U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[7U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[7U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[7U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[7U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[7U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[7U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[7U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[7U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[7U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[7U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[7U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[7U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[7U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[7U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[8U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[8U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[8U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[8U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[8U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[8U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[8U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[8U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[8U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[8U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[8U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[8U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[8U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[8U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[8U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[8U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[9U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[9U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[9U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[9U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[9U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[9U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[9U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[9U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[9U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[9U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[9U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[9U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[9U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[9U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[9U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[9U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0xaU][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0xaU][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0xaU][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0xaU][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0xaU][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0xaU][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0xaU][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0xaU][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0xaU][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0xaU][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0xaU][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0xaU][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0xaU][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0xaU][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0xaU][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0xaU][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0xbU][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0xbU][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0xbU][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0xbU][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0xbU][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0xbU][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0xbU][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0xbU][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0xbU][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0xbU][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0xbU][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0xbU][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0xbU][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0xbU][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0xbU][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0xbU][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0xcU][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0xcU][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0xcU][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0xcU][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0xcU][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0xcU][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0xcU][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0xcU][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0xcU][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0xcU][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0xcU][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0xcU][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0xcU][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0xcU][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0xcU][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0xcU][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0xdU][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0xdU][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0xdU][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0xdU][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0xdU][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0xdU][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0xdU][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0xdU][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0xdU][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0xdU][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0xdU][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0xdU][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0xdU][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0xdU][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0xdU][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0xdU][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0xeU][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0xeU][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0xeU][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0xeU][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0xeU][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0xeU][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0xeU][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0xeU][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0xeU][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0xeU][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0xeU][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0xeU][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0xeU][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0xeU][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0xeU][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0xeU][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0xfU][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0xfU][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0xfU][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0xfU][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0xfU][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0xfU][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0xfU][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0xfU][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0xfU][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0xfU][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0xfU][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0xfU][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0xfU][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0xfU][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0xfU][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0xfU][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x10U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x10U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x10U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x10U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x10U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x10U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x10U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x10U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x10U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x10U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x10U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x10U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x10U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x10U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x10U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x10U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x11U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x11U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x11U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x11U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x11U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x11U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x11U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x11U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x11U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x11U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x11U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x11U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x11U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x11U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x11U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x11U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x12U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x12U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x12U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x12U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x12U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x12U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x12U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x12U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x12U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x12U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x12U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x12U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x12U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x12U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x12U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x12U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x13U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x13U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x13U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x13U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x13U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x13U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x13U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x13U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x13U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x13U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x13U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x13U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x13U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x13U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x13U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x13U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x14U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x14U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x14U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x14U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x14U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x14U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x14U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x14U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x14U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x14U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x14U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x14U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x14U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x14U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x14U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x14U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x15U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x15U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x15U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x15U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x15U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x15U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x15U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x15U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x15U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x15U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x15U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x15U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x15U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x15U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x15U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x15U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x16U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x16U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x16U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x16U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x16U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x16U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x16U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x16U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x16U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x16U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x16U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x16U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x16U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x16U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x16U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x16U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x17U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x17U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x17U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x17U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x17U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x17U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x17U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x17U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x17U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x17U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x17U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x17U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x17U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x17U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x17U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x17U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x18U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x18U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x18U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x18U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x18U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x18U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x18U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x18U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x18U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x18U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x18U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x18U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x18U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x18U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x18U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x18U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x19U][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x19U][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x19U][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x19U][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x19U][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x19U][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x19U][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x19U][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x19U][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x19U][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x19U][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x19U][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x19U][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x19U][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x19U][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x19U][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x1aU][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x1aU][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x1aU][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x1aU][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x1aU][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x1aU][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x1aU][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x1aU][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x1aU][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x1aU][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x1aU][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x1aU][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x1aU][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x1aU][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x1aU][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x1aU][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x1bU][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x1bU][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x1bU][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x1bU][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x1bU][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x1bU][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x1bU][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x1bU][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x1bU][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x1bU][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x1bU][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x1bU][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x1bU][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x1bU][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x1bU][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x1bU][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x1cU][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x1cU][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x1cU][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x1cU][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x1cU][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x1cU][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x1cU][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x1cU][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x1cU][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x1cU][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x1cU][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x1cU][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x1cU][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x1cU][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x1cU][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x1cU][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x1dU][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x1dU][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x1dU][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x1dU][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x1dU][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x1dU][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x1dU][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x1dU][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x1dU][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x1dU][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x1dU][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x1dU][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x1dU][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x1dU][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x1dU][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x1dU][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x1eU][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x1eU][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x1eU][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x1eU][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x1eU][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x1eU][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x1eU][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x1eU][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x1eU][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x1eU][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x1eU][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x1eU][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x1eU][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x1eU][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x1eU][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x1eU][0xfU];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[0U] 
        = vlSelfRef.__PVT__bus[0x1fU][0U];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[1U] 
        = vlSelfRef.__PVT__bus[0x1fU][1U];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[2U] 
        = vlSelfRef.__PVT__bus[0x1fU][2U];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[3U] 
        = vlSelfRef.__PVT__bus[0x1fU][3U];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[4U] 
        = vlSelfRef.__PVT__bus[0x1fU][4U];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[5U] 
        = vlSelfRef.__PVT__bus[0x1fU][5U];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[6U] 
        = vlSelfRef.__PVT__bus[0x1fU][6U];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[7U] 
        = vlSelfRef.__PVT__bus[0x1fU][7U];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[8U] 
        = vlSelfRef.__PVT__bus[0x1fU][8U];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[9U] 
        = vlSelfRef.__PVT__bus[0x1fU][9U];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[0xaU] 
        = vlSelfRef.__PVT__bus[0x1fU][0xaU];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[0xbU] 
        = vlSelfRef.__PVT__bus[0x1fU][0xbU];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[0xcU] 
        = vlSelfRef.__PVT__bus[0x1fU][0xcU];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[0xdU] 
        = vlSelfRef.__PVT__bus[0x1fU][0xdU];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[0xeU] 
        = vlSelfRef.__PVT__bus[0x1fU][0xeU];
    vlSelfRef.__Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in[0xfU] 
        = vlSelfRef.__PVT__bus[0x1fU][0xfU];
    vlSelfRef.ch_out[0U] = vlSelfRef.__PVT__bus[0x20U]
        [0U];
    vlSelfRef.ch_out[1U] = vlSelfRef.__PVT__bus[0x20U]
        [1U];
    vlSelfRef.ch_out[2U] = vlSelfRef.__PVT__bus[0x20U]
        [2U];
    vlSelfRef.ch_out[3U] = vlSelfRef.__PVT__bus[0x20U]
        [3U];
    vlSelfRef.ch_out[4U] = vlSelfRef.__PVT__bus[0x20U]
        [4U];
    vlSelfRef.ch_out[5U] = vlSelfRef.__PVT__bus[0x20U]
        [5U];
    vlSelfRef.ch_out[6U] = vlSelfRef.__PVT__bus[0x20U]
        [6U];
    vlSelfRef.ch_out[7U] = vlSelfRef.__PVT__bus[0x20U]
        [7U];
    vlSelfRef.ch_out[8U] = vlSelfRef.__PVT__bus[0x20U]
        [8U];
    vlSelfRef.ch_out[9U] = vlSelfRef.__PVT__bus[0x20U]
        [9U];
    vlSelfRef.ch_out[0xaU] = vlSelfRef.__PVT__bus[0x20U]
        [0xaU];
    vlSelfRef.ch_out[0xbU] = vlSelfRef.__PVT__bus[0x20U]
        [0xbU];
    vlSelfRef.ch_out[0xcU] = vlSelfRef.__PVT__bus[0x20U]
        [0xcU];
    vlSelfRef.ch_out[0xdU] = vlSelfRef.__PVT__bus[0x20U]
        [0xdU];
    vlSelfRef.ch_out[0xeU] = vlSelfRef.__PVT__bus[0x20U]
        [0xeU];
    vlSelfRef.ch_out[0xfU] = vlSelfRef.__PVT__bus[0x20U]
        [0xfU];
}
