#include "mcc/regalloc.h"
#include <stdlib.h>
#include <string.h>

RegAllocResult *allocate_registers(IRFunction *func) {
    if (!func || func->next_reg_id == 0) return NULL;
    
    RegAllocResult *res = malloc(sizeof(RegAllocResult));
    res->allocation = malloc(func->next_reg_id * sizeof(int));
    
    // Stub: Chaitin-Briggs allocator
    // Assigns mock physical registers to virtual registers
    for (int i = 0; i < func->next_reg_id; ++i) {
        res->allocation[i] = i % 14; 
    }
    
    return res;
}

void regalloc_free(RegAllocResult *res) {
    if (!res) return;
    free(res->allocation);
    free(res);
}
