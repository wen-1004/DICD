// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vangle.h for the primary calling header

#include "Vangle__pch.h"

void Vangle___024root___ctor_var_reset(Vangle___024root* vlSelf);

Vangle___024root::Vangle___024root(Vangle__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vangle___024root___ctor_var_reset(this);
}

void Vangle___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vangle___024root::~Vangle___024root() {
    VL_DO_DANGLING(free(const_cast<char*>(vlNamep)), vlNamep);
}
