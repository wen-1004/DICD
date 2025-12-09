// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmag.h for the primary calling header

#include "Vmag__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmag___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vmag___024root___eval_triggers__ico(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_triggers__ico\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
    vlSelfRef.__VicoFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmag___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
}

bool Vmag___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___trigger_anySet__ico\n"); );
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

void Vmag___024root___ico_sequent__TOP__0(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___ico_sequent__TOP__0\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*13:0*/ mag__DOT__ax0;
    mag__DOT__ax0 = 0;
    SData/*13:0*/ mag__DOT__ay0;
    mag__DOT__ay0 = 0;
    CData/*0:0*/ mag__DOT____VdfgRegularize_h502bd168_0_0;
    mag__DOT____VdfgRegularize_h502bd168_0_0 = 0;
    // Body
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

void Vmag___024root___eval_ico(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_ico\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vmag___024root___ico_sequent__TOP__0(vlSelf);
    }
}

bool Vmag___024root___eval_phase__ico(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_phase__ico\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vmag___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = Vmag___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vmag___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmag___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vmag___024root___eval_triggers__act(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_triggers__act\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.clk) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmag___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vmag___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___trigger_anySet__act\n"); );
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

void Vmag___024root___nba_sequent__TOP__0(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___nba_sequent__TOP__0\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*3:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    if (vlSelfRef.rst) {
        vlSelfRef.mag__DOT__left1 = 0U;
        vlSelfRef.mag__DOT__max_u1 = 0U;
        vlSelfRef.mag__DOT__seg_idx_s2 = 9U;
        vlSelfRef.mag_out = 0U;
        vlSelfRef.mag__DOT__term_b_s3 = 0U;
        vlSelfRef.mag__DOT__term_a_s3 = 0U;
        vlSelfRef.mag__DOT__min_s2 = 0U;
        vlSelfRef.mag__DOT__max_s2 = 0U;
        vlSelfRef.mag__DOT__min_s1 = 0U;
        vlSelfRef.mag__DOT__max_s1 = 0U;
    } else {
        vlSelfRef.mag__DOT__left1 = ((IData)(vlSelfRef.mag__DOT__min0) 
                                     << 8U);
        vlSelfRef.mag__DOT__max_u1 = vlSelfRef.mag__DOT__max0;
        vlSelfRef.mag__DOT__seg_idx_s2 = vlSelfRef.mag__DOT__seg_idx_c;
        vlSelfRef.mag_out = (0x00003fffU & ((IData)(vlSelfRef.mag__DOT__term_a_s3) 
                                            + (IData)(vlSelfRef.mag__DOT__term_b_s3)));
        vlSelfRef.mag__DOT__term_b_s3 = (0x00007fffU 
                                         & VL_SHIFTRS_III(24,24,32, 
                                                          (0x00ffffffU 
                                                           & VL_MULS_III(24, 
                                                                         (0x00ffffffU 
                                                                          & VL_EXTENDS_II(24,10, (IData)(vlSelfRef.mag__DOT__beta_s3_c))), 
                                                                         (0x00ffffffU 
                                                                          & VL_EXTENDS_II(24,14, (IData)(vlSelfRef.mag__DOT__min_s2))))), 8U));
        vlSelfRef.mag__DOT__term_a_s3 = (0x00007fffU 
                                         & VL_SHIFTRS_III(24,24,32, 
                                                          (0x00ffffffU 
                                                           & VL_MULS_III(24, 
                                                                         (0x00ffffffU 
                                                                          & VL_EXTENDS_II(24,10, (IData)(vlSelfRef.mag__DOT__alpha_s3_c))), 
                                                                         (0x00ffffffU 
                                                                          & VL_EXTENDS_II(24,14, (IData)(vlSelfRef.mag__DOT__max_s2))))), 8U));
        vlSelfRef.mag__DOT__min_s2 = vlSelfRef.mag__DOT__min_s1;
        vlSelfRef.mag__DOT__max_s2 = vlSelfRef.mag__DOT__max_s1;
        vlSelfRef.mag__DOT__min_s1 = vlSelfRef.mag__DOT__min0;
        vlSelfRef.mag__DOT__max_s1 = vlSelfRef.mag__DOT__max0;
    }
    vlSelfRef.mag__DOT__max_zero1 = ((IData)(vlSelfRef.rst) 
                                     || (0U == (IData)(vlSelfRef.mag__DOT__max0)));
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
}

void Vmag___024root___eval_nba(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_nba\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vmag___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vmag___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vmag___024root___eval_phase__act(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_phase__act\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vmag___024root___eval_triggers__act(vlSelf);
    Vmag___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vmag___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vmag___024root___eval_phase__nba(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_phase__nba\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vmag___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vmag___024root___eval_nba(vlSelf);
        Vmag___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vmag___024root___eval(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
            Vmag___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("src/rtl/mag.sv", 3, "", "Input combinational region did not converge after 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
    } while (Vmag___024root___eval_phase__ico(vlSelf));
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vmag___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("src/rtl/mag.sv", 3, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vmag___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("src/rtl/mag.sv", 3, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vmag___024root___eval_phase__act(vlSelf));
    } while (Vmag___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vmag___024root___eval_debug_assertions(Vmag___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmag___024root___eval_debug_assertions\n"); );
    Vmag__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
