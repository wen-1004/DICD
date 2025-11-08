// mag.cpp — Piecewise AMBM |x + j y| with 1% target error
#include <systemc>
#include <cmath>
using namespace sc_core;

typedef double fx_gamma_t;   // inputs: gm_in_real / gm_in_imag
typedef double fx_mag_t;     // output: mag_out

// Piecewise AMBM: if (Min/Max < 0.4142135) use (α,β)=(0.99,0.197); else (0.84,0.561)
// Includes a clamp so the approximation never underestimates Max near axes.
static inline fx_mag_t ambm_pw_hypot_fx(fx_gamma_t x, fx_gamma_t y) {
  double ax = std::fabs((double)x), ay = std::fabs((double)y);
  if (ax < ay) std::swap(ax, ay);              // ax = Max, ay = Min
  if (ax == 0.0) return 0.0;                   // both zero

  const double T = 0.4142135;                  // threshold on Min/Max
  const double r = ay / ax;

  double alpha, beta;
  if (r < T) { alpha = 0.99; beta = 0.197; }   // segment 0
  else       { alpha = 0.80; beta = 0.590; }   // segment 1

  double z = alpha * ax + beta * ay;

  // Clamp to avoid |z| < Max (common AMBM pitfall near axes)
  if (z < ax) z = ax;
  return (fx_mag_t)z;
}

struct mag : public sc_module {
  sc_in<fx_gamma_t> gm_in_real;
  sc_in<fx_gamma_t> gm_in_imag;
  sc_out<fx_mag_t>  mag_out;

  SC_HAS_PROCESS(mag);
  mag(sc_module_name n) : sc_module(n) {
    SC_METHOD(proc);
    sensitive << gm_in_real << gm_in_imag;
    dont_initialize();
  }

  void proc() {
    mag_out.write(ambm_pw_hypot_fx(gm_in_real.read(), gm_in_imag.read()));
  }
};
