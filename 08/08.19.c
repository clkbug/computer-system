#include "csapp.h"

void
foo(int n)
{
    for (int i = 0; i < n; i++) {
        Fork();
    }
    printf("hello\n");
    exit(0);
}

int
main(int argc, char** argv)
{
    int n = atoi(argv[1]);
    foo(n); // 2^n 回 hello の出力
}