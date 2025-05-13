#include <stdio.h>

#include "s21_matrix_suites.h"

START_TEST(determinant_test_1) {
  matrix_t matrix;
  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 0;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 1;

  double result = 0;
  double expected_result = -40;

  s21_determinant(&matrix, &result);

  ck_assert_float_eq(result, expected_result);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(determinant_test_2) {
  matrix_t matrix;
  s21_create_matrix(4, 4, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[0][3] = 4;
  matrix.matrix[1][0] = 5;
  matrix.matrix[1][1] = 6;
  matrix.matrix[1][2] = 7;
  matrix.matrix[1][3] = 8;
  matrix.matrix[2][0] = 9;
  matrix.matrix[2][1] = 10;
  matrix.matrix[2][2] = 11;
  matrix.matrix[2][3] = 12;
  matrix.matrix[3][0] = 13;
  matrix.matrix[3][1] = 14;
  matrix.matrix[3][2] = 15;
  matrix.matrix[3][3] = 16;

  double result = 0;
  double expected_result = 0;

  s21_determinant(&matrix, &result);

  ck_assert_float_eq(result, expected_result);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(determinant_test_3) {
  matrix_t matrix;
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

  double result = 0;

  ck_assert_int_eq(s21_determinant(&matrix, &result), CALC_ERROR);

  s21_remove_matrix(&matrix);
}
END_TEST

Suite *determinant_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("determinant_matrix");
  tc = tcase_create("determinant_matrix_case");

  tcase_add_test(tc, determinant_test_1);
  tcase_add_test(tc, determinant_test_2);
  tcase_add_test(tc, determinant_test_3);

  suite_add_tcase(s, tc);
  return s;
}
