#include <stdio.h>
#include <math.h>
#include "gauss.h"

double function1(double x)
{
	return x * x * x;
}

double function2(double x)
{
	return x * x ;
}

double function3(double x)
{
	return sin(x);
}

double function4(double x)
{
	return cos(x);
}


void main(void)
{
	int number_of_functions = 4;
	func functions[4] = { function1, function2, function3, function4 };
	double A[4] = { 0 , 0, 0, 0 };
	double B[4] = { 5, 5, 5, 5 };
	double answers[4] = { 156.250000, 41.666667, 0.716338, -0.958924};
	int index;
	double result;
	int N = 5000000;


	printf("                   Result              |            Correct result            \n");
	printf("      ---------------------------------+--------------------------------------\n");

	for (index = 0; index < number_of_functions; index++)
	{
		int error = gauss(functions[index], A[index], B[index], N, &result);
		if (!error)
		{
			printf("               %12lf            |           %12lf               \n", result, answers[index]);
			printf("      ---------------------------------+--------------------------------------\n");
		}
		else
		{
			printf("error: %s (%d)\n", getErrorMessage(error), error);
		}
	}

}