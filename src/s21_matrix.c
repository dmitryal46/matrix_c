#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || result == NULL) {
    return INCORRECT_MATRIX;
  }
  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)malloc(rows * sizeof(double *));
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)malloc(columns * sizeof(double));
  }

  return OK;
}

void s21_remove_matrix(matrix_t *A) {
  if (A == NULL) return;
  if (A->matrix == NULL) return;
  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i]) {
      free(A->matrix[i]);
    }
  }
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (A == NULL || B == NULL) {
    res = FAILURE;
  } else if (A->matrix == NULL || B->matrix == NULL) {
    res = FAILURE;
  } else if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
             B->columns <= 0) {
    res = FAILURE;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    res = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) {
          res = FAILURE;
          i = A->rows;
          j = A->columns;
        }
      }
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A == NULL || B == NULL || result == NULL) {
    res = INCORRECT_MATRIX;
  } else if (A->matrix == NULL || B->matrix == NULL) {
    res = INCORRECT_MATRIX;
  } else if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
             B->columns <= 0) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    res = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A == NULL || B == NULL || result == NULL) {
    res = INCORRECT_MATRIX;
  } else if (A->matrix == NULL || B->matrix == NULL) {
    res = INCORRECT_MATRIX;
  } else if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
             B->columns <= 0) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    res = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (A == NULL || result == NULL || A->matrix == NULL || A->rows <= 0 ||
      A->columns <= 0) {
    res = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A == NULL || B == NULL || result == NULL) {
    res = INCORRECT_MATRIX;
  } else if (A->matrix == NULL || B->matrix == NULL) {
    res = INCORRECT_MATRIX;
  } else if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
             B->columns <= 0) {
    res = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    res = CALC_ERROR;
  } else {
    int rows = A->rows;
    int columns = B->columns;
    int len = A->columns;
    s21_create_matrix(rows, columns, result);
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++) result->matrix[i][j] = 0.0;
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
        for (int k = 0; k < len; k++)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (A == NULL || result == NULL || A->matrix == NULL || A->rows <= 0 ||
      A->columns <= 0) {
    res = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++)
      for (int j = 0; j < result->columns; j++)
        result->matrix[i][j] = A->matrix[j][i];
  }
  return res;
}

void create_minor_matrix(int m, int n, matrix_t *A, matrix_t *result) {
  // P.S. входные данные проверяются во внешних функциях
  s21_create_matrix(A->rows - 1, A->columns - 1, result);
  int rows = 0;
  int columns = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == m) continue;
    for (int j = 0; j < A->columns; j++) {
      if (j == n) continue;
      result->matrix[rows][columns] = A->matrix[i][j];
      columns++;
    }
    rows++;
    columns = 0;
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;
  if (A == NULL || result == NULL || A->matrix == NULL || A->rows <= 0 ||
      A->columns <= 0) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res = CALC_ERROR;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      *result = 0;
      for (int i = 0; i < A->columns; i++) {
        matrix_t minor_matrix;
        create_minor_matrix(0, i, A, &minor_matrix);
        double alg_dop = 0.0;
        s21_determinant(&minor_matrix, &alg_dop);
        s21_remove_matrix(&minor_matrix);
        (*result) += pow(-1, 2 + i) * A->matrix[0][i] * alg_dop;
      }
    }
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (A == NULL || result == NULL || A->matrix == NULL || A->rows <= 1 ||
      A->columns <= 1) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t minor_matrix;
        create_minor_matrix(i, j, A, &minor_matrix);
        double det = 0;
        s21_determinant(&minor_matrix, &det);
        det *= pow(-1, 2 + i + j);
        result->matrix[i][j] = det;
        s21_remove_matrix(&minor_matrix);
      }
    }
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (A == NULL || result == NULL || A->matrix == NULL || A->rows <= 1 ||
      A->columns <= 1) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res = CALC_ERROR;
  } else {
    double det = 0;
    matrix_t m;
    matrix_t m_t;
    s21_determinant(A, &det);
    if (fabs(det) > EPS) {
      s21_calc_complements(A, &m);
      s21_transpose(&m, &m_t);
      s21_remove_matrix(&m);
      s21_mult_number(&m_t, 1.0 / fabs(det), result);
      s21_remove_matrix(&m_t);
      for (int i = 0; i < result->rows; i++)
        for (int j = 0; j < result->columns; j++) result->matrix[i][j] *= -1;
    } else {
      res = CALC_ERROR;
    }
  }
  return res;
}