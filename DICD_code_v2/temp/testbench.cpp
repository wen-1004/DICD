// =======================
// testbench.cpp (完整版本)
// =======================

#include <systemc>
#include <algorithm>
#include <cstdint>
#include <complex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace sc_core;
using namespace std;

// 重要：為了拿到模組與型別，直接包含 model.cpp
// ⚠️ 請確保 CMake 不要另外把 model.cpp 獨立編入同一個 target，否則會重複定義
#include "model.cpp"

// =======================
// 檔名常數（依需求可改）
// =======================
static const string kFileRe   = "dataset_r_real_bin.txt";
static const string kFileIm   = "dataset_r_imag_bin.txt";
static const string kFileRho  = "dataset_rho_bin.txt";
static const string kFileEps  = "dataset_epsa_bin.txt";
static const string kFileTh   = "dataset_theta_bin.txt";

// =======================
// 小工具：二進位字串解碼
// =======================

// 解析「有號」二進位字串（MSB→LSB），回傳 sign-extended 的 int64
static int64_t parse_signed_bin(const string& s, int total_bits) {
  uint64_t u = 0;
  for (char c : s) u = (u << 1) | (c == '1');
  if (total_bits < 64 && ((u >> (total_bits - 1)) & 1ULL)) {
    u |= (~0ULL) << total_bits;  // sign-extend
  }
  return (int64_t)u;
}

// 解析「無號」二進位字串（MSB→LSB），回傳 uint64
static uint64_t parse_unsigned_bin(const string& s) {
  uint64_t u = 0;
  for (char c : s) u = (u << 1) | (c == '1');
  return u;
}

// Qm.n raw → double
static inline double q_to_double(int64_t raw, int frac_bits) {
  return (double)raw / (double)(1LL << frac_bits);
}

// 讀「每行一個二進位字串」→ vector<int64_t>（保留 raw），並做長度檢查
static bool load_bin_lines_raw(const string& path, int bitlen,
                               vector<int64_t>& out_raw, bool is_signed) {
  ifstream fin(path);
  if (!fin) return false;
  out_raw.clear();
  string line;
  while (getline(fin, line)) {
    if (line.empty()) continue;
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    if ((int)line.size() != bitlen) return false;
    int64_t v = is_signed ? parse_signed_bin(line, bitlen)
                          : (int64_t)parse_unsigned_bin(line);
    out_raw.push_back(v);
  }
  return !out_raw.empty();
}

// 讀「單行」純二進位字串為 raw
static bool load_bin_scalar_raw(const string& path, int bitlen,
                                int64_t& raw, bool is_signed) {
  ifstream fin(path);
  if (!fin) return false;
  string line;
  if (!getline(fin, line)) return false;
  line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
  if ((int)line.size() != bitlen) return false;
  raw = is_signed ? parse_signed_bin(line, bitlen)
                  : (int64_t)parse_unsigned_bin(line);
  return true;
}

// =======================
// 讀檔：r(k) 與 meta
// =======================

static bool load_r_q1_15(const string& re_path, const string& im_path,
                         vector<complex<double>>& r_out) {
  vector<int64_t> re_raw, im_raw;
  if (!load_bin_lines_raw(re_path, 16, re_raw, /*signed*/ true)) return false;
  if (!load_bin_lines_raw(im_path, 16, im_raw, /*signed*/ true)) return false;
  if (re_raw.size() != im_raw.size()) return false;
  const int M = (int)re_raw.size();
  r_out.resize(M);
  for (int i = 0; i < M; ++i) {
    double re = q_to_double(re_raw[i], 15);  // Q1.15
    double im = q_to_double(im_raw[i], 15);
    r_out[i]  = {re, im};
  }
  return true;
}

static bool load_meta(const string& rho_path, const string& eps_path,
                      const string& theta_path, double& rho, double& eps_true,
                      int& theta_true) {
  int64_t raw;
  if (!load_bin_scalar_raw(rho_path, 8, raw, /*signed*/ true)) return false;
  rho = q_to_double(raw, 7);  // Q1.7

  if (!load_bin_scalar_raw(eps_path, 21, raw, /*signed*/ true)) return false;
  eps_true = q_to_double(raw, 20);  // Q1.20

  if (!load_bin_scalar_raw(theta_path, 8, raw, /*signed*/ false)) return false;
  theta_true = (int)raw;  // u8
  return true;
}

