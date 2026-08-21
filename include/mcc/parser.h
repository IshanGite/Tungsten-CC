#ifndef MCC_PARSER_H
#define MCC_PARSER_H

#include "mcc/ast.h"
#include "mcc/lexer.h"
#include <stdbool.h>

typedef struct {
    Lexer *lexer;
    Token current;
    Token previous;
    bool had_error;
    bool panic_mode;
} Parser;

ASTNode *parse(Lexer *lexer);

#endif // MCC_PARSER_H
