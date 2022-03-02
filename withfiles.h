//-------------------------------------------------------
//Заголовный файл с описанием функций для работы с файлами
//-------------------------------------------------------

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>


//Функция для чтения матрицы и текстового файла
Matrix& ReadTextFile(Matrix& object, string filet) {

	string s;
	ifstream file(filet);
	if (!file) {
		cerr << "Could not be opened for reading!" << endl;
		exit(1);
	}
	size_t array_size = 0;
	while (getline(file, s))
		array_size++;
	s.clear();
	file.clear();
	file.seekg(0);


	string comastr = ",";
	string dotstr = ".";
	stringstream ss;
	vector <vector<double>> rows;
	rows.resize(array_size);
	size_t i = 0;
	while (getline(file, s)) {
		while (s.find(comastr) != -1) {
			size_t pos = s.find(comastr);
			s.replace(pos, 1, dotstr);
		}

		ss.clear();
		ss.str(s);
		string data = "";
		while (getline(ss, data, '\t')) {
			stringstream element;
			element << data;
			double number = 0.0;
			element >> number;
			rows[i].push_back(number);

		}
		i++;
	}

	int M_number = 0;

	M_number = rows.size();

	for (size_t j = 1; j < M_number; j++)
		if (rows[j].size() != rows[j - 1].size())
			throw MyException1();
	int N_number = rows[0].size();
	object.M = M_number;
	object.N = N_number;

	object.matrix.resize(object.M);
	for (size_t j = 0; j < object.M; j++) {
		object.matrix[j].resize(object.N);

		for (size_t l = 0; l < object.N; l++)
			object.matrix[j][l] = rows[j][l];
	}
	file.close();

	return object;
}

//Перегрузка оператора для чтения матрицы из текстового файла
Matrix& operator>>(string filet, Matrix& object)
{
	ReadTextFile(object, filet);

	return object;
}

//Перегрузка оператора вывода/записи в текстовый файл
ofstream& operator<<(string filet, Matrix& object)
{
	ofstream out;
	out.open(filet, ios_base::out);

	for (int i = 0; i < object.M; i++)
	{
		for (int j = 0; j < object.N; j++) {
			if (abs(object.matrix[i][j]) < pow(10, -5))
				out << "0.000" << '\t';
			else
			{

				out << setw(5) << object.matrix[i][j] << '\t';
			}
		}
		out << endl;
	}
	return out;
}

//Функция для ввода матрицы в бинарный файл
void CreateBinary(Matrix& object, string bins)
{
	ofstream binary_file(bins, ios::out | ios::binary);
	if (!binary_file)
		throw MyException8();
	binary_file.seekp(0);
	for (size_t i = 0; i < object.M; i++)
		for (size_t j = 0; j < object.N; j++)
			binary_file.write((char*)&object.matrix[i][j], sizeof(double));
	binary_file.write((char*)&object.M, sizeof(object.M));
	binary_file.write((char*)&object.N, sizeof(object.N));
	binary_file.close();

}

//Функция для чтения матрицы из бинарного файла
Matrix& ReadBinaryFile(Matrix& object, string bins)
{
	int size_bin, size_temp = 0;
	vector<vector<double>> vec = {};
	ifstream binary_file(bins, ios::binary | ios::in);
	if (!binary_file)
		throw MyException8();

	binary_file.seekg(0, ios::end);
	size_temp = binary_file.tellg();

	size_bin = size_temp - 2 * sizeof(int);
	binary_file.seekg(size_bin, ios::beg);
	binary_file.read((char*)&object.M, sizeof(object.M));
	binary_file.read((char*)&object.N, sizeof(object.N));

	binary_file.seekg(0, ios::beg);

	object.matrix.resize(object.M);
	for (size_t i = 0; i < object.M; i++) {
		object.matrix[i].resize(object.N);
		for (size_t j = 0; j < object.N; j++)
			binary_file.read((char*)&object.matrix[i][j], sizeof(double));
	}

	binary_file.close();

	return object;
}