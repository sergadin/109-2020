#include <stdio.h>
#include "Zhukova_z1_2.h"
//эта фунция ищет корень с точностью до некоторого eps
//условия на функцию func:
//она должна принимать на концах отрезка разные знаки,
//быть непрерывной,
//быть строго монотонной и строго выпуклой на заданном отрезке [a,b]
//(следовательно, в точке а фунция строго меньше 0
//а в точке b строго больше 0)
double findroot (double( * func) (double ), double a, double b, double eps)
{

	double dfunc; //производная функции func
	double ddfunc;//вторая производная

	if ((func(a) > 0) || (func(b) < 0))
	{
		return a - 5;
	}


	while ((int)(func(b)/eps) > 1)
	{
		dfunc = (func(b + eps) - func(b - eps))/(2*eps); //вычисление 1 и 2 производной в точке b
		ddfunc = (func(b + eps) - 2*func(b) + func(b + eps))/(eps*eps);

		if ((dfunc <= 0) || (ddfunc <= 0))
		{
			return a - 4;
		}

		b = b - (func(b))/dfunc;
//		printf ("b=%f\n", b);
	}

	return b;

}


