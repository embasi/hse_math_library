#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <cassert>
#include <iostream>
#include <algorithm>
#include "Matrix.h"


int main() {
	
	string file1 = "loadings.txt";
	string file2 = "test.txt";
	string file3 = "bin.dat";
	try {
		vector<double> v1 = { 5,4,8,-9,16,3 };
		vector<double> v2 = { -3,-2,5,-4,8, -6 };
		vector<double> v3 = { 6,4,-5,15,-7,8 };
		Matrix m1(3, 2, v1);
		Matrix m2(2, 3, v2);
		Matrix m0(3, 2, v3);

		//������������ ������ 1

		cout << "Basic matrix:" << endl;
		cout << m1 << endl;

		cout << "Another matrix:" << endl;
		cout << m0 << endl;

		cout << "Matrix addition:" << endl;
		m1 + m0;
		cout << m1 << endl;

		cout << "Matrix subtraction:" << endl;
		m1 - m0;
		cout << m1 << endl;

		cout << "Matrix multiplication by number:" << endl;
		cout << 3 * m1 << endl;

		cout << "Multiplying a matrix by a number on the other side:" << endl;
		cout << m1 * 3 << endl;

		cout << "Matrix multiplication:" << endl;
		Matrix m3 = m1 * m2;
		cout << m3 << endl;

		cout << "Adamara multiplication:" << endl;
		Matrix m4 = m1.Adamara(m0);
		cout << m4 << endl;

		cout << "Diagonal matrix:" << endl;
		Diagonal m5(v1);
		cout << m5 << endl;

		cout << "Lower triangular matrix:" << endl;
		LowTriangular m6(v1);
		cout << m6 << endl;

		cout << "Upper triangular matrix:" << endl;
		UpTriangular m7(v1);
		cout << m7 << endl;

		cout << "Symmetric matrix:" << endl;
		Symmetric m8(v1);
		cout << m8 << endl;

		cout << "Identity matrix:" << endl;
		Identity m9(4);
		cout << m9 << endl << endl;
		
		//������������ ������ 2

		vector<double> v4 = { 17,3,3,-14,5,26,0,0, 9 };
		vector<double> v5 = { 1,2,6,4,5,-6,7,8,9 };

		Matrix t2(3, 3, v5);
		cout << "Next matrix:" << endl;
		cout << t2 << endl;

		cout << "The trace of the previous matrix is :" << trace(t2) << endl;

		cout << "Determinant of the previous matrix is: " << Det(t2) << endl;
		cout << endl;

		Matrix x1(1, 9, v4);
		Matrix x2(1, 9, v5);

		cout << x1;
		cout << x2 << endl;
		cout << "Scalar product of vectors is :" << scalar_product(x1, x2) << endl;

		cout << "Euclidean norm of the second vector is: " << endl;
		cout << vector_norm(x2) << endl;

		cout << "The max norm of the second vector is: " << vector_norm_max(x2) << endl;

		cout << "Norm of the previous matrix is:" << endl;
		cout << matrix_norm(t2) << endl << endl;

		//������������ ������ 3

		cout << x1;
		Matrix x3(1, 9, v5);
		cout << x3 << endl;
		cout << "Angle between the previous vectors is: " << vec_angle(x1, x3) << endl;

		Matrix  t1(3, 3, v4);
		cout << t1 << endl;
		cout << "Rank of the previous matrix is:" << Rank(t1) << endl;

		Matrix inv(3, 3, v4);
		cout << "Inverse matrix:" << endl;
		cout << inverse_matrix(inv) << endl << endl << endl;

		cout << "Transposed matrix:" << endl;
		cout << inv.Transpose() << endl;

		cout << "The alteration of type of the matrix to row reduced by Gaussian elimination:" << endl;
		cout << RowReduce(t1) << endl;

		//������������ ������ 4

		cout << "Matrix from the file loading.txt" << endl;
		Matrix loading;
		file1 >> loading;
		cout << loading << endl;

		//������ ����������� ������� � ���� test.txt
		file2 << loading;

		//���������� ������� � �������� ���� bin.dat
		CreateBinary(loading, file3);

		//��������� ������� �� ��������� ����� � loadning2
		Matrix loading2;
		cout << "The same matrix written in the binary file and than read and put into console:" << endl;
		cout << ReadBinaryFile(loading2, file3) << endl;

		//������ ����������/�������� ������ � �������� ������
		cout << "Testing the methods of binary file. Doing 'save' in the new file and 'load' from this file. " << endl;

		Matrix test2;
		loading.save_file("test2.dat");
		cout << "We get the same matrix:" << endl;
		test2.load_file("test2.dat");
		cout << test2;
	}

	catch (exception& e) {
		cout << e.what() << endl;
	}
	return 0;
}