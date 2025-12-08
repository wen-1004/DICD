// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vphi_sum.h for the primary calling header

#include "Vphi_sum__pch.h"

void Vphi_sum___024root___ctor_var_reset(Vphi_sum___024root* vlSelf);

Vphi_sum___024root::Vphi_sum___024root(Vphi_sum__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vphi_sum___024root___ctor_var_reset(this);
}

void Vphi_sum___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vphi_sum___024root::~Vphi_sum___024root() {
    VL_DO_DANGLING(free(const_cast<char*>(vlNamep)), vlNamep);
}
