/*
1. gcc root.c
2. sudo chown root ./a.out
3. sudo chmod 4750 ./a.out
4. sudo rm -rf /tmp/dir1
5. sudo ./a.out
6. ls -ld /tmp/dir1
7. sudo ls -ld /tmp/dir1/subdir
*/
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define DEMO_PATH "/tmp/dir1"

int
main(int argc, char *argv[])
{
    int rc;

    if (geteuid() != 0)
    {
        fprintf(stderr, "This demo requires root access\n");
        return -1;
    }

    if (access(DEMO_PATH, F_OK) == 0)
    {
        fprintf(stderr, "Remove " DEMO_PATH "\n");
        return -1;
    }

    rc = mkdir(DEMO_PATH, 0777);
    if (rc != 0)
    {
        fprintf(stderr, "Can't create base demo dir " DEMO_PATH "\n");
        return -1;
    }

    rc = chmod(DEMO_PATH, 0000);
    if (rc != 0)
    {
        fprintf(stderr, "Can't remove permissions from " DEMO_PATH "\n");
        return -1;
    }

    rc = mkdir(DEMO_PATH "/subdir", 0777);
    if (rc == 0)
    {
        fprintf(stderr, "Parent " DEMO_PATH " has no permissions, but root "
            "still can create subdirs in it. Just created "
            DEMO_PATH "/subdir\n");
        return -1;
    }
    else
    {
        fprintf(stderr, "Seems you are not root\n");
        return -1;
    }
    return 0;
}
