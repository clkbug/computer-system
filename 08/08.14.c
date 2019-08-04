#include "csapp.h"

void
doit()
{
    if (Fork() == 0) {               // 子プロセス1生成
        Fork();                      // 子プロセス2生成←1
        printf("hello in doit()\n"); // 子プロセス２個で実行される
        exit(0);
    }
    return;
}

int
main()
{
    doit();
    printf("hello in main()\n"); // 親プロセスでのみ実行
    exit(0);
}
