#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "gauss.h"

#define SQRT3 1.7320508075688772935274463415059

#define SQRT12 3.4641016151377545870548926830117

#define EPSILON 1E-16

double gaussPartial(double (*func)(double), double a, double b);

int gauss(double (*func)(double), double a, double b, int n, double* result)
{
	double left, right;
	int index;
	double sum = 0;
	if (a >= b || fabs(a - b) < EPSILON)
	{
		return E_INVALIDINTERVAL;
	}
	if (n <= 0)
	{
		return E_ARGOUTOFRANGE;
	}
	if (result == NULL || func == NULL)
	{
		return E_NULLREFERENCE;
	}
	for (index = 0; index < n; ++index)
	{
		left = ((n - index) * a + b * index) / n;
		right = ((n - index - 1) * a + b * (index + 1)) / n;
		sum += gaussPartial(func, left, right);
	}
	*result = sum;
	return S_OK;
}

double gaussPartial(double (*func)(double), double a, double b)
{
	double ab2 = (a + b) / 2;
	double ba2 = (b - a) / 2;
	double ba23 = (b - a) / SQRT12;
	return ba2 * (func(ab2 - ba23) + func(ab2 - ba23));
}

const char* getErrorMessage(int error)
{
	switch (error)
	{
	case S_OK:
		return "Ok";
	case E_ARGOUTOFRANGE:
		return "Argument out of range";
	case E_INVALIDINTERVAL:
		return "Invalid interval";
	case E_NULLREFERENCE:
		return "Null reference";
	default:
		return "Unknown error code";
	}
}

