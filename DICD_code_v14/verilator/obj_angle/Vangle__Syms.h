// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VANGLE__SYMS_H_
#define VERILATED_VANGLE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vangle.h"

// INCLUDE MODULE CLASSES
#include "Vangle___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vangle__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vangle* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vangle___024root               TOP;

    // CONSTRUCTORS
    Vangle__Syms(VerilatedContext* contextp, const char* namep, Vangle* modelp);
    ~Vangle__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
