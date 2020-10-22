#include "matr.h"
#include <iostream>

using namespace std;
int main()
{
	matr A(2, 3);
	matr B(2, 3);
	matr C(2, 3);
	for(int i = 1; i<3; ++i)
	{
		A.set_element(i, i, 1);
		A.set_element(i+2, i, 2);
		A.set_element(i+4, i, 3);
		
	}
	cout << A;
	cout << B;
	C = B+A;
	cout << C;
	cout << A+B+C;
	podmatr D(&A, 1,1,2,2);
	cout << D.get_element(1,1) << " "<< D.get_element(1,2) << endl;
	cout << D.get_element(2,1) << " "<< D.get_element(2,2) << endl;
	return 0;
}
