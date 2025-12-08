// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VDELAY_N__SYMS_H_
#define VERILATED_VDELAY_N__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vdelay_n.h"

// INCLUDE MODULE CLASSES
#include "Vdelay_n___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vdelay_n__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vdelay_n* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vdelay_n___024root             TOP;

    // CONSTRUCTORS
    Vdelay_n__Syms(VerilatedContext* contextp, const char* namep, Vdelay_n* modelp);
    ~Vdelay_n__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
