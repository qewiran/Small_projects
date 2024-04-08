#ifndef POWER_METHOD_H
#define POWER_METHOD_H

#include <cstddef>
#include <float.h>

#include "LUdecomp.hpp"
#include "matrix.hpp"


static const double rtol = 1e-6;

template<typename Field, size_t ROWS, size_t COLUMNS>
ColVec<Field, ROWS> directMethod(const Matrix<Field, ROWS, COLUMNS>& mat, const ColVec<Field, ROWS>& y_0){
  auto y = y_0;
  auto z_prev = y;
  auto z_curr = y;
  auto lambda_curr = y;
  ColVec<Field, ROWS> lambda_prev{};

  auto copy = mat;

  while (std::abs((lambda_curr- lambda_prev).euclNorm() - rtol * std::max(lambda_curr.infNorm(),lambda_prev.infNorm()))>= EPS){
    z_prev = y * (1.0/y.infNorm());
    y = copy*z_prev;

    z_curr = y* (1.0 / y.infNorm());

    lambda_prev = lambda_curr;

    for (size_t i=0; i < ROWS; ++i){
      std::abs(z_prev[i] - DELTA > 0. ? lambda_curr = y[i]/z_prev[i] : lambda_curr = 0.;
          }
          }
          }

          class Power_Method {
          private:
          Matrix *pInitialMatrix = nullptr;
          double maxEigenValue = -DBL_MAX;
          double minEigenValue = DBL_MAX;

          public:
          double GetMaxEigenValue();
          double GetMinEigenValue();
          Power_Method() = default;
          Power_Method(Matrix &);
          ~Power_Method();
          Matrix *pMaxEigenVector = nullptr;
          Matrix *pMinEigenVector = nullptr;

          void DirectMethod(const Matrix &);
          void ReverseMethodShifts(const Matrix &, const double);
          void ReverseMethod(const Matrix &, const double);
          std::vector<double> EigenValues();
          };

#endif /* POWER_METHOD_H*/
