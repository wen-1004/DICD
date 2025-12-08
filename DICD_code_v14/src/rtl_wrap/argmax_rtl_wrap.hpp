#pragma once

#include <systemc>
#include "../../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_argmax/Vargmax.h"

using namespace sc_core;
using namespace sc_dt;

// SystemC wrapper around Verilated Vargmax (clocked version)
SC_MODULE(argmax_rtl_wrap) {
    // Match the RTL/SystemC argmax interface
    sc_in<bool>      clk;
    sc_in<bool>      rst;         // follow your RTL reset polarity
    sc_in<lambda_t>  lambda_in;   // Q6.8 signed (14-bit)
    sc_in<ang_t>     angle_in;    // Q3.8 signed (11-bit)
    sc_out<theta_t>  theta_out;   // 8-bit unsigned index
    sc_out<eps_t>    eps_out;     // Q1.20 signed (21-bit)

    Vargmax* core;

    void eval_proc() {
        // Q formats aligned with your current typedefs:
        // lambda_t : 14-bit, Q6.8  => FRAC=8
        // ang_t    : 11-bit, Q3.8  => FRAC=8
        // eps_t    : 21-bit, Q1.20 => FRAC=20
        const int LAMBDA_FRAC = 8;
        const int ANG_FRAC    = 8;
        const int EPS_FRAC    = 20;

        // Drive clock/reset first (same style as minus wrapper)
        core->clk = clk.read();
        core->rst = rst.read();

        // Encode fixed-point -> raw ints
        sc_int<14> lambda_raw = (sc_int<14>)(lambda_in.read() * (1 << LAMBDA_FRAC));
        sc_int<11> angle_raw  = (sc_int<11>)(angle_in.read()  * (1 << ANG_FRAC));

        // Drive Verilated ports (bit-accurate masking)
        core->lambda_in = (uint32_t)(lambda_raw & 0x3FFF);
        core->angle_in  = (uint32_t)(angle_raw  & 0x07FF);

        // Evaluate DUT
        core->eval();

        // ---- Read theta_out (8-bit) ----
        if (clk.event() && clk.read() == true) {
            uint32_t th_u = core->theta_out & 0xFFu;
            theta_out.write(theta_t(th_u));

            // ---- Read eps_out (21-bit signed) ----
            uint32_t eps_u = core->eps_out & 0x1FFFFFu;

            // Sign extend from 21 bits
            int32_t eps_s = (eps_u & 0x100000u)
                          ? (int32_t)(eps_u | ~0x1FFFFFu)
                          : (int32_t)eps_u;

            // Convert back to SystemC eps_t (Q1.20)
            eps_t eps_val = eps_t((double)eps_s / (double)(1 << EPS_FRAC));
            eps_out.write(eps_val);
        }
    }

    SC_CTOR(argmax_rtl_wrap) {
        core = new Vargmax("rtl_argmax");

        // For clocked logic, evaluate on any clock/reset/input change
        SC_METHOD(eval_proc);
        sensitive << clk << rst << lambda_in << angle_in;
        dont_initialize();
    }

    ~argmax_rtl_wrap() {
        delete core;
    }
};
