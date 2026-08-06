#ifndef VEC8_H
#define VEC8_H

#include <stdint.h>

typedef int8_t rad8_t;

struct vec8 {
  int8_t x;
  int8_t y;
  int8_t z;
};

struct vec8 *vec8_rotate(/*@returned@*/ struct vec8 *ctx, rad8_t angle);
struct vec8 *vec8_translate(/*@returned@*/ struct vec8 *ctx, const struct vec8 *t);
// struct vec8 *vec8_scale(/*@returned@*/ struct vec8 *ctx, int8_t scale);
// struct vec8 *vec8_project(/*@returned@*/ struct vec8 *ctx);

#endif