// =======================
// 由 r(k) 生成 γ(m)、Φ(m)
// m = 0..N，共 N+1 筆
// =======================
static void make_gamma_phi(const vector<complex<double>>& r, int N, int L,
                           vector<complex<double>>& gamma,
                           vector<double>& phiL) {
  const int M = (int)r.size();
  (void)M;
  gamma.assign(N + 1, complex<double>(0, 0));
  phiL.assign(N + 1, 0.0);

  for (int m = 0; m <= N; ++m) {
    complex<double> g = 0.0;
    double P = 0.0;
    for (int k = m; k < m + L; ++k) {
      const auto& rk  = r[k];
      const auto& rkN = r[k + N];
      g += rk * conj(rkN);
      P += 0.5 * (norm(rk) + norm(rkN));
    }
    gamma[m] = g;   // 用於 (13) 的相位
    phiL[m]  = P;   // 能量項（非負，不要再取 abs）
  }
}

// =======================
// 測試平台 TB
// =======================
struct TB : public sc_module {
  // 參數：CP 長度（你可改）
  static constexpr int L = 16;

  // 時脈/重置
  sc_signal<bool> clk, rst;

  // DUT 介面訊號（型別需與 model.cpp 一致）
  sc_signal<fx_gamma_t>  s_gamma_re, s_gamma_im;  // 第一級（實務上我們直接餵第二級亦可）
  sc_signal<fx_mag_t>    s_mag;                   // 由第一級輸出（此處不會用到，留線）
  sc_signal<fx_phase_t>  s_phase;                 // 由第一級輸出（此處不會用到，留線）
  sc_signal<bool>        s_fe_valid;
  sc_signal<fx_phi_t>    s_phi_Lpass;
  sc_signal<ux_theta_t>  s_fe_k;


  sc_signal<fx_rho_t>    s_rho;                   // ρ
  sc_signal<fx_phi_t>    s_phi_L;                 // Φ_L(m)
  sc_signal<bool>        s_mc_valid;
  sc_signal<ux_theta_t>  s_mc_k;


  sc_signal<fx_lambda_t> s_lambda;                // Λ(m)
  sc_signal<fx_phase_t>  s_phase_passthru;        // ∠γ(m) pass through

  sc_signal<bool>        s_valid;
  sc_signal<fx_phase_t>  s_phase_hat;
  sc_signal<fx_eps_t>    s_eps_hat;
  sc_signal<ux_theta_t>  s_theta_hat;
  sc_signal<ux_theta_t>  s_ph_k;


  // 三個模組
  FeatureExtract fe{"fe"};
  MetricCalc     mc{"mc"};
  PeakHold       ph{"ph"};

  SC_HAS_PROCESS(TB);
  TB(sc_module_name n) : sc_module(n) {
    // 連接 FeatureExtract（如果你目前不使用，可保留掛線不中斷）
    fe.i_clk(clk); fe.i_rst(rst);
    fe.i_phi(s_phi_L);
    fe.i_gamma_re(s_gamma_re); fe.i_gamma_im(s_gamma_im);
    fe.o_magnitude(s_mag); fe.o_phase(s_phase);
    fe.o_fe_valid(s_fe_valid); fe.o_fe_k(s_fe_k);  fe.o_fe_phi(s_phi_Lpass);

    // 連接 MetricCalc
    mc.i_clk(clk); mc.i_rst(rst);
    mc.i_rho(s_rho); mc.i_phi_L(s_phi_Lpass);
    // 這裡直接把 gamma 的 re/im 讓 MetricCalc 內部自行取角度
    mc.i_magnitude(s_mag);     // 可不用，若你的 MetricCalc 用不到可在 model 裡忽略
    mc.i_phase(s_phase);       // 可不用，真正使用的是 i_gamma_re/im（若你的 model 是那版請自行對接）
    mc.i_fe_valid(s_fe_valid);
    mc.i_fe_k(s_fe_k);
    // 為了時序一致，這裡我們改法：把 fe 輸出忽略，直接在 mc 裡用 i_gamma_re/im
    // 若你的 MetricCalc 介面不同，請依 model.cpp 調整 port 名稱
    // （以下兩行示範你若有 i_gamma_* 可接）


    mc.o_mc_valid(s_mc_valid);  mc.o_mc_k(s_mc_k);
    mc.o_lambda(s_lambda);
    mc.o_phase(s_phase_passthru);  // 讓 PeakHold 用這個 phase 做 (13)

    // 連接 PeakHold（只在 CP 內找最大 Λ）
    ph.i_clk(clk); ph.i_rst(rst);
    ph.i_lambda(s_lambda);
    ph.i_phase(s_phase_passthru);
    ph.i_mc_valid(s_mc_valid);
    ph.i_mc_k(s_mc_k);
    ph.o_valid(s_valid);
    ph.o_phase_hat(s_phase_hat);
    ph.o_eps_hat(s_eps_hat);
    ph.o_theta_hat(s_theta_hat);
    ph.o_ph_k(s_ph_k);

    SC_THREAD(clock_gen);
    SC_THREAD(run);
  }

