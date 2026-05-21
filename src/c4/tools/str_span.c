#include "c4/tools/str.h"
#include <stdio.h>
#include <stdlib.h>

#include "c4/tools/str_span.h"

c4_str_span c4_str_span_make(c4_str string, c4_u32 start, c4_u32 len) {
    return (c4_str_span) {
        .start = start,
        .len = len,
        .string = string
    };
}

c4_str_span c4_str_span_make_bounds(c4_str string, c4_u32 start, c4_u32 end) {
    return (c4_str_span) {
        .start = start,
        .len = end - start,
        .string = string
    };
}

c4_str c4_str_span_to_strv(c4_str_span* self) {
    return c4_strv_make(
        self->string.chars + self->start,
        self->len
    );
}

void c4_str_span_panic(c4_str_span* self, c4_str msg) {
    c4_u32 start = self->start;
    c4_u32 end = self->len - self->start;

    const char* src = self->string.chars;
    c4_u32 len = self->string.len;

    if (start > len) start = len;
    if (end > len) end = len;
    if (end < start) end = start;

    // 1. Find line start
    c4_u32 line_start = start;
    while (line_start > 0 && src[line_start - 1] != '\n') {
        line_start--;
    }

    // 2. Find line end
    c4_u32 line_end = start;
    while (line_end < len && src[line_end] != '\n') {
        line_end++;
    }

    // 3. Compute line number
    c4_u32 line_number = 1;
    for (c4_u32 i = 0; i < line_start; i++) {
        if (src[i] == '\n') line_number++;
    }

    // 4. Compute column positions
    c4_u32 col_start = start - line_start;
    c4_u32 col_end   = end   - line_start;

    // 5. Print header
    fprintf(stderr, "Error at line %u: %.*s\n",
        line_number,
        msg.len,
        msg.chars
    );

    // 6. Print the line itself
    fprintf(stderr, "%.*s\n",
        (int)(line_end - line_start),
        src + line_start
    );

    // 7. Print underline
    for (c4_u32 i = 0; i < col_start; i++) {
        fputc(src[line_start + i] == '\t' ? '\t' : ' ', stderr);
    }

    // At least one caret
    c4_u32 underline_len = (col_end > col_start) ? (col_end - col_start) : 1;

    for (c4_u32 i = 0; i < underline_len; i++) {
        fputc('^', stderr);
    }

    fputc('\n', stderr);

    exit(1);
}
