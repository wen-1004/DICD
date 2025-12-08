// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdelay_n.h for the primary calling header

#include "Vdelay_n__pch.h"

void Vdelay_n___024root___ctor_var_reset(Vdelay_n___024root* vlSelf);

Vdelay_n___024root::Vdelay_n___024root(Vdelay_n__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vdelay_n___024root___ctor_var_reset(this);
}

void Vdelay_n___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vdelay_n___024root::~Vdelay_n___024root() {
    VL_DO_DANGLING(free(const_cast<char*>(vlNamep)), vlNamep);
}
