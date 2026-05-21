#include "c4/lexer/lexer_table.h"

typedef struct {
    char c;
    c4_token_type type;
} single_kvp;

typedef struct {
    c4_str keyword;
    c4_token_type type;
} keyword_kvp;

static char skip_char_list[] = {
#define X(ch) ch,
c4_skip_char_token_list
#undef X
};

static single_kvp single_kvp_list[] = {
#define X(t, ch) {.type = t, .c = ch},
c4_single_char_token_list
#undef X
};

static keyword_kvp keyword_kvp_list[] = {
#define X(t, k) {.type = t, .keyword = c4_strv_lit(k)},
c4_keyword_token_list
#undef X
};

static c4_str tok_name_list[] = {
#define X(type, k) c4_strv_lit(#type),
c4_single_char_token_list
#undef X

#define X(type, k) c4_strv_lit(#type),
c4_keyword_token_list
#undef X

#define X(type) c4_strv_lit(#type),
c4_special_token_list
#undef X
};

bool
c4_token_is_skip_char(
    char c
) {
    for(c4_u32 i = 0; i < sizeof(skip_char_list) / sizeof(char); i++) {
        if(c == skip_char_list[i]) {
            return true; 
        }
    }

    return false;
}

c4_token_type_opt 
c4_token_is_single_char(
    char c
) {
    for(
        c4_u32 i = 0;
        i < sizeof(single_kvp_list) / sizeof(single_kvp);
        i++
    ) {
        if(single_kvp_list[i].c == c) {
            return (c4_token_type_opt) {
                .type = single_kvp_list[i].type,
                .has_some = true
            };
        }
    }
            
    return (c4_token_type_opt) {
        .has_some = false
    };
}

c4_token_type_opt 
c4_token_is_keyword(
    c4_str keyword
) {
    for(
        c4_u32 i = 0;
        i < sizeof(keyword_kvp_list) / sizeof(keyword_kvp);
        i++
    ) {
        if(c4_str_equal(keyword_kvp_list[i].keyword, keyword)) {
            return (c4_token_type_opt) {
                .type = keyword_kvp_list[i].type,
                .has_some = true
            };
        }
    }
            
    return (c4_token_type_opt) {
        .has_some = false
    };
}

c4_str 
c4_token_type_to_strv(
    c4_token_type type
) {
    return tok_name_list[type];
}
