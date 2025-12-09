// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vmag.h for the primary calling header

#ifndef VERILATED_VMAG___024ROOT_H_
#define VERILATED_VMAG___024ROOT_H_  // guard

#include "verilated.h"


class Vmag__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vmag___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    CData/*0:0*/ mag__DOT__max_zero1;
    CData/*3:0*/ mag__DOT__seg_idx_c;
    CData/*3:0*/ mag__DOT__seg_idx_s2;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    VL_IN16(gm_in_real,13,0);
    VL_IN16(gm_in_imag,13,0);
    VL_OUT16(mag_out,13,0);
    SData/*13:0*/ mag__DOT__max0;
    SData/*13:0*/ mag__DOT__min0;
    SData/*13:0*/ mag__DOT__max_s1;
    SData/*13:0*/ mag__DOT__min_s1;
    SData/*13:0*/ mag__DOT__max_u1;
    SData/*13:0*/ mag__DOT__max_s2;
    SData/*13:0*/ mag__DOT__min_s2;
    SData/*9:0*/ mag__DOT__alpha_s3_c;
    SData/*9:0*/ mag__DOT__beta_s3_c;
    SData/*14:0*/ mag__DOT__term_a_s3;
    SData/*14:0*/ mag__DOT__term_b_s3;
    IData/*21:0*/ mag__DOT__left1;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vmag__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vmag___024root(Vmag__Syms* symsp, const char* namep);
    ~Vmag___024root();
    VL_UNCOPYABLE(Vmag___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
