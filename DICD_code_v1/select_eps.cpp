#include <systemc>
#include <cmath>
using namespace sc_core;
using namespace sc_dt;

typedef double fx_phase_t;   // 相位 (rad)
typedef short ux_theta_t;   // 8-bit index
typedef double fx_eps_t;     // ε 輸出

// ================================================================
// select_eps: 組合模組
// 每次 angle_in/θ_in 變化時，立即輸出對應 ε = -Φ / (2π)
// ================================================================
struct select_eps : public sc_module {
  sc_in<fx_phase_t>  angle_in;   // 連續輸入角度
  sc_in<ux_theta_t>  theta_in;   // 輸入索引
  sc_out<fx_eps_t>   eps_out;    // 輸出 ε

  static const int BUF_LEN = 256;
  fx_phase_t angle_buf[BUF_LEN];
  int wr_ptr;

  SC_HAS_PROCESS(select_eps);
  select_eps(sc_module_name n) : sc_module(n) {
    wr_ptr = 0;
    for (int i = 0; i < BUF_LEN; ++i)
      angle_buf[i] = 0.0;

    // 使用方法：每當 angle_in 或 theta_in 改變時，更新輸出
    SC_METHOD(proc);
    sensitive << angle_in << theta_in;
    dont_initialize();
  }

  void proc() {
    const double TWO_PI = 6.28318530717958647692;

    // 寫入最新角度到 buffer
    fx_phase_t ang = angle_in.read();
    angle_buf[wr_ptr] = ang;
    wr_ptr = (wr_ptr + 1) % BUF_LEN;

    // 讀出 θ 對應角度
    ux_theta_t th = theta_in.read();
    fx_phase_t sel_ang = angle_buf[th & 0xFF];

    // 計算 ε = -Φ / 2π
    fx_eps_t eps = -sel_ang / TWO_PI;

    // 正規化到 [-0.5, 0.5)
    while (eps <= -0.5) eps += 1.0;
    while (eps >   0.5) eps -= 1.0;

    eps_out.write(eps);
  }
};
