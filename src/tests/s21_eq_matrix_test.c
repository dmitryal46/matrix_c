#include <stdio.h>

#include "s21_matrix_suites.h"

START_TEST(eq_matrix_test_1) {
  matrix_t matrix1, matrix2;

  s21_create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 1, matrix1.matrix[0][1] = 2, matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 0, matrix1.matrix[1][1] = 4, matrix1.matrix[1][2] = 2;
  matrix1.matrix[2][0] = 5, matrix1.matrix[2][1] = 2, matrix1.matrix[2][2] = 1;

  s21_create_matrix(3, 3, &matrix2);
  matrix2.matrix[0][0] = 1, matrix2.matrix[0][1] = 2, matrix2.matrix[0][2] = 3;
  matrix2.matrix[1][0] = 0, matrix2.matrix[1][1] = 4, matrix2.matrix[1][2] = 2;
  matrix2.matrix[2][0] = 5, matrix2.matrix[2][1] = 2, matrix2.matrix[2][2] = 1;

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_matrix_test_2) {
  matrix_t matrix1, matrix2;

  s21_create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 1, matrix1.matrix[0][1] = 2, matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 5, matrix1.matrix[1][1] = 4, matrix1.matrix[1][2] = 2;
  matrix1.matrix[2][0] = 5, matrix1.matrix[2][1] = 2, matrix1.matrix[2][2] = 1;

  s21_create_matrix(3, 3, &matrix2);
  matrix2.matrix[0][0] = 1, matrix2.matrix[0][1] = 2, matrix2.matrix[0][2] = 3;
  matrix2.matrix[1][0] = 0, matrix2.matrix[1][1] = 4, matrix2.matrix[1][2] = 2;
  matrix2.matrix[2][0] = 5, matrix2.matrix[2][1] = 2, matrix2.matrix[2][2] = 1;

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(eq_matrix_test_3) {
  matrix_t matrix1, matrix2;

  s21_create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 1, matrix1.matrix[0][1] = 2, matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 0, matrix1.matrix[1][1] = 4, matrix1.matrix[1][2] = 2;
  matrix1.matrix[2][0] = 5, matrix1.matrix[2][1] = 2, matrix1.matrix[2][2] = 1;

  s21_create_matrix(3, 2, &matrix2);
  matrix2.matrix[0][0] = 1, matrix2.matrix[0][1] = 2;
  matrix2.matrix[1][0] = 0, matrix2.matrix[1][1] = 4;
  matrix2.matrix[2][0] = 5, matrix2.matrix[2][1] = 2;

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

Suite *eq_matrix_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("eq_matrix");
  tc = tcase_create("eq_matrix_case");

  tcase_add_test(tc, eq_matrix_test_1);
  tcase_add_test(tc, eq_matrix_test_2);
  tcase_add_test(tc, eq_matrix_test_3);

  suite_add_tcase(s, tc);
  return s;
}
