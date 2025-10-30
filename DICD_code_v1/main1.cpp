#include <systemc.h>
#include "delay_n.cpp"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 10, SC_NS);
    sc_signal<bool> reset;
    sc_signal<double> r_in_real, r_in_imag;
    sc_signal<double> r_out_real, r_out_imag;
    sc_signal<double> r_delayed_real, r_delayed_imag;
    sc_signal<bool> valid_out;

    delay_n my_delay("my_delay");
    my_delay.clk(clk);
    my_delay.reset(reset);
    my_delay.r_in_real(r_in_real);
    my_delay.r_in_imag(r_in_imag);
    my_delay.r_out_real(r_out_real);
    my_delay.r_out_imag(r_out_imag);
    my_delay.r_delayed_out_real(r_delayed_real);
    my_delay.r_delayed_out_imag(r_delayed_imag);
    my_delay.valid_out(valid_out);

    sc_start(0, SC_NS);
    reset = true;
    sc_start(10, SC_NS);
    reset = false;

    for (int i = 0; i < 300; ++i) {
        r_in_real = 254 + i;
        r_in_imag = 25.4 + i*0.1;
        sc_start(10, SC_NS);

        std::cout << "@" << sc_time_stamp() 
                  << " | Rin(r,i)=(" << r_in_real.read() << "," << r_in_imag.read() << ")"
                  << " | Rout(r,i)=(" << r_out_real.read() << "," << r_out_imag.read() << ")"
                  << " | Rdel(r,i)=(" << r_delayed_real.read() << "," << r_delayed_imag.read() << ")"
                  << " | Valid=" << valid_out.read()
                  << std::endl;
    }

    return 0;
}

