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

int ez_init_context(ez_context* context)
{
    if (context == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    memset(context, 0, sizeof(ez_context));
    return EZ_OK;
}

int ez_cleanup_context(ez_context* context)
{
    if (context == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if (context->error_string != NULL)
    {
        free(context->error_string);
    }

    memset(context, 0, sizeof(ez_context));

    return EZ_OK;
}

int ez_execute(ez_context* context, const char* code)
{
    return EZ_NOT_IMPLEMENTED;
}