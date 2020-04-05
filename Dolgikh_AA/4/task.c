#include "task.h"
#include <math.h>

double cosine(double x, double eps)
{
	int n = 0;
	double sum = 1;
	double slagaemoe = 1;

	while(fabs(slagaemoe*x/(n+1)) > eps)
	{
		slagaemoe *= (-1)*x*x/(n+1)/(n+2);
		sum += slagaemoe;
		n += 2;
	}

	return sum;
}
