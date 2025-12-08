#include <systemc.h>
#include <cmath>
#include "../include/data_type.hpp"

#include <cmath>
#include <cstdint>
#include <iostream>

// Print unsigned Q6.8 in the same style as RTL wrapper
template <typename T>
static inline void print_phi_q68_like_rtl(const char* tag, const T& v) {
    const int PHI_FRAC = 8;
    // Convert numeric value -> raw Q6.8 integer
    long long raw = llround((double)v * (1LL << PHI_FRAC));
    uint32_t raw_u = (uint32_t)raw & 0x3FFFu;  // match RTL 14-bit mask

    uint32_t int_part  = raw_u >> PHI_FRAC;
    uint32_t frac_part = raw_u & ((1u << PHI_FRAC) - 1u);

    std::cout << tag << " = "
              << int_part << " + " << frac_part << "/256"
              << "  raw=" << raw_u
              << std::endl;
}


SC_MODULE(phi_sum) {
    sc_in<bool> clk;
    sc_in<bool> rst;

    sc_in<r_t> r_k_in_real;
    sc_in<r_t> r_k_in_imag;
    sc_in<r_t> r_k_minus_N_in_real;
    sc_in<r_t> r_k_minus_N_in_imag;

    sc_in<rho_t> rho_in;

    sc_out<phi_t> phi_out;

    static const int L_CONST_PHI = 16;

    // Original state
    phi_t delay_line[L_CONST_PHI];
    phi_t current_sum;
    phi_t phi_out_reg;  // the original 1-cycle latency register

    // Extra output latency to match hardware
    static const int EXTRA_LAT = 4;
    phi_t out_pipe[EXTRA_LAT];

    SC_CTOR(phi_sum) {
        SC_CTHREAD(proc, clk.pos());
        reset_signal_is(rst, true);
    }

    void proc() {
        // reset
        for (int i = 0; i < L_CONST_PHI; ++i) delay_line[i] = 0.0;
        current_sum = 0.0;
        phi_out_reg = 0.0;

        for (int i = 0; i < EXTRA_LAT; ++i) out_pipe[i] = 0.0;

        phi_out.write(0.0);

        wait();

        while (true) {
            rho_t rho_half = rho_in.read() >> 1;
            r_t a_re = r_k_in_real.read();
            r_t a_im = r_k_in_imag.read();
            r_t b_re = r_k_minus_N_in_real.read();
            r_t b_im = r_k_minus_N_in_imag.read();
            phi_t r_k_sq   = a_re * a_re + a_im * a_im;
            phi_t r_kmN_sq = b_re * b_re + b_im * b_im;
            phi_t energy_to_sum = rho_half * (r_k_sq + r_kmN_sq);

            // subtract oldest, add newest
            phi_t old_energy = delay_line[L_CONST_PHI - 1];
            current_sum = current_sum + energy_to_sum - old_energy;

            // shift delay line
            for (int i = L_CONST_PHI - 1; i > 0; --i) {
                delay_line[i] = delay_line[i - 1];
            }
            delay_line[0] = energy_to_sum;

            // extra output-only pipeline
            for (int i = EXTRA_LAT - 1; i > 0; --i)
                out_pipe[i] = out_pipe[i - 1];
            out_pipe[0] = current_sum;

            phi_out.write(out_pipe[EXTRA_LAT - 1]);

            phi_t phi_final = out_pipe[EXTRA_LAT - 1];
            print_phi_q68_like_rtl("phi_out", phi_final);

            wait();
        }
    }
};
