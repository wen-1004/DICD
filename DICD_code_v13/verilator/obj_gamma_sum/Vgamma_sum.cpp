// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vgamma_sum__pch.h"

//============================================================
// Constructors

Vgamma_sum::Vgamma_sum(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vgamma_sum__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , r_k_in_real{vlSymsp->TOP.r_k_in_real}
    , r_k_in_imag{vlSymsp->TOP.r_k_in_imag}
    , r_k_minus_N_in_real{vlSymsp->TOP.r_k_minus_N_in_real}
    , r_k_minus_N_in_imag{vlSymsp->TOP.r_k_minus_N_in_imag}
    , gamma_out_real{vlSymsp->TOP.gamma_out_real}
    , gamma_out_imag{vlSymsp->TOP.gamma_out_imag}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vgamma_sum::Vgamma_sum(const char* _vcname__)
    : Vgamma_sum(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vgamma_sum::~Vgamma_sum() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vgamma_sum___024root___eval_debug_assertions(Vgamma_sum___024root* vlSelf);
#endif  // VL_DEBUG
void Vgamma_sum___024root___eval_static(Vgamma_sum___024root* vlSelf);
void Vgamma_sum___024root___eval_initial(Vgamma_sum___024root* vlSelf);
void Vgamma_sum___024root___eval_settle(Vgamma_sum___024root* vlSelf);
void Vgamma_sum___024root___eval(Vgamma_sum___024root* vlSelf);

void Vgamma_sum::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vgamma_sum::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vgamma_sum___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vgamma_sum___024root___eval_static(&(vlSymsp->TOP));
        Vgamma_sum___024root___eval_initial(&(vlSymsp->TOP));
        Vgamma_sum___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vgamma_sum___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vgamma_sum::eventsPending() { return false; }

uint64_t Vgamma_sum::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vgamma_sum::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vgamma_sum___024root___eval_final(Vgamma_sum___024root* vlSelf);

VL_ATTR_COLD void Vgamma_sum::final() {
    Vgamma_sum___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vgamma_sum::hierName() const { return vlSymsp->name(); }
const char* Vgamma_sum::modelName() const { return "Vgamma_sum"; }
unsigned Vgamma_sum::threads() const { return 1; }
void Vgamma_sum::prepareClone() const { contextp()->prepareClone(); }
void Vgamma_sum::atClone() const {
    contextp()->threadPoolpOnClone();
}
