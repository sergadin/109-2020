#include <iostream>
#include "matr.h"

const int min_value = 1000000;

using namespace std;
int main()
{
	Matr q(min_value, min_value + 5);

	std::cout<< q<< endl;

	try
	{
		Matr q2(1, 7);
		q = q2;
        q = q;
        q.add(min_value + 2);
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
