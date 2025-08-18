/*
  Throw exception from within a signal handler.
  This causes heap corruption b/c of allocated exception block.
  Compile with optimization to get the error faster.
*/
#include <signal.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

static void
signal_handler(int n)
{
	if (::write(1, "Signal handler\n", 6) == -1)
		abort();
	throw 1;
}

static void
setup_signal()
{
	struct sigaction sig;
	memset(&sig, 0, sizeof(struct sigaction));
	sig.sa_handler = signal_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;

	sigaction(SIGINT, &sig, NULL);
}

int
main(int argc, char *argv[])
{
	(void)argv;
	bool need_allocate = argc > 1;
	setup_signal();

	try
	{
		if (need_allocate)
		{
			/* This conflicts with __cxa_allocate_exception which corrupts heap.
			 */
			while (true)
			{
				char *p = new char[1];
				delete[] p;
			}
		}
		else
		{
			pause();
		}
	}
	catch (int v)
	{
		std::cerr << "VAL " << v << std::endl;
	}
	return 0;
}
