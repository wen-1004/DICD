// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgamma_sum.h for the primary calling header

#include "Vgamma_sum__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vgamma_sum___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vgamma_sum___024root___eval_triggers__act(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval_triggers__act\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.clk) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vgamma_sum___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vgamma_sum___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___trigger_anySet__act\n"); );
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

void Vgamma_sum___024root___nba_sequent__TOP__0(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___nba_sequent__TOP__0\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VdlySet__gamma_sum__DOT__delay_line_real__v0;
    __VdlySet__gamma_sum__DOT__delay_line_real__v0 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v16;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v16 = 0;
    CData/*0:0*/ __VdlySet__gamma_sum__DOT__delay_line_real__v16;
    __VdlySet__gamma_sum__DOT__delay_line_real__v16 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v17;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v17 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v18;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v18 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v19;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v19 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v20;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v20 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v21;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v21 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v22;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v22 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v23;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v23 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v24;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v24 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v25;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v25 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v26;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v26 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v27;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v27 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v28;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v28 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v29;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v29 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v30;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v30 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_real__v31;
    __VdlyVal__gamma_sum__DOT__delay_line_real__v31 = 0;
    CData/*0:0*/ __VdlySet__gamma_sum__DOT__delay_line_imag__v0;
    __VdlySet__gamma_sum__DOT__delay_line_imag__v0 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v16;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v16 = 0;
    CData/*0:0*/ __VdlySet__gamma_sum__DOT__delay_line_imag__v16;
    __VdlySet__gamma_sum__DOT__delay_line_imag__v16 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v17;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v17 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v18;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v18 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v19;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v19 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v20;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v20 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v21;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v21 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v22;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v22 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v23;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v23 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v24;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v24 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v25;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v25 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v26;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v26 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v27;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v27 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v28;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v28 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v29;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v29 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v30;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v30 = 0;
    SData/*13:0*/ __VdlyVal__gamma_sum__DOT__delay_line_imag__v31;
    __VdlyVal__gamma_sum__DOT__delay_line_imag__v31 = 0;
    // Body
    __VdlySet__gamma_sum__DOT__delay_line_real__v0 = 0U;
    __VdlySet__gamma_sum__DOT__delay_line_real__v16 = 0U;
    __VdlySet__gamma_sum__DOT__delay_line_imag__v0 = 0U;
    __VdlySet__gamma_sum__DOT__delay_line_imag__v16 = 0U;
    if (vlSelfRef.rst) {
        __VdlySet__gamma_sum__DOT__delay_line_real__v0 = 1U;
        __VdlySet__gamma_sum__DOT__delay_line_imag__v0 = 1U;
        vlSelfRef.gamma_out_real = 0U;
        vlSelfRef.gamma_out_imag = 0U;
        vlSelfRef.gamma_sum__DOT__current_sum_real = 0U;
        vlSelfRef.gamma_sum__DOT__current_sum_imag = 0U;
        vlSelfRef.gamma_sum__DOT__product_real_s2 = 0U;
        vlSelfRef.gamma_sum__DOT__product_imag_s2 = 0U;
        vlSelfRef.gamma_sum__DOT__ac_mul12_s1 = 0U;
        vlSelfRef.gamma_sum__DOT__bd_mul12_s1 = 0U;
        vlSelfRef.gamma_sum__DOT__bc_mul12_s1 = 0U;
        vlSelfRef.gamma_sum__DOT__ad_mul12_s1 = 0U;
    } else {
        __VdlyVal__gamma_sum__DOT__delay_line_real__v16 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [0x0eU];
        __VdlySet__gamma_sum__DOT__delay_line_real__v16 = 1U;
        __VdlyVal__gamma_sum__DOT__delay_line_real__v17 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [0x0dU];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v18 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [0x0cU];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v19 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [0x0bU];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v20 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [0x0aU];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v21 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [9U];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v22 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [8U];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v23 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [7U];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v24 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [6U];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v25 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [5U];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v26 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [4U];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v27 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [3U];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v28 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [2U];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v29 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [1U];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v30 
            = vlSelfRef.gamma_sum__DOT__delay_line_real
            [0U];
        __VdlyVal__gamma_sum__DOT__delay_line_real__v31 
            = vlSelfRef.gamma_sum__DOT__product_real_s2;
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v16 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [0x0eU];
        __VdlySet__gamma_sum__DOT__delay_line_imag__v16 = 1U;
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v17 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [0x0dU];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v18 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [0x0cU];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v19 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [0x0bU];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v20 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [0x0aU];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v21 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [9U];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v22 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [8U];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v23 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [7U];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v24 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [6U];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v25 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [5U];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v26 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [4U];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v27 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [3U];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v28 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [2U];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v29 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [1U];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v30 
            = vlSelfRef.gamma_sum__DOT__delay_line_imag
            [0U];
        __VdlyVal__gamma_sum__DOT__delay_line_imag__v31 
            = vlSelfRef.gamma_sum__DOT__product_imag_s2;
        vlSelfRef.gamma_out_real = vlSelfRef.gamma_sum__DOT__new_sum_real_w;
        vlSelfRef.gamma_out_imag = vlSelfRef.gamma_sum__DOT__new_sum_imag_w;
        vlSelfRef.gamma_sum__DOT__current_sum_real 
            = vlSelfRef.gamma_sum__DOT__new_sum_real_w;
        vlSelfRef.gamma_sum__DOT__current_sum_imag 
            = vlSelfRef.gamma_sum__DOT__new_sum_imag_w;
        vlSelfRef.gamma_sum__DOT__product_real_s2 = 
            (0x00003fffU & VL_SHIFTRS_III(15,15,32, 
                                          (0x00007fffU 
                                           & (VL_EXTENDS_II(15,14, (IData)(vlSelfRef.gamma_sum__DOT__ac_mul12_s1)) 
                                              + VL_EXTENDS_II(15,14, (IData)(vlSelfRef.gamma_sum__DOT__bd_mul12_s1)))), 4U));
        vlSelfRef.gamma_sum__DOT__product_imag_s2 = 
            (0x00003fffU & VL_SHIFTRS_III(15,15,32, 
                                          (0x00007fffU 
                                           & (VL_EXTENDS_II(15,14, (IData)(vlSelfRef.gamma_sum__DOT__bc_mul12_s1)) 
                                              - VL_EXTENDS_II(15,14, (IData)(vlSelfRef.gamma_sum__DOT__ad_mul12_s1)))), 4U));
        vlSelfRef.gamma_sum__DOT__ac_mul12_s1 = (0x00003fffU 
                                                 & VL_MULS_III(14, 
                                                               (0x00003fffU 
                                                                & VL_EXTENDS_II(14,7, (IData)(vlSelfRef.r_k_in_real))), 
                                                               (0x00003fffU 
                                                                & VL_EXTENDS_II(14,7, (IData)(vlSelfRef.r_k_minus_N_in_real)))));
        vlSelfRef.gamma_sum__DOT__bd_mul12_s1 = (0x00003fffU 
                                                 & VL_MULS_III(14, 
                                                               (0x00003fffU 
                                                                & VL_EXTENDS_II(14,7, (IData)(vlSelfRef.r_k_in_imag))), 
                                                               (0x00003fffU 
                                                                & VL_EXTENDS_II(14,7, (IData)(vlSelfRef.r_k_minus_N_in_imag)))));
        vlSelfRef.gamma_sum__DOT__bc_mul12_s1 = (0x00003fffU 
                                                 & VL_MULS_III(14, 
                                                               (0x00003fffU 
                                                                & VL_EXTENDS_II(14,7, (IData)(vlSelfRef.r_k_in_imag))), 
                                                               (0x00003fffU 
                                                                & VL_EXTENDS_II(14,7, (IData)(vlSelfRef.r_k_minus_N_in_real)))));
        vlSelfRef.gamma_sum__DOT__ad_mul12_s1 = (0x00003fffU 
                                                 & VL_MULS_III(14, 
                                                               (0x00003fffU 
                                                                & VL_EXTENDS_II(14,7, (IData)(vlSelfRef.r_k_in_real))), 
                                                               (0x00003fffU 
                                                                & VL_EXTENDS_II(14,7, (IData)(vlSelfRef.r_k_minus_N_in_imag)))));
    }
    if (__VdlySet__gamma_sum__DOT__delay_line_real__v0) {
        vlSelfRef.gamma_sum__DOT__delay_line_real[0U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[1U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[2U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[3U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[4U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[5U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[6U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[7U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[8U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[9U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[0x0aU] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[0x0bU] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[0x0cU] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[0x0dU] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[0x0eU] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_real[0x0fU] = 0U;
    }
    if (__VdlySet__gamma_sum__DOT__delay_line_real__v16) {
        vlSelfRef.gamma_sum__DOT__delay_line_real[0x0fU] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v16;
        vlSelfRef.gamma_sum__DOT__delay_line_real[0x0eU] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v17;
        vlSelfRef.gamma_sum__DOT__delay_line_real[0x0dU] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v18;
        vlSelfRef.gamma_sum__DOT__delay_line_real[0x0cU] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v19;
        vlSelfRef.gamma_sum__DOT__delay_line_real[0x0bU] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v20;
        vlSelfRef.gamma_sum__DOT__delay_line_real[0x0aU] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v21;
        vlSelfRef.gamma_sum__DOT__delay_line_real[9U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v22;
        vlSelfRef.gamma_sum__DOT__delay_line_real[8U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v23;
        vlSelfRef.gamma_sum__DOT__delay_line_real[7U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v24;
        vlSelfRef.gamma_sum__DOT__delay_line_real[6U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v25;
        vlSelfRef.gamma_sum__DOT__delay_line_real[5U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v26;
        vlSelfRef.gamma_sum__DOT__delay_line_real[4U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v27;
        vlSelfRef.gamma_sum__DOT__delay_line_real[3U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v28;
        vlSelfRef.gamma_sum__DOT__delay_line_real[2U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v29;
        vlSelfRef.gamma_sum__DOT__delay_line_real[1U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v30;
        vlSelfRef.gamma_sum__DOT__delay_line_real[0U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_real__v31;
    }
    if (__VdlySet__gamma_sum__DOT__delay_line_imag__v0) {
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[1U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[2U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[3U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[4U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[5U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[6U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[7U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[8U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[9U] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0x0aU] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0x0bU] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0x0cU] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0x0dU] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0x0eU] = 0U;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0x0fU] = 0U;
    }
    if (__VdlySet__gamma_sum__DOT__delay_line_imag__v16) {
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0x0fU] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v16;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0x0eU] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v17;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0x0dU] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v18;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0x0cU] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v19;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0x0bU] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v20;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0x0aU] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v21;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[9U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v22;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[8U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v23;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[7U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v24;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[6U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v25;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[5U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v26;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[4U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v27;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[3U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v28;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[2U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v29;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[1U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v30;
        vlSelfRef.gamma_sum__DOT__delay_line_imag[0U] 
            = __VdlyVal__gamma_sum__DOT__delay_line_imag__v31;
    }
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

void Vgamma_sum___024root___eval_nba(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval_nba\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vgamma_sum___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vgamma_sum___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vgamma_sum___024root___eval_phase__act(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval_phase__act\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vgamma_sum___024root___eval_triggers__act(vlSelf);
    Vgamma_sum___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vgamma_sum___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vgamma_sum___024root___eval_phase__nba(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval_phase__nba\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vgamma_sum___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vgamma_sum___024root___eval_nba(vlSelf);
        Vgamma_sum___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vgamma_sum___024root___eval(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vgamma_sum___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("src/rtl/gamma_sum.sv", 3, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vgamma_sum___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("src/rtl/gamma_sum.sv", 3, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vgamma_sum___024root___eval_phase__act(vlSelf));
    } while (Vgamma_sum___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vgamma_sum___024root___eval_debug_assertions(Vgamma_sum___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgamma_sum___024root___eval_debug_assertions\n"); );
    Vgamma_sum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
    if (VL_UNLIKELY(((vlSelfRef.r_k_in_real & 0x80U)))) {
        Verilated::overWidthError("r_k_in_real");
    }
    if (VL_UNLIKELY(((vlSelfRef.r_k_in_imag & 0x80U)))) {
        Verilated::overWidthError("r_k_in_imag");
    }
    if (VL_UNLIKELY(((vlSelfRef.r_k_minus_N_in_real 
                      & 0x80U)))) {
        Verilated::overWidthError("r_k_minus_N_in_real");
    }
    if (VL_UNLIKELY(((vlSelfRef.r_k_minus_N_in_imag 
                      & 0x80U)))) {
        Verilated::overWidthError("r_k_minus_N_in_imag");
    }
}
#endif  // VL_DEBUG
