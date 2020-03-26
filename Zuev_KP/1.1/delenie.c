#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"delenie.h"

double delenie(double a, double b, double ep, RRFUN func)
{
	double k1 = a, ser = 0, k2 = b, res1 = 0, ser1 = 0, res2 = 0;
	double n = b - a;
	ser = (a + b)/2;
	res1 = (*func)(k1);
	res2 = (*func)(k2);
	if(res1*res2 >= 0)
		{
			printf("нет корня\n");
			return 0;
		}
	while(n > ep)
	{
		ser = (k1 + k2)/2;
		res1 = (*func)(k1);
		res2 = (*func)(k2);
		ser1 = (*func)(ser);
		if(ser1*res1 <= 0)
		{
			k2 = ser;
		}
		if (ser1*res1 > 0)
		{
			k1 = ser;
		}
		n = k2 - k1;
	}
	return (k1 + k2)/2;
}


