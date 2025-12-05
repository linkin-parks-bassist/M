// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vpipeline__Syms.h"


void Vpipeline___024root__trace_chg_0_sub_0(Vpipeline___024root* vlSelf, VerilatedFst::Buffer* bufp);

void Vpipeline___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root__trace_chg_0\n"); );
    // Init
    Vpipeline___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vpipeline___024root*>(voidSelf);
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vpipeline___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vpipeline___024root__trace_chg_0_sub_0(Vpipeline___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root__trace_chg_0_sub_0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgBit(oldp+0,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_write));
        bufp->chgBit(oldp+1,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_update));
        bufp->chgBit(oldp+2,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_write));
        bufp->chgBit(oldp+3,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_update));
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity
                      [2U])))) {
        bufp->chgSData(oldp+4,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0]),16);
        bufp->chgSData(oldp+5,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[1]),16);
        bufp->chgSData(oldp+6,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[2]),16);
        bufp->chgSData(oldp+7,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[3]),16);
        bufp->chgSData(oldp+8,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[4]),16);
        bufp->chgSData(oldp+9,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[5]),16);
        bufp->chgSData(oldp+10,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[6]),16);
        bufp->chgSData(oldp+11,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[7]),16);
        bufp->chgSData(oldp+12,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[8]),16);
        bufp->chgSData(oldp+13,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[9]),16);
        bufp->chgSData(oldp+14,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[10]),16);
        bufp->chgSData(oldp+15,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[11]),16);
        bufp->chgSData(oldp+16,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[12]),16);
        bufp->chgSData(oldp+17,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[13]),16);
        bufp->chgSData(oldp+18,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[14]),16);
        bufp->chgSData(oldp+19,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[15]),16);
        bufp->chgSData(oldp+20,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0]),16);
        bufp->chgSData(oldp+21,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[1]),16);
        bufp->chgSData(oldp+22,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[2]),16);
        bufp->chgSData(oldp+23,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[3]),16);
        bufp->chgSData(oldp+24,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[4]),16);
        bufp->chgSData(oldp+25,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[5]),16);
        bufp->chgSData(oldp+26,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[6]),16);
        bufp->chgSData(oldp+27,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[7]),16);
        bufp->chgSData(oldp+28,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[8]),16);
        bufp->chgSData(oldp+29,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[9]),16);
        bufp->chgSData(oldp+30,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[10]),16);
        bufp->chgSData(oldp+31,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[11]),16);
        bufp->chgSData(oldp+32,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[12]),16);
        bufp->chgSData(oldp+33,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[13]),16);
        bufp->chgSData(oldp+34,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[14]),16);
        bufp->chgSData(oldp+35,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[15]),16);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[2U]))) {
        bufp->chgSData(oldp+36,(vlSelfRef.pipeline__DOT__sample_latched),16);
        bufp->chgSData(oldp+37,(vlSelfRef.pipeline__DOT__state),16);
        bufp->chgSData(oldp+38,(vlSelfRef.pipeline__DOT__ctr),16);
        bufp->chgBit(oldp+39,(vlSelfRef.pipeline__DOT__invalid));
        bufp->chgCData(oldp+40,((((IData)(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done) 
                                  << 1U) | (IData)(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done))),2);
        bufp->chgSData(oldp+41,(vlSelfRef.pipeline__DOT__mul_bus_x[0]),16);
        bufp->chgSData(oldp+42,(vlSelfRef.pipeline__DOT__mul_bus_x[1]),16);
        bufp->chgSData(oldp+43,(vlSelfRef.pipeline__DOT__mul_bus_y[0]),16);
        bufp->chgSData(oldp+44,(vlSelfRef.pipeline__DOT__mul_bus_y[1]),16);
        bufp->chgIData(oldp+45,(vlSelfRef.pipeline__DOT__mul_result),32);
        bufp->chgCData(oldp+46,(vlSelfRef.pipeline__DOT__mul_done),2);
        bufp->chgSData(oldp+47,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[0]),16);
        bufp->chgSData(oldp+48,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[1]),16);
        bufp->chgSData(oldp+49,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[2]),16);
        bufp->chgSData(oldp+50,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[3]),16);
        bufp->chgSData(oldp+51,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[4]),16);
        bufp->chgSData(oldp+52,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[5]),16);
        bufp->chgSData(oldp+53,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[6]),16);
        bufp->chgSData(oldp+54,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[7]),16);
        bufp->chgSData(oldp+55,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[8]),16);
        bufp->chgSData(oldp+56,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[9]),16);
        bufp->chgSData(oldp+57,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[10]),16);
        bufp->chgSData(oldp+58,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[11]),16);
        bufp->chgSData(oldp+59,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[12]),16);
        bufp->chgSData(oldp+60,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[13]),16);
        bufp->chgSData(oldp+61,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[14]),16);
        bufp->chgSData(oldp+62,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[15]),16);
        bufp->chgSData(oldp+63,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a),16);
        bufp->chgSData(oldp+64,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b),16);
        bufp->chgBit(oldp+65,((1U & (IData)(vlSelfRef.pipeline__DOT__mul_done))));
        bufp->chgBit(oldp+66,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done));
        bufp->chgIData(oldp+67,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr),32);
        bufp->chgCData(oldp+68,((0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)),5);
        bufp->chgCData(oldp+69,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                         >> 5U))),4);
        bufp->chgCData(oldp+70,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                         >> 9U))),4);
        bufp->chgCData(oldp+71,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                         >> 0xdU))),4);
        bufp->chgCData(oldp+72,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                         >> 0x11U))),4);
        bufp->chgBit(oldp+73,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 0x15U))));
        bufp->chgBit(oldp+74,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 0x16U))));
        bufp->chgBit(oldp+75,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 0x17U))));
        bufp->chgBit(oldp+76,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                     >> 0x18U))));
        bufp->chgSData(oldp+77,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0]),16);
        bufp->chgSData(oldp+78,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[1]),16);
        bufp->chgSData(oldp+79,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[2]),16);
        bufp->chgSData(oldp+80,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[3]),16);
        bufp->chgSData(oldp+81,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[4]),16);
        bufp->chgSData(oldp+82,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[5]),16);
        bufp->chgSData(oldp+83,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[6]),16);
        bufp->chgSData(oldp+84,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[7]),16);
        bufp->chgSData(oldp+85,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[8]),16);
        bufp->chgSData(oldp+86,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[9]),16);
        bufp->chgSData(oldp+87,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[10]),16);
        bufp->chgSData(oldp+88,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[11]),16);
        bufp->chgSData(oldp+89,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[12]),16);
        bufp->chgSData(oldp+90,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[13]),16);
        bufp->chgSData(oldp+91,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[14]),16);
        bufp->chgSData(oldp+92,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[15]),16);
        bufp->chgSData(oldp+93,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0]),16);
        bufp->chgSData(oldp+94,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[1]),16);
        bufp->chgSData(oldp+95,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[2]),16);
        bufp->chgSData(oldp+96,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[3]),16);
        bufp->chgSData(oldp+97,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[4]),16);
        bufp->chgSData(oldp+98,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[5]),16);
        bufp->chgSData(oldp+99,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[6]),16);
        bufp->chgSData(oldp+100,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[7]),16);
        bufp->chgSData(oldp+101,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[8]),16);
        bufp->chgSData(oldp+102,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[9]),16);
        bufp->chgSData(oldp+103,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[10]),16);
        bufp->chgSData(oldp+104,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[11]),16);
        bufp->chgSData(oldp+105,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[12]),16);
        bufp->chgSData(oldp+106,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[13]),16);
        bufp->chgSData(oldp+107,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[14]),16);
        bufp->chgSData(oldp+108,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[15]),16);
        bufp->chgSData(oldp+109,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[0]),16);
        bufp->chgSData(oldp+110,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[1]),16);
        bufp->chgSData(oldp+111,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[2]),16);
        bufp->chgSData(oldp+112,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[3]),16);
        bufp->chgSData(oldp+113,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[4]),16);
        bufp->chgSData(oldp+114,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[5]),16);
        bufp->chgSData(oldp+115,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[6]),16);
        bufp->chgSData(oldp+116,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[7]),16);
        bufp->chgSData(oldp+117,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[8]),16);
        bufp->chgSData(oldp+118,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[9]),16);
        bufp->chgSData(oldp+119,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[10]),16);
        bufp->chgSData(oldp+120,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[11]),16);
        bufp->chgSData(oldp+121,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[12]),16);
        bufp->chgSData(oldp+122,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[13]),16);
        bufp->chgSData(oldp+123,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[14]),16);
        bufp->chgSData(oldp+124,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[15]),16);
        bufp->chgBit(oldp+125,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0]));
        bufp->chgBit(oldp+126,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[1]));
        bufp->chgBit(oldp+127,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[2]));
        bufp->chgBit(oldp+128,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[3]));
        bufp->chgBit(oldp+129,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[4]));
        bufp->chgBit(oldp+130,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[5]));
        bufp->chgBit(oldp+131,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[6]));
        bufp->chgBit(oldp+132,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[7]));
        bufp->chgBit(oldp+133,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[8]));
        bufp->chgBit(oldp+134,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[9]));
        bufp->chgBit(oldp+135,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[10]));
        bufp->chgBit(oldp+136,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[11]));
        bufp->chgBit(oldp+137,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[12]));
        bufp->chgBit(oldp+138,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[13]));
        bufp->chgBit(oldp+139,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[14]));
        bufp->chgBit(oldp+140,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[15]));
        bufp->chgSData(oldp+141,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0]),16);
        bufp->chgSData(oldp+142,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[1]),16);
        bufp->chgSData(oldp+143,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[2]),16);
        bufp->chgSData(oldp+144,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[3]),16);
        bufp->chgSData(oldp+145,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[4]),16);
        bufp->chgSData(oldp+146,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[5]),16);
        bufp->chgSData(oldp+147,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[6]),16);
        bufp->chgSData(oldp+148,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[7]),16);
        bufp->chgSData(oldp+149,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[8]),16);
        bufp->chgSData(oldp+150,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[9]),16);
        bufp->chgSData(oldp+151,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[10]),16);
        bufp->chgSData(oldp+152,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[11]),16);
        bufp->chgSData(oldp+153,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[12]),16);
        bufp->chgSData(oldp+154,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[13]),16);
        bufp->chgSData(oldp+155,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[14]),16);
        bufp->chgSData(oldp+156,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[15]),16);
        bufp->chgSData(oldp+157,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[16]),16);
        bufp->chgSData(oldp+158,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[17]),16);
        bufp->chgSData(oldp+159,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[18]),16);
        bufp->chgSData(oldp+160,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[19]),16);
        bufp->chgSData(oldp+161,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[20]),16);
        bufp->chgSData(oldp+162,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[21]),16);
        bufp->chgSData(oldp+163,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[22]),16);
        bufp->chgSData(oldp+164,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[23]),16);
        bufp->chgSData(oldp+165,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[24]),16);
        bufp->chgSData(oldp+166,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[25]),16);
        bufp->chgSData(oldp+167,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[26]),16);
        bufp->chgSData(oldp+168,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[27]),16);
        bufp->chgSData(oldp+169,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[28]),16);
        bufp->chgSData(oldp+170,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[29]),16);
        bufp->chgSData(oldp+171,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[30]),16);
        bufp->chgSData(oldp+172,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[31]),16);
        bufp->chgCData(oldp+173,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_unified_addr),5);
        bufp->chgCData(oldp+174,((0x1fU & ((0x400000U 
                                            & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                                            ? ((IData)(0x10U) 
                                               + (0xfU 
                                                  & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                     >> 9U)))
                                            : (0xfU 
                                               & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                  >> 9U))))),5);
        bufp->chgCData(oldp+175,((0x1fU & ((0x800000U 
                                            & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                                            ? ((IData)(0x10U) 
                                               + (0xfU 
                                                  & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                     >> 0xdU)))
                                            : (0xfU 
                                               & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                  >> 0xdU))))),5);
        bufp->chgCData(oldp+176,((0x1fU & ((0x1000000U 
                                            & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                                            ? ((IData)(0x10U) 
                                               + (0xfU 
                                                  & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                     >> 0x11U)))
                                            : (0xfU 
                                               & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                  >> 0x11U))))),5);
        bufp->chgSData(oldp+177,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_latched),16);
        bufp->chgSData(oldp+178,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a),16);
        bufp->chgSData(oldp+179,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b),16);
        bufp->chgIData(oldp+180,(((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a) 
                                               << 1U)) 
                                  | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a))),17);
        bufp->chgIData(oldp+181,(((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b) 
                                               << 1U)) 
                                  | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b))),17);
        bufp->chgIData(oldp+182,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum_ext),17);
        bufp->chgCData(oldp+183,(((5U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr))
                                   ? 1U : (0x1fU & 
                                           (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                            >> 0x19U)))),5);
        bufp->chgIData(oldp+184,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_shifted),32);
        bufp->chgSData(oldp+185,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final),16);
        bufp->chgSData(oldp+186,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum),16);
        bufp->chgSData(oldp+187,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod),16);
        bufp->chgBit(oldp+188,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin));
        bufp->chgBit(oldp+189,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready));
        bufp->chgSData(oldp+190,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state),9);
        bufp->chgIData(oldp+191,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__i),32);
        bufp->chgSData(oldp+192,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[0]),16);
        bufp->chgSData(oldp+193,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[1]),16);
        bufp->chgSData(oldp+194,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[2]),16);
        bufp->chgSData(oldp+195,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[3]),16);
        bufp->chgSData(oldp+196,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[4]),16);
        bufp->chgSData(oldp+197,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[5]),16);
        bufp->chgSData(oldp+198,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[6]),16);
        bufp->chgSData(oldp+199,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[7]),16);
        bufp->chgSData(oldp+200,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[8]),16);
        bufp->chgSData(oldp+201,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[9]),16);
        bufp->chgSData(oldp+202,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[10]),16);
        bufp->chgSData(oldp+203,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[11]),16);
        bufp->chgSData(oldp+204,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[12]),16);
        bufp->chgSData(oldp+205,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[13]),16);
        bufp->chgSData(oldp+206,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[14]),16);
        bufp->chgSData(oldp+207,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[15]),16);
        bufp->chgSData(oldp+208,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a),16);
        bufp->chgSData(oldp+209,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b),16);
        bufp->chgBit(oldp+210,((1U & ((IData)(vlSelfRef.pipeline__DOT__mul_done) 
                                      >> 1U))));
        bufp->chgBit(oldp+211,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done));
        bufp->chgIData(oldp+212,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr),32);
        bufp->chgCData(oldp+213,((0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)),5);
        bufp->chgCData(oldp+214,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                          >> 5U))),4);
        bufp->chgCData(oldp+215,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                          >> 9U))),4);
        bufp->chgCData(oldp+216,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                          >> 0xdU))),4);
        bufp->chgCData(oldp+217,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                          >> 0x11U))),4);
        bufp->chgBit(oldp+218,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                      >> 0x15U))));
        bufp->chgBit(oldp+219,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                      >> 0x16U))));
        bufp->chgBit(oldp+220,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                      >> 0x17U))));
        bufp->chgBit(oldp+221,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                      >> 0x18U))));
        bufp->chgSData(oldp+222,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0]),16);
        bufp->chgSData(oldp+223,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[1]),16);
        bufp->chgSData(oldp+224,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[2]),16);
        bufp->chgSData(oldp+225,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[3]),16);
        bufp->chgSData(oldp+226,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[4]),16);
        bufp->chgSData(oldp+227,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[5]),16);
        bufp->chgSData(oldp+228,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[6]),16);
        bufp->chgSData(oldp+229,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[7]),16);
        bufp->chgSData(oldp+230,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[8]),16);
        bufp->chgSData(oldp+231,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[9]),16);
        bufp->chgSData(oldp+232,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[10]),16);
        bufp->chgSData(oldp+233,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[11]),16);
        bufp->chgSData(oldp+234,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[12]),16);
        bufp->chgSData(oldp+235,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[13]),16);
        bufp->chgSData(oldp+236,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[14]),16);
        bufp->chgSData(oldp+237,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[15]),16);
        bufp->chgSData(oldp+238,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0]),16);
        bufp->chgSData(oldp+239,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[1]),16);
        bufp->chgSData(oldp+240,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[2]),16);
        bufp->chgSData(oldp+241,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[3]),16);
        bufp->chgSData(oldp+242,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[4]),16);
        bufp->chgSData(oldp+243,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[5]),16);
        bufp->chgSData(oldp+244,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[6]),16);
        bufp->chgSData(oldp+245,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[7]),16);
        bufp->chgSData(oldp+246,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[8]),16);
        bufp->chgSData(oldp+247,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[9]),16);
        bufp->chgSData(oldp+248,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[10]),16);
        bufp->chgSData(oldp+249,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[11]),16);
        bufp->chgSData(oldp+250,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[12]),16);
        bufp->chgSData(oldp+251,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[13]),16);
        bufp->chgSData(oldp+252,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[14]),16);
        bufp->chgSData(oldp+253,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[15]),16);
        bufp->chgSData(oldp+254,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[0]),16);
        bufp->chgSData(oldp+255,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[1]),16);
        bufp->chgSData(oldp+256,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[2]),16);
        bufp->chgSData(oldp+257,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[3]),16);
        bufp->chgSData(oldp+258,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[4]),16);
        bufp->chgSData(oldp+259,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[5]),16);
        bufp->chgSData(oldp+260,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[6]),16);
        bufp->chgSData(oldp+261,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[7]),16);
        bufp->chgSData(oldp+262,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[8]),16);
        bufp->chgSData(oldp+263,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[9]),16);
        bufp->chgSData(oldp+264,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[10]),16);
        bufp->chgSData(oldp+265,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[11]),16);
        bufp->chgSData(oldp+266,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[12]),16);
        bufp->chgSData(oldp+267,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[13]),16);
        bufp->chgSData(oldp+268,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[14]),16);
        bufp->chgSData(oldp+269,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[15]),16);
        bufp->chgBit(oldp+270,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0]));
        bufp->chgBit(oldp+271,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[1]));
        bufp->chgBit(oldp+272,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[2]));
        bufp->chgBit(oldp+273,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[3]));
        bufp->chgBit(oldp+274,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[4]));
        bufp->chgBit(oldp+275,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[5]));
        bufp->chgBit(oldp+276,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[6]));
        bufp->chgBit(oldp+277,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[7]));
        bufp->chgBit(oldp+278,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[8]));
        bufp->chgBit(oldp+279,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[9]));
        bufp->chgBit(oldp+280,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[10]));
        bufp->chgBit(oldp+281,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[11]));
        bufp->chgBit(oldp+282,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[12]));
        bufp->chgBit(oldp+283,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[13]));
        bufp->chgBit(oldp+284,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[14]));
        bufp->chgBit(oldp+285,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[15]));
        bufp->chgSData(oldp+286,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0]),16);
        bufp->chgSData(oldp+287,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[1]),16);
        bufp->chgSData(oldp+288,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[2]),16);
        bufp->chgSData(oldp+289,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[3]),16);
        bufp->chgSData(oldp+290,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[4]),16);
        bufp->chgSData(oldp+291,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[5]),16);
        bufp->chgSData(oldp+292,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[6]),16);
        bufp->chgSData(oldp+293,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[7]),16);
        bufp->chgSData(oldp+294,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[8]),16);
        bufp->chgSData(oldp+295,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[9]),16);
        bufp->chgSData(oldp+296,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[10]),16);
        bufp->chgSData(oldp+297,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[11]),16);
        bufp->chgSData(oldp+298,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[12]),16);
        bufp->chgSData(oldp+299,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[13]),16);
        bufp->chgSData(oldp+300,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[14]),16);
        bufp->chgSData(oldp+301,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[15]),16);
        bufp->chgSData(oldp+302,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[16]),16);
        bufp->chgSData(oldp+303,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[17]),16);
        bufp->chgSData(oldp+304,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[18]),16);
        bufp->chgSData(oldp+305,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[19]),16);
        bufp->chgSData(oldp+306,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[20]),16);
        bufp->chgSData(oldp+307,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[21]),16);
        bufp->chgSData(oldp+308,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[22]),16);
        bufp->chgSData(oldp+309,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[23]),16);
        bufp->chgSData(oldp+310,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[24]),16);
        bufp->chgSData(oldp+311,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[25]),16);
        bufp->chgSData(oldp+312,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[26]),16);
        bufp->chgSData(oldp+313,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[27]),16);
        bufp->chgSData(oldp+314,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[28]),16);
        bufp->chgSData(oldp+315,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[29]),16);
        bufp->chgSData(oldp+316,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[30]),16);
        bufp->chgSData(oldp+317,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[31]),16);
        bufp->chgCData(oldp+318,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_unified_addr),5);
        bufp->chgCData(oldp+319,((0x1fU & ((0x400000U 
                                            & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                                            ? ((IData)(0x10U) 
                                               + (0xfU 
                                                  & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                     >> 9U)))
                                            : (0xfU 
                                               & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                  >> 9U))))),5);
        bufp->chgCData(oldp+320,((0x1fU & ((0x800000U 
                                            & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                                            ? ((IData)(0x10U) 
                                               + (0xfU 
                                                  & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                     >> 0xdU)))
                                            : (0xfU 
                                               & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                  >> 0xdU))))),5);
        bufp->chgCData(oldp+321,((0x1fU & ((0x1000000U 
                                            & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                                            ? ((IData)(0x10U) 
                                               + (0xfU 
                                                  & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                     >> 0x11U)))
                                            : (0xfU 
                                               & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                  >> 0x11U))))),5);
        bufp->chgSData(oldp+322,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_latched),16);
        bufp->chgSData(oldp+323,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a),16);
        bufp->chgSData(oldp+324,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b),16);
        bufp->chgIData(oldp+325,(((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a) 
                                               << 1U)) 
                                  | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a))),17);
        bufp->chgIData(oldp+326,(((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b) 
                                               << 1U)) 
                                  | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b))),17);
        bufp->chgIData(oldp+327,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum_ext),17);
        bufp->chgCData(oldp+328,(((5U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr))
                                   ? 1U : (0x1fU & 
                                           (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                            >> 0x19U)))),5);
        bufp->chgIData(oldp+329,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_shifted),32);
        bufp->chgSData(oldp+330,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final),16);
        bufp->chgSData(oldp+331,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum),16);
        bufp->chgSData(oldp+332,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod),16);
        bufp->chgBit(oldp+333,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin));
        bufp->chgBit(oldp+334,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready));
        bufp->chgSData(oldp+335,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state),9);
        bufp->chgIData(oldp+336,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__i),32);
        bufp->chgSData(oldp+337,(vlSelfRef.pipeline__DOT____Vcellinp__mul__x[0]),16);
        bufp->chgSData(oldp+338,(vlSelfRef.pipeline__DOT____Vcellinp__mul__x[1]),16);
        bufp->chgSData(oldp+339,(vlSelfRef.pipeline__DOT____Vcellinp__mul__y[0]),16);
        bufp->chgSData(oldp+340,(vlSelfRef.pipeline__DOT____Vcellinp__mul__y[1]),16);
        bufp->chgBit(oldp+341,(vlSelfRef.pipeline__DOT__mul__DOT__index));
        bufp->chgIData(oldp+342,(vlSelfRef.pipeline__DOT__mul__DOT__i),32);
    }
    bufp->chgBit(oldp+343,(vlSelfRef.clk));
    bufp->chgSData(oldp+344,(vlSelfRef.in_sample),16);
    bufp->chgBit(oldp+345,(vlSelfRef.in_valid));
    bufp->chgBit(oldp+346,(vlSelfRef.reset));
    bufp->chgSData(oldp+347,(vlSelfRef.out_sample),16);
    bufp->chgBit(oldp+348,(vlSelfRef.ready));
    bufp->chgBit(oldp+349,(vlSelfRef.block_target));
    bufp->chgCData(oldp+350,(vlSelfRef.reg_target),4);
    bufp->chgIData(oldp+351,(vlSelfRef.instr_val),32);
    bufp->chgBit(oldp+352,(vlSelfRef.instr_write));
    bufp->chgSData(oldp+353,(vlSelfRef.reg_val),16);
    bufp->chgBit(oldp+354,(vlSelfRef.reg_update));
    bufp->chgBit(oldp+355,(vlSelfRef.reg_write));
    bufp->chgBit(oldp+356,(vlSelfRef.error));
    bufp->chgBit(oldp+357,(((IData)(vlSelfRef.instr_write) 
                            & (~ (IData)(vlSelfRef.block_target)))));
    bufp->chgBit(oldp+358,(((IData)(vlSelfRef.instr_write) 
                            & (IData)(vlSelfRef.block_target))));
}

void Vpipeline___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root__trace_cleanup\n"); );
    // Init
    Vpipeline___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vpipeline___024root*>(voidSelf);
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
