#include "02.h"

// 02.55
void
hw02_55(void)
{
    int a = 0x12345678;
    show_bytes((byte_pointer)&a, sizeof(int));
    // little endian  <=> 78 56 34 12
    // big endian     <=> 12 34 56 78
}

// 02.56 - 57 skip

// 02.58
int
is_little_endian(void)
{
    int a = 0x12345678;
    char* p = (char*)&a;
    if (*p == 0x12) {
        return 0;
    } else {
        return 1;
    }
}

void
hw02_58(void)
{
    if (is_little_endian() == 1) {
        printf("02.58 ... little endian\n");
    } else {
        printf("02.58 ... big endian\n");
    }
}

// 02.59
int
swap_least_significant_byte(int x, int y)
{
    return (x & 0xFF) | (y & 0xFFFFFF00);
}

void
hw02_59(void)
{
    assert(swap_least_significant_byte(0x89ABCDEF, 0x76543210) == 0x765432EF);
    printf("02.59 ... ok\n");
}

// 02.60
unsigned int
replace_byte(unsigned int x, int i, unsigned char b)
{
    return (x & ~(0xFF << 8 * i)) | (b << 8 * i);
}

void
hw02_60(void)
{
    assert(replace_byte(0x12345678, 2, 0xAB) == 0x12AB5678);
    assert(replace_byte(0x12345678, 0, 0xAB) == 0x123456AB);
    printf("02.60 ... ok\n");
}

// 02.61
int
hw02_61_a(int x)
{
    return ~x == 0;
}
int
hw02_61_b(int x)
{
    return x == 0;
}
int
hw02_61_c(int x)
{
    return (x & 0xFF) == 0xFF;
}
int
hw02_61_d(int x)
{
    return get_msb(x) == 0;
}

void
hw02_61(void)
{
    assert(hw02_61_a(0) == 0);
    assert(hw02_61_a(1) == 0);
    assert(hw02_61_a(0xFFFFFFFF) == 1);
    assert(hw02_61_a(0xFFFFEFFF) == 0);
    printf("02.61 A ... ok\n");

    assert(hw02_61_b(0) == 1);
    assert(hw02_61_b(1) == 0);
    assert(hw02_61_b(0x10100) == 0);
    assert(hw02_61_b(0x10000000) == 0);
    printf("02.61 B ... ok\n");

    assert(hw02_61_c(0) == 0);
    assert(hw02_61_c(10) == 0);
    assert(hw02_61_c(0x101FF) == 1);
    assert(hw02_61_c(0x10000000) == 0);
    printf("02.61 C ... ok\n");

    assert(hw02_61_d(0) == 1);
    assert(hw02_61_d(10) == 1);
    assert(hw02_61_d(0xAE5101FF) == 0);
    assert(hw02_61_d(0x10000000) == 0);
    printf("02.61 D ... ok\n");
}

/* 02.62 */
int
int_shifts_are_arithmetic(void)
{
    int bit_length = sizeof(int) << 3;
    int x = -1;
    if ((x >> (bit_length - 1)) == -1) {
        return 1;
    } else {
        return 0;
    }
}

void
hw02_62(void)
{
    printf("02.62 ... ");
    if (int_shifts_are_arithmetic() == 1) { /* GCC/Clang on x64 */
        printf("arithmetic shift\n");
    } else {
        printf("logical shift\n");
    }
}

/* 02.63 */
unsigned int
srl(unsigned int x, int k)
{
    /* Perform shift arithmetically */
    unsigned int xsra = (int)x >> k;
    const int bit_length = sizeof(int) * 8;

    /*  (1 << k) - 1                         = 0b11...1
        ((1 << k) - 1 << (bit_length - k))   = 0b11...100...0 (1: k, 0: bit_length - k)
        ~((1 << k) - 1 << (bit_length - k))  = 0b00...011...1 (0: k, 1: bit_length - k) */
    const unsigned int msb_zeros = ~(((1 << k) - 1) << (bit_length - k));
    return xsra & msb_zeros;
}

int
sra(int x, int k)
{
    /* Perform shift logically */
    // int xsrl = (unsigned int)x >> k;
    // const int bit_length = sizeof(int) * 8;
    return 0;
}

void
hw02_63(void)
{
    printf("srl(8, 2) == %x\n", srl(0xFFFFFFF, 32));
    assert(srl(0xFFFFFFFF, 1) == 0x7FFFFFFF);
    assert(srl(0xFFFFFFFF, 16) == 0xFFFF);
    assert(srl(0xFFFFFFFF, 31) == 1);
    /* assert(srl(0xFFFFFFFF, 32) == 0); */ /* undefined behavior; See https://www.jpcert.or.jp/sc-rules/c-int34-c.html */

    printf("02.63 ... ok\n");
}

int
main()
{
    hw02_55();

    hw02_58();
    hw02_59();
    hw02_60();
    hw02_61();
    hw02_62();
    hw02_63();

    return 0;
}
