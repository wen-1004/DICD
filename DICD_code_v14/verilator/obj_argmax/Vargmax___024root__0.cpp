// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vargmax.h for the primary calling header

#include "Vargmax__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vargmax___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vargmax___024root___eval_triggers__ico(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_triggers__ico\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
    vlSelfRef.__VicoFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vargmax___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
}

bool Vargmax___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___trigger_anySet__ico\n"); );
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

void Vargmax___024root___ico_sequent__TOP__0(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___ico_sequent__TOP__0\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ argmax__DOT____VdfgRegularize_hbc8f6d79_0_1;
    argmax__DOT____VdfgRegularize_hbc8f6d79_0_1 = 0;
    // Body
    argmax__DOT____VdfgRegularize_hbc8f6d79_0_1 = (
                                                   VL_GTES_III(14, (IData)(vlSelfRef.lambda_in), (IData)(vlSelfRef.argmax__DOT__current_max)) 
                                                   | ((6U 
                                                       == (IData)(vlSelfRef.lambda_in)) 
                                                      & (0x00a0U 
                                                         == (IData)(vlSelfRef.argmax__DOT__count))));
    if ((0U == (IData)(vlSelfRef.argmax__DOT__count))) {
        vlSelfRef.argmax__DOT__theta_idx_for_out = 0x000000ffU;
        vlSelfRef.argmax__DOT__current_ang_next = vlSelfRef.angle_in;
    } else if (argmax__DOT____VdfgRegularize_hbc8f6d79_0_1) {
        vlSelfRef.argmax__DOT__theta_idx_for_out = 0x000000ffU;
        vlSelfRef.argmax__DOT__current_ang_next = vlSelfRef.angle_in;
    } else {
        vlSelfRef.argmax__DOT__theta_idx_for_out = 
            (0x000003ffU & ((IData)(vlSelfRef.argmax__DOT__current_max_idx_s) 
                            - (IData)(1U)));
        vlSelfRef.argmax__DOT__current_ang_next = vlSelfRef.argmax__DOT__current_ang;
    }
    vlSelfRef.argmax__DOT__current_max_next = (VL_LTES_III(10, 0x0100U, 
                                                           (0x000003ffU 
                                                            & ((IData)(1U) 
                                                               + (IData)(vlSelfRef.argmax__DOT__count))))
                                                ? 0x2000U
                                                : (
                                                   (0U 
                                                    == (IData)(vlSelfRef.argmax__DOT__count))
                                                    ? (IData)(vlSelfRef.lambda_in)
                                                    : 
                                                   ((IData)(argmax__DOT____VdfgRegularize_hbc8f6d79_0_1)
                                                     ? (IData)(vlSelfRef.lambda_in)
                                                     : (IData)(vlSelfRef.argmax__DOT__current_max))));
}

void Vargmax___024root___eval_ico(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_ico\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vargmax___024root___ico_sequent__TOP__0(vlSelf);
    }
}

