// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vminus.h for the primary calling header

#include "Vminus__pch.h"

void Vminus___024unit___ctor_var_reset(Vminus___024unit* vlSelf);

void Vminus___024unit::ctor(Vminus__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vminus___024unit___ctor_var_reset(this);
}

void Vminus___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vminus___024unit::dtor() {
    VL_DO_DANGLING(free(const_cast<char*>(vlNamep)), vlNamep);
}
