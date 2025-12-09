// minus.cpp
#include <systemc>
using namespace sc_core;
using namespace sc_dt;

#include "../include/data_type.hpp"

struct minus : public sc_module {
    sc_in<bool>      clk;
    sc_in<bool>      rst;
    sc_in<mag_t>     mag_in;     // |γ(k)|
    sc_in<phi_t>     phi_in;     // Φ_L(k)
    sc_in<rho_t>     rho_in;     // ρ
    sc_out<lambda_t> lambda_out; // Λ(k)

    static const int N_DELAY = 2;

    lambda_t delay_line[N_DELAY];

    SC_HAS_PROCESS(minus);
    minus(sc_module_name n) : sc_module(n) {
        SC_CTHREAD(proc, clk.pos());
        reset_signal_is(rst, true);
    }

    void proc() {
        // reset
        lambda_out.write(0);
        wait();
        while (true) {
            mag_t mag  = mag_in.read();
            phi_t phi  = phi_in.read();
            rho_t rho  = rho_in.read();

            lambda_t lambda = mag - rho * phi;

            for (int i = N_DELAY - 1; i > 0; --i)
                delay_line[i] = delay_line[i - 1];
  
            delay_line[0] = lambda;

            lambda_out.write(delay_line[N_DELAY - 1]);
            
            wait();
        }
    }
};
