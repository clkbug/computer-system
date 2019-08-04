#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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

pid_t
Wait(int* status)
{
    pid_t pid = wait(status);
    if (pid == -1) {
        perror("wait");
        exit(1);
    }
    return pid;
}