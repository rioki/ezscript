
#include "test.h"
#include "ezscript.h"

int test_empty() 
{  
    int r = ez_compile("");
    return r >= 0;
}

int register_parse_tests()
{
    int r = 0;

    tst_register("empty", test_empty);
}
