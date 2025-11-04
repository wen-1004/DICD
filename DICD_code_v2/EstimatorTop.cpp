// EstimatorTop.hpp — connects all 8 modules with your concrete port names (double)
#pragma once
#include <systemc>
#include <iostream>
#include <iomanip>
#include <string>

// You are including .cpp modules directly (ok for now if they have include guards)
#include "delay_n.cpp"     // SC_MODULE(delay_n)
#include "phi_sum.cpp"     // SC_MODULE(phi_sum)
#include "gamma_sum.cpp"   // SC_MODULE(gamma_sum)
#include "mag_mod.cpp"     // SC_MODULE(mag_mod)
#include "angle_mod.cpp"   // SC_MODULE(angle_mod)
#include "minus_mod.cpp"   // SC_MODULE(minus_mod)
#include "argmax_mod.cpp"  // SC_MODULE(argmax_mod)
#include "select_eps.cpp"  // SC_MODULE(select_eps)

struct EstimatorTop : sc_core::sc_module {
  // ---------- Top-level ports ----------
  sc_core::sc_in<bool>    clk   {"clk"};
  sc_core::sc_in<bool>    rst   {"rst"};                // active-low
  sc_core::sc_in<double>  r_in_real {"r_in_real"};
  sc_core::sc_in<double>  r_in_imag {"r_in_imag"};
  sc_core::sc_in<double>  rho_in    {"rho_in"};

  sc_core::sc_out<short>  theta_out {"theta_out"};      // θ index (0..255)
  sc_core::sc_out<double> eps_out   {"eps_out"};        // ε

  // ---------- Internal signals ----------
  // delay_n outputs
  sc_core::sc_signal<double> r_d1_real       {"r_d1_real"};       // r(k) after 1-cycle
  sc_core::sc_signal<double> r_d1_imag       {"r_d1_imag"};
  sc_core::sc_signal<double> r_dN_out_real   {"r_dN_out_real"};   // r(k+N)
  sc_core::sc_signal<double> r_dN_out_imag   {"r_dN_out_imag"};
  sc_core::sc_signal<bool>   valid_d         {"valid_d"};

  // phi_sum
  sc_core::sc_signal<double> phi_out         {"phi_out"};
  sc_core::sc_signal<bool>   phi_valid       {"phi_valid"};

  // gamma_sum (complex)
  sc_core::sc_signal<double> gamma_out_real  {"gamma_out_real"};
  sc_core::sc_signal<double> gamma_out_imag  {"gamma_out_imag"};
  sc_core::sc_signal<bool>   gamma_valid     {"gamma_valid"};

  // mag / angle
  sc_core::sc_signal<double> mag_out         {"mag_out"};
  sc_core::sc_signal<double> ang_out         {"ang_out"};

  // minus → λ
  sc_core::sc_signal<double> lambda_out      {"lambda_out"};

  // argmax θ (internal)
  sc_core::sc_signal<short>  theta_sig       {"theta_sig"};

  // ---------- Instances ----------
  delay_n     *U_DELAY_N   {nullptr};
  phi_sum     *U_PHI_SUM   {nullptr};
  gamma_sum   *U_GAMMA_SUM {nullptr};
  mag_mod     *U_MAG       {nullptr};
  angle_mod   *U_ANGLE     {nullptr};
  minus_mod   *U_MINUS     {nullptr};
  argmax_mod  *U_ARGMAX    {nullptr};
  select_eps  *U_SELECT    {nullptr};

