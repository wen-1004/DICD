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

    ratio_t r = ay / ax;         // in [0,1]

    const ratio_t segment[8] = {
        ratio_t("0b0.00011001"), // 25/256  ≈ 0.09765625  (orig 0.0984914033)
        ratio_t("0b0.00110011"), // 51/256  ≈ 0.19921875  (orig 0.1989123674)
        ratio_t("0b0.01001110"), // 78/256  ≈ 0.30468750  (orig 0.3033466836)
        ratio_t("0b0.01101010"), // 106/256 ≈ 0.41406250  (orig 0.4142135624)
        ratio_t("0b0.10001001"), // 137/256 ≈ 0.53515625  (orig 0.5345111360)
        ratio_t("0b0.10101011"), // 171/256 ≈ 0.66796875  (orig 0.6681786379)
        ratio_t("0b0.11001000"), // 200/256 ≈ 0.78125000  (orig 0.7800000000)
        ratio_t("0b0.11010010")  // 210/256 ≈ 0.82031250  (orig 0.8206787908)
    };

    static const ambm_t alpha_lut[9] = {
        ambm_t("0b1.0011001110"), // 1.201171875 ≈ 1.2012
        ambm_t("0b0.1111111010"), // 0.994140625 ≈ 0.994
        ambm_t("0b0.1111101001"), // 0.9775390625 ≈ 0.9772
        ambm_t("0b0.1111001110"), // 0.951171875 ≈ 0.951
        ambm_t("0b0.1110101010"), // 0.916015625 ≈ 0.9156
        ambm_t("0b0.1101111111"), // 0.8740234375 ≈ 0.8744
        ambm_t("0b0.1101000101"), // 0.8173828125 ≈ 0.8178
        ambm_t("0b0.1101000110"), // 0.818359375  ≈ 0.8188
        ambm_t("0b0.1011010101")  // 0.7080078125 ≈ 0.7084
    };

    static const ambm_t beta_lut[9] = {
        ambm_t("0b0.0000011001"), // 0.0244140625 ≈ 0.0246
        ambm_t("0b0.0001111110"), // 0.123046875  ≈ 0.1226
        ambm_t("0b0.0011100001"), // 0.2197265625 ≈ 0.2194
        ambm_t("0b0.0101000010"), // 0.314453125  ≈ 0.3142
        ambm_t("0b0.0110100000"), // 0.40625      ≈ 0.4059
        ambm_t("0b0.0111111001"), // 0.4931640625 ≈ 0.4936
        ambm_t("0b0.1001001111"), // 0.5771484375 ≈ 0.5767
        ambm_t("0b0.1001001111"), // 0.5771484375 ≈ 0.5767 (same segment)
        ambm_t("0b0.1011010001")  // 0.7041015625 ≈ 0.7042
    };

    ambm_t alpha, beta;

    // r thresholds: tan(k * π/32), k = 1..7
    if (r < segment[0]) {            // [0, π/32)
        alpha = alpha_lut[0];  beta = beta_lut[0];
    } else if (r < segment[1]) {     // [π/32, π/16)
        alpha = alpha_lut[1];  beta = beta_lut[1];
    } else if (r < segment[2]) {     // [π/16, 3π/32)
        alpha = alpha_lut[2];  beta = beta_lut[2];
    } else if (r < segment[3]) {     // [3π/32, π/8)
        alpha = alpha_lut[3];  beta = beta_lut[3];
    } else if (r < segment[4]) {     // [π/8, 5π/32)
        alpha = alpha_lut[4];  beta = beta_lut[4];
    } else if (r < segment[5]) {     // [5π/32, 3π/16)
        alpha = alpha_lut[5];  beta = beta_lut[5];
    } else if (r < segment[6]) {
        alpha = alpha_lut[6];  beta = beta_lut[6];
    } else if (r < segment[7]) {     // [3π/16, 7π/32)
        alpha = alpha_lut[7];  beta = beta_lut[7];
    } else {                         // [7π/32, π/4]
        alpha = alpha_lut[8];  beta = beta_lut[8];
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