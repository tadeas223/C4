#include "c4/parser/nodes/expr.h"
#include "c4/parser/ast_node.h"
#include "c4/parser/nodes/addr_of.h"
#include "c4/parser/nodes/deref.h"
#include "c4/parser/nodes/number.h"
#include "c4/parser/nodes/variable.h"
#include "c4/parser/parser_ctx.h"
#include "c4/tools/sb.h"
#include "c4/tools/sb_kvp.h"
#include "c4/tools/str_span.h"
#include <stdlib.h>

c4_precendence_kvp c4_precedence_table[] = {
    {c4_token_plus, 1.0, 1.1},
    {c4_token_minus, 1.0, 1.1},
    {c4_token_star, 2.0, 2.1},
    {c4_token_slash, 2.0, 2.1},
};

c4_u32 c4_precedence_table_len = sizeof(c4_precedence_table) / sizeof(c4_precendence_kvp);

c4_ast_node* 
c4_ast_node_expr_make(
    c4_ast_node* lhs,
    c4_str op,
    c4_ast_node* rhs
) {
    c4_ast_node* node = malloc(sizeof(*node));
    
    node->node_type = c4_ast_expr;
    node->free_func = c4_ast_node_expr_free;
    node->to_str_func = c4_ast_node_expr_to_str;

    node->expr.lhs = lhs;
    node->expr.op = op;
    node->expr.rhs = rhs;

    return node;
}

void 
c4_ast_node_expr_free(
    c4_ast_node* node
) {
    c4_ast_node_free(node->expr.lhs);
    c4_ast_node_free(node->expr.rhs);
    free(node);
}

void 
c4_ast_node_expr_to_str(
    c4_ast_node* self,
    c4_sb* sb
) {
    c4_sb_kvp_start(sb, c4_strv_lit("expr"));

    c4_sb_kvp_append_key(sb, c4_strv_lit("lhs"));
    c4_sb_line_end(sb);
    
    c4_sb_kvp_value_start(sb);
    c4_ast_node_to_str(self->expr.lhs, sb);
    c4_sb_kvp_value_end(sb);

    c4_sb_kvp_append_key(sb, c4_strv_lit("rhs"));
    c4_sb_line_end(sb);
    
    c4_sb_kvp_value_start(sb);
    c4_ast_node_to_str(self->expr.rhs, sb);
    c4_sb_kvp_value_end(sb);
    
    c4_sb_kvp_append_key(sb, c4_strv_lit("op"));
    c4_sb_line_end(sb);
    
    c4_sb_kvp_value_start(sb);
    c4_sb_line_start(sb);
    c4_sb_append_str(sb, self->expr.op);
    c4_sb_line_end(sb);
    c4_sb_kvp_value_end(sb);

    c4_sb_kvp_end(sb);
}

c4_precendence_kvp*
c4_find_operator(
    c4_token* token
) {
    if(token == NULL) {
        return NULL;
    }

    for(c4_u32 i = 0; i < c4_precedence_table_len; i++) {
        if(token->type == c4_precedence_table[i].op) {
            return &c4_precedence_table[i];
        }
    }

    return NULL;
}

c4_ast_node*
c4_ast_node_expr_parse(
    c4_parser_ctx* ctx
) {
    return c4_ast_node_expr_parse2(ctx, 0);   
}

c4_ast_node*
c4_ast_node_expr_parse2(
    c4_parser_ctx* ctx,
    float min_precedence
) {
    c4_u32 mark = c4_parser_ctx_mark(ctx);
    c4_ast_node* lhs;

    c4_token lparen = c4_parser_ctx_peek(ctx, 0);
    if(lparen.type == c4_token_lparen) {
        c4_parser_ctx_pop(ctx);

        lhs = c4_ast_node_expr_parse2(ctx, 0);
        c4_parser_ctx_pop_expect(ctx, c4_token_rparen);
    } else {
        lhs = c4_ast_node_expr_atom_parse(ctx);
    }

    if(lhs == NULL) {
        c4_str_span span = c4_str_span_make_bounds(
            ctx->source,
            mark,
            c4_parser_ctx_mark(ctx)
        );

        c4_str_span_panic(&span, c4_strv_lit("invalid expression"));
    }
    
    while(true) {
        c4_token op = c4_parser_ctx_peek(ctx, 0);
        
        if(op.type == c4_token_eof) {
            break; 
        }

        if(op.type == c4_token_rparen) {
            break;
        }

        c4_precendence_kvp* op_precedence = c4_find_operator(&op);
        if(op_precedence == NULL) {
            // let other parsers handle this
            break;
        }
        
        if(op_precedence->lhs < min_precedence) {
            break; 
        }
        
        c4_parser_ctx_pop(ctx);

        c4_ast_node* rhs = c4_ast_node_expr_parse2(ctx, op_precedence->rhs);
        lhs = c4_ast_node_expr_make(lhs, c4_str_span_to_strv(&op.span), rhs);
    }
    
    return lhs;
}

c4_ast_node*
c4_ast_node_expr_atom_parse(
    c4_parser_ctx* ctx
) {
    c4_token token = c4_parser_ctx_peek(ctx, 0);
    
    switch(token.type) {
        case c4_token_ident: {
                //c4_token lparen = c4_parser_ctx_peek(ctx, 1);
                //if(lparen.type == c4_token_lparen) {
                //    return c4_func_call_parse(ctx); 
                //}
                return c4_ast_node_variable_parse(ctx);
        }
        case c4_token_star: {
                return c4_ast_node_deref_parse(ctx);
        }
        case c4_token_ampersand: {
                return c4_ast_node_addr_of_parse(ctx);
        }
        case c4_token_num:
            return c4_ast_node_number_parse(ctx);
        // case c4_token_type_lbrace:
        //     return c4_struct_init_parse(ctx);
        default:
            c4_parser_ctx_pop(ctx);
            return NULL;
    }
}
