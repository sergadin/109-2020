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
  		std::cout<< q<< endl;
  		q.put(-1);
  		std::cout<< q<< endl;
  		q.put(0);
  		std::cout<< q<< endl;
  		q.del_elem(-2);
  		q.put(-2);
  		std::cout<< q<< endl;
  		return 0;
	}
	catch(MatrError &err)
	{
		std::cout << "EXC"<< err.get_reason() << std::endl;
	}
	std::cout << q << endl;

	return 0;


}
