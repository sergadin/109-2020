
#include "text.h"
//#include <iostream>

int main()
{
	ZZ *a1, *a2, *a3, b(4,4);
	a1 = new ZZ[3];
	a2 = new ZZ[3];
	a3 = new ZZ[3];
	for(int i = 0; i < 3;i++)
	{
		a1[i](0,3);
		a2[i](1,3);
		a3[i](2,3);
	}
	for(int i = 0; i < 3;i++)
	{
		a1[i].name[i];
		a2[i].name[i%2];
		a3[i].name[i%2];
		if(i == 2) //2 = message
		{
			a1[i].message(a2[i - 1]);
		}
	}
	for(int i = 0; i < 3; i++)
	{
		a1[i].print();
		a2[i].print();
		a3[i].print();
	}
	return 0;
}
