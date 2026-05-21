#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c4/tools/str.h"


c4_str c4_strv_make(char* chars, c4_u32 len) {
    return (c4_str){
        .chars = chars,
        .len = len
    };
}

c4_str c4_strv_make_str(c4_str string) {
    return c4_strv_make(string.chars, string.len);
}

c4_str c4_strv_make_bounds(char* chars, c4_u32 start, c4_u32 end) {
    return (c4_str) {
        .chars = chars + (start * sizeof(char)),
        .len = end - start
    };
}

c4_str* c4_stra_make(char* chars, c4_u32 len) {
    c4_str* self = malloc(sizeof(*self));
    
    self->chars = malloc(len);
    self->len = len;

    memcpy(self->chars, chars, len);

    return self;
}

c4_str* c4_stra_make_str(c4_str string) {
    return c4_stra_make(string.chars, string.len);
}

void c4_stra_free(c4_str* self) {
    free(self->chars);
    free(self);
}

void c4_stra_append_chars(c4_str* self, char* chars, c4_u32 len) {
    char* new_chars = realloc(self->chars, self->len + len);

    memcpy(new_chars + self->len, chars, len);

    self->chars = new_chars;
    self->len += len;
}

void c4_str_print(c4_str self) {
    fwrite(self.chars, self.len, 1, stdout);
}

bool c4_str_equal(c4_str a, c4_str b) {
    if(a.len != b.len) {
        return false; 
    }

    for(c4_u32 i = 0; i < a.len; i++) {
        if(a.chars[i] != b.chars[i]) {
            return false; 
        }
    }

    return true;
}
