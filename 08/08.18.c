#include "csapp.h"

void
end(void)
{
    printf("2");
}

int
main()
{
    if (Fork() == 0) {
        atexit(end);
    }
    if (Fork() == 0) {
        printf("0");
    } else {
        printf("1");
    }
    exit(0);

    // ありえるのは A 112002, C 102120, E 100212 // C, E はでた
    // B. 211020 ← 2が0/1に先行するのはありえない
    // D. 122001 ← 2は先行する0/1を必要とするので2個目の2はありえない
}
