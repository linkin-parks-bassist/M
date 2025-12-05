// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vpipeline.h for the primary calling header

#ifndef VERILATED_VPIPELINE_PIPELINE_SECTION_H_
#define VERILATED_VPIPELINE_PIPELINE_SECTION_H_  // guard

#include "verilated.h"


class Vpipeline__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vpipeline_pipeline_section final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(reset,0,0);
        IData/*31:0*/ __PVT__blocks__BRA__0__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__1__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__2__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__3__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__4__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__5__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__6__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__7__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__8__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__9__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__10__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__11__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__12__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__13__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__14__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__15__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__16__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__17__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__18__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__19__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__20__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__21__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__22__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__23__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__24__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__25__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__26__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__27__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__28__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__29__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__30__KET____DOT__block_inst__DOT__i;
        IData/*31:0*/ __PVT__blocks__BRA__31__KET____DOT__block_inst__DOT__i;
        VL_IN16(ch_in[16],15,0);
        VL_OUT16(ch_out[16],15,0);
        VlUnpacked<VlUnpacked<SData/*15:0*/, 16>, 33> __PVT__bus;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__2__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__2__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__3__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__3__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__4__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__4__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__5__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__5__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__6__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__6__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__7__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__7__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__8__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__8__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__9__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__9__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__10__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__10__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__11__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__11__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__12__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__12__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__13__KET____DOT__block_inst__ch_out;
    };
    struct {
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__13__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__14__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__14__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__15__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__15__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__16__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__16__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__17__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__17__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__18__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__18__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__19__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__19__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__20__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__20__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__21__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__21__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__22__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__22__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__23__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__23__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__24__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__24__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__25__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__25__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__26__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__26__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__27__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__27__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__28__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__28__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__29__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__29__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__30__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__30__KET____DOT__block_inst__ch_in;
        VlUnpacked<SData/*15:0*/, 16> __Vcellout__blocks__BRA__31__KET____DOT__block_inst__ch_out;
        VlUnpacked<SData/*15:0*/, 16> __Vcellinp__blocks__BRA__31__KET____DOT__block_inst__ch_in;
    };

    // INTERNAL VARIABLES
    Vpipeline__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vpipeline_pipeline_section(Vpipeline__Syms* symsp, const char* v__name);
    ~Vpipeline_pipeline_section();
    VL_UNCOPYABLE(Vpipeline_pipeline_section);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
