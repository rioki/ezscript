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

enum 
{
    EZ_OK               = 0,
    EZ_NOT_IMPLEMENTED  = -1,
    EZ_OUT_OF_MEMORY    = -2,
    EZ_INVALID_ARGUMENT = -3,
    EZ_PARSE_ERROR      = -40,
};

struct ez_context {
    const char* error_string;
};
typedef struct ez_context ez_context;

int ez_init_context(ez_context* context);
int ez_cleanup_context(ez_context* context);

int ez_compile(const char* code);

int ez_execute(ez_context* context, const char* code);

const char* ez_error_string(int errorid);

#endif
