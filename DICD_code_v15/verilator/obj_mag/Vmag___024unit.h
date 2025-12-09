// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vmag.h for the primary calling header

#ifndef VERILATED_VMAG___024UNIT_H_
#define VERILATED_VMAG___024UNIT_H_  // guard

#include "verilated.h"


class Vmag__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vmag___024unit final {
  public:

    // INTERNAL VARIABLES
    Vmag__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vmag___024unit() = default;
    ~Vmag___024unit() = default;
    void ctor(Vmag__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vmag___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
