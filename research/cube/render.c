#include "render.h"

#include <sys/ioctl.h>
#include <stdlib.h>
#include <math.h>   
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "vec.h"

#define PIXEL_RATIO 4

struct termios orig_termios;

void reset_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

struct framebuffer* create_framebuffer() {
    tcgetattr(0, &orig_termios);
    atexit(reset_terminal);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);

    struct framebuffer* fb = (struct framebuffer*)malloc(sizeof(struct framebuffer));
    fb->width = ws.ws_col;
    fb->height = ws.ws_row;
    fb->pixels = (unsigned char*)malloc(fb->width * fb->height);

    for(int i = 0; i < fb->width * fb->height; i++) {
        fb->pixels[i] = ' ';
    }

    return fb;
}

void destroy_framebuffer(struct framebuffer* fb) {
    if (fb) {
        free(fb->pixels);
        free(fb);
    }
}

int map_x(float px, int width) { 
    int x = (int)((px + 1.0f) * 0.5f * (width - 1));
    if (x < 0) x = 0;
    if (x >= width) x = width - 1;
    return x;
}

int map_y(float py, int height) {
    // Compute distance from center
    float y_center = height / 2.0f;

    // Scale distance from center by pixel aspect
    float y_distance = -py * y_center * PIXEL_RATIO;

    // Map back to framebuffer coordinates
    int y = (int)(y_center + y_distance);

    if (y < 0) y = 0;
    if (y >= height) y = height - 1;
    return y;
}

void draw_pixel(struct framebuffer* fb, vec2 pos) {
    if(pos.x < -1.0f || pos.x > 1.0f || pos.y < -1.0f || pos.y > 1.0f)
        return;

    int x_draw = map_x(pos.x, fb->width);
    int y_draw = map_y(pos.y, fb->height);

    if(fabs(pos.x - 0.5f) < BLUR_RANGE) {
         fb->pixels[y_draw * fb->width + x_draw + ((0.5 - pos.x) > 0 ? 1 : -1)] = '#';
    }

    fb->pixels[y_draw * fb->width + x_draw] = '#';
}

void draw_line(struct framebuffer* fb, vec3 start, vec3 end) {
    vec2 p0 = project_to_screen(start, 90.0f, (float)fb->width / (float)fb->height);
    vec2 p1 = project_to_screen(end, 90.0f, (float)fb->width / (float)fb->height);

    // Projecting to screen coordinates
    int x0 = map_x(p0.x, fb->width);
    int y0 = map_y(p0.y, fb->height);
    int x1 = map_x(p1.x, fb->width);
    int y1 = map_y(p1.y, fb->height);

    // Calculate deltas (direction + length to move for slope error) and steps (direction to move for the pixel coords)
    int delta_x = abs(x1 - x0);
    int step_x = x0 < x1 ? 1 : -1;
    int delta_y = -abs(y1 - y0);
    int step_y = y0 < y1 ? 1 : -1;

    // Calculate initilal slope error
    int slope_error = delta_x + delta_y;
    int slope_double;

    while(1) {
        //Checking if pixel is within framebuffer bounds
        if(x0 >= 0 && x0 < fb->width && y0 >= 0 && y0 < fb->height)
            fb->pixels[y0 * fb->width + x0] = '#';

        // Checking if we reached the end point
        if(x0 == x1 && y0 == y1) break;

        slope_double = 2 * slope_error;
        if(slope_double >= delta_y) {
            slope_error += delta_y;
            x0 += step_x;
        }
        if(slope_double <= delta_x) {
            slope_error += delta_x;
            y0 += step_y;
        }
    }
}

void render(struct framebuffer* fb) {
    printf("\x1b[?1049h");
    printf("\x1b[H");  // move cursor home
    for(int y = 0; y < fb->height; y++) {
        fwrite(&fb->pixels[y * fb->width], 1, fb->width, stdout);
        putchar('\n'); // newline at end of row
    }
    fflush(stdout);
    printf("\x1b[?1049l");

    // clear framebuffer
    for(int i = 0; i < fb->width * fb->height; i++)
        fb->pixels[i] = ' ';
}