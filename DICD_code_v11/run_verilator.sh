verilator -cc --sv src/rtl/minus.sv -Iinclude -Mdir verilator/obj_minus -Wall
verilator -cc --sv src/rtl/argmax.sv -Iinclude -Mdir verilator/obj_argmax -Wall
make -C verilator/obj_minus -f Vminus.mk Vminus__ALL.a
make -C verilator/obj_argmax -f Vargmax.mk Vargmax__ALL.a
