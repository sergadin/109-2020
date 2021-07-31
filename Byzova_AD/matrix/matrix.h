#pragma once
#include <iostream>
#include <cstring>
#include<cstdio>
#include <math.h>

class matrixError {
private:
	int code_;
	std::string reason_;
public: 
	matrixError(int code, const std::string& reason) {
		code_ = code;
		reason_ = reason;
	}

	const std::string& get_reason() const { 
		return reason_; 
	}
};
class Matrix;

class SubM {
private:
	Matrix *matrix_;
	int i_corner_;
	int j_corner_;
	int n_sub_;
	int m_sub_;
public:
	SubM(Matrix *m, int i_corner, int j_corner, int n_sub, int m_sub);
	int GetElem(int row, int coloumn);
//	~SubM();
	//void get_submatrix(Matrix *matrix, int i0, int j0, int ns, int ms); // взятие подматрицы
};	


//class Matrix;
class Matrix {
private:
	int n_;// количество строк
	int m_;// количество столбцов
	int *matr_;// матрица
public:
	Matrix(int n,int m);
	Matrix(const Matrix& obj);// создать копию обьекта obj
	~Matrix();
	
	int getval_n();
	int getval_m(); 
	friend std::ostream& operator <<(std::ostream &os, const Matrix& m);
	void clear();
	Matrix & operator=(const Matrix & right);
	// создаем матрицу
	void create(const Matrix &m); 
	//получение размеров матрицы
	void get_value(const Matrix &m); 
	// получение элемента с заданными индексами
	int get_element(int i, int j); 
	// изменение элемента с заданными индексами
	void change_element(int i, int j, int new_el);
	// сложение матриц
	Matrix operator+ (const Matrix &right); 
	void print(const Matrix &m); 
	// печать матрицы

	SubM get_submatrix(int i0, int j0, int ns, int ms); // взятие подматрицы
};

/*
class SubM {
private:
	Matrix *matrix_;
	int i_corner_;
	int j_corner_;
	int n_sub_;
	int m_sub_;
public:
	SubM(Matrix *m, int i_corner, int j_corner, int n_sub, int m_sub);
	int GetElem(int row, int coloumn);
//	~SubM();
	//void get_submatrix(Matrix *matrix, int i0, int j0, int ns, int ms); // взятие подматрицы
};*/	
