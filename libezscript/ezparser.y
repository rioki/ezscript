
%defines
%locations
%error-verbose
%name-prefix "ez"

%code requires 
{

#include <assert.h>
#include "ast.h"

int ezlex();
void ezerror(const char* file, ez_ast_t* ast_root, const char* msg) ;

}

%parse-param {const char* file}
%parse-param {ez_ast_t* ast_root}

%union
{    
    char*     string;
    ez_ast_t* node;
}

%token              END 0           "end of file"
%token              ERROR           "lexing error"

%token              VAR             "var"

%token              EQUAL           "="
%token              SEMI            ";"

%token <string>     IDENTIFIER      "identifier"
%token <string>     NUMBER          "number"
%token <string>     STRING          "string"

%type <node>        number string identifier
%type <node>        literal statement statements variable_declaration

%destructor { free($$); } <string>
%destructor { free($$); } <node>

%%

ezscript                : statements 
                        {
                            assert(ast_root != NULL);
                            ez_ast_append_child(ast_root, $1);
                        };

statements              : statements statement 
                        {
                            $$ = ez_ast_append_sibling($1, $2);
                        }
                        | statement 
                        {
                            $$ = $1;
                        };

statement               : variable_declaration 
                        {
                            $$ = ez_ast_create(file, @1.first_line, EZ_STATEMENT, NULL); 
                            ez_ast_append_child($$, $1);
                        };

variable_declaration    : "var" identifier ";" 
                        {
                            $$ = ez_ast_create(file, @1.first_line, EZ_VARIABLE_DECLARATION, NULL); 
                            ez_ast_append_child($$, $2);
                        }
                        | "var" identifier "=" literal ";" {
                            $$ = ez_ast_create(file, @1.first_line, EZ_VARIABLE_DECLARATION, NULL); 
                            ez_ast_append_child($$, $2);
                            ez_ast_append_child($$, $4);
                        };
                     
literal                 : number 
                        | string;

identifier              : IDENTIFIER 
                        {
                            $$ = ez_ast_create(file, @1.first_line, EZ_AST_IDENTIFIER, $1); 
                        };

number                  : NUMBER 
                        {
                            $$ = ez_ast_create(file, @1.first_line, EZ_AST_NUMBER, $1);   
                        };

string                  : STRING 
                        {
                            $$ = ez_ast_create(file, @1.first_line, EZ_AST_STRING, $1);   
                        };

%%

#include <stdio.h>

void ezerror(const char* file, ez_ast_t* ast_root, const char* msg) 
{
    printf("error: %s \n", msg);
}
