#include <systemc.h>
#include "../include/data_type.hpp"

SC_MODULE(delay_n) {
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_in<r_t> r_in_real;
    sc_in<r_t> r_in_imag;

    sc_out<r_t> r_d1_real;
    sc_out<r_t> r_d1_imag;
    sc_out<r_t> r_dN_out_real;
    sc_out<r_t> r_dN_out_imag;

    static const int N = 256;
    r_t delay_line_real[N];
    r_t delay_line_imag[N];
    unsigned int count;


    SC_HAS_PROCESS(delay_n);
    delay_n(sc_module_name n) : sc_module(n) {
        SC_CTHREAD(proc, clk.pos());
        reset_signal_is(rst, true);
    }

    void proc() {
        for (int i = 0; i < N; ++i) {
            delay_line_real[i] = 0.0;
            delay_line_imag[i] = 0.0;
        }
        count = 0;

        r_dN_out_real.write(0.0);
        r_dN_out_imag.write(0.0);

        wait();

        while (true) {
            r_d1_real.write(r_in_real.read());
            r_d1_imag.write(r_in_imag.read());

            r_t out_val_real = delay_line_real[N-1];
            r_t out_val_imag = delay_line_imag[N-1];

            for (int i = N-1; i > 0; --i) {
                delay_line_real[i] = delay_line_real[i-1];
                delay_line_imag[i] = delay_line_imag[i-1];
            }

            delay_line_real[0] = r_in_real.read();
            delay_line_imag[0] = r_in_imag.read();

            if (count < N) count++;

            r_dN_out_real.write(out_val_real);
            r_dN_out_imag.write(out_val_imag);

            wait();
        }
    }
};
