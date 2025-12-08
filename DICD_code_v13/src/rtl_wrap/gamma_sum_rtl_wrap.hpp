#pragma once

#include <systemc>
#include "../../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_gamma_sum/Vgamma_sum.h"
#include <bitset>

using namespace sc_core;
using namespace sc_dt;

// SystemC wrapper around Verilated Vgamma_sum (clocked version)
SC_MODULE(gamma_sum_rtl_wrap) {
    // Match the RTL/SystemC gamma_sum interface
    sc_in<bool>   clk;
    sc_in<bool>   rst;  // follow your RTL reset polarity (ACTIVE-HIGH)

    sc_in<r_t>    r_k_in_real;
    sc_in<r_t>    r_k_in_imag;
    sc_in<r_t>    r_k_minus_N_in_real;
    sc_in<r_t>    r_k_minus_N_in_imag;

    sc_out<gamma_t> gamma_out_real;
    sc_out<gamma_t> gamma_out_imag;

    Vgamma_sum* core;

    void eval_proc() {
        // Q formats aligned with your current typedefs:
        // r_t     : 7-bit signed, Q1.6
        // gamma_t : 14-bit signed, Q6.8
        const int R_FRAC     = 6;
        const int GAMMA_FRAC = 8;

        // Drive clock/reset first
        core->clk = clk.read();
        core->rst = rst.read();

        // Encode fixed-point -> raw ints
        // Use rounding consistent with simple cast behavior (truncate toward 0).
        sc_int<7> rk_re_raw   = (sc_int<7>)(r_k_in_real.read()         * (1 << R_FRAC));
        sc_int<7> rk_im_raw   = (sc_int<7>)(r_k_in_imag.read()         * (1 << R_FRAC));
        sc_int<7> rkmN_re_raw = (sc_int<7>)(r_k_minus_N_in_real.read() * (1 << R_FRAC));
        sc_int<7> rkmN_im_raw = (sc_int<7>)(r_k_minus_N_in_imag.read() * (1 << R_FRAC));

        // Drive Verilated ports (bit-accurate masking)
        // r_t ports are 7-bit signed in RTL typedefs.
        core->r_k_in_real         = (uint32_t)(rk_re_raw   & 0x7F);
        core->r_k_in_imag         = (uint32_t)(rk_im_raw   & 0x7F);
        core->r_k_minus_N_in_real = (uint32_t)(rkmN_re_raw & 0x7F);
        core->r_k_minus_N_in_imag = (uint32_t)(rkmN_im_raw & 0x7F);

        // Evaluate DUT
        core->eval();

        // Update outputs on posedge, like your phi wrapper
        if (clk.event() && clk.read() == true) {
            // Read gamma_out_real/imag (14-bit signed)
            uint32_t raw_r_u = core->gamma_out_real & 0x3FFFu;
            uint32_t raw_i_u = core->gamma_out_imag & 0x3FFFu;

            // Sign-extend 14-bit to 32-bit
            int32_t raw_r_s = (raw_r_u & 0x2000u) ? (int32_t)(raw_r_u | 0xFFFFC000u)
                                                 : (int32_t)(raw_r_u);
            int32_t raw_i_s = (raw_i_u & 0x2000u) ? (int32_t)(raw_i_u | 0xFFFFC000u)
                                                 : (int32_t)(raw_i_u);

            // Convert back to SystemC gamma_t (Q6.8)
            gamma_t val_r = gamma_t((double)raw_r_s / (double)(1 << GAMMA_FRAC));
            gamma_t val_i = gamma_t((double)raw_i_s / (double)(1 << GAMMA_FRAC));

            gamma_out_real.write(val_r);
            gamma_out_imag.write(val_i);
        }
    }

    SC_CTOR(gamma_sum_rtl_wrap) {
        core = new Vgamma_sum("rtl_gamma_sum");

        // For clocked logic, evaluate on any clock/reset/input change.
        SC_METHOD(eval_proc);
        sensitive << clk << rst
                  << r_k_in_real << r_k_in_imag
                  << r_k_minus_N_in_real << r_k_minus_N_in_imag;
        dont_initialize();
    }

    ~gamma_sum_rtl_wrap() {
        delete core;
    }
};

