#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prog5-3.h"
#define eps 0.000001

double square5(double x);
double cube(double x);
double exp4(double x);


int main(void)
{
	double  res, argument, difference;
	double trueans[5];
	fpointer F[5];
	int i, n;
	FILE *input;
	
	F[0] = sin;
	F[1] = exp4;
	F[2] = cos;
	F[3] = square5;
	F[4] = cube;
	
	
	if((input = fopen("input.txt","r")) == NULL)
	{
		fprintf(stderr, "File opening error\n");
		fclose(input);
		return -1;
	}
	if(fscanf(input, "%d %lf", &n, &argument) != 2)
	{
		fprintf(stderr, "File reading error\n");
		fclose(input);	
		return -1;
	}
	
	double xarray[n];
	
	for(i = 0; i < n; i++)
	{
		if(fscanf(input, "%lf", &xarray[i]) != 1)
		{
			fprintf(stderr, "File reading error\n");
			fclose(input);	
			return -1;
		}
	}
	fclose(input);
	
	for (i=0; i<n-1; ++i)
	{
		if(fabs(xarray[i] - xarray[i+1]) < eps)
		{
			fprintf(stdout, "Arguments must not be equal \n");
			return -1;
		}
	}
	
		if ((argument<xarray[0])||(xarray[n-1]<argument)) 
	{
			printf("Wrong interval. %lf is not between %lf  and %lf \n",argument,xarray[0] ,xarray[n-1]);
			return -1;
	}
	
	for(i=0; i<5; ++i)
	{
		trueans[i] = F[i](argument);
	}
	
	for(i = 0; i < 5; i++)
	{
		res = ParabolaInterpol(argument, xarray, n, F[i]);
		fprintf(stdout, "Test #%d \n", i + 1);
		fprintf(stdout, "Function returns %lf, the correct answer is %lf \n", res, trueans[i]);
		difference = fabs(res - trueans[i]);
		fprintf(stdout, "The difference is %lf \n", difference);
	}
	
	return 0;	
}

double square5(double x)
{
	return x*x - 5;
}

double cube(double x)
{
	return x*(x-2)*(x+4);
}

double exp4(double x)
{
	return exp(x) - 4;
}
