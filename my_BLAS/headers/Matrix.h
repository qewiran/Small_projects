#pragma once
#include <cstdlib>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <utility>

class LU_Decomposer;
class Matrix
{
    friend class LU_Decomposer;

private:
    int n = 0, m = 0;
    int rank = 0;
    std::vector<std::vector<double>> rows;

public:
    int GetRank() const;
    int GetN() const;
    int GetM() const;
    double max_row_abs = 0.0;

    void SwapRows(int, int);
    void SwapCols(int, int);
    void MakeRandom(bool);

    void MakeCustom();
    void MakeIdentity();

    Matrix() = default;
    Matrix(int, int);
    Matrix(const Matrix &);
    Matrix(Matrix &&) noexcept;
    ~Matrix() = default;

    Matrix &operator*(const Matrix &);
    Matrix const &operator*(const Matrix &) const;

    Matrix &operator*(const double k);
    Matrix const &operator*(const double k) const;

    Matrix &operator+(const Matrix &);
    Matrix const &operator+(const Matrix &) const;

    Matrix &operator-(const Matrix &);
    Matrix const &operator-(const Matrix &) const;

    Matrix &operator=(Matrix);

    std::vector<double> &operator[](const int);
    std::vector<double> const &operator[](const int) const;

    void swap(Matrix &matrix1, Matrix &matrix2) noexcept;

    Matrix Transposed() const;
    void Display() const;
    double EuclNorm() const;
    double InfNorm() const;
};

Matrix diag(const Matrix &A);

std::vector<double> operator+(const std::vector<double> &v1,
                              const std::vector<double> &v2);

std::vector<double> operator-(const std::vector<double> &v1,
                              const std::vector<double> &v2);

std::vector<double> operator*(const std::vector<double> &v1, double k);
