#include "c4/tools/sb.h"
#include "c4/tools/sb_kvp.h"

void c4_sb_kvp_start(c4_sb* sb, c4_str name) {
    c4_sb_line_start(sb);
    c4_sb_append_str(sb, c4_sb_kvp_name_prefix);
    c4_sb_append_str(sb, name);
    c4_sb_append_str(sb, c4_sb_kvp_name_postfix);
    c4_sb_line_end(sb);
    
    c4_sb_prefix_inc(sb);
}

void c4_sb_kvp_append_key(c4_sb* sb, c4_str key) {
    c4_sb_line_start(sb);
    c4_sb_append_str(sb, c4_sb_kvp_key_prefix);
    c4_sb_append_str(sb, key);
    c4_sb_append_str(sb, c4_sb_kvp_key_postfix);
}

void c4_sb_kvp_value_start(c4_sb* sb) {
    c4_sb_prefix_inc(sb);
}

void c4_sb_kvp_value_end(c4_sb* sb) {
    c4_sb_prefix_dec(sb);
}

void c4_sb_kvp_end(c4_sb* sb) {
    c4_sb_prefix_dec(sb);
}
