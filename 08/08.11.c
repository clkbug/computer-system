#include "csapp.h"

int
main()
{
    for (int i = 0; i < 2; i++) {
        if (fork() == -1) {
            perror("fork");
            exit(1);
        }
    }

    printf("hello\n"); // 親プロセスが2回フォーク，子プロセス1が1回フォークするので4プロセスがhelloと表示する
}