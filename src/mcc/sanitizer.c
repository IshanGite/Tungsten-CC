#include "mcc/sanitizer.h"
#include <stdlib.h>

void sanitize_asan(IRProgram *prog) {
    if (!prog) return;
    // Stub: Inject ASan shadow memory checks for IR_LOAD and IR_STORE
}

void sanitize_ubsan(IRProgram *prog) {
    if (!prog) return;
    // Stub: Inject UBSan divide-by-zero checks for IR_DIV and IR_MOD
}
