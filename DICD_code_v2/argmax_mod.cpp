#include <systemc>
#include <algorithm>  // for std::max_element, std::distance
using namespace sc_core;
using namespace sc_dt;

typedef double fx_lambda_t;   // λ(k)
typedef short  ux_theta_t;    // 8-bit index (0–255)

// =============================================================
// argmax_mod (Sliding-Window 256 + 8-cycle delay)
// 維持最近 256 筆 λ(k)，每次新 λ 進來：
//   → 插入到 buf[0]
//   → 其他元素往後移一格
//   → 丟掉最舊的
//   → 找出最大值的 index
//   → 延遲 8 個 clock 後輸出
// =============================================================
struct argmax_mod : public sc_module {
  sc_in<bool>        clk;
  sc_in<bool>        rst;          // active-low reset
  sc_in<fx_lambda_t> lambda_in;    // Λ(k)
  sc_out<ux_theta_t> theta_out;    // 最大值所在 index (0–255)

  static const int N = 256;        // buffer 長度
  static const int N_DELAY = 8;    // 輸出延遲 8 拍

  fx_lambda_t buf[N];
  ux_theta_t  delay_line[N_DELAY];

  SC_HAS_PROCESS(argmax_mod);
  argmax_mod(sc_module_name n) : sc_module(n) {
    SC_CTHREAD(proc, clk.pos());
    reset_signal_is(rst, false);
  }

  void proc() {
    // === 初始化 ===
    for (int i = 0; i < N; ++i) buf[i] = 0.0;
    for (int i = 0; i < N_DELAY; ++i) delay_line[i] = 0;
    theta_out.write(0);
    wait();

    while (true) {
      if (!rst.read()) {
        for (int i = 0; i < N; ++i) buf[i] = 0.0;
        for (int i = 0; i < N_DELAY; ++i) delay_line[i] = 0;
        theta_out.write(0);
      } else {
        fx_lambda_t new_val = lambda_in.read();

        // (1) 整個陣列往後移一格
        for (int i = N - 1; i > 0; --i)
          buf[i] = buf[i - 1];
        buf[0] = new_val;

        // (2) 尋找最大值索引
        auto max_it = std::max_element(buf, buf + N);
        int idx = std::distance(buf, max_it); // 回傳最大值的 index

        // (3) 延遲線更新
        for (int i = N_DELAY - 1; i > 0; --i)
          delay_line[i] = delay_line[i - 1];
        delay_line[0] = (ux_theta_t)(idx & 0xFF);

        // (4) 輸出延遲 8 拍的結果
        theta_out.write(delay_line[N_DELAY - 1]);
      }

      wait(); // 下一個 clock
    }
  }
};

