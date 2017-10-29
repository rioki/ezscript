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

int test_code_init_null()
{
    int r = ez_code_init(NULL);

    TST_ASSERT(r == EZ_INVALID_ARGUMENT);
    
    return 1;
}

int test_code_cleanup_null()
{
    int r = ez_code_cleanup(NULL);

    TST_ASSERT(r == EZ_INVALID_ARGUMENT);
    
    return 1;
}

int test_code_simple_life()
{
    int r;
    ez_code_t code;
    r = ez_code_init(&code);
    TST_ASSERT(r == EZ_OK);

    r = ez_code_cleanup(&code);
    TST_ASSERT(r == EZ_OK);
    
    return 1;
}

int test_parse_null()
{
    int r;
    ez_code_t code;
    r = ez_code_init(&code);
    TST_ASSERT(r == EZ_OK);

    r = ez_compile(&code, NULL);
    TST_ASSERT(r == EZ_INVALID_ARGUMENT);

    r = ez_code_cleanup(&code);
    TST_ASSERT(r == EZ_OK);
    
    return 1;
}

int test_parse_empty()
{
    int r;
    ez_code_t code;
    r = ez_code_init(&code);
    TST_ASSERT(r == EZ_OK);

    r = ez_compile(&code, "");
    TST_ASSERT(r == EZ_OK);

    r = ez_code_cleanup(&code);
    TST_ASSERT(r == EZ_OK);
    
    return 1;
}

int test_parse_variable()
{
    int r;
    ez_code_t code;
    r = ez_code_init(&code);
    TST_ASSERT(r == EZ_OK);

    r = ez_compile(&code, "var i = 1;");
    TST_ASSERT(r == EZ_OK);

    r = ez_code_cleanup(&code);
    TST_ASSERT(r == EZ_OK);
    
    return 1;
}

int register_parse_tests()
{
    TST_REGISTER(test_code_init_null);
    TST_REGISTER(test_code_cleanup_null);
    TST_REGISTER(test_code_simple_life);
    TST_REGISTER(test_parse_empty);
    TST_REGISTER(test_parse_variable);
    
    return 0;
}
