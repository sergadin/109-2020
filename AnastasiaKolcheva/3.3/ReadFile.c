#include <stdio.h>
#include <math.h>
#include "minimum.h"


double function1(double x)
{
	return x * x;
}

double function2(double x)
{
	return x * x * x;
}

double function3(double x)
{
	return - x * x ;
}

double function4(double x)
{
	return - x * x * x;
}


int main(int argc, char** argv)
{
	int number_of_functions = 4;
	func functions[4] = {function1, function2, function3, function4};
	double A[4] = {0 , 0, 0, 0};
	double B[4] = {5, 5, 5, 5};
	double answers[4] = {0, 0 , -25, -125};
	int index;
	double result;
	double epsilon = 0.001;
	

	printf("                     Result             |            Correct result            |          Accuracy\n");
	printf("      ----------------------------------+--------------------------------------+------------------------------\n");

	for (index = 0; index < number_of_functions; index++)
	{
		result = findMinimum(functions[index], A[index], B[index], epsilon);
		printf("                %12lf            |           %12lf               |      %12lf\n", result, answers[index], epsilon);
		printf("      ----------------------------------+--------------------------------------+------------------------------\n");
	}

	return 0;
}

