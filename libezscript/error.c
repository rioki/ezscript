
#include "ezscript.h"

const char* ez_error_string(int errorid)
{
    switch (errorid)
    {
        case EZ_OK:
            return "EZ_OK";
        case EZ_NOT_IMPLEMENTED:
            return "EZ_NOT_IMPLEMENTED";
        case EZ_OUT_OF_MEMORY:
            return "EZ_OUT_OF_MEMORY";
        case EZ_INVALID_ARGUMENT:
            return "EZ_INVALID_ARGUMENT";
        case EZ_PARSE_ERROR:
            return "EZ_PARSE_ERROR";   
    }
}