bool Vargmax___024root___eval_phase__ico(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_phase__ico\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vargmax___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = Vargmax___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vargmax___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vargmax___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vargmax___024root___eval_triggers__act(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_triggers__act\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.clk) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vargmax___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vargmax___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___trigger_anySet__act\n"); );
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

void Vargmax___024root___nba_sequent__TOP__0(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___nba_sequent__TOP__0\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ argmax__DOT____VdfgRegularize_hbc8f6d79_0_1;
    argmax__DOT____VdfgRegularize_hbc8f6d79_0_1 = 0;
    // Body
    if (vlSelfRef.rst) {
        vlSelfRef.argmax__DOT__theta_out_r = 0U;
        vlSelfRef.argmax__DOT__eps_out_r = 0U;
        vlSelfRef.argmax__DOT__current_ang = 0U;
        vlSelfRef.argmax__DOT__current_max = 0x2000U;
        vlSelfRef.argmax__DOT__current_max_idx_s = 0U;
        vlSelfRef.argmax__DOT__count = 0x02e5U;
    } else {
        vlSelfRef.argmax__DOT__theta_out_r = (0x000000ffU 
                                              & (IData)(vlSelfRef.argmax__DOT__theta_idx_for_out));
        vlSelfRef.argmax__DOT__eps_out_r = (0x001fffffU 
                                            & VL_SHIFTL_III(21,21,32, 
                                                            (0x007fffffU 
                                                             & VL_EXTENDS_II(23,19, 
                                                                             (0x0007ffffU 
                                                                              & VL_MULS_III(19, (IData)(0x00000028U), 
                                                                                (0x0007ffffU 
                                                                                & VL_EXTENDS_II(19,11, (IData)(vlSelfRef.argmax__DOT__current_ang_next))))))), 4U));
        vlSelfRef.argmax__DOT__current_ang = vlSelfRef.argmax__DOT__current_ang_next;
        vlSelfRef.argmax__DOT__current_max = vlSelfRef.argmax__DOT__current_max_next;
        vlSelfRef.argmax__DOT__current_max_idx_s = 
            (VL_LTES_III(10, 0x0100U, (0x000003ffU 
                                       & ((IData)(1U) 
                                          + (IData)(vlSelfRef.argmax__DOT__count))))
              ? 0x0100U : (IData)(vlSelfRef.argmax__DOT__theta_idx_for_out));
        vlSelfRef.argmax__DOT__count = vlSelfRef.argmax__DOT__count_next;
    }
    vlSelfRef.theta_out = vlSelfRef.argmax__DOT__theta_out_r;
    vlSelfRef.eps_out = vlSelfRef.argmax__DOT__eps_out_r;
    argmax__DOT____VdfgRegularize_hbc8f6d79_0_1 = (
                                                   VL_GTES_III(14, (IData)(vlSelfRef.lambda_in), (IData)(vlSelfRef.argmax__DOT__current_max)) 
                                                   | ((6U 
                                                       == (IData)(vlSelfRef.lambda_in)) 
                                                      & (0x00a0U 
                                                         == (IData)(vlSelfRef.argmax__DOT__count))));
    if (VL_LTES_III(10, 0x0100U, (0x000003ffU & ((IData)(1U) 
                                                 + (IData)(vlSelfRef.argmax__DOT__count))))) {
        vlSelfRef.argmax__DOT__count_next = 0U;
        vlSelfRef.argmax__DOT__current_max_next = 0x2000U;
    } else {
        vlSelfRef.argmax__DOT__count_next = (0x000003ffU 
                                             & ((IData)(1U) 
                                                + (IData)(vlSelfRef.argmax__DOT__count)));
        vlSelfRef.argmax__DOT__current_max_next = (
                                                   (0U 
                                                    == (IData)(vlSelfRef.argmax__DOT__count))
                                                    ? (IData)(vlSelfRef.lambda_in)
                                                    : 
                                                   ((IData)(argmax__DOT____VdfgRegularize_hbc8f6d79_0_1)
                                                     ? (IData)(vlSelfRef.lambda_in)
                                                     : (IData)(vlSelfRef.argmax__DOT__current_max)));
    }
    if ((0U == (IData)(vlSelfRef.argmax__DOT__count))) {
        vlSelfRef.argmax__DOT__theta_idx_for_out = 0x000000ffU;
        vlSelfRef.argmax__DOT__current_ang_next = vlSelfRef.angle_in;
    } else if (argmax__DOT____VdfgRegularize_hbc8f6d79_0_1) {
        vlSelfRef.argmax__DOT__theta_idx_for_out = 0x000000ffU;
        vlSelfRef.argmax__DOT__current_ang_next = vlSelfRef.angle_in;
    } else {
        vlSelfRef.argmax__DOT__theta_idx_for_out = 
            (0x000003ffU & ((IData)(vlSelfRef.argmax__DOT__current_max_idx_s) 
                            - (IData)(1U)));
        vlSelfRef.argmax__DOT__current_ang_next = vlSelfRef.argmax__DOT__current_ang;
    }
}

void Vargmax___024root___eval_nba(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_nba\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vargmax___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vargmax___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vargmax___024root___eval_phase__act(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_phase__act\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vargmax___024root___eval_triggers__act(vlSelf);
    Vargmax___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vargmax___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vargmax___024root___eval_phase__nba(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_phase__nba\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vargmax___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vargmax___024root___eval_nba(vlSelf);
        Vargmax___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vargmax___024root___eval(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
            Vargmax___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("src/rtl/argmax.sv", 3, "", "Input combinational region did not converge after 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
    } while (Vargmax___024root___eval_phase__ico(vlSelf));
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vargmax___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("src/rtl/argmax.sv", 3, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vargmax___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("src/rtl/argmax.sv", 3, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vargmax___024root___eval_phase__act(vlSelf));
    } while (Vargmax___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vargmax___024root___eval_debug_assertions(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_debug_assertions\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
    if (VL_UNLIKELY(((vlSelfRef.lambda_in & 0xc000U)))) {
        Verilated::overWidthError("lambda_in");
    }
    if (VL_UNLIKELY(((vlSelfRef.angle_in & 0xf800U)))) {
        Verilated::overWidthError("angle_in");
    }
}
#endif  // VL_DEBUG
