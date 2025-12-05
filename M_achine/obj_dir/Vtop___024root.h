// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(tb_tx_valid,0,0);
    VL_OUT8(tb_tx_ready,0,0);
    VL_OUT8(tb_rx_valid,0,0);
    VL_IN8(tb_rx_ready,0,0);
    CData/*0:0*/ top__DOT__i2s_sck;
    CData/*0:0*/ top__DOT__i2s_ws;
    CData/*0:0*/ top__DOT__i2s_sd_out;
    CData/*0:0*/ top__DOT__i2s_sd_in;
    CData/*2:0*/ top__DOT__i2s0__DOT__div_cnt;
    CData/*0:0*/ top__DOT__i2s0__DOT__bclk_rise;
    CData/*5:0*/ top__DOT__i2s0__DOT__bit_cnt;
    CData/*0:0*/ top__DOT__i2s0__DOT__chan;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    VL_IN16(tb_tx_sample_l,15,0);
    VL_IN16(tb_tx_sample_r,15,0);
    VL_OUT16(tb_rx_sample_l,15,0);
    VL_OUT16(tb_rx_sample_r,15,0);
    SData/*15:0*/ top__DOT__i2s0__DOT__tx_shift;
    SData/*15:0*/ top__DOT__i2s0__DOT__rx_shift;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
