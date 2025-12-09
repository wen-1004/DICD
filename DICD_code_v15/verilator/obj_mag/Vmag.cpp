// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vmag__pch.h"

//============================================================
// Constructors

Vmag::Vmag(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vmag__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , gm_in_real{vlSymsp->TOP.gm_in_real}
    , gm_in_imag{vlSymsp->TOP.gm_in_imag}
    , mag_out{vlSymsp->TOP.mag_out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vmag::Vmag(const char* _vcname__)
    : Vmag(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vmag::~Vmag() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vmag___024root___eval_debug_assertions(Vmag___024root* vlSelf);
#endif  // VL_DEBUG
void Vmag___024root___eval_static(Vmag___024root* vlSelf);
void Vmag___024root___eval_initial(Vmag___024root* vlSelf);
void Vmag___024root___eval_settle(Vmag___024root* vlSelf);
void Vmag___024root___eval(Vmag___024root* vlSelf);

void Vmag::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmag::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vmag___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vmag___024root___eval_static(&(vlSymsp->TOP));
        Vmag___024root___eval_initial(&(vlSymsp->TOP));
        Vmag___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vmag___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vmag::eventsPending() { return false; }

uint64_t Vmag::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vmag::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vmag___024root___eval_final(Vmag___024root* vlSelf);

VL_ATTR_COLD void Vmag::final() {
    Vmag___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vmag::hierName() const { return vlSymsp->name(); }
const char* Vmag::modelName() const { return "Vmag"; }
unsigned Vmag::threads() const { return 1; }
void Vmag::prepareClone() const { contextp()->prepareClone(); }
void Vmag::atClone() const {
    contextp()->threadPoolpOnClone();
}
