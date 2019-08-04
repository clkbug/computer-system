#include "csapp.h"

int
main(int argc, char** argv)
{
    execve("/bin/ls", argv, __environ); // GNU ls は COLUMNS をターミナルドライバに幅を問い合わせて返ってこなかった時にだけ見るらしいのでうまく確認できない
    return 0;
}