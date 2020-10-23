#include <iostream>
#include "matrix.h"

int main()
{
    matrix_t<double>* matrix = new matrix_t<double>(7, 7);
    std::cout << "rows: " << matrix->getRows() << std::endl;
    std::cout << "columns: " << matrix->getCols() << std::endl;

    for (int index = 0; index < matrix->getRows() * matrix->getCols(); ++index)
    {
        matrix->setElement(index / matrix->getCols(), index % matrix->getCols(), index);
    }
    std::cout << (*matrix) << std::endl;

    matrix_t<double>& result = *matrix + *matrix;

    std::cout << result << std::endl;;

    std::cout << result.get(1, 5, 2, 2) << std::endl;
    std::cout << result.get(1, 1, 2, 2) << std::endl;

    std::cout << result.get(1, 5, 2, 2) + result.get(1, 1, 2, 2) << std::endl;

    delete matrix;
    std::cout << "Press Enter to Continue";
    std::cin.ignore();
    return 0;
}