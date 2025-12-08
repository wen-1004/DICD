// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VMINUS__SYMS_H_
#define VERILATED_VMINUS__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vminus.h"

// INCLUDE MODULE CLASSES
#include "Vminus___024root.h"
#include "Vminus___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vminus__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vminus* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vminus___024root               TOP;

    // CONSTRUCTORS
    Vminus__Syms(VerilatedContext* contextp, const char* namep, Vminus* modelp);
    ~Vminus__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
