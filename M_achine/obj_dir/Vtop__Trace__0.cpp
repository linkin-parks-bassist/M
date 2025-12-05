// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgBit(oldp+0,(vlSelfRef.top__DOT__i2s_sck));
        bufp->chgBit(oldp+1,(vlSelfRef.top__DOT__i2s_ws));
        bufp->chgBit(oldp+2,(vlSelfRef.top__DOT__i2s_sd_out));
        bufp->chgCData(oldp+3,(vlSelfRef.top__DOT__i2s0__DOT__div_cnt),3);
        bufp->chgBit(oldp+4,(vlSelfRef.top__DOT__i2s0__DOT__bclk_rise));
        bufp->chgCData(oldp+5,(vlSelfRef.top__DOT__i2s0__DOT__bit_cnt),6);
        bufp->chgBit(oldp+6,(vlSelfRef.top__DOT__i2s0__DOT__chan));
        bufp->chgSData(oldp+7,(vlSelfRef.top__DOT__i2s0__DOT__tx_shift),16);
        bufp->chgSData(oldp+8,(vlSelfRef.top__DOT__i2s0__DOT__rx_shift),16);
    }
    bufp->chgBit(oldp+9,(vlSelfRef.clk));
    bufp->chgBit(oldp+10,(vlSelfRef.rst));
    bufp->chgSData(oldp+11,(vlSelfRef.tb_tx_sample_l),16);
    bufp->chgSData(oldp+12,(vlSelfRef.tb_tx_sample_r),16);
    bufp->chgBit(oldp+13,(vlSelfRef.tb_tx_valid));
    bufp->chgBit(oldp+14,(vlSelfRef.tb_tx_ready));
    bufp->chgSData(oldp+15,(vlSelfRef.tb_rx_sample_l),16);
    bufp->chgSData(oldp+16,(vlSelfRef.tb_rx_sample_r),16);
    bufp->chgBit(oldp+17,(vlSelfRef.tb_rx_valid));
    bufp->chgBit(oldp+18,(vlSelfRef.tb_rx_ready));
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
