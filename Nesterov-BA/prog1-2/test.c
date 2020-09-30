#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prog1-2.h"
#define eps 0.000001

double linear(double x);
double exp4(double x);
double square5(double x);
double square36(double x);
double cube7(double x);
double cube125(double x);


int main(void)
{
	double  res, c;
	double left_end[10],right_end[10],trueans[10];
	fpointer F[10];
	int i;
	FILE *input;
	
	F[0] = linear;
	F[1] = F[2] = sin;
	F[3] = F[4] = cos;
	F[5] = exp4;
	F[6] = square5;
	F[7] = square36;
	F[8] = cube7;
	F[9] = cube125;
	
	if((input = fopen("input.txt","r")) == NULL)
	{
		fprintf(stderr, "File opening error\n");
		fclose(input);
		return -1;
	}
	for(i = 0; i < 10; i++)
	{
		if(fscanf(input, "%lf %lf %lf", &left_end[i], &right_end[i], &trueans[i]) != 3)
		{
			fprintf(stderr, "File reading error\n");
			fclose(input);	
			return -1;
		}
		if(left_end[i] > right_end[i])
		{
			c = left_end[i];
			left_end[i] = right_end[i];
			right_end[i] = c;
		}
	}
	fclose(input);

	for(i = 0; i < 10; i++)
	{
		res = newton_method(F[i], left_end[i], right_end[i], eps);
		fprintf(stdout, "Test #%d \n", i + 1);
		fprintf(stdout, "Function returns %lf, the correct answer is %lf \n", res, trueans[i]);
		if (fabs(res-left_end[i]+2)<eps)
		{
			fprintf(stdout, "Computation time exceeded \n");
		}
		if(fabs(res - trueans[i]) > eps)
		{
			fprintf(stdout, "Wrong answer\n");
			return -1;
		}
		else
			fprintf(stdout, "Right answer\n");
	}
	
	return 0;	
}

double linear(double x)
{
	return x;
}
double exp4(double x)
{
	return exp(x) - 4;
}
double square5(double x)
{
	return x*x - 5;
}
double square36(double x)
{
	return x*x - 36;
}
double cube7(double x)
{
	return x*x*x - 7;
}
double cube125(double x)
{
	return x*x*x - 125;
}
