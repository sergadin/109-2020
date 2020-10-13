#include <iostream>
#include "stack.h"

using namespace std;

int main() 
{
	try
	{
		Stack q0(5, 0);
		Stack q1(5, 1);
		Stack q2(5, 2);
		Stack q3(5, 3);
		Stack q4(5, 4);
		std::cout << q4 << endl;
	}
	catch(StackError &err)
	{
		std::cout << err.get_reason() << std::endl;
	}
	return 0;
}
