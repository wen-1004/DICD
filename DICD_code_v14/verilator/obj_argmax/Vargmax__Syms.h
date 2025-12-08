// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VARGMAX__SYMS_H_
#define VERILATED_VARGMAX__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vargmax.h"

// INCLUDE MODULE CLASSES
#include "Vargmax___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vargmax__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vargmax* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vargmax___024root              TOP;

    // CONSTRUCTORS
    Vargmax__Syms(VerilatedContext* contextp, const char* namep, Vargmax* modelp);
    ~Vargmax__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
