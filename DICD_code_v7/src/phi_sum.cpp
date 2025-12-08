#ifndef PHI_SUM_CPP_H
#define PHI_SUM_CPP_H

#include <systemc.h>
#include <cmath>
#include "../include/data_type.hpp"

SC_MODULE(phi_sum) {
    sc_in<bool> clk;
    sc_in<bool> rst;  // active-low

    sc_in<r_t> r_k_in_real;
    sc_in<r_t> r_k_in_imag;
    sc_in<r_t> r_k_minus_N_in_real;
    sc_in<r_t> r_k_minus_N_in_imag;

    sc_in<rho_t> rho_in;

    sc_out<phi_t> phi_out;

    static const int L_CONST_PHI = 16;

    phi_t delay_line[L_CONST_PHI];
    phi_t current_sum;
    phi_t phi_out_reg;  // 1-cycle latency register

    SC_CTOR(phi_sum) {
        SC_CTHREAD(moving_sum_phi, clk.pos());
        reset_signal_is(rst, false);
    }

    void moving_sum_phi() {
        // reset
        for (int i = 0; i < L_CONST_PHI; ++i) delay_line[i] = 0.0;
        current_sum = 0.0;
        phi_out_reg = 0.0;
        phi_out.write(0.0);

        wait(); // wait for first clock after reset deassertion

        while (true) {
            // compute new sample energy
            rho_t rho_half = rho_in.read() * rho_t(0.5);
            phi_t r_k_sq = r_k_in_real.read() * r_k_in_real.read()
                         + r_k_in_imag.read() * r_k_in_imag.read();
            phi_t r_kmN_sq = r_k_minus_N_in_real.read() * r_k_minus_N_in_real.read()
                           + r_k_minus_N_in_imag.read() * r_k_minus_N_in_imag.read();
            phi_t energy_to_sum = phi_t(rho_half) * (r_k_sq + r_kmN_sq);

            // subtract oldest, add newest
            phi_t old_energy = delay_line[L_CONST_PHI - 1];
            current_sum = current_sum + energy_to_sum - old_energy;

            // shift delay line
            for (int i = L_CONST_PHI - 1; i > 0; --i) {
                delay_line[i] = delay_line[i - 1];
            }
            delay_line[0] = energy_to_sum;

            // 1-cycle delayed output:
            // drive previous sum, then update register with new sum
            phi_out.write(phi_out_reg);
            phi_out_reg = current_sum;

            wait();
        }
    }
};

#endif // PHI_SUM_CPP_H
