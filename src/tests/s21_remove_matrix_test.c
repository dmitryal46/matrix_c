#include <stdio.h>

#include "s21_matrix_suites.h"

START_TEST(remove_matrix_test_1) {
  int rows = 5;
  int columns = 7;
  matrix_t A;
  s21_create_matrix(rows, columns, &A);
  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

Suite *remove_matrix_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("remove_matrix_");
  tc = tcase_create("remove_matrix_case");

  tcase_add_test(tc, remove_matrix_test_1);

  suite_add_tcase(s, tc);
  return s;
}