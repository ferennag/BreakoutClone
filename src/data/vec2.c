#include <string.h>
#include <math.h>
#include "util/math.h"
#include "util/float.h"
#include "data/vec2.h"

Vec2 Vec2_init(float x, float y)
{
    Vec2 result;
    result.x = x;
    result.y = y;
    return result;
}

Vec2 Vec2_zeroes()
{
    return Vec2_init(0, 0);
}

Vec2 Vec2_ones()
{
    return Vec2_init(1, 1);
}

Vec2 Vec2_up()
{
    return Vec2_init(0, 1);
}

Vec2 Vec2_copy(const Vec2 other)
{
    return Vec2_init(other.x, other.y);
}

bool Vec2_eq(const Vec2 a, const Vec2 b)
{
    return (
        float_eq(a.x, b.x) &&
        float_eq(a.y, b.y)
    );
}

Vec2 Vec2_add(const Vec2 a, const Vec2 b)
{
    return Vec2_init(
        a.x + b.x,
        a.y + b.y
    );
}

Vec2 Vec2_sub(const Vec2 a, const Vec2 b)
{
    return Vec2_init(
        a.x - b.x,
        a.y - b.y
    );
}

Vec2 Vec2_mul(const Vec2 a, const Vec2 b)
{
    return Vec2_init(
        a.x * b.x,
        a.y * b.y
    );
}

Vec2 Vec2_div(const Vec2 a, const Vec2 b)
{
    return Vec2_init(
        a.x / b.x,
        a.y / b.y
    );
}

Vec2 Vec2_adds(const Vec2 a, const float scalar)
{
    return Vec2_init(
        a.x + scalar,
        a.y + scalar
    );
}

Vec2 Vec2_subs(const Vec2 a, const float scalar)
{
    return Vec2_init(
        a.x - scalar,
        a.y - scalar
    );
}

Vec2 Vec2_muls(const Vec2 a, const float scalar)
{
    return Vec2_init(
        a.x * scalar,
        a.y * scalar
    );
}

Vec2 Vec2_divs(const Vec2 a, const float scalar)
{
    return Vec2_init(
        a.x / scalar,
        a.y / scalar
    );
}

float Vec2_dot(const Vec2 a, const Vec2 b)
{
    return (
        a.x * b.x +
        a.y * b.y
    );
}

float Vec2_cross(const Vec2 a, const Vec2 b)
{
    return a.x * b.y - a.y * b.x;
}

float Vec2_magnitude(const Vec2 a)
{
    return sqrtf(
        powf(a.x, 2) +
        powf(a.y, 2)
    );
}

Vec2 Vec2_negate(const Vec2 a)
{
    return Vec2_init(
        -a.x,
        -a.y
    );
}

Vec2 Vec2_normalize(const Vec2 a)
{
    float magnitude = Vec2_magnitude(a);
    return Vec2_divs(a, magnitude);
}

Vec2 Vec2_clamp(const Vec2 a, const Vec2 min, const Vec2 max)
{
    Vec2 result = Vec2_zeroes();
    result.x = clamp(a.x, min.x, max.x);
    result.y = clamp(a.y, min.y, max.y);
    return result;
}