// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgamma_sum.h for the primary calling header

#include "Vgamma_sum__pch.h"

VL_ATTR_COLD void Vgamma_sum___024root___eval_static(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval_static\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vgamma_sum___024root___eval_initial(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval_initial\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vgamma_sum___024root___eval_final(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval_final\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vgamma_sum___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vgamma_sum___024root___eval_phase__stl(Vgamma_sum___024root* vlSelf);

VL_ATTR_COLD void Vgamma_sum___024root___eval_settle(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval_settle\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vgamma_sum___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("src/rtl/gamma_sum.sv", 3, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vgamma_sum___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vgamma_sum___024root___eval_triggers__stl(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval_triggers__stl\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vgamma_sum___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vgamma_sum___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vgamma_sum___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vgamma_sum___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vgamma_sum___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vgamma_sum___024root___stl_sequent__TOP__0(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___stl_sequent__TOP__0\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.gamma_sum__DOT__new_sum_real_w = (0x00003fffU 
                                                & (((IData)(vlSelfRef.gamma_sum__DOT__current_sum_real) 
                                                    + (IData)(vlSelfRef.gamma_sum__DOT__product_real_s2)) 
                                                   - 
                                                   vlSelfRef.gamma_sum__DOT__delay_line_real
                                                   [0x0fU]));
    vlSelfRef.gamma_sum__DOT__new_sum_imag_w = (0x00003fffU 
                                                & (((IData)(vlSelfRef.gamma_sum__DOT__current_sum_imag) 
                                                    + (IData)(vlSelfRef.gamma_sum__DOT__product_imag_s2)) 
                                                   - 
                                                   vlSelfRef.gamma_sum__DOT__delay_line_imag
                                                   [0x0fU]));
}

VL_ATTR_COLD void Vgamma_sum___024root___eval_stl(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval_stl\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vgamma_sum___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vgamma_sum___024root___eval_phase__stl(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval_phase__stl\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vgamma_sum___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vgamma_sum___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vgamma_sum___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vgamma_sum___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vgamma_sum___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vgamma_sum___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vgamma_sum___024root___ctor_var_reset(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___ctor_var_reset\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->r_k_in_real = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 1012348690585150053ull);
    vlSelf->r_k_in_imag = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 11713670859878628183ull);
    vlSelf->r_k_minus_N_in_real = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 2641590558406439550ull);
    vlSelf->r_k_minus_N_in_imag = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 4931015844333247018ull);
    vlSelf->gamma_out_real = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 5328084392106176407ull);
    vlSelf->gamma_out_imag = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 5863293007973893795ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->gamma_sum__DOT__delay_line_real[__Vi0] = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 6837242954702528157ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->gamma_sum__DOT__delay_line_imag[__Vi0] = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 7031868919907729308ull);
    }
    vlSelf->gamma_sum__DOT__current_sum_real = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 12731138820437867918ull);
    vlSelf->gamma_sum__DOT__current_sum_imag = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 6800226547470666ull);
    vlSelf->gamma_sum__DOT__ac_mul12_s1 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 17673023502800891455ull);
    vlSelf->gamma_sum__DOT__bd_mul12_s1 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 9064500742401610197ull);
    vlSelf->gamma_sum__DOT__bc_mul12_s1 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 14279794589900486029ull);
    vlSelf->gamma_sum__DOT__ad_mul12_s1 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 9478654614455067299ull);
    vlSelf->gamma_sum__DOT__product_real_s2 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 14196996305206273121ull);
    vlSelf->gamma_sum__DOT__product_imag_s2 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 2926068796695611809ull);
    vlSelf->gamma_sum__DOT__new_sum_real_w = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 2944350571572236172ull);
    vlSelf->gamma_sum__DOT__new_sum_imag_w = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 12906437912949191344ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
