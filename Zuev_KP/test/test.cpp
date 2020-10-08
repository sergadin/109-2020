#include <iostream>
#include "intset.h"

using namespace std;

int main() 
{
	try
	{
	IntSet q(5, 11);
	if (q.is_empty())
	{
		cout << "pusto " << std::endl;
	}
	q.put(5);
	q.put(9);
	q.put(10);
	q.put(10);
	q.put(10);
	q.put(10);
	q.put(10);
	q.put(10);
	q.put(11);
	q = q*q;
	q *= q;
	std::cout << q << endl;
	cout << "left: "<< q.lima() << std::endl;
	cout << "right: "<< q.limb() << std::endl;
	cout << "max: "<< q.max() << std::endl;
	cout << "min: "<< q.min() << std::endl;
	q.exc(5);
	std::cout << q << endl;
	}
	catch(IntSetError &err)
	{
		std::cout << err.get_reason() << std::endl;
	}
	return 0;
}
