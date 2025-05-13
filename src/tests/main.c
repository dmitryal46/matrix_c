#include "s21_matrix_suites.h"

void run_testcase(Suite *testcase) {
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

void run_tests() {
  Suite *test_cases[] = {
      create_matrix_suite(), transpose_matrix_suite(), determinant_suite(),
      eq_matrix_suite(),     inverse_matrix_suite(),   mult_matrix_suite(),
      sum_matrix_suite(),    calc_complements_suite(), mult_number_suite(),
      sub_matrix_suite(),    remove_matrix_suite(),    NULL};

  for (Suite **current_testcase = test_cases; *current_testcase != NULL;
       current_testcase++)
    run_testcase(*current_testcase);
}

int main() {
  run_tests();
  return 0;
}
