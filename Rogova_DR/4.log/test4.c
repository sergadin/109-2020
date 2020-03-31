#include<math.h>
#include<stdio.h>
#include"log4.h"



int main(void)
{
	ErrorCode ec;
	int i;
	double res;
	double x[] = {-1, 1, 200};
	double eps = 0.001;
	for(i = 0; i < 3; i++)
	{
		res = teyl(x[i], eps, &ec);
		if(ec != MF_OK)
		{
			printf("Upsss.....\n");
		}
		else
			printf("correct:\n%lf\nmy:\n%lf\n", log(1 + x[i]), res);

	}

}
