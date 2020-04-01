#include<stdio.h>
#include<stdlib.h>
#include"solve.h"
#include"test.h"
#include<math.h>
#define MAX_IT 1e6

int solve(double a, double b, double eps,double*res,double(*func)(double))
{
	int it;
	double fa=func(a),fb=func(b),c,fc;
	
	if(fa*fb>0)
	{
		printf("cannot find\n");
		return -2;
	} 
	
	for(it=0;it<MAX_IT;it++)
	{
		c=a-fa*(b-a)/(fb-fa);
		fc=func(c);
		
		if(fabs(fc)<eps)break;
		
		if(fa*fc<0)
		{
			b=c;
			fb=fc;
		}
		else
		{
			a=c;
			fa=fc;
		}	
	}
	
	if(it>=MAX_IT)
	{
		printf("not found\n");
		return -1;
	}
	
	*res=c;
	
	return it;
}