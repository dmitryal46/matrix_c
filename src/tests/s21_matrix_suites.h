#ifndef S21_MATRIX_SUITES
#define S21_MATRIX_SUITES

#include <check.h>

#include "../s21_matrix.h"

Suite *create_matrix_suite();
Suite *calc_complements_suite();
Suite *transpose_matrix_suite();
Suite *determinant_suite();
Suite *eq_matrix_suite();
Suite *inverse_matrix_suite();
Suite *mult_matrix_suite();
Suite *mult_number_suite();
Suite *sub_matrix_suite();
Suite *sum_matrix_suite();
Suite *remove_matrix_suite();

#endif
