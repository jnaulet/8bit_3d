#include "vec.h"
#include <math.h>

vec2 project_to_screen(vec3 v, float fov, float aspect_ratio) {
    float fov_rad = 1.0f / tanf(fov * 0.5f / 180.0f * M_PI);
    vec2 projected;
    projected.x = v.x * fov_rad * aspect_ratio / v.z;
    projected.y = v.y * fov_rad / v.z;
    return projected;
}

vec3 rotate_y(vec3 v, float angle) {
    float rad = angle * M_PI / 180.0f;
    vec3 rotated;
    rotated.x = v.x * cosf(rad) - v.z * sinf(rad);
    rotated.y = v.y;
    rotated.z = v.x * sinf(rad) + v.z * cosf(rad);
    return rotated;
}

vec3 rotate_x(vec3 v, float angle) {
    float rad = angle * M_PI / 180.0f;
    vec3 rotated;
    rotated.x = v.x;
    rotated.y = v.y * cosf(rad) - v.z * sinf(rad);
    rotated.z = v.y * sinf(rad) + v.z * cosf(rad);
    return rotated;
}

vec3 rotate_z(vec3 v, float angle) {
    float rad = angle *M_PI / 180.0f;
    vec3 rotated;
    rotated.x = v.x * cosf(rad) - v.y * sinf(rad);
    rotated.y = v.x * sinf(rad) + v.y * cosf(rad);
    rotated.z = v.z;
    return rotated;
}

vec3 add_vec3(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

vec3 sub_vec3(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}