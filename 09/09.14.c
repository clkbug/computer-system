#include "09.h"

int
main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./09.14 hello.txt\n");
        exit(1);
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("open error: ");
        exit(1);
    }

    char* addr = mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (!addr) {
        perror("failed to mmap: ");
        exit(1);
    }

    addr[0] = 'J';
    munmap(addr, 256);
    close(fd);
    return 0;
}