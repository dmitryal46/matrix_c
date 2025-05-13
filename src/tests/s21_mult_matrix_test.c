#include <stdio.h>

#include "s21_matrix_suites.h"

START_TEST(mult_matrix_test_1) {
  int rows = -1;
  int columns = 0;
  matrix_t m1 = {0};
  s21_create_matrix(rows, columns, &m1);
  matrix_t m2 = {0};
  s21_create_matrix(columns, rows, &m2);
  matrix_t res = {0};

  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &res), INCORRECT_MATRIX);

  if (m1.matrix != NULL) s21_remove_matrix(&m1);
  if (m2.matrix != NULL) s21_remove_matrix(&m2);
  if (res.matrix != NULL) s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_matrix_test_2) {
  matrix_t m1 = {0};
  int rows = 2;
  int columns = 3;
  s21_create_matrix(rows, columns, &m1);

  matrix_t m2 = {0};
  rows = 4;
  columns = 5;
  s21_create_matrix(rows, columns, &m2);

  matrix_t res = {0};

  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &res), CALC_ERROR);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  if (res.matrix != NULL) s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_matrix_test_3) {
  matrix_t matrix1, matrix2, result, expected_result;

  s21_create_matrix(3, 2, &matrix1);
  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 2;
  matrix1.matrix[1][1] = 5;
  matrix1.matrix[2][0] = 3;
  matrix1.matrix[2][1] = 6;

  s21_create_matrix(2, 3, &matrix2);
  matrix2.matrix[0][0] = 1;
  matrix2.matrix[0][1] = -1;
  matrix2.matrix[0][2] = 1;
  matrix2.matrix[1][0] = 2;
  matrix2.matrix[1][1] = 3;
  matrix2.matrix[1][2] = 4;

  s21_create_matrix(3, 3, &expected_result);
  expected_result.matrix[0][0] = 9;
  expected_result.matrix[0][1] = 11;
  expected_result.matrix[0][2] = 17;
  expected_result.matrix[1][0] = 12;
  expected_result.matrix[1][1] = 13;
  expected_result.matrix[1][2] = 22;
  expected_result.matrix[2][0] = 15;
  expected_result.matrix[2][1] = 15;
  expected_result.matrix[2][2] = 27;

  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&expected_result, &result), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
}
END_TEST

Suite *mult_matrix_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("mult_matrix");
  tc = tcase_create("mult_matrix_case");

  tcase_add_test(tc, mult_matrix_test_1);
  tcase_add_test(tc, mult_matrix_test_2);
  tcase_add_test(tc, mult_matrix_test_3);

  suite_add_tcase(s, tc);
  return s;
}
