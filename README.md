# DICD

This is the systemC implementation of "ML Estimation of Time and Frequency Offset in OFDM Systems, IEEE Transactions on Signal processing, 1997". We will build the system using systemC from algorithm level to bit-accurate/cycle-accurate, and write RTL and perform HW/SW co-simulation.

## Developement log

- Version 1: Initial build, wire connection and testbench formation
- Version 2: First standalone system simulation with all signal using "double"
- Version 3: Replace C++ Primatives with user-defined SC data type
- Version 4: Debugging, adjust Alpla-max approximation parameter, passed testcase
- Version 5: Trim redundant bits for datapath
- Version 6: Further reduce bits for datapath
- Version 7: Add 1 more latency in the system
- Version 8: HW/SW co-simulation, replace "minus" module for example
- Version 9: Remove 2 lines of buffer, remove select_eps module
- Version 10: Final version of systemc, datapath optimization, invert reset
- Version 11: RTL MINUS, ARGMAX finish, 9 cycle latency
- Version 12: ANGLE, DELAY_N finished, add to 10 cycle latency
- Version 13: PHI_SUM, GAMMA_SUM finished, add to 12 cycle latency
- Version 14: MAG, Adjust I/O, add Top, sim pass
- Version 15: Optimized for pipeline MAG, add to 13 cycle latency

## How to run

1. (verilator) ./run_varilator.sh to "verilate" RTL module to C object
2. ./run_sim.sh to compile executable file
3. ./full_test prog{x} to run simulation
