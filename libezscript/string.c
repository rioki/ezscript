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
#include "dbg.h"

unsigned int string_magic = 0x2996EBA4;
struct _ez_string
{
    unsigned int magic;
    char* string;
};
typedef struct _ez_string ez_string_t;

ez_result_t _ez_string_equals(ez_value_t* this, ez_value_t* result, int argc, const ez_value_t* argv)
{
    ez_result_t r;
    const char* lhs;
    const char* rhs;
    char*       res;
    size_t      len, lhs_len, rhs_len;

    EZ_CHECK_ARGUMENT(this != NULL);
    EZ_CHECK_ARGUMENT(result != NULL);
    EZ_CHECK_ARGUMENT(argc == 1);
    EZ_CHECK_ARGUMENT(argv != NULL);

    r = ez_get_string(this, &lhs);
    EZ_CHECK_RESULT(r);

    r = ez_get_string(argv, &rhs);
    EZ_CHECK_RESULT(r);

    r = ez_create_boolean(result, strcmp(lhs, rhs) == 0);
    EZ_CHECK_RESULT(r);

    return EZ_SUCCESS;
}

ez_result_t _ez_string_add(ez_value_t* this, ez_value_t* result, int argc, const ez_value_t* argv)
{
    ez_result_t r;
    const char* lhs;
    const char* rhs;
    char*       res;
    size_t      len, lhs_len, rhs_len;

    EZ_CHECK_ARGUMENT(this != NULL);
    EZ_CHECK_ARGUMENT(result != NULL);
    EZ_CHECK_ARGUMENT(argc == 1);
    EZ_CHECK_ARGUMENT(argv != NULL);

    r = ez_get_string(this, &lhs);
    EZ_CHECK_RESULT(r);

    r = ez_get_string(this, &rhs);
    EZ_CHECK_RESULT(r);

    lhs_len = strlen(lhs);
    rhs_len = strlen(rhs);
    len     = lhs_len + rhs_len;

    res = (char*)malloc(len);
    memcpy(res, lhs, lhs_len);
    memcpy(res + lhs_len, rhs, rhs_len);
    res[len] = 0;

    r = ez_wrap_string(result, res);
    EZ_CHECK_RESULT(r);

    return EZ_SUCCESS;
}

ez_result_t ez_create_string(ez_value_t* value, const char* string)
{
    ez_result_t r;
    char*       copy;

    EZ_CHECK_ARGUMENT(value != NULL);
    EZ_CHECK_ARGUMENT(string != NULL);

    copy = strdup(string);

    r = ez_wrap_string(value, copy);
    EZ_CHECK_RESULT(r);

    return EZ_SUCCESS;
}

ez_result_t ez_wrap_string(ez_value_t* value, char* string)
{
    ez_result_t r;
    ez_string_t* handle;
    ez_value_t equals, add;

    EZ_CHECK_ARGUMENT(value != NULL);
    EZ_CHECK_ARGUMENT(string != NULL);

    r = ez_create_typed_object(value, "string");
    EZ_CHECK_RESULT(r);

    handle = (ez_string_t*)malloc(sizeof(ez_string_t));
    handle->magic  = string_magic;
    handle->string = string;

    r = ez_set_object_data(value, handle);
    EZ_CHECK_RESULT(r);

    r = ez_create_function(&equals, _ez_string_equals);
    EZ_CHECK_RESULT(r);
    r = ez_create_function(&add, _ez_string_add);
    EZ_CHECK_RESULT(r);

    r = ez_set_member(value, "equals", &equals);
    EZ_CHECK_RESULT(r);
    r = ez_set_member(value, "add", &add);
    EZ_CHECK_RESULT(r);

    return EZ_SUCCESS;
}

ez_result_t ez_get_string(const ez_value_t* value, const char** string)
{
    ez_result_t r;
    const char* type;
    ez_string_t* handle;

    EZ_CHECK_ARGUMENT(value != NULL);
    EZ_CHECK_ARGUMENT(string != NULL);

    r = ez_get_object_type(value, &type);
    EZ_CHECK_RESULT(r);
    if (strcmp("string", type) != 0)
    {
        EZ_TRACEV("Expected object of type string, but got %s", type);
        return EZ_INVALID_TYPE;
    }

    r = ez_get_object_data(value, &handle);
    EZ_CHECK_RESULT(r);

    EZ_CHECK_ARGUMENT(handle != NULL);
    EZ_CHECK_ARGUMENT(handle->magic == string_magic);
    EZ_ASSERT(handle->string != NULL);

    *string = handle->string;

    return EZ_SUCCESS;
}