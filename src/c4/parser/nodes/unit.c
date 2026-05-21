#include "c4/parser/nodes/dtype.h"
#include "c4/parser/nodes/expr.h"
#include "c4/parser/nodes/fn.h"
#include "c4/parser/nodes/param.h"
#include "c4/parser/nodes/struct.h"
#include "c4/parser/parser_ctx.h"
#include "c4/tools/sb.h"
#include "c4/tools/sb_kvp.h"
#include "c4/tools/str.h"
#include "c4/tools/str_span.h"
#include <inttypes.h>
#include <stdlib.h>
#include "c4/parser/nodes/unit.h"
#include "lib/stb_ds.h"

c4_ast_node*
c4_ast_node_unit_make(
    c4_str_span span,
    c4_ast_node** node_list
) {
    c4_ast_node* self = malloc(sizeof(*self));

    self->span = span;
    self->node_type = c4_ast_unit;
    self->free_func = c4_ast_node_unit_free;
    self->to_str_func = c4_ast_node_unit_to_str;

    self->unit.node_list = node_list;
    
    return self;
}

void 
c4_ast_node_unit_free(
    c4_ast_node* self
) {
    for(c4_u32 i = 0; i < arrlen(self->unit.node_list); i++) {
        c4_ast_node_free(self->unit.node_list[i]); 
    }
    arrfree(self->unit.node_list);

    free(self);
}

void 
c4_ast_node_unit_to_str(
    c4_ast_node* self,
    c4_sb* sb
) {
    c4_sb_kvp_start(sb, c4_strv_lit("unit"));
    {
        c4_sb_kvp_append_key(sb, c4_strv_lit("node_list"));
        c4_sb_line_end(sb);

        c4_sb_kvp_value_start(sb);
        {
            for(c4_u32 i = 0; i < arrlen(self->unit.node_list); i++) {
                c4_ast_node_to_str(self->unit.node_list[i], sb); 
            }
        }
        c4_sb_kvp_end(sb);
    }
    c4_sb_kvp_end(sb);
}

c4_ast_node* 
c4_ast_node_unit_parse(
    c4_parser_ctx* ctx
) {
    c4_u32 mark = c4_parser_ctx_mark(ctx);
    c4_ast_node** node_list = NULL;
    
    c4_token eof = c4_parser_ctx_peek(ctx, 0);
    while(eof.type != c4_token_eof) {
        c4_token token = c4_parser_ctx_peek(ctx, 0);
        c4_ast_node* node = NULL;
        switch(token.type) {
            case c4_token_struct:
                node = c4_ast_node_struct_parse(ctx);
                break;
            case c4_token_fn:
                node = c4_ast_node_fn_parse(ctx);
                break;
            default:
                node = NULL;
                break;
        }

        if(node == NULL) {
            c4_str_span_panic(&token.span, c4_strv_lit("invalid token"));
        }

        arrput(node_list, node);
        eof = c4_parser_ctx_peek(ctx, 0);
    }
    
    c4_str_span span = c4_str_span_make_bounds(
        ctx->source,
        mark,
        c4_parser_ctx_mark(ctx)
    );

    return c4_ast_node_unit_make(span, node_list);
}
