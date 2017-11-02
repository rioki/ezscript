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

#include <string.h>
#include <stdlib.h>

#include "interpreter.h"

int ez_context_init(ez_context_t* context)
{
    if (context == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    memset(context, 0, sizeof(ez_context_t));
    return EZ_OK;
}

int ez_context_clear(ez_context_t* context)
{
    if (context == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if (context->error_string != NULL)
    {
        free(context->error_string);
    }

    memset(context, 0, sizeof(ez_context_t));

    return EZ_OK;
}

int ez_execute(ez_context_t* context, ez_code_t* code)
{
    return EZ_NOT_IMPLEMENTED;
}

int ez_evaluate(ez_context_t* context, const char* scode)
{
    // TODO remove memory leak of code
    int ezres;
    ez_code_t code;

    if (context == NULL || scode == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if (strcmp(scode, "") == 0)
    {
        // explicitly handling empty sting make the parser simpler
        return EZ_OK;
    }

    ezres = ez_code_init(&code);
    if (ezres != EZ_OK)
    {
        return ezres;
    }

    ezres = ez_compile(&code, scode);
    if (ezres != EZ_OK)
    {
        return ezres;
    }

    ezres = ez_execute(context, &code);
    if (ezres != EZ_OK)
    {
        return ezres;
    }

    ezres = ez_code_clear(&code);
    if (ezres != EZ_OK)
    {
        return ezres;
    }

    return EZ_OK;
}

int ez_value_get(ez_context_t* context, const char* id, ez_value_t* value)
{
    return ES_UNDEFINED;
}

int ez_value_set(ez_context_t* context, const char* id, ez_value_t* value)
{
    return ES_UNDEFINED;
}