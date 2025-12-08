// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VGAMMA_SUM__SYMS_H_
#define VERILATED_VGAMMA_SUM__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vgamma_sum.h"

// INCLUDE MODULE CLASSES
#include "Vgamma_sum___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vgamma_sum__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vgamma_sum* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vgamma_sum___024root           TOP;

    // CONSTRUCTORS
    Vgamma_sum__Syms(VerilatedContext* contextp, const char* namep, Vgamma_sum* modelp);
    ~Vgamma_sum__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
