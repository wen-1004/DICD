#ifndef GAMMA_SUM_CPP_H
#define GAMMA_SUM_CPP_H

#include <systemc.h>
#include "data_type.hpp"

SC_MODULE(gamma_sum) {
    sc_in<bool> clk;
    sc_in<bool> reset;  // active-low

    sc_in<r_t> r_k_in_real;
    sc_in<r_t> r_k_in_imag;
    sc_in<r_t> r_k_minus_N_in_real;
    sc_in<r_t> r_k_minus_N_in_imag;

    sc_out<gamma_t> gamma_out_real;
    sc_out<gamma_t> gamma_out_imag;

    static const int L_CONST = 16;

    double delay_line_real[L_CONST];
    double delay_line_imag[L_CONST];
    double current_sum_real;
    double current_sum_imag;

    void moving_sum_thread() {
        // reset
        for (int i = 0; i < L_CONST; ++i) {
            delay_line_real[i] = 0.0;
            delay_line_imag[i] = 0.0;
        }
        current_sum_real = 0.0;
        current_sum_imag = 0.0;
        gamma_out_real.write(0.0);
        gamma_out_imag.write(0.0);

        wait(); // wait for first clock after reset deassertion

        while (true) {
            // new product (r_k) * conj(r_{k-N})
            double a = r_k_in_real.read();
            double b = r_k_in_imag.read();
            double c = r_k_minus_N_in_real.read();
            double d = r_k_minus_N_in_imag.read();

            double product_real = (a * c) + (b * d);
            double product_imag = (b * c) - (a * d);

            // subtract oldest, add newest
            double old_real = delay_line_real[L_CONST - 1];
            double old_imag = delay_line_imag[L_CONST - 1];

            current_sum_real = current_sum_real + product_real - old_real;
            current_sum_imag = current_sum_imag + product_imag - old_imag;

            // outputs
            gamma_out_real.write(current_sum_real);
            gamma_out_imag.write(current_sum_imag);

            // shift delay line
            for (int i = L_CONST - 1; i > 0; --i) {
                delay_line_real[i] = delay_line_real[i - 1];
                delay_line_imag[i] = delay_line_imag[i - 1];
            }
            delay_line_real[0] = product_real;
            delay_line_imag[0] = product_imag;

            wait();
        }
    }

    SC_CTOR(gamma_sum) {
        SC_CTHREAD(moving_sum_thread, clk.pos());
        reset_signal_is(reset, false);
    }
};

#endif // GAMMA_SUM_CPP_H
