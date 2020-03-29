#include<math.h>
#include<stdio.h>
#include"mini.h"

double mod(double x);
double sign(double x);
double vparab(double a, double b, double c, RRF func);


double mini(double a1, double c1, double eps, RRF func)
{
	double k = (sqrt(5) - 1)/2;
	double a = a1;
        double c = c1;
	double x = (a + c)/2, w = x, v = x;
	double fx = (*func)(x), fw = fx, fv= fx;
	double d = c - a, e = d;
	double g, u, fu;
	while(e > eps)
	{
		g = e;
		e = d;
		if((x != w) && (w != u) && (u != x) && (fx != fw) && (fv != fw) && (fv != fx))
			u = vparab(x, w, u, func);
		if((u <= c - eps) && (u >= a + eps) && (mod(u - x) < g/2))
		{
			d = mod(u - x);
		}	
		else 
		{
			if(x < (c - a)/2)
			{
				u = x + k*(c - x);
				d = c - x;
			}
			else
			{
				u = x - k*(x - a);
				d = x - a;
			}
		}
		if(mod(u - x) < eps)
			u = x + sign(u - x)*eps;
		fu = (*func)(u);
		if(fu <= fx)
		{
			if(u >= x)
				a = x;
			else
				c = x;
			v = u;
			w = x;
			x = u;
			fv = fw;
			fw = fx;
			fx = fu;
		}
		else
		{
			if(u >= x)
				c = u;
			else
				a = u;
			if((fu <= fw) || (w = x))
			{
				v = w;
				w = u;
				fv = fw;
				fw = fu;
			}
			else
			{
				if((fu <= fv) || (v == x) || (v == w))
				{
					v = u;
					fv = fu;
				}
			}

		}

	}
	return fu;

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
	v = b - ((b - a)*(b - a)*(yb - yc) - (b - c)*(b - c)*(yb - ya))*0.5/((b - a)*(yb - yc) - (b - c)*(yb - ya));
	return v;


}


double sign(double x)
{
	if(x < 0)
		return -1;
	else
		return 1;
}
