#include <stdio.h>

typedef double (*Fun) (double x);
void znach(Fun f, Fun g, double x);
double f1(double x);
double g1(double x);
double f2(double x);
double g2(double x);

void znach(Fun f, Fun g, double x)
{
	int i = 1;
	
	x = f(x);
	
	while(g(x) <= 0)
	{
		x = f(x);
		
		i++;
		
		if(i > 1e7) break;
	}
	
	if(i > 1e7) printf("takogo znach net");
	
	else printf("%lf", g(x));
}

double f1(double x)
{
	return x + 1;
}

double g1(double x)
{
	return x;
}

double f2(double x)
{
	return x + 1;
}

double g2(double x)
{
	return -x*x;
}

int main()
{
	int i;
	double x = -2;
	
	printf("f = x + 1; g = x; x = -2 : ");
	
	znach(f1, g1, x);
	
	printf("\n");
	
	printf("f = x + 1; g = -x*x; x = -2 : ");
	
	znach(f2, g2, x);
	
	return 0;
}
