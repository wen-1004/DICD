g++ -std=c++17 \
  -DUSE_PHI_SUM \
  -DUSE_MINUS \
  -DUSE_MAG \
  -DUSE_ANGLE \
  -DUSE_ARGMAX \
  -DUSE_GAMMA_SUM \
  -DUSE_DELAY_N \
  -I"$SYSTEMC_HOME/include" \
  -I"$VERILATOR_ROOT/include" \
  -I"$VERILATOR_ROOT/include/vltstd" \
  sim/main.cpp \
  src/EstimatorTop.cpp \
  verilator/obj_minus/Vminus__ALL.a \
  verilator/obj_argmax/Vargmax__ALL.a \
  verilator/obj_angle/Vangle__ALL.a \
  verilator/obj_delay_n/Vdelay_n__ALL.a \
  verilator/obj_phi_sum/Vphi_sum__ALL.a \
  verilator/obj_gamma_sum/Vgamma_sum__ALL.a \
  verilator/obj_mag/Vmag__ALL.a \
  "$VERILATOR_ROOT/include/verilated.cpp" \
  "$VERILATOR_ROOT/include/verilated_threads.cpp" \
  -L"$SYSTEMC_HOME/lib64" \
  -lsystemc -lm -pthread \
  -o full_test
