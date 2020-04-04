#include "f.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long double f (long double x)
{
	return x*x - 3*x - 4;
}

int g (long double x, long double y)
{
	if(x == y)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int main(){
    double x = 0.5;
    a(f, g, x);
}
