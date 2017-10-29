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

int test_context_init_null()
{
    int r = ez_init_context(NULL);

    TST_ASSERT(r == EZ_INVALID_ARGUMENT);
    
    return 1;
}

int test_context_cleanup_null()
{
    int r = ez_cleanup_context(NULL);

    TST_ASSERT(r == EZ_INVALID_ARGUMENT);
    
    return 1;
}

int test_context_simple_life()
{
    int r;
    ez_context context;
    r = ez_init_context(&context);
    TST_ASSERT(r == EZ_OK);

    r = ez_cleanup_context(&context);
    TST_ASSERT(r == EZ_OK);
    
    return 1;
}

int register_context_tests()
{
    TST_REGISTER(test_context_init_null);
    TST_REGISTER(test_context_cleanup_null);
    TST_REGISTER(test_context_simple_life);
    
    return 0;
}
