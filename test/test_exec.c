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

#include "test.h"
#include "ezscript.h"

int test_execute_empty()
{
    int r;
    ez_context_t context;
    r = ez_context_init(&context);
    TST_ASSERT(r == EZ_OK);

    r = ez_evaluate(&context, "");
    TST_ASSERT(r == EZ_OK);

    r = ez_context_clear(&context);
    TST_ASSERT(r == EZ_OK);
    
    return 1;
}

int test_assign_variable()
{
    int r;
    ez_context_t context;
    r = ez_context_init(&context);
    TST_ASSERT(r == EZ_OK);

    r = ez_evaluate(&context, "var i = 12;");
    TST_ASSERT(r == EZ_OK);

    ez_value_t value;
    r = ez_value_get(&context, "i", &value);
    TST_ASSERT(r == EZ_OK);

    TST_ASSERT(value.type == EZ_TYPE_INTEGER);
    TST_ASSERT(value.integer_value == 12);
    ez_value_clear(&value);

    r = ez_context_clear(&context);
    TST_ASSERT(r == EZ_OK);
    
    return 1;
}

int register_exec_tests()
{
    TST_REGISTER(test_execute_empty);
    TST_REGISTER(test_assign_variable);
    
    return 0;
}
