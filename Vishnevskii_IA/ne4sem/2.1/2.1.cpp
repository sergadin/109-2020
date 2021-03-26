#include<iostream>

double f(double x)
{
	return x*x;
}

int main()
{
	
	double a, b, n, s, i, h, l;
	
	s = 0;
	
	scanf("%lf%lf%lf", &a, &b, &n);
	
	l = a;
	
	for(i = 0; i < n; i++)
	{
		
		h = f(a + (b - l) / (2*n));
		
		s = s + h * (b - l) / n;
		
		a = a + (b - l) / n;
		
	}
	
	printf("%lf", s);
	
	return 0;
	
}
