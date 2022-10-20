#include "data/mat2.h"
#include "data/mat3.h"

Mat3 Mat3_create(float *values) {
    Mat3 m;

    for(unsigned int i=0; i < 3; ++i) {
        for(unsigned int j=0; j < 3; ++j) {
            m.m[i][j] = values[i * 3 + j];
        }
    }

    return m;
}

Mat2 Mat3_minor(const Mat3 mat, unsigned int row, unsigned int col)
{
    Mat2 result;

    int resultRow = 0;
    int resultCol = 0;
    for (int i = 0; i < 3; ++i) {
        if (row == i) {
            continue;
        }
        
        resultCol = 0;
        for (int j = 0; j < 3; ++j) {
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

float Mat3_det(const Mat3 mat)
{
    float det1 = Mat2_det(Mat3_minor(mat, 0, 0));
    float det2 = Mat2_det(Mat3_minor(mat, 0, 1));
    float det3 = Mat2_det(Mat3_minor(mat, 0, 2));
    
    return mat.m[0][0] * det1 - mat.m[0][1] * det2 + mat.m[0][2] * det3;
}