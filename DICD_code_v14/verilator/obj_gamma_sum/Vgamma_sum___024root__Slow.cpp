// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgamma_sum.h for the primary calling header

#include "Vgamma_sum__pch.h"

void Vgamma_sum___024root___ctor_var_reset(Vgamma_sum___024root* vlSelf);

Vgamma_sum___024root::Vgamma_sum___024root(Vgamma_sum__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vgamma_sum___024root___ctor_var_reset(this);
}

void Vgamma_sum___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vgamma_sum___024root::~Vgamma_sum___024root() {
    VL_DO_DANGLING(free(const_cast<char*>(vlNamep)), vlNamep);
}
