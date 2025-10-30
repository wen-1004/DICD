#ifndef GAMMA_SUM_CPP_H
#define GAMMA_SUM_CPP_H

#include <systemc.h>

SC_MODULE(gamma_sum) {
    sc_in<bool> clk;
    sc_in<bool> reset;

    sc_in<double> r_k_in_real;
    sc_in<double> r_k_in_imag;
    sc_in<double> r_k_minus_N_in_real;
    sc_in<double> r_k_minus_N_in_imag;
    sc_in<bool> valid_in;

    sc_out<double> gamma_out_real;
    sc_out<double> gamma_out_imag;
    sc_out<bool> valid_out;

    static const int L_CONST = 16;

    double delay_line_real[L_CONST];
    double delay_line_imag[L_CONST];
    double current_sum_real;
    double current_sum_imag;
    unsigned int count;

    void moving_sum_thread() {
        for (int i = 0; i < L_CONST; ++i) {
            delay_line_real[i] = 0.0;
            delay_line_imag[i] = 0.0;
        }
        current_sum_real = 0.0;
        current_sum_imag = 0.0;
        count = 0;
        gamma_out_real.write(0.0);
        gamma_out_imag.write(0.0);
        valid_out.write(false);

        wait();

        while (true) {
            double product_to_sum_real = 0.0;
            double product_to_sum_imag = 0.0;

            if (valid_in.read()) {
                double a = r_k_in_real.read();
                double b = r_k_in_imag.read();
                double c = r_k_minus_N_in_real.read();
                double d = r_k_minus_N_in_imag.read();

                product_to_sum_real = (a*c) + (b*d);
                product_to_sum_imag = (b*c) - (a*d);

                if (count < L_CONST) count++;
            } else {
                count = 0;
            }

            double old_product_real = delay_line_real[L_CONST-1];
            double old_product_imag = delay_line_imag[L_CONST-1];

            current_sum_real = current_sum_real + product_to_sum_real - old_product_real;
            current_sum_imag = current_sum_imag + product_to_sum_imag - old_product_imag;

            gamma_out_real.write(current_sum_real);
            gamma_out_imag.write(current_sum_imag);
            valid_out.write(count == L_CONST);

            for (int i = L_CONST-1; i > 0; --i) {
                delay_line_real[i] = delay_line_real[i-1];
                delay_line_imag[i] = delay_line_imag[i-1];
            }
            delay_line_real[0] = product_to_sum_real;
            delay_line_imag[0] = product_to_sum_imag;

            wait();
        }
    }

    SC_CTOR(gamma_sum) {
        SC_CTHREAD(moving_sum_thread, clk.pos());
        reset_signal_is(reset, true);
    }
};

#endif // GAMMA_SUM_CPP_H

