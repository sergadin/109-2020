#pragma once
#include <iostream>
#include "Sub_Matrix.h"
using namespace std;

template <class T>
class SubMatrix;

template <class T>
class Matrix
{
private:
    int N, M;
    T* matrix;
public:
    //Matrix() = delete;
    Matrix(int N, int M);
    ~Matrix();
    Matrix(const Matrix<T> &arg);
    int get_row_count() const;
    int get_col_count() const;
    T get_element(int N, int M) const;
    void set_element(int N, int M, T element);
    void print() const;
    Matrix<T> operator+(const Matrix<T> &arg);
    Matrix<T>& operator=(const Matrix<T> &arg);
    SubMatrix<T> get_submatrix(int start_x, int start_y, int size_x, int size_y);

    friend class SubMatrix<T>;
};
