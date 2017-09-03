
#include "ezscript.h"
#include "ezlexer.h"
#include "ezparser.h"

int ez_compile(const char* code)
{
    YY_BUFFER_STATE buffer;
    int             result;
    
    buffer = ez_scan_string(code);
    
    result = ezparse();
    
    ez_delete_buffer(buffer);
    
    switch (result)
    {
        case 0:
            return EZ_OK;
        case 2:
            return EZ_OUT_OF_MEMORY;
        case 1:
        default:
            return EZ_PARSE_ERROR;
    }
}
