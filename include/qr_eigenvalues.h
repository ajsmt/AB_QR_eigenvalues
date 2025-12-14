#pragma once

#include "matrix_utils.h"

enum class solving_Code
{
    Success = 0,
    NotSquareMatrix,
    SingularMatrix
};

Matrix toHessenberg(const Matrix &A, const double eps=1e-12);

std::tuple <std::vector<std::pair<double, double> >, int, double> 
Solve(const Matrix& A, int iters = 10000, double eps = 1e-12);
