#pragma once

typedef union Mat2 {
    float m[2][2];
} Mat2;

float Mat2_det(Mat2 mat);