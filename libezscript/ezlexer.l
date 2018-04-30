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
%}            

%%

[ \t\v]                     /* skip */
(\n|\r|(\r\n))              /* tbd lines */
      
"null"                      return NILL;         

"="                         return EQUAL;
"+"                         return PLUS;
"-"                         return MINUS;
"*"                         return STAR;
"/"                         return SLASH;
"%"                         return PERCENT;
"("                         return OPEN_PAREN;
")"                         return CLOSE_PAREN;
";"                         return SEMI;

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
                                ezlval.string = strdup(yytext);
                                return STRING;
                            }

.                           return ERROR;

%%

#include <stdio.h>

int yywrap()
{
    return 1;
}

void ezerror(ast_node_t** root, const char* msg) 
{
    printf("string(%d): error: %s \n", ezlineno, msg);
}