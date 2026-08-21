#ifndef MCC_CODEGEN_H
#define MCC_CODEGEN_H

#include "mcc/ir.h"
#include "mcc/regalloc.h"
#include <stdio.h>

void codegen_amd64(IRProgram *prog, RegAllocResult *alloc, FILE *out);

#endif // MCC_CODEGEN_H
