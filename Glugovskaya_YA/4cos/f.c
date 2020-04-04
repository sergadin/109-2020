#include "f.h"

double f(double x, double eps)
{
	double result;
	int sgn = 0, sign = 0;

	if(x < 0)
	{
		x *= (-1);
	}

	x = fmod(x,2*M_PI);

	if(x >= M_PI)
	{
		x = 2 * M_PI - x;
	}
	if(x >= M_PI/2)
	{
		x = M_PI - x;
		sign = 1; 
	}

		x = M_PI/2 - x;

		/*result = 2 * (2 * (4 * sinus(x/16,eps) * cosinus(x/16,eps) * 
		(1.0 - 2 * sinus(x/16,eps) * sinus(x/16,eps))) * (1 - 2 * 
		(2 * sinus(x/16,eps) * cosinus(x/16,eps)) * (2 * sinus(x/16,eps) * cosinus(x/16,eps)))) * 
		(1 - 2 * (4 * sinus(x/16,eps) * cosinus(x/16,eps) * (1.0 - 2 * sinus(x/16,eps) * sinus(x/16,eps))) * 
		(4 * sinus(x/16,eps) * cosinus(x/16,eps) * (1.0 - 2 * sinus(x/16,eps) * sinus(x/16,eps))));*/
		result = 2 * (2 * (2 * (4 * sinus(x/32,eps) * cosinus(x/32,eps) * 
		(1.0 - 2 * sinus(x/32,eps) * sinus(x/32,eps))) * (1 - 2 * 
		(2 * sinus(x/32,eps) * cosinus(x/32,eps)) * (2 * sinus(x/32,eps) * cosinus(x/32,eps)))) * 
		(1 - 2 * (4 * sinus(x/32,eps) * cosinus(x/32,eps) * (1.0 - 2 * sinus(x/32,eps) * sinus(x/32,eps))) * 
		(4 * sinus(x/32,eps) * cosinus(x/32,eps) * (1.0 - 2 * sinus(x/32,eps) * sinus(x/32,eps)))))
		* (1 - 2 * (2 * (4 * sinus(x/32,eps) * cosinus(x/32,eps) * 
		(1.0 - 2 * sinus(x/32,eps) * sinus(x/32,eps))) * (1 - 2 * 
		(2 * sinus(x/32,eps) * cosinus(x/32,eps)) * (2 * sinus(x/32,eps) * cosinus(x/32,eps)))) * (2 * (4 * sinus(x/32,eps) * cosinus(x/32,eps) * 
		(1.0 - 2 * sinus(x/32,eps) * sinus(x/32,eps))) * (1 - 2 * 
		(2 * sinus(x/32,eps) * cosinus(x/32,eps)) * (2 * sinus(x/32,eps) * cosinus(x/32,eps)))));
	
	if(sign == 1) return result * (-1);
	return result;
}

double sinus(double x, double eps)
{
	double result = 0.0, m = x;
	int i = 1;
	while(fabs(m) > eps)
	{
		//printf("l\n");
		result += m;
		m = (-1) * m * x * x / ((i+1) * (i+2));
		i += 2;
	}
	return result;
}
double cosinus(double x, double eps)
{
	double result = 0.0, m = 1.0;
	int i = 0;
	while(fabs(m) > eps)
	{
		//printf("l\n");
		result += m;
		m = (-1) * m * x * x / ((i+1) * (i+2));
		i += 2;
	}
	return result;
}