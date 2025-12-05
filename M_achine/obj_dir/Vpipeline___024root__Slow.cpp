// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline.h for the primary calling header

#include "Vpipeline__pch.h"
#include "Vpipeline__Syms.h"
#include "Vpipeline___024root.h"

void Vpipeline___024root___ctor_var_reset(Vpipeline___024root* vlSelf);

Vpipeline___024root::Vpipeline___024root(Vpipeline__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vpipeline___024root___ctor_var_reset(this);
}

void Vpipeline___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vpipeline___024root::~Vpipeline___024root() {
}
