// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vgamma_sum.h for the primary calling header

#ifndef VERILATED_VGAMMA_SUM___024ROOT_H_
#define VERILATED_VGAMMA_SUM___024ROOT_H_  // guard

#include "verilated.h"


class Vgamma_sum__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vgamma_sum___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(r_k_in_real,6,0);
    VL_IN8(r_k_in_imag,6,0);
    VL_IN8(r_k_minus_N_in_real,6,0);
    VL_IN8(r_k_minus_N_in_imag,6,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    VL_OUT16(gamma_out_real,13,0);
    VL_OUT16(gamma_out_imag,13,0);
    SData/*13:0*/ gamma_sum__DOT__current_sum_real;
    SData/*13:0*/ gamma_sum__DOT__current_sum_imag;
    SData/*13:0*/ gamma_sum__DOT__ac_mul12_s1;
    SData/*13:0*/ gamma_sum__DOT__bd_mul12_s1;
    SData/*13:0*/ gamma_sum__DOT__bc_mul12_s1;
    SData/*13:0*/ gamma_sum__DOT__ad_mul12_s1;
    SData/*13:0*/ gamma_sum__DOT__product_real_s2;
    SData/*13:0*/ gamma_sum__DOT__product_imag_s2;
    SData/*13:0*/ gamma_sum__DOT__new_sum_real_w;
    SData/*13:0*/ gamma_sum__DOT__new_sum_imag_w;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<SData/*13:0*/, 16> gamma_sum__DOT__delay_line_real;
    VlUnpacked<SData/*13:0*/, 16> gamma_sum__DOT__delay_line_imag;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vgamma_sum__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vgamma_sum___024root(Vgamma_sum__Syms* symsp, const char* namep);
    ~Vgamma_sum___024root();
    VL_UNCOPYABLE(Vgamma_sum___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
