
#include "text.h"
//#include <iostream>

int main()
{
	ZZ a1(0,3), a2(0,3), a3(0,3), b1(1,3), b2(1,3), b3(1,3);
	a1.name(1);
	a2.name(2);
	a3.name(3);
	b1.name(1);
	b2.name(2);
	b3.name(3);
	a2.message(b2);
	a1.print();
	a2.print();
	a3.print();
	
	return 0;
}
