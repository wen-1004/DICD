// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vminus.h for the primary calling header

#include "Vminus__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vminus___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vminus___024root___eval_triggers__act(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_triggers__act\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.clk) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vminus___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vminus___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___trigger_anySet__act\n"); );
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

void Vminus___024root___nba_sequent__TOP__0(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___nba_sequent__TOP__0\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VdlySet__minus__DOT__delay_line__v0;
    __VdlySet__minus__DOT__delay_line__v0 = 0;
    SData/*13:0*/ __VdlyVal__minus__DOT__delay_line__v6;
    __VdlyVal__minus__DOT__delay_line__v6 = 0;
    CData/*0:0*/ __VdlySet__minus__DOT__delay_line__v6;
    __VdlySet__minus__DOT__delay_line__v6 = 0;
    SData/*13:0*/ __VdlyVal__minus__DOT__delay_line__v7;
    __VdlyVal__minus__DOT__delay_line__v7 = 0;
    CData/*0:0*/ __VdlySet__minus__DOT__delay_line__v7;
    __VdlySet__minus__DOT__delay_line__v7 = 0;
    SData/*13:0*/ __VdlyVal__minus__DOT__delay_line__v8;
    __VdlyVal__minus__DOT__delay_line__v8 = 0;
    CData/*0:0*/ __VdlySet__minus__DOT__delay_line__v8;
    __VdlySet__minus__DOT__delay_line__v8 = 0;
    SData/*13:0*/ __VdlyVal__minus__DOT__delay_line__v9;
    __VdlyVal__minus__DOT__delay_line__v9 = 0;
    CData/*0:0*/ __VdlySet__minus__DOT__delay_line__v9;
    __VdlySet__minus__DOT__delay_line__v9 = 0;
    SData/*13:0*/ __VdlyVal__minus__DOT__delay_line__v10;
    __VdlyVal__minus__DOT__delay_line__v10 = 0;
    CData/*0:0*/ __VdlySet__minus__DOT__delay_line__v10;
    __VdlySet__minus__DOT__delay_line__v10 = 0;
    SData/*13:0*/ __VdlyVal__minus__DOT__delay_line__v11;
    __VdlyVal__minus__DOT__delay_line__v11 = 0;
    CData/*0:0*/ __VdlySet__minus__DOT__delay_line__v11;
    __VdlySet__minus__DOT__delay_line__v11 = 0;
    // Body
    __VdlySet__minus__DOT__delay_line__v0 = 0U;
    __VdlySet__minus__DOT__delay_line__v6 = 0U;
    __VdlySet__minus__DOT__delay_line__v7 = 0U;
    __VdlySet__minus__DOT__delay_line__v8 = 0U;
    __VdlySet__minus__DOT__delay_line__v9 = 0U;
    __VdlySet__minus__DOT__delay_line__v10 = 0U;
    __VdlySet__minus__DOT__delay_line__v11 = 0U;
    if (vlSelfRef.rst) {
        __VdlySet__minus__DOT__delay_line__v0 = 1U;
    } else {
        __VdlyVal__minus__DOT__delay_line__v6 = (0x00003fffU 
                                                 & ((IData)(vlSelfRef.mag_in) 
                                                    - 
                                                    (0x003fffffU 
                                                     & VL_SHIFTRS_III(22,22,32, 
                                                                      (0x003fffffU 
                                                                       & VL_MULS_III(22, 
                                                                                (0x003fffffU 
                                                                                & VL_EXTENDS_II(22,8, (IData)(vlSelfRef.rho_in))), 
                                                                                (0x003fffffU 
                                                                                & VL_EXTENDS_II(22,15, (IData)(vlSelfRef.phi_in))))), 7U))));
        __VdlySet__minus__DOT__delay_line__v6 = 1U;
        vlSelfRef.minus__DOT____Vlvbound_heb8cafb3__0 
            = vlSelfRef.minus__DOT__delay_line[0U];
        __VdlyVal__minus__DOT__delay_line__v7 = vlSelfRef.minus__DOT____Vlvbound_heb8cafb3__0;
        __VdlySet__minus__DOT__delay_line__v7 = 1U;
        vlSelfRef.minus__DOT____Vlvbound_heb8cafb3__0 
            = vlSelfRef.minus__DOT__delay_line[1U];
        __VdlyVal__minus__DOT__delay_line__v8 = vlSelfRef.minus__DOT____Vlvbound_heb8cafb3__0;
        __VdlySet__minus__DOT__delay_line__v8 = 1U;
        vlSelfRef.minus__DOT____Vlvbound_heb8cafb3__0 
            = vlSelfRef.minus__DOT__delay_line[2U];
        __VdlyVal__minus__DOT__delay_line__v9 = vlSelfRef.minus__DOT____Vlvbound_heb8cafb3__0;
        __VdlySet__minus__DOT__delay_line__v9 = 1U;
        vlSelfRef.minus__DOT____Vlvbound_heb8cafb3__0 
            = vlSelfRef.minus__DOT__delay_line[3U];
        __VdlyVal__minus__DOT__delay_line__v10 = vlSelfRef.minus__DOT____Vlvbound_heb8cafb3__0;
        __VdlySet__minus__DOT__delay_line__v10 = 1U;
        vlSelfRef.minus__DOT____Vlvbound_heb8cafb3__0 
            = vlSelfRef.minus__DOT__delay_line[4U];
        __VdlyVal__minus__DOT__delay_line__v11 = vlSelfRef.minus__DOT____Vlvbound_heb8cafb3__0;
        __VdlySet__minus__DOT__delay_line__v11 = 1U;
    }
    if (__VdlySet__minus__DOT__delay_line__v0) {
        vlSelfRef.minus__DOT__delay_line[0U] = 0U;
        vlSelfRef.minus__DOT__delay_line[1U] = 0U;
        vlSelfRef.minus__DOT__delay_line[2U] = 0U;
        vlSelfRef.minus__DOT__delay_line[3U] = 0U;
        vlSelfRef.minus__DOT__delay_line[4U] = 0U;
        vlSelfRef.minus__DOT__delay_line[5U] = 0U;
    }
    if (__VdlySet__minus__DOT__delay_line__v6) {
        vlSelfRef.minus__DOT__delay_line[0U] = __VdlyVal__minus__DOT__delay_line__v6;
    }
    if (__VdlySet__minus__DOT__delay_line__v7) {
        vlSelfRef.minus__DOT__delay_line[1U] = __VdlyVal__minus__DOT__delay_line__v7;
    }
    if (__VdlySet__minus__DOT__delay_line__v8) {
        vlSelfRef.minus__DOT__delay_line[2U] = __VdlyVal__minus__DOT__delay_line__v8;
    }
    if (__VdlySet__minus__DOT__delay_line__v9) {
        vlSelfRef.minus__DOT__delay_line[3U] = __VdlyVal__minus__DOT__delay_line__v9;
    }
    if (__VdlySet__minus__DOT__delay_line__v10) {
        vlSelfRef.minus__DOT__delay_line[4U] = __VdlyVal__minus__DOT__delay_line__v10;
    }
    if (__VdlySet__minus__DOT__delay_line__v11) {
        vlSelfRef.minus__DOT__delay_line[5U] = __VdlyVal__minus__DOT__delay_line__v11;
    }
    vlSelfRef.lambda_out = vlSelfRef.minus__DOT__delay_line
        [5U];
}

void Vminus___024root___eval_nba(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_nba\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vminus___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vminus___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vminus___024root___eval_phase__act(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_phase__act\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vminus___024root___eval_triggers__act(vlSelf);
    Vminus___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vminus___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vminus___024root___eval_phase__nba(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_phase__nba\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vminus___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vminus___024root___eval_nba(vlSelf);
        Vminus___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vminus___024root___eval(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vminus___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("src/rtl/minus.sv", 3, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vminus___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("src/rtl/minus.sv", 3, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vminus___024root___eval_phase__act(vlSelf));
    } while (Vminus___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vminus___024root___eval_debug_assertions(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_debug_assertions\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
    if (VL_UNLIKELY(((vlSelfRef.mag_in & 0xc000U)))) {
        Verilated::overWidthError("mag_in");
    }
    if (VL_UNLIKELY(((vlSelfRef.phi_in & 0xc000U)))) {
        Verilated::overWidthError("phi_in");
    }
}
#endif  // VL_DEBUG
