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

#include "ezlexer.h"
#include "ezparser.h"

int ez_code_init(ez_code_t* code)
{
    if (code == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    memset(code, 0, sizeof(ez_code_t));
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

int ez_compile(ez_code_t* code, const char* scode)
{
    YY_BUFFER_STATE buffer;
    int             result;

    if (code == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if (strcmp(scode, "") == 0)
    {
        // explicitly handling empty sting make the parser simpler
        return EZ_OK;
    }
    
    buffer = ez_scan_string(scode);
    
    result = ezparse();
    
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