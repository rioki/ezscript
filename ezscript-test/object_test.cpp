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

TEST(C_API, test_create_object_null)
{
    ez_result_t r;

    r = ez_create_object(NULL);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_create_typed_object_null)
{
    ez_result_t r;

    r = ez_create_typed_object(NULL, "object");
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
}

TEST(C_API, test_get_member_null)
{
    ez_result_t r;
    ez_value_t  object;
    ez_value_t  value;
    
    r = ez_create_object(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(NULL, "moo", &value);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
    r = ez_get_member(&object, NULL, &value);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
    r = ez_get_member(&object, "moo", NULL);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
    
    r = ez_release_value(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_set_member_null)
{
    ez_result_t r;
    ez_value_t  object;
    ez_value_t  value;
    
    r = ez_create_object(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_create_null(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(NULL, "moo", &value);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
    r = ez_get_member(&object, NULL, &value);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
    r = ez_get_member(&object, "moo", NULL);
    ASSERT_TRUE(r == EZ_INVALID_ARGUMENT);
    
    r = ez_release_value(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_create_object)
{
    ez_result_t r;
    ez_value_t  value;
    ez_type_t   type;

    r = ez_create_object(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_type(&value, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(type == EZ_TYPE_OBJECT);
    
    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_create_typed_object)
{
    ez_result_t r;
    ez_value_t  value;
    const char* type;

    r = ez_create_typed_object(&value, "CoolObject");
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_object_type(&value, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    EXPECT_STREQ("CoolObject", type);
    
    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_create_object_is_type_object)
{
    ez_result_t r;
    ez_value_t  value;
    const char* type;

    r = ez_create_object(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_object_type(&value, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    EXPECT_STREQ("object", type);
    
    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_undefined_members)
{
    ez_result_t r;
    ez_value_t  object;
    ez_value_t  value;
    ez_type_t   type;
    
    r = ez_create_object(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&object, "moo", &value);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_type(&value, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(type == EZ_TYPE_UNDEFINED);
    
    r = ez_release_value(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_set_member)
{
    ez_result_t r;
    ez_value_t  object;
    ez_value_t  first;
    ez_value_t  second;
    long        ivalue;

    
    r = ez_create_object(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_create_integer(&first, 85);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_set_member(&object, "moo", &first);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&object, "moo", &second);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_integer(&second, &ivalue);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(ivalue == 85);
    
    r = ez_release_value(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&first);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&second);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_multiple_values)
{
    ez_result_t r;
    ez_value_t  object;
    ez_value_t  first;
    ez_value_t  second;
    long        ivalue;
    double      rvalue;
    
    r = ez_create_object(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_create_integer(&first, 85);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_set_member(&object, "a", &first);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&first);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_create_real(&first, 123.6);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_set_member(&object, "b", &first);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&first);
    ASSERT_TRUE(r == EZ_SUCCESS);
    


    r = ez_get_member(&object, "a", &second);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_get_integer(&second, &ivalue);
    ASSERT_TRUE(r == EZ_SUCCESS);    
    ASSERT_TRUE(ivalue == 85);
    r = ez_release_value(&second);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&object, "b", &second);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_get_real(&second, &rvalue);
    ASSERT_TRUE(r == EZ_SUCCESS);    
    ASSERT_TRUE(ivalue == 85);
    r = ez_release_value(&second);
    ASSERT_TRUE(r == EZ_SUCCESS);
    
    r = ez_release_value(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_override_values)
{
    ez_result_t r;
    ez_value_t  object;
    ez_value_t  value;
    double      rvalue;
    
    r = ez_create_object(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);

    // object.a = 85
    r = ez_create_integer(&value, 85);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_set_member(&object, "a", &value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);

    // object.a = 123.6
    r = ez_create_real(&value, 123.6);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_set_member(&object, "a", &value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);

    // 123.6 == object.a
    r = ez_get_member(&object, "a", &value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    r = ez_get_real(&value, &rvalue);
    ASSERT_TRUE(r == EZ_SUCCESS);    
    ASSERT_TRUE(rvalue == 123.6);
    r = ez_release_value(&value);
    ASSERT_TRUE(r == EZ_SUCCESS);
    
    r = ez_release_value(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_object_data)
{
    ez_result_t r;
    ez_value_t  object;
    int         some_data = 90;
    int*        pdata = NULL;
    
    r = ez_create_object(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_set_object_data(&object, &some_data);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_object_data(&object, (void**)&pdata);
    ASSERT_TRUE(r == EZ_SUCCESS);

    ASSERT_TRUE(*pdata == 90);
    ASSERT_TRUE(pdata == &some_data);

    r = ez_release_value(&object);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_empty_object)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  obj;
    ez_type_t   type;
    const char code[] = "obj = {};\n";
    
    r = ez_create_object(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "obj", &obj);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_type(&obj, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(type == EZ_TYPE_OBJECT);
    
    r = ez_release_value(&obj);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_object_from_code)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  obj;
    ez_type_t   type;
    const char code[] = "obj = {a: 1};\n";
    
    r = ez_create_object(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "obj", &obj);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_type(&obj, &type);
    ASSERT_TRUE(r == EZ_SUCCESS);
    ASSERT_TRUE(type == EZ_TYPE_OBJECT);
    
    r = ez_release_value(&obj);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_object_from_code2)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  obj;
    ez_value_t  a, b;
    long        av, bv;
    const char code[] = "obj = {a: 1, b: 2 + 3};\n";
    
    r = ez_create_object(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "obj", &obj);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&obj, "a", &a);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_integer(&a, &av);
    ASSERT_TRUE(r == EZ_SUCCESS);    
    ASSERT_TRUE(av == 1);

    r = ez_get_member(&obj, "b", &b);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_integer(&b, &bv);
    ASSERT_TRUE(r == EZ_SUCCESS);    
    ASSERT_TRUE(bv == 5);

    r = ez_release_value(&a);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&b);
    ASSERT_TRUE(r == EZ_SUCCESS);
    
    r = ez_release_value(&obj);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_read_member)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  yob;
    long        yobv;
    const char code[] = "var dob = {\n"
                        "  year: 1984,\n"
                        "  month: 9,\n"
                        "  day: 20\n"
                        "};\n"
                        "var yob = dob.year;\n";
    
    r = ez_create_object(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "yob", &yob);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_integer(&yob, &yobv);
    ASSERT_TRUE(r == EZ_SUCCESS);    
    ASSERT_TRUE(yobv == 1984);
    
    r = ez_release_value(&yob);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

void print_listing(const char* code)
{
    ez_value_t function;

    ez_compile(&function, code);

    ez_print_function_code(stdout, &function);
}

TEST(C_API, test_write_member)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t  dob;
    ez_value_t  dob_year;
    long        yobv;
    const char code[] = "dob = {\n"
                        "  year: 1984,\n"
                        "  month: 9,\n"
                        "  day: 20\n"
                        "};\n"
                        "dob.year = 1980;\n";

    r = ez_create_object(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "dob", &dob);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&dob, "year", &dob_year);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_integer(&dob_year, &yobv);
    ASSERT_TRUE(r == EZ_SUCCESS);    
    ASSERT_TRUE(yobv == 1980);
    
    r = ez_release_value(&dob);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&dob_year);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}

TEST(C_API, test_deep_nested)
{
    ez_result_t r;
    ez_value_t  root;
    ez_value_t message, to, name;
    const char* text;
    const char code[] = "message = {\n"
                        "  to: {\n"
                        "    name: \"Sean Farell\",\n"
                        "    email: \"sean.farrell@rioki.org\"\n"
                        "  },\n"
                        "  body: \"ezscript rocks!\""
                        "};\n"
                        "message.to.name = \"Sean Farrell\";\n";

    r = ez_create_object(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_eval(&root, code);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&root, "message", &message);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&message, "to", &to);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_member(&to, "name", &name);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_get_string(&name, &text);
    ASSERT_TRUE(r == EZ_SUCCESS);
    EXPECT_STREQ("Sean Farrell", text);

    r = ez_release_value(&name);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&to);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&message);
    ASSERT_TRUE(r == EZ_SUCCESS);

    r = ez_release_value(&root);
    ASSERT_TRUE(r == EZ_SUCCESS);
}
