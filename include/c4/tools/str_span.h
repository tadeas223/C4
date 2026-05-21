#ifndef __c4_tools_str_span_h__
#define __c4_tools_str_span_h__

#include "c4/tools/str.h"
#include "c4/tools/types.h"

typedef struct {
    c4_str string;
    c4_u32 start;
    c4_u32 len;
} c4_str_span;

c4_str_span
c4_str_span_make(
    c4_str string,
    c4_u32 start,
    c4_u32 len
);

c4_str_span 
c4_str_span_make_bounds(
    c4_str string,
    c4_u32 start, 
    c4_u32 end
);

c4_str 
c4_str_span_to_strv(
    c4_str_span* self
);

void 
c4_str_span_panic(
    c4_str_span* self, 
    c4_str msg
);

#endif /* __c4_tools_str_span_h__ */
