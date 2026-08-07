#ifndef VEC_H
#define VEC_H

typedef struct {
    float x;
    float y;
    float z;
} vec3;

typedef struct {
    float x;
    float y;
} vec2;

vec2 project_to_screen(vec3 v, float fov, float aspect_ratio);
vec3 rotate_y(vec3 v, float angle);
vec3 rotate_x(vec3 v, float angle);
vec3 rotate_z(vec3 v, float angle);
vec3 add_vec3(vec3 a, vec3 b);
vec3 sub_vec3(vec3 a, vec3 b);

#endif // VEC_H