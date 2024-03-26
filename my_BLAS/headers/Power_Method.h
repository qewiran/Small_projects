#ifndef POWER_METHOD_H
#define POWER_METHOD_H

#include <float.h>

#include "LU_Decomposer.h"
#include "Matrix.h"
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
