#ifndef RENDER_H
#define RENDER_H

#define BLUR_RANGE 0.2f
#define FPS 30

#include "vec.h"

struct framebuffer {
    int width;
    int height;
    unsigned char* pixels;
};

//help functions
int map_x(float px, int width);
int map_y(float py, int height);

//framebuffer management
struct framebuffer* create_framebuffer();
void destroy_framebuffer(struct framebuffer* fb);

//drawing functions
void draw_pixel(struct framebuffer* fb, vec2 pos);
void draw_line(struct framebuffer* fb, vec3 start, vec3 end);

void render(struct framebuffer* fb);

#endif // RENDER_H