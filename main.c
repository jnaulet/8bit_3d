#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "vec8.h"

#define VERTEX_COUNT 8

#define HOME "\x1b[H"
#define CLS  "\x1b[2J"

int main(void)
{
    /* *INDENT-OFF* */
    static struct vec8 vertex[VERTEX_COUNT] = {
        { -31, -31, -31 },      /* back-bottom-left */
        {  31, -31, -31 },      /* back-bottom-right */
        {  31,  31, -31 },      /* back-top-right */
        { -31,  31, -31 },      /* back-top-left */
        { -31, -31,  31 },      /* front-bottom-left */
        {  31, -31,  31 },      /* front-bottom-right */
        {  31,  31,  31 },      /* front-top-right */
        { -31,  31,  31 },      /* front-top-left */
    };
    /* *INDENT-ON* */

    for (;;) {
        for (rad8_t a = 0, b = 0, c = 0;;) {
            /* clear screen */
            fprintf(stderr, HOME CLS);
            fprintf(stderr, "a: %u\n", (unsigned) a);
            /* for each vertice */
            for (int i = VERTEX_COUNT; i-- != 0;) {
                struct vec8 v;
                (void) vec8_rotate_xyz(&v, &vertex[i], a, a, a);
                // (void) vec8_rotate_xy(&v, &vertex[i], a, a);
                // (void) vec8_project(&v, &v);
                /* crude projection */
                fprintf(stderr, "\x1b[%d;%df" "#", (v.y + 64) / 2, (v.x + 64));
            }

            /* render */
            // for (int i = VERTEX_COUNT; i-- != 0;)
            //    fprintf(stderr, "\x1b[%u;%uf" "#", v.y + 48, v.x + 32);

            /* next move */
            a++;
            b += (a & 1);
            c += (b & 1);

            /* x fps */
            (void) usleep((useconds_t) 50000);
        }
    }

    return 0;
}
