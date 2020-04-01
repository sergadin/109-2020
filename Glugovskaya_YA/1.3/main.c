#include<stdio.h>
#include<stdlib.h>
#include"solve.h"
#include<math.h>
#include"test.h"

int main(void)
{
	double a,b,e,x, corAn;
	int res;
	
	printf("input a\n");
	if(scanf("%lf",&a)!=1)
	{
		printf("cannot read a\n");
		return 1;
	}
	printf("input b\n");
	
	if(scanf("%lf",&b)!=1)
	{
		printf("cannot read b\n");
		return 2;
	}
	
	printf("input eps\n");
	
	if(scanf("%lf",&e)!=1)
	{
		printf("cannot read eps\n");
		return 2;
	}
	
	
	res=solve(a,b,e,&x,func);	
	printf("Итерации=%d Корень=%lf\n",res,x);
	corAn=1.70977;
	printf("%lf\n", corAn-x);
	if (fabs(corAn-x)<e) printf("Correct answer\n");
	
	res=solve(a,b,e,&x,func1);
	printf("Итерации=%d Корень=%lf\n",res,x);
	corAn=2.142397398973329;
	if (fabs(corAn-x)<e) printf("Correct answer\n");
	
	res=solve(a,b,e,&x,func2);
	printf("Итерации=%d Корень=%lf\n",res,x);
	corAn=-0.337571;
	if (fabs(corAn-x)<e) printf("Correct answer\n");
	return 0;
}