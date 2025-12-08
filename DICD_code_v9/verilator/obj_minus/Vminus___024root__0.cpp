// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vminus.h for the primary calling header

#include "Vminus__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vminus___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vminus___024root___eval_triggers__ico(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_triggers__ico\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
    vlSelfRef.__VicoFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vminus___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
}

bool Vminus___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___trigger_anySet__ico\n"); );
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

void Vminus___024root___ico_sequent__TOP__0(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___ico_sequent__TOP__0\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.lambda_out = (0x0000ffffU & ((IData)(vlSelfRef.mag_in) 
                                           - (0x00ffffffU 
                                              & VL_SHIFTRS_III(24,24,32, 
                                                               (0x00ffffffU 
                                                                & VL_MULS_III(24, 
                                                                              (0x00ffffffU 
                                                                               & VL_EXTENDS_II(24,8, (IData)(vlSelfRef.rho_in))), 
                                                                              (0x00ffffffU 
                                                                               & VL_EXTENDS_II(24,16, (IData)(vlSelfRef.phi_in))))), 7U))));
}

void Vminus___024root___eval_ico(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_ico\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vminus___024root___ico_sequent__TOP__0(vlSelf);
    }
}

bool Vminus___024root___eval_phase__ico(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_phase__ico\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vminus___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = Vminus___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vminus___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vminus___024root___eval(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vminus___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("src/rtl/minus.sv", 18, "", "Input combinational region did not converge after 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
    } while (Vminus___024root___eval_phase__ico(vlSelf));
}

#ifdef VL_DEBUG
void Vminus___024root___eval_debug_assertions(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_debug_assertions\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
