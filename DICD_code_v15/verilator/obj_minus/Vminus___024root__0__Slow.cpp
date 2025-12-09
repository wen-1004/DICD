// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vminus.h for the primary calling header

#include "Vminus__pch.h"

VL_ATTR_COLD void Vminus___024root___eval_static(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_static\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
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

VL_ATTR_COLD void Vminus___024root___eval_settle(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___eval_settle\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vminus___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vminus___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vminus___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vminus___024root___ctor_var_reset(Vminus___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vminus___024root___ctor_var_reset\n"); );
    Vminus__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->mag_in = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 1167741162239610098ull);
    vlSelf->phi_in = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 14297889747923002183ull);
    vlSelf->rho_in = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15788846033398348421ull);
    vlSelf->lambda_out = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 13234030760567760274ull);
    vlSelf->minus__DOT__prod_full_s1 = VL_SCOPED_RAND_RESET_I(22, __VscopeHash, 9486512289631667571ull);
    vlSelf->minus__DOT__mag_s1 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 2285500060629461001ull);
    vlSelf->minus__DOT__rho_phi_q6_8_s2 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 685476628172684018ull);
    vlSelf->minus__DOT__mag_s2 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 1554025886309113489ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
