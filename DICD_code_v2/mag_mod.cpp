// mag_mod.cpp
#include <systemc>
using namespace sc_core;
using namespace sc_dt;

// ====== 型別定義 ======
typedef double   fx_gamma_t;   // input: gm_in_real / gm_in_imag
typedef double   fx_mag_t;     // output: mag_out

// ======================= AMBM |x + j y| =======================
static inline fx_mag_t ambm_hypot_fx(fx_gamma_t x, fx_gamma_t y) {
  fx_gamma_t ax = (x >= 0) ? x : -x;
  fx_gamma_t ay = (y >= 0) ? y : -y;
  if (ax < ay) { fx_gamma_t t = ax; ax = ay; ay = t; } // ax = max, ay = min

  // 低誤差係數
  const double alpha = 0.960433870103;
  const double beta  = 0.397824734759;

  return fx_mag_t(alpha * (double)ax + beta * (double)ay);
}

// =========================== module ===========================
struct mag_mod : public sc_module {
  // === 介面 ===
  sc_in<fx_gamma_t> gm_in_real;
  sc_in<fx_gamma_t> gm_in_imag;
  sc_out<fx_mag_t>  mag_out;

  SC_HAS_PROCESS(mag_mod);

  mag_mod(sc_module_name n) : sc_module(n) {
    SC_METHOD(proc);
    sensitive << gm_in_real << gm_in_imag; // 只要輸入改變即觸發
    dont_initialize(); // 可省略
  }

  void proc() {
    fx_gamma_t xr = gm_in_real.read();
    fx_gamma_t xi = gm_in_imag.read();
    fx_mag_t mag = ambm_hypot_fx(xr, xi);
    mag_out.write(mag);
  }
};