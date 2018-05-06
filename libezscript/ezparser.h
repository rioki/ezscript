/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_EZ_LIBEZSCRIPT_EZPARSER_H_INCLUDED
# define YY_EZ_LIBEZSCRIPT_EZPARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int ezdebug;
#endif
/* "%code requires" blocks.  */
#line 31 "libezscript/ezparser.y" /* yacc.c:1909  */


#include "ezscript.h"
#include "ast.h"


#line 51 "libezscript/ezparser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    END = 0,
    ERROR = 258,
    KW_NULL = 259,
    KW_TRUE = 260,
    KW_FALSE = 261,
    EQUAL = 262,
    PLUS = 263,
    MINUS = 264,
    SEMI = 265,
    COLON = 266,
    COMMA = 267,
    DOT = 268,
    STAR = 269,
    SLASH = 270,
    PERCENT = 271,
    OPEN_PAREN = 272,
    CLOSE_PAREN = 273,
    OPEN_CURLY = 274,
    CLOSE_CURLY = 275,
    OPEN_SQUARE = 276,
    CLOSE_SQUARE = 277,
    IDENTIFIER = 278,
    REAL = 279,
    INTEGER = 280,
    STRING = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 49 "libezscript/ezparser.y" /* yacc.c:1909  */

    char* string;
    ast_node_t* node;  

#line 96 "libezscript/ezparser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE ezlval;
extern YYLTYPE ezlloc;
int ezparse (ast_node_t** root);

#endif /* !YY_EZ_LIBEZSCRIPT_EZPARSER_H_INCLUDED  */
