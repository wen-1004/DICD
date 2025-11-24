// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vminus.h for the primary calling header

#ifndef VERILATED_VMINUS___024UNIT_H_
#define VERILATED_VMINUS___024UNIT_H_  // guard

#include "verilated.h"


class Vminus__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vminus___024unit final {
  public:

    // INTERNAL VARIABLES
    Vminus__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vminus___024unit() = default;
    ~Vminus___024unit() = default;
    void ctor(Vminus__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vminus___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
