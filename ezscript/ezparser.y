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

%defines
%locations
%error-verbose
%name-prefix "ez"
%locations
%parse-param {ast_node_t** root}

%code requires {

#include "ezscript.h"
#include "ast.h"

}

%{

#include "stdlib.h"

#include "ast.h"

int ezlex();
void ezerror(ast_node_t** root, const char* msg);

%}

%union {
    char* string;
    ast_node_t* node;  
}

%token              END 0           "end of file"
%token              ERROR           "lexing error"

%token              KW_VAR          "var"
%token              KW_NULL         "null"
%token              KW_TRUE         "true"
%token              KW_FALSE        "false"

%token              EQUAL           "="
%token              EQUALS          "=="
%token              NOT_EQUALS      "!="
%token              LESS            "<"
%token              GRATER          ">"
%token              LESS_EQUAL      "<="  
%token              GRATER_EQUAL    ">="
%token              PLUS            "+"
%token              MINUS           "-"
%token              SEMI            ";"
%token              COLON           ":"
%token              COMMA           ","
%token              DOT             "."
%token              STAR            "*"
%token              SLASH           "/"
%token              PERCENT         "%"
%token              OPEN_PAREN      "("
%token              CLOSE_PAREN     ")"
%token              OPEN_CURLY      "{"
%token              CLOSE_CURLY     "}"
%token              OPEN_SQUARE     "["
%token              CLOSE_SQUARE    "]"

%token <string>     IDENTIFIER      "identifier"
%token <string>     REAL            "real"
%token <string>     INTEGER         "integer"
%token <string>     STRING          "string"

%type <node>        statements statement 
%type <node>        literal reference assignment primexp
%type <node>        expression addexp mulexp equexp cmpexp
%type <node>        object members member vardecl
%type <node>        array elements element

%%

ezscript                : statements                            {(*root) = $1;};   
                        | /* nothing */                         {(*root) = NULL;}
                        ;

statements              : statements statement                  {$$ = ast_append($1, $2);}
                        | statement                             {$$ = $1;}
                        ;

statement               : assignment                            {$$ = $1;}
                        | vardecl                               {$$ = $1;}
                        ;

vardecl                 : "var" reference "=" expression ";"    {$$ = ast_join(AST_VARDECL, $2, $4);}

assignment              : reference "=" expression ";"          {$$ = ast_join(AST_ASSIGNMENT, $1, $3);}

expression              : equexp                                {$$ = $1;}
                        ;

equexp                  : cmpexp                                {$$ = $1;}
                        | equexp "==" cmpexp                    {$$ = ast_join(AST_EQUALS, $1, $3);}
                        | equexp "!=" cmpexp                    {$$ = ast_join(AST_NOT_EQUALS, $1, $3);}
                        ;

cmpexp                  : addexp                                {$$ = $1;}
                        | cmpexp "<" addexp                     {$$ = ast_join(AST_LESS, $1, $3);}
                        | cmpexp "<=" addexp                    {$$ = ast_join(AST_LESS_EQUAL, $1, $3);}
                        | cmpexp ">" addexp                     {$$ = ast_join(AST_GRATER, $1, $3);}
                        | cmpexp ">=" addexp                    {$$ = ast_join(AST_GRATER_EQUAL, $1, $3);}


addexp                  : mulexp                                {$$ = $1;}
                        | addexp "+" mulexp                     {$$ = ast_join(AST_ADDITION, $1, $3);}
                        | addexp "-" mulexp                     {$$ = ast_join(AST_SUBTRACTION, $1, $3);}
                        ;

mulexp                  : primexp                               {$$ = $1;}
                        | mulexp "*" primexp                    {$$ = ast_join(AST_MULTIPLICATION, $1, $3);}     
                        | mulexp "/" primexp                    {$$ = ast_join(AST_DIVISION, $1, $3);}     
                        | mulexp "%" primexp                    {$$ = ast_join(AST_MODULO, $1, $3);}
                        ;                       

primexp                 : "(" expression ")"                    {$$ = $2;}
                        | array                                 {$$ = $1;}
                        | object                                {$$ = $1;}
                        | reference                             {$$ = $1;}
                        | literal                               {$$ = $1;}
                        ;

array                   : "[" elements "]"                      {$$ = ast_single(AST_ARRAY, $2);}
                        | "[" "]"                               {$$ = ast_create(AST_ARRAY);}
                        ; 

elements                : elements "," element                  {$$ = ast_append($1, $3);}
                        | element                               {$$ = $1;}
                        ;

element                 : expression                            {$$ = $1;}
                        ;

object                  : "{" members "}"                       {$$ = ast_single(AST_OBJECT, $2);}
                        | "{" "}"                               {$$ = ast_create(AST_OBJECT);}
                        ;

members                 : members "," members                   {$$ = ast_append($1, $3);}
                        | member                                {$$ = $1;}
                        ;

member                  : IDENTIFIER ":" expression             {$$ = ast_named_single(AST_MEMBER, $1, $3);}
                        ;

reference               : reference "." IDENTIFIER              {$$ = ast_child($1, ast_leaf(AST_REFERENCE, $3));}
                        | IDENTIFIER                            {$$ = ast_leaf(AST_REFERENCE, $1);}
                        ;

literal                 : REAL                                  {$$ = ast_leaf(AST_LITERAL_REAL, $1);}
                        | INTEGER                               {$$ = ast_leaf(AST_LITERAL_INTEGER, $1);}
                        | STRING                                {$$ = ast_leaf(AST_LITERAL_STRING, $1);}
                        | "true"                                {$$ = ast_cleaf(AST_LITERAL_BOOLEAN, "true");}
                        | "false"                               {$$ = ast_cleaf(AST_LITERAL_BOOLEAN, "false");}
                        | "null"                                {$$ = ast_cleaf(AST_LITERAL_NULL, "null");}
                        ;

%%

