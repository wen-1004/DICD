// EstimatorTop.hpp — connects all 8 modules with your concrete port names (double)
#include <systemc>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>

#include "delay_n.cpp"
#include "phi_sum.cpp"
#include "gamma_sum.cpp"
#include "mag.cpp"
#include "angle.cpp"
#include "minus.cpp"
#include "argmax.cpp"

#include "../include/data_type.hpp"

// RTL wrapper
#include "rtl/minus_rtl_wrap.hpp"

template <typename T>
std::string fmt3(const T& x) {
    double v = static_cast<double>(x);

    if (v == 0.0) return "0";

    double av = std::fabs(v);
    int e = static_cast<int>(std::floor(std::log10(av)));

    // decimals = 2 - e  ⇒ total ≈ 3 significant digits
    int decimals = 2 - e;
    if (decimals < 0) decimals = 0;      // big numbers: no fraction
    if (decimals > 9) decimals = 9;      // clamp to something sane

    std::ostringstream oss;
    oss.setf(std::ios::fixed, std::ios::floatfield);
    oss << std::setprecision(decimals) << v;
    return oss.str();
}


struct EstimatorTop : sc_core::sc_module {
    // ---------- Top-level ports ----------
    sc_core::sc_in<bool>     clk               {"clk"};
    sc_core::sc_in<bool>     rst               {"rst"};
    sc_core::sc_in<r_t>      r_in_real         {"r_in_real"};
    sc_core::sc_in<r_t>      r_in_imag         {"r_in_imag"};
    sc_core::sc_in<rho_t>    rho_in            {"rho_in"};
    sc_core::sc_out<theta_t> theta_out         {"theta_out"};
    sc_core::sc_out<eps_t>   eps_out           {"eps_out"};

    // ---------- Internal signals ----------
    // delay_n outputs
    sc_core::sc_signal<r_t>  r_d1_real         {"r_d1_real"};
    sc_core::sc_signal<r_t>  r_d1_imag         {"r_d1_imag"};
    sc_core::sc_signal<r_t>  r_dN_out_real     {"r_dN_out_real"};
    sc_core::sc_signal<r_t>  r_dN_out_imag     {"r_dN_out_imag"};

    // phi_sum
    sc_core::sc_signal<phi_t> phi_out          {"phi_out"};

    // gamma_sum (complex)
    sc_core::sc_signal<gamma_t> gamma_out_real {"gamma_out_real"};
    sc_core::sc_signal<gamma_t> gamma_out_imag {"gamma_out_imag"};

    // mag / angle
    sc_core::sc_signal<mag_t> mag_out          {"mag_out"};
    sc_core::sc_signal<ang_t> ang_out          {"ang_out"};

    // minus → λ
    sc_core::sc_signal<lambda_t> lambda_out      {"lambda_out"};

    // argmax θ (internal)
    sc_core::sc_signal<theta_t>  theta_sig       {"theta_sig"};

    // ---------- Instances ----------
    delay_n     *U_DELAY_N   {nullptr};
    phi_sum     *U_PHI_SUM   {nullptr};
    gamma_sum   *U_GAMMA_SUM {nullptr};
    mag         *U_MAG       {nullptr};
    angle       *U_ANGLE     {nullptr};
#ifdef USE_RTL_MINUS
    minus_rtl_wrap *U_MINUS  {nullptr};
#else
    minus          *U_MINUS  {nullptr};
#endif
    argmax      *U_ARGMAX    {nullptr};

