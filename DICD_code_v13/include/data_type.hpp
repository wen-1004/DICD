#include <systemc>
#include <sysc/datatypes/fx/sc_fixed.h>
#include <sysc/datatypes/fx/sc_ufixed.h>

using sc_dt::sc_fixed;
using sc_dt::sc_ufixed;
using sc_dt::sc_uint;

// I/O
using r_t      = sc_fixed<7,1>;
using rho_t    = sc_fixed<8,1>;
using eps_t    = sc_fixed<21,1>;
using theta_t  = sc_uint<8>;

// Port
using phi_t    = sc_fixed<14,6>;
using gamma_t  = sc_fixed<14,6>;
using mag_t    = sc_fixed<14,6>;
using ang_t    = sc_fixed<11,3>;
using lambda_t = sc_fixed<14,6>;

// Internal
using ambm_t   = sc_fixed<10,2>;
using PI_t     = sc_ufixed<8,0>;
using ratio_t  = sc_ufixed<8,0>;
