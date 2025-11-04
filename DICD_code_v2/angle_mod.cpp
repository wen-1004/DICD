// angle_mod.cpp
#include <systemc>
#include <cmath>
using namespace sc_core;
using namespace sc_dt;

// ====== 定點格式定義 ======
typedef double   fx_gamma_t;   // 輸入 gm_in_real, gm_in_imag
typedef double  fx_phase_t;   // 輸出 ang_out（弧度制）

// ======================= 定點 CORDIC（vectoring）求相位 ======================= 
// 傳回 atan2(y, x) [rad] 以定點格式 fx_phase_t
static inline fx_phase_t cordic_atan2_fx(fx_gamma_t y_in, fx_gamma_t x_in) {
  const int ITERS = 16; // 可依精度需求調大
  static const double atan_lut_d[32] = {
    7.85398163397448e-01, 4.63647609000806e-01, 2.44978663126864e-01,
    1.24354994546761e-01, 6.24188099959573e-02, 3.12398334302683e-02,
    1.56237286204769e-02, 7.81234106010111e-03, 3.90623013196697e-03,
    1.95312251647882e-03, 9.76562189559319e-04, 4.88281211194898e-04,
    2.44140620149362e-04, 1.22070311893670e-04, 6.10351561742088e-05,
    3.05175781155261e-05
  };
  fx_phase_t atan_lut[ITERS];  
  for (int i=0; i<ITERS; ++i) atan_lut[i] = fx_phase_t(atan_lut_d[i]);

  fx_gamma_t x = x_in;
  fx_gamma_t y = y_in;
  fx_phase_t z = 0.0;

  // quadrant 調整：移動到 x >= 0 半平面
  if (x < 0) {
    if (y >= 0) {
      fx_gamma_t xt =  y; fx_gamma_t yt = -x; 
      x = xt; y = yt; 
      z =  fx_phase_t(M_PI/2.0);
    } else {
      fx_gamma_t xt = -y; fx_gamma_t yt =  x; 
      x = xt; y = yt; 
      z = -fx_phase_t(M_PI/2.0);
    }
  }

  // vectoring：讓 y -> 0
  for (int i = 0; i < ITERS; ++i) {
    fx_gamma_t x_shift = x / (1 << i);
    fx_gamma_t y_shift = y / (1 << i);
    if (y >= 0) { x = x + y_shift; y = y - x_shift; z = z + atan_lut[i]; }
    else        { x = x - y_shift; y = y + x_shift; z = z - atan_lut[i]; }
  }
  return z; // 近似 atan2(y_in, x_in)
}

// =========================== angle_mod 模組 ===========================
struct angle_mod : public sc_module {
  // === 介面 ===
  sc_in<bool>       clk;
  sc_in<bool>       rst;        // active-low
  sc_in<fx_gamma_t> gm_in_real;
  sc_in<fx_gamma_t> gm_in_imag;
  sc_out<fx_phase_t> ang_out;

  // === delay 參數 ===
  int N_DELAY = 8 ; // 可自訂的延遲拍數

  // === constructor ===
  SC_HAS_PROCESS(angle_mod);
  angle_mod(sc_module_name n, int delay_cycles = 1)
  : sc_module(n), N_DELAY(delay_cycles) {
    SC_CTHREAD(proc, clk.pos());
    reset_signal_is(rst, false);
  }

  // === 主行程 ===
  void proc() {
    std::vector<fx_phase_t> delay_line(N_DELAY, 0);

    // reset
    ang_out.write(0);
    wait();

    while (true) {
      fx_gamma_t xr = gm_in_real.read();
      fx_gamma_t xi = gm_in_imag.read();

      fx_phase_t phase_now = cordic_atan2_fx(xi, xr);

      // 輸出最舊的一筆 (N_DELAY 拍前的資料)
      ang_out.write(delay_line.back());

      // 移動 delay line（往後推一格）
      for (int i = N_DELAY - 1; i > 0; --i)
        delay_line[i] = delay_line[i - 1];

      // 放入最新的計算值
      delay_line[0] = phase_now;

      wait(); // 下一拍
    }
  }
};
