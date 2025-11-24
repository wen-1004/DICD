// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vminus.h for the primary calling header

#include "Vminus__pch.h"

void Vminus___024root___ctor_var_reset(Vminus___024root* vlSelf);

Vminus___024root::Vminus___024root(Vminus__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vminus___024root___ctor_var_reset(this);
}

void Vminus___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vminus___024root::~Vminus___024root() {
    VL_DO_DANGLING(free(const_cast<char*>(vlNamep)), vlNamep);
}
