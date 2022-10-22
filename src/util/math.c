#include "util/math.h"

float deg_to_rad(float deg)
{
    return deg * (M_PI / 180.0f);
}

float mymax(float left, float right)
{
    return left < right ? right : left;
}

float mymin(float left, float right)
{
    return left < right ? left : right;
}

float clamp(float value, float min, float max)
{
    return mymax(min, mymin(max, value));
}