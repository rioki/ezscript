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