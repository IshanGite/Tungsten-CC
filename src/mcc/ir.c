#include "mcc/ir.h"
#include <stdlib.h>
#include <string.h>

static IRFunction *current_func = NULL;

static IRBlock *ir_new_block(IRFunction *func) {
    IRBlock *block = calloc(1, sizeof(IRBlock));
    block->id = func->block_count;
    if (func->block_count >= func->block_capacity) {
        func->block_capacity = func->block_capacity == 0 ? 4 : func->block_capacity * 2;
        func->blocks = realloc(func->blocks, func->block_capacity * sizeof(IRBlock *));
    }
    func->blocks[func->block_count++] = block;
    return block;
}

static void ir_generate_func(IRProgram *prog, ASTNode *func_node) {
    if (prog->func_count >= prog->func_capacity) {
        prog->func_capacity = prog->func_capacity == 0 ? 4 : prog->func_capacity * 2;
        prog->functions = realloc(prog->functions, prog->func_capacity * sizeof(IRFunction *));
    }
    IRFunction *func = calloc(1, sizeof(IRFunction));
    func->name = func_node->name ? func_node->name : "anonymous";
    current_func = func;
    
    ir_new_block(func); // entry block
    prog->functions[prog->func_count++] = func;
}

IRProgram *ir_generate(ASTNode *ast) {
    if (!ast) return NULL;
    IRProgram *prog = calloc(1, sizeof(IRProgram));
    
    // Stub: generate IR for function declarations
    if (ast->kind == AST_PROGRAM) {
        for (size_t i = 0; i < ast->child_count; ++i) {
            if (ast->children[i]->kind == AST_FUNC_DECL) {
                ir_generate_func(prog, ast->children[i]);
            }
        }
    }
    return prog;
}

void ir_free(IRProgram *prog) {
    if (!prog) return;
    for (size_t i = 0; i < prog->func_count; ++i) {
        IRFunction *func = prog->functions[i];
        for (size_t j = 0; j < func->block_count; ++j) {
            IRBlock *block = func->blocks[j];
            free(block->instrs);
            free(block->preds);
            free(block->succs);
            free(block);
        }
        free(func->blocks);
        free(func);
    }
    free(prog->functions);
    free(prog);
}
