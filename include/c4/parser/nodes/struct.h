#ifndef __c4_parser_nodes_struct_h__
#define __c4_parser_nodes_struct_h__

#include "c4/parser/parser_ctx.h"
#include "c4/parser/ast_node.h"

c4_ast_node*
c4_ast_node_struct_make(
    c4_str_span span,
    c4_str name,
    c4_ast_node** param_list
);

void 
c4_ast_node_struct_free(
    c4_ast_node* self
);

void 
c4_ast_node_struct_to_str(
    c4_ast_node* self,
    c4_sb* sb
);

c4_ast_node*
c4_ast_node_struct_parse(
    c4_parser_ctx* ctx
);


#endif /* __c4_parser_nodes_struct_h__ */
