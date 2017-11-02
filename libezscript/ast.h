/*
    ezscript
    Copyright (c) 2017 Sean Farrell <sean.farrell@rioki.org>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

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

#ifndef _EZ_AST_H_
#define _EZ_AST_H_

// NOTE:
// The AST API does not follow the public result driven style. This is done
// to simplify the parser's code. The AST generation is directly tied
// into the parser's implementation and should not be seen as a sepeate
// or stable API.

#include "ezscript.h"

enum ez_ast_node_type_e 
{
    EZ_AST_ROOT,
    EZ_AST_NUMBER,
    EZ_AST_IDENTIFIER,
    EZ_AST_STRING,
    EZ_VARIABLE_DECLARATION,
    EZ_STATEMENT

};
typedef enum ez_ast_node_type_e ez_ast_node_type_t;

struct ez_ast_s 
{
    ez_ast_node_type_t type;
    char*              file;
    int                line;
    char*              svalue;
    struct ez_ast_s*   next;
    struct ez_ast_s*   child;
};
typedef struct ez_ast_s ez_ast_t;

ez_ast_t* ez_ast_create(const char* file, int line, ez_ast_node_type_t type, const char* svalue);

ez_ast_t* ez_ast_append_sibling(ez_ast_t* fist, ez_ast_t* next);

ez_ast_t* ez_ast_append_child(ez_ast_t* parent, ez_ast_t* child);

void ez_ast_free(ez_ast_t* node);

#endif
