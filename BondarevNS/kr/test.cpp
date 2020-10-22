#include "matr.h"
#include <iostream>

using namespace std;
int main()
{
	matr A(2, 3);
	matr B(2, 3);
	matr C(2, 3);
	for(int i = 1; i<; ++i)
	{
		A.set_elem(i, i, 1);
		A.set_elem(i+2, i, 2);
		A.set_elem(i+4, i, 3);
		
	}
	cout << A;
	cout << B;
	C = B+A;
	cout << C;
	cout << A+B+C;
	submatrix D(&A, 1,1,2,2);
	cout << D.get_elem(1,1) << " "<< D.get_elem(1,2) << endl;
	cout << D.get_elem(2,1) << " "<< D.get_elem(2,2) << endl;
	return 0;
}
