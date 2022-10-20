#include <check.h>
#include "check_check.h"
#include "util/float.h"
#include "data/mat4.h"

START_TEST (mat4_identity) {
    Mat4 result = Mat4_identity();
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if(row == col) {
                ck_assert_float_eq_tol(1.0, result.m[row][col], FLOAT_TOLERANCE);
            } else {
                ck_assert_float_eq_tol(0.0, result.m[row][col], FLOAT_TOLERANCE);
            }
        }
    }
}
END_TEST

START_TEST (mat4_zeroes) {
    Mat4 result = Mat4_zeroes();
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            ck_assert_float_eq_tol(0.0, result.m[row][col], FLOAT_TOLERANCE);
        }
    }
}
END_TEST

START_TEST (mat4_copy) {
    Mat4 m = Mat4_identity();
    m.m[0][0] = 12;
    m.m[0][1] = 11;
    m.m[0][2] = 10;
    m.m[0][3] = 9;

    Mat4 result = Mat4_copy(m);

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            ck_assert_float_eq_tol(m.m[row][col], result.m[row][col], FLOAT_TOLERANCE);
        }
    }
}
END_TEST

START_TEST (mat4_create) {
    float array[16] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 8, 7, 6,
        5, 4, 3, 2
    };

    Mat4 result = Mat4_create(array);

    // Row 1
    ck_assert_float_eq_tol(1, result.m[0][0], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(2, result.m[0][1], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(3, result.m[0][2], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(4, result.m[0][3], FLOAT_TOLERANCE);

    // Row 2
    ck_assert_float_eq_tol(5, result.m[1][0], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(6, result.m[1][1], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(7, result.m[1][2], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(8, result.m[1][3], FLOAT_TOLERANCE);

    // Row 3
    ck_assert_float_eq_tol(9, result.m[2][0], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(8, result.m[2][1], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(7, result.m[2][2], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(6, result.m[2][3], FLOAT_TOLERANCE);

    // Row 4
    ck_assert_float_eq_tol(5, result.m[3][0], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(4, result.m[3][1], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(3, result.m[3][2], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(2, result.m[3][3], FLOAT_TOLERANCE);
}
END_TEST

START_TEST (mat4_eq_true) {
    Mat4 m1 = Mat4_identity();
    Mat4 m2 = Mat4_identity();
    ck_assert(Mat4_eq(m1, m2));
}
END_TEST

START_TEST (mat4_eq_false) {
    Mat4 m1 = Mat4_identity();
    Mat4 m2 = Mat4_identity();
    m2.m[0][1] = 3;

    ck_assert(!Mat4_eq(m1, m2));
}
END_TEST

START_TEST (mat4_transpose_identity) {
    Mat4 m = Mat4_identity();
    Mat4 result = Mat4_transpose(m);

    ck_assert(Mat4_eq(Mat4_identity(), result));
}
END_TEST

START_TEST (mat4_transpose_custom) {
    Mat4 m = Mat4_zeroes();
    m.m[0][0] = 1;
    m.m[0][1] = 1;
    m.m[0][2] = 1;
    m.m[0][3] = 1;

    Mat4 result = Mat4_transpose(m);

    ck_assert_float_eq_tol(m.m[0][0], result.m[0][0], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(m.m[0][1], result.m[1][0], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(m.m[0][2], result.m[2][0], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(m.m[0][3], result.m[3][0], FLOAT_TOLERANCE);
}
END_TEST

START_TEST (mat4_mul_zeroes) {
    Mat4 m1 = Mat4_identity();
    Mat4 m2 = Mat4_zeroes();
    Mat4 result = Mat4_mul(m1, m2);

    ck_assert(Mat4_eq(Mat4_zeroes(), result));
}
END_TEST

START_TEST (mat4_mul_custom) {
    float array[16] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 8, 7, 6,
        5, 4, 3, 2
    };

    Mat4 m1 = Mat4_create(array);
    Mat4 m2 = Mat4_create(array);
    Mat4 result = Mat4_mul(m1, m2);

    float expectedArray[16] = {
        58, 54, 50, 46,
        138, 134, 130, 126,
        142, 146, 150, 154,
        62, 66, 70, 74
    };

    Mat4 expected = Mat4_create(expectedArray);
    ck_assert(Mat4_eq(expected, result));
}
END_TEST

START_TEST (mat4_det) {
    float array[16] = {
        4, 3, 2, 2,
        0, 1, -3, 3,
        0, -1, 3, 3, 
        0, 3, 1, 1
    };

    Mat4 m1 = Mat4_create(array);
    float result = Mat4_det(m1);

    ck_assert_float_eq_tol(-240, result, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (mat4_inverse) {
    float array[16] = {
       -5, 2, 6, -8, 
        1, -5, 1, 8, 
        7, 7, -6, -7, 
        1, -3, 7, 4
    };

    Mat4 m1 = Mat4_create(array);
    Mat4 result = Mat4_inverse(m1);

    float expectedArray[16] = {
         0.2180,  0.4511,  0.2406, -0.0451, 
        -0.8082, -1.4567, -0.4436,  0.5206, 
        -0.0789, -0.2236, -0.0526,  0.1973, 
        -0.5225, -0.8139, -0.3007,  0.3063
    };

    Mat4 expected = Mat4_create(expectedArray);
    ck_assert(Mat4_eq(expected, result));
}
END_TEST

Suite *mat4_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Mat4");

	/* Core test case */
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, mat4_identity);
	tcase_add_test(tc_core, mat4_zeroes);
	tcase_add_test(tc_core, mat4_copy);
	tcase_add_test(tc_core, mat4_create);
	tcase_add_test(tc_core, mat4_eq_true);
	tcase_add_test(tc_core, mat4_eq_false);
	tcase_add_test(tc_core, mat4_transpose_identity);
	tcase_add_test(tc_core, mat4_transpose_custom);
	tcase_add_test(tc_core, mat4_mul_zeroes);
	tcase_add_test(tc_core, mat4_mul_custom);
	tcase_add_test(tc_core, mat4_det);
	tcase_add_test(tc_core, mat4_inverse);

	suite_add_tcase(s, tc_core);
	return s;
}

