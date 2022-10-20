#pragma once

#include "data/mat2.h"

typedef union Mat3 {
    float m[3][3];
} Mat3;

Mat3 Mat3_create(float *values);

Mat2 Mat3_minor(const Mat3 mat, unsigned int row, unsigned int col);
float Mat3_det(const Mat3 mat);