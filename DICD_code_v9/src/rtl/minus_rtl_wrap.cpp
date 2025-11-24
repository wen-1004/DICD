#pragma once

#include <systemc>
#include "../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_minus/Vminus.h"

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(minus_rtl_wrap) {
    // ==========================================================
    // 1. Ports (Match Verilog Interface)
    // ==========================================================
    // 注意：因為是純組合邏輯，Verilog 模組沒有 clk 和 rst
    
    // Inputs
    sc_in<mag_t> mag_in;
    sc_in<phi_t> phi_rho; // 注意：Verilog Port 名稱為 phi_rho

    // Output
    sc_out<lambda_t> lambda_out;

    // ==========================================================
    // 2. Verilated Core Pointer
    // ==========================================================
    Vminus* core;

    // ==========================================================
    // 3. Configuration (Fixed Point Precision)
    // ==========================================================
    // 根據註解: Q6.10 (10 fractional bits)
    static const int F_BITS = 10;

    // ==========================================================
    // 4. Evaluation Logic (Combinational)
    // ==========================================================
    void eval_proc() {
        // --- A. Drive Inputs (SC -> RTL) ---
        
        // 轉換 Double -> Integer (Q6.10)
        core->mag_in  = (uint32_t)(mag_in.read()  * (1 << F_BITS));
        core->phi_rho = (uint32_t)(phi_rho.read() * (1 << F_BITS));

        // --- B. Evaluate Core ---
        
        // 因為沒有時脈，直接呼叫 eval() 計算組合邏輯
        core->eval();

        // --- C. Read Output (RTL -> SC) ---
        
        // Lambda: Convert Raw Integer -> Double (Q6.10)
        // 處理 16-bit 符號擴展 (lambda_out 為 16-bit signed)
        auto rtl_to_sc = [](uint32_t raw_val) -> lambda_t {
            uint32_t masked = raw_val & 0xFFFF;
            // Sign Extension
            int32_t s_val = (masked & 0x8000) 
                            ? (int32_t)(masked | 0xFFFF0000) 
                            : (int32_t)masked;
            
            return lambda_t((double)s_val / (double)(1 << F_BITS));
        };

        lambda_out.write(rtl_to_sc(core->lambda_out));
    }

    // ==========================================================
    // 5. Constructor
    // ==========================================================
    SC_CTOR(minus_rtl_wrap) {
        core = new Vminus("rtl_minus_core");

        // 使用 SC_METHOD，並對輸入訊號敏感
        // 這樣當 mag_in 或 phi_rho 改變時，輸出會立即更新 (0 Latency)
        SC_METHOD(eval_proc);
        sensitive << mag_in << phi_rho;
        dont_initialize();
    }

    ~minus_rtl_wrap() {
        delete core;
    }
};