#include "class.h"
#include <iostream>

using namespace std;

int main()
{
	matrix matr1(2, 4);
	matrix matr2(2, 4);
	matrix matr3(2, 4);

	for(int i = 1; i < 4; ++i)
	{
		matr1.change(i, i, 1);
		matr2.change(i+1, i, 2);
		matr3.change(i+2, i, 3);
		
	}
	cout<<matr1;
	cout<<matr2;
	
	matr3 = matr1+matr2;
	cout<<matr3;
	
	podmatrix matr4(&matr1, 1,1,2,2);
	cout << matr4.element(1,1)<<" "<< matr4.element(1,2) << endl;
	cout << matr4.element(2,1)<<" "<< matr4.element(2,2) << endl;
	
	return 0;
};
