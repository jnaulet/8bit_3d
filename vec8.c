#include "vec8.h"

/* *INDENT-OFF* */
static const int8_t sin8[256] = {
      0,   2,   3,   5,   6,   8,   9,  11,  12,  14,  15,  17,  18,  20,  21,  23, 
     24,  26,  27,  28,  30,  31,  32,  34,  35,  36,  38,  39,  40,  41,  42,  43, 
     45,  46,  47,  48,  49,  50,  51,  52,  52,  53,  54,  55,  56,  56,  57,  58, 
     58,  59,  59,  60,  60,  61,  61,  61,  62,  62,  62,  63,  63,  63,  63,  63, 
     63,  63,  63,  63,  63,  63,  62,  62,  62,  61,  61,  61,  60,  60,  59,  59, 
     58,  58,  57,  56,  56,  55,  54,  53,  52,  52,  51,  50,  49,  48,  47,  46, 
     45,  43,  42,  41,  40,  39,  38,  36,  35,  34,  32,  31,  30,  28,  27,  26, 
     24,  23,  21,  20,  18,  17,  15,  14,  12,  11,   9,   8,   6,   5,   3,   2, 
     -0,  -2,  -3,  -5,  -6,  -8,  -9, -11, -12, -14, -15, -17, -18, -20, -21, -23, 
    -24, -26, -27, -28, -30, -31, -32, -34, -35, -36, -38, -39, -40, -41, -42, -43, 
    -45, -46, -47, -48, -49, -50, -51, -52, -52, -53, -54, -55, -56, -56, -57, -58, 
    -58, -59, -59, -60, -60, -61, -61, -61, -62, -62, -62, -63, -63, -63, -63, -63, 
    -63, -63, -63, -63, -63, -63, -62, -62, -62, -61, -61, -61, -60, -60, -59, -59, 
    -58, -58, -57, -56, -56, -55, -54, -53, -52, -52, -51, -50, -49, -48, -47, -46, 
    -45, -43, -42, -41, -40, -39, -38, -36, -35, -34, -32, -31, -30, -28, -27, -26, 
    -24, -23, -21, -20, -18, -17, -15, -14, -12, -11,  -9,  -8,  -6,  -5,  -3,  -2, 
};

static const int8_t cos8[256] = {
     63,  63,  63,  63,  63,  63,  62,  62,  62,  61,  61,  61,  60,  60,  59,  59, 
     58,  58,  57,  56,  56,  55,  54,  53,  52,  52,  51,  50,  49,  48,  47,  46, 
     45,  43,  42,  41,  40,  39,  38,  36,  35,  34,  32,  31,  30,  28,  27,  26, 
     24,  23,  21,  20,  18,  17,  15,  14,  12,  11,   9,   8,   6,   5,   3,   2, 
     -0,  -2,  -3,  -5,  -6,  -8,  -9, -11, -12, -14, -15, -17, -18, -20, -21, -23, 
    -24, -26, -27, -28, -30, -31, -32, -34, -35, -36, -38, -39, -40, -41, -42, -43, 
    -45, -46, -47, -48, -49, -50, -51, -52, -52, -53, -54, -55, -56, -56, -57, -58, 
    -58, -59, -59, -60, -60, -61, -61, -61, -62, -62, -62, -63, -63, -63, -63, -63, 
    -63, -63, -63, -63, -63, -63, -62, -62, -62, -61, -61, -61, -60, -60, -59, -59, 
    -58, -58, -57, -56, -56, -55, -54, -53, -52, -52, -51, -50, -49, -48, -47, -46, 
    -45, -43, -42, -41, -40, -39, -38, -36, -35, -34, -32, -31, -30, -28, -27, -26, 
    -24, -23, -21, -20, -18, -17, -15, -14, -12, -11,  -9,  -8,  -6,  -5,  -3,  -2, 
      0,   2,   3,   5,   6,   8,   9,  11,  12,  14,  15,  17,  18,  20,  21,  23, 
     24,  26,  27,  28,  30,  31,  32,  34,  35,  36,  38,  39,  40,  41,  42,  43, 
     45,  46,  47,  48,  49,  50,  51,  52,  52,  53,  54,  55,  56,  56,  57,  58, 
     58,  59,  59,  60,  60,  61,  61,  61,  62,  62,  62,  63,  63,  63,  63,  63, 
};

