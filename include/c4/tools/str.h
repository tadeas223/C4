#ifndef __c4_tools_str_h__
#define __c4_tools_str_h__

#include "c4/tools/macros.h"
#include "c4/tools/types.h"

#define c4_strv_lit(literal) \
    (c4_str){ \
        .chars = literal, \
        .len = (sizeof(literal) - 1) * sizeof(char) \
    }

#define c4_strv_multiline(...) c4_strv_lit(c4_stringify(__VA_ARGS__))

#define c4_stra_lit(literal) \
    c4_stra_make( \
        literal, \
        (sizeof(literal) - 1) * sizeof(char) \
    )

typedef struct {
    char* chars;
    c4_u32 len;
} c4_str;

c4_str
c4_strv_make(
    char* chars,
    c4_u32 len
);

c4_str 
c4_strv_make_bounds(
    char* chars,
    c4_u32 start,
    c4_u32 end
);

c4_str 
c4_strv_make_str(
    c4_str string
);

c4_str*
c4_stra_make(
    char* chars,
    c4_u32 len
);

c4_str* 
c4_stra_make_str(
    c4_str string
);

void 
c4_stra_free(
    c4_str* self
);

void 
c4_stra_append_chars(
    c4_str* self,
    char* chars,
    c4_u32 len
);

void 
c4_str_print(
    c4_str self
);

bool 
c4_str_equal(
    c4_str a, 
    c4_str b
);

#endif /* __c4_tools_str_h__ */
