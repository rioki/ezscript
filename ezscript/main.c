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

#include <stdio.h>
#include <stdlib.h>
#include <ezscript.h>

int main(int argc, char* argv[])
{
    int          ezres;
    size_t       buffer_size = 0;
    char*        buffer      = NULL;
    ez_context_t context;

    printf("ezscript - Version: %s\n", VERSION);

    ezres = ez_context_init(&context);
    if (ezres != EZ_OK)
    {
        printf("Failed to initialize context: %s\n", ez_error_string(ezres));
    }

    while (1)
    {
        int chars_read = getline(&buffer, &buffer_size, stdin);
        if (chars_read < 1)
        {
            break;
        }
        
        ezres = ez_execute(&context, buffer);
        if (ezres != EZ_OK)
        {
            printf("Failed to execute line: %s\n", ez_error_string(ezres));
        }
    }

    ezres = ez_context_clear(&context);
    if (ezres != EZ_OK)
    {
        printf("Failed to cleanup context: %s\n", ez_error_string(ezres));
    }

    return 0;
}
