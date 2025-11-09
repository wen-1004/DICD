// main.cpp — drive DUT, sample at 5310 ns + 2560*k, compare per-output goldens
#include <systemc>
#include <deque>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

#include "../src/EstimatorTop.cpp"   // your DUT wiring (connects 8 modules)
#include "../include/data_type.hpp"    // your data types

using namespace sc_core;

// ---- helpers ---------------------------------------------------------------

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

// Read single-line bitstring (still tolerant)
static std::string read_one_bits(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs) { std::cerr << "ERR: open " << path << "\n"; return ""; }
    std::string line, bits;
    std::getline(ifs, line);
    for (char c: line) if (c=='0' || c=='1') bits.push_back(c);
    return bits;
}

// s(1,F) two's-complement -> double
static double s1F_to_double(const std::string& bits, int F) {
    const int T = 1 + F;
    if ((int)bits.size() != T) {
        // Be forgiving: sign-extend or truncate if needed
        std::string b = bits;
        if ((int)b.size() < T) {
            char sign = b.empty()? '0' : b.front();
            b = std::string(T - b.size(), sign) + b;
        } else if ((int)b.size() > T) {
            b = b.substr(b.size() - T);
        }
        return s1F_to_double(b, F);
    }
    long long u = 0;
    for (char c: bits) { u = (u<<1) | (c=='1'); }
    const long long sign = 1LL << (T-1);
    long long s = (u & sign) ? (u - (1LL<<T)) : u;
    return double(s) / double(1LL<<F);
}

// u(8,0) -> unsigned int
static unsigned u8_to_uint(const std::string& bits_in) {
    std::string bits = bits_in;
    if ((int)bits.size() < 8) bits = std::string(8 - bits.size(), '0') + bits;
    if ((int)bits.size() > 8) bits = bits.substr(bits.size()-8);
    unsigned u = 0;
    for (char c: bits) { u = (u<<1) | (c=='1'); }
    return u & 0xFFu;
}

