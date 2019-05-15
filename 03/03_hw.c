#include "03.h"

/* 03.58 */
long
decode2_c(long x, long y, long z)
{
    return x + y + z;
}

void
hw03_58(void)
{
    for (int i = 0; i < 10000; i++) {
        long x = rand(), y = rand(), z = rand();
        assert(decode2(x, y, z) == decode2_c(x, y, z));
    }
    printf("03.58 ... ok\n");
}

int
main()
{
    srand(0x12345678);

    hw03_58();

    return 0;
}
