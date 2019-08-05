#include "csapp.h"

int
mysystem(char* command)
{
    char arg1[] = "-c";
    char* args[] = { "/bin/sh", arg1, command, NULL };
    if (Fork() == 0) {
        Execve(args[0], args, __environ);

        fprintf(stderr, "after execve...\n");
        assert(1);
    } else {
        int status;
        waitpid(-1, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            fprintf(stderr, "???\n");
            exit(100);
        }
    }
    return 0;
}

int
main(int argc, char** argv)
{
    int s = mysystem(argv[1]);
    printf("%s: %d\n", argv[1], s);
}