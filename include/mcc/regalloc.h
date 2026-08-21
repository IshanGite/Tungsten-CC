#ifndef MCC_REGALLOC_H
#define MCC_REGALLOC_H

#include "mcc/ssa.h"

typedef struct {
    int *allocation; // Virtual Reg ID to PhysReg map
} RegAllocResult;

RegAllocResult *allocate_registers(IRFunction *func);
void regalloc_free(RegAllocResult *res);

#endif // MCC_REGALLOC_H
