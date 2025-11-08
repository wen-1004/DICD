g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib64 -lsystemc -lm \
src/EstimatorTop.cpp \
src/delay_n.cpp \
src/phi_sum.cpp \
src/gamma_sum.cpp \
src/mag.cpp \
src/angle.cpp \
src/minus.cpp \
src/argmax.cpp \
src/select_eps.cpp \
sim/main.cpp \
-o full_test
