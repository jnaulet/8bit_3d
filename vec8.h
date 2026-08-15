#ifndef VEC8_H
#define VEC8_H

#include <stdint.h>

typedef int8_t ub8_t;   /* 8bit unit ball: -63 -> -1.0, 63 -> 1.0 */
typedef uint8_t rad8_t; /* 8bit radian: 0 ->  0, 255 -> 2PI */

struct vec8 {
    ub8_t x;
    ub8_t y;
    ub8_t z;
};

struct vec8 *vec8_rotate_x(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, rad8_t angle);
struct vec8 *vec8_rotate_y(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, rad8_t angle);
struct vec8 *vec8_rotate_z(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, rad8_t angle);
struct vec8 *vec8_rotate_xy(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, rad8_t ax, rad8_t ay);
struct vec8 *vec8_rotate_xyz(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, rad8_t ax, rad8_t ay, rad8_t az);

struct vec8 *vec8_translate_x(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, ub8_t x, ub8_t y, ub8_t z);
struct vec8 *vec8_scale(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, ub8_t scale);

#endif
