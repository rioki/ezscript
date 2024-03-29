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

#include "stack.h"
#include "dbg.h"

ez_result_t ez_allocate_stack(ez_stack_t* stack, size_t size)
{
    EZ_CHECK_ARGUMENT(stack != NULL);

    stack->size  = size;
    stack->top   = 0;
    stack->stack = (ez_value_t*)malloc(size * sizeof(ez_value_t));

    if (stack->stack == NULL)
    {
        EZ_TRACE("Failed to allocate stack.");
        return EZ_OUT_OF_MEMORY;
    }
    
    return EZ_SUCCESS;
}

ez_result_t ez_free_stack(ez_stack_t* stack)
{
    EZ_CHECK_ARGUMENT(stack != NULL);
    EZ_CHECK_ARGUMENT(stack->top == 0);

    free(stack->stack);

    return EZ_SUCCESS;
}

ez_result_t ez_push_stack(ez_stack_t* stack, ez_value_t* value)
{
    ez_result_t r;

    EZ_CHECK_ARGUMENT(stack != NULL);
    EZ_CHECK_ARGUMENT(value != NULL);

    if (stack->top >= stack->size)
    {
        EZ_TRACEV("Stack read out of bounds: top = %d, size = %d", stack->top, stack->size);
        return EZ_OVERFLOW;
    }

    r = ez_copy_value(&stack->stack[stack->top], value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to copy value to stack: %s", ez_result_to_string(r));
        return r;
    }
    stack->top += 1;

    return EZ_SUCCESS;
}

ez_result_t ez_pop_stack(ez_stack_t* stack, ez_value_t* value)
{
    ez_result_t r;

    EZ_CHECK_ARGUMENT(stack != NULL);
    EZ_CHECK_ARGUMENT(value != NULL);

    if (stack->top == 0)
    {
        EZ_TRACEV("Stack read out of bounds: top = %d, size = %d", stack->top, stack->size);
        return EZ_OVERFLOW;
    }

    r = ez_copy_value(value, &stack->stack[stack->top - 1]);
    if (r < 0)
    {
        EZ_TRACEV("Failed to copy value to stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&stack->stack[stack->top - 1]);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release stack value: %s", ez_result_to_string(r));
        return r;
    }

    stack->top -= 1;

    return EZ_SUCCESS;
}

ez_result_t ez_stack_top(ez_stack_t* stack, ez_value_t* value)
{
    ez_result_t r;

    EZ_CHECK_ARGUMENT(stack != NULL);
    EZ_CHECK_ARGUMENT(value != NULL);

    EZ_ASSERT(stack->top <= stack->size);

    r = ez_copy_value(value, &stack->stack[stack->top - 1]);
    if (r < 0)
    {
        EZ_TRACEV("Failed to copy value to stack: %s", ez_result_to_string(r));
        return r;
    }

    return EZ_SUCCESS;
}
