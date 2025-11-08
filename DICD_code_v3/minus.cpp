// minus.cpp
#include <systemc>
using namespace sc_core;
using namespace sc_dt;

// ====== 型別定義（暫時全用 double） ======
typedef double fx_mag_t;     // |γ(k)|
typedef double fx_phase_t;   // Φ_L(k)
typedef double fx_rho_t;     // ρ
typedef double fx_lambda_t;  // Λ(k)

// =========================== module ===========================
struct minus : public sc_module {
  // === 介面 ===
  sc_in<fx_mag_t>    mag_in;     // |γ(k)|
  sc_in<fx_phase_t>  phi_in;     // Φ_L(k)
  sc_in<fx_rho_t>    rho_in;     // ρ
  sc_out<fx_lambda_t> lambda_out; // Λ(k)

  SC_HAS_PROCESS(minus);

  minus(sc_module_name n) : sc_module(n) {
    SC_METHOD(proc);
    sensitive << mag_in << phi_in << rho_in; // 組合邏輯
    dont_initialize();
  }

  void proc() {
    fx_mag_t   mag  = mag_in.read();
    fx_phase_t phiL = phi_in.read();
    fx_rho_t   rho  = rho_in.read();

    fx_lambda_t lambda = mag - rho * phiL;
    lambda_out.write(lambda);
  }
};
