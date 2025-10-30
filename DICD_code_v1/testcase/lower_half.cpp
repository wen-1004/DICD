#define SC-ALLOW_DEPRECATED_IEEE_API
#include <systemc>
#include <cmath>
using namespace sc_core;
using namespace sc_dt;
using namespace std;

// ======================= 組態 =======================
static constexpr int N_WINDOW = 256; // 第三顆模組的視窗長度


// ======================= 型別定義 =======================
// 說明：括號內對應 s(I.F) / u(I.F) 期望格式
typedef double   fx_gamma_t;    // γ_re / γ_im（來自 r(k)r*(k+N) 的單點值，保留餘裕）
typedef double  fx_mag_t;      // |γ|（幅度）                         ~ s(14.10)
typedef double  fx_phi_t;      // Φ_L（窗口能量和，可能較大）            ~ s(20.12)
typedef double    fx_rho_t;      // ρ ∈ [0,1]                           s(1.7)
typedef double   fx_phase_t;    // 相位（rad，-π~+π）                     s(3.17)  夠用
typedef double  fx_lambda_t;   // Λ = |γ| - ρΦ_L                       s(20.12)
typedef double   fx_eps_t;      // ε（Normalized CFO）                   s(1.20)  <<要求
typedef sc_uint<8>       ux_theta_t;    // θ（樣本偏移量，整數）                  u(8.0)   <<要求


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


// ======================= 定點 CORDIC（vectoring）求相位 =======================
// 傳回 atan2(y, x) [rad] 以定點格式 fx_phase_t
static inline fx_phase_t cordic_atan2_fx(fx_gamma_t y_in, fx_gamma_t x_in) {
  const int ITERS = 16; // 可依精度需求調大
  // 角度查表（rad）
  static const double atan_lut_d[32] = {
    7.85398163397448e-01, 4.63647609000806e-01, 2.44978663126864e-01,
    1.24354994546761e-01, 6.24188099959573e-02, 3.12398334302683e-02,
    1.56237286204769e-02, 7.81234106010111e-03, 3.90623013196697e-03,
    1.95312251647882e-03, 9.76562189559319e-04, 4.88281211194898e-04,
    2.44140620149362e-04, 1.22070311893670e-04, 6.10351561742088e-05,
    3.05175781155261e-05
  };
  fx_phase_t atan_lut[ITERS];  for (int i=0;i<ITERS;++i) atan_lut[i] = fx_phase_t(atan_lut_d[i]);


  fx_gamma_t x = x_in;
  fx_gamma_t y = y_in;
  fx_phase_t z = 0.0;


  // quadrant 調整，先把向量搬到 x>=0 半平面（簡化迴圈）
  if (x < 0) {
    if (y >= 0) { fx_gamma_t xt =  y; fx_gamma_t yt = -x; x = xt; y = yt; z =  fx_phase_t(M_PI/2.0); }
    else        { fx_gamma_t xt = -y; fx_gamma_t yt =  x; x = xt; y = yt; z = -fx_phase_t(M_PI/2.0); }
  }


  // vectoring：讓 y -> 0，同時累積角度
  for (int i = 0; i < ITERS; ++i) {
    fx_gamma_t x_shift = x / (1 << i);
    fx_gamma_t y_shift = y / (1 << i);
    if (y >= 0) { x = x + y_shift; y = y - x_shift; z = z + atan_lut[i]; }
    else        { x = x - y_shift; y = y + x_shift; z = z - atan_lut[i]; }
  }
  return z; // 近似 atan2(y_in, x_in)
}

// =====================================================================
// 1) FeatureExtract：輸入 γ_re/γ_im，輸出 |γ|（AMBM）與 phase（rad）
// clk : sc_in<bool>; reset: 同步低態有效
// =====================================================================
struct FeatureExtract : public sc_module {
  sc_in<bool>    i_clk, i_rst;
  sc_in<fx_gamma_t> i_gamma_re, i_gamma_im;
  sc_in<fx_phi_t> i_phi;

  sc_out<fx_mag_t>  o_magnitude;
  sc_out<fx_phase_t> o_phase;
  sc_out<bool>       o_fe_valid;
  sc_out< ux_theta_t> o_fe_k;
  sc_out<fx_phi_t> o_fe_phi;
  bool last_clk;
  ux_theta_t k=0;
  bool prime = false;

  SC_HAS_PROCESS(FeatureExtract);
  FeatureExtract(sc_module_name n) : sc_module(n), last_clk(false) {
    SC_METHOD(proc);
    sensitive << i_clk;
    dont_initialize();
  }

