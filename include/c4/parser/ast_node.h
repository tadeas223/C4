#ifndef __c4_parser_ast_node_h__
#define __c4_parser_ast_node_h__

#include "c4/tools/sb.h"
#include "c4/tools/str.h"
#include "c4/tools/str_span.h"

#define c4_ast_node_type_list \
    X(c4_ast_unit) \
    X(c4_ast_fn) \
    X(c4_ast_struct) \
    X(c4_ast_return) \
    X(c4_ast_param) \
    X(c4_ast_expr) \
    X(c4_ast_type) \
    X(c4_ast_declare) \
    X(c4_ast_assign) \
    X(c4_ast_deref) \
    X(c4_ast_addr_of) \

typedef enum {
#define X(t) t,
    c4_ast_node_type_list
#undef X
} c4_ast_node_type;

typedef struct c4_ast_node c4_ast_node;
typedef void c4_ast_node_free_f(c4_ast_node* self);
typedef void c4_ast_node_to_str_f(c4_ast_node* self, c4_sb* sb);

struct c4_ast_node {
    c4_ast_node_type node_type;
    c4_str_span span;
    c4_ast_node_free_f* free_func;
    c4_ast_node_to_str_f* to_str_func;

    union {
        struct {
            c4_ast_node** node_list;
        } unit;
        
        struct {
            c4_str name;
        } dtype;
        
        struct {
            c4_str name;
        } variable;
        
        struct {
            c4_str content;
        } number;
        
        struct {
            c4_str name;
            c4_ast_node* type;
        } param;
        
        struct {
            c4_str name;
            c4_ast_node** param_list;
        } struct_;
        
        struct {
            c4_ast_node* expr;
        } return_;
        
        struct {
            c4_ast_node* expr;
        } deref;
        
        struct {
            c4_ast_node* expr;
        } addr_of;
        
        struct {
            c4_ast_node* param;
            c4_ast_node* expr;
        } declare;
        
        struct {
            c4_ast_node* lhs;
            c4_ast_node* rhs;
        } assign;
        
        struct {
            c4_str op;
            c4_ast_node* lhs;
            c4_ast_node* rhs;
        } expr;
        
        struct {
            c4_str name;
            c4_ast_node* returns;
            c4_ast_node** param_list;
            c4_ast_node** scope_list;
        } fn;
    };
};

void 
c4_ast_node_free(
    c4_ast_node* self
);

void 
c4_ast_node_to_str(
    c4_ast_node* self, 
    c4_sb* sb
);

#endif /* __c4_parser_ast_node_h__ */
