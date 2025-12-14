#pragma once

#include "include.h"

Matrix random_matrix(int n, int minVal = -10, int maxVal = 10);
Vector random_vector(int n, int minVal = -10, int maxVal = 10);

double matrix_Norm_Infinity(const Matrix& A);

double vector_euclid_Norm_sq(const Vector&, int st = 0);
double vector_euclid_Norm(const Vector&, int st = 0);

Vector Matrix_dot_Vector(const Matrix&, const Vector&);

Vector Vector_sub_Vector(const Vector&, const Vector&);

double Residual_vector_Norm(const Matrix&, const Vector&, const Vector&);