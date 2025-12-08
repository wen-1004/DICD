// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vangle__pch.h"

//============================================================
// Constructors

Vangle::Vangle(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vangle__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , gm_in_real{vlSymsp->TOP.gm_in_real}
    , gm_in_imag{vlSymsp->TOP.gm_in_imag}
    , ang_out{vlSymsp->TOP.ang_out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vangle::Vangle(const char* _vcname__)
    : Vangle(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vangle::~Vangle() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vangle___024root___eval_debug_assertions(Vangle___024root* vlSelf);
#endif  // VL_DEBUG
void Vangle___024root___eval_static(Vangle___024root* vlSelf);
void Vangle___024root___eval_initial(Vangle___024root* vlSelf);
void Vangle___024root___eval_settle(Vangle___024root* vlSelf);
void Vangle___024root___eval(Vangle___024root* vlSelf);

void Vangle::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vangle::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vangle___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vangle___024root___eval_static(&(vlSymsp->TOP));
        Vangle___024root___eval_initial(&(vlSymsp->TOP));
        Vangle___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vangle___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vangle::eventsPending() { return false; }

uint64_t Vangle::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vangle::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vangle___024root___eval_final(Vangle___024root* vlSelf);

VL_ATTR_COLD void Vangle::final() {
    Vangle___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vangle::hierName() const { return vlSymsp->name(); }
const char* Vangle::modelName() const { return "Vangle"; }
unsigned Vangle::threads() const { return 1; }
void Vangle::prepareClone() const { contextp()->prepareClone(); }
void Vangle::atClone() const {
    contextp()->threadPoolpOnClone();
}
