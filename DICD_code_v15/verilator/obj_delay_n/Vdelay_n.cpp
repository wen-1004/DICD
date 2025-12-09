// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vdelay_n__pch.h"

//============================================================
// Constructors

Vdelay_n::Vdelay_n(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vdelay_n__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , r_d1_real{vlSymsp->TOP.r_d1_real}
    , r_d1_imag{vlSymsp->TOP.r_d1_imag}
    , r_dN_out_real{vlSymsp->TOP.r_dN_out_real}
    , r_dN_out_imag{vlSymsp->TOP.r_dN_out_imag}
    , r_in_real{vlSymsp->TOP.r_in_real}
    , r_in_imag{vlSymsp->TOP.r_in_imag}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vdelay_n::Vdelay_n(const char* _vcname__)
    : Vdelay_n(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vdelay_n::~Vdelay_n() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vdelay_n___024root___eval_debug_assertions(Vdelay_n___024root* vlSelf);
#endif  // VL_DEBUG
void Vdelay_n___024root___eval_static(Vdelay_n___024root* vlSelf);
void Vdelay_n___024root___eval_initial(Vdelay_n___024root* vlSelf);
void Vdelay_n___024root___eval_settle(Vdelay_n___024root* vlSelf);
void Vdelay_n___024root___eval(Vdelay_n___024root* vlSelf);

void Vdelay_n::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vdelay_n::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vdelay_n___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vdelay_n___024root___eval_static(&(vlSymsp->TOP));
        Vdelay_n___024root___eval_initial(&(vlSymsp->TOP));
        Vdelay_n___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vdelay_n___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vdelay_n::eventsPending() { return false; }

uint64_t Vdelay_n::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vdelay_n::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vdelay_n___024root___eval_final(Vdelay_n___024root* vlSelf);

VL_ATTR_COLD void Vdelay_n::final() {
    Vdelay_n___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vdelay_n::hierName() const { return vlSymsp->name(); }
const char* Vdelay_n::modelName() const { return "Vdelay_n"; }
unsigned Vdelay_n::threads() const { return 1; }
void Vdelay_n::prepareClone() const { contextp()->prepareClone(); }
void Vdelay_n::atClone() const {
    contextp()->threadPoolpOnClone();
}
