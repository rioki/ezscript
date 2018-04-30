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

struct _ez_member
{
    char*              id;
    ez_value_t         value;
    struct _ez_member* next;
};
typedef struct _ez_member ez_member_t;

struct _ez_object 
{
    int          count;
    ez_member_t* members;
    void*        data;
};

ez_result_t _ez_init_object(ez_object_t* object)
{
    if (object == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    object->count   = 1;
    object->members = NULL;
    object->data    = NULL;

    return EZ_SUCCESS;
}

ez_result_t _ez_reference_object(ez_object_t* object)
{
    if (object == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    object->count++;

    return EZ_SUCCESS;
}

ez_result_t _ez_release_object(ez_object_t* object)
{
    ez_result_t r;

    if (object == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    object->count--;
 
    if (object->count == 0) 
    {
        ez_member_t* member = object->members;
        while (member != NULL)
        {
            r = ez_release_value(&member->value);
            if (r < 0)            
            {
                EZ_TRACEV("Failed to release member %s: %s", member->id, ez_result_to_string(r));
                return r;
            }
            member = member->next;
        }

        free(object);
    }

    return EZ_SUCCESS;
}

ez_result_t ez_create_object(ez_value_t* value)
{
    if (value == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    value->type   = EZ_TYPE_OBJECT;
    value->object = (ez_object_t*)malloc(sizeof(ez_object_t));

    if (value->object == NULL)
    {
        return EZ_OUT_OF_MEMORY;
    }

    return _ez_init_object(value->object);
}

ez_result_t ez_get_member(const ez_value_t* object, const char* id, ez_value_t* value)
{
    if (object == NULL || id == NULL || value == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if (object->type != EZ_TYPE_OBJECT) 
    {
        return EZ_INVALID_TYPE;
    }

    ez_member_t* member = object->object->members;
    while (member != NULL)
    {
        if (strcmp(member->id, id) == 0) {            
           return ez_copy_value(value, &(member->value));           
        }
        member = member->next;
    }

    value->type = EZ_TYPE_UNDEFINED;
    return EZ_SUCCESS;
}

ez_result_t ez_set_member(ez_value_t* object, const char* id, const ez_value_t* value)
{
    ez_result_t r = EZ_SUCCESS;

    if (object == NULL || id == NULL || value == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if (object->type != EZ_TYPE_OBJECT) 
    {
        return EZ_INVALID_TYPE;
    }

    ez_member_t* member = object->object->members;
    while (member != NULL)
    {
        if (strcmp(member->id, id) == 0) {
           return ez_copy_value(&(member->value), value);        
        }
        member = member->next;
    }

    member = (ez_member_t*)malloc(sizeof(ez_member_t));
    if (member == NULL)
    {
        return EZ_OUT_OF_MEMORY;
    }

    member->id = strdup(id);
    if (member->id == NULL)
    {
        free(member);
        return EZ_OUT_OF_MEMORY;
    }

    r = ez_copy_value(&(member->value), value);
    if (r != EZ_SUCCESS) 
    {
        free(member);
        return r;
    }
    member->next = NULL;
    
    if (object->object->members == NULL)
    {
        object->object->members = member;        
    }
    else
    {
        ez_member_t* last = object->object->members;
        while (last->next != NULL) 
        {
            last = last->next;
        }
        last->next = member;
    }

    return EZ_SUCCESS;
}

ez_result_t ez_set_object_data(ez_value_t* object, void* data)
{
    if (object == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if (object->type != EZ_TYPE_OBJECT) 
    {
        return EZ_INVALID_TYPE;
    }

    object->object->data = data;

    return EZ_SUCCESS;
}

ez_result_t ez_get_object_data(ez_value_t* object, void** data)
{
    if (object == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if (object->type != EZ_TYPE_OBJECT) 
    {
        return EZ_INVALID_TYPE;
    }

    (*data) = object->object->data;

    return EZ_SUCCESS;
}
