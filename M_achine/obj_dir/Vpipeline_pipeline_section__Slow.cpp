// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline.h for the primary calling header

#include "Vpipeline__pch.h"
#include "Vpipeline__Syms.h"
#include "Vpipeline_pipeline_section.h"

void Vpipeline_pipeline_section___ctor_var_reset(Vpipeline_pipeline_section* vlSelf);

Vpipeline_pipeline_section::Vpipeline_pipeline_section(Vpipeline__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vpipeline_pipeline_section___ctor_var_reset(this);
}

void Vpipeline_pipeline_section::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vpipeline_pipeline_section::~Vpipeline_pipeline_section() {
}
