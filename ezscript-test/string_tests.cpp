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
#include "string.h"

TEST(C_API, test_create_string_value_null)
{
    ez_result_t r;

    r = ez_create_string(NULL, "YOLO");
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_create_string_string_null)
{
    ez_result_t r;
    ez_value_t value;

    r = ez_create_string(&value, NULL);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_create_string)
{
    ez_result_t r;
    ez_value_t value;
    const char* text;

    r = ez_create_string(&value, "Hello World!");
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_string(&value, &text);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(strcmp(text, "Hello World!") == 0);

    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_get_string_with_object)
{
    ez_result_t r;
    ez_value_t value;
    const char* text;

    r = ez_create_object(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_string(&value, &text);
    ASSERT_TRUE(r == EZ_INVALID_TYPE);

    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}


TEST(C_API, test_get_string_with_object_with_data)
{
    ez_result_t r;
    ez_value_t value;
    const char* text;

    r = ez_create_object(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_set_object_data(&value, &value);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_string(&value, &text);
    ASSERT_TRUE(r == EZ_INVALID_TYPE);

    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_string_from_code)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  string;
    const char* text;
    const char code[] = "string = \"Hello World!\";";
    
    r = ez_create_object(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "string", &string);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_string(&string, &text);
    ASSERT_TRUE(r == EZ_SUCCESS);
    EXPECT_STREQ("Hello World!", text);

    r = ez_release_value(&string);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_string_equals)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  x, y, z;
    int         value;
    const char code[] = "a = \"One\";\n"
                        "b = \"One\";\n"
                        "c = \"Two\";\n"
                        "x = a == b;\n"
                        "y = a == c;\n"
                        "z = a != b;\n";

    /*print_listing(code);*/

    r = ez_create_object(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "x", &x);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_get_member(&root, "y", &y);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_get_member(&root, "z", &z);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_boolean(&x, &value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(1 == value);

    r = ez_get_boolean(&y, &value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(0 == value);

    r = ez_get_boolean(&z, &value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(0 == value);

    r = ez_release_value(&x);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&y);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}
