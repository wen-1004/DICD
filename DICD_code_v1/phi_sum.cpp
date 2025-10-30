#ifndef PHI_SUM_CPP_H
#define PHI_SUM_CPP_H

#include <systemc.h>
#include <cmath>

SC_MODULE(phi_sum) {
    sc_in<bool> clk;
    sc_in<bool> reset;

    sc_in<double> r_k_in_real;
    sc_in<double> r_k_in_imag;
    sc_in<double> r_k_minus_N_in_real;
    sc_in<double> r_k_minus_N_in_imag;
    sc_in<bool> valid_in;

    sc_in<double> p_in;

    sc_out<double> phi_out;
    sc_out<bool> valid_out;

    static const int L_CONST_PHI = 16;

    double delay_line[L_CONST_PHI];
    double current_sum;
    unsigned int count;

    void moving_sum_thread() {
        for (int i = 0; i < L_CONST_PHI; ++i) delay_line[i] = 0.0;
        current_sum = 0.0;
        count = 0;
        phi_out.write(0.0);
        valid_out.write(false);

        wait();

        while (true) {
            double energy_to_sum = 0.0;

            if (valid_in.read()) {
                double p_half = p_in.read() / 2.0;
                double r_k_sq = std::pow(r_k_in_real.read(),2) + std::pow(r_k_in_imag.read(),2);
                double r_k_minus_N_sq = std::pow(r_k_minus_N_in_real.read(),2) + std::pow(r_k_minus_N_in_imag.read(),2);
                energy_to_sum = p_half * (r_k_sq + r_k_minus_N_sq);

                if (count < L_CONST_PHI) count++;
            } else {
                count = 0;
            }

            double old_energy = delay_line[L_CONST_PHI-1];
            current_sum = current_sum + energy_to_sum - old_energy;

            for (int i = L_CONST_PHI-1; i > 0; --i) {
                delay_line[i] = delay_line[i-1];
            }
            delay_line[0] = energy_to_sum;

            phi_out.write(current_sum);
            valid_out.write(count == L_CONST_PHI);

            wait();
        }
    }

    SC_CTOR(phi_sum) {
        SC_CTHREAD(moving_sum_thread, clk.pos());
        reset_signal_is(reset, true);
    }
};

#endif // PHI_SUM_CPP_H

