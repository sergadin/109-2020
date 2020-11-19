#include "Matrix.h"


template <class T>
Matrix<T>::Matrix(int N, int M)
{
    this->N = N;
    this->M = M;
    matrix = new T[N*M];
}

template <class T>
Matrix<T>::~Matrix()
{
    delete[] matrix;
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &arg)
{
    this->N = arg.N;
    this->M = arg.M;
    matrix = new T[N*M];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            matrix[M*i + j] = arg.matrix[M*i + j];
        }
    }
}
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& arg)
{
    N = arg.N;
    M = arg.M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            set_element(i, j, arg.get_element(i, j));
        }
    }
    return *this;
}

template <class T>
int Matrix<T>::get_row_count() const
{
    return N;
}

template <class T>
int Matrix<T>::get_col_count() const
{
    return M;
}

template <class T>
T Matrix<T>::get_element(int N, int M) const
{
    try
    {
        if (N < 0 || M < 0 || N >= this->N || M >= this->M)
        {
            throw -1;
        }
        return matrix[(this->M)*N + M];
    }
    catch (int exc)
    {
        cout << "Error - incorrect indexes." << endl;
    }
}

template <class T>
void Matrix<T>::set_element(int N, int M, T element)
{
    try
    {
        if (N < 0 || M < 0 || N >= this->N || M >= this->M)
        {
            throw -1;
        }
        matrix[(this->M)*N + M] = element;
    }
    catch (int exc)
    {
        cout << "Error - incorrect indexes." << endl;
    }
}
template <class T>
void Matrix<T>::print() const
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << " " << matrix[M*i + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &arg)
{
    try
    {
        if (N != arg.N || M != arg.M)
        {
            throw -1;
        }
        Matrix<T> result(N, M);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                result.set_element(i, j, this->get_element(i, j) + arg.get_element(i, j));
            }
        }
        return result;
    }
    catch (int exc)
    {
        cout << "Error - different matrix shapes. " << endl;
    }
}
template <class T>
SubMatrix<T> Matrix<T>::get_submatrix(int start_x, int start_y, int size_x, int size_y)
{
    try
    {
        if ((start_x + size_x > M) || (start_y + size_y > N))
        {
            throw -1;
        }
        SubMatrix<T> result(start_x, start_y, size_x, size_y, this);
        return result;
    }
    catch (int exc)
    {
        cout << "Error: incorrect submatrix parameters." << endl;
    }
}

template class Matrix<int>;
template class Matrix<double>;


