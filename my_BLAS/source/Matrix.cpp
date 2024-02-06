#include "../headers/Matrix.h"

std::vector<double> operator+(const std::vector<double> &v1,
                              const std::vector<double> &v2)
{
    std::vector<double> result(v1.size());
    for (int i = 0; i < v1.size(); i++)
    {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

std::vector<double> operator-(const std::vector<double> &v1,
                              const std::vector<double> &v2)
{
    std::vector<double> result(v1.size());
    for (int i = 0; i < v1.size(); i++)
    {
        result[i] = v1[i] - v2[i];
    }
    return result;
}
std::vector<double> operator*(const std::vector<double> &v1, double k)
{
    std::vector<double> result(v1.size());

    for (int i = 0; i < v1.size(); i++)
    {
        result[i] = v1[i] * k;
    }
    return result;
}


Matrix diag(const Matrix &A)
{
    size_t N = A.GetN();
    size_t M = A.GetM();
    Matrix diag(N, M);

    for (size_t i = 0; i < N; i++)
    {
        diag[i][i] = A[i][i];
    }

    return diag;
}

int Matrix::GetN() const
{
    return n;
}

int Matrix::GetM() const
{
    return m;
}

int Matrix::GetRank() const
{
    return rank;
}

void Matrix::SwapRows(int ind_1, int ind_2)
{
    std::vector<double> &v1 = (*this)[ind_1];
    std::vector<double> &v2 = (*this)[ind_2];
    v1.swap(v2);
}

void Matrix::SwapCols(int ind_1, int ind_2)
{
    for (int i = 0; i < n; i++)
    {
        double temp = (*this)[i][ind_1];
        (*this)[i][ind_1] = rows[i][ind_2];
        (*this)[i][ind_2] = temp;
    }
}

std::vector<double> &Matrix::operator[](const int index)
{
    return rows[index];
}

const std::vector<double> &Matrix::operator[](const int index) const
{
    return rows[index];
}

Matrix const &Matrix::operator*(const Matrix &factor) const
{
    int rows1 = this->n;
    int rows2 = factor.n;
    int cols1 = this->m;
    int cols2 = factor.m;
    if (cols1 != rows2)
    {
        throw std::invalid_argument("matrices can\
         not be multiplied (different cols1 and rows2 number) \n");
    }
    Matrix *result = new Matrix(rows1, cols2);

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            (*result)[i][j] = 0;
            for (int k = 0; k < cols1; k++)
                (*result)[i][j] += (*this)[i][k] * factor[k][j];
        }
    }
    return *result;
}

Matrix &Matrix::operator*(const Matrix &factor)
{
    return const_cast<Matrix &>(std::as_const(*this).operator*(factor));
}

Matrix const &Matrix::operator*(const double k) const
{
    Matrix *result = new Matrix(n, m);
    for (int i = 0; i < this->n; i++)
    {
        (*result)[i] = (*this)[i] * k;
    }
    return *result;
}

Matrix &Matrix::operator*(const double k)
{
    return const_cast<Matrix &>(std::as_const(*this).operator*(k));
}

Matrix const &Matrix::operator+(const Matrix &term) const
{
    if (this->n != term.n)
        throw std::invalid_argument("matrices can not be added\
         (different rows number)\n");
    Matrix *result = new Matrix(n, m);
    for (int i = 0; i < this->n; i++)
    {
        (*result)[i] = (*this)[i] + term[i];
    }
    return *result;
}

Matrix &Matrix::operator+(const Matrix &term)
{
    return const_cast<Matrix &>(std::as_const(*this).operator+(term));
}

Matrix const &Matrix::operator-(const Matrix &term) const
{
    if (this->n != term.n)
        throw std::invalid_argument("matrices can not be subtracted\
         (different rows number)\n");

    Matrix *result = new Matrix(n, m);
    for (int i = 0; i < this->n; i++)
    {
        (*result)[i] = (*this)[i] - term[i];
    }
    return *result;
}

