#ifndef QR_DECOMPOSER_H
#define QR_DECOMPOSER_H

#include "../headers/Matrix.h"
#define DELTA 1e-10

template <typename Field> Field sgn(Field val) {
  return (static_cast<Field>(0) < val) - (val < static_cast<Field>(0));
}

template <typename Field, size_t SIZE>
Matrix<Field, SIZE, SIZE> hessenbergForm(const Matrix<Field, SIZE, SIZE> &mat) {
  Matrix<Field, SIZE, SIZE> result = mat;
  ColVec<Field, SIZE> v{};
  Matrix<Field, SIZE, SIZE> iter{};
  Matrix<Field, SIZE, SIZE> I{};
  I.makeIdentity();

  Field s, mu;
  for (size_t j = 0; j < SIZE - 2; ++j) {

    s = static_cast<Field>(0);
    for (size_t i = j + 1; i < SIZE; ++i) {
      s = s + (result[i, j] * result[i, j]);
    }
    s = std::sqrt(s) * -sgn(result[j + 1, j]);

    for (size_t i = 0; i < SIZE; ++i) {
      if (i < j + 1)
        v[i] = static_cast<Field>(0);
      else
        v[i] = result[i, j];
    }
    mu = static_cast<Field>(1) / std::sqrt(2.0 * s * (s - result[j + 1, j]));

    v[j + 1] = v[j + 1] - s;
    v = v * mu;
    iter = I + ((v * static_cast<Field>(2)) * transpose(v) *
                static_cast<Field>(-1));
    result = iter * result * iter;
  }

  return result;
}

template <typename Field, size_t SIZE>
Matrix<Field, SIZE, SIZE>
getRotationGivensMat(const Matrix<Field, SIZE, SIZE> &mat, size_t idx) {
  Matrix<Field, SIZE, SIZE> G{};
  G.makeIdentity();

  Field c = static_cast<Field>(0);
  Field s = static_cast<Field>(1);

  Field denom = std::sqrt(mat[idx, idx] * mat[idx, idx] +
                          mat[idx + 1, idx] * mat[idx + 1, idx]);

  if (std::abs(denom) - static_cast<Field>(DELTA) > 0.0) {
    c = mat[idx, idx] / denom;
    s = -mat[idx + 1, idx] / denom;
  }

  G[idx, idx] = c;
  G[idx + 1, idx] = s;
  G[idx, idx + 1] = -s;
  G[idx + 1, idx + 1] = c;

  return G;
}

template <typename Field, size_t SIZE>
std::tuple<Matrix<Field, SIZE, SIZE>, Matrix<Field, SIZE, SIZE>>
QRdecompIteration(const Matrix<Field, SIZE, SIZE> &hessFormMat, size_t len) {

  Matrix<Field, SIZE, SIZE> R = hessFormMat;

  Matrix<Field, SIZE, SIZE> Q{};
  Q.makeIdentity();

  for (size_t i = 0; i < len - 1; ++i) {
    auto G = getRotationGivensMat(R, i);
    R = G * R;
    Q = G * Q;
  }
  return std::make_tuple(Q, R);
}

template <typename Field, size_t SIZE>
std::tuple<Matrix<Field, SIZE, SIZE>, Matrix<Field, SIZE, SIZE>>
QRdecomp(const Matrix<Field, SIZE, SIZE> &mat) {
  auto H = hessenbergForm(mat);
  Matrix<Field, SIZE, SIZE> I{};
  Matrix<Field, SIZE, SIZE> Q{};
  Matrix<Field, SIZE, SIZE> R{};
  auto& Qr = Q;
  auto& 

  I.makeIdentity();

  Field bCurr = H[SIZE - 1, SIZE - 1];
  Field bPrev = H[SIZE - 1, SIZE - 1] * static_cast<Field>(2);

  for (size_t n = SIZE; n > 1; --n) {
    while (std::abs(bPrev - bCurr) - (1. / 3. * std::abs(bCurr)) > DELTA ||
           std::abs(H[n - 1, n - 2]) > DELTA) {
      bPrev = bCurr;
      auto t = QRdecompIteration(H, n);
      Q = std::get<0>(t);
      R = std::get<1>(t);
      H = R * transpose(Q);
      bCurr = H[n - 1, n - 1];
    }
  }
  return std::make_tuple(Q, R);
}
// class QR_Decomposer {
// private:
//   void DecompIteration(size_t); // с аргументом, потому что костыль из-за
//                                 // уменьшения итерационно матрицы для поиска
//                                 СЧ
//   void Decomposition();
//   void DecompWithShifts();
//   const Matrix *pInitialMatrix = nullptr;
//   Matrix *Hess_form = nullptr;
//   Matrix *pQ = nullptr;
//   Matrix *pR = nullptr;
//   std::vector<double> eigen_values;

// public:
//   std::vector<double> GetEigenValues();
//   QR_Decomposer(const Matrix &,
//                 bool shifts); // 1 if QR decomp with shifts needed
//   ~QR_Decomposer();
// };

// double sgn(double);
// Matrix HessenbergForm(const Matrix &);

#endif /* QR_DECOMPOSER_H*/