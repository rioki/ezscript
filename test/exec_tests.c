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

#include "math.h"
#include "ezscript.h"
#include "test.h"

int test_exec_empty()
{
    ez_result_t r;
    ez_value_t  root;    
    
    r = ez_create_object(&root);

    r = ez_eval(&root, "");
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_exec_assign_int()
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  a;
    long        a_value;
    
    r = ez_create_object(&root);

    r = ez_eval(&root, "a = 1984;");
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&root, "a", &a);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_integer(&a, &a_value);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(a_value == 1984);

    r = ez_release_value(&a);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_exec_addition_int()
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
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&root, "c", &c);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_integer(&c, &c_value);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(c_value == 3);

    r = ez_release_value(&c);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_exec_addition_real()
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
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&root, "c", &c);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_real(&c, &c_value);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(fabs(c_value - 3.3) < 1e-5);

    r = ez_release_value(&c);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_exec_addition_real_int()
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
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&root, "c", &c);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_real(&c, &c_value);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(fabs(c_value - 3.1) < 1e-5);

    r = ez_release_value(&c);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_exec_addition_int_real()
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
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&root, "c", &c);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_real(&c, &c_value);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(fabs(c_value - 3.2) < 1e-5);

    r = ez_release_value(&c);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_exec_assign_reference()
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  b;
    long        b_value;
    const char code[] = "a = 19840920;\n"
                        "b = a;\n";
    
    r = ez_create_object(&root);

    r = ez_eval(&root, code);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&root, "b", &b);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_integer(&b, &b_value);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(b_value == 19840920);

    r = ez_release_value(&b);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}


int test_exec_division()
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
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&root, "c", &c);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_real(&c, &c_value);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(fabs(c_value - 4.0) < 1e-5);

    r = ez_release_value(&c);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}


int test_exec_subraction()
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
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&root, "c", &c);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_real(&c, &c_value);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(fabs(c_value - 9.0) < 1e-5);

    r = ez_release_value(&c);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

int test_exec_mixed()
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
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_member(&root, "d", &d);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_get_real(&d, &d_value);
    TEST_ASSERT(r == EZ_SUCCESS);
    TEST_ASSERT(fabs(d_value - 3.0) < 1e-5);

    r = ez_release_value(&d);
    TEST_ASSERT(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    TEST_ASSERT(r == EZ_SUCCESS);

    return 0;
}

void run_exec_tests(int* num_tests, int* num_errors)
{
    TEST_RUN(test_exec_empty);
    TEST_RUN(test_exec_assign_int);
    TEST_RUN(test_exec_addition_int);
    TEST_RUN(test_exec_addition_real);
    TEST_RUN(test_exec_addition_real_int);
    TEST_RUN(test_exec_addition_int_real);
    TEST_RUN(test_exec_assign_reference);
    TEST_RUN(test_exec_division);
    TEST_RUN(test_exec_subraction);
    TEST_RUN(test_exec_mixed);
}
