// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdelay_n.h for the primary calling header

#include "Vdelay_n__pch.h"

VL_ATTR_COLD void Vdelay_n___024root___eval_static(Vdelay_n___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___eval_static\n"); );
    Vdelay_n__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vdelay_n___024root___eval_initial(Vdelay_n___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___eval_initial\n"); );
    Vdelay_n__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vdelay_n___024root___eval_final(Vdelay_n___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___eval_final\n"); );
    Vdelay_n__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vdelay_n___024root___eval_settle(Vdelay_n___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___eval_settle\n"); );
    Vdelay_n__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vdelay_n___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdelay_n___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vdelay_n___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vdelay_n___024root___ctor_var_reset(Vdelay_n___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelay_n___024root___ctor_var_reset\n"); );
    Vdelay_n__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->r_in_real = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 9127817291261897851ull);
    vlSelf->r_in_imag = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 3125532235121349261ull);
    vlSelf->r_d1_real = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 12593639855704045921ull);
    vlSelf->r_d1_imag = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 6238968988027738995ull);
    vlSelf->r_dN_out_real = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 14496374759618506979ull);
    vlSelf->r_dN_out_imag = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 9954184879920117851ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->delay_n__DOT__delay_line_real[__Vi0] = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 18146820613692359587ull);
    }
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->delay_n__DOT__delay_line_imag[__Vi0] = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 7538797663599501972ull);
    }
    vlSelf->delay_n__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15690432408864663203ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
