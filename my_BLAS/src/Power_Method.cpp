#include "../headers/Power_Method.h"
#include "../headers/QR_Decomposer.h"
#include <algorithm>
#include <iterator>
#include <vector>
#define rtol 1e-6
#define EPS 1e-10
#define DELTA 1e-8
#include <thread>

using std::abs, std::max;
extern double sgn(double var);

template <typename T> void nullify(std::vector<T> &vec) {
  for (auto u : vec) {
    u = T(0);
  }
}

int cardinality(std::vector<bool> &vec) {
  int res = 0;
  for (auto u : vec) {
    if (u)
      res++;
  }
  return res;
}

double Power_Method::GetMaxEigenValue() { return this->maxEigenValue; }

double Power_Method::GetMinEigenValue() { return this->minEigenValue; }

Power_Method::Power_Method(Matrix &InitialMatrix) {
  pInitialMatrix = &InitialMatrix;
}

Power_Method::~Power_Method() {
  this->pInitialMatrix = nullptr;

  if (pMaxEigenVector != nullptr)
    pMaxEigenVector->~Matrix();

  if (pMinEigenVector != nullptr)
    pMinEigenVector->~Matrix();
}

void Power_Method::DirectMethod(const Matrix &y_0) {
  Matrix y = y_0;
  size_t N = y.GetN();
  std::vector<bool> I(N);
  Matrix z_prev = y;
  Matrix z_curr = y;
  Matrix lambda_curr = y;
  Matrix lambda_prev(N, 1);

  auto Copy = *(this->pInitialMatrix);

  while ((abs((lambda_curr - lambda_prev).InfNorm()) -
          rtol * max(lambda_curr.InfNorm(), lambda_prev.InfNorm())) >= EPS) {
    z_prev = y * (1.0 / y.InfNorm());

    y = Copy * z_prev;

    z_curr = y * (1.0 / y.InfNorm());

    nullify(I);
    lambda_prev = lambda_curr;

    for (size_t i = 0; i < N; i++) {
      if (abs(z_prev[i][0]) - DELTA > 0.0) {
        I[i] = 1;
        lambda_curr[i][0] = y[i][0] / z_prev[i][0];
      } else {
        lambda_curr[i][0] = 0.0;
      }
    }
  }

  int card_I = cardinality(I);
  double lambda_max = 0.0;
  for (size_t i = 0; i < N; i++) {
    if (I[i])
      lambda_max += lambda_curr[i][0];
  }
  this->maxEigenValue = lambda_max / (double)card_I;

  this->pMaxEigenVector = new Matrix;
  *(this->pMaxEigenVector) = z_curr;
}

void Power_Method::ReverseMethodShifts(const Matrix &y_0, const double sigma) {
  size_t N = y_0.GetN();
  std::vector<bool> I(N);

  Matrix z_prev = y_0;
  Matrix z_curr = y_0 * 2.0;

  Matrix mu = y_0 * 2.0;
  double sigma_curr = sigma;
  double sigma_prev = sigma * 2.0;

  Matrix E(N, N);
  E.MakeIdentity();
  int card_I;
  Matrix y = y_0;
  double lambda = 0.0;
  int iterations = 0;
  while (/*(abs((z_curr - z_prev).EuclNorm()) -
          rtol * max(z_curr.EuclNorm(), z_prev.EuclNorm())) >= EPS ||*/
         abs(sigma_prev - sigma_curr) > DELTA) {
    iterations++;
    sigma_prev = sigma_curr;
    LU_Decomposer LU_A(*pInitialMatrix - E * sigma_curr);

    z_prev = y * (1.0 / y.InfNorm());

    y = LU_A.EquationSolution(z_prev);

    z_curr = y * (1.0 / y.InfNorm());

    nullify(I);

    for (size_t i = 0; i < N; i++) {
      if (abs(y[i][0]) - DELTA > 0.0) {
        I[i] = 1;
        mu[i][0] = z_prev[i][0] / y[i][0];
      } else {
        mu[i][0] = 0.0;
      }
    }
    card_I = cardinality(I);
    sigma_curr = 0.0;
    for (size_t i = 0; i < N; i++) {
      if (I[i])
        sigma_curr += mu[i][0];
    }
    sigma_curr /= double(cardinality(I));
    sigma_curr += sigma_prev;
    std::cout << sigma_curr << ' ' << sigma_prev << "\n";
  }
  std::cout << sigma_curr << " iterations " << iterations << '\n';
}

void Power_Method::ReverseMethod(const Matrix &y_0, const double sigma) {
  size_t N = y_0.GetN();
  std::vector<bool> I(N);

  Matrix z_prev = y_0;
  Matrix z_curr = y_0 * 2.0;

  Matrix lambda_prev = y_0;
  Matrix lambda_curr = y_0 * 2.0;

  Matrix E(N, N);
  E.MakeIdentity();
  Matrix y = y_0;
  LU_Decomposer LU_A(*pInitialMatrix - E * sigma);
  double sum_lambda = 0;
  int card_I;
  int iterations = 0;
  while ((lambda_curr - lambda_prev).InfNorm() >
         rtol * max(lambda_curr.InfNorm(), lambda_prev.InfNorm())) {
    iterations++;
    z_prev = y * (1.0 / y.InfNorm());
    y = LU_A.EquationSolution(z_prev);

    z_curr = y * (1.0 / y.InfNorm());

    nullify(I);
    lambda_prev = lambda_curr;

    for (size_t i = 0; i < N; i++) {
      if (abs(y[i][0]) - DELTA > 0.0) {
        I[i] = 1;
        lambda_curr[i][0] = z_prev[i][0] / y[i][0];
      } else {
        lambda_curr[i][0] = 0.0;
      }
    }
  }
  card_I = cardinality(I);

  for (size_t i = 0; i < N; i++) {
    if (I[i])
      sum_lambda += lambda_curr[i][0];
  }
  std::cout << sum_lambda / (double)card_I + sigma
            << " iterations: " << iterations << '\n';
}
