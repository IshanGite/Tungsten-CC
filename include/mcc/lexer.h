#ifndef MCC_LEXER_H
#define MCC_LEXER_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    TOK_EOF = 0,
    TOK_IDENTIFIER,
    TOK_NUMBER,
    TOK_STRING,
    TOK_CHAR,
    TOK_KW_INT,
    TOK_KW_RETURN,
    TOK_KW_IF,
    TOK_KW_ELSE,
    TOK_KW_WHILE,
    TOK_KW_FOR,
    TOK_KW_VOID,
    TOK_KW_CHAR,
    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,
    TOK_PERCENT,
    TOK_ASSIGN,
    TOK_EQ,
    TOK_NEQ,
    TOK_LT,
    TOK_LE,
    TOK_GT,
    TOK_GE,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_LBRACE,
    TOK_RBRACE,
    TOK_LBRACKET,
    TOK_RBRACKET,
    TOK_COMMA,
    TOK_SEMICOLON,
    TOK_ERROR
} TokenKind;

typedef struct {
    TokenKind kind;
    const char *start;
    size_t length;
    int line;
    int column;
} Token;

typedef struct {
    const char *source;
    const char *current;
    int line;
    int column;
} Lexer;

void lexer_init(Lexer *lexer, const char *source);
Token lexer_next_token(Lexer *lexer);

#endif // MCC_LEXER_H
