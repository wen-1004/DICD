// main.cpp — drive DUT, rely on EstimatorTop's internal monitor, compare golden θ/ε
#include <systemc>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm> // for std::min

#include "EstimatorTop.cpp"   // your DUT wiring (connects 8 modules)

using namespace sc_core;

// ---- Tiny helpers ----

// Read all non-empty lines, keep only '0'/'1'
static std::vector<std::string> read_lines_bits(const std::string& path) {
  std::ifstream ifs(path);
  if (!ifs) { std::cerr << "ERR: open " << path << "\n"; return {}; }
  std::vector<std::string> v; v.reserve(1024);
  std::string line;
  while (std::getline(ifs, line)) {
    std::string bits;
    for (char c: line) if (c=='0' || c=='1') bits.push_back(c);
    if (!bits.empty()) v.push_back(bits);
  }
  return v;
}

// Read single-line bitstring
static std::string read_one_bits(const std::string& path) {
  std::ifstream ifs(path);
  if (!ifs) { std::cerr << "ERR: open " << path << "\n"; return ""; }
  std::string line, bits;
  std::getline(ifs, line);
  for (char c: line) if (c=='0' || c=='1') bits.push_back(c);
  return bits;
}

// s(1,F) two's-complement -> double (total bits = 1+F)
static double s1F_to_double(const std::string& bits, int F) {
  const int T = 1 + F;
  long long u = 0;
  for (char c: bits) { u = (u<<1) | (c=='1'); }
  const long long sign = 1LL << (T-1);
  long long s = (u & sign) ? (u - (1LL<<T)) : u;
  return double(s) / double(1LL<<F);
}

// u(8,0) -> unsigned int
static unsigned u8_to_uint(const std::string& bits) {
  unsigned u = 0;
  for (char c: bits) { u = (u<<1) | (c=='1'); }
  return u & 0xFFu;
}

int sc_main(int argc, char* argv[]) {
  // Pick dataset folder (prog0/prog1 or explicit path)
  std::string folder = (argc >= 2) ? argv[1] : "prog0";
  if (folder.find('/') == std::string::npos) folder = "testcase/" + folder;

  // File paths
  const std::string p_re    = folder + "/dataset_r_real_bin.txt";   // 528 x s(1,15)
  const std::string p_im    = folder + "/dataset_r_imag_bin.txt";   // 528 x s(1,15)
  const std::string p_rho   = folder + "/dataset_rho_bin.txt";      // 1   x s(1,7)
  const std::string p_theta = folder + "/dataset_theta_bin.txt";    // 1   x u(8,0)
  const std::string p_eps   = folder + "/dataset_epsa_bin.txt";     // 1   x s(1,20)

  // Load inputs
  auto bre   = read_lines_bits(p_re);
  auto bim   = read_lines_bits(p_im);
  auto brho  = read_one_bits(p_rho);
  auto bth   = read_one_bits(p_theta);
  auto beps  = read_one_bits(p_eps);

  if (bre.empty() || bim.empty() || brho.empty() || bth.empty() || beps.empty()) {
    std::cerr << "ERR: missing/empty input or golden files under " << folder << "\n";
    return 1;
  }
  const size_t NSAMPLES = std::min(bre.size(), bim.size());

  // Convert streams to doubles
  std::vector<double> rre; rre.reserve(NSAMPLES);
  std::vector<double> rim; rim.reserve(NSAMPLES);
  for (size_t i=0;i<NSAMPLES;i++) {
    rre.push_back(s1F_to_double(bre[i], 15));  // s(1,15)
    rim.push_back(s1F_to_double(bim[i], 15));  // s(1,15)
  }
  const double   rho_val    = s1F_to_double(brho, 7);    // s(1,7)
  const unsigned theta_gld  = u8_to_uint(bth);           // u(8,0)
  const double   eps_gld    = s1F_to_double(beps, 20);   // s(1,20)

  std::cout << "INFO: Dataset=" << folder
            << " | samples=" << NSAMPLES
            << " | rho(s1,7)=" << rho_val
            << " | theta_golden=" << theta_gld
            << " | eps_golden=" << std::setprecision(10) << eps_gld << std::setprecision(6)
            << "\n";

  // -------------------- SystemC wiring --------------------
  sc_clock clk("clk", 10, SC_NS);
  sc_signal<bool>    rst("rst");          // ACTIVE-LOW in EstimatorTop's monitor
  sc_signal<double>  r_in_real("r_in_real");
  sc_signal<double>  r_in_imag("r_in_imag");
  sc_signal<double>  rho_in("rho_in");
  sc_signal<short>   theta_out("theta_out");
  sc_signal<double>  eps_out("eps_out");

  EstimatorTop dut("EstimatorTop");
  dut.clk(clk);
  dut.rst(rst);
  dut.r_in_real(r_in_real);
  dut.r_in_imag(r_in_imag);
  dut.rho_in(rho_in);
  dut.theta_out(theta_out);
  dut.eps_out(eps_out);

  // ----- Proper reset sequence for ACTIVE-LOW reset -----
  sc_start(0, SC_NS);
  rst = false;            // assert reset (active-low)
  rho_in = rho_val;       // drive rho constant (can set during reset)
  sc_start(30, SC_NS);    // hold reset for a few cycles
  rst = true;             // deassert reset
  sc_start(10, SC_NS);    // let the monitor print header on first active cycle

  // ----- Stream samples (internal monitor will print every cycle) -----
  for (size_t i=0; i<NSAMPLES; ++i) {
    r_in_real = rre[i];
    r_in_imag = rim[i];
    sc_start(10, SC_NS);  // 1 cycle per sample
  }

  // Flush pipeline (argmax depth etc.). Use a safe margin.
  constexpr int FLUSH_CYCLES = 32;  // >= argmax(8) + other pipes
  for (int i=0; i<FLUSH_CYCLES; ++i) sc_start(10, SC_NS);

  // --- Gather DUT results ---
  const short  theta_meas_d = theta_out.read();
  const int    theta_meas   = static_cast<int>(std::llround(theta_meas_d));
  const double eps_meas     = eps_out.read();

  // --- Compare against golden ---
  const bool   theta_ok = (theta_meas == static_cast<int>(theta_gld));
  const double abs_err  = std::fabs(eps_meas - eps_gld);
  const double rel_err  = abs_err / std::max(1e-12, std::fabs(eps_gld));
  const bool   eps_ok   = (rel_err <= 0.05);  // 5% tolerance

  std::cout << "\n=== RESULT CHECK ===\n";
  std::cout << "theta: DUT=" << theta_meas << " (raw " << theta_meas_d << ")"
            << "  | golden=" << theta_gld
            << "  | " << (theta_ok ? "PASS" : "FAIL") << "\n";
  std::cout << std::setprecision(10)
            << "epsilon: DUT=" << eps_meas
            << "  | golden=" << eps_gld
            << "  | abs_err=" << abs_err
            << "  | rel_err=" << (rel_err*100.0) << "%  | "
            << (eps_ok ? "PASS (≤5%)" : "FAIL (>5%)") << "\n";

  return (theta_ok && eps_ok) ? 0 : 2;
}
