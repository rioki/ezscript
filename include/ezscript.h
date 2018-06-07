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

#ifndef _EZSCRIPT_H_
#define _EZSCRIPT_H_

#include <stdio.h>

enum _ez_result 
{
    EZ_SUCCESS          =  0,
    EZ_INVALID_ARGUMENT = -1,
    EZ_INVALID_TYPE     = -2,
    EZ_OUT_OF_MEMORY    = -3,
    EZ_OVERFLOW         = -4,
    EZ_INVALID_OP       = -5,
    EZ_RUNTIME_ERROR    = -6,
    EZ_PARSE_ERROR      = -15,
    EZ_NOT_IMPLEMENTED  = -666
};
typedef enum _ez_result ez_result_t;

enum _ez_type 
{
    EZ_TYPE_UNDEFINED,
    EZ_TYPE_NULL,    
    EZ_TYPE_BOOLEAN,
    EZ_TYPE_INTEGER,
    EZ_TYPE_REAL,
    EZ_TYPE_OBJECT,
    EZ_TYPE_FUNCTION
};
typedef enum _ez_type ez_type_t;

struct _ez_object;
typedef struct _ez_object ez_object_t;

struct _ez_function;
typedef struct _ez_function ez_function_t;

struct _ez_value 
{
    ez_type_t type;

    union 
    {
        long           long_value;
        double         double_value;
        ez_object_t*   object;
        ez_function_t* function;
    };    
};
typedef struct _ez_value ez_value_t;

typedef ez_result_t (*ez_function)(ez_value_t* this, ez_value_t* result, int argc, const ez_value_t* argv);

ez_result_t ez_create_null(ez_value_t* value);

ez_result_t ez_create_boolean(ez_value_t* value, int bvalue);

ez_result_t ez_create_integer(ez_value_t* value, long ivalue);

ez_result_t ez_create_real(ez_value_t* value, double rvalue);

ez_result_t ez_create_object(ez_value_t* value);

ez_result_t ez_create_typed_object(ez_value_t* value, const char* type);

ez_result_t ez_create_string(ez_value_t* value, const char* string);

ez_result_t ez_wrap_string(ez_value_t* value, char* string);

ez_result_t ez_create_array(ez_value_t* value);

ez_result_t ez_create_function(ez_value_t* value, ez_function function);

ez_result_t ez_get_type(const ez_value_t* value, ez_type_t* type);

ez_result_t ez_get_object_type(const ez_value_t* value, const char** type);

ez_result_t ez_get_boolean(const ez_value_t* value, int* bvalue);

ez_result_t ez_get_integer(const ez_value_t* value, long* ivalue);

ez_result_t ez_get_real(const ez_value_t* value, double* ivalue);

ez_result_t ez_get_string(const ez_value_t* value, const char** string);

ez_result_t ez_get_member(const ez_value_t* object, const char* id, ez_value_t* value);

ez_result_t ez_set_member(ez_value_t* object, const char* id, const ez_value_t* value);

ez_result_t ez_get_element(const ez_value_t* object, size_t num, ez_value_t* value);

ez_result_t ez_set_element(const ez_value_t* object, size_t num, ez_value_t* value);

ez_result_t ez_call_function(const ez_value_t* function, ez_value_t* this, ez_value_t* result, int argc, const ez_value_t* argv);

ez_result_t ez_copy_value(ez_value_t* dest, const ez_value_t* source);

ez_result_t ez_release_value(ez_value_t* value);

ez_result_t ez_set_object_data(ez_value_t* object, void* data);

ez_result_t ez_get_object_data(ez_value_t* object, void** data);

ez_result_t ez_compile(ez_value_t* function, const char* code);

ez_result_t ez_eval(ez_value_t* root, const char* code);

ez_result_t ez_print_function_code(FILE* fd, ez_value_t* function);

const char* ez_result_to_string(ez_result_t r);
const char* ez_type_to_string(ez_type_t t);

#endif
