//-------------------------------------------------------
//������������ ���� � ��������� ������ �������, ��� ������� � ����������
//-------------------------------------------------------

#pragma once

//I'd like to add something

#include <vector>
#include <random>
#include "exception.h"

using namespace std;


//�������� ������ �������
class Matrix{

protected:

	int M; //����� ����� �������
	int N; //����� �������� �������
	vector<vector<double>> matrix; //��� �������� ���������

public:

	//����������� �� ���������
	Matrix() {
		int M = 1;
		int N = 1;
		matrix = { { 1 } };
		matrix.resize(1);
	}

	//����������� � �����������: ����� ����� � ��������
	Matrix(int m, int n){
		if (m <= 0 || n<=0)
			throw MyException5();
		this->M = m;
		this->N = n;
		matrix.resize(M);
		for (int i = 0; i < M; i++)
			matrix[i].resize(N);
	}

	//����������� � �����������: ����� ����� � ��������, ������ ���������
	Matrix(int m, int n, vector<double> mat) {
		if (m <= 0 || n <= 0)
			throw MyException5();
		this->M = m;
		this->N = n;

		if (this->M * this->N != mat.size())
			throw MyException1();
		matrix.resize(this->M);
		for (size_t i = 0; i < mat.size(); i += this->N){
			matrix[i / this->N].resize(this->N);
			for (size_t j = 0; j < this->N; j++){
				this->matrix[i / this->N][j] = mat[j + i];
			}
		}
	}

	//���������� ����������
	friend ostream& operator<<(ostream& out, Matrix& object);
	friend Matrix operator+(Matrix& object1, Matrix& object2);
	friend Matrix operator-(Matrix& object1, Matrix& object2);
	friend Matrix operator*(Matrix& object1, Matrix& object2);
	friend Matrix& operator*(double num, Matrix& object);

	Matrix& operator*(double num) {
		for (size_t i = 0; i < this->M; i++)
			for (size_t j = 0; j < this->N; j++)
				this->matrix[i][j] *= num;
		return *this;
	}

	//-------------------------------------------------------
	//������ ��� ������
	//-------------------------------------------------------

	//������������ �������
	Matrix& Adamara(Matrix& object1);

	//���������������� �������
	Matrix& Transpose();

	//���������� ������� � �������� ����
	void save_file(string bins);

	//�������� ������� �� ��������� �����
	void load_file(string bins);

	//-------------------------------------------------------
	//������������� �������
	//-------------------------------------------------------
	friend void swaprows(Matrix& object, size_t row1, size_t row2);
	friend Matrix& RowReduce(Matrix& object, vector<double>& bearing_vec);
	friend void rowDivision(Matrix& object, size_t row1, double b_el);
	friend void SumRow(Matrix& object, size_t row1, size_t row2, double k);
	friend double scalar_product(Matrix& object1, Matrix& object2);
	friend double trace(Matrix& object);
	friend double vector_module(Matrix& object);
	friend double vector_norm_max(Matrix& object);
	friend double matrix_module(Matrix& object);
	friend double Det(Matrix& object);
	friend Matrix& RowReduce(Matrix& object);
	friend int Rank(Matrix& object);
	friend Matrix& matrix_norm(Matrix& object);
	friend Matrix& vector_norm(Matrix& object);
	friend Matrix& inverse_matrix(Matrix& object);

	friend Matrix& ReadTextFile(Matrix& object, string filet);//
	friend ofstream& operator<<(string filet, Matrix& object);

	friend void CreateBinary(Matrix& object, string bins);
	friend Matrix& ReadBinaryFile(Matrix& object, string bins);
};

#include "functions.h"

//����� ��� ���������� ������������ �������
Matrix& Matrix::Adamara(Matrix& object1){
	if (this->N != object1.N || this->M != object1.M)
		throw MyException1();

	for (size_t i = 0; i < this->M; i++)
		for (size_t j = 0; j < this->N; j++)
			this->matrix[i][j] = this->matrix[i][j] * object1.matrix[i][j];

	return *this;
}

//����� ��� ���������������� �������
Matrix& Matrix::Transpose() {

	int M_temp = this->N;
	int N_temp = this->M;
	vector<vector<double>> temp;
	temp.resize(M_temp);
	for (size_t i = 0; i < M_temp; i++) {
		temp[i].resize(N_temp);
		for (int j = 0; j < N_temp; j++)
			temp[i][j] = this->matrix[j][i];
	}
	this->M = M_temp;
	this->N = N_temp;
	this->matrix = temp;
	temp.resize(this->M);
	for (size_t i = 0; i < this->M; i++) {
		matrix[i].resize(this->N);
		for (int j = 0; j < this->N; j++)
			this->matrix[i][j] = temp[i][j];
	}
	return *this;
}