  void proc() {
    if (!i_rst.read()) {
      o_magnitude.write(0.0);
      o_phase.write(0.0);
      o_fe_valid.write(false);
      o_fe_k.write(0);
      o_fe_phi.write(0.0);
      last_clk = i_clk.read();
      k=0;
      prime = false;

      return;
    }
    bool cur = i_clk.read();
    if (!last_clk && cur) { // rising edge
      fx_gamma_t gr = i_gamma_re.read();
      fx_gamma_t gi = i_gamma_im.read();
      o_magnitude.write( ambm_hypot_fx(gr, gi) );
      o_phase.write( cordic_atan2_fx(gi, gr) ); // rad（定點 CORDIC）
      o_fe_phi.write ( i_phi.read());
      o_fe_k = k;
      o_fe_valid.write(true);

    }
    last_clk = cur;
    k++;
    prime = true;
  }
};

// =====================================================================
// 2) MetricCalc：輸入 ρ、Φ_L、|γ|、phase(rad)；輸出 Λ 與 phase（透傳對齊）
// Λ = |γ| - ρ·Φ_L  （公式(11)）
// =====================================================================
struct MetricCalc : public sc_module {
  sc_in<bool>    i_clk, i_rst;
  sc_in<fx_rho_t>    i_rho;       // s(1.7)
  sc_in<fx_phi_t>    i_phi_L;     // 視窗能量和
  sc_in<fx_mag_t>    i_magnitude; // |γ|
  sc_in<fx_phase_t>  i_phase;     // rad
  sc_in<bool>        i_fe_valid;
  sc_in< ux_theta_t> i_fe_k;


  sc_out<fx_lambda_t> o_lambda;   // Λ
  sc_out<fx_phase_t>  o_phase;    // rad（透傳）
  sc_out<bool>        o_mc_valid;
  sc_out< ux_theta_t> o_mc_k;


  bool last_clk;
  fx_phi_t   phi_D = 0 ;


  SC_HAS_PROCESS(MetricCalc);
  MetricCalc(sc_module_name n) : sc_module(n), last_clk(false) {
    SC_METHOD(proc);
    sensitive << i_clk;
    dont_initialize();
  }

  void proc() {
    if (!i_rst.read()) {
      o_lambda.write(0.0);
      o_phase.write(0.0);
      o_mc_k.write(0);
      o_mc_valid.write(false);
      last_clk = i_clk.read();
      return;
    }
    bool cur = i_clk.read();
    if (!last_clk && cur) { // rising edge
      bool       fev       = i_fe_valid.read();
      fx_mag_t   gamma_abs = i_magnitude.read();  // |γ(θ)|
      fx_phi_t   phi_val   = i_phi_L.read();      // Φ(θ)  (由前一模組或 TB 提供)
      fx_rho_t   rho       = i_rho.read();
      ux_theta_t km        = i_fe_k.read();
      fx_lambda_t lambda = fx_lambda_t( gamma_abs - rho * phi_val );

      if (fev){
        // 輸出 Λ(θ) 與相位（相位只 passthru 給後段做 (13)）

      o_lambda.write(lambda);
      o_phase.write(i_phase.read());
      o_mc_k.write(km);

      o_mc_valid.write(true);
      }
    }
    last_clk = cur;
  }
};

// =====================================================================
// 3) PeakHold：輸入 Λ 與 phase，維持最近 N=255 筆中的最大 Λ
//    只有當已收到 ≥ N 筆時 o_valid=1 才表示輸出有效
//    輸出：phase_hat（rad）、eps_hat（s(1.20) = -phase_hat/(2π)）、theta_hat（u8）
//    θ 的意義：時間偏移量（以「樣本數」表示，整數無誤差；外部若需秒數，可乘 Ts）
// =====================================================================

struct PeakHold : public sc_core::sc_module {
  // --- 參數 ---
  static constexpr int    WIN     = 256; // 視窗長度 = N
  static constexpr double PI      = 3.14159265358979323846;
  static constexpr double TWO_PI  = 6.28318530717958647692;

  // --- 介面 ---
  sc_core::sc_in<bool>        i_clk;
  sc_core::sc_in<bool>        i_rst;      // active-low reset
  sc_core::sc_in<bool>        i_mc_valid;
  sc_core::sc_in<fx_lambda_t> i_lambda;   // Λ(k)
  sc_core::sc_in<fx_phase_t>  i_phase;    // ∠γ(k) (rad)
  sc_core::sc_in<ux_theta_t>  i_mc_k;


