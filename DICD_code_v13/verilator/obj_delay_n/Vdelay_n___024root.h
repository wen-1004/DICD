// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vdelay_n.h for the primary calling header

#ifndef VERILATED_VDELAY_N___024ROOT_H_
#define VERILATED_VDELAY_N___024ROOT_H_  // guard

#include "verilated.h"


class Vdelay_n__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vdelay_n___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(r_in_real,6,0);
    VL_IN8(r_in_imag,6,0);
    VL_OUT8(r_d1_real,6,0);
    VL_OUT8(r_d1_imag,6,0);
    VL_OUT8(r_dN_out_real,6,0);
    VL_OUT8(r_dN_out_imag,6,0);
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    IData/*31:0*/ delay_n__DOT__i;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*6:0*/, 256> delay_n__DOT__delay_line_real;
    VlUnpacked<CData/*6:0*/, 256> delay_n__DOT__delay_line_imag;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlNBACommitQueue<VlUnpacked<CData/*6:0*/, 256>, false, CData/*6:0*/, 1> __VdlyCommitQueuedelay_n__DOT__delay_line_real;
    VlNBACommitQueue<VlUnpacked<CData/*6:0*/, 256>, false, CData/*6:0*/, 1> __VdlyCommitQueuedelay_n__DOT__delay_line_imag;

    // INTERNAL VARIABLES
    Vdelay_n__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vdelay_n___024root(Vdelay_n__Syms* symsp, const char* namep);
    ~Vdelay_n___024root();
    VL_UNCOPYABLE(Vdelay_n___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
