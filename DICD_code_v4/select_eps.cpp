#include <systemc>
#include <cmath>
#include <algorithm>
using namespace sc_core;
using namespace sc_dt;

#include "data_type.hpp"

struct select_eps : public sc_module {
  sc_in<ang_t>  angle_in;   
  sc_in<theta_t>  theta_in; 
  sc_out<eps_t>   eps_out; 

  static const int BUF_LEN = 256;
  ang_t angle_buf[BUF_LEN];

  SC_HAS_PROCESS(select_eps);
  select_eps(sc_module_name n) : sc_module(n) {
    for (int i = 0; i < BUF_LEN; ++i) angle_buf[i] = 0.0;

    SC_METHOD(proc);
    sensitive << angle_in << theta_in;
    dont_initialize();
  }

  void proc() {
    const PI_t TWO_PI = 6.28318530717958647692;

    ang_t ang_new = angle_in.read();
    for (int i = BUF_LEN - 1; i > 0; --i)
      angle_buf[i] = angle_buf[i - 1];
    angle_buf[0] = ang_new;

    theta_t th = 255 - theta_in.read();
    theta_t idx = th;
    ang_t sel_ang = angle_buf[idx];

    eps_t eps = sel_ang / TWO_PI;

    while (eps <= -0.5) eps += 1.0;
    while (eps >   0.5) eps -= 1.0;

    eps_out.write(eps);
  }
};

