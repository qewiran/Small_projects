#ifndef ITERATION_METHOD_H
#define ITERATION_METHOD_H

#include "../headers/Matrix.h"
class Iteration_Method
{
private:
    void Decomposition();
    double q;

public:
    Matrix *pInitCopy = nullptr;
    Iteration_Method(const Matrix &, const Matrix &);
    ~Iteration_Method();
    Matrix JacobiSolution();
    Matrix SeidelSolution();
    Matrix *pR = nullptr;
    Matrix *pD = nullptr;
    Matrix *pL = nullptr;
    Matrix *pB = nullptr;
    Matrix *pB_l = nullptr;
    Matrix *pB_r = nullptr;
    Matrix *pC = nullptr;
};

#endif /*ITERATION_METHOD_H*/
