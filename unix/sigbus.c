/* Generate SIGBUS */
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define SHMEMNAME "/test"

int main() {
    shm_unlink(SHMEMNAME);
    int fd = shm_open(SHMEMNAME, O_RDWR | O_CREAT, (mode_t)0600);
    //ftruncate(fd, size);
    int *map = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    map[0] = 0;
}

