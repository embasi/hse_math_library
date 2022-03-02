//-------------------------------------------------------
//Заголовочный файл с описанием исключений
//-------------------------------------------------------

#pragma once

#include <exception>

using namespace std;

//исключение несоответствия размерности
class MyException1 : public exception {
	const char* what() const noexcept {
		return "Dimensional matrix Exception.";
	}
};

//исключение невозможности заполнить верхнетреугольную матрицу
class MyException2 : public exception {
	const char* what() const noexcept {
		return "UpTriangular Exception.";
	}
};

//исключение для невозможности посчитать произведение матриц
class MyException3 : public exception {
	const char* what() const noexcept {
		return "Multiplication Exception.";
	}
};

//исключение невозможности заполнить нижнетреугольную матрицу
class MyException4 : public exception {
	const char* what() const noexcept {
		return "LowTriangular Exception.";
	}
};

//исключение при попытке создать матрицу размера 0 или меньше
class MyException5 : public exception {
	const char* what() const noexcept {
		return "Dimensions are not more than zero.";
	}
};

class MyException6 : public exception {
	const char* what() const noexcept {
		return "Operands must be vectors.";
	}
};

//исключение для случая, когда определитель матрицы не должен быть равен нулю
class MyException7 : public exception {
	const char* what() const noexcept {
		return "Determinant is equal to zero.";
	}
};

//исключение невозможности прочитать файл
class MyException8 : public exception {
	const char* what() const noexcept {
		return "The file cannot be opened";
	}
};

//исключение для бинарного режима (передали текстовый файл)
class MyException9 : public exception {
	const char* what() const noexcept {
		return "Binary file required.";
	}
};