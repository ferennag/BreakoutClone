#pragma once

#include <stdbool.h>
#include "data/vec3.h"
#include "data/mat3.h"

typedef union Mat4 {
    float m[4][4];
} Mat4;

void Mat4_print(Mat4 m);
Mat4 Mat4_identity();
Mat4 Mat4_zeroes();
Mat4 Mat4_copy(const Mat4 other);
Mat4 Mat4_create(float *values);
bool Mat4_eq(const Mat4 m1, const Mat4 m2);

Mat4 Mat4_transpose(const Mat4 m);
Mat3 Mat4_minor(const Mat4 mat, unsigned int row, unsigned int col);
float Mat4_det(const Mat4 m);
Mat4 Mat4_inverse(const Mat4 m);

Mat4 Mat4_mul(const Mat4 a, const Mat4 b);

Mat4 Mat4_divs(const Mat4 a, const float scalar);

Mat4 Mat4_translate(const Vec3 values);
Mat4 Mat4_scale(const Vec3 values);
Mat4 Mat4_rotateX(float rad);
Mat4 Mat4_rotateY(float rad);
Mat4 Mat4_rotateZ(float rad);
Mat4 Mat4_perspective(float fov, float aspect, float zNear, float zFar);
Mat4 Mat4_orthographic(int left, int right, int bottom, int top, float near, float far);