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

#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include "ezscript.h"

void ez_trace(const char* file, unsigned int line, const char* msg)
{
    printf("%s(%d): %s\n", file, line, msg);
}

void ez_tracev(const char* file, unsigned int line, const char* format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 256, format, args);
    ez_trace(file, line, buffer);
    va_end(args);
}

const char* ez_result_to_string(ez_result_t r)
{
    switch (r)
    {
        case EZ_SUCCESS:
            return "EZ_SUCCESS";
        case EZ_INVALID_ARGUMENT:
            return "EZ_INVALID_ARGUMENT";
        case EZ_INVALID_TYPE:
            return "EZ_INVALID_TYPE";
        case EZ_OUT_OF_MEMORY:
            return "EZ_OUT_OF_MEMORY";
        case EZ_OVERFLOW:
            return "EZ_OVERFLOW";
        case EZ_INVALID_OP:
            return "EZ_INVALID_OP";
        case EZ_RUNTIME_ERRPOR:
            return "EZ_RUNTIME_ERRPOR";
        case EZ_PARSE_ERROR:
            return "EZ_PARSE_ERROR";
        default:
            assert(0);
            return "UNKNOWN";
    }
}

const char* ez_type_to_string(ez_type_t t)
{
    switch (t)
    {
        case EZ_TYPE_UNDEFINED:
            return "EZ_TYPE_UNDEFINED";
        case EZ_TYPE_NULL:
            return "EZ_TYPE_NULL";
        case EZ_TYPE_BOOLEAN:
            return "EZ_TYPE_BOOLEAN";
        case EZ_TYPE_INTEGER:
            return "EZ_TYPE_INTEGER";
        case EZ_TYPE_REAL:
            return "EZ_TYPE_REAL";
        case EZ_TYPE_OBJECT:
            return "EZ_TYPE_OBJECT";
        case EZ_TYPE_FUNCTION:
            return "EZ_TYPE_FUNCTION";
        default:
            assert(0);
            return "UNKNOWN";
    }
}
