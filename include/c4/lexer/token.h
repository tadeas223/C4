#ifndef __c4_lexer_token_h__
#define __c4_lexer_token_h__

#include "c4/tools/sb.h"
#include "c4/tools/str_span.h"
#include "c4/lexer/lexer_table.h"

typedef struct {
    c4_token_type type;
    c4_str_span span;
} c4_token;

c4_token c4_token_make(
    c4_token_type type,
    c4_str source,
    c4_u32 start,
    c4_u32 end
);

void
c4_token_to_str(
    c4_token* self, 
    c4_sb* sb
);

#endif /* __c4_lexer_token_h__ */
