// angle.cpp
#include <systemc>
#include <cmath>
#include "../include/data_type.hpp"
using namespace sc_core;
using namespace sc_dt;

static inline ang_t cordic_atan2_fx(gamma_t y_in, gamma_t x_in) {
    const int ITERS = 6;
    static const ang_t atan_lut[ITERS] = {
        ang_t("0b0.11001001"), // atan(2^0)  = atan(1)    ≈ 0.785398  -> 201/256 = 0.78515625
        ang_t("0b0.01110110"), // atan(2^-1) = atan(1/2)  ≈ 0.463648  -> 118/256 = 0.4609375
        ang_t("0b0.00111110"), // atan(2^-2) = atan(1/4)  ≈ 0.244979  ->  62/256 = 0.2421875
        ang_t("0b0.00011111"), // atan(2^-3) = atan(1/8)  ≈ 0.124355  ->  31/256 = 0.12109375
        ang_t("0b0.00010000"), // atan(2^-4) = atan(1/16) ≈ 0.062419  ->  16/256 = 0.0625
        ang_t("0b0.00001000")  // atan(2^-5) = atan(1/32) ≈ 0.031240  ->   8/256 = 0.03125
    };

    gamma_t x = x_in;
    gamma_t y = y_in;
    ang_t z = 0.0;

    if (x < 0) {
        if (y >= 0) {
            gamma_t xt =  y; gamma_t yt = -x;
            x = xt; y = yt;
            z =  ang_t(M_PI/2.0);
        } else {
            gamma_t xt = -y; gamma_t yt =  x;
            x = xt; y = yt;
            z = -ang_t(M_PI/2.0);
        }
    }

    for (int i = 0; i < ITERS; ++i) {
        gamma_t x_shift = x / (1 << i);
        gamma_t y_shift = y / (1 << i);
        if (y >= 0) { x = x + y_shift; y = y - x_shift; z = z + atan_lut[i]; }
        else        { x = x - y_shift; y = y + x_shift; z = z - atan_lut[i]; }
    }
    return z;
}


struct angle : public sc_module {
    sc_in<bool>       clk;
    sc_in<bool>       rst;
    sc_in<gamma_t> gm_in_real;
    sc_in<gamma_t> gm_in_imag;
    sc_out<ang_t> ang_out;
  
    static const int N_DELAY = 7;

    ang_t delay_line[N_DELAY];

    // === constructor ===
    SC_HAS_PROCESS(angle);
    angle(sc_module_name n) : sc_module(n) {
        SC_CTHREAD(proc, clk.pos());
        reset_signal_is(rst, true);
    }
  
    void proc() {
        // reset
        ang_out.write(0);
        wait();
  
        while (true) {
            gamma_t xr = gm_in_real.read();
            gamma_t xi = gm_in_imag.read();
  
            ang_t phase_now = cordic_atan2_fx(xi, xr);
  
            for (int i = N_DELAY - 1; i > 0; --i)
                delay_line[i] = delay_line[i - 1];
  
            delay_line[0] = phase_now;

            ang_out.write(delay_line[N_DELAY - 1]);
  
            wait();
        }
    }
};

