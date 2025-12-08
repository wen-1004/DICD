// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vargmax.h for the primary calling header

#include "Vargmax__pch.h"

VL_ATTR_COLD void Vargmax___024root___eval_static(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_static\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vargmax___024root___eval_initial(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_initial\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vargmax___024root___eval_final(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_final\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vargmax___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vargmax___024root___eval_phase__stl(Vargmax___024root* vlSelf);

VL_ATTR_COLD void Vargmax___024root___eval_settle(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_settle\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vargmax___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("src/rtl/argmax.sv", 3, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vargmax___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vargmax___024root___eval_triggers__stl(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_triggers__stl\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vargmax___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vargmax___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vargmax___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vargmax___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vargmax___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vargmax___024root___stl_sequent__TOP__0(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___stl_sequent__TOP__0\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ argmax__DOT____VdfgRegularize_hbc8f6d79_0_1;
    argmax__DOT____VdfgRegularize_hbc8f6d79_0_1 = 0;
    // Body
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

VL_ATTR_COLD void Vargmax___024root___eval_stl(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_stl\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vargmax___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vargmax___024root___eval_phase__stl(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___eval_phase__stl\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vargmax___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vargmax___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vargmax___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vargmax___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vargmax___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vargmax___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vargmax___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vargmax___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vargmax___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vargmax___024root___ctor_var_reset(Vargmax___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vargmax___024root___ctor_var_reset\n"); );
    Vargmax__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->lambda_in = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 6304432764218534182ull);
    vlSelf->angle_in = VL_SCOPED_RAND_RESET_I(11, __VscopeHash, 1129794622422662970ull);
    vlSelf->theta_out = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11659937094643477204ull);
    vlSelf->eps_out = VL_SCOPED_RAND_RESET_I(21, __VscopeHash, 10917202973932627380ull);
    vlSelf->argmax__DOT__current_max = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 4620580109264717935ull);
    vlSelf->argmax__DOT__current_max_next = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 5884283130721359918ull);
    vlSelf->argmax__DOT__current_max_idx_s = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 16048402345271611342ull);
    vlSelf->argmax__DOT__current_ang = VL_SCOPED_RAND_RESET_I(11, __VscopeHash, 16747127040849853167ull);
    vlSelf->argmax__DOT__current_ang_next = VL_SCOPED_RAND_RESET_I(11, __VscopeHash, 4421931343332108524ull);
    vlSelf->argmax__DOT__count = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 15598061573752102472ull);
    vlSelf->argmax__DOT__count_next = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 2242154558144281864ull);
    vlSelf->argmax__DOT__theta_out_r = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8863695713303513758ull);
    vlSelf->argmax__DOT__eps_out_r = VL_SCOPED_RAND_RESET_I(21, __VscopeHash, 9224480055328905379ull);
    vlSelf->argmax__DOT__theta_idx_for_out = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 7523948722543962981ull);
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
