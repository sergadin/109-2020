#include "prog1-2.h"
#include <math.h>

double newton_method(fpointer f, double left_end, double right_end, double eps)
{
	int i;
	double x, A, B;

	if(fabs(f(left_end)) < eps)
		return left_end;
	if(fabs(f(right_end)) < eps)
		return right_end;
	
	if(f(left_end) * f(right_end) > 0)
		return left_end - 1;

	if(!(deriv(f, left_end, eps) * deriv(f, right_end, eps) > 0))
		return left_end - 1;


	if(f(left_end)*sderiv(f, left_end, eps) > 0)
		x = right_end;
	else
		x = left_end;
	B = x - f(x)/deriv(f, x, eps);
	A = x;

	while(fabs(A - B) > eps)
	{
		
		if(fabs(f(A)) < eps)
			return A;
		if(fabs(f(B)) < eps)
			return B;

		if(!(deriv(f, A, eps) * deriv(f, B, eps) > 0))
			return left_end - 1;


		A = B;
		B = B - f(B)/deriv(f, B, eps);

		if(i > 10000000000) 
			return left_end - 2;
		i++;
	}
	return B;
}
double deriv(fpointer f, double a, double eps)
{
	return (f(a + eps) - f(a - eps)) / (2 * eps);
}
double sderiv(fpointer f, double a, double eps)
{
	return (f(a + eps) - 2 * f(a) + f(a - eps)) / (eps * eps);
}
