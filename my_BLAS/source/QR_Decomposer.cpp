#include "../headers/Matrix.h"
#include "../headers/QR_Decomposer.h"
#define DELTA 1e-8

using std::cout, std::cin, std::abs;
double sgn(double val)
{
    return (double(0) < val) - (val < double(0));
};

extern Matrix diag(const Matrix &);

Matrix HessenbergForm(const Matrix &A)
{
    size_t N = A.GetN();
    Matrix Hess_form = A;
    Matrix v(N, 1);
    Matrix v_t;
    Matrix H_i(N, N);
    Matrix E(N, N);
    E.MakeIdentity();

    double s = 0.0, mu = 0.0;
    size_t k = 1;
    for (size_t j = 0; j < N - 2; j++)
    {
        s = 0.0;
        for (size_t i = j + 1; i < N; i++)
        {
            s += Hess_form[i][j] * Hess _form[i][j];
        }

        s = std::sqrt(s) * -sgn(Hess_form[j + 1][j]);

        for (size_t i = 0; i < N; i++)
        {
            if (i < j + 1)
                v[i][0] = 0.0;
            else
                v[i][0] = Hess_form[i][j];
        }

        mu = 1. / std::sqrt(2.0 * s * (s - Hess_form[j + 1][j]));

        v[j + 1][0] -= s;
        v = v * mu;
        v_t = v.Transposed();
        H_i = E - ((v * 2) * v_t);
        Hess_form = H_i * Hess_form * H_i;
    }
    return Hess_form;
}

void QR_Decomposer::DecompIteration(size_t len)
{
    size_t N = len;
    size_t n = Hess_form->GetN();
    Matrix G(n, n);
    G.MakeIdentity();
    
    *pR = *this->Hess_form;
    Matrix &R = *pR;
    Matrix &Q = *pQ;
    Q = G;
    double c = 0., s = 1., denom = 1.;
    for (int j = 0; j < N - 1; j++)
    {
        G.MakeIdentity();
        denom = std::sqrt(R[j][j] * R[j][j] + R[j + 1][j] * R[j + 1][j]);
        if (abs(denom) - DELTA > 0.0)
        {
            c = R[j][j] / denom;
            s = -R[j + 1][j] / denom;
        }

        G[j][j] = c;
        G[j + 1][j] = s;
        G[j][j + 1] = -s;
        G[j + 1][j + 1] = c;
        R = G * R;
        Q = G * Q;
    }
    
}

void QR_Decomposer::Decomposition()
{
    size_t N = pInitialMatrix->GetN();
    double b_curr = (*Hess_form)[N - 1][N - 1];
    double b_prev = 2 * b_curr;
    while (N > 1)
    {
        while (abs(b_prev - b_curr) - (1.0 / 3.0 * abs(b_curr)) > DELTA ||
               abs((*Hess_form)[N - 1][N - 2]) > DELTA)
        {
            b_prev = b_curr;
            DecompIteration(N);
            *Hess_form = (*this->pR) * (*this->pQ).Transposed();
            b_curr = (*Hess_form)[N - 1][N - 1];
        Hess_form->Display();
        }
        eigen_values.push_back(b_curr);
        N--;
    }
    Hess_form->Display();
    eigen_values.push_back((*Hess_form)[0][0]);
}

void QR_Decomposer::DecompWithShifts()
{
    size_t N = pInitialMatrix->GetN();
    size_t N_init = N;
    Matrix E(N, N);
    E.MakeIdentity();
    double b_curr = (*Hess_form)[N - 1][N - 1];
    double b1 = b_curr;
    double b_prev = 2 * b_curr;
    while (N > 1)
    {
        while (abs(b_prev - b_curr) - (1.0 / 3.0 * abs(b_curr)) > DELTA ||
               abs((*Hess_form)[N - 1][N - 2]) > DELTA)
        {
            b_prev = b_curr;
            *Hess_form = *Hess_form - E * b_curr;
            DecompIteration(N);
            *Hess_form = (*this->pR) * (*this->pQ).Transposed() + E * b_curr;
            b_curr = (*Hess_form)[N - 1][N - 1];
        }
        eigen_values.push_back(b_curr);
        N--;
      
    }
    eigen_values.push_back((*Hess_form)[0][0]);
}

QR_Decomposer::QR_Decomposer(const Matrix &initialMatrix, bool shift)
{
    pInitialMatrix = &initialMatrix;
    pQ = new Matrix;
    pR = new Matrix;
    Hess_form = new Matrix;
    *Hess_form = HessenbergForm(*pInitialMatrix);
    cout << "Hess_form: \n";
    Hess_form->Display();
    if (shift)
        DecompWithShifts();
    else
        Decomposition();
}

std::vector<double> QR_Decomposer::GetEigenValues()
{
    return eigen_values;
}

QR_Decomposer::~QR_Decomposer()
{
    pInitialMatrix = nullptr;
}