// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vangle.h for the primary calling header

#ifndef VERILATED_VANGLE___024ROOT_H_
#define VERILATED_VANGLE___024ROOT_H_  // guard

#include "verilated.h"


class Vangle__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vangle___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    VL_IN16(gm_in_real,13,0);
    VL_IN16(gm_in_imag,13,0);
    VL_OUT16(ang_out,10,0);
    SData/*13:0*/ angle__DOT__x0_c;
    SData/*13:0*/ angle__DOT__y0_c;
    SData/*10:0*/ angle__DOT__z0_c;
    SData/*13:0*/ angle__DOT__x0_r;
    SData/*13:0*/ angle__DOT__y0_r;
    SData/*10:0*/ angle__DOT__z0_r;
    SData/*10:0*/ angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Z_out;
    SData/*13:0*/ angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Y_out;
    SData/*13:0*/ angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__X_out;
    SData/*10:0*/ angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Z_out;
    SData/*13:0*/ angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Y_out;
    SData/*13:0*/ angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__X_out;
    SData/*10:0*/ angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Z_out;
    SData/*13:0*/ angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Y_out;
    SData/*13:0*/ angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__X_out;
    SData/*10:0*/ angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Z_out;
    SData/*13:0*/ angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Y_out;
    SData/*13:0*/ angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__X_out;
    SData/*10:0*/ angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Z_out;
    SData/*13:0*/ angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Y_out;
    SData/*10:0*/ angle__DOT____Vcellout__STAGE__BRA__5__KET____DOT__u_pipe__Z_out;
    SData/*13:0*/ __VdfgRegularize_h6e95ff9d_0_0;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vangle__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vangle___024root(Vangle__Syms* symsp, const char* namep);
    ~Vangle___024root();
    VL_UNCOPYABLE(Vangle___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
