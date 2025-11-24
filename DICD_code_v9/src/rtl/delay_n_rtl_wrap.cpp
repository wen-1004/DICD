#pragma once

#include <systemc>
#include "../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_delay_n/Vdelay_n.h"

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(delay_n_rtl_wrap) {
    // ==========================================================
    // 1. Ports (必須與原始 SystemC delay_n.h 完全一致)
    // ==========================================================
    sc_in<bool> clk;
    sc_in<bool> rst; // SystemC 模型定義為 Active Low (reset_signal_is(rst, false))

    // 輸入 Ports
    sc_in<r_t> r_in_real;
    sc_in<r_t> r_in_imag;

    // 輸出 Ports
    sc_out<r_t> r_d1_real;      // 對應 Verilog 的 r_real (1-cycle delay)
    sc_out<r_t> r_d1_imag;      
    sc_out<r_t> r_dN_out_real;  // 對應 Verilog 的 r_dN_real (N-cycle delay)
    sc_out<r_t> r_dN_out_imag;  

    // ==========================================================
    // 2. Verilated Core Pointer
    // ==========================================================
    Vdelay_n* core; 

    // ==========================================================
    // 3. Configuration
    // ==========================================================
    // 假設 r_t 為 16-bit, Q6.10 格式 (Fractional bits = 10)
    // 用於將 SystemC 的浮點數值轉換為 Verilog 的整數值
    static const int F_BITS = 10; 

    // ==========================================================
    // 4. Evaluation Logic
    // ==========================================================
    void tick_proc() {
        // --- A. 輸入驅動 (SystemC -> Verilator) ---

        // 1. Reset 處理: 
        // SystemC (Active Low, 0=Reset) -> Verilog (Active High, 1=Reset)
        // 必須反相 (!)
        core->rst = !rst.read(); 

        // 2. 數據轉換 (Fixed Point Double -> Raw Integer)
        // 對應關係: SC: r_in_real -> Verilog: rx_re_in
        core->rx_re_in  = (uint32_t)(r_in_real.read() * (1 << F_BITS));
        core->rx_img_in = (uint32_t)(r_in_imag.read() * (1 << F_BITS));

        // --- B. 時脈模擬 (Cycle Accurate) ---
        
        // 模擬 Verilog 的時脈上升緣 (PosEdge)
        core->clk = 1;
        core->eval(); 

        // 模擬時脈下降緣 (NegEdge)，完成一個完整的 Cycle
        core->clk = 0;
        core->eval(); 

        // --- C. 輸出讀取 (Verilator -> SystemC) ---

        // Lambda 函數: 處理 16-bit 符號擴展 (Sign Extension) 並轉回定點數
        auto rtl_to_sc = [](uint32_t raw_val) -> r_t {
            // 確保只取 16 bits
            uint32_t masked = raw_val & 0xFFFF;
            
            // 檢查第 15 bit (Sign bit)
            // 若為 1 (負數)，則將 32-bit 整數的高位全部補 1 (0xFFFF0000)
            int32_t sign_extended = (masked & 0x8000) 
                                    ? (int32_t)(masked | 0xFFFF0000) 
                                    : (int32_t)masked;
            
            // 除以 2^F_BITS 轉回 double/fixed-point
            return r_t((double)sign_extended / (double)(1 << F_BITS));
        };

        // 映射 1: Verilog (r_real) -> SystemC (r_d1_real)
        r_d1_real.write(rtl_to_sc(core->r_real));
        r_d1_imag.write(rtl_to_sc(core->r_imag));

        // 映射 2: Verilog (r_dN_real) -> SystemC (r_dN_out_real)
        r_dN_out_real.write(rtl_to_sc(core->r_dN_real));
        r_dN_out_imag.write(rtl_to_sc(core->r_dN_imag));
    }

    // ==========================================================
    // 5. Constructor
    // ==========================================================
    SC_CTOR(delay_n_rtl_wrap) {
        // 實例化 Verilated 模型
        core = new Vdelay_n("rtl_delay_n_core");

        // 使用 SC_METHOD 對 clk 上升緣敏感
        // 這模擬了原始 SystemC 中 SC_CTHREAD(..., clk.pos()) 的行為
        SC_METHOD(tick_proc);
        sensitive << clk.pos();
        dont_initialize();
    }

    // Destructor
    ~delay_n_rtl_wrap() {
        delete core;
    }
};