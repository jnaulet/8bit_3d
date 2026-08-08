#ifndef VEC8_H
#define VEC8_H

#include <stdint.h>

typedef uint8_t rad8_t;

struct vec8 {
    int8_t x;
    int8_t y;
    int8_t z;
};

struct vec8 *vec8_rotate_x(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, rad8_t angle);
struct vec8 *vec8_rotate_y(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, rad8_t angle);
struct vec8 *vec8_rotate_z(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, rad8_t angle);

struct vec8 *vec8_rotate_xy(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, rad8_t ax, rad8_t ay);
struct vec8 *vec8_rotate_xyz(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, rad8_t ax, rad8_t ay, rad8_t az);

struct vec8 *vec8_translate_x(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, int8_t x);
struct vec8 *vec8_translate_y(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, int8_t y);
struct vec8 *vec8_translate_z(/*@returned@*/ struct vec8 *dst, const struct vec8 *src, int8_t z);

#endif
