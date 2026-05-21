#ifndef __c4_tools_sb_kvp_h__
#define __c4_tools_sb_kvp_h__

#include "c4/tools/sb.h"

#define c4_sb_kvp_key_prefix c4_strv_lit("- ")
#define c4_sb_kvp_name_prefix c4_strv_lit("> ")

#define c4_sb_kvp_key_postfix c4_strv_lit(": ")
#define c4_sb_kvp_name_postfix c4_strv_lit(": ")

void 
c4_sb_kvp_start(
    c4_sb* sb,
    c4_str name
);

void 
c4_sb_kvp_append_key(
    c4_sb* sb,
    c4_str key
);

void 
c4_sb_kvp_value_start(
    c4_sb* sb
);

void 
c4_sb_kvp_value_end(
    c4_sb* sb
);

void 
c4_sb_kvp_end(
    c4_sb* sb
);

#endif /* __c4_tools_sb_kvp_h__ */
