// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vangle.h for the primary calling header

#include "Vangle__pch.h"

VL_ATTR_COLD void Vangle___024root___eval_static(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_static\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vangle___024root___eval_initial(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_initial\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vangle___024root___eval_final(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_final\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vangle___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vangle___024root___eval_phase__stl(Vangle___024root* vlSelf);

VL_ATTR_COLD void Vangle___024root___eval_settle(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_settle\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vangle___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("src/rtl/angle.sv", 67, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vangle___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vangle___024root___eval_triggers__stl(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_triggers__stl\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vangle___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vangle___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vangle___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vangle___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vangle___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vangle___024root___stl_sequent__TOP__0(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___stl_sequent__TOP__0\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.ang_out = vlSelfRef.angle__DOT____Vcellout__STAGE__BRA__5__KET____DOT__u_pipe__Z_out;
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
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0 = (0x00003fffU 
                                                & ((IData)(vlSelfRef.angle__DOT__x0_r) 
                                                   + (IData)(vlSelfRef.angle__DOT__y0_r)));
}

VL_ATTR_COLD void Vangle___024root___eval_stl(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_stl\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vangle___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vangle___024root___eval_phase__stl(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___eval_phase__stl\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vangle___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vangle___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vangle___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vangle___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vangle___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vangle___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vangle___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vangle___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vangle___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vangle___024root___ctor_var_reset(Vangle___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vangle___024root___ctor_var_reset\n"); );
    Vangle__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->gm_in_real = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 13940093710908832200ull);
    vlSelf->gm_in_imag = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 8565475022954267765ull);
    vlSelf->ang_out = VL_SCOPED_RAND_RESET_I(11, __VscopeHash, 15449643848301903643ull);
    vlSelf->angle__DOT__x0_c = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 11626850135462850043ull);
    vlSelf->angle__DOT__y0_c = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 9710786604856757833ull);
    vlSelf->angle__DOT__z0_c = VL_SCOPED_RAND_RESET_I(11, __VscopeHash, 15430298838484512040ull);
    vlSelf->angle__DOT__x0_r = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 5964695170260993108ull);
    vlSelf->angle__DOT__y0_r = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 3843452678742893551ull);
    vlSelf->angle__DOT__z0_r = VL_SCOPED_RAND_RESET_I(11, __VscopeHash, 13576841132305794001ull);
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Z_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__Y_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__0__KET____DOT__u_pipe__X_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Z_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__Y_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__1__KET____DOT__u_pipe__X_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Z_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__Y_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__2__KET____DOT__u_pipe__X_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Z_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__Y_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__3__KET____DOT__u_pipe__X_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Z_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__4__KET____DOT__u_pipe__Y_out = 0;
    vlSelf->angle__DOT____Vcellout__STAGE__BRA__5__KET____DOT__u_pipe__Z_out = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
