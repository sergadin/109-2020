#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prog3-2.h"
#define eps 0.000001


double square5(double x);
double cube(double x);


int main(void)
{
	double  res, c;
	double left_end[5],right_end[5],trueans[5];
	fpointer F[5];
	int i;
	FILE *input;
	
	F[0] = F[1] = sin;
	F[2] = cos;
	F[3] = square5;
	F[4] = cube;
	
	
	if((input = fopen("input.txt","r")) == NULL)
	{
		fprintf(stderr, "File opening error\n");
		fclose(input);
		return -1;
	}
	for(i = 0; i < 5; i++)
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

	for(i = 0; i < 5; i++)
	{
		res = goldenSectionSearch(left_end[i], right_end[i], eps, F[i]);
		fprintf(stdout, "Test #%d \n", i + 1);
		fprintf(stdout, "Function returns (%lf; %lf), the correct answer is %lf \n", res,F[i](res), trueans[i]);
		
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

double square5(double x)
{
	return x*x - 5;
}

double cube(double x)
{
	return x*(x-2)*(x+4);
}
