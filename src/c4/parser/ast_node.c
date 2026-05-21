#include "c4/parser/ast_node.h"
#include "c4/tools/sb.h"
#include <string.h>

void 
c4_ast_node_free(
    c4_ast_node* self
) {
    if(self == NULL) return;
    self->free_func(self);
}

void 
c4_ast_node_to_str(
    c4_ast_node* self,
    c4_sb* sb
) {
    if(self == NULL) {
        c4_sb_line_start(sb);
        c4_sb_append_str(sb, c4_strv_lit("<null>"));
        c4_sb_line_end(sb);
        return;
    }

    self->to_str_func(self, sb);
}
