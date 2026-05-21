#ifndef __c4_parser_nodes_deref_h__
#define __c4_parser_nodes_deref_h__

#include "c4/parser/parser_ctx.h"
#include "c4/parser/ast_node.h"

c4_ast_node*
c4_ast_node_deref_make(
    c4_str_span span, 
    c4_ast_node* expr
);

void 
c4_ast_node_deref_free(
    c4_ast_node* self
);

void 
c4_ast_node_deref_to_str(
    c4_ast_node* self, 
    c4_sb* sb
);

c4_ast_node* 
c4_ast_node_deref_parse(
    c4_parser_ctx* ctx
);


#endif /* __c4_parser_nodes_deref_h__ */
