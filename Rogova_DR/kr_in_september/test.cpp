#include <iostream>
#include "matr.h"

using namespace std;
int main()
{
	Matr q(1, 5);

	std::cout<< q<< endl;

	try
	{
		Matr q2(1, 7);
		q = q2;
		std::cout << "q: " << q << endl;
		std::cout << "q2: " << q2 << endl;
	}
	catch(MatrError &err)
	{
		std::cout << "EXC"<< err.get_reason() << std::endl;
	}

	std::cout << q << endl;

	return 0;


} 
