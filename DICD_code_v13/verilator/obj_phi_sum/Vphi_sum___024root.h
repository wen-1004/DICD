// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vphi_sum.h for the primary calling header

#ifndef VERILATED_VPHI_SUM___024ROOT_H_
#define VERILATED_VPHI_SUM___024ROOT_H_  // guard

#include "verilated.h"


class Vphi_sum__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vphi_sum___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(r_k_in_real,6,0);
    VL_IN8(r_k_in_imag,6,0);
    VL_IN8(r_k_minus_N_in_real,6,0);
    VL_IN8(r_k_minus_N_in_imag,6,0);
    VL_IN8(rho_in,7,0);
    CData/*7:0*/ phi_sum__DOT__rho_s1;
    CData/*7:0*/ phi_sum__DOT__rho_half_s2;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    VL_OUT16(phi_out,13,0);
    SData/*13:0*/ phi_sum__DOT__current_sum;
    SData/*13:0*/ phi_sum__DOT__a_re_sq12_s1;
    SData/*13:0*/ phi_sum__DOT__a_im_sq12_s1;
    SData/*13:0*/ phi_sum__DOT__b_re_sq12_s1;
    SData/*13:0*/ phi_sum__DOT__b_im_sq12_s1;
    SData/*13:0*/ phi_sum__DOT__r_k_sq_s2;
    SData/*13:0*/ phi_sum__DOT__r_kmN_sq_s2;
    SData/*13:0*/ phi_sum__DOT__energy_to_sum_s3;
    SData/*13:0*/ phi_sum__DOT__new_sum_w;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<SData/*13:0*/, 16> phi_sum__DOT__delay_line;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vphi_sum__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vphi_sum___024root(Vphi_sum__Syms* symsp, const char* namep);
    ~Vphi_sum___024root();
    VL_UNCOPYABLE(Vphi_sum___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
