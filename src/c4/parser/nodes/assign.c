#include "c4/parser/ast_node.h"
#include "c4/parser/nodes/expr.h"
#include "c4/parser/nodes/param.h"
#include "c4/parser/nodes/variable.h"
#include "c4/parser/parser_ctx.h"
#include "c4/tools/sb.h"
#include "c4/tools/sb_kvp.h"
#include "c4/tools/str.h"
#include "c4/tools/str_span.h"
#include <stdlib.h>
#include "c4/parser/nodes/assign.h"

c4_ast_node*
c4_ast_node_assign_make(
    c4_str_span span, 
    c4_ast_node* lhs,
    c4_ast_node* rhs 
) {
    c4_ast_node* self = malloc(sizeof(*self));

    self->node_type = c4_ast_type;
    self->span = span;
    self->free_func = c4_ast_node_assign_free;
    self->to_str_func = c4_ast_node_assign_to_str;

    self->assign.lhs = lhs;
    self->assign.rhs = rhs;

    return self;
}

void 
c4_ast_node_assign_free(
    c4_ast_node* self
) {
    c4_ast_node_free(self->assign.lhs);
    c4_ast_node_free(self->assign.rhs);

    free(self);
}

void 
c4_ast_node_assign_to_str(
    c4_ast_node* self,
    c4_sb* sb
) {
    c4_sb_kvp_start(sb, c4_strv_lit("assign"));
    {
        c4_sb_kvp_append_key(sb, c4_strv_lit("lhs"));
        c4_sb_line_end(sb);
        
        c4_sb_kvp_value_start(sb);
        {
            c4_ast_node_to_str(self->assign.lhs, sb);
        }
        c4_sb_kvp_value_end(sb);
        
        c4_sb_kvp_append_key(sb, c4_strv_lit("rhs"));
        c4_sb_line_end(sb);
        
        c4_sb_kvp_value_start(sb);
        {
            c4_ast_node_to_str(self->assign.rhs, sb);
        }
        c4_sb_kvp_value_end(sb);
    }
    c4_sb_kvp_end(sb);
}

c4_ast_node*
c4_ast_node_assign_parse(
    c4_parser_ctx* ctx
) {
    c4_u32 mark = c4_parser_ctx_mark(ctx);
    c4_ast_node* lhs = c4_ast_node_expr_parse(ctx);
    
    c4_parser_ctx_pop_expect(ctx, c4_token_eq);

    c4_ast_node* rhs = c4_ast_node_expr_parse(ctx);

    c4_str_span span = c4_str_span_make_bounds(
        ctx->source,
        mark,
        c4_parser_ctx_mark(ctx)
    );

    return c4_ast_node_assign_make(span, lhs, rhs);
}
