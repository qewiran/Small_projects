#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <utility>

template <typename Field, size_t ROWS, size_t COLUMNS> class Matrix {

private:
  size_t rank = 0;
  std::array<Field, ROWS * COLUMNS> data;

public:
  using Iterator = typename std::array<Field, ROWS * COLUMNS>::iterator;
  using ConstIterator =
      typename std::array<Field, ROWS * COLUMNS>::const_iterator;

  size_t getRank() const { return rank; }

  Field max_row_abs = 0.0; /* need later for algorithms*/

  void swapRows(size_t idx1, size_t idx2) {
    ConstIterator row1 = this->cbegin();
  }
  void swapCols(size_t, size_t);
  void makeRandom(bool);

  void makeCustom();
  void makeIdentity();

  Matrix(const std::array<Field, ROWS * COLUMNS> &otherData)
      : data(otherData) {}

  template <size_t N>
  Matrix<Field, ROWS, N> operator*(
      const Matrix<Field, COLUMNS, N> &) const; /* matrix multiplication */

  Matrix operator*(const Field coeff) const; /* multiplication by coefficient*/

  Matrix &operator+(const Matrix &) const;

  Matrix &operator-(const Matrix &) const;

  Matrix transposed() const;
  //   void display() const;
  Field euclNorm() const;
  Field infNorm() const;
  Matrix diag(const Matrix &A);
};

template <typename Field, size_t COLUMNS>
using colVec = Matrix<Field, 1, COLUMNS>;

template <typename Field, size_t ROWS> using rowVec = Matrix<Field, ROWS, 1>;

#endif /*MATRIX_H*/