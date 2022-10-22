#pragma once

#include <stdbool.h>

typedef union Vec2 {
    struct {
        float x, y;
    };
    float xy[2];
} Vec2;

Vec2 Vec2_init(float x, float y);
Vec2 Vec2_zeroes();
Vec2 Vec2_ones();
Vec2 Vec2_up();
Vec2 Vec2_copy(const Vec2 other);
bool Vec2_eq(const Vec2 a, const Vec2 b);

Vec2 Vec2_add(const Vec2 a, const Vec2 b);
Vec2 Vec2_sub(const Vec2 a, const Vec2 b);
Vec2 Vec2_mul(const Vec2 a, const Vec2 b);
Vec2 Vec2_div(const Vec2 a, const Vec2 b);

Vec2 Vec2_adds(const Vec2 a, const float scalar);
Vec2 Vec2_subs(const Vec2 a, const float scalar);
Vec2 Vec2_muls(const Vec2 a, const float scalar);
Vec2 Vec2_divs(const Vec2 a, const float scalar);

float Vec2_dot(const Vec2 a, const Vec2 b);
float Vec2_cross(const Vec2 a, const Vec2 b);

float Vec2_magnitude(const Vec2 a);
Vec2 Vec2_negate(const Vec2 a);
Vec2 Vec2_normalize(const Vec2 a);
Vec2 Vec2_clamp(const Vec2 a, const Vec2 min, const Vec2 max);