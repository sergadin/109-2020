#include <iostream>
#include <string>

#include"matrix.h"




std::ostream& operator<<(std::ostream &os, const Matrix& m)
{
	os << "размеры матрицы" << m.n_ << m.m_ << std::endl;
//	os << "введите элементы матрицы" << std::endl;
	for(int i = 0; i < m.n_ * m.m_; i++)
	{
		os << m.matr_[i] << " ";
		if (i % m.m_ == m.m_ - 1)
		{
			os << std::endl;
		}
	}
	return os;
}


//объект матрица
Matrix::Matrix(int n, int m) {
	if((n < 0) || (n == 0) || (m < 0) || (m == 0) ) {
		throw matrixError(-1, std::string("Нельзя такие размеры делать"));
	}
	n_ = n;
	m_ = m;
	matr_ = new int[m_ * n_];
	if (!matr_) {
		throw matrixError(-2, std::string("память не выделилась"));
	}
	for (int i  = 0; i < n_ ; i++) {
		for (int j = 0; j < m_; j++) {
			matr_[i * m_ + j] = 0;
		}
	}
}

//копирование
Matrix::Matrix(const Matrix & obj) {
	int msize = m_*n_;
	matr_ = new int[msize = obj.n_ * obj.m_];
	for (int k = 0; k < msize; k++) {
		matr_[k] = obj.matr_[k];
	}
	n_ = obj.n_;
	m_ = obj.m_;
}

//уничтожение
Matrix::~Matrix() {
	delete[] matr_;
}

//отчищение
//void Matrix :: clear() {
//	n_ = 0;
//	m_ = 0;
//}

//оператор равно
Matrix & Matrix::operator=(const Matrix & right) {
//        return *this;
  	this -> n_ = right.n_;
	this -> m_ = right.m_;
    delete[] matr_;

  	if(!(this -> matr_ == new int[n_ * m_])) {
		throw matrixError(-2, std::string("память не выделилась"));
    }
	int msize = n_ * m_;
    for(int k = 0; k < msize; k++)
        this -> matr_[k] = right.matr_[k];
    return *this;
}

// создание = заполнение
//void Matrix::create(const Matrix& m) {
//	Matrix matrix = Matrix(n, m);
//	std :: cout << "введите размеры матрицы" << endl;
//	std :: cin >> m.n_;
//	std :: cin >> m.m_;
//	for (int i = 0; i < n_*m_ ; i++) {
//			std :: cin >> m.matr_[i];
//	}
//}

void Matrix::get_value(const Matrix &matr) {//печать размеров матрицы
	std::cout << matr.n_ << std::endl << matr.n_;
}

int Matrix::getval_n() {
	//количество строк
	return n_;
}
int Matrix::getval_m() {
	//количнсво столбцов
	return m_;
}
int Matrix::get_element(int i, int j) { // получение элемента с заданными индексами
	if ((i >= m_) || (j >= m_) || (i < 0) || (j < 0))	{
		throw matrixError(3, "нет такого элемента");
	}
	return matr_[i * m_ + j]; 
}


void Matrix ::change_element(int i, int j, int new_el) {// изменение элемента с заданными индексами
	if ((i >= n_) || (j >= m_) || (i < 0) || (j < 0))	{
		throw matrixError(3, "нет такого элемента");
	}
	matr_[i * m_ + j] = new_el;
}
	
void Matrix ::get_submatrix(int i0, int j0, int ns, int ms){ // взятие подматрицы
		Matrix temp = *this;
		SubM SM(&temp, i0, j0, ns, ms);
		for (int i = i0 ; i <= ns; i++) {
			for (int j = j0 ; j <= ms; j++) {
				std::cout << SM.GetElem(i, j) << " ";
			}
			std::cout << std::endl;
		}


}

Matrix Matrix:: operator+ (const Matrix &right) {// сложение матриц

if ((this -> n_ != right.n_) || (this -> m_ != right.m_))	{
		throw matrixError(4, "размеры матриц не совпадают");
	}
	Matrix res(1,1);
	res = *this;
	for (int i = 0; i < n_ * m_; i++)	{
		std:: cout << res.matr_[i]<< std::endl;
		res.matr_[i] =  res.matr_[i] + right.matr_[i];
		std::cout << res.matr_[i] << " " << right.matr_[i] << std::endl;
	}
	return res;
}

/*
void Matrix ::print(const Matrix &m) { // печать матрицы
	for (int i = 0; i < n_ * m_; i++) {
//		for (int j = 0; j < matr.m_; j++) {
			std:: cout << matr_[i] << " ";
//		}
		std:: cout << std::endl;
	}
}
*/

SubM::SubM(Matrix *matr, int i, int j, int n, int m)	{
	// учитывая, что в реальности говорят не элемент 0,0 , ф элемент 1, 1
	if ((i < 1) || (j < 1) || (n <= 0) || (m <= 0))	{
		throw matrixError(-4, std::string("Нет таких подматриц"));
	}

	if ((i - 1 + n > matr -> getval_n()) || (j - 1 + m > matr -> getval_m()))	{
		throw matrixError(-4, std::string("Нет таких подматриц, ошибка с размерами"));
	}

	i_corner_ = i - 1;
	j_corner_ = j - 1;
	n_sub_ = n;
	m_sub_ = m;
//	i_ = i;
//	j_ = j;
//	n_ = n;
//	m_ = m;
	matrix_ = matr;
}
 /*
std::ostream& operator<<(std::ostream &os, const SubM &m)
{
	os << "размеры подматрицы" << m.n_sub_ << m.m_sub_ << std::endl;
	for(int i = m.i_corner_; i < m.n_sub_; i++) {
		for(int j = m.j_corner_; j < m.n_sub_; j++)	{
			os << m.matr_[i * m.m_sub_ + j] << " ";
			if (i % m.m_ == m.m_ - 1)	{
				os << std::endl;
			}
		}
	return os;
	}
}
*/

int SubM::GetElem(int i, int j)	{
	// учитывая, что в реальности говорят не элемент 0,0 , ф элемент 1, 1
	if ((i < 1) || (j < 1)){
		throw matrixError(-1, std::string("Нельзя такие размеры делать"));
	}
	if ((i - 1 >= n_sub_) || (j - 1 >= m_sub_)){
		throw matrixError(-1, std::string("Нельзя такие размеры делать. Выйдем за границы"));
	}
	return matrix_-> get_element(i - 1 +i_corner_, j - 1 + j_corner_) ;

}

