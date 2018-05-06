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
#include "string.h"

int test_create_string_value_null()
{
    ez_result_t r;

    r = ez_create_string(NULL, "YOLO");
    TEST_ASSERT(r == EZ_INVALID_ARGUMENT);

    return 0; 
}

int test_create_string_string_null()
{
    ez_result_t r;
    ez_value_t value;

    r = ez_create_string(&value, NULL);
    TEST_ASSERT(r == EZ_INVALID_ARGUMENT);

    return 0; 
}

int test_create_string()
{
    ez_result_t r;
    ez_value_t value;
    const char* text;

    r = ez_create_string(&value, "Hello World!");
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_string(&value, &text);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(strcmp(text, "Hello World!") == 0);

    r = ez_release_value(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_get_string_with_object()
{
    ez_result_t r;
    ez_value_t value;
    const char* text;

    r = ez_create_object(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_string(&value, &text);
    TEST_ASSERT(r == EZ_INVALID_TYPE);

    r = ez_release_value(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}


int test_get_string_with_object_with_data()
{
    ez_result_t r;
    ez_value_t value;
    const char* text;

    r = ez_create_object(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_set_object_data(&value, &value);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_string(&value, &text);
    TEST_ASSERT(r == EZ_INVALID_TYPE);

    r = ez_release_value(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_string_from_code()
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  string;
    const char* text;
    const char code[] = "string = \"Hello World!\";";
    
    r = ez_create_object(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_eval(&root, code);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&root, "string", &string);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_string(&string, &text);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_STRING("Hello World!", text);

    r = ez_release_value(&string);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

void run_string_tests(int* num_tests, int* num_errors)
{
    TEST_RUN(test_create_string_value_null);
    TEST_RUN(test_create_string_string_null);
    TEST_RUN(test_create_string);
    TEST_RUN(test_get_string_with_object);
    TEST_RUN(test_get_string_with_object_with_data);
    TEST_RUN(test_string_from_code);
}