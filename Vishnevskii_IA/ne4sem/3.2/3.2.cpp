#include<iostream>
#include<math.h>

double f(double x)
{
	return x*x;
}

void min(double a, double b, double e)
{
	
	double c = (1 + sqrt(5)) / 2;
	double g, h;
	
	g = b - (b - a) / c;
	h = a + (b - a) / c;
	
	while(b - a > e)
	{
		if(f(h) > f(g))
		{
			b = h;
			h = g;
			g = b - (b - a) / c;
		}
		else
		{
			a = g;
			g = h;
			h = a + (b - a) / c;
		}
	}
	
	printf("%lf", f(a));
	
}

int main()
{
	
	double a, b, e;
	
	scanf("%lf%lf%lf", &a, &b, &e);
	
	min(a, b, e);
	
	return 0;
	
}
