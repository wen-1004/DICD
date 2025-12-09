// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vargmax.h for the primary calling header

#include "Vargmax__pch.h"

void Vargmax___024root___ctor_var_reset(Vargmax___024root* vlSelf);

Vargmax___024root::Vargmax___024root(Vargmax__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vargmax___024root___ctor_var_reset(this);
}

void Vargmax___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vargmax___024root::~Vargmax___024root() {
    VL_DO_DANGLING(free(const_cast<char*>(vlNamep)), vlNamep);
}
