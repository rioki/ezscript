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

#include <stdio.h>
#include "test.h"

void run_value_tests(int* num_tests, int* num_errors);
void run_object_tests(int* num_tests, int* num_errors);
void run_function_tests(int* num_tests, int* num_errors);
void run_exec_tests(int* num_tests, int* num_errors);
void run_string_tests(int* num_tests, int* num_errors);

int main(int argc, char* argv[]) 
{
    int num_tests  = 0;
    int num_errors = 0;

    run_value_tests(&num_tests, &num_errors);
    run_object_tests(&num_tests, &num_errors);
    run_function_tests(&num_tests, &num_errors);
    run_exec_tests(&num_tests, &num_errors);
    run_string_tests(&num_tests, &num_errors);

    printf("Ran %d tests, %d failures.\n", num_tests, num_errors);

    return (num_errors == 0) ? 0 : -1;
}
