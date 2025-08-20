#include <stdio.h>
#include <unistd.h>

int
main()
{
	printf("AAA");
	fork();
	printf("\n");
	// fflush(stdout);
	return 0;
}
