#pragma once

#include <systemc>
#include <vector>
#include "../include/data_type.hpp"
#include "verilated.h"
#include "../../verilator/obj_buf/Vbuf.h"

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(buf_rtl_wrap) {
    // ==========================================================
    // 1. Ports
    // ==========================================================
    sc_in<bool> clk;
    sc_in<bool> rst; // SystemC: Active Low

    // Input
    sc_in<ang_t> ang_in;

    // Outputs
    // SystemC 不支援直接定義陣列 Port，我們使用 sc_vector 來產生 256 個 ports
    // 在波形或連接時，它們會顯示為 angle_buf_0, angle_buf_1 ...
    sc_vector<sc_out<ang_t>> angle_buf;
    
    // Write Pointer Output
    // write_ptr 是 8-bit unsigned
    sc_out<sc_uint<8>> write_ptr;

    // ==========================================================
    // 2. Verilated Core Pointer
    // ==========================================================
    Vbuf* core;

    // ==========================================================
    // 3. Configuration (Fixed Point Precision)
    // ==========================================================
    // ang_t 是 logic signed [12:0]
    // 根據 CORDIC 模組推導，這是 Q2.10
    static const int F_ANG = 10;
    static const int N_BUF = 256;

    // ==========================================================
    // 4. Evaluation Logic
    // ==========================================================
    void tick_proc() {
        // --- A. Drive Inputs (SC -> RTL) ---

        // 1. Reset: SC(Low) -> RTL(High)
        core->rst = !rst.read();

        // 2. Input Conversion (ang_t Q2.10 -> Integer)
        core->ang_in = (uint32_t)(ang_in.read() * (1 << F_ANG));

        // --- B. Clock Simulation ---
        core->clk = 1;
        core->eval();

        core->clk = 0;
        core->eval();

        // --- C. Read Outputs (RTL -> SC) ---

        // 1. Write Pointer
        write_ptr.write(core->write_ptr);

        // 2. Angle Buffer Array
        // 定義 Lambda 處理 13-bit 符號擴展 (Sign Extension)
        auto rtl_to_sc = [](uint32_t raw_val) -> ang_t {
            // Mask 13 bits (0x1FFF)
            uint32_t masked = raw_val & 0x1FFF;
            
            // Check sign bit (bit 12, 0x1000)
            // If negative, extend 1s to higher bits (32-bit int)
            int32_t s_val = (masked & 0x1000) 
                            ? (int32_t)(masked | 0xFFFFE000) 
                            : (int32_t)masked;
            
            return ang_t((double)s_val / (double)(1 << F_ANG));
        };

        // 迴圈讀取 Verilator 陣列並寫入 SystemC Ports
        // Verilator 通常將 unpacked array 映射為 C++ 陣列 core->angle_buf[i]
        for (int i = 0; i < N_BUF; ++i) {
            angle_buf[i].write(rtl_to_sc(core->angle_buf[i]));
        }
    }

    // ==========================================================
    // 5. Constructor
    // ==========================================================
    SC_CTOR(buf_rtl_wrap) 
        : angle_buf("angle_buf", N_BUF) // 初始化 sc_vector，命名為 "angle_buf"
    {
        core = new Vbuf("rtl_buf_core");

        SC_METHOD(tick_proc);
        sensitive << clk.pos();
        dont_initialize();
    }

    ~buf_rtl_wrap() {
        delete core;
    }
};