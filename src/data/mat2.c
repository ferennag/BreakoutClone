#include "data/mat2.h"

float Mat2_det(Mat2 mat)
{
    return mat.m[0][0] * mat.m[1][1] - mat.m[0][1] * mat.m[1][0];
}