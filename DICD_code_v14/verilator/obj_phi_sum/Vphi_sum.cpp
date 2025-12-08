// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vphi_sum__pch.h"

//============================================================
// Constructors

Vphi_sum::Vphi_sum(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vphi_sum__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , r_k_in_real{vlSymsp->TOP.r_k_in_real}
    , r_k_in_imag{vlSymsp->TOP.r_k_in_imag}
    , r_k_minus_N_in_real{vlSymsp->TOP.r_k_minus_N_in_real}
    , r_k_minus_N_in_imag{vlSymsp->TOP.r_k_minus_N_in_imag}
    , rho_in{vlSymsp->TOP.rho_in}
    , phi_out{vlSymsp->TOP.phi_out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vphi_sum::Vphi_sum(const char* _vcname__)
    : Vphi_sum(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vphi_sum::~Vphi_sum() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vphi_sum___024root___eval_debug_assertions(Vphi_sum___024root* vlSelf);
#endif  // VL_DEBUG
void Vphi_sum___024root___eval_static(Vphi_sum___024root* vlSelf);
void Vphi_sum___024root___eval_initial(Vphi_sum___024root* vlSelf);
void Vphi_sum___024root___eval_settle(Vphi_sum___024root* vlSelf);
void Vphi_sum___024root___eval(Vphi_sum___024root* vlSelf);

void Vphi_sum::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vphi_sum::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vphi_sum___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vphi_sum___024root___eval_static(&(vlSymsp->TOP));
        Vphi_sum___024root___eval_initial(&(vlSymsp->TOP));
        Vphi_sum___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vphi_sum___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vphi_sum::eventsPending() { return false; }

uint64_t Vphi_sum::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vphi_sum::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vphi_sum___024root___eval_final(Vphi_sum___024root* vlSelf);

VL_ATTR_COLD void Vphi_sum::final() {
    Vphi_sum___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vphi_sum::hierName() const { return vlSymsp->name(); }
const char* Vphi_sum::modelName() const { return "Vphi_sum"; }
unsigned Vphi_sum::threads() const { return 1; }
void Vphi_sum::prepareClone() const { contextp()->prepareClone(); }
void Vphi_sum::atClone() const {
    contextp()->threadPoolpOnClone();
}
