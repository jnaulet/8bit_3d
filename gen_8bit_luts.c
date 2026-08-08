#include <stdio.h>
#include <math.h>

#define PI      3.141592654
#define RAD_MAX (PI * 2.0)

/*
 * We arbitrarily determine that 1 full circle is 256 'rad8_t' 
 */
typedef unsigned char rad8_t;

static rad8_t rad_to_rad8(double rad)
{
  return (rad8_t) (rad / RAD_MAX) * 256.0;
}

static double rad_from_rad8(rad8_t rad8)
{
  return (double)rad8 / 256.0 * RAD_MAX;
}

#define LIMIT_L -63
#define LIMIT_H 63

#define SIN_COS_COUNT 256
#define QSMUL_COUNT   128
#define ABS_COUNT     256
#define DIV_COUNT     64

/*
 * 2D rotation
 * xp = x * cos(a) - y * sin(a)
 * yp = x * sin(a) + y * cos(a)
 */

int main(void)
{
  /*
   * Generate vector LUT for rotation
   */
  
  /* SIN */
  printf("static const int8_t sin8[%d] = {", SIN_COS_COUNT);
  for(int r = 0; r < SIN_COS_COUNT; r++){
    double rad = rad_from_rad8((rad8_t)r);
    if(!(r % 16)) printf("\n    ");
    printf("%3.0lf, ", sin(rad) * LIMIT_H);
  }
  printf("\n");
  printf("};");
  printf("\n\n");

  /* COS */
  printf("static const int8_t cos8[%d] = {", SIN_COS_COUNT);
  for(int r = 0; r < SIN_COS_COUNT; r++){
    double rad = rad_from_rad8((rad8_t)r);
    if(!(r % 16)) printf("\n    ");
    printf("%3.0lf, ", cos(rad) * LIMIT_H);
  }
  printf("\n");
  printf("};");
  printf("\n\n");

  /* TAN */
  printf("static const int8_t tan8[%d] = {", SIN_COS_COUNT);
  for(int r = 0; r < SIN_COS_COUNT; r++){
    double rad = rad_from_rad8((rad8_t)r);
    if(!(r % 16)) printf("\n    ");
    printf("%3.0lf, ", tan(rad) * LIMIT_H);
  }
  printf("\n");
  printf("};");
  printf("\n\n");

  /* ABS */
  printf("static const int8_t abs8[%d] = {", ABS_COUNT);
  for(int a = 0; a < ABS_COUNT; a++){
    if(!(a % 16)) printf("\n    ");
    if(a < 128) printf("%3u, ", a);
    else printf("%3u, ", ABS_COUNT - a);
  }
  printf("\n");
  printf("};");
  printf("\n\n");
  
  /* QSMUL */
  // =BITAND(BITRSHIFT(FLOOR(POWER(B17; 2)/4); 7); 127)
  printf("static const int8_t qsmul8[%d] = {", QSMUL_COUNT);
  for(int m = 0; m < QSMUL_COUNT; m++){
    if(!(m % 16)) printf("\n    ");
    printf("%3u, ", 0xffu & (((m * m) / 4) >> 7));
  }
  printf("\n");
  printf("};");
  printf("\n\n");

  /* DIV8 */
  printf("static const int8_t div8[%d] = {", DIV_COUNT);
  for(int d = 0; d < DIV_COUNT; d++){
    if(!(d % 16)) printf("\n    ");
    printf("%3u, ", 64 / (d + 1));
  }
  printf("\n");
  printf("};");
  printf("\n\n");

  printf("#define SIN8(x)      (sin8[(x)])\n");
  printf("#define COS8(x)      (cos8[(x)])\n");
  printf("#define TAN8(x)      (tan8[(x)])\n");
  printf("#define ABS8(x)      (abs8[(uint8_t)(x)])\n");
  printf("#define QSMUL8(a, b) (qsmul8[ABS8(a + b)] - qsmul8[ABS8(a - b)])\n");
  printf("#define DIV8(a, b)   QSMUL8(a, div8[(b)])\n");
  printf("\n");
  
  return 0;
}
