#include "c4/lexer/lexer_ctx.h"
#include "c4/lexer/lexer.h"

c4_token*
c4_lexer_tokenize(
    c4_str source
) {
    c4_lexer_ctx ctx = c4_lexer_ctx_make(source);

    return c4_lexer_ctx_tokenize(&ctx);
}
