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

#ifndef _TRACE_H_
#define _TRACE_H_

#ifndef NDEBUG

#define EZ_TRACE(MSG) ez_trace(__FILE__, __LINE__, MSG)
#define EZ_TRACEV(MSG, ...) ez_tracev(__FILE__, __LINE__, MSG, __VA_ARGS__)

void ez_trace(const char* file, unsigned int line, const char* msg);
void ez_tracev(const char* file, unsigned int line, const char* format, ...);

#else
#define TRACE(MSG)
#define TRACEV(MSG, ...)
#endif

#define EZ_CHECK_ARGUMENT(COND)                                                 \
    if (!(COND))                                                                \
    {                                                                           \
        EZ_TRACE(#COND);                                                        \
        return EZ_INVALID_ARGUMENT;                                             \
    }

#define EZ_CHECK_TYPE(VALUE, TYPE)                                              \
    if (VALUE->type != TYPE)                                                    \
    {                                                                           \
        EZ_TRACEV("Expected %s, but got %s", #TYPE, ez_type_to_string(VALUE->type)); \
        return EZ_INVALID_TYPE;                                                 \
    }

#endif
