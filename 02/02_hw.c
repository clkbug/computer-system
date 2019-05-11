#include "02.h"

// 02.55
void
hw02_55(void)
{
    int a = 0x12345678;
    printf("02.55 ... ");
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
    int xsrl = (unsigned int)x >> k;
    const int bit_length = sizeof(int) * 8;

    const unsigned int msb_ones = ((1 << k) - 1) << (bit_length - k);
    return xsrl | (msb_ones & (-(x < 0)));
}

void
hw02_63(void)
{
    assert(srl(0xFFFFFFFF, 1) == 0x7FFFFFFF);
    assert(srl(0xFFFFFFFF, 16) == 0xFFFF);
    assert(srl(0xFFFFFFFF, 31) == 1);
    /* assert(srl(0xFFFFFFFF, 32) == 0); */ /* undefined behavior; See https://www.jpcert.or.jp/sc-rules/c-int34-c.html */

    assert(sra(0xFFFFFFFF, 1) == 0xFFFFFFFF);
    assert(sra(0xFFFFFFFF, 16) == 0xFFFFFFFF);
    assert(sra(0xFFFFFFFF, 31) == 0xFFFFFFFF);
    assert(sra(0x7FFFFFFF, 31) == 0x0);

    printf("02.63 ... ok\n");
}

/* 02.64 */
/* Return 1 when any odd bit of x equals 1; 0 otherwise. Assume w=32 */
int
any_odd_one(unsigned int x)
{
    return x == 0xAAAAAAAA; /* assume 0-origin */
}

void
hw02_64(void)
{
    assert(any_odd_one(0xAAAAAAAA) == 1);
    assert(any_odd_one(0xA0AAAAAA) == 0);
    printf("02.64 ... ok\n");
}

/* 02.65 */
/* Return 1 when x contains an odd number of 1s; 0 otherwise. Assume w=32 */
int
odd_ones(unsigned int x)
{
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    x ^= x >> 16;
    return x & 1;
}

void
hw02_65(void)
{
    assert(odd_ones(0) == 0);
    assert(odd_ones(1) == 1);
    assert(odd_ones(2) == 1);
    assert(odd_ones(3) == 0);
    assert(odd_ones(0x101010) == 1);
    assert(odd_ones(0x101011) == 0);
    assert(odd_ones(0xFFFFFFFF) == 0);
    assert(odd_ones(0xFFFFEFFF) == 1);
    assert(odd_ones(0xFEFF7FFF) == 0);
    printf("02.65 ... ok\n");
}

/* 02.66 */
int
leftmost_one(unsigned int x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    const unsigned int y = x + 1;
    const unsigned int p = y > x;
    return ((y >> 1) & -p) | (0x80000000 & (p - 1));
    /* !!!! contains 17 logical/arithmetic/bit-wise operations ... */
}

void
hw02_66(void)
{
    assert(leftmost_one(0xFF00) == 0x8000);
    assert(leftmost_one(0x6600) == 0x4000);
    assert(leftmost_one(0xFFFFFFF) == 0x8000000);
    assert(leftmost_one(0xFFFFFFFF) == 0x80000000);
    printf("!!! 02.66 ... ok\n");
}

/* 02.67 */
int
is_int_size_is_32(void)
{
    int x = 1 << 15;
    return (x + x > 0) && ((x << 16) + (x << 16) == 0);
}

void
hw02_67(void)
{
    printf("??? 02.67 ... is_int_size_is_32() = %d\n", is_int_size_is_32());
}

/* 02.68 */
int
lower_one_mask(int n)
{
    const int p = n < (sizeof(int) << 3);
    return (((1 << n) - 1) & (-p)) | (-1 & (p - 1));
}

void
hw02_68(void)
{
    assert(lower_one_mask(6) == 0x3F);
    assert(lower_one_mask(17) == 0x1FFFF);
    assert(lower_one_mask(31) == 0x7FFFFFFF);
    assert(lower_one_mask(32) == 0xFFFFFFFF);
    printf("02.68 ... ok\n");
}

/* 02.69 */
unsigned int
rotate_left(unsigned int x, int n)
{
    const int bit_length = sizeof(int) << 3;
    const int y = x << n;
    const int z = (x >> (bit_length - n)) & lower_one_mask(n);
    return y | z; /* n == 0 ????? */
}

void
hw02_69(void)
{
    assert(rotate_left(0x12345678, 4) == 0x23456781);
    assert(rotate_left(0x12345678, 20) == 0x67812345);
    assert(rotate_left(0x12345678, 0) == 0x12345678);
    printf("??? 02.69 ... ok\n");
}

/* 02.70 */
int
fits_bits(int x, int n)
{
    return -(1 << (n - 1)) <= x && x <= (1 << (n - 1)) - 1;
}

void
hw02_70(void)
{
    assert(fits_bits(8, 3) == 0);
    assert(fits_bits(8, 4) == 0);
    assert(fits_bits(8, 5) == 1);
    assert(fits_bits(8, 6) == 1);
    assert(fits_bits(-8, 4) == 1);
    assert(fits_bits(-8, 3) == 0);
    assert(fits_bits(-1, 1) == 1);
    assert(fits_bits(0, 1) == 1);
    assert(fits_bits(1, 1) == 0);
    assert(fits_bits(INT_MAX, 32) == 1);
    assert(fits_bits(INT_MIN, 32) == 1);
    assert(fits_bits(INT_MAX, 31) == 0);
    assert(fits_bits(INT_MIN, 31) == 0);
    printf("02.70 ... ok\n");
}

/* 02.71 */
typedef unsigned int packed_t;
int
xbyte(packed_t word, int bytenum)
{
    return (int)word << (24 - (bytenum << 3)) >> 24;
}

