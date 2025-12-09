// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vangle.h for the primary calling header

#include "Vangle__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vangle___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vangle___024root___eval_triggers__ico(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_triggers__ico\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
    vlSelfRef.__VicoFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vangle___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
}

bool Vangle___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vangle___024root___ico_sequent__TOP__0(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___ico_sequent__TOP__0\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.angle__DOT__x0_c = vlSelfRef.gm_in_real;
    vlSelfRef.angle__DOT__y0_c = vlSelfRef.gm_in_imag;
    vlSelfRef.angle__DOT__z0_c = 0U;
    if (VL_GTS_III(32, 0U, VL_EXTENDS_II(32,14, (IData)(vlSelfRef.gm_in_real)))) {
        if (VL_LTES_III(32, 0U, VL_EXTENDS_II(32,14, (IData)(vlSelfRef.gm_in_imag)))) {
            vlSelfRef.angle__DOT__x0_c = (0x00003fffU 
                                          & (IData)(vlSelfRef.gm_in_imag));
            vlSelfRef.angle__DOT__y0_c = (0x00003fffU 
                                          & (- (IData)(vlSelfRef.gm_in_real)));
            vlSelfRef.angle__DOT__z0_c = 0x0192U;
        } else {
            vlSelfRef.angle__DOT__x0_c = (0x00003fffU 
                                          & (- (IData)(vlSelfRef.gm_in_imag)));
            vlSelfRef.angle__DOT__y0_c = (0x00003fffU 
                                          & (IData)(vlSelfRef.gm_in_real));
            vlSelfRef.angle__DOT__z0_c = 0x066eU;
        }
    }
}

void Vangle___024root___eval_ico(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_ico\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vangle___024root___ico_sequent__TOP__0(vlSelf);
    }
}

bool Vangle___024root___eval_phase__ico(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_phase__ico\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vangle___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = Vangle___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vangle___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vangle___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vangle___024root___eval_triggers__act(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_triggers__act\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.clk) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vangle___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vangle___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vangle___024root___nba_sequent__TOP__0(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___nba_sequent__TOP__0\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.rst) {
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__5__KET____DOT__u_pipe__Z_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Z_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Y_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Z_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__X_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Y_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Z_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__X_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Y_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Z_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__X_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Y_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Z_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__X_out = 0U;
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Y_out = 0U;
        vlSelfRef.angle__DOT__z0_r = 0U;
        vlSelfRef.angle__DOT__x0_r = 0U;
        vlSelfRef.angle__DOT__y0_r = 0U;
    } else {
        vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__5__KET____DOT__u_pipe__Z_out 
            = (0x000007ffU & ((0x00002000U & (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Y_out))
                               ? ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Z_out) 
                                  - (IData)(8U)) : 
                              ((IData)(8U) + (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Z_out))));
        if ((0x00002000U & (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Y_out))) {
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Z_out 
                = (0x000007ffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Z_out) 
                                  - (IData)(0x0010U)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Y_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Y_out) 
                                  + VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__X_out), 4U)));
        } else {
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Z_out 
                = (0x000007ffU & ((IData)(0x0010U) 
                                  + (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Z_out)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Y_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Y_out) 
                                  - VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__X_out), 4U)));
        }
        if ((0x00002000U & (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Y_out))) {
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Z_out 
                = (0x000007ffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Z_out) 
                                  - (IData)(0x001fU)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__X_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__X_out) 
                                  - VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Y_out), 3U)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Y_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Y_out) 
                                  + VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__X_out), 3U)));
        } else {
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Z_out 
                = (0x000007ffU & ((IData)(0x001fU) 
                                  + (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Z_out)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__X_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__X_out) 
                                  + VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Y_out), 3U)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Y_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Y_out) 
                                  - VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__X_out), 3U)));
        }
        if ((0x00002000U & (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Y_out))) {
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Z_out 
                = (0x000007ffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Z_out) 
                                  - (IData)(0x003eU)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__X_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__X_out) 
                                  - VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Y_out), 2U)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Y_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Y_out) 
                                  + VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__X_out), 2U)));
        } else {
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Z_out 
                = (0x000007ffU & ((IData)(0x003eU) 
                                  + (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Z_out)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__X_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__X_out) 
                                  + VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Y_out), 2U)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Y_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Y_out) 
                                  - VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__X_out), 2U)));
        }
        if ((0x00002000U & (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Y_out))) {
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Z_out 
                = (0x000007ffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Z_out) 
                                  - (IData)(0x0076U)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__X_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__X_out) 
                                  - VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Y_out), 1U)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Y_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Y_out) 
                                  + VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__X_out), 1U)));
        } else {
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Z_out 
                = (0x000007ffU & ((IData)(0x0076U) 
                                  + (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Z_out)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__X_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__X_out) 
                                  + VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Y_out), 1U)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Y_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Y_out) 
                                  - VL_SHIFTRS_III(14,14,32, (IData)(vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__X_out), 1U)));
        }
        if ((0x00002000U & (IData)(vlSelfRef.angle__DOT__y0_r))) {
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Z_out 
                = (0x000007ffU & ((IData)(vlSelfRef.angle__DOT__z0_r) 
                                  - (IData)(0x00c9U)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__X_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT__x0_r) 
                                  - (IData)(vlSelfRef.angle__DOT__y0_r)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Y_out 
                = (0x00003fffU & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0));
        } else {
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Z_out 
                = (0x000007ffU & ((IData)(0x00c9U) 
                                  + (IData)(vlSelfRef.angle__DOT__z0_r)));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__X_out 
                = (0x00003fffU & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0));
            vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Y_out 
                = (0x00003fffU & ((IData)(vlSelfRef.angle__DOT__y0_r) 
                                  - (IData)(vlSelfRef.angle__DOT__x0_r)));
        }
        vlSelfRef.angle__DOT__z0_r = vlSelfRef.angle__DOT__z0_c;
        vlSelfRef.angle__DOT__x0_r = vlSelfRef.angle__DOT__x0_c;
        vlSelfRef.angle__DOT__y0_r = vlSelfRef.angle__DOT__y0_c;
    }
    vlSelfRef.ang_out = vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__5__KET____DOT__u_pipe__Z_out;
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0 = (0x00003fffU 
                                                & ((IData)(vlSelfRef.angle__DOT__x0_r) 
                                                   + (IData)(vlSelfRef.angle__DOT__y0_r)));
}

void Vangle___024root___eval_nba(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_nba\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vangle___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vangle___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vangle___024root___eval_phase__act(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_phase__act\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vangle___024root___eval_triggers__act(vlSelf);
    Vangle___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vangle___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vangle___024root___eval_phase__nba(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_phase__nba\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vangle___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vangle___024root___eval_nba(vlSelf);
        Vangle___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vangle___024root___eval(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vangle___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("src/rtl/angle.sv", 67, "", "Input combinational region did not converge after 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
    } while (Vangle___024root___eval_phase__ico(vlSelf));
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vangle___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("src/rtl/angle.sv", 67, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vangle___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("src/rtl/angle.sv", 67, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vangle___024root___eval_phase__act(vlSelf));
    } while (Vangle___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vangle___024root___eval_debug_assertions(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_debug_assertions\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
    if (VL_UNLIKELY(((vlSelfRef.gm_in_real & 0xc000U)))) {
        Verilated::overWidthError("gm_in_real");
    }
    if (VL_UNLIKELY(((vlSelfRef.gm_in_imag & 0xc000U)))) {
        Verilated::overWidthError("gm_in_imag");
    }
}
#endif  // VL_DEBUG
