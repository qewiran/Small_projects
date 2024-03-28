#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <utility>

#define EPS 1e-14

template <typename Field, size_t ROWS, size_t COLUMNS> class Matrix {

private:
  std::array<Field, ROWS * COLUMNS> data{};
  size_t rank = 0;

public:
  void setRank(size_t rank) { this->rank = rank; }
  size_t getRank() const { return rank; }

  using Iterator = typename std::array<Field, ROWS * COLUMNS>::iterator;
  using ConstIterator =
      typename std::array<Field, ROWS * COLUMNS>::const_iterator;

  Iterator begin() { return this->data.begin(); }
  Iterator end() { return this->data.end(); }

  ConstIterator cbegin() const { return this->data.cbegin(); }
  ConstIterator cend() const { return this->data.cend(); }

  // c++23 array subscript operator overload

  inline Field operator[](size_t idx1, size_t idx2) const {
    assert(idx1 < ROWS && idx2 < COLUMNS);
    return data[idx1 * COLUMNS + idx2];
  }

  inline Field &operator[](size_t idx1, size_t idx2) {
    assert(idx1 < ROWS && idx2 < COLUMNS);
    return data[idx1 * COLUMNS + idx2];
  }

  void swapRows(size_t idx1, size_t idx2) {
    assert(idx1 < ROWS && idx2 < ROWS);

    Iterator row1It = this->begin() + idx1 * COLUMNS;
    Iterator row2It = this->begin() + idx2 * COLUMNS;

    std::swap_ranges(row1It, row1It + COLUMNS, row2It);
  }

  void swapCols(size_t idx1, size_t idx2) {
    assert(idx1 < COLUMNS && idx2 < COLUMNS);

    for (size_t i = 0; i < ROWS; ++i)
      std::swap((*this)[i, idx1], (*this)[i, idx2]);
  }

  // make values random
  void makeRandom(bool isSingular) {
    std::srand(time(NULL));

    std::for_each(this->begin(), this->end(), [](Field &elt) {
      elt = rand() % 100 * pow(-1.0, rand() % 7);
    });

    // make determinant equal zero
    if (isSingular) {
      auto zeroRowIt = this->cbegin();
      auto firstRowIt = this->cbegin() + COLUMNS;
      auto secndRowIt = this->begin() + COLUMNS * 2;
      auto thirdRowIt = this->begin() + COLUMNS * 3;

      for (size_t j = 0; j < COLUMNS; ++j) {
        *secndRowIt = *firstRowIt - *zeroRowIt;
        *thirdRowIt = *firstRowIt + *zeroRowIt;
      }
    }
  }

  // read values from stream
  void makeCustom(std::istream &stream) {
    std::for_each(this->begin(), this->end(),
                  [&](Field &elt) { stream >> elt; });
  }

  // make ones on diagonal and zeros elsewhere
  void makeIdentity() {
    auto it = this->begin();

    std::for_each(this->begin(), this->end(), [&](Field &elt) {
      std::distance(it, this->begin()) % (COLUMNS + 1) == 0
          ? elt = static_cast<Field>(1)
          : elt = static_cast<Field>(0);
      ++it;
    });
  }

  Matrix() {} // need explanation further
  Matrix(const std::array<Field, ROWS * COLUMNS> &otherData)
      : data(otherData) {}

  // by element multiplication by coeff
  Matrix operator*(Field coeff) {
    Matrix result = *this;
    std::for_each(result.begin(), result.end(),
                  [=](Field &elt) { elt = elt * coeff; });
    return result;
  }

  // matrix multiplication
  template <size_t N>
  Matrix<Field, ROWS, N> operator*(const Matrix<Field, COLUMNS, N> &other) {
    Matrix<Field, ROWS, N> result{};

    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < N; ++j) {
        result[i, j] = static_cast<Field>(0);
        for (size_t k = 0; k < COLUMNS; ++k)
          result[i, j] = result[i, j] + (*this)[i, k] * other[k, j];
      }
    }
    return result;
  }

  // by element sum
  Matrix operator+(const Matrix &other) {
    Matrix result = *this;

    auto it = this->cbegin();
    auto itOther = other.cbegin();
    std::for_each(result.begin(), result.end(), [&](Field &elt) {
      elt = *it + *itOther;
      ++it;
      ++itOther;
    });
    return result;
  }

  // frobenius norm
  Field euclNorm() const {
    Field result = static_cast<Field>(0);
    std::for_each(this->cbegin(), this->cend(),
                  [&](Field elt) { result = result + elt * elt; });
    return std::sqrt(result);
  }

  // max row sum norm
  Field infNorm() const {
    Field result = static_cast<Field>(0);
    for (size_t i = 0; i < ROWS; ++i) {
      Field sumRow = static_cast<Field>(0);
      for (size_t j = 0; j < COLUMNS; ++j) {
        sumRow = sumRow + std::abs((*this)[i, j]);
      }
      result = std::max(sumRow, result);
    }

    return result;
  }

  Field getMaxRowSumAbs() const {
    Field maxRowSumAbs = static_cast<int>(0);
    Field rowSumAbs = static_cast<int>(0);
    size_t iterations = 0;
    std::for_each(this->cbegin(), this->cend(), [&](Field elt) {
      if (iterations % COLUMNS == 0) {
        rowSumAbs = static_cast<int>(0);
        maxRowSumAbs = std::max(rowSumAbs, maxRowSumAbs);
      } else
        maxRowSumAbs += elt;
    });

    return maxRowSumAbs;
  }

  friend std::ostream &operator<<(std::ostream &stream, const Matrix &mat) {

    size_t iterations = 0;

    std::for_each(mat.cbegin(), mat.cend(), [&](Field elt) {
      ++iterations;
      stream << (std::abs(elt) > static_cast<Field>(EPS)
                     ? elt
                     : static_cast<Field>(0))
             << (iterations % COLUMNS == 0 ? '\n' : ' ');
    });

    return stream;
  }
};

template <typename Field, size_t ROWS, size_t COLUMNS>
Matrix<Field, COLUMNS, ROWS>
transpose(const Matrix<Field, ROWS, COLUMNS> &mat) {
  Matrix<Field, COLUMNS, ROWS> transposed{};
  for (size_t j = 0; j < COLUMNS; ++j) {
    for (size_t i = 0; i < ROWS; ++i) {
      transposed[j, i] = mat[i, j];
    }
  }
  return transposed;
}

template <typename Field, size_t ROWS, size_t COLUMNS>
Matrix<Field, ROWS, COLUMNS> diag(const Matrix<Field, ROWS, COLUMNS> &mat) {
  Matrix<Field, ROWS, COLUMNS> diag{};
  for (size_t i = 0; i < ROWS; ++i) {
    diag[i, i] = mat[i, i];
  }
  return diag;
}

template <typename Field, size_t COLUMNS>
using colVec = Matrix<Field, 1, COLUMNS>;

template <typename Field, size_t ROWS> using rowVec = Matrix<Field, ROWS, 1>;

#endif /*MATRIX_H*/