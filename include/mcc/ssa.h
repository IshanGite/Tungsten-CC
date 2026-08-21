#ifndef MCC_SSA_H
#define MCC_SSA_H

#include "mcc/ir.h"

void ssa_build(IRProgram *prog);
void ssa_optimize(IRProgram *prog);

#endif // MCC_SSA_H
