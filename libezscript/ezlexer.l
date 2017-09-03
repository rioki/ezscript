
%option 8bit
%option warn
%option prefix="ez"

%{
#include "ezparser.h"
%}            

%%

[ \t\v]                     /* skip */
(\n|\r|(\r\n))              /* tbd lines */

"var"                       return VAR;         

"="                         return EQUAL;
";"                         return SEMI;

[a-zA-Z_][a-zA-Z0-9_]*      return IDENTIFIER;

[0-9]+                      return NUMBER; /* tbd floats */

.                           return ERROR;

%%

int yywrap()
{
    return 1;
}
