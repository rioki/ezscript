//
// ezscript
//
// Copyright 2018-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <gtest/gtest.h>

#include "ezscript.h"

TEST(C_API, test_null_value) 
{
    ez_result_t r;
    ez_value_t  value;
    ez_type_t   type;
    
    r = ez_create_null(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_type(&value, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(type == EZ_TYPE_NULL);
    
    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_create_null_null)
{
    ez_result_t r;
    
    r = ez_create_null(NULL);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_copy_null)
{
    ez_result_t r;
    ez_value_t  first, second;
    ez_type_t   type;    

    r = ez_create_null(&first);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_copy_value(&second, &first);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_type(&second, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(type == EZ_TYPE_NULL);

    r = ez_release_value(&first);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&second);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_boolean_value)
{
    ez_result_t r;
    ez_value_t  value;
    ez_type_t   type;
    int         bvalue;

    r = ez_create_boolean(&value, 1);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_type(&value, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(type == EZ_TYPE_BOOLEAN);
    
    r = ez_get_boolean(&value, &bvalue);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(bvalue == 1);

    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_create_boolean_null)
{
    ez_result_t r;
    
    r = ez_create_boolean(NULL, 1);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_get_boolean_null)
{
    ez_result_t r;
    ez_value_t  value;
    int         bvalue;

    r = ez_get_boolean(NULL, &bvalue);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);

    r = ez_get_boolean(&value, NULL);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_copy_boolean)
{
    ez_result_t r;
    ez_value_t  first, second;
    ez_type_t   type;  
    int         bvalue;  

    r = ez_create_boolean(&first, 0);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_copy_value(&second, &first);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_type(&second, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(type == EZ_TYPE_BOOLEAN);

    r = ez_get_boolean(&second, &bvalue);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(bvalue == 0);

    r = ez_release_value(&first);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&second);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_integer_value)
{
    ez_result_t r;
    ez_value_t  value;
    ez_type_t   type;
    long        ivalue;

    r = ez_create_integer(&value, 23);
    ASSERT_TRUE(r == EZ_SUCCESS);
    
    r = ez_get_type(&value, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(type == EZ_TYPE_INTEGER);
    
    r = ez_get_integer(&value, &ivalue);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(ivalue == 23);

    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_create_integer_null)
{
    ez_result_t r;
    
    r = ez_create_integer(NULL, 24);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_get_integer_null)
{
    ez_result_t r;
    ez_value_t  value;
    long        ivalue;
    
    r = ez_get_integer(NULL, &ivalue);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);

    r = ez_get_integer(&value, NULL);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_copy_integer)
{
    ez_result_t r;
    ez_value_t  first, second;
    ez_type_t   type;  
    long        ivalue;  

    r = ez_create_integer(&first, 1984);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_copy_value(&second, &first);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_type(&second, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(type == EZ_TYPE_INTEGER);

    r = ez_get_integer(&second, &ivalue);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(ivalue == 1984);

    r = ez_release_value(&first);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&second);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_real_value)
{
    ez_result_t r;
    ez_value_t  value;
    ez_type_t   type;
    double      rvalue;

    r = ez_create_real(&value, 23.0);
    ASSERT_TRUE(r == EZ_SUCCESS);
    
    r = ez_get_type(&value, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(type == EZ_TYPE_REAL);
    
    r = ez_get_real(&value, &rvalue);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(rvalue == 23.0);

    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}


TEST(C_API, test_create_real_null)
{
    ez_result_t r;
    
    r = ez_create_real(NULL, 24);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_get_real_null)
{
    ez_result_t r;
    ez_value_t  value;
    double      rvalue;
    
    r = ez_get_real(NULL, &rvalue);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);

    r = ez_get_real(&value, NULL);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_copy_real)
{
    ez_result_t r;
    ez_value_t  first, second;
    ez_type_t   type;  
    double      rvalue;  

    r = ez_create_real(&first, 90.1);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_copy_value(&second, &first);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_type(&second, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(type == EZ_TYPE_REAL);

    r = ez_get_real(&second, &rvalue);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(rvalue == 90.1);

    r = ez_release_value(&first);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&second);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_get_type_null)
{
    ez_result_t r;
    ez_value_t  value;
    ez_type_t   type;

    r = ez_get_type(NULL, &type);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);

    r = ez_get_type(&value, NULL);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_release_value_null)
{
    ez_result_t r;    
    
    r = ez_release_value(NULL);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_copy_null_poitners)
{
    ez_result_t r;
    ez_value_t  value;

    r = ez_create_null(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_copy_value(NULL, &value);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);

    r = ez_copy_value(&value, NULL);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);

    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_var_keyword)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  v;
    ez_type_t   v_type;
    const char code[] = "var v = null;\n";
    
    r = ez_create_object(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "v", &v);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_type(&v, &v_type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(v_type == EZ_TYPE_NULL);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}