    SC_CTOR(EstimatorTop) {
        U_DELAY_N   = new delay_n   ("delay_n");
        U_PHI_SUM   = new phi_sum   ("phi_sum");
        U_GAMMA_SUM = new gamma_sum ("gamma_sum");
        U_MAG       = new mag       ("mag");
        U_ANGLE     = new angle     ("angle");
#ifdef USE_RTL_MINUS
    U_MINUS     = new minus_rtl_wrap("minus_rtl");
#else
    U_MINUS     = new minus("minus");
#endif
        U_ARGMAX    = new argmax    ("argmax");

        // -------- delay_n --------
        U_DELAY_N->clk(clk);
        U_DELAY_N->rst(rst);                      
        U_DELAY_N->r_in_real(r_in_real);
        U_DELAY_N->r_in_imag(r_in_imag);
        U_DELAY_N->r_d1_real(r_d1_real);
        U_DELAY_N->r_d1_imag(r_d1_imag);
        U_DELAY_N->r_dN_out_real(r_dN_out_real);
        U_DELAY_N->r_dN_out_imag(r_dN_out_imag);

        // -------- phi_sum --------
        U_PHI_SUM->clk(clk);
        U_PHI_SUM->rst(rst);                   
        U_PHI_SUM->r_k_in_real(r_d1_real);
        U_PHI_SUM->r_k_in_imag(r_d1_imag);
        U_PHI_SUM->r_k_minus_N_in_real(r_dN_out_real);
        U_PHI_SUM->r_k_minus_N_in_imag(r_dN_out_imag);
        U_PHI_SUM->rho_in(rho_in);           
        U_PHI_SUM->phi_out(phi_out);

        // -------- gamma_sum --------
        U_GAMMA_SUM->clk(clk);
        U_GAMMA_SUM->rst(rst);
        U_GAMMA_SUM->r_k_in_real(r_d1_real);
        U_GAMMA_SUM->r_k_in_imag(r_d1_imag);
        U_GAMMA_SUM->r_k_minus_N_in_real(r_dN_out_real);
        U_GAMMA_SUM->r_k_minus_N_in_imag(r_dN_out_imag);
        U_GAMMA_SUM->gamma_out_real(gamma_out_real);
        U_GAMMA_SUM->gamma_out_imag(gamma_out_imag);

        // -------- mag --------
        U_MAG->clk(clk);
        U_MAG->rst(rst);
        U_MAG->gm_in_real(gamma_out_real);
        U_MAG->gm_in_imag(gamma_out_imag);
        U_MAG->mag_out(mag_out);

        // -------- angle  --------
        U_ANGLE->clk(clk);
        U_ANGLE->rst(rst); 
        U_ANGLE->gm_in_real(gamma_out_real);
        U_ANGLE->gm_in_imag(gamma_out_imag);
        U_ANGLE->ang_out(ang_out);

        // -------- minus: λ = |γ| − ρ·Φ --------
        U_MINUS->clk(clk);
        U_MINUS->rst(rst);            
        U_MINUS->mag_in(mag_out);
        U_MINUS->phi_in(phi_out);
        U_MINUS->rho_in(rho_in);        
        U_MINUS->lambda_out(lambda_out);

        // -------- argmax over 256 --------
        U_ARGMAX->clk(clk);
        U_ARGMAX->rst(rst);             
        U_ARGMAX->angle_in(ang_out);
        U_ARGMAX->lambda_in(lambda_out);
        U_ARGMAX->theta_out(theta_sig);
        U_ARGMAX->eps_out(eps_out);

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

    // Pretty monitor: print all connected signals (no valid flags)
    void print_all_proc() {
        std::cout.setf(std::ios::fixed);
        std::cout << std::setprecision(6);
        const int W = 7;

        if (!header_printed) {
            std::cout << std::right << std::setw(W) << "Time"
                      << " | " << std::setw(W) << "r_in_real"    << " " << std::setw(W) << "r_in_imag"
                      << " | " << std::setw(W) << "r_d1_real"    << " " << std::setw(W) << "r_d1_imag"
                      << " | " << std::setw(W) << "r_dN_real"    << " " << std::setw(W) << "r_dN_imag"
                      << " | " << std::setw(W) << "phi_out"
                      << " | " << std::setw(W) << "gamma_out_r"  << " " << std::setw(W) << "gamma_out_i"
                      << " | " << std::setw(W) << "mag_out"
                      << " | " << std::setw(W) << "ang_out"
                      << " | " << std::setw(W) << "lambda_out"
                      << " | " << std::setw(W) << "theta"
                      << " | " << std::setw(W) << "eps_out"
                      << "\n";

            int sep_len =
                W + 3
              + (W*2+1)             // r_in
              + 3 + (W*2+1)         // r_d1
              + 3 + (W*2+1)         // r_dN
              + 3 + W               // phi_out
              + 3 + (W*2+1)         // gamma_out real/imag
              + 3 + W               // mag_out
              + 3 + W               // ang_out
              + 3 + W               // lambda_out
              + 3 + W               // theta
              + 3 + W;              // eps_out

            std::cout << std::string(sep_len, '-') << "\n";
            header_printed = true;
        }
        std::cout << std::right << std::setw(W) << sc_core::sc_time_stamp()
                  << " | " << std::setw(W) << fmt3(r_in_real.read())        << " " << std::setw(W) << fmt3(r_in_imag.read())
                  << " | " << std::setw(W) << fmt3(r_d1_real.read())        << " " << std::setw(W) << fmt3(r_d1_imag.read())
                  << " | " << std::setw(W) << fmt3(r_dN_out_real.read())    << " " << std::setw(W) << fmt3(r_dN_out_imag.read())
                  << " | " << std::setw(W) << fmt3(phi_out.read())
                  << " | " << std::setw(W) << fmt3(gamma_out_real.read())   << " " << std::setw(W) << fmt3(gamma_out_imag.read())
                  << " | " << std::setw(W) << fmt3(mag_out.read())
                  << " | " << std::setw(W) << fmt3(ang_out.read())
                  << " | " << std::setw(W) << fmt3(lambda_out.read())
                  << " | " << std::setw(W) << short(theta_sig.read())
                  << " | " << std::setw(W) << fmt3(eps_out.read())
                  << "\n";
    }
};
