#include<math.h>
#include<stdio.h>
#include"mini.h"

double gold(double a, double b);
double vparab(double a, double b, double c, RRF func);


double mini(double a, double b, double eps, RRF func)
{
	double end1 = a, end2 = b;
	double minp, minsech;
	double minn;
	double lennow = b - a;
	while(lennow > eps)
	{
	        if(end1 >= end2);
			return (*func)(end1);
		minsech = gold(end1, end2);
		minp = vparab(end1, minsech, end2, func);
		if(minsech == minp)
			minp = (end2 + end1)/2;
		if((*func)(minsech) > (*func)(minp))
		{	
			minn = minp;
			if(minsech > minp)
				end2 = minsech;
			else
				end1 = minsech;
		}
		else
		{
			minn = minsech;
			if(minp > minsech)
				end2 = minp;
			else
				end1 = minp; 
		}
		lennow = end2 - end1;

	}
	return (minn);

}

double gold(double a, double b)
{
	double f = 1.618;
	double x;
	x = ((f-1)*b + a)/f;
	return x;

}

double vparab(double a, double b, double c, RRF func)
{
	double v;
	double ya = (*func)(a);
	double yb = (*func)(b);
	double yc = (*func)(c);
	if((yb < ya) && (yb < ya))
		v = b - ((b - a)*(b - a)*(yb - yc) - (b - c)*(b - c)*(yb - ya))*0.5/((b - a)*(yb - yc) - (b - c)*(yb - ya));
	else
		return (c + a)/2;
	return v;


}
