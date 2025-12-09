// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmag.h for the primary calling header

#include "Vmag__pch.h"

void Vmag___024unit___ctor_var_reset(Vmag___024unit* vlSelf);

void Vmag___024unit::ctor(Vmag__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vmag___024unit___ctor_var_reset(this);
}

void Vmag___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vmag___024unit::dtor() {
    VL_DO_DANGLING(free(const_cast<char*>(vlNamep)), vlNamep);
}
