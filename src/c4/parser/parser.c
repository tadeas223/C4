#include "c4/parser/nodes/unit.h"
#include "c4/parser/parser.h"

c4_ast_node*
c4_parser_parse(
    c4_str source,
    c4_token* token_list
) {
    c4_parser_ctx ctx = c4_parser_ctx_make(source, token_list);
    return c4_ast_node_unit_parse(&ctx);
}
