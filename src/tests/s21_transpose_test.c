#include <stdio.h>

#include "s21_matrix_suites.h"

START_TEST(transpose_matrix_test_1) {
  matrix_t matrix1 = {0}, matrix2 = {0}, result = {0};

  s21_create_matrix(3, 3, &matrix1);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++)
    for (int j = 0; j < matrix1.columns; j++) matrix1.matrix[i][j] = k++;

  s21_create_matrix(3, 3, &matrix2);
  matrix2.matrix[0][0] = 0, matrix2.matrix[0][1] = 3, matrix2.matrix[0][2] = 6;
  matrix2.matrix[1][0] = 1, matrix2.matrix[1][1] = 4, matrix2.matrix[1][2] = 7;
  matrix2.matrix[2][0] = 2, matrix2.matrix[2][1] = 5, matrix2.matrix[2][2] = 8;

  s21_transpose(&matrix1, &result);

  for (int i = 0; i < result.rows; i++)
    for (int j = 0; j < result.columns; j++)
      ck_assert_double_eq_tol(result.matrix[i][j], matrix2.matrix[i][j], EPS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_matrix_test_2) {
  matrix_t matrix1, matrix2, result;

  s21_create_matrix(3, 3, &matrix1);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++)
    for (int j = 0; j < matrix1.columns; j++) matrix1.matrix[i][j] = k++;

  s21_create_matrix(3, 3, &matrix2);
  matrix2.matrix[0][0] = 0, matrix2.matrix[0][1] = 3, matrix2.matrix[0][2] = 6;
  matrix2.matrix[1][0] = 1, matrix2.matrix[1][1] = 4, matrix2.matrix[1][2] = 7;
  matrix2.matrix[2][0] = 2, matrix2.matrix[2][1] = 5, matrix2.matrix[2][2] = 8;

  s21_transpose(&matrix1, &result);

  for (int i = 0; i < result.rows; i++)
    for (int j = 0; j < result.columns; j++)
      ck_assert_double_eq_tol(result.matrix[i][j], matrix2.matrix[i][j], EPS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_matrix_test_3) {
  matrix_t result = {0};
  ck_assert_int_eq(s21_transpose(NULL, &result), INCORRECT_MATRIX);
}
END_TEST

Suite *transpose_matrix_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("transpose_matrix");
  tc = tcase_create("transpose_matrix_case");

  tcase_add_test(tc, transpose_matrix_test_1);
  tcase_add_test(tc, transpose_matrix_test_2);
  tcase_add_test(tc, transpose_matrix_test_3);
  suite_add_tcase(s, tc);
  return s;
}
