#include <check.h>
#include "data/vec2.h"
#include "check_check.h"

START_TEST (vec2_init) {
    Vec2 point = Vec2_init(1.0, 2.0);
    ck_assert_float_eq(point.x, 1.0);
    ck_assert_float_eq(point.y, 2.0);
}
END_TEST

START_TEST (vec2_zeroes) {
    Vec2 point = Vec2_zeroes();
    ck_assert_float_eq(point.x, 0.0);
    ck_assert_float_eq(point.y, 0.0);
}
END_TEST

START_TEST (vec2_ones) {
    Vec2 point = Vec2_ones();
    ck_assert_float_eq(point.x, 1.0);
    ck_assert_float_eq(point.y, 1.0);
}
END_TEST

START_TEST (vec2_up) {
    Vec2 point = Vec2_up();
    ck_assert_float_eq(point.x, 0.0);
    ck_assert_float_eq(point.y, 1.0);
}
END_TEST

START_TEST (vec2_copy) {
    Vec2 point = Vec2_init(2, 3);
    Vec2 result = Vec2_copy(point);
    ck_assert_float_eq(result.x, 2.0);
    ck_assert_float_eq(result.y, 3.0);
}
END_TEST

START_TEST (vec2_eq_success) {
    Vec2 a = Vec2_init(2, 3);
    Vec2 b = Vec2_init(2, 3);
    bool result = Vec2_eq(a, b);
    ck_assert(result);
}
END_TEST

START_TEST (vec2_eq_fail) {
    Vec2 a = Vec2_init(2, 3);
    Vec2 b = Vec2_init(1, 3);
    bool result = Vec2_eq(a, b);
    ck_assert(!result);
}
END_TEST

START_TEST (vec2_dot) {
    Vec2 a = Vec2_init(1, 3);
    Vec2 b = Vec2_init(4, -2);
    float result = Vec2_dot(a, b);
    ck_assert_float_eq_tol(-2, result, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec2_cross) {
    Vec2 a = Vec2_init(2, 3);
    Vec2 b = Vec2_init(5, 6);
    float result = Vec2_cross(a, b);
    ck_assert_float_eq_tol(-3, result, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec2_magnitude) {
    Vec2 a = Vec2_init(2, 3);
    float result = Vec2_magnitude(a);
    ck_assert_float_eq_tol(3.605, result, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec2_negate) {
    Vec2 a = Vec2_init(2, 3);
    Vec2 result = Vec2_negate(a);
    ck_assert_float_eq_tol(-2, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(-3, result.y, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec2_normalize) {
    Vec2 a = Vec2_init(3, 1);
    Vec2 result = Vec2_normalize(a);
    ck_assert_float_eq_tol(0.948, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(0.316, result.y, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec2_add) {
    Vec2 a = Vec2_init(3, 1);
    Vec2 b = Vec2_init(-0.5, 1.5);
    Vec2 result = Vec2_add(a, b);
    ck_assert_float_eq_tol(2.5, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(2.5, result.y, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec2_sub) {
    Vec2 a = Vec2_init(3, 1);
    Vec2 b = Vec2_init(-0.5, 1.5);
    Vec2 result = Vec2_sub(a, b);
    ck_assert_float_eq_tol(3.5, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(-0.5, result.y, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec2_mul) {
    Vec2 a = Vec2_init(3, 1);
    Vec2 b = Vec2_init(-0.5, 1.5);
    Vec2 result = Vec2_mul(a, b);
    ck_assert_float_eq_tol(-1.5, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(1.5, result.y, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec2_div) {
    Vec2 a = Vec2_init(3, 1);
    Vec2 b = Vec2_init(2, 1);
    Vec2 result = Vec2_div(a, b);
    ck_assert_float_eq_tol(1.5, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(1, result.y, FLOAT_TOLERANCE);
}
END_TEST


START_TEST (vec2_adds) {
    Vec2 a = Vec2_init(3, 1);
    Vec2 result = Vec2_adds(a, 2);
    ck_assert_float_eq_tol(5, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(3, result.y, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec2_subs) {
    Vec2 a = Vec2_init(3, 1);
    Vec2 result = Vec2_subs(a, 2);
    ck_assert_float_eq_tol(1, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(-1, result.y, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec2_muls) {
    Vec2 a = Vec2_init(3, 1);
    Vec2 result = Vec2_muls(a, 2);
    ck_assert_float_eq_tol(6, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(2, result.y, FLOAT_TOLERANCE);
}
END_TEST

START_TEST (vec2_divs) {
    Vec2 a = Vec2_init(3, 1);
    Vec2 result = Vec2_divs(a, 2);
    ck_assert_float_eq_tol(1.5, result.x, FLOAT_TOLERANCE);
    ck_assert_float_eq_tol(0.5, result.y, FLOAT_TOLERANCE);
}
END_TEST


Suite *vec2_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Vec2");

	/* Core test case */
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, vec2_init);
	tcase_add_test(tc_core, vec2_zeroes);
	tcase_add_test(tc_core, vec2_ones);
	tcase_add_test(tc_core, vec2_up);
	tcase_add_test(tc_core, vec2_copy);
	tcase_add_test(tc_core, vec2_eq_success);
	tcase_add_test(tc_core, vec2_eq_fail);
	tcase_add_test(tc_core, vec2_dot);
	tcase_add_test(tc_core, vec2_cross);
	tcase_add_test(tc_core, vec2_magnitude);
	tcase_add_test(tc_core, vec2_negate);
	tcase_add_test(tc_core, vec2_normalize);
	tcase_add_test(tc_core, vec2_add);
	tcase_add_test(tc_core, vec2_sub);
	tcase_add_test(tc_core, vec2_mul);
	tcase_add_test(tc_core, vec2_div);
    tcase_add_test(tc_core, vec2_adds);
	tcase_add_test(tc_core, vec2_subs);
	tcase_add_test(tc_core, vec2_muls);
	tcase_add_test(tc_core, vec2_divs);

	suite_add_tcase(s, tc_core);
	return s;
}

