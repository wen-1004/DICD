#include <systemc>
using namespace sc_core;
using namespace sc_dt;

typedef double fx_lambda_t;   // λ(k)
typedef short ux_theta_t;    // 8-bit 輸出索引 (0~255)

// =========================== argmax_mod ===========================
// 累計最大 λ 與 index，每次比較新值，延遲 N=8 拍後輸出
struct argmax_mod : public sc_module {
  sc_in<bool>        clk;
  sc_in<bool>        rst;          // active-low
  sc_in<fx_lambda_t> lambda_in;    // λ(k)
  sc_out<ux_theta_t> theta_out;    // θ (8-bit index)

  // --- delay pipeline 參數 ---
  static const int N_DELAY = 8;

  SC_HAS_PROCESS(argmax_mod);
  argmax_mod(sc_module_name n) : sc_module(n) {
    SC_CTHREAD(proc, clk.pos());
    reset_signal_is(rst, false);
  }

  void proc() {
    fx_lambda_t best_val = -1e30;
    ux_theta_t  best_idx = 0;
    ux_theta_t  delay_buf[N_DELAY] = {0};

    int k = 0;
    theta_out.write(0);
    wait();

    while (true) {
      if (!rst.read()) {
        best_val = -1e30;
        best_idx = 0;
        for (int i = 0; i < N_DELAY; ++i) delay_buf[i] = 0;
        k = 0;
        theta_out.write(0);
      } else {
        fx_lambda_t new_val = lambda_in.read();

        // --- 比較是否更新最大值 ---
        if (new_val > best_val) {
          best_val = new_val;
          best_idx = (ux_theta_t)(k & 0xFF); // 限制 8-bit
        }

        // --- delay pipeline ---
        for (int i = N_DELAY - 1; i > 0; --i)
          delay_buf[i] = delay_buf[i - 1];
        delay_buf[0] = best_idx;

        // --- 延遲後輸出 ---
        theta_out.write(delay_buf[N_DELAY - 1]);

        k++;
      }
      wait();
    }
  }
};
