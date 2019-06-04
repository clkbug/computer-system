#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 03_asm.s */
long decode2(long x, long y, long z);

/* 03.59 */
typedef __int128 int128_t;

void
store_prod(int128_t* dest, int64_t x, int64_t y)
{
    *dest = x * (int128_t)y;
}

/* 03_asm.s */
long loop(long x, int n);
