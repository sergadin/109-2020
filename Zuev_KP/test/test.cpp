#include <iostream>
#include "kuslin.h"

using namespace std;

int main()
{
	Queue q(10);
	
	q.put(1234);
	std::cout << q << endl;

	try
	{
	Queue q2(0);
	Queue q3 = q2;
	q = q2;
	q = q;
	std::cout << "q: " << q << endl;
	std::cout << "q2: " << q2 << endl;
	}	
	catch(QueueError &err)
	{
		std::cout << "EXCEPTION: " << err.get_reason() << std::endl;
	}

	std::cout << q << endl;

	cout << "First item is: "<< q.get_first() << std::endl;
	std::cout << q << endl;

	return 0;
} 
