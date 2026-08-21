#include "mcc/ast.h"
#include <stdlib.h>
#include <string.h>

ASTNode *ast_new_node(ASTNodeKind kind, Token token) {
    ASTNode *node = (ASTNode *)calloc(1, sizeof(ASTNode));
    if (!node) return NULL;
    node->kind = kind;
    node->token = token;
    return node;
}

void ast_add_child(ASTNode *parent, ASTNode *child) {
    if (!parent || !child) return;
    if (parent->child_count >= parent->child_capacity) {
        size_t new_capacity = parent->child_capacity == 0 ? 4 : parent->child_capacity * 2;
        ASTNode **new_children = (ASTNode **)realloc(parent->children, new_capacity * sizeof(ASTNode *));
        if (!new_children) return;
        parent->children = new_children;
        parent->child_capacity = new_capacity;
    }
    parent->children[parent->child_count++] = child;
}

void ast_free(ASTNode *node) {
    if (!node) return;
    ast_free(node->left);
    ast_free(node->right);
    ast_free(node->condition);
    ast_free(node->body);
    ast_free(node->else_body);
    ast_free(node->init);
    ast_free(node->increment);
    for (size_t i = 0; i < node->child_count; ++i) {
        ast_free(node->children[i]);
    }
    if (node->children) free(node->children);
    if (node->name) free((void *)node->name);
    free(node);
}
