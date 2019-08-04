#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

__pid_t
Fork(void)
{
    __pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    return pid;
}