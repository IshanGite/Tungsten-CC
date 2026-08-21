#ifndef MCC_IR_H
#define MCC_IR_H

#include "mcc/ast.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    IR_ADD, IR_SUB, IR_MUL, IR_DIV, IR_MOD,
    IR_CMP_EQ, IR_CMP_NEQ, IR_CMP_LT, IR_CMP_LE, IR_CMP_GT, IR_CMP_GE,
    IR_ASSIGN, IR_LOAD, IR_STORE, IR_ALLOCA,
    IR_JMP, IR_CJMP, IR_RET, IR_CALL, IR_PHI
} IROpcode;

typedef struct { int id; } IRReg;
typedef struct IRBlock IRBlock;

typedef struct {
    IROpcode op;
    IRReg dest;
    IRReg src1;
    IRReg src2;
    int immediate;
    const char *name;
    IRBlock *target_true;
    IRBlock *target_false;
} IRInstr;

struct IRBlock {
    int id;
    IRInstr *instrs;
    size_t instr_count;
    size_t instr_capacity;
    
    IRBlock **preds;
    size_t pred_count;
    IRBlock **succs;
    size_t succ_count;
    
    IRBlock *idom;
};

typedef struct {
    const char *name;
    IRBlock **blocks;
    size_t block_count;
    size_t block_capacity;
    int next_reg_id;
} IRFunction;

typedef struct {
    IRFunction **functions;
    size_t func_count;
    size_t func_capacity;
} IRProgram;

IRProgram *ir_generate(ASTNode *ast);
void ir_free(IRProgram *prog);

#endif // MCC_IR_H
