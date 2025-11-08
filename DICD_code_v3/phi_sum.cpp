#ifndef PHI_SUM_CPP_H
#define PHI_SUM_CPP_H

#include <systemc.h>
#include <cmath>

SC_MODULE(phi_sum) {
    sc_in<bool> clk;
    sc_in<bool> reset;  // active-low

    sc_in<double> r_k_in_real;
    sc_in<double> r_k_in_imag;
    sc_in<double> r_k_minus_N_in_real;
    sc_in<double> r_k_minus_N_in_imag;

    sc_in<double> p_in;

    sc_out<double> phi_out;

    static const int L_CONST_PHI = 16;

    double delay_line[L_CONST_PHI];
    double current_sum;

    void moving_sum_thread() {
        // reset
        for (int i = 0; i < L_CONST_PHI; ++i) delay_line[i] = 0.0;
        current_sum = 0.0;
        phi_out.write(0.0);

        wait(); // wait for first clock after reset deassertion

        while (true) {
            // compute new sample energy
            double p_half = p_in.read() * 0.5;
            double r_k_sq = std::pow(r_k_in_real.read(), 2) + std::pow(r_k_in_imag.read(), 2);
            double r_kmN_sq = std::pow(r_k_minus_N_in_real.read(), 2) + std::pow(r_k_minus_N_in_imag.read(), 2);
            double energy_to_sum = p_half * (r_k_sq + r_kmN_sq);

            // subtract oldest, add newest
            double old_energy = delay_line[L_CONST_PHI - 1];
            current_sum = current_sum + energy_to_sum - old_energy;

            // shift delay line
            for (int i = L_CONST_PHI - 1; i > 0; --i) {
                delay_line[i] = delay_line[i - 1];
            }
            delay_line[0] = energy_to_sum;

            // drive output
            phi_out.write(current_sum);

            wait();
        }
    }

    SC_CTOR(phi_sum) {
        SC_CTHREAD(moving_sum_thread, clk.pos());
        reset_signal_is(reset, false);
    }
};

#endif // PHI_SUM_CPP_H
