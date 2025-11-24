#pragma once

#include <systemc>
#include "../include/data_type.hpp" // 包含 r_t, rho_t, etc.
#include "verilated.h"
#include "../../verilator/obj_top/Vtop.h" // Verilator 編譯 top.sv 產生的 header

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(top_rtl_wrap) {
    // ==========================================================
    // 1. Ports (Match top.sv Interface)
    // ==========================================================
    sc_in<bool> clk;
    sc_in<bool> rst;       // SystemC: Active Low
    sc_in<bool> in_valid;

    // Inputs
    // top.sv: input signed [15:0] rx_re_in (Q1.15)
    sc_in<r_t> rx_re_in; 
    sc_in<r_t> rx_img_in;
    
    // top.sv: input [7:0] rho (Q1.7)
    sc_in<rho_t> rho;

    // Outputs
    // top.sv: output [7:0] theta (Integer)
    sc_out<theta_t> theta;
    
    // top.sv: output [20:0] epsilon (Q2.19)
    sc_out<eps_t> epsilon;
    
    // top.sv: output out_valid
    sc_out<bool> out_valid;

    // ==========================================================
    // 2. Verilated Core Pointer
    // ==========================================================
    Vtop* core;

    // ==========================================================
    // 3. Configuration (Fixed Point Precision)
    // ==========================================================
    // 根據 top.sv parameter: FRAC_BITS = 15
    static const int F_IN = 15; 
    
    // 根據 top.sv parameter: RHO_FRAC_BITS = 7
    static const int F_RHO = 7;

    // 根據 select_eps 模組推導: Q2.19
    static const int F_EPS = 19;

    // ==========================================================
    // 4. Evaluation Logic
    // ==========================================================
    void tick_proc() {
        // --- A. Drive Inputs (SC -> RTL) ---

        // 1. Reset: SC(Low) -> RTL(High)
        core->rst = !rst.read();
        core->in_valid = in_valid.read();

        // 2. Data Conversion (Double -> Raw Integer)
        core->rx_re_in = (uint32_t)(rx_re_in.read() * (1 << F_IN));
        core->rx_img_in = (uint32_t)(rx_img_in.read() * (1 << F_IN));
        core->rho = (uint32_t)(rho.read() * (1 << F_RHO));

        // --- B. Clock Simulation ---
        core->clk = 1;
        core->eval();

        core->clk = 0;
        core->eval();

        // --- C. Read Outputs (RTL -> SC) ---
        
        // 1. Valid
        out_valid.write(core->out_valid);

        // 2. Theta (Integer, no scaling)
        theta.write((theta_t)core->theta);

        // 3. Epsilon (21-bit signed Q2.19 -> Double)
        uint32_t raw_eps = core->epsilon & 0x1FFFFF; // Mask 21 bits
        int32_t s_eps = (raw_eps & 0x100000) 
                        ? (int32_t)(raw_eps | 0xFFE00000) // Sign extend
                        : (int32_t)raw_eps;
        
        epsilon.write(eps_t((double)s_eps / (double)(1 << F_EPS)));
    }

    // ==========================================================
    // 5. Constructor
    // ==========================================================
    SC_CTOR(top_rtl_wrap) {
        core = new Vtop("rtl_top_core");

        SC_METHOD(tick_proc);
        sensitive << clk.pos();
        dont_initialize();
    }

    ~top_rtl_wrap() {
        // Optional: Dump trace if enabled in Verilator
        // core->final();
        delete core;
    }
};