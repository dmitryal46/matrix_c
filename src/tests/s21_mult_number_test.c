#include <stdio.h>

#include "s21_matrix_suites.h"

START_TEST(mult_number_test_1) {
  int rows = -1;
  int columns = 0;
  matrix_t A = {0};
  s21_create_matrix(rows, columns, &A);
  matrix_t result = {0};

  double number = 1.0;

  ck_assert_int_eq(s21_mult_number(&A, number, &result), INCORRECT_MATRIX);

  if (A.matrix != NULL) s21_remove_matrix(&A);
  if (result.matrix != NULL) s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_test_2) {
  matrix_t matrix, result, expected_result;

  s21_create_matrix(3, 2, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[1][0] = 4;
  matrix.matrix[1][1] = 5;
  matrix.matrix[2][0] = 6;
  matrix.matrix[2][1] = 8;

  s21_create_matrix(3, 2, &expected_result);
  expected_result.matrix[0][0] = 2;
  expected_result.matrix[0][1] = 4;
  expected_result.matrix[1][0] = 8;
  expected_result.matrix[1][1] = 10;
  expected_result.matrix[2][0] = 12;
  expected_result.matrix[2][1] = 16;

  double number = 2;

  ck_assert_int_eq(s21_mult_number(&matrix, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&expected_result, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
}
END_TEST

START_TEST(mult_number_test_3) {
  matrix_t matrix, result, expected_result;

  s21_create_matrix(3, 2, &matrix);
  matrix.matrix[0][0] = 0;
  matrix.matrix[0][1] = 0;
  matrix.matrix[1][0] = 0;
  matrix.matrix[1][1] = 0;
  matrix.matrix[2][0] = 6;
  matrix.matrix[2][1] = 8;

  s21_create_matrix(3, 2, &expected_result);
  expected_result.matrix[0][0] = 0;
  expected_result.matrix[0][1] = 0;
  expected_result.matrix[1][0] = 0;
  expected_result.matrix[1][1] = 0;
  expected_result.matrix[2][0] = 18;
  expected_result.matrix[2][1] = 24;

  double number = 3;

  ck_assert_int_eq(s21_mult_number(&matrix, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&expected_result, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
}
END_TEST

Suite *mult_number_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("mult_number");
  tc = tcase_create("mult_numbercase");

  tcase_add_test(tc, mult_number_test_1);
  tcase_add_test(tc, mult_number_test_2);
  tcase_add_test(tc, mult_number_test_3);

  suite_add_tcase(s, tc);
  return s;
}
