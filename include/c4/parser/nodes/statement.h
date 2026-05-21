#ifndef __c4_parser_nodes_statement_h__
#define __c4_parser_nodes_statement_h__

#include "c4/parser/parser_ctx.h"
#include "c4/parser/ast_node.h"

c4_ast_node* 
c4_ast_node_ident_statement_parse(
    c4_parser_ctx* ctx
);

c4_ast_node* 
c4_ast_node_statement_parse(
    c4_parser_ctx* ctx
);

#endif /* __c4_parser_nodes_statement_h__ */
