#include "csapp.h"

const int WAIT_TIME = 5;

sigjmp_buf buf;

void
alarm_handler(int sig)
{
    siglongjmp(buf, 1);
}

char*
tfgets(char* s, int size, FILE* stream)
{
    Signal(SIGALRM, alarm_handler);
    alarm(WAIT_TIME);
    if (!sigsetjmp(buf, 1)) {
        return fgets(s, size, stream);
    } else {
        return NULL;
    }
}

int
main()
{
    char s[512] = "hello, world";
    if (!tfgets(s, sizeof(s), stdin)) {
        printf("\n");
        printf("TIME OUT!\n");
    } else {
        printf("%s", s);
    }
    return 0;
}