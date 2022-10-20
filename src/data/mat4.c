#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "util/float.h"
#include "data/mat3.h"
#include "data/mat4.h"

void Mat4_print(Mat4 m) {
    for(unsigned int i=0; i < 4; ++i) {
        for(unsigned int j=0; j < 4; ++j) {
            printf("%2.3f\t", m.m[i][j]);
        }
        printf("\n");
    }
}

Mat4 Mat4_identity()
{
    Mat4 mat = {
        .m = {
            {1, 0, 0, 0},
            {0, 1, 0 ,0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        }
    };

    return mat;
}

Mat4 Mat4_zeroes()
{
    Mat4 mat = {
        .m = {
            {0, 0, 0, 0},
            {0, 0, 0 ,0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    };

    return mat;
}

Mat4 Mat4_copy(const Mat4 other)
{
    Mat4 mat;
    memcpy(mat.m, other.m, 4 * 4 * sizeof(float));
    return mat;
}

Mat4 Mat4_create(float *values) {
    Mat4 m = Mat4_zeroes();

    for(unsigned int i=0; i < 4; ++i) {
        for(unsigned int j=0; j < 4; ++j) {
            m.m[i][j] = values[i * 4 + j];
        }
    }

    return m;
}


bool Mat4_eq(const Mat4 m1, const Mat4 m2)
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if(!float_eq(m1.m[row][col], m2.m[row][col])) {
                return false;
            }
        }
    }

    return true;
}

Mat4 Mat4_transpose(const Mat4 mat)
{
    Mat4 result;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.m[row][col] = mat.m[col][row];
        }
    }
    return result;
}

Mat4 Mat4_mul(const Mat4 m1, const Mat4 m2)
{
    Mat4 result = Mat4_zeroes();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m1.m[i][k] * m2.m[k][j];
            }
        }
    }
    return result;
}

Mat4 Mat4_divs(const Mat4 a, const float scalar)
{
    Mat4 result = Mat4_zeroes();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = a.m[i][j] / scalar;
        }
    }
    return result;
}

Mat3 Mat4_minor(const Mat4 mat, unsigned int row, unsigned int col)
{
    Mat3 result;

    int resultRow = 0;
    int resultCol = 0;
    for (int i = 0; i < 4; ++i) {
        if (row == i) {
            continue;
        }
        
        resultCol = 0;
        for (int j = 0; j < 4; ++j) {
            if (col == j) {
                continue;
            }

            result.m[resultRow][resultCol] = mat.m[i][j];
            ++resultCol;
        }
        ++resultRow;
    }

    return result;
}

float Mat4_det(const Mat4 mat)
{
    float det1 = Mat3_det(Mat4_minor(mat, 0, 0));
    float det2 = Mat3_det(Mat4_minor(mat, 0, 1));
    float det3 = Mat3_det(Mat4_minor(mat, 0, 2));
    float det4 = Mat3_det(Mat4_minor(mat, 0, 3));
    
    return mat.m[0][0] * det1 - mat.m[0][1] * det2 + mat.m[0][2] * det3 - mat.m[0][3] * det4;
}

Mat4 Mat4_inverse(const Mat4 m)
{
    Mat4 cofactorMat = Mat4_zeroes();
    float dets[4] = {0};
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Mat3 minor = Mat4_minor(m, i, j);
            float det = Mat3_det(minor);

            if (0 == i) {
                dets[j] = det;
            }

            float cofactor = pow(-1, i + j) * det;
            cofactorMat.m[i][j] = cofactor;
        }
    }

    Mat4 adjointMat = Mat4_transpose(cofactorMat);
    float det = m.m[0][0] * dets[0] - m.m[0][1] * dets[1] + m.m[0][2] * dets[2] - m.m[0][3] * dets[3];

    return Mat4_divs(adjointMat, det);
}

Mat4 Mat4_translate(const Vec3 values)
{
    Mat4 m = Mat4_identity();

    m.m[0][3] = values.x;
    m.m[1][3] = values.y;
    m.m[2][3] = values.z;

    return m;
}

Mat4 Mat4_scale(const Vec3 values)
{
    Mat4 m = Mat4_identity();

    m.m[0][0] = values.x;
    m.m[1][1] = values.y;
    m.m[2][2] = values.z;

    return m;
}

Mat4 Mat4_rotateX(const float radians)
{
    Mat4 m = Mat4_identity();

    m.m[1][1] = cos(radians);
    m.m[1][2] = -sin(radians);
    m.m[2][1] = sin(radians);
    m.m[2][2] = cos(radians);

    return m;
}

Mat4 Mat4_rotateY(const float radians)
{
    Mat4 m = Mat4_identity();

    m.m[0][0] = cos(radians);
    m.m[0][2] = sin(radians);
    m.m[2][0] = -sin(radians);
    m.m[2][2] = cos(radians);

    return m;
}

Mat4 Mat4_rotateZ(const float radians)
{
    Mat4 m = Mat4_identity();

    m.m[0][0] = cos(radians);
    m.m[0][1] = -sin(radians);
    m.m[1][0] = sin(radians);
    m.m[1][1] = cos(radians);

    return m;
}

Mat4 Mat4_perspective(float fov, float aspect, float zNear, float zFar)
{
    Mat4 result = Mat4_zeroes();
    result.m[0][0] = 1 / (aspect * tanf(fov / 2));
    result.m[1][1] = 1 / tanf(fov / 2);
    result.m[2][2] = -(zFar + zNear) / (zFar - zNear);
    result.m[2][3] = (-2 * zFar * zNear) / (zFar - zNear);
    result.m[3][2] = -1;
    return result;
}

Mat4 Mat4_orthographic(int left, int right, int bottom, int top, float near, float far)
{
    Mat4 result = Mat4_zeroes();
    result.m[0][0] = 2.0f / (right - left);
    result.m[1][1] = 2.0f / (top - bottom);
    result.m[2][2] = -2.0f / (far - near);
    result.m[3][3] = 1;
    
    result.m[0][3] = -(right + left) / (float)(right - left);
    result.m[1][3] = -(top + bottom) / (float)(top - bottom);
    result.m[2][3] = -(far + near) / (float)(far - near);

    
    return result;
}