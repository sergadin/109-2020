#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double cos(double x, double e)
{
	
	double b = 1, s = 0, i = 0;
	
	while(fabs(b) > e)
	{
		
		s = s + b;
		
		i++;
		
		b = (b * (-1) * pow(x, 2)) / (2 * i * (2 * i - 1));
		
	}
	
	return s;
	
}

int main()
{
	double x, e;
	
	scanf("%lf%lf", &x, &e);
	
	printf("%lf", cos(x, e));
	
	return 0;
}
