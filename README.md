# DICD

This is the systemC implementation of "ML Estimation of Time and Frequency Offset in OFDM Systems, IEEE 1997". We will build the system using systemC from algorithm level to bit-accurate/cycle-accurate, and write RTL and perform HW/SW co-simulation.

## Developement log

- Version 1: Initial build, wire connection and testbench formation
- Version 2: First standalone system simulation with all signal using "double"
- Version 3: Replace "double" with user-defined data type
- Version 4: Debugging, adjust Alpla-max approximation parameter, passed testcase
- Version 5: Trim redundant bits for datapath
- Version 6: Further reduce bits for datapath
- Version 7: Add 1 more latency in the system
- Version 8: HW/SW co-simulation, replace "minus" module for example

## How to run

1. ./run_sim.sh to compile executable file
2. (verilator) ./run_varilator.sh
3. ./full_test prog{x} to run simulation
