#include "csapp.h"

void
doit()
{
    if (Fork() == 0) {               // 子プロセス1生成
        Fork();                      // 子プロセス2生成←1
        printf("hello in doit()\n"); // 子プロセス２個で実行される
        return;
    }
    return;
}

int
main()
{
    doit();
    printf("hello in main()\n"); // 親プロセス1，子プロセス2個の計3プロセスで実行
    // トータルで5行
    exit(0);
}