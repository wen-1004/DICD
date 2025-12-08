g++ -std=c++17 \
  -I"$SYSTEMC_HOME/include" \
  -DUSE_RTL_MINUS \
  -DUSE_RTL_ARGMAX \
  -Iinclude \
  -Isrc \
  -Iobj_minus \
  -I"$VERILATOR_ROOT/include" \
  -I"$VERILATOR_ROOT/include/vltstd" \
  sim/main.cpp \
  src/EstimatorTop.cpp \
  verilator/obj_minus/Vminus__ALL.a \
  verilator/obj_argmax/Vargmax__ALL.a \
  "$VERILATOR_ROOT/include/verilated.cpp" \
  "$VERILATOR_ROOT/include/verilated_threads.cpp" \
  -L"$SYSTEMC_HOME/lib64" \
  -lsystemc -lm -pthread \
  -o full_test
