#include "c4/parser/nodes/fn.h"
#include <stdlib.h>
#include "c4/parser/ast_node.h"
#include "c4/parser/nodes/dtype.h"
#include "c4/parser/nodes/param.h"
#include "c4/parser/nodes/statement.h"
#include "c4/parser/parser_ctx.h"
#include "c4/tools/sb.h"
#include "c4/tools/sb_kvp.h"
#include "c4/tools/str_span.h"
#include "lib/stb_ds.h"

c4_ast_node*
c4_ast_node_fn_make(
    c4_str_span span, 
    c4_str name,
    c4_ast_node* returns,
    c4_ast_node** param_list,
    c4_ast_node** scope_list
) {
    c4_ast_node* self = malloc(sizeof(*self));
    
    self->node_type = c4_ast_fn;
    self->free_func = c4_ast_node_fn_free;
    self->to_str_func = c4_ast_node_fn_to_str;
    
    self->fn.name = name;
    self->fn.returns = returns;
    self->fn.param_list = param_list;
    self->fn.scope_list = scope_list;

    return self;
}

void 
c4_ast_node_fn_free(
    c4_ast_node* self
) {
    c4_ast_node** scope_list = self->fn.scope_list;
    for(c4_u32 i = 0; i < arrlen(scope_list); i++) {
        c4_ast_node_free(scope_list[i]); 
    }
    arrfree(scope_list);
    
    c4_ast_node** param_list = self->fn.param_list;
    for(c4_u32 i = 0; i < arrlen(param_list); i++) {
        c4_ast_node_free(param_list[i]); 
    }
    arrfree(param_list);
   
    c4_ast_node_free(self->fn.returns);

    free(self);
}

void 
c4_ast_node_fn_to_str(
    c4_ast_node* self, 
    c4_sb* sb
) {
    c4_sb_kvp_start(sb, c4_strv_lit("fn"));

    c4_sb_kvp_append_key(sb, c4_strv_lit("name"));
    
    c4_sb_kvp_value_start(sb);
    c4_sb_append_str(sb, self->fn.name);
    c4_sb_kvp_value_end(sb);
    
    c4_sb_line_end(sb);
    
    c4_sb_kvp_append_key(sb, c4_strv_lit("returns"));
    c4_sb_line_end(sb);
    
    c4_sb_kvp_value_start(sb);
    c4_ast_node_to_str(self->fn.returns, sb);
    c4_sb_kvp_value_end(sb);
    
    
    c4_sb_kvp_append_key(sb, c4_strv_lit("param_list"));
    c4_sb_line_end(sb);
    
    c4_sb_kvp_value_start(sb);
    c4_ast_node** param_list = self->fn.param_list;
    for(c4_u32 i = 0; i < arrlen(param_list); i++) {
        c4_ast_node_to_str(param_list[i], sb); 
    }
    c4_sb_kvp_value_end(sb);
    
    c4_sb_kvp_append_key(sb, c4_strv_lit("scope_list"));
    c4_sb_line_end(sb);
    
    c4_sb_kvp_value_start(sb);
    c4_ast_node** scope_list = self->fn.scope_list;
    for(c4_u32 i = 0; i < arrlen(scope_list); i++) {
        c4_ast_node_to_str(scope_list[i], sb); 
    }
    c4_sb_kvp_value_end(sb);

    c4_sb_kvp_end(sb);
}

c4_ast_node* 
c4_ast_node_fn_parse(
    c4_parser_ctx* ctx
) {
    c4_u32 mark = c4_parser_ctx_mark(ctx);

    c4_ast_node** scope_list = NULL;
    c4_ast_node** param_list = NULL;
    c4_ast_node* returns = NULL;

    c4_parser_ctx_pop_expect(ctx, c4_token_fn);
    
    c4_token name = c4_parser_ctx_pop_expect(ctx, c4_token_ident);
    
    c4_parser_ctx_pop_expect(ctx, c4_token_lparen);
    
    while(true) {
        c4_ast_node* param = c4_ast_node_param_parse(ctx); 
        arrput(param_list, param);
        
        c4_token comma = c4_parser_ctx_peek(ctx, 0);
        if(comma.type != c4_token_comma) {
            break;
        }
        c4_parser_ctx_pop(ctx);
    }

    c4_parser_ctx_pop_expect(ctx, c4_token_rparen);
    
    c4_token token = c4_parser_ctx_peek(ctx, 0);
    if(token.type == c4_token_minus) {
        c4_parser_ctx_pop_expect(ctx, c4_token_minus);
        c4_parser_ctx_pop_expect(ctx, c4_token_gt);

        returns = c4_ast_node_dtype_parse(ctx);
    } 
    
    c4_parser_ctx_pop_expect(ctx, c4_token_lbrace);
    
    if(c4_parser_ctx_peek(ctx, 0).type != c4_token_rbrace) {
        while(true) {
            c4_ast_node* stmt = c4_ast_node_statement_parse(ctx); 
            arrput(scope_list, stmt);
            
            c4_token semi = c4_parser_ctx_pop(ctx);
            if(semi.type == c4_token_semicolon) {
                c4_token rbrace = c4_parser_ctx_peek(ctx, 0);
                if(rbrace.type == c4_token_rbrace) {
                    break;
                }
            }
        }
    }

    c4_parser_ctx_pop_expect(ctx, c4_token_rbrace);
    
    c4_str_span span = c4_str_span_make(ctx->source, mark, c4_parser_ctx_mark(ctx));

    return c4_ast_node_fn_make(
        span,
        c4_str_span_to_strv(&name.span),
        returns,
        param_list,
        scope_list
    );
}
