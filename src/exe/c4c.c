#include "c4/lexer/lexer_table.h"

#include "c4/lexer/lexer.h"
#include "c4/lexer/token.h"
#include "c4/parser/ast_node.h"
#include "c4/parser/nodes/unit.h"
#include "c4/parser/parser.h"
#include "lib/stb_ds.h"


#include <stdio.h>
#include <stdlib.h>

#include "c4/tools/sb_kvp.h"
#include "c4/tools/str.h"
#include "c4/tools/sb.h"


int main(int argc, char *argv[])
{
    c4_str source = c4_strv_multiline(
        struct test {
            x: u32,
            y: u32
        }

        fn test(x: u32) -> u32 {
            let x: u32 = *1;

            *x = 10;
        }
    );

    c4_token* tokens = c4_lexer_tokenize(source);
        
    c4_str_print(c4_strv_lit("tokens:\n"));
    for(c4_u32 i = 0; i < arrlen(tokens); i++) {
        c4_sb* sb = c4_sb_make();

        c4_token_to_str(&tokens[i], sb);

        c4_str_print(c4_sb_to_strv(sb));

        c4_sb_free(sb);
    }
    
    c4_str_print(c4_strv_lit("\n\nast:\n"));
    
    c4_ast_node* unit = c4_parser_parse(source, tokens);
    
    c4_sb* sb = c4_sb_make();
    c4_ast_node_unit_to_str(unit, sb);
    c4_str_print(c4_sb_to_strv(sb));
    
    c4_sb_free(sb);
    c4_ast_node_unit_free(unit);
    arrfree(tokens);

    return 0;
}
