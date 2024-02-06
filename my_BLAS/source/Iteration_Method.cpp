
#include "../headers/Iteration_Method.h"
#include "../headers/QR_Decomposer.h"
#include "../headers/LU_Decomposer.h"
#include <chrono>
#define tick() std::chrono::high_resolution_clock::now();
#define interval(t1, t2) std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
void Iteration_Method::Decomposition()
{
    size_t N = pInitCopy->GetN();
    size_t M = pInitCopy->GetM();
    pD = new Matrix(N, M);
    pL = new Matrix(N, M);
    pR = new Matrix(N, M);
    for (int i = 0, j = 1; i < N; i++, ++j)
    {
        if (std::abs((*pInitCopy)[i][i]) - pInitCopy->max_row_abs < 0.0)
            (*pD)[i][i] = pInitCopy->max_row_abs + (*pInitCopy)[i][i];
        else
            (*pD)[i][i] = (*pInitCopy)[i][i];

        std::copy((*pInitCopy)[i].begin(),
                  (*pInitCopy)[i].begin() + (j - 1), (*pL)[i].begin());

        std::copy((*pInitCopy)[i].begin() + j,
                  (*pInitCopy)[i].end(), (*pR)[i].begin() + j);
    }
}

Iteration_Method::Iteration_Method(const Matrix &A, const Matrix &b)
{
    pInitCopy = new Matrix;
    *pInitCopy = A; //мб вместо копии все же работать с указателем на исходную

    pB = new Matrix;
    pB_l = new Matrix;
    pB_r = new Matrix;
    pC = new Matrix;
    Decomposition();

    Matrix &L = *pL;
    Matrix &R = *pR;
    Matrix &D = *pD;

    size_t N = pInitCopy->GetN();
    for (int i = 0; i < N; i++)
        (*pInitCopy)[i][i] = D[i][i];

    LU_Decomposer LU_D(D);
    std::cout << (*pInitCopy).max_row_abs << "\n";
    D = LU_D.GetInverted();

    *pB = D * (L + R) * (-1.0);
    *pB_l = D * L * (-1.0);
    *pB_r = D * R * (-1.0);
    *pC = D * b;

    double B_norm = (*pB).EuclNorm();
    double C_norm = (*pC).EuclNorm();
    std::cout << B_norm << " :b norm and c norm: " << C_norm << '\n';
    B_norm - 1.0 > 1e-14 ? q = 0.1 : q = B_norm;
    double k = std::ceil(std::log(1e-13 / C_norm * (1 - q)) / std::log(q));
    std::cout << "calculated k:" << k << '\n';
}

Matrix Iteration_Method::JacobiSolution()
{
    double q = this->q;
    int k = 1;
    Matrix prev_iteration(*pC);
    Matrix curr_iteration = prev_iteration;
    double norm = curr_iteration.EuclNorm();
    while (q / (1 - q) * norm > 1e-13)
    {
        curr_iteration = (*pB) * prev_iteration + (*pC);
        auto diff = curr_iteration - prev_iteration;
        norm = diff.EuclNorm();
        // std::cout << norm << "\n";
        ++k;
        prev_iteration = curr_iteration;
    }
    std::cout << "K: " << k << "\n";
    return curr_iteration;
}

Matrix Iteration_Method::SeidelSolution()
{
    double q = this->q;
    int k = 1;
    size_t N = pInitCopy->GetN();
    Matrix prev_iteration(*pC);
    Matrix curr_iteration = prev_iteration;
    double norm = curr_iteration.EuclNorm();
    while (q / (1 - q) * norm > 1e-13)
    {
        for (int i = 0; i < N; i++)
        {
            curr_iteration[i][0] = 0.0;
            for (int j = 0; j < i; j++)
            {
                curr_iteration[i][0] += (*pB_l)[i][j] * curr_iteration[j][0];
            }
            for (int j = i; j < N; j++)
            {
                curr_iteration[i][0] += (*pB_r)[i][j] * prev_iteration[j][0];
            }
            curr_iteration[i][0] += (*pC)[i][0];
        }
        norm = (curr_iteration - prev_iteration).EuclNorm();
        ++k;
        prev_iteration = curr_iteration;
    }
    std::cout << "K: " << k << "\n";
    return curr_iteration;
}



Iteration_Method::~Iteration_Method()
{
    if (pL != nullptr)
        pL->~Matrix();

    if (pD != nullptr)
        pD->~Matrix();

    if (pR != nullptr)
        pR->~Matrix();
}