#pragma once

#include <systemc>
#include <vector>
#include "../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_select_eps/Vselect_eps.h"

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(select_eps_rtl_wrap) {
    // ==========================================================
    // 1. Ports
    // ==========================================================
    // 純組合邏輯，無 clk/rst

    // Array Input: 來自 buf 模組
    // 使用 sc_vector 方便與 buf 的 sc_vector<sc_out> 對接
    sc_vector<sc_in<ang_t>> angle_buf;

    // Control Inputs
    sc_in<sc_uint<8>> write_ptr;
    sc_in<theta_t>    theta_in;   // theta_t is 8-bit

    // Output
    sc_out<eps_t>     eps_out;    // eps_t is 21-bit signed

    // ==========================================================
    // 2. Verilated Core Pointer
    // ==========================================================
    Vselect_eps* core;

    // ==========================================================
    // 3. Configuration (Fixed Point Precision)
    // ==========================================================
    static const int N_BUF = 256;
    
    // 輸入 ang_t: Q2.10 (基於 CORDIC 輸出)
    static const int F_ANG = 10;

    // 輸出 eps_t:
    // Logic: ang(Q.10) * INV_2PI(Q.13) = Q.23
    // Slice [24:4] 等同於右移 4 位 -> Q.19
    static const int F_EPS = 19;

    // ==========================================================
    // 4. Evaluation Logic
    // ==========================================================
    void eval_proc() {
        // --- A. Drive Inputs (SC -> RTL) ---

        // 1. Drive Array Input
        // 遍歷 sc_vector 並轉換為 Verilator 的 C 陣列輸入
        for (int i = 0; i < N_BUF; ++i) {
            core->angle_buf[i] = (uint32_t)(angle_buf[i].read() * (1 << F_ANG));
        }

        // 2. Drive Controls
        core->write_ptr = write_ptr.read();
        core->theta_in  = theta_in.read(); // theta_t is simple int/uint8

        // --- B. Evaluate (Combinational) ---
        core->eval();

        // --- C. Read Output (RTL -> SC) ---
        
        // eps_out is 21-bit signed
        // Mask: 0x1FFFFF
        // Sign Bit: 20 (0x100000)
        auto rtl_to_sc = [](uint32_t raw_val) -> eps_t {
            uint32_t masked = raw_val & 0x1FFFFF; // Keep 21 bits
            
            // Sign Extension to 32-bit
            int32_t s_val = (masked & 0x100000) 
                            ? (int32_t)(masked | 0xFFE00000) // Fill top 11 bits with 1
                            : (int32_t)masked;

            return eps_t((double)s_val / (double)(1 << F_EPS));
        };

        eps_out.write(rtl_to_sc(core->eps_out));
    }

    // ==========================================================
    // 5. Constructor
    // ==========================================================
    SC_CTOR(select_eps_rtl_wrap) 
        : angle_buf("angle_buf", N_BUF) // 初始化 vector 大小
    {
        core = new Vselect_eps("rtl_select_eps_core");

        SC_METHOD(eval_proc);
        
        // Sensitivity List 設定
        // 必須對所有輸入敏感，包括陣列中的每一個元素
        sensitive << write_ptr << theta_in;
        for (int i = 0; i < N_BUF; ++i) {
            sensitive << angle_buf[i];
        }
        
        dont_initialize();
    }

    ~select_eps_rtl_wrap() {
        delete core;
    }
};