#include "../include/matrix_io.h"

io_Code read_Matrix(Matrix &A, std::istream &in)
{
    A.clear();

    int n;
    if (!(in >> n))
        return io_Code::NoData;

    A.resize(n);
    for (int i = 0; i < n; i++)
    {
        A[i].resize(n);
        for (int j = 0; j < n; j++)
            if (!(in >> A[i][j]))
                return io_Code::NotEnoughData;
    }

    return io_Code::Success;
}

io_Code read_Matrix(Matrix &A, const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin.is_open())
        return io_Code::FileNotFound;
    return read_Matrix(A, fin);
}

io_Code write_Matrix(const Matrix &A, std::ostream &out)
{
    int n = A.size();
    out << n << '\n';

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            out << A[i][j] << '\t';
        out << '\n';
    }

    return io_Code::Success;
}

io_Code write_Matrix(const Matrix &A, const std::string &filename)
{
    std::ofstream fout(filename);
    if (!fout.is_open())
        return io_Code::FileNotFound;
    return write_Matrix(A, fout);
}

io_Code MatrixForm(const Matrix &A, std::ostream &out)
{
    int n = A.size();

    out << '{';

    for (int i = 0; i < n; i++)
    {
        out << '{';
        for (int j = 0; j < n; j++)
        {
            out << A[i][j];
            if (j + 1 < n)
                out << ',';
        }
        out << '}';
        if (i + 1 < n)
            out << ',';
    }
    out << '}';

    return io_Code::Success;
}

io_Code MatrixForm(const Matrix &A, const std::string &filename)
{
    std::ofstream fout(filename);
    if (!fout.is_open())
        return io_Code::FileNotFound;
    return MatrixForm(A, fout);
}

io_Code read_System(Matrix &A, Vector &b, std::istream &in)
{
    A.clear();
    b.clear();

    int n;
    if (!(in >> n))
        return io_Code::NoData;

    A.resize(n, Vector(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!(in >> A[i][j]))
                return io_Code::NotEnoughData;
        }
    }

    b.resize(n);
    for (int i = 0; i < n; i++)
    {
        if (!(in >> b[i]))
            return io_Code::NotEnoughData;
    }

    return io_Code::Success;
}

io_Code read_System(Matrix &A, Vector &b, const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin.is_open())
        return io_Code::FileNotFound;
    return read_System(A, b, fin);
}

io_Code write_Vector(const Vector &b, std::ostream &out)
{
    int n = b.size();
    if (n == 0)
        return io_Code::Success;

    out << n << '\n';

    for (int i = 0; i < n; i++)
    {
        out << b[i] << '\n';
    }

    return io_Code::Success;
}

io_Code write_Vector(const Vector &b, const std::string &filename)
{
    std::ofstream fout(filename);
    if (!fout.is_open())
        return io_Code::FileNotFound;
    return write_Vector(b, fout);
}

io_Code VectorForm(const Vector &b, std::ostream &out)
{
    int n = b.size();

    out << '{';
    for (int i = 0; i < n; i++)
    {
        out << b[i];
        if (i + 1 < n)
            out << ", ";
    }
    out << '}';

    return io_Code::Success;
}

io_Code VectorForm(const Vector &b, const std::string &filename)
{
    std::ofstream fout(filename);
    if (!fout.is_open())
        return io_Code::FileNotFound;
    return VectorForm(b, fout);
}
