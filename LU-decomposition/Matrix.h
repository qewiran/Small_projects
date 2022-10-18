#pragma once
#include <iostream>
#include <algorithm>
#include <tuple> 
#include <limits>
#include <string>
#include <cmath>

class LU_Decomposer;

class Matrix
{
	/*�� ��� ������, ����� ������������ ������������� ������, ����� ��� ������ � ����� ������� � �������, ������.
	���� ������. � */
	friend class LU_Decomposer;

protected:
	int rows, cols;
	double** values;

public:
	//������� ��� ������������� ������
	void MakeIdentity();
	void MakeCustom();

	/*������������� ��������� : ��������� - ���-� ������, ������ - ����������, ������������ - 
	����������� ������������������� ������� �������*/
	Matrix& operator* (const Matrix&);
	inline double& operator()(int, int);
	const inline double& operator()(int, int) const;
	inline double*& operator()(int);
	const inline double* operator()(int) const;
	Matrix& operator=(const Matrix&);

	/*������������: �� ��������� - ������� ������� 1�1, ������������� ����� ������ - �������� ������ ��� ����. ������� 
	�� n �����, m ��������, ����������� - �������� �������� ������� � �����
	����������: ����������� ������������ ������, ���������� ������� �������� */
	Matrix();
	Matrix(int n,int m);
	Matrix(const Matrix&);
	~Matrix();

	/*������ ������������ ����� � �������� ��� ����������*/
	void Swap_Rows(int,int);
	void Swap_Cols(int, int);

	/* ������� - ����� �������, ��������� - ������������*/
	void Display();
	void Transpose();

};
