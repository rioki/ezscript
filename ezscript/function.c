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

#include <stdlib.h>
#include <string.h>

#include "ezscript.h"
#include "interpreter.h"
#include "dbg.h"

struct _ez_function
{
    int         count;
    ez_function function;
    ez_code_t*  code;
};

ez_result_t _ez_init_function(ez_function_t* function, ez_function ptr, ez_code_t* code)
{
    if (function == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    function->count    = 1;
    function->function = ptr;
    function->code     = code;

    return EZ_SUCCESS;
}

ez_result_t _ez_reference_function(ez_function_t* function)
{
    if (function == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    function->count++;

    return EZ_SUCCESS;
}

ez_result_t _ez_release_function(ez_function_t* function)
{
    if (function == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    function->count--;

    if (function->count == 0)
    {
        free(function->code);
        free(function);
    }

    return EZ_SUCCESS;
}

ez_result_t ez_create_function(ez_value_t* value, ez_function ptr)
{
    if (value == NULL || ptr == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    value->type     = EZ_TYPE_FUNCTION;
    value->function = (ez_function_t*)malloc(sizeof(ez_function_t));

    if (value->function == NULL)
    {
        return EZ_OUT_OF_MEMORY;
    }

    return _ez_init_function(value->function, ptr, NULL);
}

ez_result_t ez_wrap_code(ez_value_t* value, ez_code_t* code)
{
    if (value == NULL || code == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    value->type     = EZ_TYPE_FUNCTION;
    value->function = (ez_function_t*)malloc(sizeof(ez_function_t));

    if (value->function == NULL)
    {
        return EZ_OUT_OF_MEMORY;
    }

    return _ez_init_function(value->function, NULL, code);
}

ez_result_t ez_call_function(const ez_value_t* function, ez_value_t* this, ez_value_t* result, int argc, const ez_value_t* argv)
{
    EZ_CHECK_ARGUMENT(function != NULL);
    EZ_CHECK_ARGUMENT(this != NULL);
    EZ_CHECK_ARGUMENT(argc >= 0);
    EZ_CHECK_ARGUMENT(argc == 0 || argv != NULL);
    EZ_CHECK_TYPE(function, EZ_TYPE_FUNCTION);

    if (function->function->function)
    {
        return function->function->function(this, result, argc, argv);
    }
    else
    {
        return ez_exec_code(this, function->function->code);
    }
}

ez_result_t ez_print_function_code(FILE* fd, ez_value_t* function)
{
    ez_result_t r;

    EZ_CHECK_ARGUMENT(function != NULL);
    EZ_CHECK_ARGUMENT(fd);
    EZ_CHECK_TYPE(function, EZ_TYPE_FUNCTION);
    
    if (function->function->code == NULL)
    {
        EZ_TRACE("Not a scripted function.");
        return EZ_INVALID_TYPE;
    }

    r = ez_print_code(fd, function->function->code);
    if (r < 0)
    {
        EZ_TRACEV("Failed to print code: %s", ez_result_to_string(r));
        return r;
    }

    return EZ_SUCCESS;
}

