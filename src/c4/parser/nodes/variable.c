#include "c4/parser/parser_ctx.h"
#include "c4/tools/sb.h"
#include "c4/tools/sb_kvp.h"
#include "c4/tools/str.h"
#include "c4/tools/str_span.h"
#include <stdlib.h>
#include "c4/parser/nodes/variable.h"

c4_ast_node*
c4_ast_node_variable_make(
    c4_str_span span, 
    c4_str name
) {
    c4_ast_node* self = malloc(sizeof(*self));

    self->node_type = c4_ast_type;
    self->span = span;
    self->free_func = c4_ast_node_variable_free;
    self->to_str_func = c4_ast_node_variable_to_str;

    self->variable.name = name;

    return self;
}

void 
c4_ast_node_variable_free(
    c4_ast_node* self
) {
    free(self);
}

void 
c4_ast_node_variable_to_str(
    c4_ast_node* self,
    c4_sb* sb
) {
    c4_sb_kvp_start(sb, c4_strv_lit("variable"));
    {
        c4_sb_kvp_append_key(sb, c4_strv_lit("name"));
        
        c4_sb_kvp_value_start(sb);
        {
            c4_sb_append_str(sb, self->variable.name);
        }
        c4_sb_kvp_value_end(sb);
        c4_sb_line_end(sb);
    }
    c4_sb_kvp_end(sb);
}

c4_ast_node*
c4_ast_node_variable_parse(
    c4_parser_ctx* ctx
) {
    c4_token ident = c4_parser_ctx_pop_expect(ctx, c4_token_ident);
    
    return c4_ast_node_variable_make(
        ident.span,
        c4_str_span_to_strv(&ident.span)
    );
}
