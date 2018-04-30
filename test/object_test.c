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


int test_create_object_null()
{
    ez_result_t r;

    r = ez_create_object(NULL);
    TEST_ASSERT(r == EZ_INVALID_ARGUMENT);

    return 0; 
}

int test_get_member_null()
{
    ez_result_t r;
    ez_value_t  object;
    ez_value_t  value;
    
    r = ez_create_object(&object);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(NULL, "moo", &value);
    TEST_ASSERT(r == EZ_INVALID_ARGUMENT);
    r = ez_get_member(&object, NULL, &value);
    TEST_ASSERT(r == EZ_INVALID_ARGUMENT);
    r = ez_get_member(&object, "moo", NULL);
    TEST_ASSERT(r == EZ_INVALID_ARGUMENT);
    
    r = ez_release_value(&object);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_set_member_null()
{
    ez_result_t r;
    ez_value_t  object;
    ez_value_t  value;
    
    r = ez_create_object(&object);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_create_null(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(NULL, "moo", &value);
    TEST_ASSERT(r == EZ_INVALID_ARGUMENT);
    r = ez_get_member(&object, NULL, &value);
    TEST_ASSERT(r == EZ_INVALID_ARGUMENT);
    r = ez_get_member(&object, "moo", NULL);
    TEST_ASSERT(r == EZ_INVALID_ARGUMENT);
    
    r = ez_release_value(&object);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_create_object()
{
    ez_result_t r;
    ez_value_t  value;
    ez_type_t   type;

    r = ez_create_object(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_type(&value, &type);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(type == EZ_TYPE_OBJECT);
    
    r = ez_release_value(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0; 
}

int test_undefined_members()
{
    ez_result_t r;
    ez_value_t  object;
    ez_value_t  value;
    ez_type_t   type;
    
    r = ez_create_object(&object);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&object, "moo", &value);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_type(&value, &type);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(type == EZ_TYPE_UNDEFINED);
    
    r = ez_release_value(&object);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_release_value(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_set_member()
{
    ez_result_t r;
    ez_value_t  object;
    ez_value_t  first;
    ez_value_t  second;
    long        ivalue;

    
    r = ez_create_object(&object);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_create_integer(&first, 85);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_set_member(&object, "moo", &first);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&object, "moo", &second);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_integer(&second, &ivalue);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(ivalue == 85);
    
    r = ez_release_value(&object);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_release_value(&first);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_release_value(&second);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_multiple_values()
{
    ez_result_t r;
    ez_value_t  object;
    ez_value_t  first;
    ez_value_t  second;
    long        ivalue;
    double      rvalue;
    
    r = ez_create_object(&object);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_create_integer(&first, 85);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_set_member(&object, "a", &first);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_release_value(&first);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_create_real(&first, 123.6);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_set_member(&object, "b", &first);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_release_value(&first);
    TEST_ASSERT(r == EZ_SUCCESS);
    


    r = ez_get_member(&object, "a", &second);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_get_integer(&second, &ivalue);
    TEST_ASSERT(r == EZ_SUCCESS);    
    TEST_ASSERT(ivalue == 85);
    r = ez_release_value(&second);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&object, "b", &second);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_get_real(&second, &rvalue);
    TEST_ASSERT(r == EZ_SUCCESS);    
    TEST_ASSERT(ivalue == 85);
    r = ez_release_value(&second);
    TEST_ASSERT(r == EZ_SUCCESS);
    
    r = ez_release_value(&object);
    TEST_ASSERT(r == EZ_SUCCESS);
    
    return 0;
}

int test_override_values()
{
    ez_result_t r;
    ez_value_t  object;
    ez_value_t  value;
    double      rvalue;
    
    r = ez_create_object(&object);
    TEST_ASSERT(r == EZ_SUCCESS);

    // object.a = 85
    r = ez_create_integer(&value, 85);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_set_member(&object, "a", &value);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_release_value(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    // object.a = 123.6
    r = ez_create_real(&value, 123.6);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_set_member(&object, "a", &value);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_release_value(&value);
    TEST_ASSERT(r == EZ_SUCCESS);

    // 123.6 == object.a
    r = ez_get_member(&object, "a", &value);
    TEST_ASSERT(r == EZ_SUCCESS);
    r = ez_get_real(&value, &rvalue);
    TEST_ASSERT(r == EZ_SUCCESS);    
    TEST_ASSERT(rvalue == 123.6);
    r = ez_release_value(&value);
    TEST_ASSERT(r == EZ_SUCCESS);
    
    r = ez_release_value(&object);
    TEST_ASSERT(r == EZ_SUCCESS);
    
    return 0;
}

int teat_object_data()
{
    ez_result_t r;
    ez_value_t  object;
    int         some_data = 90;
    int*        pdata = NULL;
    
    r = ez_create_object(&object);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_set_object_data(&object, &some_data);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_object_data(&object, (void*)&pdata);
    TEST_ASSERT(r == EZ_SUCCESS);

    TEST_ASSERT(*pdata == 90);
    TEST_ASSERT(pdata == &some_data);

    r = ez_release_value(&object);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

void run_object_tests(int* num_tests, int* num_errors)
{
    TEST_RUN(test_create_object_null); 
    TEST_RUN(test_get_member_null);
    TEST_RUN(test_set_member_null);
    TEST_RUN(test_create_object);    
    TEST_RUN(test_undefined_members);  
    TEST_RUN(test_set_member);
    TEST_RUN(test_multiple_values);
    TEST_RUN(test_override_values);
    TEST_RUN(teat_object_data);
}