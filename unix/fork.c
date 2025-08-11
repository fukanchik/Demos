/* Copy-on-write on fork() of MAP_PRIVATE */
#include <unistd.h>
#include <memory.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int
main()
{
  pid_t pid;
  char *shared = mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
  char *private = mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

  strcpy(shared, "SHARED");
  strcpy(private, "PRIVATE");
  printf("SHARED=%p:%s PRIVATE=%p:%s\n", shared, shared, private, private);

  pid = fork();
  if (pid == 0)
  {
    memcpy(shared, "NONE!", 6);
    memcpy(private, "NONE!", 6);
    return 0;
  }
  wait(NULL);
  printf("SHARED=%s PRIVATE=%s\n", shared, private);
  return 0;
}
