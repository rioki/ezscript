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

#include "ezscript.h"
#include "dbg.h"

unsigned int array_magic = 0x4005FB18;

struct _ez_element
{
    ez_value_t value;
    struct _ez_element* next;
};
typedef struct _ez_element ez_element_t;

struct _ez_array
{
    unsigned int magic;
    ez_element_t* elements;
};
typedef struct _ez_array ez_array_t;

ez_result_t ez_create_array(ez_value_t* value)
{
    return EZ_NOT_IMPLEMENTED;
}

ez_result_t ez_get_element(const ez_value_t* object, size_t num, ez_value_t* value)
{
    return EZ_NOT_IMPLEMENTED;
}

ez_result_t ez_set_element(const ez_value_t* object, size_t num, ez_value_t* value)
{
    return EZ_NOT_IMPLEMENTED;
}

