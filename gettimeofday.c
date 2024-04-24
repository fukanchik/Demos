/*
 gettimeofday granularity plus demo of non-monotonicity
*/
#include <stdio.h>
#include <sys/time.h>
#include <stddef.h>

static int
EQ(struct timeval a, struct timeval b)
{
  return a.tv_sec==b.tv_sec && a.tv_usec == b.tv_usec;
}

int
main()
{
  long int i;
  struct timeval z, x;
  gettimeofday(&z, NULL);
  gettimeofday(&x, NULL);

  for(i=1; EQ(x,z); i++)
  {
    gettimeofday(&z, NULL);
  }

  printf("%ld: %ld\n",i, (z.tv_sec*1000000+z.tv_usec)-(x.tv_sec*1000000+x.tv_usec));
}
