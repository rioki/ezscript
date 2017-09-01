
#include <assert.h>
#include <stdlib.h> 
#include <stdio.h>
#include "test.h"

typedef struct Test {
  const char*  name;
  test_fun     fun;
  struct Test* next;
} Test;

Test* test_root = NULL;

int tst_register(const char* name, test_fun fun)
{
  Test* test = malloc(sizeof(Test));
  if (test == NULL)
  {
    printf("Failed to alocate structures for %s.\n", name);
    // this will probably do nothing sensible, because this code is executed premain
    return -1; 
  }
  
  test->name = name; // safe if used with TEST macro
  test->fun  = fun;
  test->next = NULL;
  
  if (test_root == NULL) {
    test_root = test;
  }
  else
  {
    Test* tmp = test_root;
    while (tmp->next != NULL) 
    {
      tmp = tmp->next;
    }
    tmp->next = test;
  }
  
  return 0;
}

int tst_run() 
{
  int success = 0;
  int fail    = 0;
  int sum;
  
  Test* tmp = test_root;
  while (tmp != NULL) 
  {
    int r = tmp->fun();
    if (r) 
    {
      success++;
    }
    else
    {
      fail++;
      printf("Test %s failed.\n", tmp->name);
    }
    
    tmp = tmp->next;
  }
  
  sum = success + fail;
  printf("Ran %d tests: %d success %d fail\n", sum, success, fail);
  
  return 0;
}