//����� ��� ���������� ������� � �������� ����
void Matrix::save_file(string bins) {
	if (bins.substr(bins.size() - 3, 3) == "txt")
		throw MyException9();
	CreateBinary(*this, bins);
}

//����� ��� �������� ������� �� ��������� �����
void Matrix::load_file(string bins) {

	*this = ReadBinaryFile(*this, bins);
}

//-------------------------------------------------------
//�������� ���������� ������ �������
//-------------------------------------------------------

//��������� �������
class Identity : public Matrix{

public:
	Identity(int m) {
		if (m <= 0)
			throw MyException5();
		M = m;
		N = m;
		matrix.resize(M);
		for (size_t i = 0; i < M; i++){
			matrix[i].resize(N);
			for (size_t j = 0; j < M; j++) {
				if (i == j)
					matrix[i][j] = 1;
				else
					matrix[i][j] = 0;
			}
		}
	}
};

//������������ �������
class Symmetric : public Matrix {

public:

	Symmetric(vector<double> sym){
		if (sym.size() <= 0)
			throw MyException5();
		if (abs(int(sqrt(1 + 8 * sym.size())) - sqrt(1 + 8 * sym.size())) > pow(10, -5))
			throw MyException2();
		M = (-1 + sqrt(1 + 8 * sym.size())) / 2;
		N = (-1 + sqrt(1 + 8 * sym.size())) / 2;
		matrix.resize(M);//��������� ����������� ������� �� ����� �������
		size_t k = 0;
		for (size_t i = 0; i < M; i++){
			matrix[i].resize(N);
		}

		for (size_t i = 0; i < M; i++)
			for (size_t j = i; j < N; j++) {
				matrix[i][j] = sym.at(k);
				k++;
				if (j != i)
					matrix[j][i] = matrix[i][j];
			}
	}
};

//���������������� �������
class UpTriangular : public Matrix {

public:
	UpTriangular(vector<double> Uptr){
		if (Uptr.size() <= 0)
			throw MyException5();
		if (abs(int(sqrt(1 + 8 * Uptr.size())) - sqrt(1 + 8 * Uptr.size())) > pow(10, -5))
			throw MyException2();
		M = (-1 + sqrt(1 + 8 * Uptr.size())) / 2;
		N = (-1 + sqrt(1 + 8 * Uptr.size())) / 2;
		matrix.resize(M);//��������� ����������� ������� �� ����� �������
		size_t k = 0;
		for (size_t i = 0; i < M; i++){
			matrix[i].resize(N);
		}

		for (size_t i = 0; i < M; i++)
			for (size_t j = i; j < N; j++) {
				matrix[i][j] = Uptr.at(k);
				k++;
				if (j != i)
					matrix[j][i] = 0;
			}
	}
};

//���������������� �������
class LowTriangular : public Matrix {

public:
	LowTriangular(vector<double> Uptr){
		if (Uptr.size() <= 0)
			throw MyException5();
		if (abs(int(sqrt(1 + 8 * Uptr.size())) - sqrt(1 + 8 * Uptr.size())) > pow(10, -5))
			throw MyException4();
		M = (-1 + sqrt(1 + 8 * Uptr.size())) / 2;
		N = (-1 + sqrt(1 + 8 * Uptr.size())) / 2;
		matrix.resize(M);//��������� ����������� ������� �� ����� �������
		size_t k = 0;
		for (size_t i = 0; i < M; i++){
			matrix[i].resize(N);
		}

		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j <= i; j++) {
				matrix[i][j] = Uptr.at(k);
				k++;
				if (j != i)
					matrix[j][i] = 0;
			}
	}
};

//������������ �������
class Diagonal : public Matrix{

public:
	Diagonal(vector<double> diagon) {
		if (diagon.size() <= 0)
			throw MyException5();
		M = diagon.size();
		N = diagon.size();
		matrix.resize(diagon.size());
		for (size_t i = 0; i < diagon.size(); i++){
			matrix[i].resize(diagon.size());
			for (size_t j = 0; j < diagon.size(); j++) {
				if (i == j)
					matrix[i][j] = diagon[j];
				else
					matrix[i][j] = 0;
			}
		}
	}
};