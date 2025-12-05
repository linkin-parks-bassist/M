// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vpipeline__pch.h"
#include "verilated_fst_c.h"

//============================================================
// Constructors

Vpipeline::Vpipeline(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vpipeline__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , in_valid{vlSymsp->TOP.in_valid}
    , reset{vlSymsp->TOP.reset}
    , ready{vlSymsp->TOP.ready}
    , block_target{vlSymsp->TOP.block_target}
    , reg_target{vlSymsp->TOP.reg_target}
    , instr_write{vlSymsp->TOP.instr_write}
    , reg_update{vlSymsp->TOP.reg_update}
    , reg_write{vlSymsp->TOP.reg_write}
    , error{vlSymsp->TOP.error}
    , in_sample{vlSymsp->TOP.in_sample}
    , out_sample{vlSymsp->TOP.out_sample}
    , reg_val{vlSymsp->TOP.reg_val}
    , instr_val{vlSymsp->TOP.instr_val}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vpipeline::Vpipeline(const char* _vcname__)
    : Vpipeline(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vpipeline::~Vpipeline() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vpipeline___024root___eval_debug_assertions(Vpipeline___024root* vlSelf);
#endif  // VL_DEBUG
void Vpipeline___024root___eval_static(Vpipeline___024root* vlSelf);
void Vpipeline___024root___eval_initial(Vpipeline___024root* vlSelf);
void Vpipeline___024root___eval_settle(Vpipeline___024root* vlSelf);
void Vpipeline___024root___eval(Vpipeline___024root* vlSelf);

void Vpipeline::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vpipeline::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vpipeline___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vpipeline___024root___eval_static(&(vlSymsp->TOP));
        Vpipeline___024root___eval_initial(&(vlSymsp->TOP));
        Vpipeline___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vpipeline___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vpipeline::eventsPending() { return false; }

uint64_t Vpipeline::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vpipeline::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vpipeline___024root___eval_final(Vpipeline___024root* vlSelf);

VL_ATTR_COLD void Vpipeline::final() {
    Vpipeline___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vpipeline::hierName() const { return vlSymsp->name(); }
const char* Vpipeline::modelName() const { return "Vpipeline"; }
unsigned Vpipeline::threads() const { return 1; }
void Vpipeline::prepareClone() const { contextp()->prepareClone(); }
void Vpipeline::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vpipeline::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vpipeline___024root__trace_decl_types(VerilatedFst* tracep);

void Vpipeline___024root__trace_init_top(Vpipeline___024root* vlSelf, VerilatedFst* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedFst* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vpipeline___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vpipeline___024root*>(voidSelf);
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vpipeline___024root__trace_decl_types(tracep);
    Vpipeline___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vpipeline___024root__trace_register(Vpipeline___024root* vlSelf, VerilatedFst* tracep);

VL_ATTR_COLD void Vpipeline::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedFstC* const stfp = dynamic_cast<VerilatedFstC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vpipeline::trace()' called on non-VerilatedFstC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vpipeline___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
