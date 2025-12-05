// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vpipeline__Syms.h"


VL_ATTR_COLD void Vpipeline___024root__trace_init_sub__TOP__0(Vpipeline___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root__trace_init_sub__TOP__0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+344,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+345,0,"in_sample",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+346,0,"in_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+347,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+348,0,"out_sample",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+349,0,"ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+350,0,"block_target",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+351,0,"reg_target",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+352,0,"instr_val",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+353,0,"instr_write",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+354,0,"reg_val",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+355,0,"reg_update",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+356,0,"reg_write",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+357,0,"error",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("pipeline", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+360,0,"n_blocks",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+361,0,"n_block_registers",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+361,0,"data_width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+361,0,"n_channels",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+344,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+345,0,"in_sample",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+346,0,"in_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+347,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+348,0,"out_sample",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+349,0,"ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+350,0,"block_target",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+351,0,"reg_target",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+352,0,"instr_val",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+353,0,"instr_write",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+354,0,"reg_val",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+355,0,"reg_update",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+356,0,"reg_write",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+357,0,"error",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+37,0,"sample_latched",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+38,0,"state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+39,0,"ctr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+40,0,"invalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+41,0,"dones",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->pushPrefix("mul_bus_x", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+42+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("mul_bus_y", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+44+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+46,0,"mul_result",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+47,0,"mul_done",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->pushPrefix("blocks[0]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("block_inst", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+362,0,"data_width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+362,0,"n_channels",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+362,0,"n_registers",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBit(c+344,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+346,0,"tick",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+347,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("ch_in", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+5+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("ch_out", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+48+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+352,0,"instr_val",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+358,0,"instr_write",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+354,0,"reg_val",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+351,0,"reg_target",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+1,0,"reg_write",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"reg_update",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+64,0,"mul_req_a",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+65,0,"mul_req_b",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+46,0,"mul_result",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+66,0,"mul_done",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+68,0,"instr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+69,0,"operation",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+70,0,"src_a",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+71,0,"src_b",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+72,0,"src_c",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+73,0,"dest",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+363,0,"operand_type_start_index",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+74,0,"src_a_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+75,0,"src_b_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+76,0,"src_c_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+77,0,"dest_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+364,0,"pms_start_index",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("ch_regs", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+78+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("regs", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+94+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("reg_updates", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+110+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("reg_updated", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBit(c+126+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("unified_regs", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+142+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+365,0,"UNIFIED_W",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+174,0,"src_a_unified_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+175,0,"src_b_unified_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+176,0,"src_c_unified_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+177,0,"dest_unified_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+178,0,"src_a_latched",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+366,0,"src_b_latched",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+367,0,"src_c_latched",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+179,0,"summand_a",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+180,0,"summand_b",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+181,0,"summand_a_ext",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 16,0);
    tracep->declBus(c+182,0,"summand_b_ext",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 16,0);
    tracep->declBus(c+183,0,"sum_ext",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 16,0);
    tracep->declBus(c+368,0,"MAX_SHIFT",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+369,0,"SHIFT_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+184,0,"post_mul_shift",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+370,0,"SAT_MAX_EXT",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+371,0,"SAT_MIN_EXT",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+185,0,"mul_result_shifted",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+186,0,"mul_result_final",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+187,0,"sum",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+188,0,"prod",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+189,0,"mul_wait_begin",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+190,0,"mul_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+191,0,"state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 8,0);
    tracep->declBus(c+192,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("blocks[1]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("block_inst", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+362,0,"data_width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+362,0,"n_channels",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+362,0,"n_registers",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBit(c+344,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+346,0,"tick",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+347,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("ch_in", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+21+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("ch_out", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+193+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+352,0,"instr_val",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+359,0,"instr_write",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+354,0,"reg_val",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+351,0,"reg_target",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+3,0,"reg_write",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+4,0,"reg_update",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+209,0,"mul_req_a",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+210,0,"mul_req_b",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+46,0,"mul_result",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+211,0,"mul_done",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+212,0,"done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+213,0,"instr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+214,0,"operation",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+215,0,"src_a",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+216,0,"src_b",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+217,0,"src_c",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+218,0,"dest",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+363,0,"operand_type_start_index",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+219,0,"src_a_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+220,0,"src_b_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+221,0,"src_c_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+222,0,"dest_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+364,0,"pms_start_index",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("ch_regs", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+223+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("regs", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+239+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("reg_updates", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+255+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("reg_updated", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBit(c+271+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("unified_regs", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+287+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+365,0,"UNIFIED_W",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+319,0,"src_a_unified_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+320,0,"src_b_unified_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+321,0,"src_c_unified_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+322,0,"dest_unified_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+323,0,"src_a_latched",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+372,0,"src_b_latched",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+373,0,"src_c_latched",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+324,0,"summand_a",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+325,0,"summand_b",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+326,0,"summand_a_ext",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 16,0);
    tracep->declBus(c+327,0,"summand_b_ext",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 16,0);
    tracep->declBus(c+328,0,"sum_ext",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 16,0);
    tracep->declBus(c+368,0,"MAX_SHIFT",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+369,0,"SHIFT_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+329,0,"post_mul_shift",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+370,0,"SAT_MAX_EXT",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+371,0,"SAT_MIN_EXT",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+330,0,"mul_result_shifted",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+331,0,"mul_result_final",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+332,0,"sum",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+333,0,"prod",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+334,0,"mul_wait_begin",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+335,0,"mul_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+336,0,"state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 8,0);
    tracep->declBus(c+337,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("mul", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+361,0,"width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+360,0,"n_blocks",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+344,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+347,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("x", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+338+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("y", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+340+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+46,0,"prod",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+47,0,"done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+374,0,"index_width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+375,0,"initial_index",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+342,0,"index",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+343,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vpipeline___024root__trace_init_top(Vpipeline___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root__trace_init_top\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vpipeline___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vpipeline___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp);
VL_ATTR_COLD void Vpipeline___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vpipeline___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vpipeline___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/);

VL_ATTR_COLD void Vpipeline___024root__trace_register(Vpipeline___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root__trace_register\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vpipeline___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vpipeline___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vpipeline___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vpipeline___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vpipeline___024root__trace_const_0_sub_0(Vpipeline___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vpipeline___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root__trace_const_0\n"); );
    // Init
    Vpipeline___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vpipeline___024root*>(voidSelf);
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vpipeline___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vpipeline___024root__trace_const_0_sub_0(Vpipeline___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root__trace_const_0_sub_0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+360,(2U),32);
    bufp->fullIData(oldp+361,(0x10U),32);
    bufp->fullIData(oldp+362,(0x10U),32);
    bufp->fullIData(oldp+363,(0x15U),32);
    bufp->fullIData(oldp+364,(0x19U),32);
    bufp->fullIData(oldp+365,(5U),32);
    bufp->fullSData(oldp+366,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_b_latched),16);
    bufp->fullSData(oldp+367,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_c_latched),16);
    bufp->fullIData(oldp+368,(0x1eU),32);
    bufp->fullIData(oldp+369,(5U),32);
    bufp->fullIData(oldp+370,(0x7fffU),32);
    bufp->fullIData(oldp+371,(0xffff8000U),32);
    bufp->fullSData(oldp+372,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_b_latched),16);
    bufp->fullSData(oldp+373,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_c_latched),16);
    bufp->fullIData(oldp+374,(1U),32);
    bufp->fullBit(oldp+375,(1U));
}

VL_ATTR_COLD void Vpipeline___024root__trace_full_0_sub_0(Vpipeline___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vpipeline___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root__trace_full_0\n"); );
    // Init
    Vpipeline___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vpipeline___024root*>(voidSelf);
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vpipeline___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vpipeline___024root__trace_full_0_sub_0(Vpipeline___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline___024root__trace_full_0_sub_0\n"); );
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_write));
    bufp->fullBit(oldp+2,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__reg_update));
    bufp->fullBit(oldp+3,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_write));
    bufp->fullBit(oldp+4,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__reg_update));
    bufp->fullSData(oldp+5,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[0]),16);
    bufp->fullSData(oldp+6,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[1]),16);
    bufp->fullSData(oldp+7,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[2]),16);
    bufp->fullSData(oldp+8,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[3]),16);
    bufp->fullSData(oldp+9,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[4]),16);
    bufp->fullSData(oldp+10,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[5]),16);
    bufp->fullSData(oldp+11,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[6]),16);
    bufp->fullSData(oldp+12,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[7]),16);
    bufp->fullSData(oldp+13,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[8]),16);
    bufp->fullSData(oldp+14,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[9]),16);
    bufp->fullSData(oldp+15,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[10]),16);
    bufp->fullSData(oldp+16,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[11]),16);
    bufp->fullSData(oldp+17,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[12]),16);
    bufp->fullSData(oldp+18,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[13]),16);
    bufp->fullSData(oldp+19,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[14]),16);
    bufp->fullSData(oldp+20,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__0__KET____DOT__block_inst__ch_in[15]),16);
    bufp->fullSData(oldp+21,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[0]),16);
    bufp->fullSData(oldp+22,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[1]),16);
    bufp->fullSData(oldp+23,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[2]),16);
    bufp->fullSData(oldp+24,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[3]),16);
    bufp->fullSData(oldp+25,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[4]),16);
    bufp->fullSData(oldp+26,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[5]),16);
    bufp->fullSData(oldp+27,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[6]),16);
    bufp->fullSData(oldp+28,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[7]),16);
    bufp->fullSData(oldp+29,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[8]),16);
    bufp->fullSData(oldp+30,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[9]),16);
    bufp->fullSData(oldp+31,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[10]),16);
    bufp->fullSData(oldp+32,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[11]),16);
    bufp->fullSData(oldp+33,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[12]),16);
    bufp->fullSData(oldp+34,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[13]),16);
    bufp->fullSData(oldp+35,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[14]),16);
    bufp->fullSData(oldp+36,(vlSelfRef.pipeline__DOT____Vcellinp__blocks__BRA__1__KET____DOT__block_inst__ch_in[15]),16);
    bufp->fullSData(oldp+37,(vlSelfRef.pipeline__DOT__sample_latched),16);
    bufp->fullSData(oldp+38,(vlSelfRef.pipeline__DOT__state),16);
    bufp->fullSData(oldp+39,(vlSelfRef.pipeline__DOT__ctr),16);
    bufp->fullBit(oldp+40,(vlSelfRef.pipeline__DOT__invalid));
    bufp->fullCData(oldp+41,((((IData)(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done) 
                               << 1U) | (IData)(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done))),2);
    bufp->fullSData(oldp+42,(vlSelfRef.pipeline__DOT__mul_bus_x[0]),16);
    bufp->fullSData(oldp+43,(vlSelfRef.pipeline__DOT__mul_bus_x[1]),16);
    bufp->fullSData(oldp+44,(vlSelfRef.pipeline__DOT__mul_bus_y[0]),16);
    bufp->fullSData(oldp+45,(vlSelfRef.pipeline__DOT__mul_bus_y[1]),16);
    bufp->fullIData(oldp+46,(vlSelfRef.pipeline__DOT__mul_result),32);
    bufp->fullCData(oldp+47,(vlSelfRef.pipeline__DOT__mul_done),2);
    bufp->fullSData(oldp+48,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[0]),16);
    bufp->fullSData(oldp+49,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[1]),16);
    bufp->fullSData(oldp+50,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[2]),16);
    bufp->fullSData(oldp+51,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[3]),16);
    bufp->fullSData(oldp+52,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[4]),16);
    bufp->fullSData(oldp+53,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[5]),16);
    bufp->fullSData(oldp+54,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[6]),16);
    bufp->fullSData(oldp+55,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[7]),16);
    bufp->fullSData(oldp+56,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[8]),16);
    bufp->fullSData(oldp+57,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[9]),16);
    bufp->fullSData(oldp+58,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[10]),16);
    bufp->fullSData(oldp+59,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[11]),16);
    bufp->fullSData(oldp+60,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[12]),16);
    bufp->fullSData(oldp+61,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[13]),16);
    bufp->fullSData(oldp+62,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[14]),16);
    bufp->fullSData(oldp+63,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__ch_out[15]),16);
    bufp->fullSData(oldp+64,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_a),16);
    bufp->fullSData(oldp+65,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__mul_req_b),16);
    bufp->fullBit(oldp+66,((1U & (IData)(vlSelfRef.pipeline__DOT__mul_done))));
    bufp->fullBit(oldp+67,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__0__KET____DOT__block_inst__done));
    bufp->fullIData(oldp+68,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr),32);
    bufp->fullCData(oldp+69,((0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)),5);
    bufp->fullCData(oldp+70,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                      >> 5U))),4);
    bufp->fullCData(oldp+71,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                      >> 9U))),4);
    bufp->fullCData(oldp+72,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                      >> 0xdU))),4);
    bufp->fullCData(oldp+73,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                      >> 0x11U))),4);
    bufp->fullBit(oldp+74,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                  >> 0x15U))));
    bufp->fullBit(oldp+75,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                  >> 0x16U))));
    bufp->fullBit(oldp+76,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                  >> 0x17U))));
    bufp->fullBit(oldp+77,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                  >> 0x18U))));
    bufp->fullSData(oldp+78,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[0]),16);
    bufp->fullSData(oldp+79,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[1]),16);
    bufp->fullSData(oldp+80,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[2]),16);
    bufp->fullSData(oldp+81,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[3]),16);
    bufp->fullSData(oldp+82,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[4]),16);
    bufp->fullSData(oldp+83,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[5]),16);
    bufp->fullSData(oldp+84,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[6]),16);
    bufp->fullSData(oldp+85,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[7]),16);
    bufp->fullSData(oldp+86,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[8]),16);
    bufp->fullSData(oldp+87,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[9]),16);
    bufp->fullSData(oldp+88,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[10]),16);
    bufp->fullSData(oldp+89,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[11]),16);
    bufp->fullSData(oldp+90,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[12]),16);
    bufp->fullSData(oldp+91,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[13]),16);
    bufp->fullSData(oldp+92,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[14]),16);
    bufp->fullSData(oldp+93,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__ch_regs[15]),16);
    bufp->fullSData(oldp+94,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[0]),16);
    bufp->fullSData(oldp+95,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[1]),16);
    bufp->fullSData(oldp+96,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[2]),16);
    bufp->fullSData(oldp+97,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[3]),16);
    bufp->fullSData(oldp+98,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[4]),16);
    bufp->fullSData(oldp+99,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[5]),16);
    bufp->fullSData(oldp+100,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[6]),16);
    bufp->fullSData(oldp+101,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[7]),16);
    bufp->fullSData(oldp+102,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[8]),16);
    bufp->fullSData(oldp+103,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[9]),16);
    bufp->fullSData(oldp+104,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[10]),16);
    bufp->fullSData(oldp+105,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[11]),16);
    bufp->fullSData(oldp+106,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[12]),16);
    bufp->fullSData(oldp+107,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[13]),16);
    bufp->fullSData(oldp+108,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[14]),16);
    bufp->fullSData(oldp+109,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__regs[15]),16);
    bufp->fullSData(oldp+110,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[0]),16);
    bufp->fullSData(oldp+111,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[1]),16);
    bufp->fullSData(oldp+112,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[2]),16);
    bufp->fullSData(oldp+113,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[3]),16);
    bufp->fullSData(oldp+114,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[4]),16);
    bufp->fullSData(oldp+115,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[5]),16);
    bufp->fullSData(oldp+116,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[6]),16);
    bufp->fullSData(oldp+117,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[7]),16);
    bufp->fullSData(oldp+118,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[8]),16);
    bufp->fullSData(oldp+119,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[9]),16);
    bufp->fullSData(oldp+120,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[10]),16);
    bufp->fullSData(oldp+121,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[11]),16);
    bufp->fullSData(oldp+122,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[12]),16);
    bufp->fullSData(oldp+123,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[13]),16);
    bufp->fullSData(oldp+124,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[14]),16);
    bufp->fullSData(oldp+125,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updates[15]),16);
    bufp->fullBit(oldp+126,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[0]));
    bufp->fullBit(oldp+127,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[1]));
    bufp->fullBit(oldp+128,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[2]));
    bufp->fullBit(oldp+129,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[3]));
    bufp->fullBit(oldp+130,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[4]));
    bufp->fullBit(oldp+131,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[5]));
    bufp->fullBit(oldp+132,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[6]));
    bufp->fullBit(oldp+133,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[7]));
    bufp->fullBit(oldp+134,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[8]));
    bufp->fullBit(oldp+135,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[9]));
    bufp->fullBit(oldp+136,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[10]));
    bufp->fullBit(oldp+137,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[11]));
    bufp->fullBit(oldp+138,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[12]));
    bufp->fullBit(oldp+139,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[13]));
    bufp->fullBit(oldp+140,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[14]));
    bufp->fullBit(oldp+141,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__reg_updated[15]));
    bufp->fullSData(oldp+142,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[0]),16);
    bufp->fullSData(oldp+143,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[1]),16);
    bufp->fullSData(oldp+144,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[2]),16);
    bufp->fullSData(oldp+145,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[3]),16);
    bufp->fullSData(oldp+146,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[4]),16);
    bufp->fullSData(oldp+147,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[5]),16);
    bufp->fullSData(oldp+148,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[6]),16);
    bufp->fullSData(oldp+149,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[7]),16);
    bufp->fullSData(oldp+150,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[8]),16);
    bufp->fullSData(oldp+151,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[9]),16);
    bufp->fullSData(oldp+152,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[10]),16);
    bufp->fullSData(oldp+153,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[11]),16);
    bufp->fullSData(oldp+154,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[12]),16);
    bufp->fullSData(oldp+155,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[13]),16);
    bufp->fullSData(oldp+156,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[14]),16);
    bufp->fullSData(oldp+157,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[15]),16);
    bufp->fullSData(oldp+158,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[16]),16);
    bufp->fullSData(oldp+159,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[17]),16);
    bufp->fullSData(oldp+160,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[18]),16);
    bufp->fullSData(oldp+161,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[19]),16);
    bufp->fullSData(oldp+162,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[20]),16);
    bufp->fullSData(oldp+163,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[21]),16);
    bufp->fullSData(oldp+164,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[22]),16);
    bufp->fullSData(oldp+165,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[23]),16);
    bufp->fullSData(oldp+166,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[24]),16);
    bufp->fullSData(oldp+167,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[25]),16);
    bufp->fullSData(oldp+168,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[26]),16);
    bufp->fullSData(oldp+169,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[27]),16);
    bufp->fullSData(oldp+170,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[28]),16);
    bufp->fullSData(oldp+171,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[29]),16);
    bufp->fullSData(oldp+172,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[30]),16);
    bufp->fullSData(oldp+173,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__unified_regs[31]),16);
    bufp->fullCData(oldp+174,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_unified_addr),5);
    bufp->fullCData(oldp+175,((0x1fU & ((0x400000U 
                                         & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                                         ? ((IData)(0x10U) 
                                            + (0xfU 
                                               & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                  >> 9U)))
                                         : (0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                             >> 9U))))),5);
    bufp->fullCData(oldp+176,((0x1fU & ((0x800000U 
                                         & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                                         ? ((IData)(0x10U) 
                                            + (0xfU 
                                               & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                  >> 0xdU)))
                                         : (0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                             >> 0xdU))))),5);
    bufp->fullCData(oldp+177,((0x1fU & ((0x1000000U 
                                         & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr)
                                         ? ((IData)(0x10U) 
                                            + (0xfU 
                                               & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                  >> 0x11U)))
                                         : (0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                             >> 0x11U))))),5);
    bufp->fullSData(oldp+178,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__src_a_latched),16);
    bufp->fullSData(oldp+179,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a),16);
    bufp->fullSData(oldp+180,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b),16);
    bufp->fullIData(oldp+181,(((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a) 
                                            << 1U)) 
                               | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_a))),17);
    bufp->fullIData(oldp+182,(((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b) 
                                            << 1U)) 
                               | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__summand_b))),17);
    bufp->fullIData(oldp+183,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum_ext),17);
    bufp->fullCData(oldp+184,(((5U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr))
                                ? 1U : (0x1fU & (vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__instr 
                                                 >> 0x19U)))),5);
    bufp->fullIData(oldp+185,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_shifted),32);
    bufp->fullSData(oldp+186,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_result_final),16);
    bufp->fullSData(oldp+187,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__sum),16);
    bufp->fullSData(oldp+188,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__prod),16);
    bufp->fullBit(oldp+189,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_wait_begin));
    bufp->fullBit(oldp+190,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__mul_ready));
    bufp->fullSData(oldp+191,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__state),9);
    bufp->fullIData(oldp+192,(vlSelfRef.pipeline__DOT__blocks__BRA__0__KET____DOT__block_inst__DOT__i),32);
    bufp->fullSData(oldp+193,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[0]),16);
    bufp->fullSData(oldp+194,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[1]),16);
    bufp->fullSData(oldp+195,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[2]),16);
    bufp->fullSData(oldp+196,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[3]),16);
    bufp->fullSData(oldp+197,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[4]),16);
    bufp->fullSData(oldp+198,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[5]),16);
    bufp->fullSData(oldp+199,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[6]),16);
    bufp->fullSData(oldp+200,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[7]),16);
    bufp->fullSData(oldp+201,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[8]),16);
    bufp->fullSData(oldp+202,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[9]),16);
    bufp->fullSData(oldp+203,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[10]),16);
    bufp->fullSData(oldp+204,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[11]),16);
    bufp->fullSData(oldp+205,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[12]),16);
    bufp->fullSData(oldp+206,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[13]),16);
    bufp->fullSData(oldp+207,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[14]),16);
    bufp->fullSData(oldp+208,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__ch_out[15]),16);
    bufp->fullSData(oldp+209,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_a),16);
    bufp->fullSData(oldp+210,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__mul_req_b),16);
    bufp->fullBit(oldp+211,((1U & ((IData)(vlSelfRef.pipeline__DOT__mul_done) 
                                   >> 1U))));
    bufp->fullBit(oldp+212,(vlSelfRef.pipeline__DOT____Vcellout__blocks__BRA__1__KET____DOT__block_inst__done));
    bufp->fullIData(oldp+213,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr),32);
    bufp->fullCData(oldp+214,((0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)),5);
    bufp->fullCData(oldp+215,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                       >> 5U))),4);
    bufp->fullCData(oldp+216,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                       >> 9U))),4);
    bufp->fullCData(oldp+217,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                       >> 0xdU))),4);
    bufp->fullCData(oldp+218,((0xfU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                       >> 0x11U))),4);
    bufp->fullBit(oldp+219,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                   >> 0x15U))));
    bufp->fullBit(oldp+220,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                   >> 0x16U))));
    bufp->fullBit(oldp+221,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                   >> 0x17U))));
    bufp->fullBit(oldp+222,((1U & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                   >> 0x18U))));
    bufp->fullSData(oldp+223,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[0]),16);
    bufp->fullSData(oldp+224,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[1]),16);
    bufp->fullSData(oldp+225,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[2]),16);
    bufp->fullSData(oldp+226,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[3]),16);
    bufp->fullSData(oldp+227,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[4]),16);
    bufp->fullSData(oldp+228,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[5]),16);
    bufp->fullSData(oldp+229,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[6]),16);
    bufp->fullSData(oldp+230,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[7]),16);
    bufp->fullSData(oldp+231,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[8]),16);
    bufp->fullSData(oldp+232,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[9]),16);
    bufp->fullSData(oldp+233,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[10]),16);
    bufp->fullSData(oldp+234,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[11]),16);
    bufp->fullSData(oldp+235,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[12]),16);
    bufp->fullSData(oldp+236,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[13]),16);
    bufp->fullSData(oldp+237,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[14]),16);
    bufp->fullSData(oldp+238,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__ch_regs[15]),16);
    bufp->fullSData(oldp+239,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[0]),16);
    bufp->fullSData(oldp+240,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[1]),16);
    bufp->fullSData(oldp+241,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[2]),16);
    bufp->fullSData(oldp+242,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[3]),16);
    bufp->fullSData(oldp+243,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[4]),16);
    bufp->fullSData(oldp+244,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[5]),16);
    bufp->fullSData(oldp+245,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[6]),16);
    bufp->fullSData(oldp+246,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[7]),16);
    bufp->fullSData(oldp+247,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[8]),16);
    bufp->fullSData(oldp+248,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[9]),16);
    bufp->fullSData(oldp+249,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[10]),16);
    bufp->fullSData(oldp+250,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[11]),16);
    bufp->fullSData(oldp+251,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[12]),16);
    bufp->fullSData(oldp+252,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[13]),16);
    bufp->fullSData(oldp+253,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[14]),16);
    bufp->fullSData(oldp+254,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__regs[15]),16);
    bufp->fullSData(oldp+255,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[0]),16);
    bufp->fullSData(oldp+256,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[1]),16);
    bufp->fullSData(oldp+257,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[2]),16);
    bufp->fullSData(oldp+258,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[3]),16);
    bufp->fullSData(oldp+259,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[4]),16);
    bufp->fullSData(oldp+260,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[5]),16);
    bufp->fullSData(oldp+261,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[6]),16);
    bufp->fullSData(oldp+262,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[7]),16);
    bufp->fullSData(oldp+263,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[8]),16);
    bufp->fullSData(oldp+264,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[9]),16);
    bufp->fullSData(oldp+265,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[10]),16);
    bufp->fullSData(oldp+266,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[11]),16);
    bufp->fullSData(oldp+267,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[12]),16);
    bufp->fullSData(oldp+268,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[13]),16);
    bufp->fullSData(oldp+269,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[14]),16);
    bufp->fullSData(oldp+270,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updates[15]),16);
    bufp->fullBit(oldp+271,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[0]));
    bufp->fullBit(oldp+272,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[1]));
    bufp->fullBit(oldp+273,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[2]));
    bufp->fullBit(oldp+274,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[3]));
    bufp->fullBit(oldp+275,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[4]));
    bufp->fullBit(oldp+276,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[5]));
    bufp->fullBit(oldp+277,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[6]));
    bufp->fullBit(oldp+278,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[7]));
    bufp->fullBit(oldp+279,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[8]));
    bufp->fullBit(oldp+280,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[9]));
    bufp->fullBit(oldp+281,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[10]));
    bufp->fullBit(oldp+282,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[11]));
    bufp->fullBit(oldp+283,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[12]));
    bufp->fullBit(oldp+284,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[13]));
    bufp->fullBit(oldp+285,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[14]));
    bufp->fullBit(oldp+286,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__reg_updated[15]));
    bufp->fullSData(oldp+287,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[0]),16);
    bufp->fullSData(oldp+288,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[1]),16);
    bufp->fullSData(oldp+289,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[2]),16);
    bufp->fullSData(oldp+290,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[3]),16);
    bufp->fullSData(oldp+291,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[4]),16);
    bufp->fullSData(oldp+292,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[5]),16);
    bufp->fullSData(oldp+293,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[6]),16);
    bufp->fullSData(oldp+294,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[7]),16);
    bufp->fullSData(oldp+295,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[8]),16);
    bufp->fullSData(oldp+296,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[9]),16);
    bufp->fullSData(oldp+297,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[10]),16);
    bufp->fullSData(oldp+298,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[11]),16);
    bufp->fullSData(oldp+299,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[12]),16);
    bufp->fullSData(oldp+300,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[13]),16);
    bufp->fullSData(oldp+301,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[14]),16);
    bufp->fullSData(oldp+302,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[15]),16);
    bufp->fullSData(oldp+303,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[16]),16);
    bufp->fullSData(oldp+304,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[17]),16);
    bufp->fullSData(oldp+305,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[18]),16);
    bufp->fullSData(oldp+306,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[19]),16);
    bufp->fullSData(oldp+307,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[20]),16);
    bufp->fullSData(oldp+308,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[21]),16);
    bufp->fullSData(oldp+309,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[22]),16);
    bufp->fullSData(oldp+310,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[23]),16);
    bufp->fullSData(oldp+311,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[24]),16);
    bufp->fullSData(oldp+312,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[25]),16);
    bufp->fullSData(oldp+313,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[26]),16);
    bufp->fullSData(oldp+314,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[27]),16);
    bufp->fullSData(oldp+315,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[28]),16);
    bufp->fullSData(oldp+316,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[29]),16);
    bufp->fullSData(oldp+317,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[30]),16);
    bufp->fullSData(oldp+318,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__unified_regs[31]),16);
    bufp->fullCData(oldp+319,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_unified_addr),5);
    bufp->fullCData(oldp+320,((0x1fU & ((0x400000U 
                                         & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                                         ? ((IData)(0x10U) 
                                            + (0xfU 
                                               & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                  >> 9U)))
                                         : (0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                             >> 9U))))),5);
    bufp->fullCData(oldp+321,((0x1fU & ((0x800000U 
                                         & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                                         ? ((IData)(0x10U) 
                                            + (0xfU 
                                               & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                  >> 0xdU)))
                                         : (0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                             >> 0xdU))))),5);
    bufp->fullCData(oldp+322,((0x1fU & ((0x1000000U 
                                         & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr)
                                         ? ((IData)(0x10U) 
                                            + (0xfU 
                                               & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                  >> 0x11U)))
                                         : (0xfU & 
                                            (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                             >> 0x11U))))),5);
    bufp->fullSData(oldp+323,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__src_a_latched),16);
    bufp->fullSData(oldp+324,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a),16);
    bufp->fullSData(oldp+325,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b),16);
    bufp->fullIData(oldp+326,(((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a) 
                                            << 1U)) 
                               | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_a))),17);
    bufp->fullIData(oldp+327,(((0x10000U & ((IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b) 
                                            << 1U)) 
                               | (IData)(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__summand_b))),17);
    bufp->fullIData(oldp+328,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum_ext),17);
    bufp->fullCData(oldp+329,(((5U == (0x1fU & vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr))
                                ? 1U : (0x1fU & (vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__instr 
                                                 >> 0x19U)))),5);
    bufp->fullIData(oldp+330,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_shifted),32);
    bufp->fullSData(oldp+331,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_result_final),16);
    bufp->fullSData(oldp+332,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__sum),16);
    bufp->fullSData(oldp+333,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__prod),16);
    bufp->fullBit(oldp+334,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_wait_begin));
    bufp->fullBit(oldp+335,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__mul_ready));
    bufp->fullSData(oldp+336,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__state),9);
    bufp->fullIData(oldp+337,(vlSelfRef.pipeline__DOT__blocks__BRA__1__KET____DOT__block_inst__DOT__i),32);
    bufp->fullSData(oldp+338,(vlSelfRef.pipeline__DOT____Vcellinp__mul__x[0]),16);
    bufp->fullSData(oldp+339,(vlSelfRef.pipeline__DOT____Vcellinp__mul__x[1]),16);
    bufp->fullSData(oldp+340,(vlSelfRef.pipeline__DOT____Vcellinp__mul__y[0]),16);
    bufp->fullSData(oldp+341,(vlSelfRef.pipeline__DOT____Vcellinp__mul__y[1]),16);
    bufp->fullBit(oldp+342,(vlSelfRef.pipeline__DOT__mul__DOT__index));
    bufp->fullIData(oldp+343,(vlSelfRef.pipeline__DOT__mul__DOT__i),32);
    bufp->fullBit(oldp+344,(vlSelfRef.clk));
    bufp->fullSData(oldp+345,(vlSelfRef.in_sample),16);
    bufp->fullBit(oldp+346,(vlSelfRef.in_valid));
    bufp->fullBit(oldp+347,(vlSelfRef.reset));
    bufp->fullSData(oldp+348,(vlSelfRef.out_sample),16);
    bufp->fullBit(oldp+349,(vlSelfRef.ready));
    bufp->fullBit(oldp+350,(vlSelfRef.block_target));
    bufp->fullCData(oldp+351,(vlSelfRef.reg_target),4);
    bufp->fullIData(oldp+352,(vlSelfRef.instr_val),32);
    bufp->fullBit(oldp+353,(vlSelfRef.instr_write));
    bufp->fullSData(oldp+354,(vlSelfRef.reg_val),16);
    bufp->fullBit(oldp+355,(vlSelfRef.reg_update));
    bufp->fullBit(oldp+356,(vlSelfRef.reg_write));
    bufp->fullBit(oldp+357,(vlSelfRef.error));
    bufp->fullBit(oldp+358,(((IData)(vlSelfRef.instr_write) 
                             & (~ (IData)(vlSelfRef.block_target)))));
    bufp->fullBit(oldp+359,(((IData)(vlSelfRef.instr_write) 
                             & (IData)(vlSelfRef.block_target))));
}
