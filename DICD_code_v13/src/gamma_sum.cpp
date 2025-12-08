#include <systemc.h>
#include "../include/data_type.hpp"

SC_MODULE(gamma_sum) {
    sc_in<bool> clk;
    sc_in<bool> rst;  

    sc_in<r_t> r_k_in_real;
    sc_in<r_t> r_k_in_imag;
    sc_in<r_t> r_k_minus_N_in_real;
    sc_in<r_t> r_k_minus_N_in_imag;

    sc_out<gamma_t> gamma_out_real;
    sc_out<gamma_t> gamma_out_imag;

    static const int L_CONST = 16;

    gamma_t delay_line_real[L_CONST];
    gamma_t delay_line_imag[L_CONST];
    gamma_t current_sum_real;
    gamma_t current_sum_imag;

    // ---- NEW: extra output pipeline ----
    // Current model is treated as 1-cycle latency.
    // Add 2 more cycles here -> total visible latency = 3 cycles.
    static const int OUT_DELAY = 2;
    gamma_t out_delay_line_real[OUT_DELAY];
    gamma_t out_delay_line_imag[OUT_DELAY];

    SC_CTOR(gamma_sum) {
        SC_CTHREAD(proc, clk.pos());
        reset_signal_is(rst, true);
    }

    void proc() {
        // reset
        for (int i = 0; i < L_CONST; ++i) {
            delay_line_real[i] = 0.0;
            delay_line_imag[i] = 0.0;
        }
        current_sum_real = 0.0;
        current_sum_imag = 0.0;

        for (int i = 0; i < OUT_DELAY; ++i) {
            out_delay_line_real[i] = 0.0;
            out_delay_line_imag[i] = 0.0;
        }

        gamma_out_real.write(0.0);
        gamma_out_imag.write(0.0);

        wait(); // wait for first clock after reset deassertion

        while (true) {
            // new product (r_k) * conj(r_{k-N})
            r_t a = r_k_in_real.read();
            r_t b = r_k_in_imag.read();
            r_t c = r_k_minus_N_in_real.read();
            r_t d = r_k_minus_N_in_imag.read();

            gamma_t product_real = (a * c) + (b * d);
            gamma_t product_imag = (b * c) - (a * d);

            // subtract oldest, add newest
            gamma_t old_real = delay_line_real[L_CONST - 1];
            gamma_t old_imag = delay_line_imag[L_CONST - 1];

            current_sum_real = current_sum_real + product_real - old_real;
            current_sum_imag = current_sum_imag + product_imag - old_imag;

            // ---- NEW: 2-cycle delayed output path ----
            gamma_t out_old_real = out_delay_line_real[OUT_DELAY - 1];
            gamma_t out_old_imag = out_delay_line_imag[OUT_DELAY - 1];

            for (int i = OUT_DELAY - 1; i > 0; --i) {
                out_delay_line_real[i] = out_delay_line_real[i - 1];
                out_delay_line_imag[i] = out_delay_line_imag[i - 1];
            }
            out_delay_line_real[0] = current_sum_real;
            out_delay_line_imag[0] = current_sum_imag;

            gamma_out_real.write(out_old_real);
            gamma_out_imag.write(out_old_imag);

            // shift delay line (window history)
            for (int i = L_CONST - 1; i > 0; --i) {
                delay_line_real[i] = delay_line_real[i - 1];
                delay_line_imag[i] = delay_line_imag[i - 1];
            }
            delay_line_real[0] = product_real;
            delay_line_imag[0] = product_imag;

            wait();
        }
    }
};
