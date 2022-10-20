#include <check.h>
#include "check_check.h"
#include "util/float.h"
#include "data/mat2.h"
#include "data/mat3.h"

START_TEST (mat3_minor_0_0) {
    float array[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

    Mat3 mat = Mat3_create(array);
    Mat2 result = Mat3_minor(mat, 0, 0);

    ck_assert_float_eq_tol(5, result.m[0][0], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(6, result.m[0][1], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(8, result.m[1][0], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(9, result.m[1][1], FLOAT_TOLERANCE);
}
END_TEST

START_TEST (mat3_minor_2_2) {
    float array[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

    Mat3 mat = Mat3_create(array);
    Mat2 result = Mat3_minor(mat, 2, 2);

    ck_assert_float_eq_tol(1, result.m[0][0], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(2, result.m[0][1], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(4, result.m[1][0], FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(5, result.m[1][1], FLOAT_TOLERANCE);
}
END_TEST

START_TEST (mat3_det) {
    float array[9] = {
        2, -3,  1,
        2,  0, -1,
        1,  4,  5
    };

    Mat3 mat = Mat3_create(array);
    float result = Mat3_det(mat);

    ck_assert_float_eq_tol(49, result, FLOAT_TOLERANCE);
}
END_TEST

Suite *mat3_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Mat3");

	/* Core test case */
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, mat3_minor_0_0);
	tcase_add_test(tc_core, mat3_minor_2_2);
	tcase_add_test(tc_core, mat3_det);

	suite_add_tcase(s, tc_core);
	return s;
}

