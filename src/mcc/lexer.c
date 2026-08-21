#include "mcc/lexer.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void lexer_init(Lexer *lexer, const char *source) {
    lexer->source = source;
    lexer->current = source;
    lexer->line = 1;
    lexer->column = 1;
}

static bool is_at_end(Lexer *lexer) { return *lexer->current == '\0'; }
static char advance(Lexer *lexer) { lexer->column++; return *lexer->current++; }
static char peek(Lexer *lexer) { return *lexer->current; }

Token lexer_next_token(Lexer *lexer) {
    if (is_at_end(lexer)) {
        Token t = {TOK_EOF, lexer->current, 0, lexer->line, lexer->column};
        return t;
    }
    // minimal stub for now
    char c = advance(lexer);
    Token t = {TOK_ERROR, lexer->current - 1, 1, lexer->line, lexer->column - 1};
    return t;
}
