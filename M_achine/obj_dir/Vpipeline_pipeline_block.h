// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vpipeline.h for the primary calling header

#ifndef VERILATED_VPIPELINE_PIPELINE_BLOCK_H_
#define VERILATED_VPIPELINE_PIPELINE_BLOCK_H_  // guard

#include "verilated.h"


class Vpipeline__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vpipeline_pipeline_block final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(tick,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(instr_write,0,0);
    VL_IN8(reg_target,3,0);
    VL_IN8(reg_write,0,0);
    VL_IN8(mul_done,0,0);
    VL_OUT8(done,0,0);
    VL_IN16(reg_val,15,0);
    VL_OUT16(mul_req_a,15,0);
    VL_OUT16(mul_req_b,15,0);
    SData/*15:0*/ __PVT__summand_a;
    SData/*15:0*/ __PVT__summand_b;
    SData/*15:0*/ __PVT__sum;
    SData/*15:0*/ __PVT__prod;
    SData/*8:0*/ __PVT__state;
    VL_IN(instr_val,31,0);
    VL_IN(mul_result,31,0);
    IData/*31:0*/ __PVT__instr;
    IData/*16:0*/ __PVT__sum_ext;
    IData/*31:0*/ __PVT__i;
    VL_IN16(ch_in[16],15,0);
    VL_OUT16(ch_out[16],15,0);
    VlUnpacked<SData/*15:0*/, 16> __PVT__ch_regs;
    VlUnpacked<SData/*15:0*/, 16> __PVT__regs;

    // INTERNAL VARIABLES
    Vpipeline__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vpipeline_pipeline_block(Vpipeline__Syms* symsp, const char* v__name);
    ~Vpipeline_pipeline_block();
    VL_UNCOPYABLE(Vpipeline_pipeline_block);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
