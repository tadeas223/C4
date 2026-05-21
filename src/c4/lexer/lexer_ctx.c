#include "c4/lexer/lexer_table.h"
#include "c4/lexer/token.h"
#include "lib/stb_ds.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "c4/lexer/lexer_ctx.h"

c4_lexer_ctx
c4_lexer_ctx_make(
    c4_str source
) {
    return (c4_lexer_ctx) {
        .source = source,
        .index = 0
    };
}

void 
c4_lexer_ctx_push(
    c4_lexer_ctx* self
) {
    self->index--;
}

int 
c4_lexer_ctx_pop(
    c4_lexer_ctx* self
) {
    if(self->index >= self->source.len) {
        return -1;
    }

    char c = self->source.chars[self->index];
    self->index++;
    return c;
}

int 
c4_lexer_ctx_peek(
    c4_lexer_ctx* self,
    c4_u32 offset
) {
    c4_u32 index = self->index + offset;
    
    if(index >= self->source.len) {
        return -1;
    }

    return self->source.chars[index];
}

c4_str
c4_lexer_ctx_load_content(
    c4_lexer_ctx* self, 
    int (*cond)(int c)
) {
   c4_u32 start = c4_lexer_ctx_mark(self);

   while(
        c4_lexer_ctx_peek(self, 0) != -1 
        && cond((c4_lexer_ctx_peek(self, 0)))
   ) {
       c4_lexer_ctx_pop(self);
   }

   return c4_strv_make_bounds(
       self->source.chars,
       start,
       c4_lexer_ctx_mark(self)
   );
}

c4_u32
c4_lexer_ctx_mark(
    c4_lexer_ctx* self
) {
    return self->index;
}

void 
c4_lexer_ctx_reset(
    c4_lexer_ctx* self,
    c4_u32 mark
) {
    self->index = mark;
}

c4_token*
c4_lexer_ctx_tokenize(
    c4_lexer_ctx* self
) {
    c4_u32 mark = c4_lexer_ctx_mark(self);
    
    c4_token* tokens = NULL;
    
    int c_int = -1;
    while((c_int = c4_lexer_ctx_pop(self)) != -1) {
        c4_u32 start = c4_lexer_ctx_mark(self) - 1;

        char c = (char)c_int;
        
        if(c4_token_is_skip_char(c)) {
            continue;
        }

        if(isalpha(c)) {
            c4_lexer_ctx_push(self);
            c4_str content = c4_lexer_ctx_load_content(self, isalnum);
            
            c4_token_type type;
            const c4_token_type_opt opt = c4_token_is_keyword(content);
            if(opt.has_some) {
                type = opt.type;
            } else {
                type = c4_token_ident;
            }

            c4_token tok = c4_token_make(
                type,
                self->source,
                start,
                c4_lexer_ctx_mark(self)
            );

            arrput(tokens, tok);
            continue;
        }

        else if(isdigit(c)) {
            c4_lexer_ctx_push(self);
            c4_lexer_ctx_load_content(self, isdigit);

            c4_token tok = c4_token_make(
                c4_token_num,
                self->source,
                start,
                c4_lexer_ctx_mark(self)
            );

            arrput(tokens, tok);
            continue;
        }
        
        c4_token_type_opt opt = c4_token_is_single_char(c);
        if(opt.has_some) {
            c4_token tok = c4_token_make(
                opt.type,
                self->source,
                start,
                c4_lexer_ctx_mark(self)
            );

            arrput(tokens, tok);
        } else {
            printf("invalid character: '%c'\n", c);
            exit(1);
        }
    }
    
    c4_token eof = c4_token_make(c4_token_eof, self->source, self->source.len-1, self->source.len-1);
    
    arrput(tokens, eof);
    c4_lexer_ctx_reset(self, mark);
    
    return tokens;

}
