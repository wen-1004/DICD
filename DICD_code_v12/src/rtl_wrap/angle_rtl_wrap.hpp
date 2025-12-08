#pragma once

#include <systemc>
#include "../../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_angle/Vangle.h"

using namespace sc_core;
using namespace sc_dt;

// SystemC wrapper around Verilated Vangle (clocked version)
SC_MODULE(angle_rtl_wrap) {
    // -------------------------
    // Local type + Q format 선언
    // -------------------------
    // Keep consistent with your SV package:
    // gamma_t: 14-bit signed, Q6.8  => I=6, FRAC=8
    // ang_t  : 11-bit signed, Q3.8  => I=3, FRAC=8
    static const int GAMMA_W    = 14;
    static const int GAMMA_I    = 6;
    static const int GAMMA_FRAC = GAMMA_W - GAMMA_I; // 8

    static const int ANG_W      = 11;
    static const int ANG_I      = 3;
    static const int ANG_FRAC   = ANG_W - ANG_I;     // 8

    using gamma_t_c = sc_fixed<GAMMA_W, GAMMA_I>;
    using ang_t_c   = sc_fixed<ANG_W,   ANG_I>;

    // -------------------------
    // Ports (match angle interface)
    // -------------------------
    sc_in<bool>     clk;
    sc_in<bool>     rst;          // follow your RTL reset polarity
    sc_in<gamma_t_c> gm_in_real;  // Q6.8 signed
    sc_in<gamma_t_c> gm_in_imag;  // Q6.8 signed
    sc_out<ang_t_c>  ang_out;     // Q3.8 signed

    Vangle* core;

    void eval_proc() {
        // Drive clock/reset first
        core->clk = clk.read();
        core->rst = rst.read();

        // Encode fixed-point -> raw ints
        sc_int<GAMMA_W> gm_r_raw = (sc_int<GAMMA_W>)(gm_in_real.read() * (1 << GAMMA_FRAC));
        sc_int<GAMMA_W> gm_i_raw = (sc_int<GAMMA_W>)(gm_in_imag.read() * (1 << GAMMA_FRAC));

        // Drive Verilated ports (bit-accurate masking)
        core->gm_in_real = (uint32_t)(gm_r_raw & 0x3FFF);
        core->gm_in_imag = (uint32_t)(gm_i_raw & 0x3FFF);

        // Evaluate DUT
        core->eval();

        if (clk.event() && clk.read() == true) {
            // Read ang_out (11-bit signed)
            uint32_t raw_u = core->ang_out & 0x07FFu;

            // Sign extend from 11 bits
            int32_t raw_s = (raw_u & 0x0400u)
                          ? (int32_t)(raw_u | ~0x07FFu)
                          : (int32_t)raw_u;

            // Convert back to SystemC ang_t (Q3.8)
            ang_t_c val = ang_t_c((double)raw_s / (double)(1 << ANG_FRAC));
            ang_out.write(val);
        }
    }

    SC_CTOR(angle_rtl_wrap) {
        core = new Vangle("rtl_angle");

        // For clocked logic, evaluate on any clock change and reset/input change.
        SC_METHOD(eval_proc);
        sensitive << clk << rst << gm_in_real << gm_in_imag;
        dont_initialize();
    }

    ~angle_rtl_wrap() {
        delete core;
    }
};
