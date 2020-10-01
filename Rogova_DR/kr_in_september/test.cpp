#include <iostream>
#include "dasha.h"

using namespace std;
int main()
{
	Queue q(100);
	q.put(1234);

	std::cout<< q<< endl;

	try
	{
		Queue q2(1);
		q = q2;
		std::cout << "q: " << q << endl;
		std::cout << "q2: " << q2 << endl;
	}
	catch(QueueError &err)
	{
		std::cout << "EXC"<< err.get_reason() << std::endl;
	}

	std::cout << q << endl;

	return 0;


} 
