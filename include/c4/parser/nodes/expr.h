#ifndef c4_parser_expr_h
#define c4_parser_expr_h

#include "c4/parser/ast_node.h"
#include "c4/parser/parser_ctx.h"

typedef struct {
    c4_token_type op;
    float lhs;
    float rhs;
} c4_precendence_kvp;


extern c4_precendence_kvp c4_precedence_table[];
extern c4_u32 c4_precedence_table_len;

c4_ast_node* 
c4_ast_node_expr_make(
    c4_ast_node* lhs,
    c4_str op,
    c4_ast_node* rhs
);

void 
c4_ast_node_expr_free(
    c4_ast_node* self
);

void 
c4_ast_node_expr_to_str(
    c4_ast_node* self,
    c4_sb* sb
);

c4_ast_node*
c4_ast_node_expr_parse(
    c4_parser_ctx* ctx
);

c4_precendence_kvp*
c4_find_operator(
    c4_token* token
);

c4_ast_node*
c4_ast_node_expr_parse2(
    c4_parser_ctx* ctx,
    float min_precedence
);

c4_ast_node*
c4_ast_node_expr_atom_parse(
    c4_parser_ctx* ctx
);

#endif /* c4_parser_expr_h */
