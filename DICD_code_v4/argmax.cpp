#include <systemc>
#include <algorithm>  // std::max_element, std::distance
#include <iostream>
#include <iomanip>
#include "data_type.hpp"

using namespace sc_core;
using namespace sc_dt;


// =============================================================
// argmax_mod (Sliding-Window 256 + 8-cycle delay)
// 維持最近 256 筆 λ(k)，每次新 λ 進來：
//   → 插入到 buf[0]
//   → 其他元素往後移一格
//   → 丟掉最舊的
//   → 找出最大值的 index
//   → 延遲 8 個 clock 後輸出
// 並在每拍列印被選 index 以及其鄰居的值（例如 119, 120, 121）。
// =============================================================
struct argmax : public sc_module {
  sc_in<bool>        clk;
  sc_in<bool>        rst;          // active-low reset
  sc_in<lambda_t> lambda_in;    // Λ(k)
  sc_out<theta_t> theta_out;    // 最大值所在 index (0–255)

  static const int N = 256;        // buffer 長度
  static const int N_DELAY = 8;    // 輸出延遲 8 拍

  double buf[N];
  theta_t delay_line[N_DELAY];

  SC_HAS_PROCESS(argmax);
  argmax(sc_module_name n) : sc_module(n) {
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
        double new_val = lambda_in.read();

        for (int i = N - 1; i > 0; --i)
          buf[i] = buf[i - 1];
        buf[0] = new_val;

        int pos = 0;
        double maxv = buf[0];
        for (int i = 1; i < N; ++i) {
          if (buf[i] > maxv) {
            maxv = buf[i];
            pos = i;
          }
        }
//        for (int i = 133; i < 137; ++i) {
//          std::cout << "buf[" << i << "] = " << buf[i] << " ";
//          std::cout << std::endl;
//        }
//        std::cout << "pos=" << pos << " maxv=" << maxv << std::endl;
        
        int idx = 255 - pos;

        for (int i = N_DELAY - 1; i > 0; --i)
          delay_line[i] = delay_line[i - 1];
        delay_line[0] = static_cast<theta_t>(idx & 0xFF);


        // (4) 輸出延遲 8 拍的結果
        theta_out.write(delay_line[N_DELAY - 1]);
      }

      wait(); // 下一個 clock
    }
  }
};