  sc_core::sc_out<bool>       o_valid;
  sc_core::sc_out<fx_phase_t> o_phase_hat;
  sc_core::sc_out<fx_eps_t>   o_eps_hat;
  sc_core::sc_out<ux_theta_t> o_theta_hat;
  sc_core::sc_out<ux_theta_t> o_ph_k;

  // --- 建構 ---
  SC_HAS_PROCESS(PeakHold);
  PeakHold(sc_core::sc_module_name n) : sc_module(n) {
    SC_CTHREAD(proc, i_clk.pos());
    reset_signal_is(i_rst, false);
  }

  // --- 工具：角度 / ε 範圍正規化 ---
  static double norm_to_pm_pi(double a) {
    while (a <= -PI) a += TWO_PI;
    while (a >   PI) a -= TWO_PI;
    return a;
  }
  static double norm_eps_pm_half(double e) {
    while (e <= -0.5) e += 1.0;
    while (e >   0.5) e -= 1.0;
    return e;
  }

  // --- 內部緩衝 ---
  fx_lambda_t buf_lambda[WIN];
  fx_phase_t  buf_phase [WIN];
  int         wr_idx;    // 寫入索引 (0..WIN-1)
  int         filled;    // 已填入筆數 (0..WIN)
  ux_theta_t  theta_pre ;

  // --- 主流程 ---
  void proc() {
    // Reset outputs
    o_valid.write(false);
    o_phase_hat.write(0.0);
    o_eps_hat.write(0.0);
    o_theta_hat.write(0);
    o_ph_k.write(0);

    // Reset state
    wr_idx = 0;
    filled = 0;

    wait(); // 等 reset 釋放

    while (true) {
      if (!i_rst.read()) {
        // 硬體 reset
        wr_idx = 0;
        filled = 0;

        o_valid.write(false);
        o_phase_hat.write(0.0);
        o_eps_hat.write(0.0);
        o_theta_hat.write(0);
        o_ph_k.write(0);
      } else {
        // 讀入當拍資料
        fx_lambda_t Lk = i_lambda.read();
        fx_phase_t  Pk = i_phase.read();
        ux_theta_t  kp = i_mc_k.read();
        bool       mcv = i_mc_valid.read();




        // 寫入環形緩衝
        buf_lambda[wr_idx] = Lk;
        buf_phase [wr_idx] = Pk;
        wr_idx  =(wr_idx + 1) % WIN ;

        if (filled < WIN) filled++;
        // 在「目前視窗」(最近 filled 筆，最多 WIN) 內找 argmax Λ
        // 這裡每拍重新掃描 WIN 次，WIN=256 成本可接受；要更快可做遞迴最大值結構
        double bestL  = -1e300;
        int    best_i = 0;      // 視窗內位置 0..filled-1（0 表示最舊，filled-1 表示最新）
        int    br = (wr_idx - filled + WIN) %WIN;

        for (int i = 0; i < filled; ++i) {
          int idx = (br + i) % WIN;
          double Li = (double)buf_lambda[idx];
          if (Li > bestL) {
            bestL  = Li;
            best_i = i;
          }
     // 對應的真正陣列索引
        int best_idx_ring = (br + best_i) % WIN;
        fx_phase_t best_phase = buf_phase[best_idx_ring];

        // 你要的 theta_hat 定義成「視窗內索引」0..255（可直接用 best_i）
        // 若你希望它代表從 0..N-1 對應到 OFDM 取樣偏移，也是 OK


        ux_theta_t theta_hat = (ux_theta_t)best_i - br - 1 ;


        // 由相位估 CFO：ε̂ = -phase / (2π) 正規化至 (-0.5,0.5]
        double ph  = norm_to_pm_pi((double)best_phase);
        double eps = norm_eps_pm_half( -ph / TWO_PI );
        ux_theta_t del = (ux_theta_t)br  ;


        // ★ 每拍都輸出：便於 debug 視覺化「有沒有在跑」
        if (mcv){


        o_theta_hat.write(theta_hat);
        o_phase_hat.write(best_phase);
        o_eps_hat.write((fx_eps_t)eps);
        o_valid.write(true);
        o_ph_k.write(del);
        }
        // ★ 如果你真的不想用 valid，可以改成 always true
        //    但建議：填滿 WIN 以前 valid=0，之後拉 1，TB 就不會卡
      }

      wait(); // 下一個正緣
    }
  }
};








