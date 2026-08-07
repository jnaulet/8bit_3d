#include "render.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(void) {
    struct framebuffer* fb = create_framebuffer();
    int milliseconds = 1000 / FPS;

    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000L;

    vec3 cube_vertices[8] = {
        { -0.5f, -0.5f, -0.5f }, // back-bottom-left
        {  0.5f, -0.5f, -0.5f }, // back-bottom-right
        {  0.5f,  0.5f, -0.5f }, // back-top-right
        { -0.5f,  0.5f, -0.5f }, // back-top-left
        { -0.5f, -0.5f,  0.5f }, // front-bottom-left
        {  0.5f, -0.5f,  0.5f }, // front-bottom-right
        {  0.5f,  0.5f,  0.5f }, // front-top-right
        { -0.5f,  0.5f,  0.5f }  // front-top-left
    };
    int cube_edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // back face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // front face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // side edges
    };

    vec3 position = {0.0f, 0.0f, 3.0f};
    vec3 cube_position = {0.0f, 0.0f, 3};
    
    float yaw = 0.0f;
    float pitch = 0.0f;

    float cube_y_angle = 0.0f;
    float cube_x_angle = 0.0f;

    while(1) {
        for(int i = 0; i < 12; i++) {
                vec3 start = cube_vertices[cube_edges[i][0]];
                vec3 end   = cube_vertices[cube_edges[i][1]];

                // model rotation
                start = rotate_y(start, cube_y_angle);
                start = rotate_x(start, cube_x_angle);
                end = rotate_y(end, cube_y_angle);
                end = rotate_x(end, cube_x_angle);

                // model translation
                start = add_vec3(start, cube_position);
                end = add_vec3(end, cube_position);
                
                // camera transform (world → camera)
                start = sub_vec3(start, position);
                start = rotate_y(start, -yaw);
                start = rotate_x(start, -pitch);

                end = sub_vec3(end, position);
                end = rotate_y(end, -yaw);
                end = rotate_x(end, -pitch);

                if (start.z <= 0 || end.z <= 0) continue;

                draw_line(fb, start, end);
        }

        char buf[3];
        ssize_t n = read(STDIN_FILENO, &buf, 3);
        if (n > 0 && n != 3) {
            switch (buf[0])
            {
            case 'w':
                position.z += 0.1f;
                break;
            case 's':
                position.z -= 0.1f;
                break;
            case 'a':
                position.x -= 0.1f;
                break;
            case 'd':
                position.x += 0.1f;
                break;
            default:
                break;
            }
        }
        if (n == 3 && buf[0] == '\x1b' && buf[1] == '[') {
            switch (buf[2]) {
            case 'A': // Up
                pitch -= 2.0f;
                break;
            case 'B': // Down
                pitch += 2.0f;
                break;
            case 'C': // Right
                yaw -= 2.0f;
                break;
            case 'D': // Left
                yaw += 2.0f;
                break;
            }
        }

        cube_y_angle += 1.0f;
        cube_x_angle += 0.5f;

        render(fb);

        nanosleep(&ts, NULL);
    }

    destroy_framebuffer(fb);
    return 0;
}
