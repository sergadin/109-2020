#include "class.h"
#include <iostream>

using namespace std;

int main()
{
	try{
		matrix matr1(2, 4);
		matrix matr2(2, 4);
		matrix matr3(2, 4);

		for(int i = 1; i < 3; i++)
		{
			matr1.change(i, i, 1);
			matr1.change(i+2, i, 2);
			matr1.change(i+4, i, 3);
			matr1.change(i+6, i, 4);										
		}

		cout<<matr1;
		cout<<matr2;

		matr3 = matr2+matr1;
		cout<<matr3;

		podmatrix matr4(&matr1,1,1,1,2);
		cout << matr4.element(1,1)<<" "<< matr4.element(1,2) << endl;

	}
	catch(iskl &exc)
	{
		std::cout << "ERROR : " << exc.message() << std::endl;
	}
	return 0;
}
