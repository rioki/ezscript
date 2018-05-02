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
#include <stdio.h>

#include "interpreter.h"
#include "dbg.h"
#include "code.h"
#include "stack.h"

ez_result_t exec_ltn(ez_code_t* code, ez_stack_t* stack, size_t* ip, ez_value_t* this)
{
    ez_result_t r;
    ez_value_t  value;

    r = ez_create_null(&value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to create null value: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_push_stack(stack, &value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to push stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release value: %s", ez_result_to_string(r));
        return r;
    }

    return EZ_SUCCESS;
}

ez_result_t exec_lti(ez_code_t* code, ez_stack_t* stack, size_t* ip, ez_value_t* this)
{
    ez_result_t r;
    int32_t     literal;
    ez_value_t  value;

    r = ez_code_int32_read(code, ip, &literal);
    if (r < 0)
    {
        EZ_TRACEV("Failed to read integer: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_create_integer(&value, literal);
    if (r < 0)
    {
        EZ_TRACEV("Failed to create integer value: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_push_stack(stack, &value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to push stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release value: %s", ez_result_to_string(r));
        return r;
    }

    return EZ_SUCCESS;
}

ez_result_t exec_ltr(ez_code_t* code, ez_stack_t* stack, size_t* ip, ez_value_t* this)
{
    ez_result_t r;
    double      literal;
    ez_value_t  value;

    r = ez_code_double_read(code, ip, &literal);
    if (r < 0)
    {
        EZ_TRACEV("Failed to read real: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_create_real(&value, literal);
    if (r < 0)
    {
        EZ_TRACEV("Failed to create real value: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_push_stack(stack, &value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to push stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release value: %s", ez_result_to_string(r));
        return r;
    }

    return EZ_SUCCESS;
}

ez_result_t exec_obj(ez_code_t* code, ez_stack_t* stack, size_t* ip, ez_value_t* this)
{
    ez_result_t r;
    ez_value_t  value;

    r = ez_create_object(&value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to create object: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_push_stack(stack, &value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to push stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release value: %s", ez_result_to_string(r));
        return r;
    }

    return EZ_SUCCESS;
}

ez_result_t exec_lts(ez_code_t* code, ez_stack_t* stack, size_t* ip, ez_value_t* this)
{
    /* TODO implement string class */
    return EZ_INVALID_OP;
}

ez_result_t exec_sto(ez_code_t* code, ez_stack_t* stack, size_t* ip, ez_value_t* this)
{
    ez_result_t r;
    const char* id;
    ez_value_t  value;

    r = ez_code_string_read(code, ip, &id);
    if (r < 0)
    {
        EZ_TRACEV("Failed to read string: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_pop_stack(stack, &value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to pop stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_set_member(this, id, &value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to set member: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release value: %s", ez_result_to_string(r));
        return r;
    }

    return EZ_SUCCESS;
}

ez_result_t exec_lod(ez_code_t* code, ez_stack_t* stack, size_t* ip, ez_value_t* this)
{
    ez_result_t r;
    const char* id;
    ez_value_t  value;

    r = ez_code_string_read(code, ip, &id);
    if (r < 0)
    {
        EZ_TRACEV("Failed to read string: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_get_member(this, id, &value);
    if (r < 0)
    {
        EZ_TRACEV("Faild to read %s from root: %s", id, ez_result_to_string(r));
        return r;
    }

    r = ez_push_stack(stack, &value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to push stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release value: %s", ez_result_to_string(r));
        return r;
    }

    return EZ_SUCCESS;
}

ez_result_t exec_dmb(ez_code_t* code, ez_stack_t* stack, size_t* ip)
{
    ez_result_t r;
    const char* id;
    ez_value_t  value;
    ez_value_t  object;

    r = ez_code_string_read(code, ip, &id);
    if (r < 0)
    {
        EZ_TRACEV("Failed to read string: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_pop_stack(stack, &value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to pop stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_stack_top(stack, &object);
    if (r < 0)
    {
        EZ_TRACEV("Failed to read stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_set_member(&object, id, &value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to set member: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release value: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&object);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release object: %s", ez_result_to_string(r));
        return r;
    }

    return EZ_SUCCESS;
}


ez_result_t exec_smb(ez_code_t* code, ez_stack_t* stack, size_t* ip)
{
    ez_result_t r;
    const char* id;
    ez_value_t  value;
    ez_value_t  object;

    r = ez_code_string_read(code, ip, &id);
    if (r < 0)
    {
        EZ_TRACEV("Failed to read string: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_pop_stack(stack, &object);
    if (r < 0)
    {
        EZ_TRACEV("Failed to read stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_pop_stack(stack, &value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to pop stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_set_member(&object, id, &value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to set member: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release value: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&object);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release object: %s", ez_result_to_string(r));
        return r;
    }

    return EZ_SUCCESS;
}

ez_result_t exec_lmb(ez_code_t* code, ez_stack_t* stack, size_t* ip)
{
    ez_result_t r;
    const char* id;
    ez_value_t  value;
    ez_value_t  object;

    r = ez_code_string_read(code, ip, &id);
    if (r < 0)
    {
        EZ_TRACEV("Failed to read string: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_pop_stack(stack, &object);
    if (r < 0)
    {
        EZ_TRACEV("Failed to read stack: %s", ez_result_to_string(r));
        return r;
    }
    
    r = ez_get_member(&object, id, &value);
    if (r < 0)
    {
        EZ_TRACEV("Faild to read %s from root: %s", id, ez_result_to_string(r));
        return r;
    }

    r = ez_push_stack(stack, &value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to push stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&value);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release value: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&object);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release object: %s", ez_result_to_string(r));
        return r;
    }

    return EZ_SUCCESS;
}

ez_result_t exec_binop(ez_op_t op, ez_stack_t* stack, ez_value_t* this)
{
    ez_result_t r;
    ez_value_t  rhs;
    ez_value_t  lhs;
    ez_value_t  res;

    r = ez_pop_stack(stack, &rhs);
    if (r < 0)
    {
        EZ_TRACEV("Failed to pop stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_pop_stack(stack, &lhs);
    if (r < 0)
    {
        EZ_TRACEV("Failed to pop stack: %s", ez_result_to_string(r));
        return r;
    }

    if (lhs.type == EZ_TYPE_OBJECT)
    {
        ez_value_t  fun;
        const char* name;
        switch (op)
        {
            case OP_ADD:
                name = "add";
                break;
            case OP_SUB:
                name = "substract";
                break;
            case OP_MUL:
                name = "multiply";
                break;
            case OP_DIV:
                name = "divide";
                break;
            case OP_MOD:
                name = "module";
                break;
            default:
                EZ_TRACE("This can not happen.");
                return EZ_INVALID_OP;
        }

        r = ez_get_member(&rhs, name, &fun);
        if (r < 0)
        {
            EZ_TRACEV("Failed to read member %s: %s", name, ez_result_to_string(r));
            return r;
        }

        if (fun.type != EZ_TYPE_FUNCTION)
        {
            EZ_TRACEV("%s is not a function.", name);
            return EZ_RUNTIME_ERRPOR;
        }

        r = ez_call_function(&fun, this, &res, 1, &lhs);
        if (r < 0)
        {
            EZ_TRACEV("Call to %s failed: %s", name, ez_result_to_string(r));
            return r;
        }
    }
    else if (lhs.type == EZ_TYPE_INTEGER || lhs.type == EZ_TYPE_REAL)
    {
        long lhsi, rhsi;
        double  lhsr, rhsr;

        if (lhs.type == EZ_TYPE_INTEGER)
        {
            r = ez_get_integer(&lhs, &lhsi);
            if (r < 0)
            {
                EZ_TRACEV("Failed to read integer value: %s", ez_result_to_string(r));
                return r;
            }
        }
        else if (lhs.type == EZ_TYPE_REAL)
        {
            r = ez_get_real(&lhs, &lhsr);
            if (r < 0)
            {
                EZ_TRACEV("Failed to read real value: %s", ez_result_to_string(r));
                return r;
            }
        }
        else
        {
            EZ_TRACE("This can not happen.");
            return EZ_INVALID_OP;
        }

        if (rhs.type == EZ_TYPE_INTEGER)
        {
            r = ez_get_integer(&rhs, &rhsi);
            if (r < 0)
            {
                EZ_TRACEV("Failed to read integer value: %s", ez_result_to_string(r));
                return r;
            }
        }
        else if (rhs.type == EZ_TYPE_REAL)
        {
            r = ez_get_real(&rhs, &rhsr);
            if (r < 0)
            {
                EZ_TRACEV("Failed to read real value: %s", ez_result_to_string(r));
                return r;
            }
        }
        else
        {
            EZ_TRACE("rhs is not integer or real.");
            return EZ_RUNTIME_ERRPOR;
        }

        if (lhs.type == EZ_TYPE_INTEGER && rhs.type == EZ_TYPE_INTEGER)
        {
            int32_t result;
            switch (op)
            {
                case OP_ADD:
                    result = lhsi + rhsi;
                    break;
                case OP_SUB:
                    result = lhsi - rhsi;
                    break;
                case OP_MUL:
                    result = lhsi * rhsi;
                    break;
                case OP_DIV:
                    result = lhsi / rhsi;
                    break;
                case OP_MOD:
                    result = lhsi % rhsi;
                    break;
                default:
                    EZ_TRACE("This can not happen.");
                    return EZ_INVALID_OP;
            }

            r = ez_create_integer(&res, result);
            if (r < 0)
            {
                EZ_TRACEV("Failed to create integer: %s", ez_result_to_string(r));
                return r;
            }
        }
        else
        {
            double result;

            if (lhs.type == EZ_TYPE_INTEGER)
            {
                lhsr = (double)lhsi;
            }
            if (rhs.type == EZ_TYPE_INTEGER)
            {
                rhsr = (double)rhsi;
            }
            
            switch (op)
            {
                case OP_ADD:
                    result = lhsr + rhsr;
                    break;
                case OP_SUB:
                    result = lhsr - rhsr;
                    break;
                case OP_MUL:
                    result = lhsr * rhsr;
                    break;
                case OP_DIV:
                    result = lhsr / rhsr;
                    break;
                case OP_MOD:
                    EZ_TRACE("Modulo not defined for real.");
                    return EZ_RUNTIME_ERRPOR;
                default:
                    EZ_TRACE("This can not happen.");
                    return EZ_INVALID_OP;
            }

            r = ez_create_real(&res, result);
            if (r < 0)
            {
                EZ_TRACEV("Failed to create realmake : %s", ez_result_to_string(r));
                return r;
            }
        }
    }
    else
    {
        EZ_TRACE("lhs is not integer, real or object.");
        return EZ_RUNTIME_ERRPOR;
    }
    
    r = ez_push_stack(stack, &res);
    if (r < 0)
    {
        EZ_TRACEV("Failed to push stack: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&lhs);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release lhs: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&rhs);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release rhs: %s", ez_result_to_string(r));
        return r;
    }

    r = ez_release_value(&res);
    if (r < 0)
    {
        EZ_TRACEV("Failed to release res: %s", ez_result_to_string(r));
        return r;
    }

    return EZ_SUCCESS;
}

ez_result_t ez_exec_code(ez_value_t* this, ez_code_t* code)
{
    ez_result_t r    = EZ_SUCCESS;
    size_t      ip   = 0;
    ez_op_t     op   = OP_NOP;
    ez_stack_t  stack;
    int         running = 1;

    EZ_CHECK_ARGUMENT(this != NULL);
    EZ_CHECK_ARGUMENT(code != NULL);

    r = ez_allocate_stack(&stack, 16);
    if (r < 0)
    {
        EZ_TRACEV("Failed to allocate stack: %s", ez_result_to_string(r));
        return r;
    }

    while (running)
    {
        r = ez_code_op_read(code, &ip, &op);
        if (r < 0)
        {
            EZ_TRACEV("Failed to read opcode: %s", ez_result_to_string(r));
            return r;
        }

        switch (op)
        {
            case OP_NOP:
                /* nothing */
                break;
            case OP_RET:
                running = 0;
                break;
            case OP_LTN:
                r = exec_ltn(code, &stack, &ip, this);
                break;
            case OP_LTI:
                r = exec_lti(code, &stack, &ip, this);
                break;
            case OP_LTR:
                r = exec_ltr(code, &stack, &ip, this);
                break;
            case OP_LTS:
                r = exec_lts(code, &stack, &ip, this);
                break;
            case OP_OBJ:
                r = exec_obj(code, &stack, &ip, this);
                break;
            case OP_STO:
                r = exec_sto(code, &stack, &ip, this);
                break;
            case OP_LOD:
                r = exec_lod(code, &stack, &ip, this);
                break;
            case OP_DMB:
                r = exec_dmb(code, &stack, &ip);
                break;
            case OP_SMB:
                r = exec_smb(code, &stack, &ip);
                break;
            case OP_LMB:
                r = exec_lmb(code, &stack, &ip);
                break;
            case OP_ADD:
            case OP_SUB:
            case OP_MUL:
            case OP_DIV:
            case OP_MOD:
                r = exec_binop(op, &stack, this);
                break;   
            default:
                EZ_TRACEV("Unknown opcode: %d", op);
                running = 0;
                break;
        }

        if (r < 0)
        {
            running = 0;
        } 
    }

    ez_free_stack(&stack); 

    return r;
}

ez_result_t ez_eval(ez_value_t* root, const char* code)
{
    ez_result_t r = EZ_SUCCESS;    
    ez_value_t function;    

    r = ez_compile(&function, code);
    if (r < 0) 
    {
        EZ_TRACE("Failed to compile code.");
        return r;
    }

    r = ez_call_function(&function, root, NULL, 0, NULL);
    if (r < 0) 
    {
        EZ_TRACEV("Failed to execute code: %s", ez_result_to_string(r));
    }
        
    ez_release_value(&function);
    return r;
}
