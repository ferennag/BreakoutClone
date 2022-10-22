#pragma once

#include <stdbool.h>

typedef union Vec3 {
    struct {
        float x, y, z;
    };
    float xyz[3];
} Vec3;

Vec3 Vec3_init(float x, float y, float z);
Vec3 Vec3_zeroes();
Vec3 Vec3_ones();
Vec3 Vec3_up();
Vec3 Vec3_copy(const Vec3 other);
bool Vec3_eq(const Vec3 a, const Vec3 b);

Vec3 Vec3_add(const Vec3 a, const Vec3 b);
Vec3 Vec3_sub(const Vec3 a, const Vec3 b);
Vec3 Vec3_mul(const Vec3 a, const Vec3 b);
Vec3 Vec3_div(const Vec3 a, const Vec3 b);

Vec3 Vec3_adds(const Vec3 a, const float scalar);
Vec3 Vec3_subs(const Vec3 a, const float scalar);
Vec3 Vec3_muls(const Vec3 a, const float scalar);
Vec3 Vec3_divs(const Vec3 a, const float scalar);

float Vec3_dot(const Vec3 a, const Vec3 b);
Vec3 Vec3_cross(const Vec3 a, const Vec3 b);

float Vec3_magnitude(const Vec3 a);
Vec3 Vec3_negate(const Vec3 a);
Vec3 Vec3_normalize(const Vec3 a);
Vec3 Vec3_clamp(const Vec3 a, const Vec3 min, const Vec3 max);