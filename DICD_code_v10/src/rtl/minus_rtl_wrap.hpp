#pragma once

#include <systemc>
#include "../../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_minus/Vminus.h"

using namespace sc_core;
using namespace sc_dt;

// SystemC wrapper around plain Verilated Vminus
SC_MODULE(minus_rtl_wrap) {
    // Match original SystemC minus interface
    sc_in<mag_t>     mag_in;      // |γ(k)|
    sc_in<phi_t>     phi_in;      // Φ_L(k)
    sc_in<rho_t>     rho_in;      // ρ
    sc_out<lambda_t> lambda_out;  // Λ(k)

    Vminus* core;  // Verilated DUT

    void eval_proc() {
        // Q formats from your sv typedefs:
        // mag_t, phi_t, lambda_t : signed [15:0] ≈ Q6.10
        // rho_t                  : signed [7:0]  ≈ Q1.7

        const int F_MAG = 10;
        const int F_PHI = 10;
        const int F_RHO = 7;

        // Encode fixed-point → RTL ints
        sc_int<16> mag_raw = (sc_int<16>)(mag_in.read() * (1 << F_MAG));
        sc_int<16> phi_raw = (sc_int<16>)(phi_in.read() * (1 << F_PHI));
        sc_int<8>  rho_raw = (sc_int<8> )(rho_in.read() * (1 << F_RHO));

        // Drive Verilated ports (they are plain ints / CData/SData)
        core->mag_in = (uint32_t)(mag_raw & 0xFFFF);
        core->phi_in = (uint32_t)(phi_raw & 0xFFFF);
        core->rho_in = (uint32_t)(rho_raw & 0xFF);

        // Evaluate combinational logic
        core->eval_step();   // eval_step is the public entry in recent Verilator

        // Read result, sign-extend from 16 bits, convert back to lambda_t
        uint32_t raw_u = core->lambda_out & 0xFFFFu;
        int32_t  raw_s = (raw_u & 0x8000u)
                       ? (int32_t)(raw_u | ~0xFFFFu)   // sign-extend
                       : (int32_t)raw_u;

        lambda_t val = lambda_t((double)raw_s / (double)(1 << F_MAG));
        lambda_out.write(val);
    }

    SC_CTOR(minus_rtl_wrap) {
        // Create Verilated model (name optional)
        core = new Vminus("rtl_minus");

        // Pure combinational wrapper: trigger on any input change
        SC_METHOD(eval_proc);
        sensitive << mag_in << phi_in << rho_in;
        dont_initialize();
    }

    ~minus_rtl_wrap() {
        delete core;
    }
};
