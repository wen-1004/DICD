#include <systemc>
#include <cmath>
#include <algorithm>
using namespace sc_core;
using namespace sc_dt;

typedef double fx_phase_t;   // 相位 (rad)
typedef short  ux_theta_t;   // 0..255
typedef double fx_eps_t;     // ε

// ================================================================
// select_eps: Sliding-Window 256（與 argmax 同步規則）
// - 每次有新 angle_in：把它寫到 buf[0]，其餘元素整體右移一格，丟掉最舊的 buf[255]
// - 以輸入的 theta_in（0..255）直接索引當前緩衝區，取出 angle 計算 ε = angle / (2π)
// - 無 clk/rst，SC_METHOD 組合邏輯
// ================================================================
struct select_eps : public sc_module {
  sc_in<fx_phase_t>  angle_in;   // 新角度（每拍來一筆）
  sc_in<ux_theta_t>  theta_in;   // 要取的索引（0=最新）
  sc_out<fx_eps_t>   eps_out;    // ε 輸出

  static const int BUF_LEN = 256;
  fx_phase_t angle_buf[BUF_LEN];

  SC_HAS_PROCESS(select_eps);
  select_eps(sc_module_name n) : sc_module(n) {
    // 初始化 buffer
    for (int i = 0; i < BUF_LEN; ++i) angle_buf[i] = 0.0;

    SC_METHOD(proc);
    sensitive << angle_in << theta_in;
    dont_initialize();
  }

  void proc() {
    const double TWO_PI = 6.28318530717958647692;

    // --- 1) 寫入最新 angle 到 buf[0]，整體右移，丟掉最舊 ---
    fx_phase_t ang_new = angle_in.read();
    for (int i = BUF_LEN - 1; i > 0; --i)
      angle_buf[i] = angle_buf[i - 1];
    angle_buf[0] = ang_new;

    // --- 2) 用 theta 直接索引目前滑動視窗 ---
    ux_theta_t th = 255 - theta_in.read();
    int idx = (int)th & 0xFF;           // 保險起見取 0..255
    fx_phase_t sel_ang = angle_buf[idx];

    // --- 3) 計算 ε（依你最新說法：ε = angle / (2π)；若需負號再改）---
    fx_eps_t eps = sel_ang / TWO_PI;

    // --- 4) 正規化到 [-0.5, 0.5) ---
    while (eps <= -0.5) eps += 1.0;
    while (eps >   0.5) eps -= 1.0;

    eps_out.write(eps);
  }
};

