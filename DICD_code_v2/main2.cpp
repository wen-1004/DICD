// main.cpp — minimal loader + terminal trace
#include <systemc>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>


#include "delay_n.cpp"  // your module

using namespace sc_core;

// --- Tiny helpers ---

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

int sc_main(int argc, char* argv[]) {
  // Pick dataset folder
  std::string folder = (argc >= 2) ? argv[1] : "prog0";
  if (folder.find('/') == std::string::npos) folder = "testcase/" + folder;

  // File paths
  const std::string p_re  = folder + "/dataset_r_real_bin.txt";   // 528 x s(1,15)
  const std::string p_im  = folder + "/dataset_r_imag_bin.txt";   // 528 x s(1,15)
  const std::string p_rho = folder + "/dataset_rho_bin.txt";      // 1   x s(1,7)

  // Load bits
  auto bre = read_lines_bits(p_re);
  auto bim = read_lines_bits(p_im);
  auto brho= read_one_bits(p_rho);

  if (bre.empty() || bim.empty() || brho.empty()) {
    std::cerr << "ERR: missing/empty input files under " << folder << "\n";
    return 1;
  }
  const size_t N = std::min(bre.size(), bim.size());

  // Convert to double
  std::vector<double> rre; rre.reserve(N);
  std::vector<double> rim; rim.reserve(N);
  for (size_t i=0;i<N;i++) {
    rre.push_back(s1F_to_double(bre[i], 15));  // s(1,15)
    rim.push_back(s1F_to_double(bim[i], 15));  // s(1,15)
  }
  double rho_val = s1F_to_double(brho, 7);     // s(1,7)

  std::cout << "INFO: Dataset=" << folder
            << " | samples=" << N
            << " | rho(s1,7)=" << rho_val << "\n";

  // SystemC wiring
  sc_clock clk("clk", 10, SC_NS);
  sc_signal<bool> rst;
  sc_signal<double> r_in_real, r_in_imag;
  sc_signal<double> r_d1_real, r_d1_imag;
  sc_signal<double> r_dN_real, r_dN_imag;
  sc_signal<bool>   valid_out;

  delay_n dut("delay_n");
  dut.clk(clk);
  dut.rst(rst);
  dut.r_in_real(r_in_real);
  dut.r_in_imag(r_in_imag);
  dut.r_d1_real(r_d1_real);
  dut.r_d1_imag(r_d1_imag);
  dut.r_dN_out_real(r_dN_real);
  dut.r_dN_out_imag(r_dN_imag);
  dut.valid_out(valid_out);

  // Reset
  sc_start(0, SC_NS);
  rst = true;  sc_start(10, SC_NS);
  rst = false; // release

  // Pretty table formatting
  std::cout.setf(std::ios::fixed);
  std::cout << std::setprecision(6);
  
  const int WT = 12;   // time col width
  const int W  = 11;   // number col width
  const int WV = 5;    // valid col width
  
  // Header
  std::cout << std::right << std::setw(WT) << "Time"
            << " | " << std::setw(W) << "Rin.r"  << " " << std::setw(W) << "Rin.i"
            << " | " << std::setw(W) << "Rout.r" << " " << std::setw(W) << "Rout.i"
            << " | " << std::setw(W) << "Rdel.r" << " " << std::setw(W) << "Rdel.i"
            << " | " << std::setw(WV) << "Valid" << "\n";
  
  // Separator
  std::cout << std::string(WT + 3 + (W*2+1)*3 + 3 + WV, '-') << "\n";


  // Drive & print terminal trace
  for (size_t i=0; i<N; ++i) {
    r_in_real = rre[i];
    r_in_imag = rim[i];
    sc_start(10, SC_NS);
    std::cout << std::right << std::setw(WT) << sc_time_stamp()
              << " | " << std::setw(W) << r_in_real.read()   << " " << std::setw(W) << r_in_imag.read()
              << " | " << std::setw(W) << r_d1_real.read()  << " " << std::setw(W) << r_d1_imag.read()
              << " | " << std::setw(W) << r_dN_real.read() << " " << std::setw(W) << r_dN_imag.read()
              << " | " << std::setw(WV) << (int)valid_out.read()
              << "\n";
  }

  // Flush a bit
  sc_start(100, SC_NS);
  return 0;
}