void
hw02_71(void)
{
    assert(xbyte(0x12345688, 0) == 0xFFFFFF88);
    assert(xbyte(0x1234AB78, 1) == 0xFFFFFFAB);
    assert(xbyte(0x12345678, 2) == 0x34);
    assert(xbyte(0x12345678, 3) == 0x12);
    printf("02.71 ... ok\n");
}

/* 02.72 */
void
copy_int(int val, void* buf, int maxbytes)
{
    if (maxbytes >= sizeof(val)) {
        memcpy(buf, (void*)&val, sizeof(val));
    }
}

void
hw02_72(void)
{
    int a = 0;
    copy_int(0x12345678, &a, 4);
    assert(a == 0x12345678);
    a = 0;
    copy_int(0x12345678, &a, 3);
    assert(a == 0);
    printf("02.72 ... ok\n");
}

/* 02.73 */
int
saturationg_add(int x, int y)
{
    const int sum = x + y;
    if ((x > 0 && y > 0 && sum <= 0)) {
        return INT_MAX;
    } else if (x < 0 && y < 0 && sum >= 0) {
        return INT_MIN;
    } else {
        return sum;
    }
}

void
hw02_73(void)
{
    assert(saturationg_add(100, 20) == 120);
    assert(saturationg_add(-1, INT_MIN) == INT_MIN);
    assert(saturationg_add(INT_MAX, INT_MAX) == INT_MAX);
    printf("02.73 ... ok\n");
}

/* 02.74 */
int
tsub_ok(int x, int y)
{
    return (x - y) == saturationg_add(x, -y);
}

void
hw02_74(void)
{
    assert(tsub_ok(0, INT_MIN) == 1);
    assert(tsub_ok(-1, INT_MIN) == 0);
    printf("02.74 ... ok\n");
}

/* 02.75 */
int
signed_high_prod(int x, int y)
{
    /* cheating */
    const long z = (unsigned long)(unsigned int)x * (unsigned long)(unsigned int)y;
    return z >> 32;
}

unsigned int
unsigned_high_prod(unsigned int x, unsigned int y)
{
    return signed_high_prod(x, y);
}

void
hw02_75(void)
{
    assert(unsigned_high_prod(100, 20) == 0);
    assert(unsigned_high_prod(0xFFFFFFFF, 0xFFFFFFFF) == 0xFFFFFFFE);
    assert(unsigned_high_prod(0x8FFFFFFF, 0x2) == 0x1);
    printf("02.75 ... ok\n");
}

/* 02.76 */
void*
my_calloc(size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0) {
        return NULL;
    }

    void* buf = malloc(size * nmemb);

    if (buf == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size * nmemb; i++) {
        ((uint8_t*)buf)[i] = 0;
    }

    return buf;
}

void
hw02_76(void)
{
    assert(my_calloc(0, 100) == NULL);
    assert(my_calloc(10, 0) == NULL);

    int* buf = my_calloc(10, sizeof(int));
    for (size_t i = 0; i < 10; i++)
        assert(buf[i] == 0);

    double* bufd = my_calloc(32, sizeof(double));
    for (size_t i = 0; i < 32; i++)
        assert(bufd[i] == 0.0);

    printf("02.76 ... ok\n");
}

/* 02.77 */
int
mul_17(int x)
{
    return (x << 4) + x;
}
int
mul_m7(int x)
{
    return -(x << 3) + x;
}
int
mul_60(int x)
{
    return (x << 6) - (x << 2);
}
int
mul_m112(int x)
{
    return (x << 4) - (x << 7);
}

void
hw02_77(void)
{
    for (int i = 0; i < 1000; i++) {
        const int r = rand();
        assert(mul_17(r) == r * 17);
        assert(mul_m7(r) == r * (-7));
        assert(mul_60(r) == r * 60);
        assert(mul_m112(r) == r * (-112));
    }
    printf("02.77 ... ok\n");
}

/* 02.78 */
int
divide_power2(int x, int k)
{
    return x >> k;
}

void
hw02_78(void)
{
    assert(divide_power2(10, 0) == 10);
    assert(divide_power2(10, 1) == 5);
    assert(divide_power2(10, 2) == 2);
    assert(divide_power2(10, 3) == 1);
    assert(divide_power2(10, 4) == 0);
    printf("02.78 ... ok\n");
}

/* 02.79 */
int
mul3div4(int x)
{
    return ((x << 1) + x) >> 2;
}

void
hw02_79(void)
{
    assert(mul3div4(20) == 15);
    assert(mul3div4(-240) == -180);
    // assert(mul3div4(732777683) == 732777683 * 3 / 4);
    printf("02.79 ... ok\n");
}

/* 02.80 */
int
threefourths(int x)
{
    int y = x >> 2;
    y = (y << 1) + y;
    int z = x & 3;
    z = (z << 1) + z;
    z >>= 2;
    return y + z;
}

void
hw02_80(void)
{
    assert(threefourths(20) == 15);
    assert(threefourths(-240) == -180);
    assert(threefourths(732777683) == 732777683l * 3 / 4);
    for (int i = 0; i < 1000; i++) {
        const long r = rand();
        assert(threefourths(r) == r * 3 / 4);
    }

    printf("02.80 ... ok\n");
}

int
main()
{
    srand(0x12345678);
    hw02_55();

    hw02_58();
    hw02_59();
    hw02_60();
    hw02_61();
    hw02_62();
    hw02_63();
    hw02_64();
    hw02_65();
    hw02_66();
    hw02_67();
    hw02_68();
    hw02_69();
    hw02_70();
    hw02_71();
    hw02_72();
    hw02_73();
    hw02_74();
    hw02_75();
    hw02_76();
    hw02_77();
    hw02_78();
    hw02_79();
    hw02_80();

    return 0;
}
