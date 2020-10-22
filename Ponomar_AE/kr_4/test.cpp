#include "class.h"
#include <iostream>

using namespace std;

int main()
{
	matrix matr1(2, 4);
	matrix matr2(2, 4);
	matrix matr3(2, 4);

	for(int i = 1; i < 3; ++i)
	{
		matr1.change(i, i, 2);
		matr1.change(i+2, i, 3);
		matr1.change(i+4, i, 1);
		matr1.change(i+6, i, 7);
		matr2.change(1, i, 1);
		matr2.change(1, i, 3);
		matr2.change(1, i, 5);
		matr2.change(1, i, 7);

	}

	cout<<matr1.str()<<endl;
	cout<<matr1.stolb()<<endl;
	cout<<matr1;
	cout<<matr2;

	matr3 = matr2+matr1;
	cout<<matr3;

	podmatrix matr4(&matr1,1,1,1,2);
	cout << matr4.element(1,1)<<" "<< matr4.element(1,2) << endl;
	return 0;
}
