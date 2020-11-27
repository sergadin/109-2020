#include <stdio.h>
#include <math.h>

typedef double (*Fun) (double x);
double komp(Fun *a, int n, double x);

double komp(Fun *a, int n, double x)
{
    int i;
    for(i = n - 1; i >= 0; i--)
	{
        x = a[i](x);
    }
    return x;
}

double f0(double x);
double f1(double x);
double f2(double x);

double f0(double x)
{
	return x * x;
}

double f1(double x)
{
	return x;
}

double f2(double x)
{
	return x + 1;
}

int main()
{
	Fun funcs[] = {f0, f1, f2};
	int n = 3;
	double x = 2;
	
	x = komp(funcs, n, x);
	
	printf("%lf\n", x);
	
	return 0;
}


