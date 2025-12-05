// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline.h for the primary calling header

#include "Vpipeline__pch.h"
#include "Vpipeline__Syms.h"
#include "Vpipeline_pipeline_block__NB10.h"

void Vpipeline_pipeline_block__NB10___ctor_var_reset(Vpipeline_pipeline_block__NB10* vlSelf);

Vpipeline_pipeline_block__NB10::Vpipeline_pipeline_block__NB10(Vpipeline__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vpipeline_pipeline_block__NB10___ctor_var_reset(this);
}

void Vpipeline_pipeline_block__NB10::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vpipeline_pipeline_block__NB10::~Vpipeline_pipeline_block__NB10() {
}
