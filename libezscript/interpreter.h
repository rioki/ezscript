/*
    ezscript
    Copyright (c) 2017 Sean Farrell <sean.farrell@rioki.org>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

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

#ifndef _EZ_INTERPRETER_H_
#define _EZ_INTERPRETER_H_

/**
 * The Operation Codes 
 **/
enum ez_opcode_e
{
    /**
     * Null Operation
     **/
    EZ_NOP,
    /**
     * Define Variable
     * 
     * @arg id the variable's identifier as string
     * 
     * Created variable with id in the global or local variable store with the
     * given id. 
     **/
    EZ_DEFVAR,
    /**
     * Load a Variable
     * 
     * @arg uchar the register to load the value to
     * @arg hash the variables identifier as hashed int
     * 
     * Loads the given variable to the given register. 
     **/
    EZ_LDVAR,
    /**
     * Store a Variable
     * 
     * @arg uchar the register to store the value from
     * @arg hash the variables identifier as hashed int
     * 
     * Stores the given variable value from the given register. 
     **/
    EZ_STOVAR,
    /**
     * Load a NULL Value
     * 
     * @arg uchar the register to load the value to
     * 
     * Sets a given register to NULL.
     **/
    EZ_LDNUL,
    /**
     * Load a Contant Boolean
     * 
     * @arg uchar the register to load the value to
     * @arg uchar the value to load
     * 
     * Loads the given boolean into the given regier.
     **/
    EZ_LDBOL,
    /**
     * Load a Contant Integer
     * 
     * @arg uchar the register to load the value to
     * @arg long long the value to load
     * 
     * Loads the given integer into the given regier.
     **/
    EZ_LDINT,
    /**
     * Load a Contant Real
     * 
     * @arg uchar the register to load the value to
     * @arg double the value to load
     * 
     * Loads the given integer into the given regier.
     **/
    EZ_LDREL,
    /**
     * Load a Contant String
     * 
     * @arg uchar the register to load the value to
     * @arg uint the string length
     * @arg char* the string 
     * 
     * Loads the given integer into the given regier.
     **/
    EZ_LDSTR
};
typedef enum ez_opcode_e ez_opcode_t;

#endif
