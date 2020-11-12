#pragma once
#include "Matrix.h"

template <class T>
class Matrix;

template <class T>
class SubMatrix
{
private:
    Matrix<T>* parent_matrix;
    int start_x, start_y, size_x, size_y;
public:
    SubMatrix();
    SubMatrix(int start_x, int start_y, int size_x, int size_y, Matrix<T>* parent_matrix);
    T get_element(int N, int M);
};
