#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double lagrang(double *a, double *b, double x, int n);

double lagrang(double *a, double *b, double x, int n)
{
	int i, j;
	double s, c, d;
	
	s = 0;
	
	for( i = 0; i < n; i++)
	{
		c = 1;
		
		d = 1;
		
		for( j = 0; j < n; j++)
		{
			
			if(i == j)
			{
				
				c = c * 1;
				
				d = d * 1;
				
			}
			else 
			{
				
				c = c * (x - a[j]);
				
				d = d * (a[i] - a[j]);
		
			}
			
		}
		
		s = s + b[i] * c / d;
		
	}
	
	return s;
	
}

int main()
{
	int n, i;
	
	scanf("%d", &n);
	
	double *a, *b, x;
	
	a = (double*)malloc(n*sizeof(double));
	b = (double*)malloc(n*sizeof(double));
	
	for(i = 0; i < n; i++)
	{
		scanf("%lf", &a[i]);
	}
	
	for(i = 0; i < n; i++)
	{
		scanf("%lf", &b[i]);
	}
	
	scanf("%lf", &x);
	
	printf("%lf", lagrang(a, b, x, n));
	
	return 0;
}
