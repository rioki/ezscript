
#include "test.h"

int test_dummy() 
{
  return 1;
}

int register_parse_tests()
{
  int r = 0;
  
  tst_register("dummy", test_dummy);
}
