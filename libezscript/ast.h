/*
ezscript 
Copyright 2018 Sean Farrell <sean.farrell@rioki.org>

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
*/

#ifndef _AST_H_
#define _AST_H_

enum ast_type 
{
    AST_ADDITION,
    AST_ARRAY,
    AST_ASSIGNMENT,
    AST_DIVISION,
    AST_EQUALS,
    AST_GRATER_EQUAL,
    AST_GRATER,
    AST_LESS_EQUAL,
    AST_LESS,
    AST_LITERAL_BOOLEAN,
    AST_LITERAL_INTEGER,
    AST_LITERAL_NULL,
    AST_LITERAL_REAL,
    AST_LITERAL_STRING,
    AST_MEMBER,
    AST_MODULO,
    AST_MULTIPLICATION,
    AST_NOT_EQUALS,
    AST_NULL,
    AST_OBJECT,
    AST_REFERENCE,
    AST_SUBTRACTION,
    AST_VARDECL,
};
typedef enum ast_type ast_type_t;

struct ast_node 
{
    ast_type_t type;

    struct ast_node* parent;
    struct ast_node* child;
    struct ast_node* next;

    char* svalue;
};
typedef struct ast_node ast_node_t;

void ast_init(ast_node_t* node);

void ast_root(ast_node_t* node, ast_node_t* child);

ast_node_t* ast_create(ast_type_t type);

ast_node_t* ast_append(ast_node_t* list, ast_node_t* next);

ast_node_t* ast_child(ast_node_t* parent, ast_node_t* child);

ast_node_t* ast_single(ast_type_t type, ast_node_t* child);

ast_node_t* ast_named_single(ast_type_t type, char* id, ast_node_t* child);

ast_node_t* ast_join(ast_type_t type, ast_node_t* lhs, ast_node_t* rhs);

ast_node_t* ast_leaf(ast_type_t type, char* id);

ast_node_t* ast_cleaf(ast_type_t type, const char* id);

void ast_free(ast_node_t* node);

#endif
