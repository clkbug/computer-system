#include "csapp.h"

const int N = 2;

int
main(int argc, char** argv)
{
    int status;
    pid_t pid;

    for (int i = 0; i < N; i++) {
        if ((pid = Fork()) == 0) {
            int* p = (int*)0x500;
            *p = 10;
            exit(100 + i);
        }
    }

    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("child %d terminated by signal %d: %s\n", pid, WTERMSIG(status), strsignal(WTERMSIG(status)));

        } else {
            printf("child %d terminated abnormally\n", pid);
        }
    }

    if (errno != ECHILD)
        perror("waitpid error");

    exit(0);
}