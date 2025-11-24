#pragma once

#include <systemc>
#include "../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_phi_rho/Vphi_rho.h"

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(phi_rho_rtl_wrap) {
    // ==========================================================
    // 1. Ports (Match original SystemC interface)
    // ==========================================================
    sc_in<bool> clk;
    sc_in<bool> rst; // SystemC: Active Low

    // Inputs
    sc_in<phi_t> phi_in;
    sc_in<rho_t> rho_in;

    // Output
    sc_out<phi_t> phi_rho;

    // ==========================================================
    // 2. Verilated Core Pointer
    // ==========================================================
    Vphi_rho* core;

    // ==========================================================
    // 3. Configuration (Fixed Point Precision)
    // ==========================================================
    // phi_t: 16-bit, Q6.10
    static const int F_PHI = 10;
    // rho_t: 8-bit, Q1.7
    static const int F_RHO = 7;

    // ==========================================================
    // 4. Evaluation Logic
    // ==========================================================
    void tick_proc() {
        // --- A. Drive Inputs (SC -> RTL) ---

        // 1. Reset Polarity: SC(Low) -> RTL(High)
        core->rst = !rst.read();

        // 2. Convert Inputs
        // phi_in (Q6.10) -> Integer
        core->phi_in = (uint32_t)(phi_in.read() * (1 << F_PHI));
        
        // rho_in (Q1.7) -> Integer
        core->rho_in = (uint32_t)(rho_in.read() * (1 << F_RHO));

        // --- B. Clock Simulation ---
        
        // Rising Edge (Update Registers)
        core->clk = 1;
        core->eval();

        // Falling Edge
        core->clk = 0;
        core->eval();

        // --- C. Read Output (RTL -> SC) ---
        
        // Lambda: Convert Raw Integer -> Double (Q6.10)
        auto rtl_to_sc = [](uint32_t raw_val) -> phi_t {
            uint32_t masked = raw_val & 0xFFFF;
            // Sign Extension for 16-bit
            int32_t s_val = (masked & 0x8000) 
                            ? (int32_t)(masked | 0xFFFF0000) 
                            : (int32_t)masked;
            
            return phi_t((double)s_val / (double)(1 << F_PHI));
        };

        phi_rho.write(rtl_to_sc(core->phi_rho));
    }

    // ==========================================================
    // 5. Constructor
    // ==========================================================
    SC_CTOR(phi_rho_rtl_wrap) {
        core = new Vphi_rho("rtl_phi_rho_core");

        SC_METHOD(tick_proc);
        sensitive << clk.pos();
        dont_initialize();
    }

    ~phi_rho_rtl_wrap() {
        delete core;
    }
};