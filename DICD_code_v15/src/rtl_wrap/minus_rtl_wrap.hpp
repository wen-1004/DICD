#pragma once

#include <systemc>
#include "../../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_minus/Vminus.h"

using namespace sc_core;
using namespace sc_dt;

// SystemC wrapper around Verilated Vminus (clocked version)
SC_MODULE(minus_rtl_wrap) {
    // Match the RTL/SystemC minus interface
    sc_in<bool>      clk;
    sc_in<bool>      rst;        // active-low
    sc_in<mag_t>     mag_in;     // Q6.8 signed
    sc_in<phi_t>     phi_in;     // Q6.8 unsigned
    sc_in<rho_t>     rho_in;     // Q1.7 signed
    sc_out<lambda_t> lambda_out; // Q6.8 signed

    Vminus* core;

    void eval_proc() {
        // Q formats aligned with your current typedefs:
        // mag_t, phi_t, lambda_t : 14-bit, Q6.8
        // rho_t                  : 8-bit,  Q1.7
        const int MAG_FRAC = 8;
        const int PHI_FRAC = 8;
        const int RHO_FRAC = 7;

        // Drive clock/reset first
        core->clk = clk.read();
        core->rst = rst.read();

        // Encode fixed-point -> raw ints
        sc_int<14>  mag_raw = (sc_int<14>)(mag_in.read() * (1 << MAG_FRAC));
        sc_uint<14> phi_raw = (sc_uint<14>)(phi_in.read() * (1 << PHI_FRAC));
        sc_int<8>   rho_raw = (sc_int<8> )(rho_in.read() * (1 << RHO_FRAC));

        // Drive Verilated ports (bit-accurate masking)
        core->mag_in = (uint32_t)(mag_raw & 0x3FFF);
        core->phi_in = (uint32_t)(phi_raw & 0x3FFF);
        core->rho_in = (uint32_t)(rho_raw & 0x00FF);

        // Evaluate DUT
        core->eval();

        if (clk.event() && clk.read() == true) {
            // Read lambda_out (14-bit signed)
            uint32_t raw_u = core->lambda_out & 0x3FFFu;

            // Sign extend from 14 bits
            int32_t raw_s = (raw_u & 0x2000u)
                          ? (int32_t)(raw_u | ~0x3FFFu)
                          : (int32_t)raw_u;

            // Convert back to SystemC lambda_t (Q6.8)
            lambda_t val = lambda_t((double)raw_s / (double)(1 << MAG_FRAC));
            lambda_out.write(val);
        }
    }

    SC_CTOR(minus_rtl_wrap) {
        core = new Vminus("rtl_minus");

        // For clocked logic, evaluate on any clock change and reset change.
        // This is the common Verilator+SystemC glue style.
        SC_METHOD(eval_proc);
        sensitive << clk << rst << mag_in << phi_in << rho_in;
        dont_initialize();
    }

    ~minus_rtl_wrap() {
        delete core;
    }
};
