#pragma once

#include <systemc>
#include "../../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_delay_n/Vdelay_n.h"

using namespace sc_core;
using namespace sc_dt;

// SystemC wrapper around Verilated Vdelay_n (clocked version)
SC_MODULE(delay_n_rtl_wrap) {
    // Match the RTL/SystemC delay_n interface
    sc_in<bool> clk;
    sc_in<bool> rst;          // follow your RTL reset polarity (ACTIVE-HIGH)

    sc_in<r_t>  r_in_real;    // Q1.6 signed (7-bit)
    sc_in<r_t>  r_in_imag;    // Q1.6 signed (7-bit)

    sc_out<r_t> r_d1_real;
    sc_out<r_t> r_d1_imag;
    sc_out<r_t> r_dN_out_real;
    sc_out<r_t> r_dN_out_imag;

    Vdelay_n* core;

    void eval_proc() {
        // Q formats aligned with your current typedefs:
        // r_t : 7-bit, Q1.6
        const int R_FRAC = 6;

        // Drive clock/reset first
        core->clk = clk.read();
        core->rst = rst.read();

        // Encode fixed-point -> raw ints
        sc_int<7> rre_raw = (sc_int<7>)(r_in_real.read() * (1 << R_FRAC));
        sc_int<7> rim_raw = (sc_int<7>)(r_in_imag.read() * (1 << R_FRAC));

        // Drive Verilated ports (bit-accurate masking)
        core->r_in_real = (uint32_t)(rre_raw & 0x7F);
        core->r_in_imag = (uint32_t)(rim_raw & 0x7F);

        // Evaluate DUT
        core->eval();

        if (clk.event() && clk.read() == true) {
            // ---- Read r_d1_real (7-bit signed) ----
            uint32_t d1r_u = core->r_d1_real & 0x7Fu;
            int32_t  d1r_s = (d1r_u & 0x40u)
                           ? (int32_t)(d1r_u | ~0x7Fu)
                           : (int32_t)d1r_u;
            r_t d1r_val = r_t((double)d1r_s / (double)(1 << R_FRAC));
            r_d1_real.write(d1r_val);

            // ---- Read r_d1_imag (7-bit signed) ----
            uint32_t d1i_u = core->r_d1_imag & 0x7Fu;
            int32_t  d1i_s = (d1i_u & 0x40u)
                           ? (int32_t)(d1i_u | ~0x7Fu)
                           : (int32_t)d1i_u;
            r_t d1i_val = r_t((double)d1i_s / (double)(1 << R_FRAC));
            r_d1_imag.write(d1i_val);

            // ---- Read r_dN_out_real (7-bit signed) ----
            uint32_t dnr_u = core->r_dN_out_real & 0x7Fu;
            int32_t  dnr_s = (dnr_u & 0x40u)
                           ? (int32_t)(dnr_u | ~0x7Fu)
                           : (int32_t)dnr_u;
            r_t dnr_val = r_t((double)dnr_s / (double)(1 << R_FRAC));
            r_dN_out_real.write(dnr_val);

            // ---- Read r_dN_out_imag (7-bit signed) ----
            uint32_t dni_u = core->r_dN_out_imag & 0x7Fu;
            int32_t  dni_s = (dni_u & 0x40u)
                           ? (int32_t)(dni_u | ~0x7Fu)
                           : (int32_t)dni_u;
            r_t dni_val = r_t((double)dni_s / (double)(1 << R_FRAC));
            r_dN_out_imag.write(dni_val);
        }
    }

    SC_CTOR(delay_n_rtl_wrap) {
        core = new Vdelay_n("rtl_delay_n");

        // For clocked logic, evaluate on any clock change and reset change.
        // This is the common Verilator+SystemC glue style.
        SC_METHOD(eval_proc);
        sensitive << clk << rst << r_in_real << r_in_imag;
        dont_initialize();
    }

    ~delay_n_rtl_wrap() {
        delete core;
    }
};

