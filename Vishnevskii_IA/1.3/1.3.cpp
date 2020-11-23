#include <iostream>
#include <math.h>

double f(double x)
{
	return x*x;
}

double kor(double a, double b, double e)
{
	
	while(fabs(b - a) > e)
	{
		
		a = b - (b - a) * f(b) / (f(b) - f(a));
		
		b = a - (a - b) * f(a) / (f(a) - f(b));
		
	}
	
	return b;
	
}

int main()
{
	
	double a, b, e;
	
	scanf("%lf%lf%lf", &a, &b, &e);
	
	printf("%lf", kor(a, b, e));
	
	return 0;
}

