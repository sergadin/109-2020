#include <stdio.h>
#include "Zhukova_z2_1.h"
//эта фунция вычисляет интеграл на отрезке
//по составной формуле прямоугольников с s отрезками
//условия на функцию func:
//она должна быть определена на всём отрезке
double findint (double( * func) (double ), double a, double b, int s)
{

	double eps;
        double intf = 0; //интеграл функции func
	double x;

	x = a;
	eps = (b - a)/s; //шаг

//	printf ("eps=%f a=%f b=%f\n", eps, a, b);

        while ((int)((b - x)/eps) > 0)
        {

                intf = (func(x))*eps + intf; //вычисление площади прямоугольника
                x = x + eps;

//              printf ("intf=%f  x=%f\n", intf, x);
        }

        return intf;

}
