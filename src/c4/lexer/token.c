#include "c4/tools/sb.h"
#include "c4/tools/sb_kvp.h"

#include "c4/lexer/token.h"

c4_token c4_token_make(
    c4_token_type type,
    c4_str source,
    c4_u32 start,
    c4_u32 end
) {
    return (c4_token) {
        .type = type,
        .span = c4_str_span_make(source, start, end - start)
    };
}

void 
c4_token_to_str(
    c4_token* self,
    c4_sb* sb
) {
    c4_sb_kvp_start(sb, c4_strv_lit("token"));

    c4_sb_kvp_append_key(sb, c4_strv_lit("type"));

    c4_sb_kvp_value_start(sb);
    c4_sb_append_str(sb, c4_token_type_to_strv(self->type));
    c4_sb_kvp_value_end(sb);
    
    c4_sb_line_end(sb);
    
    c4_sb_kvp_append_key(sb, c4_strv_lit("content"));
    
    c4_sb_kvp_value_start(sb);
    
    c4_sb_append_str(sb, c4_str_span_to_strv(&self->span));
    c4_sb_kvp_value_end(sb);
    
    c4_sb_line_end(sb);
    
    c4_sb_kvp_end(sb);
}
