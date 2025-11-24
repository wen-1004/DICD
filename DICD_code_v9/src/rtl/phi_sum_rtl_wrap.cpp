#pragma once

#include <systemc>
#include "../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_phi_sum/Vphi_sum.h"

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(phi_sum_rtl_wrap) {
    // ==========================================================
    // 1. Ports (Match original SystemC phi_sum.h)
    // ==========================================================
    sc_in<bool> clk;
    sc_in<bool> rst; // SystemC: Active Low (reset_signal_is(rst, false))

    // Input r_t vectors
    sc_in<r_t> r_k_in_real;
    sc_in<r_t> r_k_in_imag;
    sc_in<r_t> r_k_minus_N_in_real;
    sc_in<r_t> r_k_minus_N_in_imag;

    // Coefficient
    sc_in<rho_t> rho_in;

    // Output
    sc_out<phi_t> phi_out;

    // ==========================================================
    // 2. Verilated Core Pointer
    // ==========================================================
    Vphi_sum* core;

    // ==========================================================
    // 3. Configuration (Fixed Point Precision)
    // ==========================================================
    // 根據 Verilog 邏輯推導:
    // 1. temp_rk_sq >>> 20 得到 Q.10 -> temp_rk_sq 為 Q.30 -> r_t 輸入為 Q.15
    static const int F_R_IN = 15; 
    
    // 2. rho 定義為 Q1.7
    static const int F_RHO  = 7;

    // 3. 輸出 phi_t 與中間變數對齊，根據 data_type 習慣與 Verilog 註解，應為 Q.10
    static const int F_PHI  = 10;

    // ==========================================================
    // 4. Evaluation Logic
    // ==========================================================
    void tick_proc() {
        // --- A. Drive Inputs (SC -> RTL) ---
        
        // 1. Reset Polarity: SC(Low) -> RTL(High)
        core->rst = !rst.read();

        // 2. Convert r_t inputs (Double -> Q.15 Integer)
        // 注意：這裡使用 F_R_IN = 15，因為 RTL 內部做平方後右移 20 位
        core->r_k_in_real         = (uint32_t)(r_k_in_real.read()         * (1 << F_R_IN));
        core->r_k_in_imag         = (uint32_t)(r_k_in_imag.read()         * (1 << F_R_IN));
        core->r_k_minus_N_in_real = (uint32_t)(r_k_minus_N_in_real.read() * (1 << F_R_IN));
        core->r_k_minus_N_in_imag = (uint32_t)(r_k_minus_N_in_imag.read() * (1 << F_R_IN));

        // 3. Convert rho (Double -> Q.7 Integer)
        // 注意：Verilog Port 名稱為 'rho'，SC 為 'rho_in'
        core->rho = (uint32_t)(rho_in.read() * (1 << F_RHO));

        // --- B. Clock Step ---
        
        // Rising Edge
        core->clk = 1;
        core->eval();

        // Falling Edge
        core->clk = 0;
        core->eval();

        // --- C. Read Output (RTL -> SC) ---
        
        // Lambda for output conversion (Q.10 Integer -> Double)
        // phi_t 為 16-bit signed
        uint32_t raw_out = core->phi_out & 0xFFFF;
        int32_t  s_out   = (raw_out & 0x8000) ? (int32_t)(raw_out | 0xFFFF0000) : (int32_t)raw_out;
        
        phi_out.write(phi_t((double)s_out / (double)(1 << F_PHI)));
    }

    // ==========================================================
    // 5. Constructor
    // ==========================================================
    SC_CTOR(phi_sum_rtl_wrap) {
        core = new Vphi_sum("rtl_phi_sum_core");

        SC_METHOD(tick_proc);
        sensitive << clk.pos();
        dont_initialize();
    }

    ~phi_sum_rtl_wrap() {
        delete core;
    }
};