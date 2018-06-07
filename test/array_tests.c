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

int test_empty_array_definition()
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  a;
    const char code[] = "var a = [];\n";
    
    r = ez_create_object(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_eval(&root, code);
    TEST_ASSERT(r == EZ_SUCCESS);    

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_define_array()
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  a, a0, a1, a2;
    long        va0, va1, va2;

    const char code[] = "var a = [1, 2, 3];\n";
    
    r = ez_create_object(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_eval(&root, code);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&root, "a", &a);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_element(&a, 0, &a0);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_integer(&a0, &va0);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(va0 == 1);

    r = ez_get_element(&a, 1, &a1);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_integer(&a1, &va1);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(va1 == 2);

    r = ez_get_element(&a, 2, &a2);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(va2 == 3);

    r = ez_get_integer(&a2, &va2);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&a);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

void run_array_tests(int* num_tests, int* num_errors)
{
    TEST_RUN(test_empty_array_definition);
    TEST_RUN(test_define_array);
}