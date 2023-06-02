#include <stdio.h>

#define NUM_YEARS 20000000
#define NTRIES 128

extern int years_to_check[NUM_YEARS];

extern long long someval;

extern int is_leap1(int);//smart computation
extern int is_leap2(int);//dumb computation
extern int is_leap3(int);//dumb LUT
extern int is_leap4(int);//smart LUT

int
main(int argc, char *argv[])
{
	int i, j;
	int sum = 0;

	for(j=0;j<NTRIES;++j)
	for(i=0;i<NUM_YEARS;++i)
	{
		sum += is_leap4(years_to_check[i]);
		someval = someval + sum + 1;
	}
	return sum;
#if 0
	printf("%d\n", is_leap(2016));
	printf("%d\n", is_leap(1900));
	printf("%d\n", is_leap(2000));
	printf("%d\n", is_leap(2001));
#endif
	return 0;
}
