#include<math.h>
#include<stdio.h>
#include"mini.h"

double mod(double x);
double sign(double x);
double vparab(double a, double x, double b, RRF func);


double mini(double a1, double b1, double eps, RRF func)
{
	double minn, x,  k = (sqrt(5) + 1)/2;
	double a = a1;
        double b = b1;
	double f1, f2;
	double x1, x2;
	while(mod(b - a) >= eps)
	{
		x1 = b - (b - a)/k;
		x2 = a + (b - a)/k;
		f1 = (*func)(x1);
		f2 = (*func)(x2);
		if(f1 >= f2)
		{
			a = x1;
			x = x2;
		}
		else
		{
			b = x2;
			x = x1;
		}
		if(mod(b - a) < eps)
		{
			x = (a + b)/2;
		}
	}
	if(((*func)(x) != (*func)(a)) && ((*func)(x) != (*func)(b)))
		minn = (*func)(x - ((x-a)*(x-a)*((*func)(x)-(*func)(b))-(x-b)*(x-b)*((*func)(x)-(*func)(a)))/(2*((x-a)*((*func)(x)-(*func)(b))-(x-b)*((*func)(x)-(*func)(a)))));
	else
		minn = (*func)(x);
	return minn;



}

double mod(double x)
{
	if(x < 0)
		return -x;
	else
		return x;

}

double vparab(double a, double x, double b, RRF func)
{
	double v;
	double ya = (*func)(a);
	double yx = (*func)(x);
	double yb = (*func)(b);
	v = x - ((x - a)*(x - a)*(yx - yb) - (x - b)*(x - b)*(yx - ya))/(2*((x - a)*(yx - yb) - (x - b)*(yx - ya)));
	return v;


}


double sign(double x)
{
	if(x < 0)
		return -1;
	else
		return 1;
}
