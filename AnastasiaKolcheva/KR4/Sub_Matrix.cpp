#include "Sub_Matrix.h"
#include "Matrix.h"
template <class T>
SubMatrix<T>::SubMatrix()
{
    start_x = 0;
    start_y = 0;
    size_x = 0;
    size_y = 0;
    parent_matrix = nullptr;
}
template <class T>
SubMatrix<T>::SubMatrix(int start_x, int start_y, int size_x, int size_y, Matrix<T>* parent_matrix)
{
    this->start_x = start_x;
    this->start_y = start_y;
    this->size_x = size_x;
    this->size_y = size_y;
    this->parent_matrix = parent_matrix;
}

template <class T>
T SubMatrix<T>::get_element(int N, int M)
{
    try
    {
        if (M >= size_x || N >= size_y)
        {
            throw -1;
        }
        return parent_matrix->get_element(start_x + M, start_y + N);
    }
    catch (int exc)
    {
        cout << "Error: incorrect indexes." << endl;
    }
}
template class SubMatrix<int>;
template class SubMatrix<double>;