  SC_CTOR(EstimatorTop) {
    // Create
    U_DELAY_N   = new delay_n   ("delay_n");
    U_PHI_SUM   = new phi_sum   ("phi_sum");
    U_GAMMA_SUM = new gamma_sum ("gamma_sum");
    U_MAG       = new mag_mod   ("mag");
    U_ANGLE     = new angle_mod ("angle", /*delay_cycles=*/7);
    U_MINUS     = new minus_mod ("minus");
    U_ARGMAX    = new argmax_mod("argmax");
    U_SELECT    = new select_eps("select");

    // -------- delay_n --------
    U_DELAY_N->clk(clk);
    U_DELAY_N->rst(rst);                         // your delay_n uses 'rst'
    U_DELAY_N->r_in_real(r_in_real);
    U_DELAY_N->r_in_imag(r_in_imag);
    U_DELAY_N->r_d1_real(r_d1_real);
    U_DELAY_N->r_d1_imag(r_d1_imag);
    U_DELAY_N->r_dN_out_real(r_dN_out_real);
    U_DELAY_N->r_dN_out_imag(r_dN_out_imag);
    U_DELAY_N->valid_out(valid_d);

    // -------- phi_sum --------
    U_PHI_SUM->clk(clk);
    U_PHI_SUM->reset(rst);                       // phi_sum uses 'reset'
    U_PHI_SUM->r_k_in_real(r_d1_real);
    U_PHI_SUM->r_k_in_imag(r_d1_imag);
    U_PHI_SUM->r_k_minus_N_in_real(r_dN_out_real);
    U_PHI_SUM->r_k_minus_N_in_imag(r_dN_out_imag);
    U_PHI_SUM->valid_in(valid_d);
    U_PHI_SUM->p_in(rho_in);                     // if used internally
    U_PHI_SUM->phi_out(phi_out);
    U_PHI_SUM->valid_out(phi_valid);

    // -------- gamma_sum --------
    U_GAMMA_SUM->clk(clk);
    U_GAMMA_SUM->reset(rst);
    U_GAMMA_SUM->r_k_in_real(r_d1_real);
    U_GAMMA_SUM->r_k_in_imag(r_d1_imag);
    U_GAMMA_SUM->r_k_minus_N_in_real(r_dN_out_real);
    U_GAMMA_SUM->r_k_minus_N_in_imag(r_dN_out_imag);
    U_GAMMA_SUM->valid_in(valid_d);
    U_GAMMA_SUM->gamma_out_real(gamma_out_real);
    U_GAMMA_SUM->gamma_out_imag(gamma_out_imag);
    U_GAMMA_SUM->valid_out(gamma_valid);

    // -------- mag (0-cycle alpha-max) --------
    U_MAG->gm_in_real(gamma_out_real);
    U_MAG->gm_in_imag(gamma_out_imag);
    U_MAG->mag_out(mag_out);

    // -------- angle (7-cycle) --------
    U_ANGLE->clk(clk);
    U_ANGLE->rst(rst);                            // active-low
    U_ANGLE->gm_in_real(gamma_out_real);
    U_ANGLE->gm_in_imag(gamma_out_imag);
    U_ANGLE->ang_out(ang_out);

    // -------- minus: λ = |γ| − ρ·Φ --------
    U_MINUS->mag_in(mag_out);
    U_MINUS->phi_in(phi_out);
    U_MINUS->rho_in(rho_in);                      // keep if minus uses ρ
    U_MINUS->lambda_out(lambda_out);

    // -------- argmax over 256 --------
    U_ARGMAX->clk(clk);
    U_ARGMAX->rst(rst);                           // active-low
    U_ARGMAX->lambda_in(lambda_out);
    U_ARGMAX->theta_out(theta_sig);               // internal signal ONLY

    // -------- select ε(θ) --------
    U_SELECT->angle_in(ang_out);
    U_SELECT->theta_in(theta_sig);
    U_SELECT->eps_out(eps_out);

    // ---- forward internal θ to top port (avoid multi-driver) ----
    SC_METHOD(fwd_theta_proc);
    sensitive << theta_sig;
    dont_initialize();

    // ---- pretty printer each clock ----
    SC_METHOD(print_all_proc);
    sensitive << clk.pos();
    dont_initialize();
  }

private:
  bool header_printed{false};

  // Forward θ from internal signal to top-level output port
  void fwd_theta_proc() {
    theta_out.write(theta_sig.read());
  }

  // Pretty monitor: print all connected signals
  void print_all_proc() {
    if (!rst.read()) {        // in reset: reprint header next time
      header_printed = false;
      return;
    }

    std::cout.setf(std::ios::fixed);
    std::cout << std::setprecision(6);
    const int WT = 12, W = 11;

    if (!header_printed) {
      std::cout << std::right << std::setw(WT) << "Time"
                << " | " << std::setw(W) << "r_in_real"    << " " << std::setw(W) << "r_in_imag"
                << " | " << std::setw(W) << "r_d1_real"    << " " << std::setw(W) << "r_d1_imag"
                << " | " << std::setw(W) << "r_dN_real"    << " " << std::setw(W) << "r_dN_imag"
                << " | " << std::setw(W) << "valid_d"
                << " | " << std::setw(W) << "phi_out"      << " " << std::setw(W) << "phi_vld"
                << " | " << std::setw(W) << "gamma_out_r"  << " " << std::setw(W) << "gamma_out_i"
                << " | " << std::setw(W) << "gamma_vld"
                << " | " << std::setw(W) << "mag_out"
                << " | " << std::setw(W) << "ang_out"
                << " | " << std::setw(W) << "rho_in"
                << " | " << std::setw(W) << "lambda_out"
                << " | " << std::setw(W) << "theta"
                << " | " << std::setw(W) << "eps_out"
                << "\n";

      int sep_len =
          WT + 3
        + (W*2+1)             // r_in
        + 3 + (W*2+1)         // r_d1
        + 3 + (W*2+1)         // r_dN
        + 3 + W               // valid_d
        + 3 + (W*2+1)         // phi_out + phi_valid
        + 3 + (W*2+1)         // gamma_out real/imag
        + 3 + W               // gamma_valid
        + 3 + W               // mag_out
        + 3 + W               // ang_out
        + 3 + W               // rho_in
        + 3 + W               // lambda_out
        + 3 + W               // theta
        + 3 + W;              // eps_out

      std::cout << std::string(sep_len, '-') << "\n";
      header_printed = true;
    }

    std::cout << std::right << std::setw(WT) << sc_core::sc_time_stamp()
              << " | " << std::setw(W) << r_in_real.read()        << " " << std::setw(W) << r_in_imag.read()
              << " | " << std::setw(W) << r_d1_real.read()        << " " << std::setw(W) << r_d1_imag.read()
              << " | " << std::setw(W) << r_dN_out_real.read()    << " " << std::setw(W) << r_dN_out_imag.read()
              << " | " << std::setw(W) << int(valid_d.read())
              << " | " << std::setw(W) << phi_out.read()          << " " << std::setw(W) << int(phi_valid.read())
              << " | " << std::setw(W) << gamma_out_real.read()   << " " << std::setw(W) << gamma_out_imag.read()
              << " | " << std::setw(W) << int(gamma_valid.read())
              << " | " << std::setw(W) << mag_out.read()
              << " | " << std::setw(W) << ang_out.read()
              << " | " << std::setw(W) << rho_in.read()
              << " | " << std::setw(W) << lambda_out.read()
              << " | " << std::setw(W) << int(theta_sig.read())
              << " | " << std::setw(W) << eps_out.read()
              << "\n";
  }
};
