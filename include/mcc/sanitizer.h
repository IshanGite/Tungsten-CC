#ifndef MCC_SANITIZER_H
#define MCC_SANITIZER_H

#include "mcc/ir.h"

void sanitize_asan(IRProgram *prog);
void sanitize_ubsan(IRProgram *prog);

#endif // MCC_SANITIZER_H
