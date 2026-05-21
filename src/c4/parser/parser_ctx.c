#include "c4/parser/parser_ctx.h"
#include "c4/tools/str_span.h"
#include "lib/stb_ds.h"

c4_parser_ctx 
c4_parser_ctx_make(
    c4_str source,
    c4_token* tokens
) {
    return (c4_parser_ctx) {
        .source =source,
        .tokens = tokens,
        .index = 0
    };
}

c4_token 
c4_parser_ctx_pop(
    c4_parser_ctx* self
) {
    if(self->index >= arrlen(self->tokens)) {
        c4_str_span span = c4_str_span_make(
            self->source, 
            self->index - 1,
            self->index
        );
        
        c4_str_span_panic(&span, c4_strv_lit("unexpected EOF"));
    }

    c4_token token = self->tokens[self->index];
    self->index++;
    return token;
}

c4_token
c4_parser_ctx_pop_expect(
    c4_parser_ctx* self,
    c4_token_type expected
) {
    c4_token token = c4_parser_ctx_pop(self);

    if(token.type != expected) {
        c4_str_span_panic(&token.span, c4_strv_lit("unexpected token")); 
    }

    return token;
}

bool
c4_parser_ctx_has_tokens(
    c4_parser_ctx* self
) {
    return self->index < arrlen(self->tokens);
}

c4_token 
c4_parser_ctx_peek(
    c4_parser_ctx* self,
    c4_u32 offset
) {
    c4_u32 index = self->index + offset;
    if(index >= arrlen(self->tokens)) {
        c4_str_span span = c4_str_span_make(
            self->source, 
            index - 1,
            index
        );
        
        c4_str_span_panic(&span, c4_strv_lit("unexpected EOF"));
    }

    c4_token token = self->tokens[index];
    return token;
}

c4_u32
c4_parser_ctx_mark(
    c4_parser_ctx* self
) {
    return self->index;
}

void
c4_parser_ctx_reset(
    c4_parser_ctx* self,
    c4_u32 mark
) {
    self->index = mark;
}
