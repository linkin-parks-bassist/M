// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vpipeline.h for the primary calling header

#ifndef VERILATED_VPIPELINE___024ROOT_H_
#define VERILATED_VPIPELINE___024ROOT_H_  // guard

#include "verilated.h"


class Vpipeline__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vpipeline___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(in_valid,0,0);
        VL_IN8(reset,0,0);
        VL_OUT8(ready,0,0);
        VL_IN8(block_target,0,0);
        VL_IN8(reg_target,3,0);
        VL_IN8(instr_write,0,0);
        VL_IN8(reg_update,0,0);
        VL_IN8(reg_write,0,0);
        VL_OUT8(error,0,0);
        CData/*0:0*/ pipeline__DOT__invalid;
        CData/*1:0*/ pipeline__DOT__mul_done;
        CData/*0:0*/ pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done;
        CData/*0:0*/ pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_update;
        CData/*0:0*/ pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_write;
        CData/*0:0*/ pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done;
        CData/*0:0*/ pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_update;
        CData/*0:0*/ pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_write;
        CData/*0:0*/ pipeline__DOT__mul__DOT__index;
        CData/*4:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_unified_addr;
        CData/*0:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin;
        CData/*0:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready;
        CData/*4:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_unified_addr;
        CData/*0:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin;
        CData/*0:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        CData/*0:0*/ __VactContinue;
        VL_IN16(in_sample,15,0);
        VL_OUT16(out_sample,15,0);
        VL_IN16(reg_val,15,0);
        SData/*15:0*/ pipeline__DOT__sample_latched;
        SData/*15:0*/ pipeline__DOT__state;
        SData/*15:0*/ pipeline__DOT__ctr;
        SData/*15:0*/ pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b;
        SData/*15:0*/ pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a;
        SData/*15:0*/ pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b;
        SData/*15:0*/ pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_latched;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_b_latched;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_c_latched;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod;
        SData/*8:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_latched;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_b_latched;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_c_latched;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum;
        SData/*15:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod;
        SData/*8:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state;
        VL_IN(instr_val,31,0);
        IData/*31:0*/ pipeline__DOT__mul_result;
        IData/*31:0*/ pipeline__DOT__mul__DOT__i;
        IData/*31:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr;
        IData/*16:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum_ext;
        IData/*31:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_shifted;
        IData/*31:0*/ pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__i;
    };
    struct {
        IData/*31:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr;
        IData/*16:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum_ext;
        IData/*31:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_shifted;
        IData/*31:0*/ pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<VlUnpacked<SData/*15:0*/, 16>, 3> pipeline__DOT__bus;
        VlUnpacked<SData/*15:0*/, 2> pipeline__DOT__mul_bus_x;
        VlUnpacked<SData/*15:0*/, 2> pipeline__DOT__mul_bus_y;
        VlUnpacked<SData/*15:0*/, 2> pipeline__DOT____Vcellinp__mul__y;
        VlUnpacked<SData/*15:0*/, 2> pipeline__DOT____Vcellinp__mul__x;
        VlUnpacked<SData/*15:0*/, 16> pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs;
        VlUnpacked<SData/*15:0*/, 16> pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs;
        VlUnpacked<SData/*15:0*/, 16> pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates;
        VlUnpacked<CData/*0:0*/, 16> pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated;
        VlUnpacked<SData/*15:0*/, 32> pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs;
        VlUnpacked<SData/*15:0*/, 16> pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs;
        VlUnpacked<SData/*15:0*/, 16> pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs;
        VlUnpacked<SData/*15:0*/, 16> pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates;
        VlUnpacked<CData/*0:0*/, 16> pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated;
        VlUnpacked<SData/*15:0*/, 32> pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs;
        VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vpipeline__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vpipeline___024root(Vpipeline__Syms* symsp, const char* v__name);
    ~Vpipeline___024root();
    VL_UNCOPYABLE(Vpipeline___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
