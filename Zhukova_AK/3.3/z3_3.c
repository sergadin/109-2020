#include <stdio.h>
#include "z3_3.h"
//эта фунция ищет минимум с точностью до некоторого eps

double findmin (double( * func) (double ), double a, double b, double eps, int n)
{
	int j;
	int minj = 0;

	double a1, a2;//парабола
	double v;//вершина параболы
	double minf, h;//minf - минимум функции на отрезке
	minf = func(a);

        while ((int)((b-a)/eps) > 1)
        {

		for (j=0; j<n;j++)
		{
			if ( (int)((minf - (func (a+(b-a)*j/n)))/eps) > 0)
			{
				minf = func (a + (b - a)*j/n);
				minj = j;
			}
		}
		h = (b - a)/n;
		a = a + h*minj;
		b = a + h;
//              printf ("a=%f b=%f h=%f minf=%f\n",a ,b, h, minf);
        }

	h = (a + b)/2;

	a1 = 2*(-2*func(h) + func(a) + func(b))/((a-b)*(a-b));
	a2 = (func(b) - func(a))/(b - a) - a1*(a+b);

	v = -a2/(2*a1);
	minf = func(v);
//	printf ("v=%f minf=%f\n", v, minf);

	if ((int)((func(v) - func(a))/eps) > 0)
	{
		minf = func(a);
	}
	else
	{
		if ((int)((func(v) - func(b))/eps) > 0)
		{
			minf = func(b);
		}
		else
		{
			minf = func(v);
		}
	}

        return minf;

}



