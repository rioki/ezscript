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

#include "math.h"
#include "ezscript.h"

TEST(C_API, test_exec_empty)
{
    ez_result_t r;
    ez_value_t  root;    
    
    r = ez_create_object(&root);

    r = ez_eval(&root, "");
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_exec_assign_int)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  a;
    long        a_value;
    
    r = ez_create_object(&root);

    r = ez_eval(&root, "a = 1984;");
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "a", &a);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_integer(&a, &a_value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(a_value == 1984);

    r = ez_release_value(&a);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_exec_addition_int)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  c;
    long        c_value;
    const char code[] = "a = 1;\n"
                        "b = 2;\n"
                        "c = a + b;\n";
    
    r = ez_create_object(&root);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "c", &c);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_integer(&c, &c_value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(c_value == 3);

    r = ez_release_value(&c);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_exec_addition_real)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  c;
    double      c_value;
    const char code[] = "a = 1.1;\n"
                        "b = 2.2;\n"
                        "c = a + b;\n";
    
    r = ez_create_object(&root);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "c", &c);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_real(&c, &c_value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(fabs(c_value - 3.3) < 1e-5);

    r = ez_release_value(&c);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_exec_addition_real_int)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  c;
    double      c_value;
    const char code[] = "a = 1.1;\n"
                        "b = 2;\n"
                        "c = a + b;\n";
    
    r = ez_create_object(&root);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "c", &c);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_real(&c, &c_value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(fabs(c_value - 3.1) < 1e-5);

    r = ez_release_value(&c);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_exec_addition_int_real)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  c;
    double      c_value;
    const char code[] = "a = 1;\n"
                        "b = 2.2;\n"
                        "c = a + b;\n";
    
    r = ez_create_object(&root);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "c", &c);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_real(&c, &c_value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(fabs(c_value - 3.2) < 1e-5);

    r = ez_release_value(&c);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_exec_assign_reference)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  b;
    long        b_value;
    const char code[] = "a = 19840920;\n"
                        "b = a;\n";
    
    r = ez_create_object(&root);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "b", &b);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_integer(&b, &b_value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(b_value == 19840920);

    r = ez_release_value(&b);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}


TEST(C_API, test_exec_division)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  c;
    double      c_value;
    const char code[] = "a = 12.0;\n"
                        "b = 3;\n"
                        "c = a / b;\n";
    
    r = ez_create_object(&root);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "c", &c);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_real(&c, &c_value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(fabs(c_value - 4.0) < 1e-5);

    r = ez_release_value(&c);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}


TEST(C_API, test_exec_subraction)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  c;
    double      c_value;
    const char code[] = "a = 12.0;\n"
                        "b = 3;\n"
                        "c = a - b;\n";
    
    r = ez_create_object(&root);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "c", &c);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_real(&c, &c_value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(fabs(c_value - 9.0) < 1e-5);

    r = ez_release_value(&c);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_exec_mixed)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  d;
    double      d_value;
    const char code[] = "a = 12.0;\n"
                        "b = 3;\n"
                        "c = 3;\n"
                        "d = (a - b) / 3;\n";

    r = ez_create_object(&root);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "d", &d);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_real(&d, &d_value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(fabs(d_value - 3.0) < 1e-5);

    r = ez_release_value(&d);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_boolean_values)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  a, b;
    int         value;
    const char code[] = "a = true;\n"
                        "b = false;\n";

    r = ez_create_object(&root);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "a", &a);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_get_member(&root, "b", &b);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_boolean(&a, &value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(1 == value);

    r = ez_get_boolean(&b, &value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(0 == value);

    r = ez_release_value(&a);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&b);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}
