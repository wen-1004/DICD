// minus.cpp
#include <systemc>
#include "data_type.hpp"
using namespace sc_core;
using namespace sc_dt;

struct minus : public sc_module {
    sc_in<mag_t>    mag_in;     // |γ(k)|
    sc_in<phi_t>    phi_in;     // Φ_L(k)
    sc_in<rho_t>    rho_in;     // ρ
    sc_out<lambda_t> lambda_out; // Λ(k)

    SC_HAS_PROCESS(minus);

    minus(sc_module_name n) : sc_module(n) {
        SC_METHOD(proc);
        sensitive << mag_in << phi_in << rho_in;
        dont_initialize();
    }

    void proc() {
        mag_t mag  = mag_in.read();
        phi_t phi = phi_in.read();
        rho_t rho  = rho_in.read();
  
        lambda_t lambda = mag - rho * phi;
        lambda_out.write(lambda);
    }
};
