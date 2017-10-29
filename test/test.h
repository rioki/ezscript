
#include <stdio.h>

typedef int (*test_fun)();

int tst_register(const char* name, test_fun fun);
int tst_run();

#define TST_REGISTER(NAME) \
    int result ## NAME = tst_register(#NAME, NAME); \
    if (result ## NAME < 0) \
    { \
        printf("Failed to register %s test.\n", #NAME); \
        return result ## NAME; \
    }

#define TST_ASSERT(COND) \
    if (!(COND)) \
    { \
        printf("%s(%d): Assertion %s failed.\n", __FILE__, __LINE__, #COND); \
        return 0; \
    }