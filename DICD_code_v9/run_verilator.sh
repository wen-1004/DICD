verilator -cc --sv src/rtl/minus.sv -Iinclude -Mdir verilator/obj_minus -Wall
make -C verilator/obj_minus -f Vminus.mk Vminus__ALL.a
