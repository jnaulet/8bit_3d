#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "vec8.h"

int main(void)
{
  static struct vec8 cube_vertices[8] = {
    { -31, -31, -31 }, /* back-bottom-left */
    {  31, -31, -31 }, /* back-bottom-right */
    {  31,  31, -31 }, /* back-top-right */
    { -31,  31, -31 }, /* back-top-left */
    { -31, -31,  31 }, /* front-bottom-left */
    {  31, -31,  31 }, /* front-bottom-right */
    {  31,  31,  31 }, /* front-top-right */
    { -31,  31,  31 }, /* front-top-left */
  };
  
  static int cube_edges[12][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0}, /* back face */
    {4, 5}, {5, 6}, {6, 7}, {7, 4}, /* front face */
    {0, 4}, {1, 5}, {2, 6}, {3, 7}  /* side edges */
  };

  
  
    return 0;
}
