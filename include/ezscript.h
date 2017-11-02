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

#ifndef _EZSCRIPT_H_
#define _EZSCRIPT_H_

#include <stdlib.h>

enum 
{
    EZ_OK               = 0,
    EZ_NOT_IMPLEMENTED  = -1,
    EZ_OUT_OF_MEMORY    = -2,
    EZ_INVALID_ARGUMENT = -3,
    EZ_PARSE_ERROR      = -4,
    ES_UNDEFINED        = -5
};

struct ez_code_s 
{
    size_t         length;
    unsigned char* code;
};
typedef struct ez_code_s ez_code_t;

struct ez_context_s 
{
    char* error_string;
};
typedef struct ez_context_s ez_context_t;

enum ez_value_type_e 
{
    EZ_TYPE_NULL,
    EZ_TYPE_BOOLEAN,
    EZ_TYPE_INTEGER,
    EZ_TYPE_REAL,
    EZ_TYPE_STRING,
    EZ_TYPE_ARRAY,
    EZ_TYPE_OBJECT
};
typedef enum ez_value_type_e ez_value_type_t;

struct ez_value_s {
    ez_value_type_t type;
    union 
    {
        int       boolean_value;
        long long integer_value;
        double    real_value;
        char*     string_value;
    };
};
typedef struct ez_value_s ez_value_t;

int ez_code_init(ez_code_t* code);
int ez_code_clear(ez_code_t* code);

int ez_value_init(ez_value_t* value);
int ez_value_get(ez_context_t* context, const char* id, ez_value_t* value);
int ez_value_set(ez_context_t* context, const char* id, ez_value_t* value);
int ez_value_clear(ez_value_t* value);

int ez_context_init(ez_context_t* context);
int ez_context_clear(ez_context_t* context);

int ez_compile(ez_code_t* code, const char* scode);
int ez_execute(ez_context_t* context, ez_code_t* code);

int ez_evaluate(ez_context_t* context, const char* scode);

const char* ez_error_string(int errorid);

#endif
