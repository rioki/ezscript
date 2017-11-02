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

#include "ezscript.h"

#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "ezlexer.h"
#include "ezparser.h"
#include "interpreter.h"

#define EZ_CODE_CHUNK_SIZE 1024

int ez_code_init(ez_code_t* code)
{
    if (code == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    memset(code, 0, sizeof(ez_code_t));

    code->length = EZ_CODE_CHUNK_SIZE;
    code->code   = malloc(EZ_CODE_CHUNK_SIZE);

    return EZ_OK;
}

int ez_code_extend(ez_code_t* code)
{
    if (code == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    unsigned int length = code->length + EZ_CODE_CHUNK_SIZE;
    code->code   = realloc(code->code, length);
    code->length = length;

    if (code->code == NULL)
    {
        return EZ_OUT_OF_MEMORY;
        code->length = 0;
    }

    return EZ_OK;
}

int ez_code_extend_length(ez_code_t* code, unsigned int len)
{
    if (code == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if (len < EZ_CODE_CHUNK_SIZE)
    {
        return ez_code_extend(code);
    }

    unsigned int lrem = EZ_CODE_CHUNK_SIZE - (len % EZ_CODE_CHUNK_SIZE);

    unsigned int length = code->length + len + lrem;
    assert(code->length % EZ_CODE_CHUNK_SIZE == 0);

    code->code   = realloc(code->code, length);
    code->length = length;

    if (code->code == NULL)
    {
        return EZ_OUT_OF_MEMORY;
        code->length = 0;
    }

    return EZ_OK;
}


int ez_code_clear(ez_code_t* code)
{
    if (code == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    return EZ_OK;
}

int ez_parse_memory(const char* file, const char* scode, ez_ast_t* ast_root)
{
    YY_BUFFER_STATE buffer;
    int             result;

    assert(file != NULL);
    assert(scode != NULL);
    
    buffer = ez_scan_string(scode);
    
    result = ezparse(file, ast_root);
    
    ez_delete_buffer(buffer);

    switch (result)
    {
        case 0:
            return EZ_OK;
        case 2:
            return EZ_OUT_OF_MEMORY;
        case 1:
        default:
            return EZ_PARSE_ERROR;
    }
}

int ez_code_add_op(ez_code_t* code, unsigned int* offset, ez_opcode_t op)
{
    if (code == NULL || offset == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if (code->length == *offset)
    {
        int r  = ez_code_extend(code);
        if (r != EZ_OK)
        {
            return r;
        }
    }

    code->code[*offset] = (unsigned char)op;
    (*offset)++;

    return EZ_OK;
}

int ez_code_add_string(ez_code_t* code, unsigned int* offset, const char* string)
{
    if (code == NULL || offset == NULL || string == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    unsigned int sl = strlen(string) + 1; // we need the terminator

    if (code->length < (*offset) + sl)
    {
        ez_code_extend_length(code, sl);
        assert(code->length > (*offset) + sl);
    }
    
    for (unsigned int i = 0; i < sl; i++)
    {
        code->code[(*offset) + i] = (unsigned char)string[i];
    }

    (*offset) += sl;
}

int ez_generate_statement(ez_code_t* code, unsigned int* offset, ez_ast_t* node)
{
    
}

int ez_code_generate(ez_code_t* code, ez_ast_t* ast_root)
{
    assert(code != NULL);
    assert(ast_root != NULL);
    assert(ast_root->type == EZ_AST_ROOT);
    assert(ast_root->next == NULL);

    int          res    = EZ_OK;
    unsigned int offset = 0;
    ez_ast_t*    node   = ast_root->child;

    while (node)
    {
        res = ez_generate_statement(code, &offset, node);
        if (res != EZ_OK)
        {
            return res;
        }

        node = node->next;
    }

    return EZ_OK;
}

int ez_compile(ez_code_t* code, const char* scode)
{
    const char* file        = "memory";
    ez_ast_t*   ast_root    = NULL;
    int         res         = EZ_OK;

    if (code == NULL || scode == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }
    
    if (strcmp(scode, "") == 0)
    {
        // explicitly handling empty sting make the parser simpler
        return EZ_OK;
    }
    
    ast_root = ez_ast_create(file, 0, EZ_AST_ROOT, NULL);
    if (ast_root == NULL)
    {
        return EZ_OUT_OF_MEMORY;
    }

    res = ez_parse_memory(file, scode, ast_root);
    if (res != EZ_OK)
    {
        return res;
    }

    res = ez_code_generate(code, ast_root);
    if (res != EZ_OK)
    {
        return res;
    }

    return EZ_OK;
}