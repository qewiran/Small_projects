#ifndef ITERATION_METHOD_H
#define ITERATION_METHOD_H

#include "../headers/Matrix.h"

template <typename Field, size_t ROWS, size_t COLUMNS> struct DLR {
  const Matrix<Field, ROWS, COLUMNS> &initMat;
  Matrix<Field, ROWS, COLUMNS> D{};
  Matrix<Field, ROWS, COLUMNS> L{};
  Matrix<Field, ROWS, COLUMNS> R{};

  DLR(const Matrix<Field, ROWS, COLUMNS> &initMat) : initMat(initMat) {}
};

// get diagonal, left triangle, right triangle
template <typename Field, size_t ROWS, size_t COLUMNS>
DLR<Field, ROWS, COLUMNS> IMdecomp(const Matrix<Field, ROWS, COLUMNS> &mat) {

  DLR<Field, ROWS, COLUMNS> decomp(mat);
  auto &D = decomp.D;
  auto &L = decomp.L;
  auto &R = decomp.R;
  D = diag(mat);
  Field maxRowSumAbs = mat.getMaxRowSumAbs();

  for (size_t i = 0; i < ROWS; ++i) {
    if (std::abs(D[i, i]) - EPS < maxRowSumAbs)
      D[i, i] = D[i, i] + maxRowSumAbs;

    if (i > 0) {
      std::copy(mat.cbegin() + (COLUMNS * i), mat.cbegin() + (COLUMNS * i) + i,
                L.begin() + (COLUMNS * i));
    }

    std::copy(mat.cbegin() + (COLUMNS * i) + (i + 1),
              mat.cbegin() + COLUMNS * (i + 1),
              R.begin() + COLUMNS * i + i + 1);
  }

  return decomp;
}

// doesnt work (dont know why)
template <typename Field, size_t ROWS, size_t COLUMNS, size_t N>
Matrix<Field, ROWS, N> jacobiSolution(const Matrix<Field, ROWS, COLUMNS> &A,
                                      const Matrix<Field, COLUMNS, N> &b) {
  auto decomp = IMdecomp<Field, ROWS, COLUMNS>(A);
  auto &D = decomp.D;
  auto &L = decomp.L;
  auto &R = decomp.R;

  auto Dinv = invert(D);
  auto B = Dinv * (L + R) * static_cast<Field>(-1);
  auto C = Dinv * b;

  Field B_norm = B.euclNorm();
  Field C_norm = C.euclNorm();

  Field q = 0.1;
  if (B_norm - 1.0 < EPS)
    q = B_norm;

  Field k_estimated = std::ceil(std::log(EPS / C_norm * (1 - q)) / std::log(q));
  Field k_iter = 1;
  auto prev = C;
  auto curr = prev;
  Field norm = curr.euclNorm();

  while (q / (1 - q) * norm > static_cast<Field>(EPS)) {
    curr = B * prev + C;
    norm = (curr + (prev * static_cast<Field>(-1))).euclNorm();
    ++k_iter;
    prev = curr;
  }
  return curr;
}

template <typename Field, size_t ROWS, size_t COLUMNS, size_t N>
Matrix<Field, ROWS, N> seidelSolution(const Matrix<Field, ROWS, COLUMNS> &A,
                                      const Matrix<Field, COLUMNS, N> &b) {
  auto decomp = IMdecomp<Field, ROWS, COLUMNS>(A);
  auto &D = decomp.D;
  auto &L = decomp.L;
  auto &R = decomp.R;

  auto Dinv = invert(D);
  auto B = Dinv * (L + R) * static_cast<Field>(-1);
  auto B_l = Dinv * L * static_cast<Field>(-1);
  auto B_r = Dinv * R * static_cast<Field>(-1);
  auto C = Dinv * b;

  Field B_norm = B.euclNorm();
  Field C_norm = B.euclNorm();

  Field q = 0.1;
  if (B_norm - 1.0 < EPS)
    q = B_norm;

  Field k_estimated = std::ceil(std::log(EPS / C_norm * (1 - q)) / std::log(q));
  Field k_iter = 1;
  auto prev = C;
  auto curr = prev;
  Field norm = curr.euclNorm();

  std::cout << "prev: " << prev << "\ncurr: " << curr << '\n';
  while (q / (1 - q) * norm > static_cast<Field>(EPS)) {
    for (size_t i = 0; i < ROWS; ++i) {
      curr[i, 0] = static_cast<Field>(0);
      for (size_t j = 0; j < i; ++j) {
        if (j < i)
          curr[i, 0] = curr[i, 0] + B_l[i, j] * curr[j, 0];
        else
          curr[i, 0] = curr[i, 0] + B_r[i, j] * prev[j, 0];
      }
      curr[i, 0] = curr[i, 0] + C[i, 0];
    }
    norm = (curr + (prev * static_cast<Field>(-1))).euclNorm();
    ++k_iter;
    prev = curr;
  }
  // std::cout << "k: " << k_iter << '\n';
  return curr;
}

// class Iteration_Method {
// private:
//   void Decomposition();
//   double q;

// public:
//   Matrix *pInitCopy = nullptr;
//   Iteration_Method(const Matrix &, const Matrix &);
//   ~Iteration_Method();
//   Matrix JacobiSolution();
//   Matrix SeidelSolution();
//   Matrix *pR = nullptr;
//   Matrix *pD = nullptr;
//   Matrix *pL = nullptr;
//   Matrix *pB = nullptr;
//   Matrix *pB_l = nullptr;
//   Matrix *pB_r = nullptr;
//   Matrix *pC = nullptr;
// };

#endif /*ITERATION_METHOD_H*/
