// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vminus.h for the primary calling header

#include "Vminus__pch.h"

VL_ATTR_COLD void Vminus___024root___eval_static(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_static\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vminus___024root___eval_initial(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_initial\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vminus___024root___eval_final(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_final\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vminus___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vminus___024root___eval_phase__stl(Vminus___024root* vlSelf);

VL_ATTR_COLD void Vminus___024root___eval_settle(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_settle\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vminus___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("src/rtl/minus.sv", 18, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vminus___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vminus___024root___eval_triggers__stl(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_triggers__stl\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vminus___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vminus___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vminus___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vminus___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vminus___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___trigger_anySet__stl\n"); );
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

void Vminus___024root___ico_sequent__TOP__0(Vminus___024root* vlSelf);

VL_ATTR_COLD void Vminus___024root___eval_stl(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_stl\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vminus___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vminus___024root___eval_phase__stl(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_phase__stl\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vminus___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vminus___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vminus___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vminus___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vminus___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vminus___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vminus___024root___ctor_var_reset(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___ctor_var_reset\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->mag_in = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1167741162239610098ull);
    vlSelf->phi_in = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14297889747923002183ull);
    vlSelf->rho_in = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15788846033398348421ull);
    vlSelf->lambda_out = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13234030760567760274ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
}
