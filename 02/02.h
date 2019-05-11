#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned char* byte_pointer;

void
show_bytes(byte_pointer start, size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

#define SHOW(NAME, TYPE) \
    void show_##NAME(TYPE x) { show_bytes((byte_pointer)&x, sizeof(TYPE)); }

SHOW(int, int)
SHOW(float, float)
SHOW(pointer, void*)

/* p.104 */
int
get_msb(int x)
{
    int shift_val = (sizeof(int) - 1) << 3;
    int xright = x >> shift_val;
    return xright & 0xFF;
}

/* 02.67 */
/*
int
bad_int_size_is_32(void)
{
    int set_msb = 1 << 31;
    int beyond_msb = 1 << 32;
    return set_msb && !beyond_msb;
}
*/
