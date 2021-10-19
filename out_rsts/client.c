#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>

#include "server.h"

int main(int argc, char *argv[])
{
	char *host;
	int count;

	struct hostent *h;
	struct sockaddr_in sa;
	int rc, i;

	if(argc != 3) {
		host="localhost";
		count=1;
	} else {
		host = argv[1];
		count = atoi(argv[2]);
	}

	h = gethostbyname(host);
	if(h==NULL) {
		herror("gethostbyname()");
		return -1;
	}
	for(i=0;i<count;++i) {
	int sockd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockd == -1) {
		perror("socket");
		return -1;
	}
	sa.sin_family=AF_INET;
	sa.sin_addr = *(struct in_addr*)h->h_addr;
	sa.sin_port = htons(SERVER_PORT);

	if(connect(sockd, (struct sockaddr*)&sa, sizeof(struct sockaddr_in)) == -1) {
		perror("connect()");
		return -1;
	}
	rc = write(sockd, &sockd, 1);
	printf("rc=%d\n", rc);
	close(sockd);
	}

//	sleep(10);

	return 0;
}

