#include "c4/parser/nodes/return.h"
#include "c4/parser/ast_node.h"
#include "c4/parser/nodes/expr.h"
#include "c4/parser/parser_ctx.h"
#include "c4/tools/sb.h"
#include "c4/tools/sb_kvp.h"
#include "c4/tools/str.h"
#include "c4/tools/str_span.h"
#include <stdlib.h>

c4_ast_node*
c4_ast_node_return_make(
    c4_str_span span, 
    c4_ast_node* expr
) {
    c4_ast_node* self = malloc(sizeof(*self));
    
    self->node_type = c4_ast_return;
    self->free_func = c4_ast_node_return_free;
    self->to_str_func = c4_ast_node_return_to_str;
    self->span = span;

    self->return_.expr = expr;

    return self;
}

void 
c4_ast_node_return_free(
    c4_ast_node* self
) {
    c4_ast_node_free(self->return_.expr);
    free(self);
}

void 
c4_ast_node_return_to_str(
    c4_ast_node* self, 
    c4_sb* sb
) {
    c4_sb_kvp_start(sb, c4_strv_lit("return"));
    
    c4_sb_kvp_append_key(sb, c4_strv_lit("expr"));
    c4_sb_line_end(sb);

    c4_sb_kvp_value_start(sb);
    c4_ast_node_to_str(self->return_.expr, sb);
    c4_sb_kvp_value_end(sb);

    c4_sb_kvp_end(sb);
}

c4_ast_node* 
c4_ast_node_return_parse(
    c4_parser_ctx* ctx
) {
    c4_u32 mark = c4_parser_ctx_mark(ctx);

    c4_parser_ctx_pop_expect(ctx, c4_token_return);

    c4_ast_node* expr = c4_ast_node_expr_parse(ctx);
    
    c4_str_span span = c4_str_span_make_bounds(
        ctx->source,
        mark,
        c4_parser_ctx_mark(ctx)
    );

    return c4_ast_node_return_make(span, expr);
}
