#include "Matrix.h"

int main(void)
{
    Matrix<int> A(3,3);
    Matrix<int> B(3,3);

    cout << "Size of A is " << A.get_row_count() << ", " << A.get_col_count() << endl;
    cout << "Size of B is " << B.get_row_count() << ", " << B.get_col_count() << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            A.set_element(i,j, i + j);
            B.set_element(i,j, (i + j)*5);
        }
    }

    cout << "----------------" << endl;
    A.print();
    B.print();
    cout << "----------------" << endl;
    Matrix<int> C(3,3);
    C = A + B + A;
    C.print();
    cout << "----------------" << endl;
    SubMatrix<int> submatrix;
    submatrix = C.get_submatrix(1,1,2,2);
    cout << submatrix.get_element(1,1) << endl;

    return 0;
}
