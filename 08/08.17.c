#include "csapp.h"

int
main()
{
    int status;
    pid_t pid;

    printf("hello\n");
    pid = Fork();
    printf("pid: %d, %d\n", pid, !pid);
    if (pid != 0) {
        if (waitpid(-1, &status, 0) > 0) {
            if (WIFEXITED(status) != 0) {
                printf("status: %d\n", WEXITSTATUS(status));
            }
        }
    }
    printf("Bye\n");
    exit(2);
}