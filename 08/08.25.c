#include "csapp.h"

const int WAIT_TIME = 5;
char* tfgets_result;

void
alarm_handler(int sig)
{
    tfgets_result = NULL;
    return;
}

void
child_handler(int sig)
{}

char*
tfgets(char* s, int size, FILE* stream)
{
    Signal(SIGCHLD, child_handler);
    Signal(SIGALRM, alarm_handler);

    sigset_t mask, prev;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    Sigprocmask(SIG_BLOCK, &mask, &prev);

    tfgets_result = s;
    if (Fork() == 0) { /* Child Process: fgets*/
        tfgets_result = fgets(s, size, stream);
        exit(0); /* SIGCHLD */
    }

    alarm(WAIT_TIME);

    sigsuspend(&prev); /* Wait SIGCHILD/SIGALRM */

    return tfgets_result;
}

int
main()
{
    char s[512] = "hello, world";
    if (!tfgets(s, sizeof(s), stdin)) {
        printf("\n");
        printf("TIME OUT!\n");
    } else {
        printf("%s\n", s);
    }
    Kill(0, SIGKILL);
}