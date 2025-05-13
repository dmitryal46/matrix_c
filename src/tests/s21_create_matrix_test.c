#include <stdio.h>

#include "s21_matrix_suites.h"

START_TEST(create_matrix_test_1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t m1 = {0};
  s21_create_matrix(rows, columns, &m1);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) {
      m1.matrix[i][j] = 0.0;
      ck_assert_ldouble_eq_tol(0.0, m1.matrix[i][j], EPS);
    }
  ck_assert_int_eq(m1.rows, rows);
  ck_assert_int_eq(m1.columns, columns);

  s21_remove_matrix(&m1);
}
END_TEST

START_TEST(create_matrix_test_2) {
  int rows = 0;
  int columns = 5;
  matrix_t m1 = {0};
  int res = s21_create_matrix(rows, columns, &m1);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_matrix_test_3) {
  int rows = 40;
  int columns = 0;
  matrix_t m1 = {0};
  int res = s21_create_matrix(rows, columns, &m1);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

Suite *create_matrix_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("create_matrix");
  tc = tcase_create("create_matrix_case");

  tcase_add_test(tc, create_matrix_test_1);
  tcase_add_test(tc, create_matrix_test_2);
  tcase_add_test(tc, create_matrix_test_3);

  suite_add_tcase(s, tc);
  return s;
}
