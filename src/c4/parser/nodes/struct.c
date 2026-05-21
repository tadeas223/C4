#include "c4/parser/ast_node.h"
#include "c4/parser/nodes/dtype.h"
#include "c4/parser/nodes/param.h"
#include "c4/parser/parser_ctx.h"
#include "c4/tools/sb.h"
#include "c4/tools/sb_kvp.h"
#include "c4/tools/str_span.h"
#include <stdlib.h>
#include "c4/parser/nodes/struct.h"
#include "lib/stb_ds.h"

c4_ast_node*
c4_ast_node_struct_make(
    c4_str_span span,
    c4_str name,
    c4_ast_node** param_list
) {
    c4_ast_node* self = malloc(sizeof(*self));

    self->node_type = c4_ast_struct;
    self->free_func = c4_ast_node_struct_free;
    self->to_str_func = c4_ast_node_struct_to_str;

    self->span = span;
    self->struct_.param_list = param_list;
    self->struct_.name = name;

    return self;
}

void 
c4_ast_node_struct_free(
    c4_ast_node* self
) {
    for(c4_u32 i = 0; i < arrlen(self->struct_.param_list); i++) {
        c4_ast_node_free(self->struct_.param_list[i]); 
    }
    arrfree(self->struct_.param_list);

    free(self);
}

void 
c4_ast_node_struct_to_str(
    c4_ast_node* self,
    c4_sb* sb
) {
    c4_sb_kvp_start(sb, c4_strv_lit("struct"));
    {
        c4_sb_kvp_append_key(sb, c4_strv_lit("name"));
        c4_sb_kvp_value_start(sb);
        {
            c4_sb_append_str(sb, self->struct_.name);
        }
        c4_sb_kvp_value_end(sb);
        
        c4_sb_line_end(sb);

        c4_sb_kvp_append_key(sb, c4_strv_lit("param_list"));
        c4_sb_line_end(sb);
        
        c4_sb_kvp_value_start(sb);
        {
            for(c4_u32 i = 0; i < arrlen(self->struct_.param_list); i++) {
                c4_ast_node_to_str(self->struct_.param_list[i], sb); 
            }
        }
        c4_sb_kvp_value_end(sb);
        
    }
    c4_sb_kvp_end(sb);
}

c4_ast_node* 
c4_ast_node_struct_parse(
    c4_parser_ctx* ctx
) {
    c4_u32 mark = c4_parser_ctx_mark(ctx);
    c4_ast_node** param_list = NULL;
    
    c4_parser_ctx_pop_expect(ctx, c4_token_struct);

    c4_token name = c4_parser_ctx_pop_expect(ctx, c4_token_ident);
    
    c4_parser_ctx_pop_expect(ctx, c4_token_lbrace);
    
    while(true) {
        c4_ast_node* param = c4_ast_node_param_parse(ctx); 
        arrput(param_list, param);
        
        c4_token comma = c4_parser_ctx_peek(ctx, 0);
        if(comma.type == c4_token_comma) {
            c4_token rbrace = c4_parser_ctx_peek(ctx, 1);
            if(rbrace.type == c4_token_rbrace) {
                break;
            }
        } else {
            break;
        }
        c4_parser_ctx_pop(ctx);
    }
            
    c4_parser_ctx_pop_expect(ctx, c4_token_rbrace);
    
    c4_str_span span = c4_str_span_make_bounds(
        ctx->source,
        mark,
        c4_parser_ctx_mark(ctx)
    );

    return c4_ast_node_struct_make(span, c4_str_span_to_strv(&name.span), param_list);
}
