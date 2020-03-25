#include "task.h"
#include <math.h>

double newton(RRFUN f, double a, double b, double eps)
{
	int k;

	//Проверяем концы отрезка
	if(f(a) == 0)
		return a;
	if(f(b) == 0)
		return b;
	
	//Выбираем начальную точку
	double x;
	/*
	if(deriv(f, a, eps)*secderiv(f, a, eps) > 0)
		x = b;
	else
		x = a;
	b = x - f(x)/df(x);
	a = x;
	*/
	x = (a + b) / 2;

	//Запускаем итерационный процесс
	while(fabs(a - b) > eps)
	{
		a = b;
		b = b - f(b)/deriv(f, b, eps);
		if(k > 1000000) return a - 1;
	}
	return b;
}
double deriv(RRFUN f, double a, double h)
{
	return (f(a + h) - f(a - h)) / (2 * h);
}
double secderiv(RRFUN f, double a, double h)
{
	return (f(a + h) - 2 * f(a) + f(a - h)) / h / h;
}
