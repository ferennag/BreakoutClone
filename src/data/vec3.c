#include <string.h>
#include <math.h>
#include "util/math.h"
#include "util/float.h"
#include "data/vec3.h"

Vec3 Vec3_init(float x, float y, float z)
{
    Vec3 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

Vec3 Vec3_zeroes()
{
    return Vec3_init(0, 0, 0);
}

Vec3 Vec3_ones()
{
    return Vec3_init(1, 1, 1);
}

Vec3 Vec3_up()
{
    return Vec3_init(0, 1, 0);
}

Vec3 Vec3_copy(const Vec3 other)
{
    return Vec3_init(other.x, other.y, other.z);
}

bool Vec3_eq(const Vec3 a, const Vec3 b)
{
    return (
        float_eq(a.x, b.x) &&
        float_eq(a.y, b.y) &&
        float_eq(a.z, b.z)
    );
}

Vec3 Vec3_add(const Vec3 a, const Vec3 b)
{
    return Vec3_init(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    );
}

Vec3 Vec3_sub(const Vec3 a, const Vec3 b)
{
    return Vec3_init(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    );
}

Vec3 Vec3_mul(const Vec3 a, const Vec3 b)
{
    return Vec3_init(
        a.x * b.x,
        a.y * b.y,
        a.z * b.z
    );
}

Vec3 Vec3_div(const Vec3 a, const Vec3 b)
{
    return Vec3_init(
        a.x / b.x,
        a.y / b.y,
        a.z / b.z
    );
}

Vec3 Vec3_adds(const Vec3 a, const float scalar)
{
    return Vec3_init(
        a.x + scalar,
        a.y + scalar,
        a.z + scalar
    );
}

Vec3 Vec3_subs(const Vec3 a, const float scalar)
{
    return Vec3_init(
        a.x - scalar,
        a.y - scalar,
        a.z - scalar
    );
}

Vec3 Vec3_muls(const Vec3 a, const float scalar)
{
    return Vec3_init(
        a.x * scalar,
        a.y * scalar,
        a.z * scalar
    );
}

Vec3 Vec3_divs(const Vec3 a, const float scalar)
{
    return Vec3_init(
        a.x / scalar,
        a.y / scalar,
        a.z / scalar
    );
}

float Vec3_dot(const Vec3 a, const Vec3 b)
{
    return (
        a.x * b.x +
        a.y * b.y +
        a.z * b.z
    );
}

Vec3 Vec3_cross(const Vec3 a, const Vec3 b)
{
    return Vec3_init(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

float Vec3_magnitude(const Vec3 a)
{
    return sqrtf(
        powf(a.x, 2) +
        powf(a.y, 2) +
        powf(a.z, 2)
    );
}

Vec3 Vec3_negate(const Vec3 a)
{
    return Vec3_init(
        -a.x,
        -a.y,
        -a.z
    );
}

Vec3 Vec3_normalize(const Vec3 a)
{
    float magnitude = Vec3_magnitude(a);
    return Vec3_divs(a, magnitude);
}

Vec3 Vec3_clamp(const Vec3 a, const Vec3 min, const Vec3 max)
{
    Vec3 result = Vec3_zeroes();
    result.x = clamp(a.x, min.x, max.x);
    result.y = clamp(a.y, min.y, max.y);
    result.z = clamp(a.z, min.z, max.z);
    return result;
}