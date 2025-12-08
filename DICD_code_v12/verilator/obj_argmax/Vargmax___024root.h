// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vargmax.h for the primary calling header

#ifndef VERILATED_VARGMAX___024ROOT_H_
#define VERILATED_VARGMAX___024ROOT_H_  // guard

#include "verilated.h"


class Vargmax__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vargmax___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_OUT8(theta_out,7,0);
    CData/*7:0*/ argmax__DOT__theta_out_r;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    VL_IN16(lambda_in,13,0);
    VL_IN16(angle_in,10,0);
    SData/*13:0*/ argmax__DOT__current_max;
    SData/*13:0*/ argmax__DOT__current_max_next;
    SData/*9:0*/ argmax__DOT__current_max_idx_s;
    SData/*10:0*/ argmax__DOT__current_ang;
    SData/*10:0*/ argmax__DOT__current_ang_next;
    SData/*9:0*/ argmax__DOT__count;
    SData/*9:0*/ argmax__DOT__count_next;
    SData/*9:0*/ argmax__DOT__theta_idx_for_out;
    VL_OUT(eps_out,20,0);
    IData/*20:0*/ argmax__DOT__eps_out_r;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vargmax__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vargmax___024root(Vargmax__Syms* symsp, const char* namep);
    ~Vargmax___024root();
    VL_UNCOPYABLE(Vargmax___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
