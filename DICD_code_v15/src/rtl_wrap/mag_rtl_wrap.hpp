#pragma once

#include <systemc>
#include "../../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_mag/Vmag.h"
#include <bitset>

using namespace sc_core;
using namespace sc_dt;

// SystemC wrapper around Verilated Vmag (clocked version)
SC_MODULE(mag_rtl_wrap) {
    // Match the RTL/SystemC mag interface
    sc_in<bool>     clk;
    sc_in<bool>     rst;        // follow your RTL reset polarity (ACTIVE-HIGH)

    sc_in<gamma_t>  gm_in_real;
    sc_in<gamma_t>  gm_in_imag;

    sc_out<mag_t>   mag_out;

    Vmag* core;

    void eval_proc() {
        // Q formats aligned with your current typedefs:
        // gamma_t : 14-bit signed, Q6.8
        // mag_t   : 14-bit signed, Q6.8
        const int GAMMA_FRAC = 8;
        const int MAG_FRAC   = 8;

        // Drive clock/reset first
        core->clk = clk.read();
        core->rst = rst.read();

        // Encode fixed-point -> raw ints
        // Use truncation style consistent with your other wrappers
        sc_int<14> gm_re_raw = (sc_int<14>)(gm_in_real.read() * (1 << GAMMA_FRAC));
        sc_int<14> gm_im_raw = (sc_int<14>)(gm_in_imag.read() * (1 << GAMMA_FRAC));

        // Drive Verilated ports (bit-accurate masking)
        core->gm_in_real = (uint32_t)(gm_re_raw & 0x3FFF);
        core->gm_in_imag = (uint32_t)(gm_im_raw & 0x3FFF);

        // Evaluate DUT
        core->eval();

        // Update outputs on posedge
        if (clk.event() && clk.read() == true) {
            // Read mag_out (14-bit signed)
            uint32_t raw_u = core->mag_out & 0x3FFFu;

            // Sign-extend 14-bit to 32-bit
            int32_t raw_s = (raw_u & 0x2000u) ? (int32_t)(raw_u | 0xFFFFC000u)
                                             : (int32_t)(raw_u);

            // Convert back to SystemC mag_t (Q6.8)
            mag_t val = mag_t((double)raw_s / (double)(1 << MAG_FRAC));
            mag_out.write(val);
        }
    }

    SC_CTOR(mag_rtl_wrap) {
        core = new Vmag("rtl_mag");

        // For clocked logic, evaluate on any clock/reset/input change.
        SC_METHOD(eval_proc);
        sensitive << clk << rst << gm_in_real << gm_in_imag;
        dont_initialize();
    }

    ~mag_rtl_wrap() {
        delete core;
    }
};

