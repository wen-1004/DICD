#include <systemc>
#include <algorithm> 
#include <iostream>
#include <iomanip>

#include "../include/data_type.hpp"

using namespace sc_core;
using namespace sc_dt;

struct argmax : public sc_module {
    sc_in<bool>        clk;
    sc_in<bool>        rst;
    sc_in<lambda_t> lambda_in;
    sc_in<ang_t>    angle_in;
    sc_out<theta_t> theta_out;
    sc_out<eps_t>   eps_out;
  
    static const int N = 256;
    const double MIN_VAL = -32.0;
  
    SC_HAS_PROCESS(argmax);
    argmax(sc_module_name n) : sc_module(n) {
        SC_CTHREAD(proc, clk.pos());
        reset_signal_is(rst, false);
    }
  
    void proc() {
        const PI_t INV_TWO_PI = PI_t("0b0.0010100011"); // 1/(2*pi) approx 0.15915494309189533577
        lambda_t current_max = MIN_VAL;
        int current_max_idx = 0;
        ang_t current_ang = 0;
        int count = -282; // -275
        theta_out.write(0);
        eps_out.write(0);

        wait();
    
        while (true) {
            lambda_t new_val = lambda_in.read();
            ang_t ang_new = angle_in.read();
    
            if (count == 0) {
                current_max = new_val;
                current_max_idx = 255; // Newest value starts at index 255
                current_ang = ang_new;
            } else {
                current_max_idx--;
                if (new_val >= current_max) {
                    current_max = new_val;
                    current_max_idx = 255;
                    current_ang = ang_new;
                }
            }

            theta_out.write(current_max_idx);
            theta_t th = 255 - current_max_idx;
            std::cout << "Count: " << count << std::endl;

            count++;
            if (count >= N) {
                count = 0; // Reset counter for the next block
                current_max = MIN_VAL; // Reset max for the next block
                current_max_idx = N;
            }
            /*--- select ---*/
            eps_t eps = current_ang * INV_TWO_PI;
 
            eps_out.write(eps);
            wait();
       }
    }
};
