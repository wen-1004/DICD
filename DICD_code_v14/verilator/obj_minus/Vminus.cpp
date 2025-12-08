// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vminus__pch.h"

//============================================================
// Constructors

Vminus::Vminus(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vminus__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , rho_in{vlSymsp->TOP.rho_in}
    , mag_in{vlSymsp->TOP.mag_in}
    , phi_in{vlSymsp->TOP.phi_in}
    , lambda_out{vlSymsp->TOP.lambda_out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vminus::Vminus(const char* _vcname__)
    : Vminus(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vminus::~Vminus() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vminus___024root___eval_debug_assertions(Vminus___024root* vlSelf);
#endif  // VL_DEBUG
void Vminus___024root___eval_static(Vminus___024root* vlSelf);
void Vminus___024root___eval_initial(Vminus___024root* vlSelf);
void Vminus___024root___eval_settle(Vminus___024root* vlSelf);
void Vminus___024root___eval(Vminus___024root* vlSelf);

void Vminus::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vminus::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vminus___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vminus___024root___eval_static(&(vlSymsp->TOP));
        Vminus___024root___eval_initial(&(vlSymsp->TOP));
        Vminus___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vminus___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vminus::eventsPending() { return false; }

uint64_t Vminus::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vminus::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vminus___024root___eval_final(Vminus___024root* vlSelf);

VL_ATTR_COLD void Vminus::final() {
    Vminus___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vminus::hierName() const { return vlSymsp->name(); }
const char* Vminus::modelName() const { return "Vminus"; }
unsigned Vminus::threads() const { return 1; }
void Vminus::prepareClone() const { contextp()->prepareClone(); }
void Vminus::atClone() const {
    contextp()->threadPoolpOnClone();
}
