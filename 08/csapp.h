#ifndef __CSAPP_H__
#define __CSAPP_H__

#include <assert.h>
#include <errno.h>
#include <features.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int
Execve(const char* __path, char* const __argv[], char* const __envp[])
{
    int r = execve(__path, __argv, __envp);
    if (r == -1) {
        perror("execve");
        exit(255);
    }
    return r;
}

__sighandler_t
Signal(int signum, __sighandler_t sighandler)
{
    __sighandler_t s = signal(signum, sighandler);
    if (s == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    return s;
}

int
Kill(pid_t pid, int sig)
{
    int r = kill(pid, sig);
    if (r == -1) {
        perror("kill");
        exit(1);
    }
    return r;
}

#endif