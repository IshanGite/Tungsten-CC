#include "mcc/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void error_at(Parser *parser, Token *token, const char *message) {
    if (parser->panic_mode) return;
    parser->panic_mode = true;
    fprintf(stderr, "[line %d] Error", token->line);
    if (token->kind == TOK_EOF) {
        fprintf(stderr, " at end");
    } else if (token->kind == TOK_ERROR) {
        // Nothing.
    } else {
        fprintf(stderr, " at '%.*s'", (int)token->length, token->start);
    }
    fprintf(stderr, ": %s\n", message);
    parser->had_error = true;
}

static void advance(Parser *parser) {
    parser->previous = parser->current;
    for (;;) {
        parser->current = lexer_next_token(parser->lexer);
        if (parser->current.kind != TOK_ERROR) break;
        error_at(parser, &parser->current, "Lexical error");
    }
}

static void consume(Parser *parser, TokenKind kind, const char *message) {
    if (parser->current.kind == kind) {
        advance(parser);
        return;
    }
    error_at(parser, &parser->current, message);
}

// Stub implementation for now
static ASTNode *expression(Parser *parser) {
    // We would implement Pratt parsing here
    return ast_new_node(AST_LITERAL_EXPR, parser->previous);
}

static ASTNode *statement(Parser *parser) {
    return ast_new_node(AST_EXPR_STMT, parser->previous);
}

static ASTNode *declaration(Parser *parser) {
    return ast_new_node(AST_VAR_DECL, parser->previous);
}

ASTNode *parse(Lexer *lexer) {
    Parser parser;
    parser.lexer = lexer;
    parser.had_error = false;
    parser.panic_mode = false;
    advance(&parser);

    ASTNode *root = ast_new_node(AST_PROGRAM, parser.current);
    while (parser.current.kind != TOK_EOF) {
        ast_add_child(root, declaration(&parser));
        if (parser.current.kind != TOK_EOF) {
            advance(&parser); // prevent infinite loop in stub
        }
    }
    return root;
}
