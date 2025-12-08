g++ -std=c++17 -DUSE_RTL_MINUS \
  -I"$SYSTEMC_HOME/include" \
  -Iinclude \
  -Isrc \
  -Iobj_minus \
  -I"$VERILATOR_ROOT/include" \
  -I"$VERILATOR_ROOT/include/vltstd" \
  sim/main.cpp \
  src/EstimatorTop.cpp \
  src/delay_n.cpp \
  src/phi_sum.cpp \
  src/gamma_sum.cpp \
  src/mag.cpp \
  src/angle.cpp \
  src/argmax.cpp \
  src/select_eps.cpp \
  verilator/obj_minus/Vminus__ALL.a \
  "$VERILATOR_ROOT/include/verilated.cpp" \
  "$VERILATOR_ROOT/include/verilated_threads.cpp" \
  -L"$SYSTEMC_HOME/lib64" \
  -lsystemc -lm -pthread \
  -o full_test