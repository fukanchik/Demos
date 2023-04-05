#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdatomic.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFSZ 8192

#define NTHREADS 4

#define NUM_WRITES 256

typedef struct
{
	int thnum;
	int start;
	int fd;
} args_t;

/* This is a counter for our position in the output file. */
static atomic_ulong offset;

static void*
writer_func(void *a)
{
	args_t *args = a;
	char buf[BUFSZ];

	for(int i = 0; i < NUM_WRITES; ++i)
	{
		int write_size = snprintf(buf, BUFSZ, "%d:%d\n", args->thnum, i);
		unsigned long myoffset = atomic_fetch_add(&offset, write_size);
		/*
		  At this point myoffset points to the last available position.
		  atomic_fetch_add moves `offset` by write_size bytes and returns us the previous value.
		  Any other thread will get a different position.
		 */
		ssize_t rc = pwrite(args->fd, buf, write_size, myoffset);
		if (rc != write_size)
		{
			fprintf(stderr, "pwrite: %s", strerror(errno));
			exit(1);
		}
	}

	return NULL;
}

int
main(int argc, char *argv[])
{
	int i, rc;

	pthread_t threads[NTHREADS];
	args_t args[NTHREADS];
	unlink("/tmp/datagrams");
	int fd = open("/tmp/datagrams", O_CREAT|O_WRONLY, 0600);

	if (fd==-1)
	{
		fprintf(stderr, "open: %s", strerror(errno));
		return -1;
	}
	/* Initialize file offset. File does not yet exist, and offset is zero. */
	offset = 0;

	for(i = 0; i < NTHREADS; ++i)
	{
		args[i].thnum=i;
		args[i].start = i * NUM_WRITES;
		args[i].fd = fd;
		rc = pthread_create(&threads[i], NULL, writer_func, args+i);
		if (rc)
		{
			fprintf(stderr, "pthread_create: %s", strerror(rc));
			return 1;
		}
	}

	for (i = 0; i < NTHREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}

	close(fd);

	return 0;
}
