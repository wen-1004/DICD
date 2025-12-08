// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vphi_sum.h for the primary calling header

#include "Vphi_sum__pch.h"

VL_ATTR_COLD void Vphi_sum___024root___eval_static(Vphi_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vphi_sum___024root___eval_static\n"); );
    Vphi_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vphi_sum___024root___eval_initial(Vphi_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vphi_sum___024root___eval_initial\n"); );
    Vphi_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vphi_sum___024root___eval_final(Vphi_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vphi_sum___024root___eval_final\n"); );
    Vphi_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vphi_sum___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vphi_sum___024root___eval_phase__stl(Vphi_sum___024root* vlSelf);

VL_ATTR_COLD void Vphi_sum___024root___eval_settle(Vphi_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vphi_sum___024root___eval_settle\n"); );
    Vphi_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vphi_sum___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("src/rtl/phi_sum.sv", 3, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vphi_sum___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vphi_sum___024root___eval_triggers__stl(Vphi_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vphi_sum___024root___eval_triggers__stl\n"); );
    Vphi_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vphi_sum___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vphi_sum___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vphi_sum___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vphi_sum___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vphi_sum___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vphi_sum___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vphi_sum___024root___trigger_anySet__stl\n"); );
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

void Vphi_sum___024root___ico_sequent__TOP__0(Vphi_sum___024root* vlSelf);

VL_ATTR_COLD void Vphi_sum___024root___eval_stl(Vphi_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vphi_sum___024root___eval_stl\n"); );
    Vphi_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vphi_sum___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vphi_sum___024root___eval_phase__stl(Vphi_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vphi_sum___024root___eval_phase__stl\n"); );
    Vphi_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vphi_sum___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vphi_sum___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vphi_sum___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vphi_sum___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vphi_sum___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vphi_sum___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vphi_sum___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vphi_sum___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vphi_sum___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vphi_sum___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vphi_sum___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vphi_sum___024root___ctor_var_reset(Vphi_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vphi_sum___024root___ctor_var_reset\n"); );
    Vphi_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->r_k_in_real = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 1012348690585150053ull);
    vlSelf->r_k_in_imag = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 11713670859878628183ull);
    vlSelf->r_k_minus_N_in_real = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 2641590558406439550ull);
    vlSelf->r_k_minus_N_in_imag = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 4931015844333247018ull);
    vlSelf->rho_in = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15788846033398348421ull);
    vlSelf->phi_out = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 14075908954498940211ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->phi_sum__DOT__delay_line[__Vi0] = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 1374591665698529325ull);
    }
    vlSelf->phi_sum__DOT__current_sum = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 8094798813934030038ull);
    vlSelf->phi_sum__DOT__current_sum_next = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 13292209285273006456ull);
    vlSelf->phi_sum__DOT__phi_out_reg = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 11202248020478455431ull);
    vlSelf->phi_sum__DOT__phi_out_reg_next = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 14828284100052337179ull);
    vlSelf->phi_sum__DOT__energy_to_sum = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 14265581421976953494ull);
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
