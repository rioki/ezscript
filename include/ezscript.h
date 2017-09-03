
#ifndef _EZSCRIPT_H_
#define _EZSCRIPT_H_

#define EZ_OK                0
#define EZ_PARSE_ERROR      -1
#define EZ_OUT_OF_MEMORY    -2

/**
 * Compile EZ script code.
 *
 **/
int ez_compile(const char* code);

#endif
