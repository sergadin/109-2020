#include "matr.h"
#include <iostream>

using namespace std;
int main()
{
	try{
	matr A(3, 4);
	matr B(3, 4);
	matr C(3, 4);
	for(int i = 1; i<4; ++i)
	{
		A.set_element(i, i, 1);
		A.set_element(i+3, i, 2);
		A.set_element(i+6, i, 3);
		A.set_element(i+9, i, 4);
		B.set_element(1, i, 1);
		B.set_element(1, i, 2);
		B.set_element(1, i, 3);
		B.set_element(1, i, 4);
	}
	cout << A.get_length() << endl;
	cout << A.get_height() << endl;
	cout << A;
	cout << B;
	C = B+A;
	cout << C;
	cout << A+B+C;
	podmatr D(&A, 1,2,2,2);
	cout << D.get_element(1,1) << " "<< D.get_element(1,2) << endl;
	cout << D.get_element(2,1) << " "<< D.get_element(2,2) << endl;
	}
	catch(Exception &exc)
	{
		std::cout << "EXCEPTION " << exc.message() << std::endl;
	}
	return 0;
}