static const int8_t abs8[256] = {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15, 
     16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31, 
     32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47, 
     48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63, 
     64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79, 
     80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95, 
     96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 
    128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 
    112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100,  99,  98,  97, 
     96,  95,  94,  93,  92,  91,  90,  89,  88,  87,  86,  85,  84,  83,  82,  81, 
     80,  79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66,  65, 
     64,  63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53,  52,  51,  50,  49, 
     48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,  37,  36,  35,  34,  33, 
     32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17, 
     16,  15,  14,  13,  12,  11,  10,   9,   8,   7,   6,   5,   4,   3,   2,   1, 
};

static const int8_t qsmul8[128] = {
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1, 
      1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   3,   3,   3,   3,   4, 
      4,   4,   4,   5,   5,   5,   5,   6,   6,   6,   7,   7,   7,   8,   8,   9, 
      9,   9,  10,  10,  10,  11,  11,  12,  12,  13,  13,  14,  14,  15,  15,  16, 
     16,  17,  17,  18,  18,  19,  19,  20,  20,  21,  21,  22,  23,  23,  24,  25, 
     25,  26,  26,  27,  28,  28,  29,  30,  30,  31,  32,  33,  33,  34,  35,  36, 
     36,  37,  38,  39,  39,  40,  41,  42,  43,  43,  44,  45,  46,  47,  48,  49, 
     49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64, 
};

static const int8_t div8[64] = {
     64,  32,  21,  16,  12,  10,   9,   8,   7,   6,   5,   5,   4,   4,   4,   4, 
      3,   3,   3,   3,   3,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2, 
      1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1, 
      1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1, 
};

#define SIN8(x)      (sin8[(x)])
#define COS8(x)      (cos8[(x)])
#define ABS8(x)      (abs8[(uint8_t)(x)])
#define QSMUL8(a, b) (qsmul8[ABS8(a + b)] - qsmul8[ABS8(a - b)])
#define DIV8(a, b)   QSMUL8(a, div8[(b)])

/* *INDENT-ON* */

struct vec8 *vec8_rotate_x(struct vec8 *dst, const struct vec8 *src, rad8_t angle)
{
    int8_t cos = COS8(angle);
    int8_t sin = SIN8(angle);
    int8_t yp = QSMUL8(src->y, cos) - QSMUL8(src->z, sin);
    int8_t zp = QSMUL8(src->y, sin) + QSMUL8(src->z, cos);

    dst->x = src->x;
    dst->y = yp;
    dst->z = zp;

    return dst;
}

struct vec8 *vec8_rotate_y(struct vec8 *dst, const struct vec8 *src, rad8_t angle)
{
    int8_t cos = COS8(angle);
    int8_t sin = SIN8(angle);
    int8_t xp = QSMUL8(src->x, cos) - QSMUL8(src->z, sin);
    int8_t zp = QSMUL8(src->x, sin) + QSMUL8(src->z, cos);

    dst->x = xp;
    dst->y = src->y;
    dst->z = zp;

    return dst;
}

struct vec8 *vec8_rotate_z(struct vec8 *dst, const struct vec8 *src, rad8_t angle)
{
    int8_t cos = COS8(angle);
    int8_t sin = SIN8(angle);
    int8_t xp = QSMUL8(src->x, cos) - QSMUL8(src->y, sin);
    int8_t yp = QSMUL8(src->x, sin) + QSMUL8(src->y, cos);

    dst->x = xp;
    dst->y = yp;
    dst->z = src->z;

    return dst;
}

