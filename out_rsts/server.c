#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <sys/resource.h>

#include "server.h"

static const int DEFAULT_MAX_COUNT = 10;

static void
silent_abort()
{
  struct rlimit lim;

  lim.rlim_cur=0;
  lim.rlim_max=0;
  setrlimit(RLIMIT_CORE, &lim);

  abort();
}

static int
get_max_count(int argc, char *argv[])
{
  if(argc > 1)
    {
      const char *count_arg = argv[1];
      char *end = NULL;
      int ret;

      errno = 0;
      ret = strtol( count_arg, &end, 10);
      if(count_arg == end || *end != '\0' || errno == ERANGE)
	{
	  fprintf(stderr, "Usage:\n\tserver <optional max-connection-count (default 10)>\n");
	  fprintf(stderr, "ERROR: '%s' is not a number.\n", count_arg);

	  exit(1);
	}
      return ret;
    }
  else
    {
      return DEFAULT_MAX_COUNT;
    }
}

int
main(int argc, char *argv[])
{
  int max_count;
  int count;
  struct sockaddr_in me;
  int yes=1;

  max_count = get_max_count(argc, argv);

  int sockd = socket(AF_INET, SOCK_STREAM, 0 );
  if(sockd==-1) {
    perror("socket()");
    return -1;
  }

  if(setsockopt(sockd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    perror("SO_REUSEADDR");
  }

  me.sin_family = AF_INET;
  me.sin_addr.s_addr = INADDR_ANY;
  me.sin_port = htons(SERVER_PORT);

  if(bind(sockd, (struct sockaddr*)&me, sizeof(struct sockaddr_in)) == -1) {
    perror("bind()");
    return -1;
  }

  if(listen(sockd, 5) == -1) {
    perror("listen()");
    return -1;
  }

  printf("listening for maximum of %d connections on %d\n", max_count, SERVER_PORT);

  for(count = 0; count < max_count; ++count) {
    socklen_t addrlen;
    struct sockaddr_in peer;

    int client = accept(sockd, (struct sockaddr*)&peer, &addrlen);
    if(client==-1) {
      perror("accept()");
      return -1;
    }
    printf("new\n");
  }
  close(sockd);

  silent_abort();
		
  return 0;
}

