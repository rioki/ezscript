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

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "ezscript.h"
#include "ezlexer.h"
#include "ezparser.h"
#include "interpreter.h"
#include "dbg.h"
#include "code.h"

ez_result_t ez_generate_expression(ez_code_t* code, size_t *ip, ast_node_t* node);

ez_result_t ez_generate_literal(ez_code_t* code, size_t *ip, ast_node_t* node)
{
    ez_result_t r = EZ_SUCCESS;

    EZ_CHECK_ARGUMENT(code != NULL);
    EZ_CHECK_ARGUMENT(ip != NULL);
    EZ_CHECK_ARGUMENT(node != NULL);

    switch (node->type)
    {
        case AST_LITERAL_NULL:
            r = ez_code_op_write(code, ip, OP_LTN);
            if (r < 0)
            {
                EZ_TRACEV("Failed to write OP: %s", ez_result_to_string(r));
                return r;
            }
            break;
        case AST_LITERAL_INTEGER:
            r = ez_code_op_write(code, ip, OP_LTI);
            if (r < 0)
            {
                return r;
            }
            return ez_code_int32_write(code, ip, atoi(node->svalue));
        case AST_LITERAL_REAL:
            r = ez_code_op_write(code, ip, OP_LTR);
            if (r < 0)
            {
                return r;
            }
            return ez_code_double_write(code, ip, atof(node->svalue));
        case AST_LITERAL_STRING:
            r = ez_code_op_write(code, ip, OP_LTS);
            if (r < 0)
            {
                return r;
            }
            return ez_code_string_write(code, ip, node->svalue);
        case AST_LITERAL_BOOLEAN:
            r = ez_code_op_write(code, ip, OP_LTB);
            EZ_CHECK_RESULT(r);
            r = ez_code_uint8_write(code, ip, strcmp(node->svalue, "true") == 0);
            EZ_CHECK_RESULT(r);
            break;
        default:
            EZ_TRACEV("Unknown AST node: %d", node->type);
            return EZ_INVALID_TYPE;
    }

    return EZ_SUCCESS;
}

