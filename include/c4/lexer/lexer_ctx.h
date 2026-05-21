#ifndef __lexer_lexer_ctx_h__
#define __lexer_lexer_ctx_h__

#include "c4/lexer/token.h"
#include "c4/tools/str.h"

typedef struct {
    c4_u32 index;
    c4_str source;
} c4_lexer_ctx;

c4_lexer_ctx
c4_lexer_ctx_make(
    c4_str source
);

void 
c4_lexer_ctx_push(
    c4_lexer_ctx* self
);

int 
c4_lexer_ctx_pop(
    c4_lexer_ctx* self
);

int 
c4_lexer_ctx_peek(
    c4_lexer_ctx* self, 
    c4_u32 offset
);

c4_str 
c4_lexer_ctx_load_content(
    c4_lexer_ctx* self, 
    int (*cond)(int c)
);

c4_u32 
c4_lexer_ctx_mark(
    c4_lexer_ctx* self
);

void 
c4_lexer_ctx_reset(
    c4_lexer_ctx* self,
    c4_u32 mark
);

c4_token*
c4_lexer_ctx_tokenize(
    c4_lexer_ctx* self
);

#endif /* __lexer_lexer_ctx_h__ */
