#include "c4/parser/ast_node.h"
#include "c4/parser/nodes/dtype.h"
#include "c4/parser/parser_ctx.h"
#include "c4/tools/sb.h"
#include "c4/tools/sb_kvp.h"
#include "c4/tools/str_span.h"
#include <stdlib.h>
#include "c4/parser/nodes/param.h"

c4_ast_node*
c4_ast_node_param_make(
    c4_str_span span,
    c4_str name,
    c4_ast_node* type
) {
    c4_ast_node* self = malloc(sizeof(*self));
    
    self->node_type = c4_ast_param;
    self->free_func = c4_ast_node_param_free;
    self->to_str_func = c4_ast_node_param_to_str;

    self->span = span;
    
    self->param.type = type;
    self->param.name = name;

    return self;
}

void
c4_ast_node_param_free(
    c4_ast_node* self
) {
    c4_ast_node_free(self->param.type);
    free(self);
}

void 
c4_ast_node_param_to_str(
    c4_ast_node* self,
    c4_sb* sb
) {
    c4_sb_kvp_start(sb, c4_strv_lit("param"));
    {
        c4_sb_kvp_append_key(sb, c4_strv_lit("name"));
        
        c4_sb_kvp_value_start(sb);
        {
            c4_sb_append_str(sb, self->param.name);
        }
        c4_sb_kvp_value_end(sb);
        
        c4_sb_line_end(sb);
        
        c4_sb_kvp_append_key(sb, c4_strv_lit("type"));
        c4_sb_line_end(sb);
        
        c4_sb_kvp_value_start(sb);
        {
            c4_ast_node_to_str(self->param.type, sb);
        }
        c4_sb_kvp_value_end(sb);
    }
    c4_sb_kvp_end(sb);
}

c4_ast_node* 
c4_ast_node_param_parse(
    c4_parser_ctx* ctx
) {
    c4_u32 mark = c4_parser_ctx_mark(ctx);
    
    c4_token name = c4_parser_ctx_pop_expect(ctx, c4_token_ident);

    c4_parser_ctx_pop_expect(ctx, c4_token_colon);

    c4_ast_node* type = c4_ast_node_dtype_parse(ctx);
    
    c4_str_span span = c4_str_span_make_bounds(
        ctx->source,
        mark,
        c4_parser_ctx_mark(ctx)
    );

    return c4_ast_node_param_make(span, c4_str_span_to_strv(&name.span), type);
}
