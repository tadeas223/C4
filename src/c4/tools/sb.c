#include "c4/tools/str.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c4/tools/sb.h"


c4_sb* c4_sb_make() {
    c4_sb* self = malloc(sizeof(*self));
    
    self->string = c4_stra_lit("");
    self->prefix = c4_sb_default_prefix;
    self->prefix_count = 0;

    return self;
}

void c4_sb_free(c4_sb* self) {
    c4_stra_free(self->string);
    free(self);
}

c4_str* c4_sb_free_to_stra(c4_sb* self) {
    c4_str* string = self->string;
    free(self);
    return string;
}

void c4_sb_prefix_set(c4_sb* self, c4_str prefix) {
    self->prefix = prefix;
}

void c4_sb_prefix_inc(c4_sb* self) {
    self->prefix_count++;
}

void c4_sb_prefix_dec(c4_sb* self) {
    self->prefix_count--;
}

void c4_sb_line_start(c4_sb* self) {
    for(c4_u32 i = 0; i < self->prefix_count; i++) {
        c4_sb_append_str(self, self->prefix); 
    }
}

void c4_sb_line_end(c4_sb* self) {
    c4_sb_append_str(self, c4_strv_lit("\n")); 
}

void c4_sb_append_chars(c4_sb* self, char* chars, c4_u32 len) {
    c4_stra_append_chars(self->string, chars, len);
}

void c4_sb_append_str(c4_sb* self, c4_str string) {
    c4_stra_append_chars(self->string, string.chars, string.len);
}

void c4_sb_append_cstr(c4_sb* self, char* string) {
    c4_stra_append_chars(self->string, string, strlen(string));
}

void c4_sb_append_u64(c4_sb* self, c4_u64 num) {
    char buffer[128];

    snprintf(buffer, sizeof(buffer), "%lu", num);

    c4_sb_append_cstr(self, buffer);
}

void c4_sb_append_s64(c4_sb* self, c4_s64 num) {
    char buffer[128];

    snprintf(buffer, sizeof(buffer), "%ld", num);

    c4_sb_append_cstr(self, buffer);
}

c4_str c4_sb_to_strv(c4_sb* self) {
    return c4_strv_make_str(*self->string);
}

c4_str* c4_sb_to_stra(c4_sb* self) {
    return c4_stra_make_str(*self->string);
}
