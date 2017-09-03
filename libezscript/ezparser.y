
%defines
%locations
%error-verbose
%name-prefix "ez"

%{

int ezlex();
void ezerror(const char* msg);

%}

%token              END 0           "end of file"
%token              ERROR           "lexing error"

%token              VAR             "var"

%token              EQUAL           "="
%token              SEMI            ";"

%token              IDENTIFIER      "identifier"
%token              NUMBER          "number"

%%

ezscript : statements 
         | /* nothing */;

statements : statements statement
           | statement;

statement : variable_declaration;

variable_declaration : "var" IDENTIFIER ";" 
                     | "var" IDENTIFIER "=" literal ";";
                     
literal : number;

number : NUMBER;

%%

#include <stdio.h>

void ezerror(const char* msg) 
{
    printf("error: %s \n", msg);
}
