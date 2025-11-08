// mag.cpp — Piecewise AMBM |x + j y| with 1% target error
#include <systemc>
#include <cmath>
#include "data_type.hpp"
using namespace sc_core;


static inline mag_t ambm_pw_hypot_fx(gamma_t x, gamma_t y) {
  gamma_t ax = std::fabs(x);
  gamma_t ay = std::fabs(y);

  if (ax < ay) std::swap(ax, ay);   // ax = Max, ay = Min
  if (ax == 0.0) return 0.0;        // both zero

  const double r = ay / ax;         // in [0,1]

  double alpha, beta;

  // r thresholds: tan(k * π/32), k = 1..7
  if (r < 0.09849140335716425) {            // [0, π/32)
    alpha = 1.2012;  beta = 0.0246;
  } else if (r < 0.19891236737965800) {     // [π/32, π/16)
    alpha = 0.994;  beta = 0.1226;
  } else if (r < 0.30334668360734240) {     // [π/16, 3π/32)
    alpha = 0.9772;  beta = 0.2194;
  } else if (r < 0.41421356237309503) {     // [3π/32, π/8)
    alpha = 0.951;  beta = 0.3142;
  } else if (r < 0.53451113595079155) {     // [π/8, 5π/32)
    alpha = 0.9156;  beta = 0.4059;
  } else if (r < 0.66817863791929892) {     // [5π/32, 3π/16)
    alpha = 0.8744;  beta = 0.4936;
  } else if (r < 0.78) {
    alpha = 0.8178;  beta = 0.5767;
  } else if (r < 0.82067879082866016) {     // [3π/16, 7π/32)
    alpha = 0.8188;  beta = 0.5767;
  } else {                                  // [7π/32, π/4]
    alpha = 0.7084;  beta = 0.7042;
  }

  mag_t z = alpha * ax + beta * ay;
  // std::cout << "alpha=" << alpha << " ax=" << ax << " beta=" << beta << " ay=" << ay << " z=" << z << " r=" << r << std::endl;

  return z;
}

struct mag : public sc_module {
  sc_in<gamma_t> gm_in_real;
  sc_in<gamma_t> gm_in_imag;
  sc_out<mag_t>  mag_out;

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