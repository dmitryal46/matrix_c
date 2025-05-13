#include <stdio.h>

#include "s21_matrix_suites.h"

START_TEST(inverse_matrix_test_1) {
  matrix_t matrix, exp_result, result;

  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 5;
  matrix.matrix[0][2] = 7;
  matrix.matrix[1][0] = 6;
  matrix.matrix[1][1] = 3;
  matrix.matrix[1][2] = 4;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = -2;
  matrix.matrix[2][2] = -3;

  s21_create_matrix(3, 3, &exp_result);
  exp_result.matrix[0][0] = 1;
  exp_result.matrix[0][1] = -1;
  exp_result.matrix[0][2] = 1;
  exp_result.matrix[1][0] = -38;
  exp_result.matrix[1][1] = 41;
  exp_result.matrix[1][2] = -34;
  exp_result.matrix[2][0] = 27;
  exp_result.matrix[2][1] = -29;
  exp_result.matrix[2][2] = 24;

  s21_inverse_matrix(&matrix, &result);

  ck_assert_int_eq(s21_eq_matrix(&exp_result, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&exp_result);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_test_2) {
  matrix_t matrix = {0}, result = {0};

  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 4;
  matrix.matrix[1][1] = 5;
  matrix.matrix[1][2] = 6;
  matrix.matrix[2][0] = 7;
  matrix.matrix[2][1] = 8;
  matrix.matrix[2][2] = 9;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), CALC_ERROR);

  s21_remove_matrix(&matrix);
  if (result.matrix != NULL) s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_test_3) {
  matrix_t matrix = {0}, result = {0};

  s21_create_matrix(3, 4, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[0][3] = 0;
  matrix.matrix[1][0] = 4;
  matrix.matrix[1][1] = 2;
  matrix.matrix[1][2] = 5;
  matrix.matrix[1][3] = 2;
  matrix.matrix[2][0] = 1;
  matrix.matrix[2][1] = 1;
  matrix.matrix[2][2] = 1;
  matrix.matrix[2][3] = 1;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), CALC_ERROR);

  s21_remove_matrix(&matrix);
  if (result.matrix != NULL) s21_remove_matrix(&result);
}
END_TEST

Suite *inverse_matrix_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("inverse_matrix");
  tc = tcase_create("inverse_matrix_case");

  tcase_add_test(tc, inverse_matrix_test_1);
  tcase_add_test(tc, inverse_matrix_test_2);
  tcase_add_test(tc, inverse_matrix_test_3);

  suite_add_tcase(s, tc);
  return s;
}
