// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vargmax__pch.h"

//============================================================
// Constructors

Vargmax::Vargmax(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vargmax__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , theta_out{vlSymsp->TOP.theta_out}
    , lambda_in{vlSymsp->TOP.lambda_in}
    , angle_in{vlSymsp->TOP.angle_in}
    , eps_out{vlSymsp->TOP.eps_out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vargmax::Vargmax(const char* _vcname__)
    : Vargmax(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vargmax::~Vargmax() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vargmax___024root___eval_debug_assertions(Vargmax___024root* vlSelf);
#endif  // VL_DEBUG
void Vargmax___024root___eval_static(Vargmax___024root* vlSelf);
void Vargmax___024root___eval_initial(Vargmax___024root* vlSelf);
void Vargmax___024root___eval_settle(Vargmax___024root* vlSelf);
void Vargmax___024root___eval(Vargmax___024root* vlSelf);

void Vargmax::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vargmax::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vargmax___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vargmax___024root___eval_static(&(vlSymsp->TOP));
        Vargmax___024root___eval_initial(&(vlSymsp->TOP));
        Vargmax___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vargmax___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vargmax::eventsPending() { return false; }

uint64_t Vargmax::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vargmax::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vargmax___024root___eval_final(Vargmax___024root* vlSelf);

VL_ATTR_COLD void Vargmax::final() {
    Vargmax___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vargmax::hierName() const { return vlSymsp->name(); }
const char* Vargmax::modelName() const { return "Vargmax"; }
unsigned Vargmax::threads() const { return 1; }
void Vargmax::prepareClone() const { contextp()->prepareClone(); }
void Vargmax::atClone() const {
    contextp()->threadPoolpOnClone();
}
