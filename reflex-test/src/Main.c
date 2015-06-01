#include "Executor.h"

int AppMain(void)
{
  Executor_Init();

  while(Executor_Run());

  return 0;
}

#ifndef TEST
int main(void)
{
  return AppMain();
}
#endif // TEST
