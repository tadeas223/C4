#ifndef __c4_tools_sb_h__
#define __c4_tools_sb_h__

#include "c4/tools/str.h"
#include "c4/tools/types.h"

#define c4_sb_default_prefix c4_strv_lit("|  ")

typedef struct {
    c4_str* string;
    c4_str prefix;
    c4_u32 prefix_count;

} c4_sb;

c4_sb* c4_sb_make();

void 
c4_sb_free(
    c4_sb* self
);

c4_str* 
c4_sb_free_to_stra(
    c4_sb* self
);

void 
c4_sb_prefix_set(
    c4_sb* self, 
    c4_str prefix
);

void 
c4_sb_prefix_inc(
    c4_sb* self
);

void 
c4_sb_prefix_dec(
    c4_sb* self
);

void 
c4_sb_line_start(
    c4_sb* self
);

void 
c4_sb_line_end(
    c4_sb* self
);

void 
c4_sb_append_chars(
    c4_sb* self,
    char* chars,
    c4_u32 len
);

void 
c4_sb_append_str(
    c4_sb* self,
    c4_str string
);

void 
c4_sb_append_cstr(
    c4_sb* self,
    char* string
);

void 
c4_sb_append_u64(
    c4_sb* self, 
    c4_u64 num
);

void 
c4_sb_append_s64(
    c4_sb* self,
    c4_s64 num
);

c4_str
c4_sb_to_strv(
    c4_sb* self
);

c4_str* 
c4_sb_to_stra(
    c4_sb* self
);

#endif /* __c4_tools_sb_h__ */
