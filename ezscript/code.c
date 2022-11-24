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

#include "string.h"

#include "code.h"
#include "dbg.h"

const size_t BLOCK_SIZE = 128;

ez_result_t ez_init_code(ez_code_t* code) 
{
    if (code == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    code->size = BLOCK_SIZE;
    code->code = (uint8_t*)malloc(code->size);

    if (code->code == NULL)
    {
        return EZ_OUT_OF_MEMORY;
    }

    memset(code->code, 0, code->size);
    
    return EZ_SUCCESS;
}

ez_result_t ez_grow_code(ez_code_t* code) 
{
    if (code == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    code->code = (uint8_t*)realloc(code->code, code->size + BLOCK_SIZE);

    if (code->code == NULL)
    {
        return EZ_OUT_OF_MEMORY;
    }

    memset(code->code + code->size, 0, BLOCK_SIZE);
    code->size += BLOCK_SIZE;

    return EZ_SUCCESS;
}

ez_result_t ez_code_op_write(ez_code_t* code, size_t* ip, ez_op_t value)
{
    ez_result_t r = EZ_SUCCESS;

    if (code == NULL || ip == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if ((*ip + sizeof(ez_op_t)) > code->size)
    {
        r = ez_grow_code(code);
        if (r < 0)
        {
            return r;
        }
    }

    memcpy(code->code + (*ip), &value, sizeof(ez_op_t));
    *ip += sizeof(ez_op_t);

    return r;
}

ez_result_t ez_code_int32_write(ez_code_t* code, size_t* ip, int32_t value)
{
    ez_result_t r = EZ_SUCCESS;

    if (code == NULL || ip == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if ((*ip + sizeof(int32_t)) > code->size)
    {
        r = ez_grow_code(code);
        if (r < 0)
        {
            return r;
        }
    }

    memcpy(code->code + (*ip), &value, sizeof(int32_t));
    *ip += sizeof(int32_t);

    return r;
}

ez_result_t ez_code_uint8_write(ez_code_t* code, size_t* ip, uint8_t value)
{
    ez_result_t r = EZ_SUCCESS;

    if (code == NULL || ip == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if ((*ip + sizeof(uint8_t)) > code->size)
    {
        r = ez_grow_code(code);
        if (r < 0)
        {
            return r;
        }
    }

    memcpy(code->code + (*ip), &value, sizeof(uint8_t));
    *ip += sizeof(uint8_t);

    return r;
}

ez_result_t ez_code_uint32_write(ez_code_t* code, size_t* ip, uint32_t value)
{
    ez_result_t r = EZ_SUCCESS;

    if (code == NULL || ip == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if ((*ip + sizeof(uint32_t)) > code->size)
    {
        r = ez_grow_code(code);
        if (r < 0)
        {
            return r;
        }
    }

    memcpy(code->code + (*ip), &value, sizeof(uint32_t));
    *ip += sizeof(uint32_t);

    return r;
}

ez_result_t ez_code_double_write(ez_code_t* code, size_t* ip, double value)
{
    ez_result_t r = EZ_SUCCESS;

    if (code == NULL || ip == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if ((*ip + sizeof(double)) > code->size)
    {
        r = ez_grow_code(code);
        if (r < 0)
        {
            return r;
        }
    }

    memcpy(code->code + (*ip), &value, sizeof(double));
    *ip += sizeof(double);

    return r;
}

ez_result_t ez_code_string_write(ez_code_t* code, size_t* ip, const char* value)
{
    ez_result_t r   = EZ_SUCCESS;
    uint32_t   len = 0;

    if (code == NULL || ip == NULL || value == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    len = strlen(value) + 1;

    r = ez_code_uint32_write(code, ip, len);
    if (r < 0)
    {
        return r;
    }

    while ((*ip + len) > code->size)
    {
        r = ez_grow_code(code);
        if (r < 0)
        {
            return r;
        }
    }

    memcpy(code->code + (*ip), value, len);
    *ip += len;

    return r;
}

ez_result_t ez_code_op_read(ez_code_t* code, size_t* ip, ez_op_t* value)
{
    ez_result_t r = EZ_SUCCESS;

    if (code == NULL || ip == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if ((*ip + sizeof(ez_op_t)) > code->size)
    {
        return EZ_OVERFLOW;
    }

    memcpy(value, code->code + (*ip), sizeof(ez_op_t));
    *ip += sizeof(ez_op_t);

    return r;
}

ez_result_t ez_code_uint8_read(ez_code_t* code, size_t* ip, uint8_t* value)
{
    ez_result_t r = EZ_SUCCESS;

    if (code == NULL || ip == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if ((*ip + sizeof(int8_t)) > code->size)
    {
        return EZ_OVERFLOW;
    }

    memcpy(value, code->code + (*ip), sizeof(int8_t));
    *ip += sizeof(int8_t);

    return r;
}

ez_result_t ez_code_int32_read(ez_code_t* code, size_t* ip, int32_t* value)
{
    ez_result_t r = EZ_SUCCESS;

    if (code == NULL || ip == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if ((*ip + sizeof(int32_t)) > code->size)
    {
        return EZ_OVERFLOW;
    }

    memcpy(value, code->code + (*ip), sizeof(int32_t));
    *ip += sizeof(int32_t);

    return r;
}

ez_result_t ez_code_uint32_read(ez_code_t* code, size_t* ip, uint32_t* value)
{
    ez_result_t r = EZ_SUCCESS;

    if (code == NULL || ip == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if ((*ip + sizeof(uint32_t)) > code->size)
    {
        return EZ_OVERFLOW;
    }

    memcpy(value, code->code + (*ip), sizeof(uint32_t));
    *ip += sizeof(uint32_t);

    return r;
}

ez_result_t ez_code_double_read(ez_code_t* code, size_t* ip, double* value)
{
    ez_result_t r = EZ_SUCCESS;

    if (code == NULL || ip == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    if ((*ip + sizeof(double)) > code->size)
    {
        return EZ_OVERFLOW;
    }

    memcpy(value, code->code + (*ip), sizeof(double));
    *ip += sizeof(double);

    return r;
}

ez_result_t ez_code_string_read(ez_code_t* code, size_t* ip, const char** value)
{
    uint32_t len = 0;

    ez_result_t r = EZ_SUCCESS;

    if (code == NULL || ip == NULL)
    {
        return EZ_INVALID_ARGUMENT;
    }

    r = ez_code_uint32_read(code, ip, &len);
    if (r < 0)
    {
        return r;
    }

    if ((*ip + len) >= code->size)
    {
        return EZ_OVERFLOW;
    }

    *value = (const char*)(code->code + *ip);
    *ip += len;


    return EZ_SUCCESS;
}

ez_result_t ez_print_code(FILE* fd, ez_code_t* code)
{
    size_t      ip   = 0;
    ez_op_t     op   = OP_NOP;
    ez_result_t r    = EZ_SUCCESS;
    const char* sval = NULL;
    int32_t     ival = 0;
    uint8_t     ui8val = 0;
    double      rval = 0;

    EZ_CHECK_ARGUMENT(code != NULL);

    while (r == EZ_SUCCESS)
    {
        r = ez_code_op_read(code, &ip, &op);
        if (r < 0)
        {
            if (r != EZ_OVERFLOW)
            {
                EZ_TRACEV("Failed to read opcode: %s", ez_result_to_string(r));
                return r;
            }
            return EZ_SUCCESS;
        }

        switch (op)
        {
            case OP_NOP:
                fprintf(fd, "  NOP\n");
                break;
            case OP_RET:
                fprintf(fd, "  RET\n");
                break;
            case OP_LTN:
                fprintf(fd, "  LTN\n");
                break;
            case OP_LTB:
                r = ez_code_uint8_read(code, &ip, &ui8val);
                EZ_ASSERT(r == EZ_SUCCESS);
                fprintf(fd, "  LTB %d\n", ui8val);
                break;
            case OP_LTI:
                r = ez_code_int32_read(code, &ip, &ival);
                EZ_ASSERT(r == EZ_SUCCESS);
                fprintf(fd, "  LTI %d\n", ival);
                break;
            case OP_LTR:
                r = ez_code_double_read(code, &ip, &rval);
                EZ_ASSERT(r == EZ_SUCCESS);
                fprintf(fd, "  LTR %f\n", rval);
                break;
            case OP_LTS:
                r = ez_code_string_read(code, &ip, &sval);
                EZ_ASSERT(r == EZ_SUCCESS);
                fprintf(fd, "  LTS %s\n", sval);
                break;
            case OP_OBJ:
                fprintf(fd, "  OBJ\n");
                break;
            case OP_STO:
                r = ez_code_string_read(code, &ip, &sval);
                EZ_ASSERT(r == EZ_SUCCESS);
                fprintf(fd, "  STO %s\n", sval);
                break;
            case OP_LOD:
                r = ez_code_string_read(code, &ip, &sval);
                EZ_ASSERT(r == EZ_SUCCESS);
                fprintf(fd, "  LOD %s\n", sval);
                break;
            case OP_DMB:
                r = ez_code_string_read(code, &ip, &sval);
                EZ_ASSERT(r == EZ_SUCCESS);
                fprintf(fd, "  DMB %s\n", sval);
                break;
            case OP_SMB:
                r = ez_code_string_read(code, &ip, &sval);
                EZ_ASSERT(r == EZ_SUCCESS);
                fprintf(fd, "  SMB %s\n", sval);
                break;
            case OP_LMB:
                r = ez_code_string_read(code, &ip, &sval);
                EZ_ASSERT(r == EZ_SUCCESS); 
                fprintf(fd, "  LMB %s\n", sval);
                break;
            case OP_EQU:
                fprintf(fd, "  EUQ\n");
                break;
            case OP_NEQ:
                fprintf(fd, "  NEQ\n");
                break;
            case OP_ADD:
                fprintf(fd, "  ADD\n");
                break;
            case OP_SUB:
                fprintf(fd, "  SUB\n");
                break;
            case OP_MUL:
                fprintf(fd, "  MUL\n");
                break;
            case OP_DIV:
                fprintf(fd, "  DIV\n");
                break;
            case OP_MOD:
                fprintf(fd, "  MOD\n");
                break;
            default:
                EZ_ASSERT(0);
                return EZ_INVALID_OP;
        }
    }

    return EZ_SUCCESS;
}