#include <iostream>
#include "vector.h"

using namespace std;

int main() 
{
	try
	{
	Vector q0(5, 0);
	Vector q1(5, 1);
	Vector q2(5, 2);
	Vector q3(5, 3);
	Vector q4(5, 4);
	q0.loc();
	q0.loc();
	q0.loc();
	q0.loc();
	q4.loc();
	q4.rec(q4, q0);
	std::cout << q0 << endl;
	std::cout << q4 << endl;
	for(int i = 0; i < 10; i++)
	{
	Vector temp = q0;
	temp = temp;
	}
	if (q0 <= q4)
	{
		cout << "true " << std::endl;
	}
	}
	catch(VectorError &err)
	{
		std::cout << err.get_reason() << std::endl;
	}
	return 0;
}