int sc_main(int argc, char* argv[]) {
    // Pick dataset folder (prog0/prog1 or explicit path)
    std::string folder = (argc >= 2) ? argv[1] : "prog0";
    if (folder.find('/') == std::string::npos) folder = "testcase/" + folder;
  
    // File paths
    const std::string p_re     = folder + "/dataset_r_real_bin.txt";   // 528 x s(1,15)
    const std::string p_im     = folder + "/dataset_r_imag_bin.txt";   // 528 x s(1,15)
    const std::string p_rho    = folder + "/dataset_rho_bin.txt";      // 1 x s(1,7)
    const std::string p_theta  = folder + "/dataset_theta_bin.txt";    // N_out lines, u(8,0)
    const std::string p_eps    = folder + "/dataset_epsa_bin.txt";     // N_out lines, s(1,20)
  
    // Load inputs
    auto bre   = read_lines_bits(p_re);
    auto bim   = read_lines_bits(p_im);
    auto rho_b = read_one_bits(p_rho);
  
    if (bre.empty() || bim.empty() || rho_b.empty()) {
        std::cerr << "ERR: missing/empty r/re/im/rho files under " << folder << "\n";
        return 1;
    }
    const size_t NSAMPLES = std::min(bre.size(), bim.size());
  
    // Convert input streams
    std::vector<double> rre; rre.reserve(NSAMPLES);
    std::vector<double> rim; rim.reserve(NSAMPLES);
    for (size_t i=0;i<NSAMPLES;i++) {
        rre.push_back(s1F_to_double(bre[i], 15));  // s(1,15)
        rim.push_back(s1F_to_double(bim[i], 15));  // s(1,15)
    }
    const double rho_val = s1F_to_double(rho_b, 7);    // s(1,7)
  
    // Load goldens (multi-line)
    auto theta_lines = read_lines_bits(p_theta);
    auto eps_lines   = read_lines_bits(p_eps);
    std::vector<unsigned> theta_gld;
    std::vector<double>   eps_gld;
    theta_gld.reserve(theta_lines.size());
    eps_gld.reserve(eps_lines.size());
    for (auto& s: theta_lines) theta_gld.push_back(u8_to_uint(s));   // u(8,0)
    for (auto& s: eps_lines)   eps_gld.push_back(s1F_to_double(s,20)); // s(1,20)
  
    // Informative banner
    std::cout << "INFO: Dataset=" << folder
              << " | samples=" << NSAMPLES
              << " | rho(s1,7)=" << rho_val
              << " | golden_count theta=" << theta_gld.size()
              << " eps=" << eps_gld.size()
              << "\n";
  
    // -------------------- SystemC wiring --------------------
    const sc_time Tclk(10, SC_NS);
    const sc_time Tpipe(100, SC_NS);  // 10 cycles × 10 ns = 100 ns
  
    sc_clock clk("clk", Tclk);
    sc_signal<bool>    rst("rst");      // ACTIVE-LOW
    sc_signal<r_t>  r_in_real("r_in_real");
    sc_signal<r_t>  r_in_imag("r_in_imag");
    sc_signal<rho_t>  rho_in("rho_in");
    sc_signal<theta_t>   theta_out("theta_out");
    sc_signal<eps_t>  eps_out("eps_out");
  
    EstimatorTop dut("EstimatorTop");
    dut.clk(clk);
    dut.rst(rst);
    dut.r_in_real(r_in_real);
    dut.r_in_imag(r_in_imag);
    dut.rho_in(rho_in);
    dut.theta_out(theta_out);
    dut.eps_out(eps_out);
  
    // Reset sequence (active-low)
    sc_start(SC_ZERO_TIME);
    rst = false;            // assert reset
    rho_in = rho_val;       // drive rho constant
    sc_start(3*Tclk);       // hold reset for 3 cycles
    rst = true;             // deassert reset
    sc_start(Tclk);         // allow monitor to print header
  
    // Argmax emission rule: first result after 528 samples, then every +256 samples
    const int FIRST_SAMPLES = 528;
    const int STEP_SAMPLES  = 256;
    const int     PIPE_CYCLES = 9;    // same as above, for actual sim steps
  
    // How many outputs we *expect* from NSAMPLES
    size_t expected_out = 0;
    if (NSAMPLES >= (size_t)FIRST_SAMPLES)
        expected_out = 1 + (NSAMPLES - FIRST_SAMPLES) / STEP_SAMPLES;
  
    struct Rec {
        sc_time t_report;  // printed time (5310 ns, 7870 ns, ...)
        int     theta;
        double eps;
    };
    std::vector<Rec> recs; recs.reserve(expected_out);
    std::deque<int> due;    // capture when sample_cnt reaches this value
  
    // ----- Stream samples and capture outputs at boundaries -----
    int sample_cnt = 0;
    for (size_t i=0; i<NSAMPLES; ++i) {
        // Drive next sample
        r_in_real = rre[i];
        r_in_imag = rim[i];
    
        // Advance one clock (updates DUT on posedge)
        sc_start(Tclk);
        ++sample_cnt;
    
        // If we hit a boundary now, schedule a capture PIPE_CYCLES later
        if (sample_cnt >= FIRST_SAMPLES &&
            (sample_cnt - FIRST_SAMPLES) % STEP_SAMPLES == 0) {
            due.push_back(sample_cnt + PIPE_CYCLES);
        }
    
        // If any capture is now due, record it (may happen multiple times if slow-fed)
        while (!due.empty() && due.front() <= sample_cnt) {
            Rec r;
            // monitor prints on the current posedge time; to match the printed line,
            // report the previous tick (e.g., 5310 ns) as sc_time_stamp() - Tclk
            r.t_report = sc_time_stamp() - Tclk;
            r.theta    = static_cast<int>(theta_out.read());
            r.eps      = eps_out.read();
            recs.push_back(r);
            due.pop_front();
        }
    }
    // ---- Final pipeline drain (let outputs propagate through 10-cycle pipe) ----
    while (!due.empty()) {
        sc_start(Tclk);
        ++sample_cnt;
        while (!due.empty() && due.front() <= sample_cnt) {
            Rec r;
            r.t_report = sc_time_stamp() - Tclk;   // e.g., 5310 + 2560*k ns
            r.theta    = static_cast<int>(theta_out.read());
            r.eps      = eps_out.read();
            recs.push_back(r);
            due.pop_front();
        }
    }
  
    // --------------- Compare each captured result ----------------
    const double EPS_REL_TOL = 0.05; // 5%
    const size_t Ncap = recs.size();
    const size_t Ngth = theta_gld.size();
    const size_t Ngep = eps_gld.size();
    const size_t Ncmp = std::min({Ncap, Ngth, Ngep});
  
    if (Ncap != expected_out) {
        std::cout << "WARN: Captured " << Ncap << " outputs but expected "
                  << expected_out << " from " << NSAMPLES
                  << " samples (first=528, step=256).\n";
    }
    if (Ncmp < Ncap || Ncmp < Ngth || Ncmp < Ngep) {
        std::cout << "WARN: Golden/captured count mismatch. Will compare first "
                  << Ncmp << " outputs only.\n";
    }
  
    std::cout << "\n=== PER-OUTPUT RESULT CHECK ===\n";
    std::cout.setf(std::ios::fixed);
    std::cout << std::setprecision(10);
  
    bool all_ok = true;
    double sum_abs_err = 0.0;
    double sum_rel_err = 0.0;
    for (size_t k = 0; k < Ncmp; ++k) {
        const auto& r = recs[k];
        const int theta_m = r.theta;
        const int theta_g = static_cast<int>(theta_gld[k]);
        const double eps_m = r.eps;
        const double eps_g = eps_gld[k];
        const double abs_err = std::fabs(eps_m - eps_g);
        const double rel_err = abs_err / std::max(1e-12, std::fabs(eps_g));
        const bool theta_ok = (theta_m == theta_g);
        const bool eps_ok   = (rel_err <= EPS_REL_TOL);
        all_ok = all_ok && theta_ok && eps_ok;
        sum_abs_err += abs_err;
        sum_rel_err += rel_err;
    
        std::cout << r.t_report << " | "
                  << "theta: DUT=" << theta_m
                  << "  golden=" << theta_g
                  << "  -> " << (theta_ok ? "PASS" : "failed")
                  << "  ||  epsilon: DUT=" << eps_m
                  << "  golden=" << eps_g
                  << "  abs_err=" << abs_err
                  << "  rel_err=" << (rel_err*100.0) << "%  -> "
                  << (eps_ok ? "PASS (≤5%)" : "failed (>5%)")
                  << "\n";
    }
  
    if (Ncmp == 0) {
        std::cout << "NOTE: No comparable outputs (captured=" << Ncap
                  << ", theta_golden=" << Ngth << ", eps_golden=" << Ngep << ").\n";
        return 2; // treat as failure
    } else if (Ncmp > 0) {
        const double avg_abs_err = sum_abs_err / static_cast<double>(Ncmp);
        const double avg_rel_err_pct = (sum_rel_err / static_cast<double>(Ncmp)) * 100.0;

        std::cout << "\n=== SUMMARY (AVERAGE EPSILON ERR) ===\n";
        std::cout << "Avg |eps_DUT - eps_golden| = " << avg_abs_err
                  << "  (" << avg_rel_err_pct << "% over " << Ncmp << " outputs)\n";
    }
    return all_ok ? 0 : 2;
}


