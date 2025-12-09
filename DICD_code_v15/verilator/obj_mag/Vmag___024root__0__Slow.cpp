// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmag.h for the primary calling header

#include "Vmag__pch.h"

VL_ATTR_COLD void Vmag___024root___eval_static(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_static\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vmag___024root___eval_initial(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_initial\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vmag___024root___eval_final(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_final\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmag___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vmag___024root___eval_phase__stl(Vmag___024root* vlSelf);

VL_ATTR_COLD void Vmag___024root___eval_settle(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_settle\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vmag___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("src/rtl/mag.sv", 3, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vmag___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vmag___024root___eval_triggers__stl(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_triggers__stl\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmag___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vmag___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmag___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vmag___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vmag___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___trigger_anySet__stl\n"); );
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

extern const VlUnpacked<SData/*9:0*/, 16> Vmag__ConstPool__TABLE_hf5a88ec6_0;
extern const VlUnpacked<SData/*9:0*/, 16> Vmag__ConstPool__TABLE_h6b6fead5_0;

VL_ATTR_COLD void Vmag___024root___stl_sequent__TOP__0(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___stl_sequent__TOP__0\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*13:0*/ mag__DOT__ax0;
    mag__DOT__ax0 = 0;
    SData/*13:0*/ mag__DOT__ay0;
    mag__DOT__ay0 = 0;
    CData/*0:0*/ mag__DOT____VdfgRegularize_h502bd168_0_0;
    mag__DOT____VdfgRegularize_h502bd168_0_0 = 0;
    CData/*3:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    vlSelfRef.mag__DOT__seg_idx_c = 8U;
    if (vlSelfRef.mag__DOT__max_zero1) {
        vlSelfRef.mag__DOT__seg_idx_c = 9U;
    } else if ((vlSelfRef.mag__DOT__left1 < (0x003fffffU 
                                             & ((IData)(0x00000019U) 
                                                * (IData)(vlSelfRef.mag__DOT__max_u1))))) {
        vlSelfRef.mag__DOT__seg_idx_c = 0U;
    } else if ((vlSelfRef.mag__DOT__left1 < (0x003fffffU 
                                             & ((IData)(0x00000033U) 
                                                * (IData)(vlSelfRef.mag__DOT__max_u1))))) {
        vlSelfRef.mag__DOT__seg_idx_c = 1U;
    } else if ((vlSelfRef.mag__DOT__left1 < (0x003fffffU 
                                             & ((IData)(0x0000004eU) 
                                                * (IData)(vlSelfRef.mag__DOT__max_u1))))) {
        vlSelfRef.mag__DOT__seg_idx_c = 2U;
    } else if ((vlSelfRef.mag__DOT__left1 < (0x003fffffU 
                                             & ((IData)(0x0000006aU) 
                                                * (IData)(vlSelfRef.mag__DOT__max_u1))))) {
        vlSelfRef.mag__DOT__seg_idx_c = 3U;
    } else if ((vlSelfRef.mag__DOT__left1 < (0x003fffffU 
                                             & ((IData)(0x00000089U) 
                                                * (IData)(vlSelfRef.mag__DOT__max_u1))))) {
        vlSelfRef.mag__DOT__seg_idx_c = 4U;
    } else if ((vlSelfRef.mag__DOT__left1 < (0x003fffffU 
                                             & ((IData)(0x000000abU) 
                                                * (IData)(vlSelfRef.mag__DOT__max_u1))))) {
        vlSelfRef.mag__DOT__seg_idx_c = 5U;
    } else if ((vlSelfRef.mag__DOT__left1 < (0x003fffffU 
                                             & ((IData)(0x000000c8U) 
                                                * (IData)(vlSelfRef.mag__DOT__max_u1))))) {
        vlSelfRef.mag__DOT__seg_idx_c = 6U;
    } else if ((vlSelfRef.mag__DOT__left1 < (0x003fffffU 
                                             & ((IData)(0x000000d2U) 
                                                * (IData)(vlSelfRef.mag__DOT__max_u1))))) {
        vlSelfRef.mag__DOT__seg_idx_c = 7U;
    }
    __Vtableidx1 = vlSelfRef.mag__DOT__seg_idx_s2;
    vlSelfRef.mag__DOT__alpha_s3_c = Vmag__ConstPool__TABLE_hf5a88ec6_0
        [__Vtableidx1];
    vlSelfRef.mag__DOT__beta_s3_c = Vmag__ConstPool__TABLE_h6b6fead5_0
        [__Vtableidx1];
    mag__DOT__ax0 = (0x00003fffU & ((0x00002000U & (IData)(vlSelfRef.gm_in_real))
                                     ? (- (IData)(vlSelfRef.gm_in_real))
                                     : (IData)(vlSelfRef.gm_in_real)));
    mag__DOT__ay0 = (0x00003fffU & ((0x00002000U & (IData)(vlSelfRef.gm_in_imag))
                                     ? (- (IData)(vlSelfRef.gm_in_imag))
                                     : (IData)(vlSelfRef.gm_in_imag)));
    mag__DOT____VdfgRegularize_h502bd168_0_0 = VL_GTES_III(14, (IData)(mag__DOT__ax0), (IData)(mag__DOT__ay0));
    if (mag__DOT____VdfgRegularize_h502bd168_0_0) {
        vlSelfRef.mag__DOT__max0 = mag__DOT__ax0;
        vlSelfRef.mag__DOT__min0 = mag__DOT__ay0;
    } else {
        vlSelfRef.mag__DOT__max0 = mag__DOT__ay0;
        vlSelfRef.mag__DOT__min0 = mag__DOT__ax0;
    }
}

VL_ATTR_COLD void Vmag___024root___eval_stl(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_stl\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vmag___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vmag___024root___eval_phase__stl(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_phase__stl\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vmag___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vmag___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vmag___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vmag___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmag___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vmag___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vmag___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmag___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vmag___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vmag___024root___ctor_var_reset(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___ctor_var_reset\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->gm_in_real = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 13940093710908832200ull);
    vlSelf->gm_in_imag = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 8565475022954267765ull);
    vlSelf->mag_out = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 6470275627258493998ull);
    vlSelf->mag__DOT__max0 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 4553618650940201291ull);
    vlSelf->mag__DOT__min0 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 9162606526987621226ull);
    vlSelf->mag__DOT__max_s1 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 9444068354757800782ull);
    vlSelf->mag__DOT__min_s1 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 12536480404115659618ull);
    vlSelf->mag__DOT__max_u1 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 17566326586760191753ull);
    vlSelf->mag__DOT__left1 = VL_SCOPED_RAND_RESET_I(22, __VscopeHash, 2047208254359546058ull);
    vlSelf->mag__DOT__max_zero1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4599559343032826956ull);
    vlSelf->mag__DOT__seg_idx_c = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 6497235438138884136ull);
    vlSelf->mag__DOT__seg_idx_s2 = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 15258255789929754097ull);
    vlSelf->mag__DOT__max_s2 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 17385565901083914036ull);
    vlSelf->mag__DOT__min_s2 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 12376558371414861398ull);
    vlSelf->mag__DOT__alpha_s3_c = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 2420263948243848863ull);
    vlSelf->mag__DOT__beta_s3_c = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 9295710394389709951ull);
    vlSelf->mag__DOT__term_a_s3 = VL_SCOPED_RAND_RESET_I(15, __VscopeHash, 10394056643365658957ull);
    vlSelf->mag__DOT__term_b_s3 = VL_SCOPED_RAND_RESET_I(15, __VscopeHash, 2197054239729644033ull);
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