ez_result_t ez_generate_load_reference(ez_code_t* code, size_t *ip, ast_node_t* node)
{
    ez_result_t r = EZ_SUCCESS;
    
    EZ_CHECK_ARGUMENT(code != NULL);
    EZ_CHECK_ARGUMENT(ip != NULL);
    EZ_CHECK_ARGUMENT(node != NULL);
    EZ_CHECK_ARGUMENT(node->svalue != NULL);

    r = ez_code_op_write(code, ip, OP_LOD);
    if (r < 0)
    {
        EZ_TRACEV("Failed to write OP: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_code_string_write(code, ip, node->svalue);
    if (r < 0)
    {
        EZ_TRACEV("Failed to write string: %s", ez_result_to_string(r));
        return r;
    }

    ast_node_t* member = node->child;
    while (member != NULL)
    {
        r = ez_code_op_write(code, ip, OP_LMB);
        if (r < 0)
        {
            EZ_TRACEV("Failed to write OP: %s", ez_result_to_string(r));
            return r;
        }

        r = ez_code_string_write(code, ip, member->svalue);
        if (r < 0)
        {
            EZ_TRACEV("Failed to write string: %s", ez_result_to_string(r));
            return r;
        }

        member = member->child;
    }

    return EZ_SUCCESS;
}

ez_result_t ez_generate_store_reference(ez_code_t* code, size_t *ip, ast_node_t* node)
{
    ez_result_t r;
    ast_node_t* member;

    member = node->child;
    if (member != NULL)
    {
        r = ez_code_op_write(code, ip, OP_LOD);
        if (r < 0)
        {
            EZ_TRACEV("Failed to write OP: %s", ez_result_to_string(r));
            return r;
        }

        r = ez_code_string_write(code, ip, node->svalue);
        if (r < 0)
        {
            EZ_TRACEV("Failed to write string: %s", ez_result_to_string(r));
            return r;
        }

        while (member != NULL)
        {
            if (member->next == NULL) /* last member */
            {
                r = ez_code_op_write(code, ip, OP_SMB);
                if (r < 0)
                {
                    EZ_TRACEV("Failed to write OP: %s", ez_result_to_string(r));
                    return r;
                }
            }
            else
            {
                r = ez_code_op_write(code, ip, OP_LMB);
                if (r < 0)
                {
                    EZ_TRACEV("Failed to write OP: %s", ez_result_to_string(r));
                    return r;
                }
            }

            r = ez_code_string_write(code, ip, member->svalue);
            if (r < 0)
            {
                EZ_TRACEV("Failed to write string: %s", ez_result_to_string(r));
                return r;
            }

            member = member->next;
        }
    }
    else
    {
        r = ez_code_op_write(code, ip, OP_STO);
        if (r < 0)
        {
            EZ_TRACEV("Failed to write OP: %s", ez_result_to_string(r));
            return r;
        }

        r = ez_code_string_write(code, ip, node->svalue);
        if (r < 0)
        {
            EZ_TRACEV("Failed to write string: %s", ez_result_to_string(r));
            return r;
        }
    }

    return EZ_SUCCESS;
}

ez_result_t ez_generate_operation(ez_code_t* code, size_t *ip, ast_node_t* node)
{
    ez_result_t r = EZ_SUCCESS;
    ast_node_t* lhs;
    ast_node_t* rhs;

    EZ_CHECK_ARGUMENT(code);
    EZ_CHECK_ARGUMENT(ip);
    EZ_CHECK_ARGUMENT(node);

    lhs = node->child;
    r = ez_generate_expression(code, ip, lhs);
    EZ_CHECK_RESULT(r);

    rhs = lhs->next;
    r = ez_generate_expression(code, ip, rhs);
    EZ_CHECK_RESULT(r);

    switch (node->type)
    {
        case AST_EQUALS:
            r = ez_code_op_write(code, ip, OP_EQU);
            EZ_CHECK_RESULT(r);
            break;
        case AST_NOT_EQUALS:
            r = ez_code_op_write(code, ip, OP_NEQ);
            EZ_CHECK_RESULT(r);
            break;
        case AST_ADDITION:
            r = ez_code_op_write(code, ip, OP_ADD);
            EZ_CHECK_RESULT(r);
            break;
        case AST_SUBTRACTION:
            r = ez_code_op_write(code, ip, OP_SUB);
            EZ_CHECK_RESULT(r);
            break;
        case AST_MULTIPLICATION:
            r = ez_code_op_write(code, ip, OP_MUL);
            EZ_CHECK_RESULT(r);
            break;
        case AST_DIVISION:
            r = ez_code_op_write(code, ip, OP_DIV);
            EZ_CHECK_RESULT(r);
            break;
        case AST_MODULO:
            r = ez_code_op_write(code, ip, OP_MOD);
            EZ_CHECK_RESULT(r);
            break;
        default:
            EZ_TRACEV("Unknown AST node: %d", node->type);
            return EZ_INVALID_TYPE;
    }

    return EZ_SUCCESS;
}

ez_result_t ez_generate_array(ez_code_t* code, size_t *ip, ast_node_t* node)
{
    ez_result_t r;
    
    EZ_CHECK_ARGUMENT(code != NULL);
    EZ_CHECK_ARGUMENT(ip != NULL);
    EZ_CHECK_ARGUMENT(node != NULL);

    r = ez_code_op_write(code, ip, OP_ARR);
    EZ_CHECK_RESULT(r);

    return EZ_SUCCESS;
}

ez_result_t ez_generate_object(ez_code_t* code, size_t *ip, ast_node_t* node)
{
    ez_result_t r;
    
    EZ_CHECK_ARGUMENT(code != NULL);
    EZ_CHECK_ARGUMENT(ip != NULL);
    EZ_CHECK_ARGUMENT(node != NULL);

    r = ez_code_op_write(code, ip, OP_OBJ);
    if (r < 0)
    {
        EZ_TRACEV("Failed to write OP: %s", ez_result_to_string(r));
        return r;
    }
    
    ast_node_t* member = node->child;
    while (member != NULL)
    {
        ast_node_t* expr = member->child;
        const char* id   = member->svalue;
        EZ_ASSERT(expr != NULL);

        r = ez_generate_expression(code, ip, expr);
        if (r < 0)
        {
            EZ_TRACEV("Fail to generate expression: %s", ez_result_to_string(r)); 
            return r;
        }

        r = ez_code_op_write(code, ip, OP_DMB);
        if (r < 0)
        {
            EZ_TRACEV("Failed to write OP: %s", ez_result_to_string(r));
            return r;
        }

        r = ez_code_string_write(code, ip, id);
        if (r < 0)
        {
            EZ_TRACEV("Failed to write string: %s", ez_result_to_string(r));
            return r;
        }

        member = member->next;
    }

    return EZ_SUCCESS;
}

ez_result_t ez_generate_expression(ez_code_t* code, size_t *ip, ast_node_t* node)
{
    ez_result_t r = EZ_SUCCESS;

    EZ_CHECK_ARGUMENT(code != NULL);
    EZ_CHECK_ARGUMENT(ip != NULL);
    EZ_CHECK_ARGUMENT(node != NULL);

    switch (node->type)
    {
        case AST_LITERAL_NULL:
        case AST_LITERAL_BOOLEAN:
        case AST_LITERAL_INTEGER:
        case AST_LITERAL_REAL:
        case AST_LITERAL_STRING:
            r = ez_generate_literal(code, ip, node);
            EZ_CHECK_RESULT(r);
            break;
        case AST_EQUALS:
        case AST_NOT_EQUALS:
        case AST_LESS:
        case AST_LESS_EQUAL:
        case AST_GRATER:
        case AST_GRATER_EQUAL:
        case AST_ADDITION:
        case AST_SUBTRACTION:
        case AST_MULTIPLICATION:
        case AST_DIVISION:
        case AST_MODULO:
            r = ez_generate_operation(code, ip, node);
            EZ_CHECK_RESULT(r);
            break;
        case AST_REFERENCE:
            r = ez_generate_load_reference(code, ip, node);
            EZ_CHECK_RESULT(r);
            break;
        case AST_ARRAY:
            r = ez_generate_array(code, ip, node);
            EZ_CHECK_RESULT(r);
            break;
        case AST_OBJECT:
            r = ez_generate_object(code, ip, node);
            EZ_CHECK_RESULT(r);
            break;
        default:
            EZ_TRACEV("Unknown AST node: %d", node->type);
            return EZ_INVALID_TYPE;
    }

    return EZ_SUCCESS;
}

ez_result_t ez_generate_assignment(ez_code_t* code, size_t *ip, ast_node_t* node)
{
    ez_result_t r = EZ_SUCCESS;
    ast_node_t* reference;
    ast_node_t* expression;
    
    assert(code != NULL);
    assert(ip != NULL);
    assert(node != NULL);

    reference = node->child;
    assert(reference != NULL);
    assert(reference->svalue != NULL);
    
    expression = reference->next;
    assert(expression != NULL);

    r = ez_generate_expression(code, ip, expression);
    EZ_CHECK_RESULT(r);
    
    r = ez_generate_store_reference(code, ip, reference);
    EZ_CHECK_RESULT(r);

    return EZ_SUCCESS;
}

ez_result_t ez_generate_node(ez_code_t* code, size_t *ip, ast_node_t* node)
{
    assert(code != NULL);
    assert(node != NULL);

    switch (node->type)
    {
        case AST_NULL:
            return EZ_SUCCESS;
        case AST_ASSIGNMENT:
        case AST_VARDECL:
            return ez_generate_assignment(code, ip, node);
        default:
            assert(0);
            return EZ_INVALID_TYPE;
    }
}

ez_result_t ez_generate(ez_value_t* function, ast_node_t* root)
{
    ez_result_t r    = EZ_SUCCESS;
    ez_code_t*  code = NULL;
    size_t      ip   = 0;

    code = (ez_code_t*)malloc(sizeof(ez_code_t));
    r = ez_init_code(code);
    if (r < 0)
    {
        free(code);
        return r;
    }

    ast_node_t* node = root;
    while (node != NULL)
    {
        r = ez_generate_node(code, &ip, node);
        if (r < 0)
        {
            free(code);
            return r;
        }
        node = node->next;
    }

    r = ez_code_op_write(code, &ip, OP_RET);
    if (r < 0)
    {
        free(code);
        return r;
    }

    /*ez_print_code(code);*/

    return ez_wrap_code(function, code);
}

ez_result_t ez_compile(ez_value_t* function, const char* code)
{
    ez_result_t     r;
    int             result;
    YY_BUFFER_STATE buffer;
    ast_node_t*     root;

    buffer = ez_scan_string(code);
    
    result = ezparse(&root);
    
    ez_delete_buffer(buffer);

    switch (result)
    {
        case 0:
            /* TODO semantic anasysis and optimisation */
            r = ez_generate(function, root); 
            ast_free(root);
            break;
        case 2:
            r = EZ_OUT_OF_MEMORY;
            EZ_TRACE("Out of Memory");
            break;
        case 1:
        default:
            r = EZ_PARSE_ERROR;
            EZ_TRACE("Parse Error");
            break;
    }

    return r;
}
