#include "matrix.h"
#include <iostream>

using namespace std;
int main()
{
	try{
	matrix A(3, 4);
	matrix B(3, 4);
	matrix C(3, 4);
	for(int i = 1; i<4; ++i)
	{
		A.set_elem(i, i, 1);
		A.set_elem(i+3, i, 2);
		A.set_elem(i+6, i, 3);
		A.set_elem(i+9, i, 4);
		B.set_elem(1, i, 1);
		B.set_elem(1, i, 2);
		B.set_elem(1, i, 3);
		B.set_elem(1, i, 4);
	}
	cout << A.get_rows() << endl;
	cout << A.get_cols() << endl;
	cout << A;
	cout << B;
	C = B+A;
	cout << C;
	cout << A+B+C;
	submatrix D(&A, 1,2,2,2);
	cout << D.get_elem(1,1) << " "<< D.get_elem(1,2) << endl;
	cout << D.get_elem(2,1) << " "<< D.get_elem(2,2) << endl;
	}
	catch(Exception &exc)
	{
		std::cout << "EXCEPTION " << exc.message() << std::endl;
	}
	return 0;
}
