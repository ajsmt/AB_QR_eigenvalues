#include "../include/qr_eigenvalues.h"

Matrix toHessenberg(const Matrix &A, double eps)
{
    int n = A.size();
    Matrix H = A;

    if (n <= 2)
        return H;

    for (int k = 0; k < n - 2; ++k)
    {
        Vector w(n, 0);

        double a_ = 0.0;
        for (int i = k + 1; i < n; ++i)
        {
            a_ += H[i][k] * H[i][k];
        }
        a_ = std::sqrt(a_);

        if (a_ < eps)
            continue;

        if (H[k + 1][k] > 0)
            a_ *= -1;

        for (int i = k + 1; i < n; ++i)
            w[i] = H[i][k];
        w[k + 1] = H[k + 1][k] - a_;

        double w_ = 0;
        for (int i = k + 1; i < n; ++i)
            w_ += w[i] * w[i];

        if (w_ < eps)
            continue;

        for (int j = k; j < n; ++j)
        {
            double a_w = 0;
            for (int i = k + 1; i < n; ++i)
                a_w += w[i] * H[i][j];

            double factor = 2 * a_w / w_;

            for (int i = k + 1; i < n; ++i)
                H[i][j] -= factor * w[i];
        }

        for (int i = 0; i < n; ++i)
        {
            double a_w = 0;
            for (int j = k + 1; j < n; ++j)
                a_w += H[i][j] * w[j];

            double factor = 2 * a_w / w_;

            for (int j = k + 1; j < n; ++j)
                H[i][j] -= factor * w[j];
        }

        for (int i = k + 1; i < n; ++i)
            H[i][k] = 0;
        H[k + 1][k] = a_;
    }

    return H;
}

std::tuple<std::vector<std::pair<double, double>>, int, double>
Solve(const Matrix &A, int iters, double eps)
{
    auto start_time = std::chrono::high_resolution_clock::now();

    Matrix H = toHessenberg(A);
    int n = H.size();

    int iterations;

    for (iterations = 0; iterations <= iters; iterations++)
    {
        bool flag = true;

        for (int i = 0; i < n - 1; i++)
        {
            if (std::abs(H[i + 1][i]) > eps)
            {
                bool complex = false;
                if ((i == n - 2) || (std::abs(H[i + 2][i + 1]) < eps))
                {
                    complex = true;
                    i++;
                }
                if (!complex)
                {
                    flag = false;
                    break;
                }
            }
        }

        if (flag && iterations > 0)
            break;

        std::vector<double> cs(n - 1);
        std::vector<double> ss(n - 1);

        for (int i = 0; i < n - 1; ++i)
        {
            double c, s;

            if (std::abs(H[i + 1][i]) < eps)
            {
                c = 1;
                s = 0;
            }
            else
            {
                double r = std::sqrt(H[i][i] * H[i][i] + H[i + 1][i] * H[i + 1][i]);
                c = H[i][i] / r;
                s = H[i + 1][i] / r;
            }

            cs[i] = c;
            ss[i] = s;

            for (int j = i; j < n; ++j)
            {
                double temp = c * H[i][j] + s * H[i + 1][j];
                H[i + 1][j] = -s * H[i][j] + c * H[i + 1][j];
                H[i][j] = temp;
            }
        }

        for (int i = 0; i < n - 1; ++i)
        {
            double c = cs[i];
            double s = ss[i];

            for (int j = 0; j < n; ++j)
            {
                double temp = c * H[j][i] + s * H[j][i + 1];
                H[j][i + 1] = -s * H[j][i] + c * H[j][i + 1];
                H[j][i] = temp;
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end_time - start_time;

    std::vector<std::pair<double, double>> eigenvalues;
    for (int i = 0; i < n; ++i)
    {
        if (i < n - 1 && std::abs(H[i + 1][i]) > eps)
        {
            double b = H[i][i] + H[i + 1][i + 1];
            double ac = H[i][i] * H[i + 1][i + 1] - H[i][i + 1] * H[i + 1][i];
            double D = b * b - 4 * ac;

            if (D >= 0)
            {
                eigenvalues.push_back({(b + std::sqrt(D)) / 2, 0});
                eigenvalues.push_back({(b - std::sqrt(D)) / 2, 0});
            }
            else
            {
                double R = b / 2.0;
                double I = std::sqrt(-D) / 2;
                eigenvalues.push_back({R, I});
                eigenvalues.push_back({R, -I});
            }
            i++;
        }
        else
            eigenvalues.push_back({H[i][i], 0});
    }

    return std::make_tuple(eigenvalues, iterations, duration.count());
}