#include <iostream>
#include "vector.h"

using namespace std;

int main() 
{
	try
	{
	Vector q();
	std::cout << q << endl;
	}
	catch(VectorError &err)
	{
		std::cout << err.get_reason() << std::endl;
	}
	return 0;
}
