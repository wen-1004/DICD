// angle.cpp
#include <systemc>
#include <cmath>
using namespace sc_core;
using namespace sc_dt;

#include "data_type.hpp"

static inline ang_t cordic_atan2_fx(gamma_t y_in, gamma_t x_in) {
    const int ITERS = 8;
    static const ang_t atan_lut[ITERS] = {
        ang_t("0b0.11001001000011111101"), // 785398
        ang_t("0b0.01110110101100011010"), // 463648
        ang_t("0b0.00111110101101101111"), // 244979
        ang_t("0b0.00011111110101011100"), // 124355
        ang_t("0b0.00001111111110101011"), // 62419
        ang_t("0b0.00000111111111110110"), // 31240
        ang_t("0b0.00000011111111111111"), // 15624
        ang_t("0b0.00000001111111111111"), // 7812
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
  
    int N_DELAY;
  
    // === constructor ===
    SC_HAS_PROCESS(angle);
    angle(sc_module_name n, int delay_cycles = 1)
    : sc_module(n), N_DELAY(delay_cycles) {
        SC_CTHREAD(proc, clk.pos());
        reset_signal_is(rst, false);
    }
  
    void proc() {
        std::vector<ang_t> delay_line(N_DELAY, 0);
  
        // reset
        ang_out.write(0);
        wait();
  
        while (true) {
            gamma_t xr = gm_in_real.read();
            gamma_t xi = gm_in_imag.read();
  
            ang_t phase_now = cordic_atan2_fx(xi, xr);
  
            ang_out.write(delay_line.back());
  
            for (int i = N_DELAY - 1; i > 0; --i)
              delay_line[i] = delay_line[i - 1];
  
            delay_line[0] = phase_now;
  
            wait();
        }
    }
};
