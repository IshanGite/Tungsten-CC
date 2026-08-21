#include "mcc/codegen.h"

void codegen_amd64(IRProgram *prog, RegAllocResult *alloc, FILE *out) {
    if (!prog || !alloc || !out) return;
    
    fprintf(out, ".intel_syntax noprefix\n");
    
    for (size_t i = 0; i < prog->func_count; ++i) {
        IRFunction *func = prog->functions[i];
        fprintf(out, ".global %s\n", func->name);
        fprintf(out, "%s:\n", func->name);
        
        // Prologue
        fprintf(out, "  push rbp\n");
        fprintf(out, "  mov rbp, rsp\n");
        
        // Body (Stub)
        for (size_t b = 0; b < func->block_count; ++b) {
            fprintf(out, ".L%s_block%d:\n", func->name, func->blocks[b]->id);
            // Translate IRInstr to AMD64 Assembly...
        }
        
        // Epilogue
        fprintf(out, "  pop rbp\n");
        fprintf(out, "  ret\n");
    }
}
