
#include "test.h"
#include "ezscript.h"

int test_empty() 
{  
    char* code = "";
    
    int r = ez_compile(code);
    
    return r == EZ_OK;
}

int test_variable() 
{
    char* code = "var a = 1;";
    
    int r = ez_compile(code);
    
    return r == EZ_OK;
}

int register_parse_tests()
{
    TST_REGISTER(test_empty);
    TST_REGISTER(test_variable);
    
    return 0;
}
