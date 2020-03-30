#include<math.h>
#include<stdio.h>
#include"mini.h"

double mod(double x);
double sign(double x);
double vparab(double a, double b, double c, RRF func);


double mini(double a1, double c1, double eps, RRF func)
{
	double minn, t, k = (sqrt(5) + 1)/2, resk = 2 - k;
	double a = a1;
        double b = c1;
	double f1, f2;
	double x1 = a + resk*(b - a) , x2 = b - resk*(b - a);
	f1 = (*func)(x1);
	f2 = (*func)(x2);
	do
	{
		if(f1 < f2)
		{
			b = x2;
			x2 = x1;
			f2 = f1;
			x1 = a + resk*(b - a);
			f1 = (*func)(x1);
			minn = x1;
		}
		else
		{
			a = x1;
			x1 = x2;
			f1 = f2;
			x2 = b - resk*(b - a);
			f2 = (*func)(x2);
			minn = x2;
		}
		
	}while (mod(b - a) > 2*eps);
	minn = vparab(a, minn, b, func);
	return (*func)(minn);



}

double mod(double x)
{
	if(x < 0)
		return -x;
	else
		return x;

}

double vparab(double a, double b, double c, RRF func)
{
	double v;
	double ya = (*func)(a);
	double yb = (*func)(b);
	double yc = (*func)(c);
	if((yc > yb) && (yb < ya))
		v = b - ((b - a)*(b - a)*(yb - yc) - (b - c)*(b - c)*(yb - ya))*0.5/((b - a)*(yb - yc) - (b - c)*(yb - ya));
	else 
		v = (a + b)/2;
	return v;


}


double sign(double x)
{
	if(x < 0)
		return -1;
	else
		return 1;
}
