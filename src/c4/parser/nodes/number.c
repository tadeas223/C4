#include "c4/parser/parser_ctx.h"
#include "c4/tools/sb.h"
#include "c4/tools/sb_kvp.h"
#include "c4/tools/str.h"
#include "c4/tools/str_span.h"
#include <stdlib.h>
#include "c4/parser/nodes/number.h"

c4_ast_node*
c4_ast_node_number_make(
    c4_str_span span,
    c4_str content
) {
    c4_ast_node* self = malloc(sizeof(*self));

    self->node_type = c4_ast_type;
    self->span = span;
    self->free_func = c4_ast_node_number_free;
    self->to_str_func = c4_ast_node_number_to_str;

    self->number.content = content;

    return self;
}

void 
c4_ast_node_number_free(
    c4_ast_node* self
) {
    free(self);
}

void 
c4_ast_node_number_to_str(
    c4_ast_node* self,
    c4_sb* sb
) {
    c4_sb_kvp_start(sb, c4_strv_lit("number"));
    {
        c4_sb_kvp_append_key(sb, c4_strv_lit("content"));
        
        c4_sb_kvp_value_start(sb);
        {
            c4_sb_append_str(sb, self->number.content);
        }
        c4_sb_kvp_value_end(sb);
        c4_sb_line_end(sb);
    }
    c4_sb_kvp_end(sb);
}

c4_ast_node*
c4_ast_node_number_parse(
    c4_parser_ctx* ctx
) {
    c4_str_span content;

    c4_token num1 = c4_parser_ctx_pop_expect(ctx, c4_token_num);
    
    c4_token dot = c4_parser_ctx_peek(ctx, 0);
    if(dot.type == c4_token_dot) {
        c4_parser_ctx_pop(ctx);
        
        c4_token num2 = c4_parser_ctx_pop_expect(ctx, c4_token_num);
        
        content = c4_str_span_make_bounds(
            ctx->source,
            num1.span.start,
            num2.span.start + num2.span.len
        );
    } else {
        content = c4_str_span_make_bounds(
            ctx->source,
            num1.span.start,
            num1.span.start + num1.span.len
        );
    }

    return c4_ast_node_number_make(content, c4_str_span_to_strv(&content));
}