  void clock_gen() {
    while (true) {
      clk.write(false); wait(5, SC_NS);
      clk.write(true);  wait(5, SC_NS);
    }
  }

  // 主要流程：讀檔→生成 γ/Φ→餵 CP 窗→等 valid→印結果
  void run() {
    // Reset 序列
    rst.write(false);
    s_gamma_re.write(0); s_gamma_im.write(0);
    s_rho.write(0); s_phi_L.write(0);
    wait(20, SC_NS);
    rst.write(true);
    wait(20, SC_NS);

    // 1) 讀 re/im 與 meta
    vector<complex<double>> r;
    if (!load_r_q1_15(kFileRe, kFileIm, r)) {
      cout << "[TB] Load r failed\n"; sc_stop(); return;
    }
    double rho, eps_true; int theta_true;
    if (!load_meta(kFileRho, kFileEps, kFileTh, rho, eps_true, theta_true)) {
      cout << "[TB] Load meta failed\n"; sc_stop(); return;
    }

    // 2) 計算 N 與總長 M（M = 2N + L）
    const int M = (int)r.size();
    const int Lcp = L;
    const int N   = (M - Lcp) / 2;
    if (2 * N + Lcp != M) {
      cout << "[TB] M not equal 2N+L (" << M << " vs " << (2 * N + Lcp) << ")\n";
      sc_stop(); return;
    }

    // 3) 生成 γ/Φ：m = 0..N → 共 N+1 筆
    vector<complex<double>> gamma;
    vector<double>          phiL;
    make_gamma_phi(r, N, Lcp, gamma, phiL);

    // 4) 固定寫 rho（Q1.7 → fx_rho_t）
    s_rho.write( (fx_rho_t)rho );
    wait(10, SC_NS);

    // 5) 只在 CP 內掃描（m = 0..L-1），逐拍餵入
    for (int m = 0; m < 255 ; ++m) {
      // gamma 的 re/im 餵進；phiL 餵進
      s_gamma_re.write( (fx_gamma_t)real(gamma[m]) );
      s_gamma_im.write( (fx_gamma_t)imag(gamma[m]) );
      s_phi_L.write(    (fx_phi_t)  (phiL[m])      );
      wait(10, SC_NS);
    }

    // 6) 等 PeakHold 拉高 valid
    bool ok = false;
    for (int t = 0; t < 100000; ++t) { // 約 1 ms 模擬時間
     if (s_valid.read()) { ok = true; break; }
     wait(10, SC_NS);
     }
    if (!ok) {
    std::cout << "[TB] Timeout waiting valid\n";
    // 仍可印出目前 theta_hat/eps_hat 觀察
}


    // 7) 讀回估計並計算誤差
    double   eps_hat   = (double)s_eps_hat.read();
    unsigned theta_hat = (unsigned)s_theta_hat.read();
    unsigned theta_k = (unsigned)s_ph_k.read();


    double eps_abs = fabs(eps_hat - eps_true);
    double eps_rel = (fabs(eps_true) > 1e-12) ? eps_abs / fabs(eps_true) : 0.0;

    cout << "\n=== TB Summary ===\n";
    cout << "M(2N+L)        : " << M << "  N=" << N << "  L=" << Lcp << "\n";
    cout << "gamma/phi count: " << (N + 1) << " (m=0.." << N << ")\n";
    cout << "Search m in N : [0," << (N) << "]\n";
    cout << "rho            : " << rho << "\n";
    cout << "theta_true     : " << theta_true << "\n";
    cout << "theta_hat      : " << theta_hat << "\n";
    cout << "theta_k      : " << theta_k << "\n";
    cout << "eps_true       : " << eps_true << "\n";
    cout << "eps_hat        : " << eps_hat << "\n";
    cout << "Abs error      : " << eps_abs << "\n";
    cout << "Rel. error     : " << eps_rel * 100.0 << " %\n";
    cout << "===================\n";

    sc_stop();
  }
};

// =======================
// sc_main
// =======================
int sc_main(int argc, char** argv) {
  TB tb{"tb"};
  sc_start();
  return 0;
}