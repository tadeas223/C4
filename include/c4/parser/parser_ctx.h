#ifndef __c4_parser_parser_ctx_h__
#define __c4_parser_parser_ctx_h__

#include "c4/parser/ast_node.h"
#include "c4/lexer/token.h"
#include "c4/tools/types.h"

typedef struct {
    c4_str source;
    c4_token* tokens;
    c4_u32 index;
} c4_parser_ctx;

c4_parser_ctx
c4_parser_ctx_make(
    c4_str source, 
    c4_token* tokens
);

c4_token 
c4_parser_ctx_pop(
    c4_parser_ctx* self
);

c4_token
c4_parser_ctx_pop_expect(
    c4_parser_ctx* self,
    c4_token_type expected
);

c4_token 
c4_parser_ctx_peek(
    c4_parser_ctx* self,
    c4_u32 offset
);

bool 
c4_parser_ctx_has_tokens(
    c4_parser_ctx* self
);

c4_u32 
c4_parser_ctx_mark(
    c4_parser_ctx* self
);

void 
c4_parser_ctx_reset(
    c4_parser_ctx* self,
    c4_u32 mark
);

#endif /* __c4_parser_parser_ctx_h__ */
