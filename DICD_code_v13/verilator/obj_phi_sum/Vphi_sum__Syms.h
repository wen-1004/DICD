// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VPHI_SUM__SYMS_H_
#define VERILATED_VPHI_SUM__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vphi_sum.h"

// INCLUDE MODULE CLASSES
#include "Vphi_sum___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vphi_sum__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vphi_sum* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vphi_sum___024root             TOP;

    // CONSTRUCTORS
    Vphi_sum__Syms(VerilatedContext* contextp, const char* namep, Vphi_sum* modelp);
    ~Vphi_sum__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
