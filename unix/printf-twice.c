#include <unistd.h>
#include <stdio.h>

int main()
{
  printf("AAA");
  fork();
  printf("\n");
  //fflush(stdout);
  return 0;
}

