#include <check.h>
#include "data/vec3.h"
#include "check_check.h"

START_TEST (vec3_init) {
    Vec3 point = Vec3_init(1.0, 2.0, 3.0);
    ck_assert_float_eq(point.x, 1.0);
    ck_assert_float_eq(point.y, 2.0);
    ck_assert_float_eq(point.z, 3.0);
}
END_TEST

START_TEST (vec3_zeroes) {
    Vec3 point = Vec3_zeroes();
    ck_assert_float_eq(point.x, 0.0);
    ck_assert_float_eq(point.y, 0.0);
    ck_assert_float_eq(point.z, 0.0);
}
END_TEST

START_TEST (vec3_ones) {
    Vec3 point = Vec3_ones();
    ck_assert_float_eq(point.x, 1.0);
    ck_assert_float_eq(point.y, 1.0);
    ck_assert_float_eq(point.z, 1.0);
}
END_TEST

START_TEST (vec3_up) {
    Vec3 point = Vec3_up();
    ck_assert_float_eq(point.x, 0.0);
    ck_assert_float_eq(point.y, 1.0);
    ck_assert_float_eq(point.z, 0.0);
}
END_TEST

START_TEST (vec3_copy) {
    Vec3 point = Vec3_init(2, 3, 4);
    Vec3 result = Vec3_copy(point);
    ck_assert_float_eq(result.x, 2.0);
    ck_assert_float_eq(result.y, 3.0);
    ck_assert_float_eq(result.z, 4.0);
}
END_TEST

START_TEST (vec3_eq_success) {
    Vec3 a = Vec3_init(2, 3, 4);
    Vec3 b = Vec3_init(2, 3, 4);
    bool result = Vec3_eq(a, b);
    ck_assert(result);
}
END_TEST

START_TEST (vec3_eq_fail) {
    Vec3 a = Vec3_init(2, 3, 4);
    Vec3 b = Vec3_init(1, 3, 4);
    bool result = Vec3_eq(a, b);
    ck_assert(!result);
}
END_TEST

START_TEST (vec3_dot) {
    Vec3 a = Vec3_init(1, 3, -5);
    Vec3 b = Vec3_init(4, -2, -1);
    float result = Vec3_dot(a, b);
    ck_assert_float_eq_tol(3, result, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec3_cross) {
    Vec3 a = Vec3_init(2, 3, 4);
    Vec3 b = Vec3_init(5, 6, 7);
    Vec3 result = Vec3_cross(a, b);
    ck_assert_float_eq_tol(-3, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(6, result.y, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(-3, result.z, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec3_magnitude) {
    Vec3 a = Vec3_init(2, 3, 4);
    float result = Vec3_magnitude(a);
    ck_assert_float_eq_tol(5.385, result, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec3_negate) {
    Vec3 a = Vec3_init(2, 3, 4);
    Vec3 result = Vec3_negate(a);
    ck_assert_float_eq_tol(-2, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(-3, result.y, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(-4, result.z, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec3_normalize) {
    Vec3 a = Vec3_init(3, 1, 2);
    Vec3 result = Vec3_normalize(a);
    ck_assert_float_eq_tol(0.802, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(0.267, result.y, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(0.534, result.z, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec3_add) {
    Vec3 a = Vec3_init(3, 1, 2);
    Vec3 b = Vec3_init(-0.5, 1.5, 2.3);
    Vec3 result = Vec3_add(a, b);
    ck_assert_float_eq_tol(2.5, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(2.5, result.y, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(4.3, result.z, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec3_sub) {
    Vec3 a = Vec3_init(3, 1, 2);
    Vec3 b = Vec3_init(-0.5, 1.5, 2.3);
    Vec3 result = Vec3_sub(a, b);
    ck_assert_float_eq_tol(3.5, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(-0.5, result.y, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(-0.3, result.z, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec3_mul) {
    Vec3 a = Vec3_init(3, 1, 2);
    Vec3 b = Vec3_init(-0.5, 1.5, 2.3);
    Vec3 result = Vec3_mul(a, b);
    ck_assert_float_eq_tol(-1.5, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(1.5, result.y, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(4.6, result.z, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec3_div) {
    Vec3 a = Vec3_init(3, 1, 2);
    Vec3 b = Vec3_init(2, 1, 4);
    Vec3 result = Vec3_div(a, b);
    ck_assert_float_eq_tol(1.5, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(1, result.y, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(0.5, result.z, FLOAT_TOLERANCE);
}
END_TEST


START_TEST (vec3_adds) {
    Vec3 a = Vec3_init(3, 1, 2);
    Vec3 result = Vec3_adds(a, 2);
    ck_assert_float_eq_tol(5, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(3, result.y, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(4, result.z, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec3_subs) {
    Vec3 a = Vec3_init(3, 1, 2);
    Vec3 result = Vec3_subs(a, 2);
    ck_assert_float_eq_tol(1, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(-1, result.y, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(0, result.z, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec3_muls) {
    Vec3 a = Vec3_init(3, 1, 2);
    Vec3 result = Vec3_muls(a, 2);
    ck_assert_float_eq_tol(6, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(2, result.y, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(4, result.z, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec3_divs) {
    Vec3 a = Vec3_init(3, 1, 2);
    Vec3 result = Vec3_divs(a, 2);
    ck_assert_float_eq_tol(1.5, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(0.5, result.y, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(1, result.z, FLOAT_TOLERANCE);
}
END_TEST


Suite *vec3_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Vec3");

	/* Core test case */
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, vec3_init);
	tcase_add_test(tc_core, vec3_zeroes);
	tcase_add_test(tc_core, vec3_ones);
	tcase_add_test(tc_core, vec3_up);
	tcase_add_test(tc_core, vec3_copy);
	tcase_add_test(tc_core, vec3_eq_success);
	tcase_add_test(tc_core, vec3_eq_fail);
	tcase_add_test(tc_core, vec3_dot);
	tcase_add_test(tc_core, vec3_cross);
	tcase_add_test(tc_core, vec3_magnitude);
	tcase_add_test(tc_core, vec3_negate);
	tcase_add_test(tc_core, vec3_normalize);
	tcase_add_test(tc_core, vec3_add);
	tcase_add_test(tc_core, vec3_sub);
	tcase_add_test(tc_core, vec3_mul);
	tcase_add_test(tc_core, vec3_div);
    tcase_add_test(tc_core, vec3_adds);
	tcase_add_test(tc_core, vec3_subs);
	tcase_add_test(tc_core, vec3_muls);
	tcase_add_test(tc_core, vec3_divs);

	suite_add_tcase(s, tc_core);
	return s;
}

