// Make sure we have core SystemC
#include <systemc>

// Some SystemC builds only include fixed-point if you pull in fx headers.
// Include them explicitly to avoid SC_INCLUDE_FX / include-order issues.
#include <sysc/datatypes/fx/sc_fixed.h>
#include <sysc/datatypes/fx/sc_ufixed.h>

using sc_dt::sc_fixed;
using sc_dt::sc_ufixed;
using sc_dt::sc_uint;

using r_t      = sc_fixed<16,1>;
using rho_t    = sc_fixed<8,1>;
using eps_t    = sc_fixed<21,1>;
using theta_t  = sc_uint<8>;

using phi_t    = sc_fixed<64,32>;
using gamma_t  = sc_fixed<64,32>;
using mag_t    = sc_ufixed<64,32>;
using ang_t    = sc_fixed<64,32>;
using lambda_t = sc_fixed<64,32>;
