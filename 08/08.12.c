#include "csapp.h"

void
doit(void)
{
    Fork();
    Fork();
    printf("hello in doit()\n"); // 4 回
    return;
}

int
main()
{
    doit();
    printf("hello in main()\n"); // 4 回
}