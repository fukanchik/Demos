/* man 3 stderr: The stream stderr is unbuffered.  The stream stdout is line-buffered when it points to a terminal. */
#include <stdio.h>
#include <unistd.h>

int
main()
{
	printf("AAA");
    fprintf(stderr, "BBB");
	fork();
	printf("\n");
    fprintf(stderr, "\n");
	// fflush(stdout);
	return 0;
}
