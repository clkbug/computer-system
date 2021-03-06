#include "03.h"

/* 03.58 */
long
decode2_c(long x, long y, long z)
{
    long t;
    y = y - z;
    x *= y;
    t = y;
    t <<= 63;
    t >>= 63;
    return t ^ x;
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

long
loop_c(long x, int n)
{
    long result = 0;

    for (long mask = 1; mask != 0; mask <<= (n & 0xFF)) {
        result |= x & mask;
    }
    return result;
}

void
hw03_59(void)
{
    for (int i = 0; i < 100; i++) {
        long x = rand();
        int n = rand() % 1000 + 1;
        assert(loop(x, n) == loop_c(x, n));
    }
    printf("03.59 ... ok\n");
}

int
main()
{
    srand(0x12345678);

    hw03_58();
    hw03_59();

    return 0;
}