struct vec8 *vec8_rotate_xy(struct vec8 *dst, const struct vec8 *src, rad8_t ax, rad8_t ay)
{
    int8_t cosx = COS8(ax);
    int8_t sinx = SIN8(ax);
    int8_t cosy = COS8(ay);
    int8_t siny = SIN8(ay);

    int8_t xp = QSMUL8(src->x, cosy) - QSMUL8(src->z, siny);
    int8_t zp = QSMUL8(src->x, siny) + QSMUL8(src->z, cosy);
    int8_t yp = QSMUL8(src->y, cosx) - QSMUL8(zp, sinx);

    dst->x = xp;
    dst->y = yp;
    dst->z = QSMUL8(src->y, sinx) + QSMUL8(zp, cosx);

    return dst;
}

struct vec8 *vec8_rotate_xyz(struct vec8 *dst, const struct vec8 *src, rad8_t ax, rad8_t ay,
                             rad8_t az)
{
    int8_t cosx = COS8(ax);
    int8_t sinx = SIN8(ax);
    int8_t cosy = COS8(ay);
    int8_t siny = SIN8(ay);
    int8_t cosz = COS8(az);
    int8_t sinz = SIN8(az);

    int8_t xp = QSMUL8(src->x, cosy) - QSMUL8(src->z, siny);
    int8_t zp = QSMUL8(src->x, siny) + QSMUL8(src->z, cosy);
    int8_t yp = QSMUL8(src->y, cosx) - QSMUL8(zp, sinx);

    dst->x = QSMUL8(xp, cosz) - QSMUL8(yp, sinz);
    dst->y = QSMUL8(xp, sinz) + QSMUL8(yp, cosz);
    dst->z = QSMUL8(src->y, sinx) + QSMUL8(zp, cosx);

    return dst;
}

struct vec8 *vec8_translate_x(struct vec8 *dst, const struct vec8 *src, int8_t x)
{
    dst->x = src->x + x;
    return dst;
}

struct vec8 *vec8_translate_y(struct vec8 *dst, const struct vec8 *src, int8_t y)
{
    dst->y = src->y + y;
    return dst;
}

struct vec8 *vec8_translate_z(struct vec8 *dst, const struct vec8 *src, int8_t z)
{
    dst->z = src->z + z;
    return dst;
}

struct vec8 *vec8_scale(struct vec8 *dst, const struct vec8 *src, ub8_t scale)
{
    dst->x = QSMUL8(src->x, scale);
    dst->y = QSMUL8(src->y, scale);
    dst->z = QSMUL8(src->z, scale);
    return dst;
}

struct vec8 *vec8_project(struct vec8 *dst, const struct vec8 *src)
{
    dst->x = DIV8(src->x, src->z);
    dst->y = DIV8(src->y, src->z);
    dst->z = 0;

    return dst;
}

#ifdef UNIT_TEST

#include <stdio.h>

int main(void)
{
    /* primitives */

    /* ABS8 */
    printf("ABS8(%d): %d\n", -63, ABS8(-63));
    printf("ABS8(%d): %d\n", -32, ABS8(-32));
    printf("ABS8(%d): %d\n", -7, ABS8(-7));
    printf("ABS8(%d): %d\n", -1, ABS8(-1));

    /* QSMUL8 */
    printf("QSMUL8(%d, %d): %d\n", 63, 63, QSMUL8(63, 63));
    printf("QSMUL8(%d, %d): %d\n", 63, 32, QSMUL8(63, 32));
    printf("QSMUL8(%d, %d): %d\n", 63, 16, QSMUL8(63, 16));
    printf("QSMUL8(%d, %d): %d\n", 63, 8, QSMUL8(63, 8));
    printf("QSMUL8(%d, %d): %d\n", 32, 32, QSMUL8(32, 32));
    printf("QSMUL8(%d, %d): %d\n", 16, 16, QSMUL8(16, 16));

    printf("DIV8(63, 63): %d\n", DIV8(63, 63));
    printf("DIV8(63, 32): %d\n", DIV8(63, 32));

    return 0;
}

#endif
