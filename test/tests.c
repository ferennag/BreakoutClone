#include <check.h>
#include "check_check.h"

int main(void)
{
	SRunner *sr = srunner_create(vec2_suite());
	srunner_add_suite(sr, vec3_suite());
	srunner_add_suite(sr, mat3_suite());
	srunner_add_suite(sr, mat4_suite());

	srunner_run_all(sr, CK_NORMAL);
	int failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return failed;
}