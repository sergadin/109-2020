#include "task.h"
#include <math.h>

double newton(RRFUN f, double a, double b, double eps)
{
	int k;
	double x, A, B;

	//Проверяем концы отрезка
	if(fabs(f(a)) < eps)
		return a;
	if(fabs(f(b)) < eps)
		return b;
	
	//Проверяем, разные ли знаки принимает функция на концах отрезка
	if(f(a) * f(b) > 0)
		return a - 1;

	//Проверяем, не разные ли знаки принимает производная на концах отрезка
	if(!(deriv(f, a, eps) * deriv(f, b, eps) > 0))
		return a - 1;


	//Выбираем начальную точку
	if(f(a)*secderiv(f, a, eps) > 0)
		x = b;
	else
		x = a;
	B = x - f(x)/deriv(f, x, eps);
	A = x;

	//Запускаем итерационный процесс
	while(fabs(A - B) > eps)
	{
		
		//Проверяем концы отрезка
		if(fabs(f(A)) < eps)
			return A;
		if(fabs(f(B)) < eps)
			return B;

		//Проверяем, не разные ли знаки принимает производная на концах отрезка
		if(!(deriv(f, A, eps) * deriv(f, B, eps) > 0))
			return a - 1;


		A = B;
		B = B - f(B)/deriv(f, B, eps);

		//если что-то не так и цикл идёт очень долго, прерываем
		if(k > 1000000) 
			return a - 1;
		k++;
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
