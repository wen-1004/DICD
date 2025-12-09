// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdelay_n.h for the primary calling header

#include "Vdelay_n__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdelay_n___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vdelay_n___024root___eval_triggers__act(Vdelay_n___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___eval_triggers__act\n"); );
    Vdelay_n__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.clk) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdelay_n___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vdelay_n___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___trigger_anySet__act\n"); );
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

void Vdelay_n___024root___nba_sequent__TOP__0(Vdelay_n___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___nba_sequent__TOP__0\n"); );
    Vdelay_n__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __VdlyDim0__delay_n__DOT__delay_line_real__v0;
    __VdlyDim0__delay_n__DOT__delay_line_real__v0 = 0;
    CData/*7:0*/ __VdlyDim0__delay_n__DOT__delay_line_imag__v0;
    __VdlyDim0__delay_n__DOT__delay_line_imag__v0 = 0;
    CData/*6:0*/ __VdlyVal__delay_n__DOT__delay_line_real__v1;
    __VdlyVal__delay_n__DOT__delay_line_real__v1 = 0;
    CData/*7:0*/ __VdlyDim0__delay_n__DOT__delay_line_real__v1;
    __VdlyDim0__delay_n__DOT__delay_line_real__v1 = 0;
    CData/*6:0*/ __VdlyVal__delay_n__DOT__delay_line_imag__v1;
    __VdlyVal__delay_n__DOT__delay_line_imag__v1 = 0;
    CData/*7:0*/ __VdlyDim0__delay_n__DOT__delay_line_imag__v1;
    __VdlyDim0__delay_n__DOT__delay_line_imag__v1 = 0;
    CData/*6:0*/ __VdlyVal__delay_n__DOT__delay_line_real__v2;
    __VdlyVal__delay_n__DOT__delay_line_real__v2 = 0;
    CData/*6:0*/ __VdlyVal__delay_n__DOT__delay_line_imag__v2;
    __VdlyVal__delay_n__DOT__delay_line_imag__v2 = 0;
    // Body
    if (vlSelfRef.rst) {
        vlSelfRef.r_d1_real = 0U;
        vlSelfRef.r_d1_imag = 0U;
    } else {
        vlSelfRef.r_d1_real = (0x0000007fU & ((IData)(vlSelfRef.r_in_real) 
                                              >> 9U));
        vlSelfRef.r_d1_imag = (0x0000007fU & ((IData)(vlSelfRef.r_in_imag) 
                                              >> 9U));
    }
    if (vlSelfRef.rst) {
        vlSelfRef.delay_n__DOT__i = 0U;
        while (VL_GTS_III(32, 0x00000100U, vlSelfRef.delay_n__DOT__i)) {
            __VdlyDim0__delay_n__DOT__delay_line_real__v0 
                = (0x000000ffU & vlSelfRef.delay_n__DOT__i);
            vlSelfRef.__VdlyCommitQueuedelay_n__DOT__delay_line_real.enqueue(0U, (IData)(__VdlyDim0__delay_n__DOT__delay_line_real__v0));
            __VdlyDim0__delay_n__DOT__delay_line_imag__v0 
                = (0x000000ffU & vlSelfRef.delay_n__DOT__i);
            vlSelfRef.__VdlyCommitQueuedelay_n__DOT__delay_line_imag.enqueue(0U, (IData)(__VdlyDim0__delay_n__DOT__delay_line_imag__v0));
            vlSelfRef.delay_n__DOT__i = ((IData)(1U) 
                                         + vlSelfRef.delay_n__DOT__i);
        }
        vlSelfRef.r_dN_out_real = 0U;
        vlSelfRef.r_dN_out_imag = 0U;
    } else {
        vlSelfRef.r_dN_out_real = vlSelfRef.delay_n__DOT__delay_line_real
            [0xffU];
        vlSelfRef.r_dN_out_imag = vlSelfRef.delay_n__DOT__delay_line_imag
            [0xffU];
        vlSelfRef.delay_n__DOT__i = 0x000000ffU;
        while (VL_LTS_III(32, 0U, vlSelfRef.delay_n__DOT__i)) {
            __VdlyVal__delay_n__DOT__delay_line_real__v1 
                = vlSelfRef.delay_n__DOT__delay_line_real
                [(0x000000ffU & (vlSelfRef.delay_n__DOT__i 
                                 - (IData)(1U)))];
            __VdlyDim0__delay_n__DOT__delay_line_real__v1 
                = (0x000000ffU & vlSelfRef.delay_n__DOT__i);
            vlSelfRef.__VdlyCommitQueuedelay_n__DOT__delay_line_real.enqueue(__VdlyVal__delay_n__DOT__delay_line_real__v1, (IData)(__VdlyDim0__delay_n__DOT__delay_line_real__v1));
            __VdlyVal__delay_n__DOT__delay_line_imag__v1 
                = vlSelfRef.delay_n__DOT__delay_line_imag
                [(0x000000ffU & (vlSelfRef.delay_n__DOT__i 
                                 - (IData)(1U)))];
            __VdlyDim0__delay_n__DOT__delay_line_imag__v1 
                = (0x000000ffU & vlSelfRef.delay_n__DOT__i);
            vlSelfRef.__VdlyCommitQueuedelay_n__DOT__delay_line_imag.enqueue(__VdlyVal__delay_n__DOT__delay_line_imag__v1, (IData)(__VdlyDim0__delay_n__DOT__delay_line_imag__v1));
            vlSelfRef.delay_n__DOT__i = (vlSelfRef.delay_n__DOT__i 
                                         - (IData)(1U));
        }
        __VdlyVal__delay_n__DOT__delay_line_real__v2 
            = (0x0000007fU & ((IData)(vlSelfRef.r_in_real) 
                              >> 9U));
        vlSelfRef.__VdlyCommitQueuedelay_n__DOT__delay_line_real.enqueue(__VdlyVal__delay_n__DOT__delay_line_real__v2, 0U);
        __VdlyVal__delay_n__DOT__delay_line_imag__v2 
            = (0x0000007fU & ((IData)(vlSelfRef.r_in_imag) 
                              >> 9U));
        vlSelfRef.__VdlyCommitQueuedelay_n__DOT__delay_line_imag.enqueue(__VdlyVal__delay_n__DOT__delay_line_imag__v2, 0U);
    }
    vlSelfRef.__VdlyCommitQueuedelay_n__DOT__delay_line_real.commit(vlSelfRef.delay_n__DOT__delay_line_real);
    vlSelfRef.__VdlyCommitQueuedelay_n__DOT__delay_line_imag.commit(vlSelfRef.delay_n__DOT__delay_line_imag);
}

void Vdelay_n___024root___eval_nba(Vdelay_n___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___eval_nba\n"); );
    Vdelay_n__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vdelay_n___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vdelay_n___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vdelay_n___024root___eval_phase__act(Vdelay_n___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___eval_phase__act\n"); );
    Vdelay_n__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vdelay_n___024root___eval_triggers__act(vlSelf);
    Vdelay_n___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vdelay_n___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vdelay_n___024root___eval_phase__nba(Vdelay_n___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___eval_phase__nba\n"); );
    Vdelay_n__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vdelay_n___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vdelay_n___024root___eval_nba(vlSelf);
        Vdelay_n___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vdelay_n___024root___eval(Vdelay_n___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___eval\n"); );
    Vdelay_n__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vdelay_n___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("src/rtl/delay_n.sv", 3, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vdelay_n___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("src/rtl/delay_n.sv", 3, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vdelay_n___024root___eval_phase__act(vlSelf));
    } while (Vdelay_n___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vdelay_n___024root___eval_debug_assertions(Vdelay_n___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___eval_debug_assertions\n"); );
    Vdelay_n__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
}
#endif  // VL_DEBUG
