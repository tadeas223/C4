#ifndef __c4_parser_parser_h__
#define __c4_parser_parser_h__

#include "c4/lexer/token.h"
#include "c4/parser/ast_node.h"

c4_ast_node* 
c4_parser_parse(
    c4_str source,
    c4_token* token_list
);

#endif /* __c4_parser_parser_h__ */
