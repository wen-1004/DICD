#pragma once

#include <systemc>
#include "../../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_phi_sum/Vphi_sum.h"
#include <bitset>

using namespace sc_core;
using namespace sc_dt;

// SystemC wrapper around Verilated Vphi_sum (clocked version)
SC_MODULE(phi_sum_rtl_wrap) {
    // Match the RTL/SystemC phi_sum interface
    sc_in<bool>   clk;
    sc_in<bool>   rst;  // follow your RTL reset polarity

    sc_in<r_t>    r_k_in_real;
    sc_in<r_t>    r_k_in_imag;
    sc_in<r_t>    r_k_minus_N_in_real;
    sc_in<r_t>    r_k_minus_N_in_imag;

    sc_in<rho_t>  rho_in;

    sc_out<phi_t> phi_out;

    Vphi_sum* core;

    void eval_proc() {
        // Q formats aligned with your current typedefs:
        // r_t   : 7-bit  signed, Q1.6
        // rho_t : 8-bit  signed, Q1.7
        // phi_t : 14-bit unsigned, Q6.8
        const int R_FRAC   = 6;
        const int RHO_FRAC = 7;
        const int PHI_FRAC = 8;

        // Drive clock/reset first
        core->clk = clk.read();
        core->rst = rst.read();

        // Encode fixed-point -> raw ints
        sc_int<7>  rk_re_raw   = (sc_int<7> )(r_k_in_real.read()        * (1 << R_FRAC));
        sc_int<7>  rk_im_raw   = (sc_int<7> )(r_k_in_imag.read()        * (1 << R_FRAC));
        sc_int<7>  rkmN_re_raw = (sc_int<7> )(r_k_minus_N_in_real.read()* (1 << R_FRAC));
        sc_int<7>  rkmN_im_raw = (sc_int<7> )(r_k_minus_N_in_imag.read()* (1 << R_FRAC));
        sc_int<8>  rho_raw     = (sc_int<8> )(rho_in.read()             * (1 << RHO_FRAC));

        // Drive Verilated ports (bit-accurate masking)
        core->r_k_in_real         = (uint32_t)(rk_re_raw   & 0x7F);
        core->r_k_in_imag         = (uint32_t)(rk_im_raw   & 0x7F);
        core->r_k_minus_N_in_real = (uint32_t)(rkmN_re_raw & 0x7F);
        core->r_k_minus_N_in_imag = (uint32_t)(rkmN_im_raw & 0x7F);
        core->rho_in              = (uint32_t)(rho_raw     & 0xFF);

        // Evaluate DUT
        core->eval();

        if (clk.event() && clk.read() == true) {
            // Read phi_out (14-bit unsigned)
            uint32_t raw_u = core->phi_out & 0x3FFFu;
            uint32_t int_part  = raw_u >> 8;          // upper 6 bits (plus any growth if used)
            uint32_t frac_part = raw_u & 0xFFu;       // lower 8 bits
            
//             std::cout << "phi_out = "
//           << int_part << " + " << frac_part << "/256"
//           << "  raw=" << raw_u
//           << std::endl;

            // Convert back to SystemC phi_t (Q6.8)
            // phi_t is unsigned in your package, so no sign extension.
            phi_t val = phi_t((double)raw_u / (double)(1 << PHI_FRAC));
            phi_out.write(val);
        }
    }

    SC_CTOR(phi_sum_rtl_wrap) {
        core = new Vphi_sum("rtl_phi_sum");

        // For clocked logic, evaluate on any clock/reset/input change.
        SC_METHOD(eval_proc);
        sensitive << clk << rst
                  << r_k_in_real << r_k_in_imag
                  << r_k_minus_N_in_real << r_k_minus_N_in_imag
                  << rho_in;
        dont_initialize();
    }

    ~phi_sum_rtl_wrap() {
        delete core;
    }
};


