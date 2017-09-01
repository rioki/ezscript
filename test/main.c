
#include <stdio.h>
#include "test.h"

int register_parse_tests();

int main(int argc, char*argv[]) 
{
    int r = 0;

    r = register_parse_tests();
    if (r < 0) 
    {
        printf("Registering parse tests failed.\n");
        return -1;
    }

    return tst_run();
}
