// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vminus.h for the primary calling header

#ifndef VERILATED_VMINUS___024ROOT_H_
#define VERILATED_VMINUS___024ROOT_H_  // guard

#include "verilated.h"


class Vminus__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vminus___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(rho_in,7,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    VL_IN16(mag_in,13,0);
    VL_IN16(phi_in,13,0);
    VL_OUT16(lambda_out,13,0);
    SData/*13:0*/ minus__DOT____Vlvbound_heb803490__0;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<SData/*13:0*/, 5> minus__DOT__delay_line;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vminus__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vminus___024root(Vminus__Syms* symsp, const char* namep);
    ~Vminus___024root();
    VL_UNCOPYABLE(Vminus___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
