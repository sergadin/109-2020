#include <iostream>
#include "matr.h"

const int min_value = -3;

using namespace std;
int main()
{
	Matr q(min_value, min_value + 5);

	std::cout<< q<< endl;

	try
	{
		Matr q2(-1, 5);
		q2.put(-1);
		q2.put(2);
		q2.put(0);
		q2.put(700);
		Matr q4(-500, 2);
                q4.put(-1);
                q4.put(2);
                q4.put(0);
		if(q2 == q4)
		{
			cout<< "1" << endl;
		}
  		std::cout<< q<< endl;
  		q.put(-1);
  		std::cout<< q<< endl;
  		q.put(0);
  		std::cout<< q<< endl;
  		q.put(-2);
  		std::cout<< q<< endl;
		Matr q3(-1, 5);
		q2 *= q;
		std::cout<< q2<< endl;
  		return 0;
	}
	catch(MatrError &err)
	{
		std::cout << "EXC"<< err.get_reason() << std::endl;
	}
	std::cout << q << endl;

	return 0;


}
