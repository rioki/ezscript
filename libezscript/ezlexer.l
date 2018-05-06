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

%option 8bit
%option warn
%option prefix="ez"
%option yylineno

%{
#include <string.h>

#include "ezparser.h"
#include "ast.h"

char* unescape(const char* source);
%}            

%%

[ \t\v]                     /* skip */
(\n|\r|(\r\n))              /* tbd lines */
      
"null"                      return KW_NULL;
"true"                      return KW_TRUE;  
"false"                     return KW_FALSE;       

"="                         return EQUAL;
"=="                        return EQUALS;
"!="                        return NOT_EQUALS;
"<"                         return LESS;
">"                         return GRATER;
"<="                        return LESS_EQUAL;
">="                        return GRATER_EQUAL;
"+"                         return PLUS;
"-"                         return MINUS;
"*"                         return STAR;
"/"                         return SLASH;
"%"                         return PERCENT;
"("                         return OPEN_PAREN;
")"                         return CLOSE_PAREN;
"{"                         return OPEN_CURLY;
"}"                         return CLOSE_CURLY;
"["                         return OPEN_SQUARE;
"]"                         return CLOSE_SQUARE;
";"                         return SEMI;
":"                         return COLON;
","                         return COMMA;
"."                         return DOT;

[a-zA-Z_][a-zA-Z0-9_]*      {
                                ezlval.string = strdup(yytext);
                                return IDENTIFIER;
                            }

[0-9]+                      {
                                ezlval.string = strdup(yytext);
                                return INTEGER;
                            }

[0-9]+\.[0-9]+              {
                                ezlval.string = strdup(yytext);
                                return REAL;
                            }

\"([^\"\n\r]+|\\\")*\"      {
                                ezlval.string = unescape(yytext);
                                return STRING;
                            }

.                           return ERROR;

%%

#include <stdio.h>

char* unescape(const char* source)
{
    size_t i, j;
    size_t len = strlen(source);
    char* result = (char*)malloc(len - 1);
    memset(result, 0, len - 1);

    /* we know that the string begins with " and ends with " */
    j = 0;
    for (i = 1; i < len - 1; i++)
    {
        if (source[i] == '\\')
        {
            i++;
            switch (source[i])
            {
                case 'a':
                    result[j] = '\a';
                    break;
                case 'b':
                    result[j] = '\b';
                    break;
                case 'f':
                    result[j] = '\f';
                    break;
                case 'n':
                    result[j] = '\n';
                    break;
                case 'r':
                    result[j] = '\r';
                    break;
                case 't':
                    result[j] = '\t';
                    break;
                case 'v':
                    result[j] = '\v';
                    break;
                case '\\':
                    result[j] = '\\';
                    break;
                case '\'':
                    result[j] = '\'';
                    break;
                case '\"':
                    result[j] = '\"';
                    break;
                case '?':
                    result[j] = '\?';
                    break;
                default:
                    result[j] = ' ';
                    break;
            }
        }
        else
        {
            result[j] = source[i];
        }
        j++;
    }
    
    return result;
}

int yywrap()
{
    return 1;
}

void ezerror(ast_node_t** root, const char* msg) 
{
    printf("string(%d): error: %s \n", ezlineno, msg);
}