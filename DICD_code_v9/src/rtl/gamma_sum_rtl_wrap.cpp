#pragma once

#include <systemc>
#include "../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_gamma_sum/Vgamma_sum.h"

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(gamma_sum_rtl_wrap) {
    // ==========================================================
    // 1. Ports (Match original SystemC gamma_sum.h)
    // ==========================================================
    sc_in<bool> clk;
    sc_in<bool> rst; // SystemC: Active Low (0=Reset)

    // Inputs (r_t)
    sc_in<r_t> r_k_in_real;
    sc_in<r_t> r_k_in_imag;
    sc_in<r_t> r_k_minus_N_in_real;
    sc_in<r_t> r_k_minus_N_in_imag;

    // Outputs (gamma_t)
    sc_out<gamma_t> gamma_out_real;
    sc_out<gamma_t> gamma_out_imag;

    // ==========================================================
    // 2. Verilated Core Pointer
    // ==========================================================
    Vgamma_sum* core;

    // ==========================================================
    // 3. Configuration (Fixed Point Precision)
    // ==========================================================
    // 根據 Verilog 邏輯 (Product >>> 20) 推導:
    // 輸入 r_t 需視為 Q1.15，這樣相乘得到 Q2.30，右移 20 後剩 Q2.10
    static const int F_R_IN = 15; 
    
    // 輸出 gamma_t 視為 Q6.10 (系統標準格式)
    static const int F_GAMMA_OUT = 10;

    // ==========================================================
    // 4. Evaluation Logic
    // ==========================================================
    void tick_proc() {
        // --- A. Drive Inputs (SystemC -> Verilator) ---

        // 1. Reset Polarity: SC(Low) -> RTL(High)
        core->rst = !rst.read();

        // 2. Convert Inputs (Double -> Integer Q1.15)
        // 使用 15-bit shift 確保 Verilog 內部的乘法與移位邏輯正確
        core->r_k_in_real         = (uint32_t)(r_k_in_real.read()         * (1 << F_R_IN));
        core->r_k_in_imag         = (uint32_t)(r_k_in_imag.read()         * (1 << F_R_IN));
        core->r_k_minus_N_in_real = (uint32_t)(r_k_minus_N_in_real.read() * (1 << F_R_IN));
        core->r_k_minus_N_in_imag = (uint32_t)(r_k_minus_N_in_imag.read() * (1 << F_R_IN));

        // --- B. Clock Simulation ---
        
        // Rising Edge (Trigger always blocks)
        core->clk = 1;
        core->eval();

        // Falling Edge
        core->clk = 0;
        core->eval();

        // --- C. Read Outputs (Verilator -> SystemC) ---
        
        // Lambda: Convert Raw Integer -> Double (Q6.10)
        // 處理 16-bit 符號擴展
        auto rtl_to_sc = [](uint32_t raw_val) -> gamma_t {
            uint32_t masked = raw_val & 0xFFFF;
            int32_t s_val   = (masked & 0x8000) 
                              ? (int32_t)(masked | 0xFFFF0000) 
                              : (int32_t)masked;
            
            return gamma_t((double)s_val / (double)(1 << F_GAMMA_OUT));
        };

        gamma_out_real.write(rtl_to_sc(core->gamma_out_real));
        gamma_out_imag.write(rtl_to_sc(core->gamma_out_imag));
    }

    // ==========================================================
    // 5. Constructor
    // ==========================================================
    SC_CTOR(gamma_sum_rtl_wrap) {
        core = new Vgamma_sum("rtl_gamma_sum_core");

        // 使用 SC_METHOD 對 clk.pos() 敏感，模擬 CTHREAD 行為
        SC_METHOD(tick_proc);
        sensitive << clk.pos();
        dont_initialize();
    }

    ~gamma_sum_rtl_wrap() {
        delete core;
    }
};