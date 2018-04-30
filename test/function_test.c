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
#include "test.h"

ez_result_t add(ez_value_t* this, ez_value_t* result, int argc, const ez_value_t* argv)
{
    ez_result_t r = EZ_SUCCESS;
    ez_type_t   type0;
    ez_type_t   type1;
    long        value0;
    long        value1;

    if (argc != 2) 
    {
        return EZ_INVALID_ARGUMENT;
    }

    r = ez_get_type(&argv[0], &type0);
    if (r < 0) 
    {
        return r;        
    }

    r = ez_get_type(&argv[1], &type1);
    if (r < 0) 
    {
        return r;
    }

    if (type0 != EZ_TYPE_INTEGER || type1 != EZ_TYPE_INTEGER)
    {
        return EZ_INVALID_ARGUMENT;   
    }

    r = ez_get_integer(&argv[0], &value0);
    if (r < 0) 
    {
        return r;
    }

    r = ez_get_integer(&argv[1], &value1);
    if (r < 0) 
    {
        return r;
    }

    return ez_create_integer(result, value0 + value1);
}

int test_create_function()
{
    ez_result_t r;
    ez_value_t  value;
    ez_type_t   type;

    r = ez_create_function(&value, &add);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_type(&value, &type);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(type == EZ_TYPE_FUNCTION);
    
    r = ez_release_value(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_call_function()
{
    ez_result_t r;
    ez_value_t  function;
    ez_value_t  this;
    ez_value_t  result;
    ez_value_t  argv[2];
    long        rvalue;

    r = ez_create_object(&this);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_create_function(&function, &add);
    TEST_ASSERT(r == EZ_SUCCESS);

    // var a = 1;
    r = ez_create_integer(&argv[0], 1);
    TEST_ASSERT(r == EZ_SUCCESS);

    // var b = 2;
    r = ez_create_integer(&argv[1], 2);
    TEST_ASSERT(r == EZ_SUCCESS);

    // var r = add(a, b);
    r = ez_call_function(&function, &this, &result, 2, argv);
    TEST_ASSERT(r == EZ_SUCCESS);

    // assert(r == 3);
    r = ez_get_integer(&result, &rvalue);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(rvalue == 3);
    
    r = ez_release_value(&this);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_release_value(&argv[0]);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_release_value(&argv[1]);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_release_value(&result);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_release_value(&function);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

void run_function_tests(int* num_tests, int* num_errors)
{
    TEST_RUN(test_create_function); 
    TEST_RUN(test_call_function); 
}
