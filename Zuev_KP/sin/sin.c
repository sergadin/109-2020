#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"sin.h"
static double modul(double x);

double taylor(double x, double ep, RRFUN ffunc)
{
	double p, s;
	int n = 2;
	p = x;
	s = x;
	while (modul(p)>ep)
	{
		p = -p*x*x/(n*(n+1)); 
		s = s+p;
		//printf("%lf\n", p);
		n = n+2;
	}
	return s;
}

static double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
