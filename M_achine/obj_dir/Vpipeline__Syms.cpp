// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vpipeline__pch.h"
#include "Vpipeline.h"
#include "Vpipeline___024root.h"

// FUNCTIONS
Vpipeline__Syms::~Vpipeline__Syms()
{
}

Vpipeline__Syms::Vpipeline__Syms(VerilatedContext* contextp, const char* namep, Vpipeline* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(1039);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
}
