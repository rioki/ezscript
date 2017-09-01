
typedef int (*test_fun)();

int tst_register(const char* name, test_fun fun);
int tst_run();
