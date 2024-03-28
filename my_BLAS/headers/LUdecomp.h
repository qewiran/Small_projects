#ifndef LU_DECOMPOSER_H
#define LU_DECOMPOSER_H

#include "../headers/Matrix.h"
#include <tuple>

template <typename Field, size_t ROWS, size_t COLUMNS> struct LUPQ {
  const Matrix<Field, ROWS, COLUMNS> &initMat;
  Matrix<Field, ROWS, COLUMNS> L{};
  Matrix<Field, ROWS, COLUMNS> U{};
  Matrix<Field, ROWS, COLUMNS> P{};
  Matrix<Field, ROWS, COLUMNS> Q{};

  LUPQ(const Matrix<Field, ROWS, COLUMNS> &initMat) : initMat(initMat) {}
};

// startIdx — specification in which matrix minor max elt should be searched
// getMaxIdx(mat,2) — exclude 1st, 2nd rows and 1st, 2nd cols
template <typename Field, size_t ROWS, size_t COLUMNS>
std::tuple<size_t, size_t> getMaxIdx(const Matrix<Field, ROWS, COLUMNS> &mat,
                                     size_t startIdx) {
  size_t rowMax = startIdx, colMax = startIdx;
  Field max = mat[rowMax, colMax];
  for (size_t i = startIdx; i < ROWS; ++i) {
    for (size_t j = startIdx; j < COLUMNS; j++) {
      if (mat[i, j] > max) {
        rowMax = i;
        colMax = j;
      }
    }
  }
  return std::make_tuple(rowMax, colMax);
}

template <typename Field, size_t ROWS, size_t COLUMNS>
LUPQ<Field, ROWS, COLUMNS> LUdecomp(Matrix<Field, ROWS, COLUMNS> &mat) {
  LUPQ<Field, ROWS, COLUMNS> result(mat);

  auto &Q = result.Q;
  Q.makeIdentity();
  auto &P = result.P;
  P.makeIdentity();
  auto &L = result.L;
  L.makeIdentity();
  auto &U = result.U;
  U.makeIdentity();

  auto copy = mat;
  for (size_t i = 0; i < ROWS; ++i) {
    auto t = getMaxIdx(mat, i);
    size_t rowMax = std::get<0>(t);
    size_t colMax = std::get<1>(t);

    Q.swapCols(i, colMax);
    P.swapRows(i, rowMax);

    copy.swapRows(i, rowMax);
    copy.swapCols(i, colMax);

    if (std::abs(copy[i, i]) - static_cast<Field>(EPS) < 0.0) {
      mat.setRank(i);
      break;
    } else
      mat.setRank(i + 1);

    for (size_t j = i + 1; j < ROWS; ++j) {
      copy[j, i] = copy[j, i] / copy[i, i];
      for (size_t k = i + 1; k < COLUMNS; ++k) {
        copy[j, k] = copy[j, k] - copy[i, k] * copy[j, i];
      }
    }
  }

  for (size_t i = 0; i < ROWS; ++i) {
    for (size_t j = 0; j < COLUMNS; ++j) {
      if (i > j)
        L[i, j] = copy[i, j];
      else
        U[i, j] = copy[i, j];
    }
  }
  return result;
}

template <typename Field, size_t ROWS, size_t COLUMNS, size_t N>
bool isCompatible(const LUPQ<Field, ROWS, COLUMNS> &decomp,
                  const Matrix<Field, COLUMNS, N> &mat) {
  auto &U = decomp.U;
  bool is_compatible = true;

  for (size_t i = 0; i < ROWS; ++i) {
    if (std::abs(U[i, i]) - static_cast<Field>(EPS) < 0.0) {
      for (size_t j = 0; j < N; ++j) {
        if (std::abs(mat[i, j]) - static_cast<Field>(EPS) > 0.0) {
          is_compatible = false;
          break;
        }
      }
    }
    if (is_compatible == false)
      break;
  }
  return is_compatible;
}

template <typename Field, size_t ROWS, size_t COLUMNS, size_t N>
Matrix<Field, ROWS, N> equationSolution(Matrix<Field, ROWS, COLUMNS> &A,
                                        const Matrix<Field, COLUMNS, N> &B) {
  auto decomp = LUdecomp<Field, ROWS, COLUMNS>(A);
  auto &P = decomp.P;
  auto &Q = decomp.Q;
  auto &U = decomp.U;
  auto &L = decomp.L;
  auto B_ = P * B;

  Matrix<Field, ROWS, N> y{};

  for (size_t i = 0; i < ROWS; ++i) {
    for (size_t j = 0; j < N; ++j) {
      y[i, j] = B_[i, j];
      for (size_t k = 0; k < i; ++k) {
        y[i, j] = y[i, j] - L[i, k] * y[k, j];
      }
    }
  }

  if (!isCompatible<Field, ROWS, COLUMNS, N>(decomp, y))
    throw std::invalid_argument("slae is not compatible\n");

  Matrix<Field, ROWS, N> z{};
  for (int i = ROWS - 1; i >= 0; --i) {
    for (size_t j = 0; j < N; ++j) {
      z[i, j] = y[i, j];
    }
    if (static_cast<size_t>(i) >= decomp.initMat.getRank())
      continue;
    for (size_t j = 0; j < N; ++j) {
      for (size_t k = i + 1; k < ROWS; ++k) {
        z[i, j] -= U[i, k] * z[k, j];
      }
      z[i, j] /= U[i, i];
    }
  }
  return Q * z;
}

template <typename Field, size_t SIZE>
Matrix<Field, SIZE, SIZE> invert(Matrix<Field, SIZE, SIZE> &mat) {
  Matrix<Field, SIZE, SIZE> I{};
  I.makeIdentity();
  return equationSolution(mat, I);
}

// TODO determinant in init matrix by multiplying diag in U matrix
#endif /* LU_DECOMPOSER_H*/