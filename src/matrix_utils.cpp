#include "../include/matrix_utils.h"

Matrix random_matrix(int n, int minVal, int maxVal)
{
    Matrix A(n, std::vector<double>(n));
    int range = maxVal - minVal + 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = minVal + (rand() % range);
    return A;
}

Vector random_vector(int n, int minVal, int maxVal)
{
    Vector A(n);
    int range = maxVal - minVal + 1;
    for (int i = 0; i < n; ++i)
        A[i] = minVal + (rand() % range);
    return A;
}

double matrix_Norm_Infinity(const Matrix &A)
{
    int n = A.size();

    double max_sum = 0;

    for (int i = 0; i < n; i++)
    {
        double t_sum = 0;
        for (int j = 0; j < n; j++)
            t_sum += std::abs(A[i][j]);
        if (t_sum > max_sum)
            max_sum = t_sum;
    }
    return max_sum;
}

double vector_euclid_Norm_sq(const Vector &a, int st)
{

    double len = 0;

    for (int i = st; i < a.size(); i++)
    {
        len += a[i] * a[i];
    }

    return len;
}

double vector_euclid_Norm(const Vector &a, int st)
{

    return std::sqrt(vector_euclid_Norm_sq(a, st));
}

Vector Matrix_dot_Vector(const Matrix &A, const Vector &x)
{
    int n = x.size();

    Vector y(n, 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            y[i] += A[i][j] * x[j];
        }
    }

    return y;
}

Vector Vector_sub_Vector(const Vector &a, const Vector &b)
{
    int n = a.size();

    Vector x(n, 0);

    for (int i = 0; i < n; i++)
        x[i] = a[i] - b[i];

    return x;
}

double Residual_vector_Norm(const Matrix &A, const Vector &x, const Vector &b)
{
    return vector_euclid_Norm(Vector_sub_Vector(Matrix_dot_Vector(A, x), b));
}