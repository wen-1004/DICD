g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib64 -lsystemc -lm EstimatorTop.cpp delay_n.cpp phi_sum.cpp gamma_sum.cpp mag.cpp angle.cpp minus.cpp argmax.cpp select_eps.cpp main.cpp -o full_test
