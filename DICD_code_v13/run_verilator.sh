verilator -cc --sv src/rtl/minus.sv -Iinclude -Mdir verilator/obj_minus -Wall
verilator -cc --sv src/rtl/argmax.sv -Iinclude -Mdir verilator/obj_argmax -Wall
verilator -cc --sv src/rtl/angle.sv -Iinclude -Mdir verilator/obj_angle -Wall
verilator -cc --sv src/rtl/delay_n.sv -Iinclude -Mdir verilator/obj_delay_n -Wall
verilator -cc --sv src/rtl/phi_sum.sv -Iinclude -Mdir verilator/obj_phi_sum -Wall
verilator -cc --sv src/rtl/gamma_sum.sv -Iinclude -Mdir verilator/obj_gamma_sum -Wall
make -C verilator/obj_minus -f Vminus.mk Vminus__ALL.a
make -C verilator/obj_argmax -f Vargmax.mk Vargmax__ALL.a
make -C verilator/obj_angle -f Vangle.mk Vangle__ALL.a
make -C verilator/obj_delay_n -f Vdelay_n.mk Vdelay_n__ALL.a
make -C verilator/obj_phi_sum -f Vphi_sum.mk Vphi_sum__ALL.a
make -C verilator/obj_gamma_sum -f Vgamma_sum.mk Vgamma_sum__ALL.a
