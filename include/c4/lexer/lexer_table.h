#ifndef __c4_lexer_lexer_table_h__
#define __c4_lexer_lexer_table_h__

#include "c4/tools/str.h"

#define c4_skip_char_token_list \
    X('\n') \
    X('\t') \
    X(' ') \

#define c4_single_char_token_list \
    X(c4_token_lparen, '(') \
    X(c4_token_rparen, ')') \
    X(c4_token_lbracket, '[') \
    X(c4_token_rbracket, ']') \
    X(c4_token_lbrace, '{') \
    X(c4_token_rbrace, '}') \
    \
    X(c4_token_comma, ',') \
    X(c4_token_dot, '.') \
    X(c4_token_ampersand, '&') \
    \
    X(c4_token_colon, ':') \
    X(c4_token_semicolon, ';') \
    \
    X(c4_token_plus, '+') \
    X(c4_token_minus, '-') \
    X(c4_token_star, '*') \
    X(c4_token_slash, '/') \
    X(c4_token_backslash, '\\') \
    \
    X(c4_token_lt, '<') \
    X(c4_token_gt, '>') \
    X(c4_token_eq, '=') \
    \
    X(c4_token_bang, '!') \

#define c4_keyword_token_list \
    X(c4_token_let, "let") \
    X(c4_token_fn, "fn") \
    X(c4_token_struct, "struct") \
    X(c4_token_return, "return") \

#define c4_special_token_list \
    X(c4_token_ident) \
    X(c4_token_num) \
    X(c4_token_eof) \

typedef enum {

#define X(type, c) type,
    c4_single_char_token_list
#undef X

#define X(type, keyword) type,
    c4_keyword_token_list
#undef X

#define X(type) type,
    c4_special_token_list
#undef X

} c4_token_type;

typedef struct {
    c4_token_type type;
    bool has_some;
} c4_token_type_opt;

bool
c4_token_is_skip_char(
    char c
);

c4_token_type_opt 
c4_token_is_single_char(
    char c
);

c4_token_type_opt 
c4_token_is_keyword(
    c4_str keyword
);

c4_str 
c4_token_type_to_strv(
    c4_token_type type
);

#endif /* __c4_lexer_lexer_table_h__ */
