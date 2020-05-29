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


	while ((int)(func(b)/eps) > 1)
	{
		dfunc = (func(b + eps) - func(b))/eps; //вычисление производной в точке b
		b = b - (func(b))/dfunc;
//		printf ("b=%f\n", b);
	}

	return b;

}


