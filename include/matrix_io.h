#pragma once

#include "include.h"

enum class io_Code
{
    Success = 0,
    NoData,
    NotEnoughData,
    FileNotFound,
};

io_Code read_Matrix(Matrix &A, std::istream &in);
io_Code read_Matrix(Matrix &A, const std::string &filename);

io_Code write_Matrix(const Matrix &A, std::ostream &out);
io_Code write_Matrix(const Matrix &A, const std::string &filename);

io_Code MatrixForm(const Matrix &A, std::ostream &out);
io_Code MatrixForm(const Matrix &A, const std::string &filename);

io_Code read_System(Matrix &A, Vector &b, std::istream &in);
io_Code read_System(Matrix &A, Vector &b, const std::string &filename);

io_Code write_Vector(const Vector &b, std::ostream &out);
io_Code write_Vector(const Vector &b, const std::string &filename);

io_Code VectorForm(const Vector &b, std::ostream &out);
io_Code VectorForm(const Vector &b, const std::string &filename);
