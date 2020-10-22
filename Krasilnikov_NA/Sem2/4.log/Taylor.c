#include <stdio.h>
#include <math.h>
#include"Taylor.h"

double series(double x, double epsilon, ErrorCode *error)
{
	*error = LOG_OK;
	int n = 1;
	double result = 0;
	double pogreshnost = (x - 1);
	double memory = (x - 1);
	if (fabs(memory) >= 1)
	{
		*error = LOG_NEOK;
		return 0;
	}
	while (fabs(pogreshnost) >= epsilon * 0.1)
	{
		pogreshnost = memory/n;
		if (n % 2 == 0)
		{
			pogreshnost = (-1) * pogreshnost;
		}
		result += pogreshnost;
		n++;
		memory *= (x - 1);
		if (n >= 100000)
		{
			*error = LOG_NEOK;
			break;
		}
	}
	return result;
}
