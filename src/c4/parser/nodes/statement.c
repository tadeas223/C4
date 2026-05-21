#include "c4/parser/nodes/statement.h"
#include "c4/parser/nodes/assign.h"
#include "c4/parser/nodes/declare.h"
#include "c4/parser/nodes/return.h"
#include "c4/parser/parser_ctx.h"
#include "c4/tools/str.h"
#include "c4/tools/str_span.h"
#include <stdlib.h>
#include <string.h>

c4_ast_node* 
c4_ast_node_statement_parse(
    c4_parser_ctx* ctx
) {
    c4_token token = c4_parser_ctx_peek(ctx, 0);

    switch(token.type) {
        case c4_token_return: {
            return c4_ast_node_return_parse(ctx);
            break;
        }
        
        case c4_token_let: {
            return c4_ast_node_declare_parse(ctx);
            break;
        }
        
        case c4_token_star:
        case c4_token_ampersand:
        case c4_token_ident: {
            return c4_ast_node_assign_parse(ctx);
            break;
        }
        
        default: {
            c4_str_span_panic(&token.span, c4_strv_lit("unexpected token"));
            exit(1);
            break;
        }
    }

}
