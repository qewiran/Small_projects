#ifndef POWER_METHOD_H
#define POWER_METHOD_H

#include "LUdecomp.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cstddef>

template <typename Field, size_t ROWS, size_t COLUMNS>
std::tuple<ColVec<Field, ROWS>, Field>
directMethod(const Matrix<Field, ROWS, COLUMNS>& mat,
             const ColVec<Field, ROWS>& y_0) {
  auto y = y_0;
  auto z_prev = y_0;
  auto z_curr = y_0;
  auto lambda_curr = y_0;
  ColVec<Field, ROWS> lambda_prev{};
  Field maxEigenValue = static_cast<Field>(0);

  while (std::abs((lambda_curr + lambda_prev*static_cast<Field>(-1)).infNorm() -
                  rtol * std::max(lambda_curr.infNorm(),
                                  lambda_prev.infNorm())) >= EPS) {
    z_prev = y * (1.0 / y.infNorm());
    y = mat * z_prev;

    z_curr = y * (1.0 / y.infNorm());
    lambda_prev = lambda_curr;

    for (size_t i = 0; i < ROWS; ++i) {
      std::abs(z_prev[i] - DELTA) > 0. ? lambda_curr[i] = y[i] / z_prev[i]
                                       : lambda_curr[i] = 0.;
    }
    size_t nonZeroElts = 0;
    Field lambda_max = 0.;
    for (size_t i = 0; i < ROWS; ++i) {
      lambda_max = lambda_max + lambda_curr[i];
      if (std::abs(lambda_curr[i]) > EPS)
        ++nonZeroElts;
    }
    maxEigenValue = lambda_max / static_cast<Field>(nonZeroElts);
  }
  return std::make_tuple(z_curr, maxEigenValue);
}

template <typename Field, size_t ROWS, size_t COLUMNS>
std::tuple<ColVec<Field, ROWS>, Field>
reverseMethodShifts(const Matrix<Field, ROWS, COLUMNS>& mat,
                    const ColVec<Field, ROWS>& y_0, Field sigma) {

  auto y = y_0;
  auto z_prev = y_0;
  auto z_curr = y_0 * static_cast<Field>(2);
  auto mu = y_0 * static_cast<Field>(2);
  auto sigma_curr = sigma;
  auto sigma_prev = y_0 * static_cast<Field>(2);
  Field maxEigenValue = static_cast<Field>(0);
  Matrix<Field, ROWS, COLUMNS> E{};
  E.makeIdentity();

  while (/* std::abs((sigma_curr - sigma_prev).infNorm() -
                  rtol * std::max(sigma_curr.infNorm(),
                                  sigma_prev.infNorm())) >= EPS */
         std::abs(sigma_prev - sigma_curr) > DELTA) {
    sigma_prev = sigma_curr;

    z_prev = y * (1.0 / y.infNorm());
    y = equationSolution(mat - E * sigma_curr, z_prev);
    z_curr = y * (1.0 / y.infNorm());

    auto y_it = y.cbegin();
    auto z_it = z_prev.cbegin();

    std::for_each(mu.begin(), mu.end(), [&](Field& elt) {
      std::abs(y_it - DELTA) > 0. ? elt = z_it / y_it : elt = 0.;
      ++z_it;
      ++y_it;
    });

    size_t nonZeroElts = 0;
    sigma_curr = 0.;

    std::for_each(mu.cbegin(), mu.cend(), [&](Field elt) {
      sigma_curr = sigma_curr + elt;
      if (std::abs(elt) > EPS)
        ++nonZeroElts;
    });
    maxEigenValue = sigma_curr / static_cast<Field>(nonZeroElts) + sigma_prev;
  }
  return std::make_tuple(z_curr, maxEigenValue);
}

template <typename Field, size_t ROWS, size_t COLUMNS>
std::tuple<ColVec<Field, ROWS>, Field>
reverseMethod(const Matrix<Field, ROWS, COLUMNS>& mat,
              const ColVec<Field, ROWS>& y_0, Field sigma) {

  auto y = y_0;
  auto z_prev = y_0;
  auto z_curr = y_0 * static_cast<Field>(2);
  auto lambda_curr = y_0 * static_cast<Field>(2);
  auto lambda_prev = y_0;
  Field maxEigenValue = static_cast<Field>(0);
  Matrix<Field, ROWS, COLUMNS> E{};
  E.makeIdentity();

  while (std::abs((lambda_curr + lambda_prev*static_cast<Field>(-1)).infNorm() -
                  rtol * std::max(lambda_curr.infNorm(),
                                  lambda_prev.infNorm())) >= EPS) {
    z_prev = y * (1.0 / y.infNorm());
    y = equationSolution(mat - E * sigma, z_prev);
    z_curr = y * (1.0 / y.infNorm());
    lambda_prev = lambda_curr;
    auto y_it = y.cbegin();
    auto z_it = z_prev.cbegin();
    std::for_each(lambda_curr.begin(), lambda_curr.end(), [&](Field& elt) {
      std::abs(y_it - DELTA) > 0. ? elt = z_it / y_it : elt = 0.;
      ++z_it;
      ++y_it;
    });
    size_t nonZeroElts = 0;
    double lambda_max = 0.;

    std::for_each(lambda_curr.cbegin(), lambda_curr.cend(), [&](Field elt) {
      lambda_max = lambda_max + elt;
      if (std::abs(elt) > EPS)
        ++nonZeroElts;
    });
    maxEigenValue = lambda_max / static_cast<Field>(nonZeroElts) + sigma;
  }
  return std::make_tuple(z_curr, maxEigenValue);
}

#endif /* POWER_METHOD_H*/
