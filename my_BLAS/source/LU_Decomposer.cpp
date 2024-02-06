#include "../headers/Matrix.h"
#include "../headers/LU_Decomposer.h"
#define out(a) std::cout << a << ": \n";
#define EPS 1e-12

std::tuple<double, size_t, size_t> GetMax(const Matrix &matrix, size_t start_idx)
{
    size_t max_row = start_idx, max_col = start_idx;
    double matrix_max = matrix[start_idx][start_idx];
    size_t N = matrix.GetN();
    size_t M = matrix.GetM();

    for (size_t j = start_idx; j < N; j++)
    {
        for (size_t k = start_idx; k < M; k++)
        {
            if (std::abs(matrix[j][k]) > std::abs(matrix_max))
            {
                matrix_max = matrix[j][k];
                max_row = j;
                max_col = k;
            }
        }
    }
    return std::make_tuple(matrix_max, max_row, max_col);
}

void LU_Decomposer::SetSquare()
{
    size_t N = pInitialMatrix->GetN();
    size_t M = pInitialMatrix->GetM();
    if (N < M)
    {
        pInitialMatrix->rows.resize(M, std::vector<double>(M));
    }
    else if (N > M)
    {
        for (size_t i = 0; i < N; i++)
        {
            (*pInitialMatrix)[i].resize(N);
        }
    }
    else
        std::cout << "squared\n";
}

void LU_Decomposer::Decomposition()
{
    size_t N = pInitialMatrix->GetN();
    size_t M = pInitialMatrix->GetM();
    Matrix Copy = *pInitialMatrix;
    Matrix &Q = *pQ; // ээээ
    Matrix &P = *pP; // нууу
    Matrix &L = *pL;
    Matrix &U = *pU;
    for (size_t i = 0; i < N; i++)
    {
        auto t = GetMax(Copy, i);
        size_t max_row = std::get<1>(t);
        size_t max_col = std::get<2>(t);

        Q.SwapCols(i, max_col);
        P.SwapRows(i, max_row);

        Copy.SwapRows(i, max_row);
        Copy.SwapCols(i, max_col);

        if (std::abs(Copy[i][i]) - EPS < 0.0)
        {
            pInitialMatrix->rank = i;
            break;
        }
        else
            pInitialMatrix->rank = i + 1;
        for (size_t j = i + 1; j < N; j++)
        {
            Copy[j][i] /= Copy[i][i];
            for (size_t k = i + 1; k < M; k++)
            {
                Copy[j][k] -= Copy[i][k] * Copy[j][i];
            }
        }
    }
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            if (i > j)
                L[i][j] = Copy[i][j];
            else
                U[i][j] = Copy[i][j];
        }
    }
}

bool LU_Decomposer::IsCompatible(const Matrix &y)
{
    size_t N = pU->GetN();
    bool is_compatible = true;
    for (size_t i = 0; i < N; i++)
    {
        if (std::abs((*pU)[i][i]) - 1e-10 < 0.0)
        {
            for (size_t j = 0; j < y.m; j++)
            {
                if (std::abs(y[i][j]) - 1e-12 > 0.0)
                {
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

Matrix LU_Decomposer::EquationSolution(const Matrix &B)
{
    size_t M = B.GetM();
    size_t N = pInitialMatrix->GetN();

    Matrix y(N, M);

    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < M; ++j)
        {
            y[i][j] = B[i][j];
            for (size_t k = 0; k < i; ++k)
            {
                y[i][j] -= (*pL)[i][k] * y[k][j];
            }
        }
    }
    if (!IsCompatible(y))
        throw std::invalid_argument("slae is not compatible\n");

    Matrix z(N, M);
    for (int i = N - 1; i >= 0; --i) // it's dangerous to put size_t into decrementing loop 
    {
        for (size_t j = 0; j < M; ++j)
        {
            z[i][j] = y[i][j];
        }
        if (i >= pInitialMatrix->GetRank())
            continue;
        for (size_t j = 0; j < M; ++j)
        {
            for (size_t k = i + 1; k < N; ++k)
            {
                z[i][j] -= (*pU)[i][k] * z[k][j];
            }
            z[i][j] /= (*pU)[i][i];
        }
    }
    return (*pQ) * z;
}

double LU_Decomposer::GetDeterminant()
{
    if (pU == nullptr)
        return 0;
    else
    {
        size_t N = pInitialMatrix->GetN();

        double det = 1.;
        for (size_t i = 0; i < N; ++i)
        {
            det *= (*pU)[i][i];
        }
        return det;
    }
}

Matrix LU_Decomposer::GetInverted()
{
    size_t N = pInitialMatrix->GetN();
    size_t M = pInitialMatrix->GetM();
    Matrix I(N, M);
    I.MakeIdentity();
    return EquationSolution(I * (*pP));
}
LU_Decomposer::LU_Decomposer(Matrix &InitialMatrix)
{
    // SetSquare();
    this->pInitialMatrix = &InitialMatrix;
    size_t N = pInitialMatrix->GetN();
    size_t M = pInitialMatrix->GetM();
    pL = new Matrix(N, M);
    pU = new Matrix(N, M);
    pP = new Matrix(N, M);
    pQ = new Matrix(N, M);
    (*pL).MakeIdentity();
    (*pU).MakeIdentity();
    (*pP).MakeIdentity();
    (*pQ).MakeIdentity();
    Decomposition();
}

LU_Decomposer::~LU_Decomposer()
{
    pInitialMatrix = nullptr;
    pL->~Matrix();
    pU->~Matrix();
    pQ->~Matrix();
    pP->~Matrix();
}