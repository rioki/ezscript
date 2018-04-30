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

#include "ezscript.h"
#include "dbg.h"

ez_result_t _ez_release_object(ez_object_t* object);
ez_result_t _ez_reference_object(ez_object_t* object);

ez_result_t _ez_release_function(ez_function_t* function);
ez_result_t _ez_reference_function(ez_function_t* function);

ez_result_t ez_create_null(ez_value_t* value)
{
    if (value == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    value->type = EZ_TYPE_NULL;

    return EZ_SUCCESS;
}

ez_result_t ez_create_boolean(ez_value_t* value, int bvalue)
{
    if (value == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    value->type       = EZ_TYPE_BOOLEAN;
    value->long_value = bvalue;

    return EZ_SUCCESS;
}

ez_result_t ez_create_integer(ez_value_t* value, long ivalue)
{
    EZ_CHECK_ARGUMENT(value != NULL);

    value->type       = EZ_TYPE_INTEGER;
    value->long_value = ivalue;

    return EZ_SUCCESS;
}

ez_result_t ez_create_real(ez_value_t* value, double rvalue)
{
    if (value == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    value->type         = EZ_TYPE_REAL;
    value->double_value = rvalue;

    return EZ_SUCCESS;
}

ez_result_t ez_get_type(const ez_value_t* value, ez_type_t* type)
{
    if (value == NULL || type == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    *type = value->type;

    return EZ_SUCCESS;
}

ez_result_t ez_get_boolean(const ez_value_t* value, int* bvalue)
{
    if (value == NULL || bvalue == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if (value->type != EZ_TYPE_BOOLEAN) 
    {
        return EZ_INVALID_TYPE;
    }
    
    *bvalue = value->long_value;

    return EZ_SUCCESS;
}

ez_result_t ez_get_integer(const ez_value_t* value, long* ivalue)
{
    EZ_CHECK_ARGUMENT(value != NULL);
    EZ_CHECK_ARGUMENT(ivalue != NULL);
    EZ_CHECK_TYPE(value, EZ_TYPE_INTEGER);
    
    *ivalue = value->long_value;

    return EZ_SUCCESS;
}

ez_result_t ez_get_real(const ez_value_t* value, double* rvalue)
{
    if (value == NULL || rvalue == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if (value->type != EZ_TYPE_REAL) 
    {
        return EZ_INVALID_TYPE;
    }
    
    *rvalue = value->double_value;

    return EZ_SUCCESS;
}

ez_result_t ez_copy_value(ez_value_t* dest, const ez_value_t* source)
{
    ez_result_t r = EZ_SUCCESS;

    if (dest == NULL || source == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }    

    dest->type = source->type;

    switch (source->type)
    {    
        case EZ_TYPE_BOOLEAN:
        case EZ_TYPE_INTEGER:
            dest->long_value = source->long_value;
            break;
        case EZ_TYPE_REAL:
            dest->double_value = source->double_value;
            break;
        case EZ_TYPE_OBJECT:            
            dest->object = source->object;
            r = _ez_reference_object(dest->object);
            break;
        case EZ_TYPE_FUNCTION:            
            dest->function = source->function;
            r = _ez_reference_function(dest->function);
            break;
        default:
            /* stfu */
            break;            
    }

    return r;
}

ez_result_t ez_release_value(ez_value_t* value)
{
    ez_result_t r = EZ_SUCCESS;

    if (value == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    switch (value->type)
    {
        case EZ_TYPE_OBJECT:
            r = _ez_release_object(value->object);
            value->object = NULL;
            break;
        case EZ_TYPE_FUNCTION:
            r = _ez_release_function(value->function);
            value->function = NULL;
            break;
        default:
            /* stfu */
            break;            
    }

    value->type = EZ_TYPE_NULL;    

    return r;
}