Matrix &Matrix::operator-(const Matrix &term)
{
    return const_cast<Matrix &>(std::as_const(*this).operator-(term));
}

Matrix &Matrix::operator=(Matrix ref)
{
    swap(*this, ref);
    return *this;
}

void Matrix::swap(Matrix &matrix1, Matrix &matrix2) noexcept
{
    std::swap(matrix1.max_row_abs, matrix2.max_row_abs);
    std::swap(matrix1.m, matrix2.m);
    std::swap(matrix1.n, matrix2.n);
    std::swap(matrix1.rows, matrix2.rows);
}

Matrix::Matrix(const Matrix &ref)
{
    if (ref.n > this->n)
    {
        this->rows.resize(ref.n);
        for (int i = this->n; i < ref.n; i++)
        {
            (*this)[i] = ref[i];
        }
    }
    else
    {
        this->rows.erase(this->rows.begin() + ref.n, this->rows.end());
        this->rows.shrink_to_fit();
    }
    this->max_row_abs = ref.max_row_abs;
    this->rows = ref.rows;
    this->n = ref.n;
    this->m = ref.m;
}
Matrix::Matrix(Matrix &&ref) noexcept : rows(std::move(ref.rows)),
                                        m(ref.m), n(ref.n)
{
}

Matrix::Matrix(int n, int m)
{
    this->n = n;
    this->m = m;
    rows.resize(n);
    for (int i = 0; i < n; i++)
    {
        rows[i].resize(m);
    }
}

void Matrix::MakeRandom(bool degen)
{
    std::srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        double row_sum = 0.0;
        for (int j = 0; j < m; j++)
        {
            (*this)[i][j] = rand() % 100 * pow(-1.0, rand() % 7);
            if (i != j)
                row_sum += std::abs((*this)[i][j]);
        }
        max_row_abs = std::max(row_sum, max_row_abs);
    }
    if (degen)
    {
        (*this)[3] = (*this)[1] - (*this)[0];
        (*this)[2] = (*this)[1] + (*this)[0];
    }
}

void Matrix::MakeCustom()
{
    for (int i = 0; i < n; i++)
    {
        double row_sum = 0.0;
        for (int j = 0; j < m; j++)
        {
            std::cin >> (*this)[i][j];
            if (i != j)
                row_sum += std::abs((*this)[i][j]);
        }
        max_row_abs = std::max(row_sum, max_row_abs);
    }
}

void Matrix::MakeIdentity()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == j)
                (*this)[i][j] = 1;
            else
                (*this)[i][j] = 0;
        }
    }
    max_row_abs = 1;
}

void Matrix::Display() const
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (std::abs((*this)[i][j]) - 1e-10 > 0.0)
                std::cout << (*this)[i][j] << " ";
            else
                std::cout << 0 << " ";
        }
        std::cout << "\n";
    }
}

Matrix Matrix::Transposed() const
{
    Matrix *Tr = new Matrix(m, n);
    for (int i = 0; i < m; i++)
    {
        double row_sum = 0.0;
        for (int j = 0; j < n; j++)
        {
            (*Tr)[i][j] = (*this)[j][i];
            if (i != j)
                row_sum += std::abs((*this)[i][j]);
        }
        (*Tr).max_row_abs = std::max(max_row_abs, row_sum);
    }
    return *Tr;
}
double Matrix::EuclNorm() const
{
    double result = 0.0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            result += (*this)[i][j] * (*this)[i][j];
        }
    }
    return std::sqrt(result);
}

double Matrix::InfNorm() const
{
    double max_row = 0.;
    double sum_row = 0.;
    for (size_t i = 0; i < m; i++)
    {
        sum_row = 0.0;
        for (size_t j = 0; j < n; j++)
        {
            sum_row += std::abs((*this)[j][i]);
        }
        max_row = std::max(max_row, sum_row);
    }

    return max_row;
}
