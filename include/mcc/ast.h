#ifndef MCC_AST_H
#define MCC_AST_H

#include "mcc/lexer.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    AST_PROGRAM,
    AST_FUNC_DECL,
    AST_VAR_DECL,
    AST_BLOCK,
    AST_IF_STMT,
    AST_WHILE_STMT,
    AST_FOR_STMT,
    AST_RETURN_STMT,
    AST_EXPR_STMT,
    AST_BINARY_EXPR,
    AST_UNARY_EXPR,
    AST_LITERAL_EXPR,
    AST_VAR_EXPR,
    AST_ASSIGN_EXPR,
    AST_CALL_EXPR
} ASTNodeKind;

typedef struct ASTNode ASTNode;

struct ASTNode {
    ASTNodeKind kind;
    Token token;
    
    ASTNode *left;
    ASTNode *right;
    ASTNode *condition;
    ASTNode *body;
    ASTNode *else_body;
    ASTNode *init;
    ASTNode *increment;

    ASTNode **children;
    size_t child_count;
    size_t child_capacity;

    int value_int;
    const char *name;
};

ASTNode *ast_new_node(ASTNodeKind kind, Token token);
void ast_add_child(ASTNode *parent, ASTNode *child);
void ast_free(ASTNode *node);

#endif // MCC_AST_H
