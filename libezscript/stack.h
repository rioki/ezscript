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

struct _ez_stack
{
    size_t      size;
    size_t      top;
    ez_value_t* stack;
};
typedef struct _ez_stack ez_stack_t;

ez_result_t ez_allocate_stack(ez_stack_t* stack, size_t size);
ez_result_t ez_free_stack(ez_stack_t* stack);
ez_result_t ez_push_stack(ez_stack_t* stack, ez_value_t* value);
ez_result_t ez_pop_stack(ez_stack_t* stack, ez_value_t* value);
