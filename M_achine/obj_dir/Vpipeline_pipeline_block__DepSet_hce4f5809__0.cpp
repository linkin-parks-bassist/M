// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline.h for the primary calling header

#include "Vpipeline__pch.h"
#include "Vpipeline__Syms.h"
#include "Vpipeline_pipeline_block.h"

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)(vlSymsp->TOP.pipeline__DOT__mul_done))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (0U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (0U == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 1U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (1U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (1U == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__2__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__2__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 2U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (2U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (2U == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__3__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__3__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 3U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (3U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (3U == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__4__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__4__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 4U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (4U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (4U == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__5__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__5__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 5U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (5U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (5U == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__6__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__6__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 6U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (6U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (6U == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__7__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__7__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 7U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (7U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (7U == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__8__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__8__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 8U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (8U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (8U == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__9__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__9__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 9U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (9U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (9U == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__10__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__10__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 0xaU)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (0xaU == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (0xaU 
                                              == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__11__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__11__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 0xbU)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (0xbU == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (0xbU 
                                              == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__12__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__12__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 0xcU)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (0xcU == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (0xcU 
                                              == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__13__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__13__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 0xdU)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (0xdU == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (0xdU 
                                              == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__14__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__14__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 0xeU)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (0xeU == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (0xeU 
                                              == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__15__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__15__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 0xfU)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (0xfU == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (0xfU 
                                              == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__16__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__16__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 0x10U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (0x10U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (0x10U 
                                              == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__17__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__17__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 0x11U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (0x11U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (0x11U 
                                              == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__18__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__18__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 0x12U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (0x12U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (0x12U 
                                              == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__19__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__19__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 0x13U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (0x13U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (0x13U 
                                              == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}

VL_INLINE_OPT void Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__20__KET____DOT__block_inst__0(Vpipeline_pipeline_block* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_pipeline_block___nba_sequent__TOP__pipeline__DOT__blocks__BRA__20__KET____DOT__block_inst__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vdly__state;
    __Vdly__state = 0;
    CData/*0:0*/ __Vdly__done;
    __Vdly__done = 0;
    SData/*15:0*/ __Vdly__prod;
    __Vdly__prod = 0;
    SData/*15:0*/ __VdlyVal__regs__v0;
    __VdlyVal__regs__v0 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v0;
    __VdlyDim0__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__regs__v0;
    __VdlySet__regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v0;
    __VdlyVal__ch_regs__v0 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v0;
    __VdlySet__ch_regs__v0 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v1;
    __VdlyVal__ch_regs__v1 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v1;
    __VdlySet__ch_regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v2;
    __VdlyVal__ch_regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v3;
    __VdlyVal__ch_regs__v3 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v4;
    __VdlyVal__ch_regs__v4 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v5;
    __VdlyVal__ch_regs__v5 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v6;
    __VdlyVal__ch_regs__v6 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v7;
    __VdlyVal__ch_regs__v7 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v8;
    __VdlyVal__ch_regs__v8 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v9;
    __VdlyVal__ch_regs__v9 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v10;
    __VdlyVal__ch_regs__v10 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v11;
    __VdlyVal__ch_regs__v11 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v12;
    __VdlyVal__ch_regs__v12 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v13;
    __VdlyVal__ch_regs__v13 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v14;
    __VdlyVal__ch_regs__v14 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v15;
    __VdlyVal__ch_regs__v15 = 0;
    SData/*15:0*/ __VdlyVal__regs__v1;
    __VdlyVal__regs__v1 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v1;
    __VdlyDim0__regs__v1 = 0;
    CData/*0:0*/ __VdlySet__regs__v1;
    __VdlySet__regs__v1 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v16;
    __VdlyVal__ch_regs__v16 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v16;
    __VdlyDim0__ch_regs__v16 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v16;
    __VdlySet__ch_regs__v16 = 0;
    SData/*15:0*/ __VdlyVal__regs__v2;
    __VdlyVal__regs__v2 = 0;
    CData/*3:0*/ __VdlyDim0__regs__v2;
    __VdlyDim0__regs__v2 = 0;
    CData/*0:0*/ __VdlySet__regs__v2;
    __VdlySet__regs__v2 = 0;
    SData/*15:0*/ __VdlyVal__ch_regs__v17;
    __VdlyVal__ch_regs__v17 = 0;
    CData/*3:0*/ __VdlyDim0__ch_regs__v17;
    __VdlyDim0__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v17;
    __VdlySet__ch_regs__v17 = 0;
    CData/*0:0*/ __VdlySet__ch_regs__v18;
    __VdlySet__ch_regs__v18 = 0;
    // Body
    __Vdly__state = vlSelfRef.__PVT__state;
    __Vdly__prod = vlSelfRef.__PVT__prod;
    __VdlySet__regs__v0 = 0U;
    __VdlySet__regs__v1 = 0U;
    __VdlySet__regs__v2 = 0U;
    __Vdly__done = vlSelfRef.done;
    __VdlySet__ch_regs__v0 = 0U;
    __VdlySet__ch_regs__v1 = 0U;
    __VdlySet__ch_regs__v16 = 0U;
    __VdlySet__ch_regs__v17 = 0U;
    __VdlySet__ch_regs__v18 = 0U;
    if (vlSymsp->TOP.in_valid) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlyVal__ch_regs__v0 = vlSelfRef.ch_in[0U];
        __VdlySet__ch_regs__v0 = 1U;
        __Vdly__state = 0U;
        __Vdly__done = 0U;
        __VdlyVal__ch_regs__v1 = vlSelfRef.ch_in[1U];
        __VdlySet__ch_regs__v1 = 1U;
        __VdlyVal__ch_regs__v2 = vlSelfRef.ch_in[2U];
        __VdlyVal__ch_regs__v3 = vlSelfRef.ch_in[3U];
        __VdlyVal__ch_regs__v4 = vlSelfRef.ch_in[4U];
        __VdlyVal__ch_regs__v5 = vlSelfRef.ch_in[5U];
        __VdlyVal__ch_regs__v6 = vlSelfRef.ch_in[6U];
        __VdlyVal__ch_regs__v7 = vlSelfRef.ch_in[7U];
        __VdlyVal__ch_regs__v8 = vlSelfRef.ch_in[8U];
        __VdlyVal__ch_regs__v9 = vlSelfRef.ch_in[9U];
        __VdlyVal__ch_regs__v10 = vlSelfRef.ch_in[0xaU];
        __VdlyVal__ch_regs__v11 = vlSelfRef.ch_in[0xbU];
        __VdlyVal__ch_regs__v12 = vlSelfRef.ch_in[0xcU];
        __VdlyVal__ch_regs__v13 = vlSelfRef.ch_in[0xdU];
        __VdlyVal__ch_regs__v14 = vlSelfRef.ch_in[0xeU];
        __VdlyVal__ch_regs__v15 = vlSelfRef.ch_in[0xfU];
    } else if ((1U & (~ (IData)(vlSelfRef.done)))) {
        if ((0U == (0x1fU & vlSelfRef.__PVT__instr))) {
            __Vdly__done = 1U;
        } else if ((1U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.__PVT__summand_a = ((0x200000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.__PVT__summand_b = ((0x400000U 
                                               & vlSelfRef.__PVT__instr)
                                               ? vlSelfRef.__PVT__regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]
                                               : vlSelfRef.__PVT__ch_regs
                                              [(0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v1 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__regs__v1 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v1 = 1U;
                } else {
                    __VdlyVal__ch_regs__v16 = vlSelfRef.__PVT__sum;
                    __VdlyDim0__ch_regs__v16 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v16 = 1U;
                }
                __Vdly__state = 1U;
            }
            __Vdly__done = 1U;
        } else if ((2U == (0x1fU & vlSelfRef.__PVT__instr))) {
            if ((0U == (IData)(vlSelfRef.__PVT__state))) {
                vlSelfRef.mul_req_a = ((0x200000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 5U))]);
                __Vdly__state = 2U;
                vlSelfRef.mul_req_b = ((0x400000U & vlSelfRef.__PVT__instr)
                                        ? vlSelfRef.__PVT__regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]
                                        : vlSelfRef.__PVT__ch_regs
                                       [(0xfU & (vlSelfRef.__PVT__instr 
                                                 >> 9U))]);
            } else if ((2U == (IData)(vlSelfRef.__PVT__state))) {
                if ((1U & (IData)((vlSymsp->TOP.pipeline__DOT__mul_done 
                                   >> 0x14U)))) {
                    __Vdly__prod = ((1U == (vlSymsp->TOP.pipeline__DOT__mul_result 
                                            >> 0x1eU))
                                     ? 0x7fffU : ((2U 
                                                   == 
                                                   (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                    >> 0x1eU))
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & (vlSymsp->TOP.pipeline__DOT__mul_result 
                                                      >> 0xfU))));
                    __Vdly__state = 3U;
                }
            } else if ((3U == (IData)(vlSelfRef.__PVT__state))) {
                if ((0x1000000U & vlSelfRef.__PVT__instr)) {
                    __VdlyVal__regs__v2 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__regs__v2 = (0xfU & 
                                            (vlSelfRef.__PVT__instr 
                                             >> 0x11U));
                    __VdlySet__regs__v2 = 1U;
                } else {
                    __VdlyVal__ch_regs__v17 = vlSelfRef.__PVT__prod;
                    __VdlyDim0__ch_regs__v17 = (0xfU 
                                                & (vlSelfRef.__PVT__instr 
                                                   >> 0x11U));
                    __VdlySet__ch_regs__v17 = 1U;
                }
                __Vdly__state = 1U;
                __Vdly__done = 1U;
            }
        }
    }
    if (vlSymsp->TOP.reset) {
        vlSelfRef.__PVT__i = 0x10U;
        __VdlySet__ch_regs__v18 = 1U;
    }
    if (((IData)(vlSymsp->TOP.reg_write) & (0x14U == (IData)(vlSymsp->TOP.block_target)))) {
        __VdlyVal__regs__v0 = vlSymsp->TOP.reg_val;
        __VdlyDim0__regs__v0 = vlSymsp->TOP.reg_target;
        __VdlySet__regs__v0 = 1U;
    }
    vlSelfRef.__PVT__state = __Vdly__state;
    vlSelfRef.__PVT__prod = __Vdly__prod;
    vlSelfRef.done = __Vdly__done;
    if (__VdlySet__regs__v0) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v0] 
            = __VdlyVal__regs__v0;
    }
    if (__VdlySet__regs__v1) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v1] 
            = __VdlyVal__regs__v1;
    }
    if (__VdlySet__regs__v2) {
        vlSelfRef.__PVT__regs[__VdlyDim0__regs__v2] 
            = __VdlyVal__regs__v2;
    }
    if (__VdlySet__ch_regs__v0) {
        vlSelfRef.__PVT__ch_regs[0U] = __VdlyVal__ch_regs__v0;
    }
    if (__VdlySet__ch_regs__v1) {
        vlSelfRef.__PVT__ch_regs[1U] = __VdlyVal__ch_regs__v1;
        vlSelfRef.__PVT__ch_regs[2U] = __VdlyVal__ch_regs__v2;
        vlSelfRef.__PVT__ch_regs[3U] = __VdlyVal__ch_regs__v3;
        vlSelfRef.__PVT__ch_regs[4U] = __VdlyVal__ch_regs__v4;
        vlSelfRef.__PVT__ch_regs[5U] = __VdlyVal__ch_regs__v5;
        vlSelfRef.__PVT__ch_regs[6U] = __VdlyVal__ch_regs__v6;
        vlSelfRef.__PVT__ch_regs[7U] = __VdlyVal__ch_regs__v7;
        vlSelfRef.__PVT__ch_regs[8U] = __VdlyVal__ch_regs__v8;
        vlSelfRef.__PVT__ch_regs[9U] = __VdlyVal__ch_regs__v9;
        vlSelfRef.__PVT__ch_regs[0xaU] = __VdlyVal__ch_regs__v10;
        vlSelfRef.__PVT__ch_regs[0xbU] = __VdlyVal__ch_regs__v11;
        vlSelfRef.__PVT__ch_regs[0xcU] = __VdlyVal__ch_regs__v12;
        vlSelfRef.__PVT__ch_regs[0xdU] = __VdlyVal__ch_regs__v13;
        vlSelfRef.__PVT__ch_regs[0xeU] = __VdlyVal__ch_regs__v14;
        vlSelfRef.__PVT__ch_regs[0xfU] = __VdlyVal__ch_regs__v15;
    }
    if (__VdlySet__ch_regs__v16) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v16] 
            = __VdlyVal__ch_regs__v16;
    }
    if (__VdlySet__ch_regs__v17) {
        vlSelfRef.__PVT__ch_regs[__VdlyDim0__ch_regs__v17] 
            = __VdlyVal__ch_regs__v17;
    }
    if (__VdlySet__ch_regs__v18) {
        vlSelfRef.__PVT__regs[0U] = 0U;
        vlSelfRef.__PVT__regs[1U] = 0U;
        vlSelfRef.__PVT__regs[2U] = 0U;
        vlSelfRef.__PVT__regs[3U] = 0U;
        vlSelfRef.__PVT__regs[4U] = 0U;
        vlSelfRef.__PVT__regs[5U] = 0U;
        vlSelfRef.__PVT__regs[6U] = 0U;
        vlSelfRef.__PVT__regs[7U] = 0U;
        vlSelfRef.__PVT__regs[8U] = 0U;
        vlSelfRef.__PVT__regs[9U] = 0U;
        vlSelfRef.__PVT__regs[0xaU] = 0U;
        vlSelfRef.__PVT__regs[0xbU] = 0U;
        vlSelfRef.__PVT__regs[0xcU] = 0U;
        vlSelfRef.__PVT__regs[0xdU] = 0U;
        vlSelfRef.__PVT__regs[0xeU] = 0U;
        vlSelfRef.__PVT__regs[0xfU] = 0U;
        vlSelfRef.__PVT__ch_regs[0U] = 0U;
        vlSelfRef.__PVT__ch_regs[1U] = 0U;
        vlSelfRef.__PVT__ch_regs[2U] = 0U;
        vlSelfRef.__PVT__ch_regs[3U] = 0U;
        vlSelfRef.__PVT__ch_regs[4U] = 0U;
        vlSelfRef.__PVT__ch_regs[5U] = 0U;
        vlSelfRef.__PVT__ch_regs[6U] = 0U;
        vlSelfRef.__PVT__ch_regs[7U] = 0U;
        vlSelfRef.__PVT__ch_regs[8U] = 0U;
        vlSelfRef.__PVT__ch_regs[9U] = 0U;
        vlSelfRef.__PVT__ch_regs[0xaU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xbU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xcU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xdU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xeU] = 0U;
        vlSelfRef.__PVT__ch_regs[0xfU] = 0U;
    }
    vlSelfRef.__PVT__sum = (VL_LTS_III(17, 0xffffU, vlSelfRef.__PVT__sum_ext)
                             ? 0x7fffU : (VL_GTS_III(17, 0x10000U, vlSelfRef.__PVT__sum_ext)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlSelfRef.__PVT__sum_ext)));
    if (((IData)(vlSymsp->TOP.instr_write) & (0x14U 
                                              == (IData)(vlSymsp->TOP.block_target)))) {
        vlSelfRef.__PVT__instr = vlSymsp->TOP.instr_val;
    }
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
    vlSelfRef.__PVT__sum_ext = (0x1ffffU & (((0x10000U 
                                              & ((IData)(vlSelfRef.__PVT__summand_a) 
                                                 << 1U)) 
                                             | (IData)(vlSelfRef.__PVT__summand_a)) 
                                            + ((0x10000U 
                                                & ((IData)(vlSelfRef.__PVT__summand_b) 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.__PVT__summand_b))));
}
