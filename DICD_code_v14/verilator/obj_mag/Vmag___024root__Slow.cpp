// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmag.h for the primary calling header

#include "Vmag__pch.h"

void Vmag___024root___ctor_var_reset(Vmag___024root* vlSelf);

Vmag___024root::Vmag___024root(Vmag__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vmag___024root___ctor_var_reset(this);
}

void Vmag___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vmag___024root::~Vmag___024root() {
    VL_DO_DANGLING(free(const_cast<char*>(vlNamep)), vlNamep);
}
