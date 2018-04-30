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

#ifndef _CODE_H_
#define _CODE_H_

#include "stdlib.h"
#include "stdint.h"
#include "ezscript.h"

enum _ez_op 
{
    /* NOP - No Operation 
       Do nothing */
    OP_NOP,
    /* RET - RETURN
       Finish execution. */
    OP_RET,             
    /* LTN - Literal NULL 
       Creates a null value on the stack */
    OP_LTN,
    /* LTI <int32> - Literal Integer 
       Creates an integer value on the stack */
    OP_LTI,
    /* LTR <double> - Literal Real 
       Creates a real value on the stack */
    OP_LTR,
    /* LTS <string> - Literal String 
       Creates a string value on the stack */   
    OP_LTS,
    /* STO <string> - Store a Value
       Copies the value from the stack into the given variable. */
    OP_STO,
    /* LOD <string> - Load a Value
       Copies the given variable to the stack. */
    OP_LOD,
    /* ADD - Addition
       Adds the top and next value from the stack and write it back to top. */
    OP_ADD,
    /* SUB - Subtraction
       Subtracts the top and next value from the stack and write it back to top. */
    OP_SUB,
    /* MUL - Multiplication
       Multiplies the top and next value from the stack and write it back to top. */
    OP_MUL,
    /* DIV - Division
       Divides the top and next value from the stack and write it back to top. */
    OP_DIV,
    /* MOD - Modulo
       Modulos the top and next value from the stack and write it back to top. */
    OP_MOD
};
typedef enum _ez_op ez_op_t;

struct _ez_code
{
    size_t   size;
    uint8_t* code;
};
typedef struct _ez_code ez_code_t;

ez_result_t ez_init_code(ez_code_t* code);
ez_result_t ez_free_code(ez_code_t* code);

ez_result_t ez_code_op_write(ez_code_t* code, size_t* ip, ez_op_t value);
ez_result_t ez_code_int32_write(ez_code_t* code, size_t* ip, int32_t value);
ez_result_t ez_code_uint32_write(ez_code_t* code, size_t* ip, uint32_t value);
ez_result_t ez_code_double_write(ez_code_t* code, size_t* ip, double value);
ez_result_t ez_code_string_write(ez_code_t* code, size_t* ip, const char* value);

ez_result_t ez_code_op_read(ez_code_t* code, size_t* ip, ez_op_t* value);
ez_result_t ez_code_int32_read(ez_code_t* code, size_t* ip, int32_t* value);
ez_result_t ez_code_uint32_read(ez_code_t* code, size_t* ip, uint32_t* value);
ez_result_t ez_code_double_read(ez_code_t* code, size_t* ip, double* value);
ez_result_t ez_code_string_read(ez_code_t* code, size_t* ip, const char** value);

#endif
