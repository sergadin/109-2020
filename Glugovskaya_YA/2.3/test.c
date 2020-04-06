#include<stdio.h>
#include<stdlib.h>
#include"test.h"
#include<math.h>


double f (double x)
{
	return sqrt(1+2*x*x-x*x*x);
}
 
double f1 (double x)
{ 
	return sin(1/x)*exp(1/x);
}