#ifndef QR_DECOMPOSER_H
#define QR_DECOMPOSER_H

#include "../headers/Matrix.h"
class QR_Decomposer
{
private:
    void DecompIteration(size_t); // с аргументом, потому что костыль из-за уменьшения итерационно матрицы
                                  // для поиска СЧ
    void Decomposition();
    void DecompWithShifts();
    const Matrix *pInitialMatrix = nullptr;
    Matrix *Hess_form = nullptr;
    Matrix *pQ = nullptr;
    Matrix *pR = nullptr;
    std::vector<double> eigen_values;

public:
    std::vector<double> GetEigenValues();
    QR_Decomposer(const Matrix &, bool shifts); // 1 if QR decomp with shifts needed
    ~QR_Decomposer();
};

double sgn(double);
Matrix HessenbergForm(const Matrix &);
