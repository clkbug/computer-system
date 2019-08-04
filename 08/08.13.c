#include "csapp.h"

int
main()
{
    int x = 3;
    __pid_t pid = Fork();
    if (pid != 0) {
        printf("x=%d(%d)\n", ++x, pid);
    }
    printf("x=%d(%d)\n", --x, pid);

    /* 2(child) */
    /* 4(parent) -> 3(parent) */
    return 0;
}