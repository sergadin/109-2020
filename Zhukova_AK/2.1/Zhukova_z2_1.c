#include <stdio.h>
#include <math.h>
#include "Zhukova_z2_1.h"
//эта фунция вычисляет интеграл на отрезке
//по составной формуле прямоугольников с s отрезками
//условия на функцию func:
//она должна быть определена на всём отрезке
double findint (double( * func) (double ), double a, double b, double eps)
{

	double x = a;
	double delta;
	double i_s = 0;
	double i_2s = 0;

	int s = (int)((b - a)/eps);
	int i;

	delta = (b - a)/s;

	for (i=0; i<s; i++)
	{
                i_s = (func(x))*delta + i_s; //вычисление площади прямоугольника
                x = x + delta;
	}

	s = s*2;
	delta = (b - a)/s;
	x = a;

	for (i=0; i<s; i++)
	{
                i_2s = (func(x))*delta + i_2s; //вычисление площади прямоугольника
                x = x + delta;
	}

//	printf ("i_s=%f i_2s=%f s=%d\n",i_s, i_2s, s);

	x = a;
//	printf ("eps=%f a=%f b=%f\n", eps, a, b);

        while (fabs(i_s-i_2s)>=eps)
        {
		i_s = i_2s;
		s = s*2;
		delta = (b - a)/s;
		x = a;
		i_2s = 0;

		for (i=0; i<s; i++)
		{
                	i_2s = (func(x))*delta + i_2s; //вычисление площади прямоугольника
               		x = x + delta;
		}


//              printf ("intf=%f  x=%f\n", intf, x);
        }

        return i_2s;

}
