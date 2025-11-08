#include <systemc>
#include <algorithm>  // std::max_element, std::distance
#include <iostream>
#include <iomanip>
#include "data_type.hpp"

using namespace sc_core;
using namespace sc_dt;

struct argmax : public sc_module {
    sc_in<bool>        clk;
    sc_in<bool>        rst;
    sc_in<lambda_t> lambda_in;
    sc_out<theta_t> theta_out;
  
    static const int N = 256;
    static const int N_DELAY = 8;
    static const int N_TOP = 3;
  
    lambda_t buf[N];
    theta_t delay_line[N_DELAY];
  
    SC_HAS_PROCESS(argmax);
    argmax(sc_module_name n) : sc_module(n) {
        SC_CTHREAD(proc, clk.pos());
        reset_signal_is(rst, false);
    }
  
    void proc() {
        for (int i = 0; i < N; ++i) buf[i] = 0.0;
        for (int i = 0; i < N_DELAY; ++i) delay_line[i] = 0;
        theta_out.write(0);
        wait();
    
        while (true) {
            if (!rst.read()) {
                for (int i = 0; i < N; ++i) buf[i] = 0.0;
                for (int i = 0; i < N_DELAY; ++i) delay_line[i] = 0;
                theta_out.write(0);
            } else {
                lambda_t new_val = lambda_in.read();
        
                for (int i = N - 1; i > 0; --i)
                    buf[i] = buf[i - 1];
                buf[0] = new_val;
        
                theta_t pos = std::distance(buf, std::max_element(buf, buf + N));
                theta_t idx = 255 - pos;
        
                for (int i = N_DELAY - 1; i > 0; --i)
                    delay_line[i] = delay_line[i - 1];
                delay_line[0] = static_cast<theta_t>(idx);
        
                theta_out.write(delay_line[N_DELAY - 1]);
            }
            wait();
        }
    }
};
